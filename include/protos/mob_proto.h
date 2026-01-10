///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

#include <cstdint>
#include <map>
#include <unordered_map>
#include <string>

#include <length.h>

enum class MobType
{
	MONSTER,
	NPC,
	STONE,
	WARP,
	DOOR,
	BUILDING,
	PC,
	POLY,
	HORSE,
	GOTO,
	PET,
	PET_PAY,
	SHOP,
	OBJECT
};

enum class MobRank
{
	PAWN,
	S_PAWN,
	KNIGHT,
	S_KNIGHT,
	BOSS,
	KING
};

enum class MobBattleType
{
	MELEE,
	RANGE,
	MAGIC,
	SPECIAL,
	POWER,
	TANKER,
	SUPER_POWER,
	SUPER_TANKER
};

enum class MobSize
{
	RESERVED,
	SMALL,
	MEDIUM,
	BIG
};

////////////////////////////////////////////////////////////////////////////////////

enum class MobAIFlag
{
	AGGR = 0,
	NOMOVE = 1,
	COWARD = 2,
	NOATTSHINSU = 3,
	NOATTCHUNJO = 4,
	NOATTJINNO = 5,
	ATTMOB = 6,
	BERSERK = 7,
	STONESKIN = 8,
	GODSPEED = 9,
	DEATHBLOW = 10,
	REVIVE = 11,
	HEALER = 12,
	COUNT = 13,
	NORECOVERY = 14,
	REFLECT = 15,
	FALL = 16,
	VIT = 17,
	RATTSPEED = 18,
	RCASTSPEED = 19,
	RHP_REGEN = 20,
	TIMEVIT = 21,
	//
	//
	//
	//
	//
	ELEMENT_BUFF_NONE = 25,
	ELEMENT_BUFF_FIRE = 26,
	ELEMENT_BUFF_ICE = 27,
	ELEMENT_BUFF_ELECT = 28,
	ELEMENT_BUFF_WIND = 29,
	ELEMENT_BUFF_EARTH = 30,
	ELEMENT_BUFF_DARK = 31
};

enum class MobRaceFlag
{
#if SCHEMA_VER_AT_LEAST(20, 4, 10)
	ANIMAL = 0,
	UNDEAD = 1,
	DEVIL = 2,
	HUMAN = 3,
	ORC = 4,
	MILGYO = 5,
	INSECT = 6,
	DESERT = 7,
	TREE = 8,
	DECO = 9,
	HIDE = 10,
	ATT_CZ = 11,
	AWEAKEN = 12,
	SUNGMAHEE = 13,
	OUTPOST = 14,
	SUNGMA_PORTAL = 15,
	MYSTERY_DUNGEON = 16,
	DRAGON = 17,
#else
	ANIMAL = 0,
	UNDEAD = 1,
	DEVIL = 2,
	HUMAN = 3,
	ORC = 4,
	MILGYO = 5,
	INSECT = 6,
	FIRE = 7,
	ICE = 8,
	DESERT = 9,
	TREE = 10,
	ATT_ELEC = 11,
	ATT_FIRE = 12,
	ATT_ICE = 13,
	ATT_WIND = 14,
	ATT_EARTH = 15,
	ATT_DARK = 16,
	DECO = 17,
	HIDE = 18,
	ATT_CZ = 19
#endif
};

enum class MobImmuneFlag
{
	STUN,
	SLOW,
	FALL,
	CURSE,
	POISON,
	TERROR,
	REFLECT,
	BLEEDING
};

enum MobEnchantType
{
	MOB_ENCHANT_CURSE,
	MOB_ENCHANT_SLOW,
	MOB_ENCHANT_POISON,
	MOB_ENCHANT_STUN,
	MOB_ENCHANT_CRITICAL,
	MOB_ENCHANT_PENETRATE,
	MOB_ENCHANTS_MAX_NUM
};

enum MobResistType
{
#if SCHEMA_VER_AT_LEAST(18, 3, 0)
	MOB_RESIST_FIST,
#endif
	MOB_RESIST_SWORD,
	MOB_RESIST_TWOHAND,
	MOB_RESIST_DAGGER,
	MOB_RESIST_BELL,
	MOB_RESIST_FAN,
	MOB_RESIST_BOW,
#if SCHEMA_VER_AT_LEAST(14, 11, 0)
	MOB_RESIST_CLAW,
#endif
	MOB_RESIST_FIRE,
	MOB_RESIST_ELECT,
	MOB_RESIST_MAGIC,
	MOB_RESIST_WIND,
	MOB_RESIST_POISON,
#if SCHEMA_VER_AT_LEAST(14, 11, 0)
	MOB_RESIST_BLEEDING,
#endif
	MOB_RESISTS_MAX_NUM
};

