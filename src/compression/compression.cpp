///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <compression/compression.h>
#include <compression/snappy_algorithm.h>

#include <crypto/tea.h>
#include <utils.h>

Compression::Compression()
{
	register_algorithm(new SnappyAlgorithm());
}

Compression::~Compression()
{
	for (size_t i = 0; i < m_algorithms.size(); ++i)
		delete m_algorithms[i];
}

void Compression::register_algorithm(CompressionAlgorithm* algo)
{
	m_algorithms.push_back(algo);
}

CompressionAlgorithm* Compression::find_algorithm(uint32_t fourcc) const
{
	for (size_t i = 0; i < m_algorithms.size(); ++i)
	{
		if (m_algorithms[i]->get_fourcc() == fourcc)
			return m_algorithms[i];
	}
	return 0;
}

void Compression::tea_decrypt(uint8_t* dest, const uint8_t* src, uint32_t size, const ProtoKey& key)
{
	if (!dest || !src || size == 0)
		return;

	tea::decrypt(reinterpret_cast<uint32_t*>(dest), reinterpret_cast<const uint32_t*>(src), key, static_cast<int>(size));
}

bool Compression::decrypt_and_decompress(const uint8_t* encrypted, uint32_t encrypted_size, const ProtoKey& key, std::vector<uint8_t>& output)
{
	if (!encrypted)
	{
		main_logger()->critical("input buffer is NULL.");
		return false;
	}

	if (encrypted_size < sizeof(Header) + sizeof(uint32_t))
	{
		main_logger()->critical("input buffer too small ({} bytes).", encrypted_size);
		return false;
	}

	const Header* header = reinterpret_cast<const Header*>(encrypted);

	uint32_t real_size = header->real_size;
	uint32_t compressed_size = header->compressed_size;

	detail_logger()->info("{:<18} : {}", "size.real", real_size);
	detail_logger()->info("{:<18} : {}", "size.compressed", compressed_size);
	detail_logger()->info("{:<18} : {}", "size.encrypted", header->encrypt_size);

	main_logger()->debug("compression ratio: {:.2f}x ({} -> {} bytes)",
		double(real_size) / compressed_size, compressed_size, real_size);

	if (real_size == 0)
	{
		main_logger()->critical("real size is zero — invalid data");
		return false;
	}

	output.clear();
	output.resize(real_size);

	std::vector<uint8_t> decrypted;
	const uint8_t* compressed_ptr = nullptr; // pointer to the actual compressed bytes that the algorith will decompress.
	uint32_t inner_fourcc = 0; // temporary output buffer for decompressed data.

	if (header->encrypt_size != 0)
	{
		detail_logger()->info("{:<18} : yes ({} bytes)", "encrypted", header->encrypt_size);

		const uint8_t* encrypted_region = encrypted + sizeof(Header);

		decrypted.resize(header->encrypt_size);
		tea_decrypt(decrypted.data(), encrypted_region, header->encrypt_size, key);

		inner_fourcc = *reinterpret_cast<uint32_t*>(decrypted.data());
		compressed_ptr = decrypted.data() + sizeof(uint32_t);
	}
	else
	{
		detail_logger()->info("{:<18} : no", "encrypted");

		inner_fourcc = *reinterpret_cast<const uint32_t*>(encrypted + sizeof(Header));
		compressed_ptr = encrypted + sizeof(Header) + sizeof(uint32_t);
	}

	detail_logger()->info("{:<18} : 0x{:08X} ({})", "inner.fourcc", inner_fourcc, fourcc_to_string(inner_fourcc));

	CompressionAlgorithm* algo = find_algorithm(inner_fourcc);
	if (!algo)
	{
		main_logger()->error("invalid TEA keys or corrupted file.");
		main_logger()->critical("algorithm : NONE (unsupported FOURCC)");
		return false;
	}

	if (FOURCC_SNAPPY == algo->get_fourcc())
		detail_logger()->info("{:<18} : Snappy", "algorithm");
	else
		detail_logger()->info("{:<18} : Unknown", "algorithm");

	std::vector<uint8_t> tmp;
	if (!algo->decompress(compressed_ptr, compressed_size, tmp, real_size))
	{
		main_logger()->error("decompression FAILED");
		return false;
	}

	if (tmp.size() != real_size)
	{
		main_logger()->critical("size mismatch: got {}, expected {}", tmp.size(), real_size);
		return false;
	}

	detail_logger()->info("{:<18} : OK ({} bytes)", "decompress", real_size);

	output.swap(tmp);
	return true;
}
