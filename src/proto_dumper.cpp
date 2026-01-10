///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <proto_dumper.h>

#include <fstream>
#include <filesystem>

#include <utils.h>

std::ofstream ProtoDumper::open_output_file(const std::string& filename) const
{
	std::filesystem::path full_path = m_output_dir + filename;

	std::ofstream out(full_path);
	if (!out)
		throw std::runtime_error("failed to open output file: " + full_path.string());

	return out;
}

void ProtoDumper::set_output_dir(const std::string& dir)
{
	m_output_dir = dir;

	if (!m_output_dir.empty() &&
		m_output_dir.back() != '/' &&
		m_output_dir.back() != '\\')
	{
		m_output_dir += '/';
	}

	std::filesystem::create_directories(m_output_dir);
}

void ProtoDumper::set_mob_proto_reference(MobTableRefMap ref, bool overwrite)
{
	m_mob_proto_ref = std::move(ref);
	m_overwrite_mob_proto = overwrite;
}

void ProtoDumper::dump_item_proto(const ItemTableMap& map)
{
	m_item_proto_map = &map;

	main_logger()->info("dumping item_proto...");

	dump_item_names();
	dump_item_table();
}

void ProtoDumper::dump_item_names() const
{
	detail_logger()->info(m_output_dir + "item_names.txt");

	std::ofstream out = open_output_file("item_names.txt");

	out << "VNUM\tLOCALE_NAME\n";
	for (const auto& [vnum, proto] : *m_item_proto_map)
		out << vnum << "\t" << proto.locale_name << "\n";
}

void ProtoDumper::dump_item_table() const
{
	detail_logger()->info(m_output_dir + "item_proto.txt");

	std::ofstream out = open_output_file("item_proto.txt");

	out << "Vnum"
		<< "\t" << "Name"
		<< "\t" << "Type"
		<< "\t" << "SubType"
		<< "\t" << "Size"
		<< "\t" << "AntiFlags"
		<< "\t" << "Flags"
		<< "\t" << "WearFlags"
		<< "\t" << "ImmuneFlags"
		<< "\t" << "ShopBuyPrice"
		<< "\t" << "ShopSellPrice"
		<< "\t" << "RefinedVnum"
		<< "\t" << "RefineSet"
		<< "\t" << "67AttrMaterial"
		<< "\t" << "AlterToMagicItemPercent";

		for (uint8_t i = 0; i < ITEM_LIMIT_MAX_NUM; ++i)
		{
			out << "\t" << "LimitType" << int(i)
				<< "\t" << "LimitValue" << int(i);
		}

		for (uint8_t i = 0; i < ITEM_APPLY_MAX_NUM; ++i)
		{
			out << "\t" << "ApplyType" << int(i)
				<< "\t" << "ApplyValue" << int(i);
		}

		for (uint8_t i = 0; i < ITEM_VALUES_MAX_NUM; ++i)
			out << "\t" << "Value" << int(i);

		out << "\t" << "Specular"
			<< "\t" << "GainSocketPercent"
			<< "\t" << "AddonType";
		out << "\n";

	for (const auto& [vnum, proto] : *m_item_proto_map)
	{
		std::string vnum_str = std::to_string(vnum);
		if (proto.vnum_range > 0)
			vnum_str += "~" + std::to_string(vnum + proto.vnum_range);

		out << vnum_str
			<< "\t" << proto.name
			<< "\t" << proto.get_type_string()
			<< "\t" << proto.get_subtype_string()
			<< "\t" << int(proto.size)
			<< "\t" << proto.get_anti_flags_string()
			<< "\t" << proto.get_flags_string()
			<< "\t" << proto.get_wear_flags_string()
			<< "\t" << proto.get_immune_flags_string()
			<< "\t" << proto.shop_buy_price
			<< "\t" << proto.shop_sell_price
			<< "\t" << proto.refined_vnum
			<< "\t" << proto.refine_set
			<< "\t" << proto.material67
			<< "\t" << int(proto.alter_to_magic_item_pct);

		for (uint8_t i = 0; i < ITEM_LIMIT_MAX_NUM; ++i)
		{
			out << "\t" << proto.get_limit_type_string(i)
				<< "\t" << proto.get_limit_type_value(i);
		}

		for (uint8_t i = 0; i < ITEM_APPLY_MAX_NUM; ++i)
		{
			out << "\t" << proto.get_apply_type_string(i)
				<< "\t" << proto.get_apply_type_value(i);
		}

		for (uint8_t i = 0; i < ITEM_VALUES_MAX_NUM; ++i)
			out << "\t" << proto.values[i];

		out << "\t" << int(proto.specular)
			<< "\t" << int(proto.gain_socket_pct)
			<< "\t" << int(proto.has_addon_type());

		out << "\n";
	}
}

