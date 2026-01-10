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

#include <lzo/lzoconf.h>
#include <lzo/lzo1x.h>

#define FOURCC_LZO MAKEFOURCC('M','C','O','Z')

class LZOAlgorithm : public CompressionAlgorithm
{
public:
	LZOAlgorithm() {}
	virtual ~LZOAlgorithm() {}

	virtual bool decompress(const uint8_t* input, uint32_t compressed_size, std::vector<uint8_t>& output, uint32_t expected_size) override;

	virtual uint32_t get_fourcc() const override;
	virtual std::size_t get_max_size(std::size_t size) const override;
};
