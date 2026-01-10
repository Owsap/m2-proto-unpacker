///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

#include <utils.h>

// Proto schema history:
// Version 14.11 (mob claw, bleeding resist)
// Version 15.5 (mob scale)
// Version 16.0 (item mask types and subtypes)
// Version 17.5 (mob points, element att, resist)
// Version 18.3 (mob fist resist)
// Version 19.2 (item material67)
// Version 19.5 (item apply_max_num4)
// Version 19.5 (hit_range)
// Version 20.4 (mob sungma stats, exp, item value10, item socket6)
// Version 25.2 (item value12)

#define SCHEMA_VER_MAJOR 25
#define SCHEMA_VER_MINOR 2
#define SCHEMA_VER_PATCH 15

#define SCHEMA_VER_ENCODE(m, n, p) ((m)*1000000 + (n)*1000 + (p))
#define SCHEMA_VER_CURRENT \
	SCHEMA_VER_ENCODE(SCHEMA_VER_MAJOR, SCHEMA_VER_MINOR, SCHEMA_VER_PATCH)

#define SCHEMA_VER_AT_LEAST(m, n, p) \
	(SCHEMA_VER_CURRENT >= SCHEMA_VER_ENCODE(m, n, p))

#define SCHEMA_VER_STRING \
	STRINGIFY(SCHEMA_VER_MAJOR) "." \
	STRINGIFY(SCHEMA_VER_MINOR) "." \
	STRINGIFY(SCHEMA_VER_PATCH)

static constexpr std::string_view VERSION_STRING = "1.4.0";

/*
* [MINOR] Add proto version–aware structs and enums. - v1.4.0
* [MINOR] Add LZO compression. - v1.3.0
* [PATCH] Correct ApplyTypes & TItemTable structure, ITEM_VALUES_MAX_NUM = 12. - v1.2.1
* [MINOR] Add mob_proto reference overwrite support via TSV (--overwrite-mob-proto). - v1.2.0
* [PATCH] Fixed mob_proto dump. - v1.1.4
* [PATCH] Fixed `ITEM_SPECIAL_DS` subtypes. - v1.1.3
* [PATCH] Optimize dump functions for performance and readability. - v1.1.2
* [PATCH] Add additional verbose logging for proto loading and compression. - v1.1.1
* [MINOR] Add CLI args for paths, verbosity, silent mode, help and version. - v1.1.0
* [PATCH] Refactor integer proto type with scoped enum class. - v1.0.3
* [PATCH] Refactor raw key arrays with ProtoKey std::array type. - v1.0.2
* [PATCH] Remove unused TEA encode and encrypt functions. - v1.0.1
* [MAJOR] Initial commit. - v1.0.0
*/
