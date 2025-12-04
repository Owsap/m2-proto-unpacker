///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <proto_loader.h>

#include <compression/compression.h>
#include <spdlog/spdlog.h>

#include <fstream>

ProtoLoader::ProtoLoader()
{
	m_item_proto_key.fill(0);
	m_mob_proto_key.fill(0);
}

void ProtoLoader::set_keys(const ProtoKey& item_proto_key, const ProtoKey& mob_proto_key)
{
	m_item_proto_key = item_proto_key;
	m_mob_proto_key = mob_proto_key;
}

bool ProtoLoader::load_item_proto()
{
	return load("item_proto", ProtoType::ITEM, m_item_proto_key);
}

bool ProtoLoader::load_mob_proto()
{
	return load("mob_proto", ProtoType::MOB, m_mob_proto_key);
}

bool ProtoLoader::load(const char* filename, ProtoType type, const ProtoKey& key)
{
	std::ifstream f(filename, std::ios::binary);
	if (!f)
		return false;

	uint32_t fourcc = 0;
	f.read(reinterpret_cast<char*>(&fourcc), sizeof(fourcc));

	uint32_t version = 0;
	uint32_t stride = 0;

	if (type == ProtoType::ITEM)
	{
		if (fourcc == MAKEFOURCC('M', 'I', 'P', 'X'))
		{
			f.read(reinterpret_cast<char*>(&version), sizeof(version));
			f.read(reinterpret_cast<char*>(&stride), sizeof(stride));

			if (version != 1)
			{
				spdlog::error("version mismatch");
				return false;
			}

			if (stride != sizeof(ItemProto))
			{
				spdlog::error("stride mismatch");
				return false;
			}
		}
		else if (fourcc != MAKEFOURCC('M', 'I', 'P', 'T'))
		{
			spdlog::error("invalid proto");
			return false;
		}
	}
	else if (type == ProtoType::MOB)
	{
		if (fourcc != MAKEFOURCC('M', 'M', 'P', 'T'))
		{
			spdlog::error("invalid proto (wrong FOURCC)");
			return false;
		}
	}

	uint32_t count = 0;
	uint32_t data_size = 0;

	f.read(reinterpret_cast<char*>(&count), sizeof(count));
	f.read(reinterpret_cast<char*>(&data_size), sizeof(data_size));

	std::vector<uint8_t> compressed(data_size);
	f.read(reinterpret_cast<char*>(compressed.data()), data_size);

	if (!f)
	{
		spdlog::error("failed to load {}", filename);
		return false;
	}

	Compression compression;
	std::vector<uint8_t> out;

	if (!compression.decrypt_and_decompress(compressed.data(), data_size, key, out))
		return false;

	if (type == ProtoType::ITEM)
	{
		uint32_t expected_size = count * sizeof(ItemProto);
		if (out.size() != expected_size)
			return false;

		ItemProto* ptr = reinterpret_cast<ItemProto*>(out.data());
		for (uint32_t i = 0; i < count; ++i)
			m_item_proto_map.emplace(ptr[i].vnum, ptr[i]);
	}
	else if (type == ProtoType::MOB)
	{
		uint32_t expected_size = count * sizeof(MobProto);
		if (out.size() != expected_size)
			return false;

		MobProto* ptr = reinterpret_cast<MobProto*>(out.data());
		for (uint32_t i = 0; i < count; ++i)
			m_mob_proto_map.emplace(ptr[i].vnum, ptr[i]);
	}

	return true;
}
