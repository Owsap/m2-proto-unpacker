///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

static constexpr std::string_view VERSION_STRING = "1.2.0";
static constexpr std::string_view PROTO_VERSION_STRING = "25.2.12";

/*
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
