///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <proto_loader.h>

#include <compression/compression.h>
#include <utils.h>
#include <csv_utils.h>

#include <fstream>
#include <filesystem>

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

bool ProtoLoader::load_item_proto(const std::string& path)
{
	main_logger()->debug("loading item_proto from: {} ({} bytes)", path, std::filesystem::file_size(path));
	main_logger()->debug("using TEA key (item_proto): [{}, {}, {}, {}]",
		m_item_proto_key[0], m_item_proto_key[1],
		m_item_proto_key[2], m_item_proto_key[3]);

	return load(path, ProtoType::ITEM, m_item_proto_key);
}

bool ProtoLoader::load_mob_proto(const std::string& path)
{
	main_logger()->debug("loading mob_proto from: {} ({} bytes)", path, std::filesystem::file_size(path));
	main_logger()->debug("using TEA key (mob_proto): [{}, {}, {}, {}]",
		m_mob_proto_key[0], m_mob_proto_key[1],
		m_mob_proto_key[2], m_mob_proto_key[3]);

	return load(path, ProtoType::MOB, m_mob_proto_key);
}

MobTableRefMap ProtoLoader::load_mob_proto_reference_tsv(const std::string& path) const
{
	MobTableRefMap out;

	csv::CSVFormat format;
	format.delimiter('\t');
	format.header_row(0);

	csv::CSVReader reader(path, format);

	for (csv::CSVRow& row : reader)
	{
		const uint32_t vnum = util::checked_u32(util::csv_i64(row, "Vnum"));

		MobTableRef ref{};

		const std::string folder = row["Folder"].get<>();
		std::strncpy(ref.folder, folder.c_str(), CHARACTER_FOLDER_MAX_LEN);
		ref.folder[CHARACTER_FOLDER_MAX_LEN] = '\0';

		ref.gold_min = util::checked_u32(util::csv_i64(row, "MinGold"));
		ref.gold_max = util::checked_u32(util::csv_i64(row, "MaxGold"));
		ref.resurrection_vnum = util::checked_u32(util::csv_i64(row, "ResurrectionVnum"));
		ref.polymorph_item_vnum = util::checked_u32(util::csv_i64(row, "PolymorphItem"));

		for (int i = 0; i < MOB_SKILL_MAX_NUM; ++i)
		{
			ref.skills[i].level = util::checked_u8(util::csv_i64(row, "SkillLevel" + std::to_string(i)));
			ref.skills[i].vnum = util::checked_u32(util::csv_i64(row, "SkillVnum" + std::to_string(i)));
		}

		ref.berserk_point = util::checked_u8(util::csv_i64(row, "SpBerserk"));
		ref.stoneskin_point = util::checked_u8(util::csv_i64(row, "SpStoneSkin"));
		ref.godspeed_point = util::checked_u8(util::csv_i64(row, "SpGodSpeed"));
		ref.deathblow_point = util::checked_u8(util::csv_i64(row, "SpDeathBlow"));
		ref.revive_point = util::checked_u8(util::csv_i64(row, "SpRevive"));
		ref.heal_point = util::checked_u8(util::csv_i64(row, "SpHeal"));

		ref.r_att_speed_p = util::checked_u8(util::csv_i64(row, "RAtkSpeed"));
		ref.r_cast_speed = util::checked_u8(util::csv_i64(row, "RCastSpeed"));
		ref.r_hp_regen = util::checked_u8(util::csv_i64(row, "RHPRegen"));

		ref.hit_range = row["HitRange"].get<float>();

		out.emplace(vnum, ref);
	}

	return out;
}

bool ProtoLoader::load(const std::string& path, ProtoType type, const ProtoKey& key)
{
	std::ifstream f(path, std::ios::binary);
	if (!f)
		return false;

	uint32_t fourcc = 0;
	f.read(reinterpret_cast<char*>(&fourcc), sizeof(fourcc));

	uint32_t version = 0;
	uint32_t stride = 0;

	Compression compression;

	if (type == ProtoType::ITEM)
	{
		if (fourcc == MAKEFOURCC('M', 'I', 'P', 'X'))
		{
			f.read(reinterpret_cast<char*>(&version), sizeof(version));
			f.read(reinterpret_cast<char*>(&stride), sizeof(stride));

			main_logger()->debug("reading header: fourcc=0x{:08X} ({}), version={}, stride={}", fourcc,
				compression.fourcc_to_string(fourcc), version, stride);

			if (version != 1)
			{
				spdlog::error("version mismatch");
				return false;
			}

			if (stride != sizeof(ItemTable))
			{
				spdlog::error("stride {} mismatch != {}", stride, sizeof(ItemTable));
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
		main_logger()->debug("reading header: fourcc=0x{:08X} ({})", fourcc, compression.fourcc_to_string(fourcc));

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
		spdlog::error("failed to load {}", path);
		return false;
	}

	main_logger()->debug("entries decoded: {}", count);

	std::vector<uint8_t> out;
	if (!compression.decrypt_and_decompress(compressed.data(), data_size, key, out))
		return false;

	if (type == ProtoType::ITEM)
	{
		uint32_t expected_size = count * sizeof(ItemTable);
		if (out.size() != expected_size)
			return false;

		ItemTable* ptr = reinterpret_cast<ItemTable*>(out.data());
		for (uint32_t i = 0; i < count; ++i)
			m_item_proto_map.emplace(ptr[i].vnum, ptr[i]);
	}
	else if (type == ProtoType::MOB)
	{
		uint32_t expected_size = count * sizeof(MobTable);
		if (out.size() != expected_size)
			return false;

		MobTable* ptr = reinterpret_cast<MobTable*>(out.data());
		for (uint32_t i = 0; i < count; ++i)
			m_mob_proto_map.emplace(ptr[i].vnum, ptr[i]);
	}

	return true;
}