enum MobElementType
{
	MOB_ELEMENT_ELECT,
	MOB_ELEMENT_FIRE,
	MOB_ELEMENT_ICE,
	MOB_ELEMENT_WIND,
	MOB_ELEMENT_EARTH,
	MOB_ELEMENT_DARK,
	MOB_ELEMENT_MAX_NUM
};

#pragma pack(push)
#pragma pack(1)
struct MobSkillLevel
{
	uint32_t vnum;
	uint8_t level;
};

struct MobTable
{
	uint32_t vnum;

	char name[CHARACTER_NAME_MAX_LEN + 1];
	char locale_name[CHARACTER_NAME_MAX_LEN + 1];

	uint8_t type;
	uint8_t rank;
	uint8_t battle_type;
	uint8_t level;
#if SCHEMA_VER_AT_LEAST(15, 5, 0)
	uint8_t scale;
#endif
	uint8_t size;

	uint32_t gold_min;
	uint32_t gold_max;

	uint32_t exp;
#if SCHEMA_VER_AT_LEAST(20, 4, 0)
	uint32_t sungma_exp;
#endif

	uint32_t max_hp;

	uint8_t regen_cycle;
	uint8_t regen_percent;

	uint16_t def;

	uint32_t ai_flags;
#if SCHEMA_VER_AT_LEAST(20, 4, 0)
	uint32_t unknown_data1;
#endif
	uint32_t race_flags;
	uint32_t immune_flags;

	uint8_t str;
	uint8_t dex;
	uint8_t con;
	uint8_t iq;
#if SCHEMA_VER_AT_LEAST(20, 4, 0)
	uint8_t sungma_str;
	uint8_t sungma_dex;
#endif

	uint32_t damage_range[2];

	int16_t attack_speed;
	int16_t moving_speed;

	uint8_t aggressive_hp_pct;
	uint16_t aggressive_sight;
	uint16_t attack_range;

	char enchants[MOB_ENCHANTS_MAX_NUM];
	char resists[MOB_RESISTS_MAX_NUM];
#if SCHEMA_VER_AT_LEAST(17, 5, 0)
	char elements[MOB_ELEMENT_MAX_NUM];
	char resist_dark;
	char resist_ice;
	char resist_earth;
#endif

	uint32_t resurrection_vnum;
	uint32_t drop_item_vnum;

	uint8_t mount_capacity;
	uint8_t onclick_type;

	uint8_t empire;
	char folder[CHARACTER_FOLDER_MAX_LEN + 1];

	float damage_multiply;

	uint32_t summon_vnum;
	uint32_t drain_sp;
	uint32_t monster_color;
	uint32_t polymorph_item_vnum;

	MobSkillLevel skills[MOB_SKILL_MAX_NUM];

	uint8_t berserk_point;
	uint8_t stoneskin_point;
	uint8_t godspeed_point;
	uint8_t deathblow_point;
	uint8_t revive_point;

#if SCHEMA_VER_AT_LEAST(17, 5, 0)
	uint8_t healer_point;
	uint8_t reduce_att_speed_point;
	uint8_t reduce_cast_speed_point;
	uint8_t reduce_hp_regen_point;
#endif

#if SCHEMA_VER_AT_LEAST(19, 5, 0)
	float hit_range;
#endif

#if SCHEMA_VER_AT_LEAST(20, 4, 0)
	uint8_t sungma_con;
	uint8_t sungma_iq;
#endif

#if SCHEMA_VER_AT_LEAST(20, 4, 0)
	uint32_t unknown_data2;
#endif

public:
	std::string get_rank_string() const;
	std::string get_type_string() const;
	std::string get_battle_type_string() const;
	std::string get_ai_flags_string() const;
	std::string get_race_flags_string() const;
	std::string get_immune_flags_string() const;
};

struct MobTableRef
{
	char folder[CHARACTER_FOLDER_MAX_LEN + 1];

	uint32_t gold_min;
	uint32_t gold_max;

	uint32_t resurrection_vnum;
	uint32_t polymorph_item_vnum;

	MobSkillLevel skills[MOB_SKILL_MAX_NUM];

	uint8_t berserk_point;
	uint8_t stoneskin_point;
	uint8_t godspeed_point;
	uint8_t deathblow_point;
	uint8_t revive_point;

#if SCHEMA_VER_AT_LEAST(17, 5, 0)
	uint8_t healer_point;
	uint8_t reduce_att_speed_point;
	uint8_t reduce_cast_speed_point;
	uint8_t reduce_hp_regen_point;
#endif

#if SCHEMA_VER_AT_LEAST(19, 5, 0)
	float hit_range;
#endif
};
#pragma pack(pop)

using MobTableMap = std::map<uint32_t, MobTable>;
using MobTableRefMap = std::unordered_map<uint32_t, MobTableRef>;
