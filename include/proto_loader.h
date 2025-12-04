///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

#include <array>

#include <protos/item_proto.h>
#include <protos/mob_proto.h>

enum ProtoType
{
	PROTO_TYPE_ITEM,
	PROTO_TYPE_MOB,
	PROTO_TYPE_MAX_NUM,
};

using ProtoKey = std::array<uint32_t, 4>;

class ProtoLoader
{
public:
	ProtoLoader();

	void set_keys(const ProtoKey& item_proto_key, const ProtoKey& mob_proto_key);

	bool load_item_proto();
	bool load_mob_proto();

	const ItemProtoMap& get_item_proto_map() const { return m_item_proto_map; }
	const MobProtoMap& get_mob_proto_map() const { return m_mob_proto_map; }

private:
	bool load(const char* filename, uint8_t type, const ProtoKey& key);

	ItemProtoMap m_item_proto_map;
	MobProtoMap m_mob_proto_map;

	ProtoKey m_item_proto_key;
	ProtoKey m_mob_proto_key;
};
