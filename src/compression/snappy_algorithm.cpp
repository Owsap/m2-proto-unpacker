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

bool SnappyAlgorithm::decompress(
	const uint8_t* input,
	uint32_t compressedSize,
	std::vector<uint8_t>& output,
	uint32_t expectedSize)
{
	output.resize(expectedSize);

	size_t outSize = expectedSize;
	snappy_status ret = snappy_uncompress(
		reinterpret_cast<const char*>(input),
		compressedSize,
		reinterpret_cast<char*>(output.data()),
		&outSize
	);

	if (ret != SNAPPY_OK)
		return false;

	if (outSize != expectedSize)
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
