///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <compression/compression.h>
#include <compression/lzo_algorithm.h>

bool LZOAlgorithm::decompress(const uint8_t* input, uint32_t compressed_size, std::vector<uint8_t>& output, uint32_t expected_size)
{
	output.resize(expected_size);

	lzo_uint out_size = expected_size;

	int ret = lzo1x_decompress(input, compressed_size, output.data(), &out_size, nullptr);
	if (ret != LZO_E_OK)
		return false;

	if (out_size != expected_size)
		return false;

	return true;
}

uint32_t LZOAlgorithm::get_fourcc() const
{
	return FOURCC_LZO;
}

std::size_t LZOAlgorithm::get_max_size(std::size_t size) const
{
	return size + (size / 64 + 16 + 3);
}
