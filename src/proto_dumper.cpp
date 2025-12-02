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

static std::ofstream openfs(const std::filesystem::path& path)
{
	std::ofstream out(path);
	if (!out)
		throw std::runtime_error("failed to open output file: " + path.string());
	return out;
}

void ProtoDumper::dump_item_proto(const ItemProtoMap& map)
{
	m_item_proto_map = &map;

	main_logger()->info("dumping item_proto...");

	dump_item_names();
	dump_item_table();
}

void ProtoDumper::dump_item_names() const
{
	detail_logger()->info("item_names.txt");

	std::ofstream out = openfs("item_names.txt");

	out << "VNUM\tLOCALE_NAME\n";
	for (const auto& [vnum, proto] : *m_item_proto_map)
		out << vnum << "\t" << proto.locale_name << "\n";
}

void ProtoDumper::dump_item_table() const
{
	detail_logger()->info("item_proto.txt");

	std::ofstream out = openfs("item_proto.txt");

	out <<
		"Vnum" "\t"
		"Name" "\t"
		"Type" "\t"
		"SubType" "\t"
		"Size" "\t"
		"AntiFlags" "\t"
		"Flags" "\t"
		"WearFlags" "\t"
		"ImmuneFlags" "\t"
		"ShopBuyPrice" "\t"
		"ShopSellPrice" "\t"
		"RefinedVnum" "\t"
		"RefineSet" "\t"
		"67AttrMaterial" "\t"
		"AlterToMagicItemPercent" "\t"
		"LimitType0" "\t"
		"LimitValue0" "\t"
		"LimitType1" "\t"
		"LimitValue1" "\t"
		"ApplyType0" "\t"
		"ApplyValue0" "\t"
		"ApplyType1" "\t"
		"ApplyValue1" "\t"
		"ApplyType2" "\t"
		"ApplyValue2" "\t"
		"ApplyType3" "\t"
		"ApplyValue3" "\t"
		"Value0" "\t"
		"Value1" "\t"
		"Value2" "\t"
		"Value3" "\t"
		"Value4" "\t"
		"Value5" "\t"
		"Value6" "\t"
		"Value7" "\t"
		"Value8" "\t"
		"Value9" "\t"
		"Specular" "\t"
		"GainSocketPercent" "\t"
		"AddonType" "\n"
		;

	for (const auto& [vnum, proto] : *m_item_proto_map)
	{
		std::string vnum_str = std::to_string(vnum);
		if (proto.vnum_range > 0)
			vnum_str += "~" + std::to_string(vnum + proto.vnum_range);

		out <<
			vnum_str << "\t" <<
			proto.name << "\t" <<
			proto.get_type_string() << "\t" <<
			proto.get_subtype_string() << "\t" <<
			+proto.size << "\t" <<
			proto.get_anti_flags_string() << "\t" <<
			proto.get_flags_string() << "\t" <<
			proto.get_wear_flags_string() << "\t" <<
			proto.get_immune_flags_string() << "\t" <<
			proto.shop_buy_price << "\t" <<
			proto.shop_sell_price << "\t" <<
			proto.refined_vnum << "\t" <<
			proto.refine_set << "\t" <<
			proto.material67 << "\t" <<
			+proto.alter_to_magic_item_pct << "\t";

		for (uint8_t i = 0; i < ITEM_LIMIT_MAX_NUM; ++i)
		{
			out << proto.get_limit_type_string(i) << "\t"
				<< proto.get_limit_type_value(i) << "\t";
		}

		for (uint8_t i = 0; i < ITEM_APPLY_MAX_NUM; ++i)
		{
			out << proto.get_apply_type_string(i) << "\t"
				<< proto.get_apply_type_value(i) << "\t";
		}

		for (uint8_t i = 0; i < ITEM_VALUES_MAX_NUM; ++i)
			out << proto.values[i] << "\t";

		out <<
			+proto.specular << "\t" <<
			+proto.gain_socket_pct << "\t" <<
			+proto.has_addon_type() << "\n";
	}
}

void ProtoDumper::dump_mob_proto(const MobProtoMap& map)
{
	m_mob_proto_map = &map;

	main_logger()->info("dumping mob_proto...");

	dump_mob_names();
	dump_mob_table();
}

void ProtoDumper::dump_mob_names() const
{
	detail_logger()->info("mob_names.txt");

	std::ofstream out = openfs("mob_names.txt");

	out << "VNUM\tLOCALE_NAME\n";
	for (const auto& [vnum, proto] : *m_mob_proto_map)
		out << vnum << "\t" << proto.locale_name << "\n";
}

