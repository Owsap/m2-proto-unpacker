///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

class CompressionAlgorithm
{
public:
	virtual ~CompressionAlgorithm() {}

	virtual bool decompress(
		const uint8_t* input,
		uint32_t compressedSize,
		std::vector<uint8_t>& output,
		uint32_t expectedSize) = 0;

	virtual uint32_t get_fourcc() const = 0;
	virtual std::size_t get_max_size(std::size_t size) const = 0;
};
