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
#include <compression/compression_algorithm.h>

#include <snappy/snappy-c.h>

#define FOURCC_SNAPPY MAKEFOURCC('M','C','S','P')

class SnappyAlgorithm : public CompressionAlgorithm
{
public:
	SnappyAlgorithm() {}
	virtual ~SnappyAlgorithm() {}

	virtual bool decompress(const uint8_t* input, uint32_t compressed_size, std::vector<uint8_t>& output, uint32_t expected_size) override;

	virtual uint32_t get_fourcc() const override;
	virtual std::size_t get_max_size(std::size_t size) const override;
};
