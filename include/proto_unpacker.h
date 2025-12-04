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
	ProtoUnpacker();

	void run();

	bool load_keys_from_json(const std::string& path, ProtoKey& item_proto_key, ProtoKey& mob_proto_key);

	void set_item_proto_path(const std::string& path);
	void set_mob_proto_path(const std::string& path);
	void set_json_path(const std::string& path);
	void set_output_dir(const std::string& dir);

private:
	ProtoLoader m_proto_loader;
	ProtoDumper m_proto_dumper;

	std::string m_item_proto_path;
	std::string m_mob_proto_path;
	std::string m_json_path;
	std::string m_output_dir;
};
