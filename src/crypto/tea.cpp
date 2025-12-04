///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <crypto/tea.h>
#include <cstring>

namespace tea
{
	void decode(const uint32_t sz, const uint32_t sy, const uint32_t* key, uint32_t* dest)
	{
		uint32_t y = sy;
		uint32_t z = sz;
		uint32_t sum = DELTA * ROUNDS;
		uint32_t n = ROUNDS;

		while (n-- > 0)
		{
			z -= ((y << 4) ^ (y >> 5)) + y ^ (sum + key[(sum >> 11) & 3]);
			sum -= DELTA;
			y -= ((z << 4) ^ (z >> 5)) + z ^ (sum + key[sum & 3]);
		}

		dest[0] = y;
		dest[1] = z;
	}

	int decrypt(uint32_t* dest, const uint32_t* src, const uint32_t* key, int size)
	{
		int resize = (size % 8 == 0) ? size : size + 8 - (size % 8);

		for (int i = 0; i < (resize >> 3); i++, dest += 2, src += 2)
			decode(src[1], src[0], key, dest);

		return resize;
	}
}
