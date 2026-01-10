///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

#include <version.h>

enum
{
	CHARACTER_NAME_MAX_LEN = 24,
	CHARACTER_FOLDER_MAX_LEN = 64,

	MOB_SKILL_MAX_NUM = 5,

	ITEM_NAME_MAX_LEN = 24,
	ITEM_LIMIT_MAX_NUM = 2,

#if SCHEMA_VER_AT_LEAST(19, 5, 0)
	ITEM_APPLY_MAX_NUM = 4,
#else
	ITEM_APPLY_MAX_NUM = 3,
#endif

#if SCHEMA_VER_AT_LEAST(20, 4, 0)
#if SCHEMA_VER_AT_LEAST(25, 2, 0)
	ITEM_VALUES_MAX_NUM = 12,
#else
	ITEM_VALUES_MAX_NUM = 10,
#endif
#else
	ITEM_VALUES_MAX_NUM = 6,
#endif

#if SCHEMA_VER_AT_LEAST(20, 4, 0)
	ITEM_SOCKET_MAX_NUM = 6,
#else
	ITEM_SOCKET_MAX_NUM = 3,
#endif
};
