///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include <compression/compression_algorithm.h>

#define MAKEFOURCC(ch0, ch1, ch2, ch3) \
	((uint32_t)(uint8_t)(ch0) | ((uint32_t)(uint8_t)(ch1) << 8) | \
	((uint32_t)(uint8_t)(ch2) << 16) | ((uint32_t)(uint8_t)(ch3) << 24 ))

class Compression
{
public:
	Compression();
	~Compression();

	bool decrypt_and_decompress(const uint8_t* encrypted, uint32_t encrypted_size, const uint32_t key[4], std::vector<uint8_t>& output);

	void register_algorithm(CompressionAlgorithm* algo);

	inline std::string fourcc_to_string(uint32_t fourcc)
	{
		std::string out;
		out.reserve(4);

		for (int i = 0; i < 4; i++)
		{
			uint8_t c = (fourcc >> (i * 8)) & 0xFF;

			if (c >= 32 && c <= 126)
				out.push_back(static_cast<char>(c));
			else
				out.push_back('.');
		}

		return out;
	}

private:
#pragma pack(push, 4)
	struct Header
	{
		uint32_t fourcc;
		uint32_t encrypt_size;
		uint32_t compressed_size;
		uint32_t real_size;
	};
#pragma pack(pop)

	CompressionAlgorithm* find_algorithm(uint32_t fourcc) const;

	void tea_decrypt(uint8_t* dest, const uint8_t* src, uint32_t size, const uint32_t key[4]);

private:
	std::vector<CompressionAlgorithm*> m_algorithms;
};
