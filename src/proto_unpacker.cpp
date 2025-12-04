///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <proto_unpacker.h>
#include <utils.h>

#include <fstream>
#include <nlohmann/json.hpp>

ProtoUnpacker::ProtoUnpacker()
	: m_item_proto_path("item_proto")
	, m_mob_proto_path("mob_proto")
	, m_json_path("tea-keys.json")
	, m_output_dir("./")
{
}

void ProtoUnpacker::run()
{
	main_logger()->debug("working directory: {}", std::filesystem::current_path().string());

	Timer timer;
	timer.reset();

	ProtoKey item_proto_key{};
	ProtoKey mob_proto_key{};

	if (!load_keys_from_json(m_json_path, item_proto_key, mob_proto_key))
	{
		main_logger()->error("failed to load key file {}", m_json_path);
		return;
	}

	m_proto_loader.set_keys(item_proto_key, mob_proto_key);
	m_proto_dumper.set_output_dir(m_output_dir);

	main_logger()->info("loading item_proto...");
	if (m_proto_loader.load_item_proto(m_item_proto_path))
		m_proto_dumper.dump_item_proto(m_proto_loader.get_item_proto_map());
	else
		main_logger()->error("failed to load {}", m_item_proto_path);

	main_logger()->info("completed in {:.2f} seconds.", timer.elapsed_seconds());

	detail_logger()->info("");
	detail_logger()->info("........................................");
	detail_logger()->info("");

	timer.reset();

	main_logger()->info("loading mob_proto...");
	if (m_proto_loader.load_mob_proto(m_mob_proto_path))
		m_proto_dumper.dump_mob_proto(m_proto_loader.get_mob_proto_map());
	else
		main_logger()->error("failed to load {}", m_mob_proto_path);

	main_logger()->info("completed in {:.2f} seconds.", timer.elapsed_seconds());
}

bool ProtoUnpacker::load_keys_from_json(const std::string& path, ProtoKey& item_proto_key, ProtoKey& mob_proto_key)
{
	std::ifstream f(path);
	if (!f.is_open())
		return false;

	try
	{
		nlohmann::json j;
		f >> j;

		if (!j.contains("item_proto") || !j["item_proto"].is_array() || j["item_proto"].size() != 4)
		{
			main_logger()->error("{}: 'item_proto' must be an array of 4 integers.", path);
			return false;
		}

		if (!j.contains("mob_proto") || !j["mob_proto"].is_array() || j["mob_proto"].size() != 4)
		{
			main_logger()->error("{}: 'mob_proto' must be an array of 4 integers.", path);
			return false;
		}

		for (size_t i = 0; i < 4; ++i)
		{
			if (!j["item_proto"][i].is_number_unsigned() || !j["mob_proto"][i].is_number_unsigned())
			{
				main_logger()->error("{}: values must be positive integers.", path);
				return false;
			}

			item_proto_key[i] = j["item_proto"][i].get<uint32_t>();
			mob_proto_key[i] = j["mob_proto"][i].get<uint32_t>();
		}

		return true;
	}
	catch (const std::exception& e)
	{
		main_logger()->error("failed to parse {}: {}", path, e.what());
		return false;
	}

	return true;
}

void ProtoUnpacker::set_item_proto_path(const std::string& path)
{
	m_item_proto_path = path;
}

void ProtoUnpacker::set_mob_proto_path(const std::string& path)
{
	m_mob_proto_path = path;
}

void ProtoUnpacker::set_json_path(const std::string& path)
{
	m_json_path = path;
}

void ProtoUnpacker::set_output_dir(const std::string& dir)
{
	m_output_dir = dir;
}
