///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <compression/compression.h>
#include <compression/snappy_algorithm.h>

#include <snappy/snappy-c.h>

bool SnappyAlgorithm::decompress(const uint8_t* input, uint32_t compressed_size, std::vector<uint8_t>& output, uint32_t expected_size)
{
	output.resize(expected_size);

	size_t out_size = expected_size;
	snappy_status ret = snappy_uncompress(reinterpret_cast<const char*>(input), compressed_size, reinterpret_cast<char*>(output.data()), &out_size);

	if (ret != SNAPPY_OK)
		return false;

	if (out_size != expected_size)
		return false;

	return true;
}

uint32_t SnappyAlgorithm::get_fourcc() const
{
	return FOURCC_SNAPPY;
}

std::size_t SnappyAlgorithm::get_max_size(std::size_t size) const
{
	return snappy_max_compressed_length(size);
}