void ProtoDumper::dump_mob_proto(const MobTableMap& map)
{
	m_mob_proto_map = &map;

	main_logger()->info("dumping mob_proto...");

	dump_mob_names();
	dump_mob_table();
}

void ProtoDumper::dump_mob_names() const
{
	detail_logger()->info(m_output_dir + "mob_names.txt");

	std::ofstream out = open_output_file("mob_names.txt");

	out << "VNUM\tLOCALE_NAME\n";
	for (const auto& [vnum, proto] : *m_mob_proto_map)
		out << vnum << "\t" << proto.locale_name << "\n";
}

void ProtoDumper::dump_mob_table() const
{
	detail_logger()->info(m_output_dir + "mob_proto.txt");

	std::ofstream out = open_output_file("mob_proto.txt");

	out << "Vnum"
		<< "\t" << "Name"
		<< "\t" << "Rank"
		<< "\t" << "Type"
		<< "\t" << "BattleType"
		<< "\t" << "Level"
		<< "\t" << "ScalePct"
		<< "\t" << "Size"
		<< "\t" << "AIFlags"
		<< "\t" << "MountCapacity"
		<< "\t" << "RaceFlags"
		<< "\t" << "ImmuneFlags"
		<< "\t" << "Empire"
		<< "\t" << "Folder"
		<< "\t" << "OnClick"
		<< "\t" << "St"
		<< "\t" << "Dx"
		<< "\t" << "Ht"
		<< "\t" << "Iq"
		<< "\t" << "SungMaSt"
		<< "\t" << "SungMaDx"
		<< "\t" << "SungMaHt"
		<< "\t" << "SungMaIq"
		<< "\t" << "MinDamage"
		<< "\t" << "MaxDamage"
		<< "\t" << "MaxHp"
		<< "\t" << "RegenCycle"
		<< "\t" << "RegenPercent"
		<< "\t" << "MinGold"
		<< "\t" << "MaxGold"
		<< "\t" << "Exp"
		<< "\t" << "SungMaExp"
		<< "\t" << "Def"
		<< "\t" << "AttackSpeed"
		<< "\t" << "MoveSpeed"
		<< "\t" << "AggressiveHpPct"
		<< "\t" << "AggressiveSight"
		<< "\t" << "AttackRange"
		<< "\t" << "DropItemGroup"
		<< "\t" << "ResurrectionVnum"
		<< "\t" << "EnchantCurse"
		<< "\t" << "EnchantSlow"
		<< "\t" << "EnchantPoison"
		<< "\t" << "EnchantStun"
		<< "\t" << "EnchantCritical"
		<< "\t" << "EnchantPenetrate"
		<< "\t" << "ResistFist"
		<< "\t" << "ResistSword"
		<< "\t" << "ResistTwoHanded"
		<< "\t" << "ResistDagger"
		<< "\t" << "ResistBell"
		<< "\t" << "ResistFan"
		<< "\t" << "ResistBow"
		<< "\t" << "ResistClaw"
		<< "\t" << "ResistFire"
		<< "\t" << "ResistElect"
		<< "\t" << "ResistMagic"
		<< "\t" << "ResistWind"
		<< "\t" << "ResistPoison"
		<< "\t" << "ResistBleeding"
		<< "\t" << "AttElec"
		<< "\t" << "AttFire"
		<< "\t" << "AttIce"
		<< "\t" << "AttWind"
		<< "\t" << "AttEarth"
		<< "\t" << "AttDark"
		<< "\t" << "ResistDark"
		<< "\t" << "ResistIce"
		<< "\t" << "ResistEarth"
		<< "\t" << "DamMultiply"
		<< "\t" << "SummonVnum"
		<< "\t" << "DrainSp"
		<< "\t" << "MobColor"
		<< "\t" << "PolymorphItem"
		<< "\t" << "SkillLevel0"
		<< "\t" << "SkillVnum0"
		<< "\t" << "SkillLevel1"
		<< "\t" << "SkillVnum1"
		<< "\t" << "SkillLevel2"
		<< "\t" << "SkillVnum2"
		<< "\t" << "SkillLevel3"
		<< "\t" << "SkillVnum3"
		<< "\t" << "SkillLevel4"
		<< "\t" << "SkillVnum4"
		<< "\t" << "SpBerserk"
		<< "\t" << "SpStoneSkin"
		<< "\t" << "SpGodSpeed"
		<< "\t" << "SpDeathBlow"
		<< "\t" << "SpRevive"
		<< "\t" << "SpHeal"
		<< "\t" << "RAtkSpeed"
		<< "\t" << "RCastSpeed"
		<< "\t" << "RHPRegen"
		<< "\t" << "HitRange";
	out << "\n";

	for (const auto& [vnum, proto] : *m_mob_proto_map)
	{
		const MobTableRef* proto_ref = nullptr;
		if (m_overwrite_mob_proto)
		{
			MobTableRefMap::const_iterator it = m_mob_proto_ref.find(proto.vnum);
			if (it != m_mob_proto_ref.end())
				proto_ref = &it->second;
		}

		out << proto.vnum
			<< "\t" << proto.name
			<< "\t" << proto.get_rank_string()
			<< "\t" << proto.get_type_string()
			<< "\t" << proto.get_battle_type_string()
			<< "\t" << int(proto.level)
			<< "\t" << int(proto.scale)
			<< "\t" /* << int(proto.size)*/
			<< "\t" << proto.get_ai_flags_string()
			<< "\t" << int(proto.mount_capacity)
			<< "\t" << proto.get_race_flags_string()
			<< "\t" << proto.get_immune_flags_string()
			<< "\t" << int(proto.empire)
			<< "\t" << (proto_ref ? proto_ref->folder : proto.folder)
			<< "\t" << int(proto.onclick_type)
			<< "\t" << int(proto.str)
			<< "\t" << int(proto.dex)
			<< "\t" << int(proto.con)
			<< "\t" << int(proto.iq)
			<< "\t" << int(proto.sungma_str)
			<< "\t" << int(proto.sungma_dex)
			<< "\t" << int(proto.sungma_con)
			<< "\t" << int(proto.sungma_iq)
			<< "\t" << proto.damage_range[0]
			<< "\t" << proto.damage_range[1]
			<< "\t" << proto.max_hp
			<< "\t" << int(proto.regen_cycle)
			<< "\t" << int(proto.regen_percent)
			<< "\t" << (proto_ref ? proto_ref->gold_min : proto.gold_min)
			<< "\t" << (proto_ref ? proto_ref->gold_max : proto.gold_max)
			<< "\t" << proto.exp
			<< "\t" << proto.sungma_exp
			<< "\t" << proto.def
			<< "\t" << proto.attack_speed
			<< "\t" << proto.moving_speed
			<< "\t" << int(proto.aggressive_hp_pct)
			<< "\t" << proto.aggressive_sight
			<< "\t" << proto.attack_range
			<< "\t" << proto.drop_item_vnum
			<< "\t" << (proto_ref ? proto_ref->resurrection_vnum : proto.resurrection_vnum);

		for (char val : proto.enchants)
			out << "\t" << int(val);

		for (char val : proto.resists)
			out << "\t" << int(val);

		for (char val : proto.elements)
			out << "\t" << int(val);

		out << "\t" << int(proto.resist_dark)
			<< "\t" << int(proto.resist_ice)
			<< "\t" << int(proto.resist_earth);

		out << "\t" << std::fixed << std::setprecision(1) << proto.damage_multiply << std::setprecision(0);

		out << "\t" << proto.summon_vnum
			<< "\t" << proto.drain_sp
			<< "\t" << proto.monster_color
			<< "\t" << (proto_ref ? proto_ref->polymorph_item_vnum : proto.polymorph_item_vnum);

		for (int i = 0; i < MOB_SKILL_MAX_NUM; ++i)
		{
			const MobSkillLevel& skill = proto_ref ? proto_ref->skills[i] : proto.skills[i];
			out << "\t" << int(skill.level)
				<< "\t" << skill.vnum;
		}

		out << "\t" << int(proto_ref ? proto_ref->berserk_point : proto.berserk_point)
			<< "\t" << int(proto_ref ? proto_ref->stoneskin_point : proto.stoneskin_point)
			<< "\t" << int(proto_ref ? proto_ref->godspeed_point : proto.godspeed_point)
			<< "\t" << int(proto_ref ? proto_ref->deathblow_point : proto.deathblow_point)
			<< "\t" << int(proto_ref ? proto_ref->revive_point : proto.revive_point)
			<< "\t" << int(proto_ref ? proto_ref->heal_point : proto.heal_point)
			<< "\t" << int(proto_ref ? proto_ref->r_att_speed_p : proto.r_att_speed_p)
			<< "\t" << int(proto_ref ? proto_ref->r_cast_speed : proto.r_cast_speed)
			<< "\t" << int(proto_ref ? proto_ref->r_hp_regen : proto.r_hp_regen);

		out << "\t" << std::fixed << std::setprecision(1) << (proto_ref ? proto_ref->hit_range : proto.hit_range) << std::setprecision(0);
		out << "\n";
	}
}