void ProtoDumper::dump_mob_table() const
{
	detail_logger()->info("mob_proto.txt");

	std::ofstream out = openfs("mob_proto.txt");

	out <<
		"Vnum" "\t"
		"Name" "\t"
		"Rank" "\t"
		"Type" "\t"
		"BattleType" "\t"
		"Level" "\t"
		"ScalePct" "\t"
		"Size" "\t"
		"AIFlags" "\t"
		"MountCapacity" "\t"
		"RaceFlags" "\t"
		"ImmuneFlags" "\t"
		"Empire" "\t"
		"Folder" "\t"
		"OnClick" "\t"
		"St" "\t"
		"Dx" "\t"
		"Ht" "\t"
		"Iq" "\t"
		"SungMaSt" "\t"
		"SungMaDx" "\t"
		"SungMaHt" "\t"
		"SungMaIq" "\t"
		"MinDamage" "\t"
		"MaxDamage" "\t"
		"MaxHp" "\t"
		"RegenCycle" "\t"
		"RegenPercent" "\t"
		"MinGold" "\t"
		"MaxGold" "\t"
		"Exp" "\t"
		"SungMaExp" "\t"
		"Def" "\t"
		"AttackSpeed" "\t"
		"MoveSpeed" "\t"
		"AggressiveHpPct" "\t"
		"AggressiveSight" "\t"
		"AttackRange" "\t"
		"DropItemGroup" "\t"
		"ResurrectionVnum" "\t"
		"EnchantCurse" "\t"
		"EnchantSlow" "\t"
		"EnchantPoison" "\t"
		"EnchantStun" "\t"
		"EnchantCritical" "\t"
		"EnchantPenetrate" "\t"
		"ResistFist" "\t"
		"ResistSword" "\t"
		"ResistTwoHanded" "\t"
		"ResistDagger" "\t"
		"ResistBell" "\t"
		"ResistFan" "\t"
		"ResistBow" "\t"
		"ResistClaw" "\t"
		"ResistFire" "\t"
		"ResistElect" "\t"
		"ResistMagic" "\t"
		"ResistWind" "\t"
		"ResistPoison" "\t"
		"ResistBleeding" "\t"
		"AttElec" "\t"
		"AttFire" "\t"
		"AttIce" "\t"
		"AttWind" "\t"
		"AttEarth" "\t"
		"AttDark" "\t"
		"ResistDark" "\t"
		"ResistIce" "\t"
		"ResistEarth" "\t"
		"DamMultiply" "\t"
		"SummonVnum" "\t"
		"DrainSp" "\t"
		"MobColor" "\t"
		"PolymorphItem" "\t"
		"SkillLevel0" "\t"
		"SkillVnum0" "\t"
		"SkillLevel1" "\t"
		"SkillVnum1" "\t"
		"SkillLevel2" "\t"
		"SkillVnum2" "\t"
		"SkillLevel3" "\t"
		"SkillVnum3" "\t"
		"SkillLevel4" "\t"
		"SkillVnum4" "\t"
		"SpBerserk" "\t"
		"SpStoneSkin" "\t"
		"SpGodSpeed" "\t"
		"SpDeathBlow" "\t"
		"SpRevive" "\t"
		"SpHeal" "\t"
		"RAtkSpeed" "\t"
		"RCastSpeed" "\t"
		"RHPRegen" "\t"
		"HitRange" "\n"
		;

	for (const auto& [vnum, proto] : *m_mob_proto_map)
	{
		out <<
			proto.vnum << "\t" <<
			proto.name << "\t" <<
			proto.get_rank_string() << "\t" <<
			proto.get_type_string() << "\t" <<
			proto.get_battle_type_string() << "\t" <<
			+proto.level << "\t" <<
			+proto.scale << "\t" <<
			/*size*/ "\t" <<
			proto.get_ai_flags_string() << "\t" <<
			+proto.mount_capacity << "\t" <<
			proto.get_race_flags_string() << "\t" <<
			proto.get_immune_flags_string() << "\t" <<
			+proto.empire << "\t" <<
			proto.folder << "\t" <<
			+proto.onclick_type << "\t" <<
			+proto.str << "\t" <<
			+proto.dex << "\t" <<
			+proto.con << "\t" <<
			+proto.iq << "\t" <<
			+proto.sungma_str << "\t" <<
			+proto.sungma_dex << "\t" <<
			+proto.sungma_con << "\t" <<
			+proto.sungma_iq << "\t" <<
			proto.damage_range[0] << "\t" <<
			proto.damage_range[1] << "\t" <<
			proto.max_hp << "\t" <<
			+proto.regen_cycle << "\t" <<
			+proto.regen_percent << "\t" <<
			proto.gold_min << "\t" <<
			proto.gold_max << "\t" <<
			proto.exp << "\t" <<
			proto.sungma_exp << "\t" <<
			proto.def << "\t" <<
			proto.attack_speed << "\t" <<
			proto.moving_speed << "\t" <<
			+proto.aggressive_hp_pct << "\t" <<
			proto.aggressive_sight << "\t" <<
			proto.attack_range << "\t" <<
			proto.drop_item_vnum << "\t" <<
			proto.resurrection_vnum << "\t";

		for (char val : proto.enchants)
			out << +val << "\t";

		for (char val : proto.resists)
			out << +val << "\t";

		for (char val : proto.elements)
			out << +val << "\t";

		out <<
			+proto.resist_dark << "\t" <<
			+proto.resist_ice << "\t" <<
			+proto.resist_earth << "\t";

		out << std::fixed << std::setprecision(1) << proto.damage_multiply << "\t";
		out << std::setprecision(0);

		out <<
			proto.summon_vnum << "\t" <<
			proto.drain_sp << "\t" <<
			proto.monster_color << "\t" <<
			proto.polymorph_item_vnum << "\t";

		for (const MobSkillLevel& skill : proto.skills)
			out << +skill.level << "\t" << skill.vnum << "\t";

		out <<
			+proto.berserk_point << "\t" <<
			+proto.stoneskin_point << "\t" <<
			+proto.godspeed_point << "\t" <<
			+proto.deathblow_point << "\t" <<
			+proto.revive_point << "\t" <<
			+proto.heal_point << "\t" <<
			+proto.r_att_speed_p << "\t" <<
			+proto.r_cast_speed << "\t" <<
			+proto.r_hp_regen << "\t";
		
		out << std::fixed << std::setprecision(1) << proto.hit_range << "\n";
		out << std::setprecision(0);
	}
}
