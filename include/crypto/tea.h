///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

#include <cstdint>
#include <cstddef>

namespace tea
{
	constexpr uint32_t DELTA = 0x9E3779B9;
	constexpr uint32_t ROUNDS = 32;

	int encrypt(uint32_t* dest, const uint32_t* src, const uint32_t* key, int size);
	int decrypt(uint32_t* dest, const uint32_t* src, const uint32_t* key, int size);
}
