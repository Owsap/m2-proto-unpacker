///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

#include <protos/item_proto.h>
#include <protos/mob_proto.h>

class ProtoDumper
{
public:
	void dump_item_proto(const ItemProtoMap& map);
	void dump_mob_proto(const MobProtoMap& map);

private:
	void dump_item_names() const;
	void dump_item_table() const;

	void dump_mob_names() const;
	void dump_mob_table() const;

private:
	const ItemProtoMap* m_item_proto_map = nullptr;
	const MobProtoMap* m_mob_proto_map = nullptr;
};