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

#include <proto_loader.h>
#include <proto_dumper.h>

#include <spdlog/spdlog.h>

class ProtoUnpacker
{
public:
	ProtoUnpacker() = default;

	void run();
	bool load_keys_from_json(const std::string& path, ProtoKey& item_proto_key, ProtoKey& mob_proto_key);

private:
	ProtoLoader m_proto_loader;
	ProtoDumper m_proto_dumper;
};
