///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <protos/item_proto.h>
#include <utils.h>

std::string ItemTable::get_type_string() const
{
	std::string_view sv = util::enum_to_sv(static_cast<ItemType>(type));
	if (!sv.empty())
		return std::string{ sv };

	return "UNK_TYPE_" + std::to_string(type);
}

std::string ItemTable::get_subtype_string() const
{
	std::string_view sv;

	switch (static_cast<ItemType>(type))
	{
		case ItemType::ITEM_NONE:
			return "0";

		case ItemType::ITEM_WEAPON:
			sv = util::enum_to_sv(static_cast<WeaponSubTypes>(subtype));
			break;

		case ItemType::ITEM_ARMOR:
			sv = util::enum_to_sv(static_cast<ArmorSubTypes>(subtype));
			break;

		case ItemType::ITEM_USE:
			sv = util::enum_to_sv(static_cast<UseSubTypes>(subtype));
			break;

		case ItemType::ITEM_AUTOUSE:
			sv = util::enum_to_sv(static_cast<AutoUseSubTypes>(subtype));
			break;

		case ItemType::ITEM_MATERIAL:
			sv = util::enum_to_sv(static_cast<MaterialSubTypes>(subtype));
			break;

		case ItemType::ITEM_SPECIAL:
			sv = util::enum_to_sv(static_cast<SpecialSubTypes>(subtype));
			break;

		case ItemType::ITEM_TOOL:
			sv = util::enum_to_sv(static_cast<ToolSubTypes>(subtype));
			break;

		case ItemType::ITEM_LOTTERY:
			sv = util::enum_to_sv(static_cast<LotterySubTypes>(subtype));
			break;

		case ItemType::ITEM_ELK:
			return "0";

		case ItemType::ITEM_METIN:
			sv = util::enum_to_sv(static_cast<MetinSubTypes>(subtype));
			break;

		case ItemType::ITEM_CONTAINER:
			return "0";

		case ItemType::ITEM_FISH:
			sv = util::enum_to_sv(static_cast<FishSubTypes>(subtype));
			break;

		case ItemType::ITEM_ROD:
			return "0";

		case ItemType::ITEM_RESOURCE:
			sv = util::enum_to_sv(static_cast<ResourceSubTypes>(subtype));
			break;

		case ItemType::ITEM_CAMPFIRE:
			return "0";

		case ItemType::ITEM_UNIQUE:
			sv = util::enum_to_sv(static_cast<UniqueSubTypes>(subtype));
			break;

		case ItemType::ITEM_SKILLBOOK:
			sv = util::enum_to_sv(static_cast<SkillBookSubTypes>(subtype));
			break;

		case ItemType::ITEM_QUEST:
			sv = util::enum_to_sv(static_cast<QuestSubTypes>(subtype));
			break;

		case ItemType::ITEM_POLYMORPH:
			sv = util::enum_to_sv(static_cast<PolymorphSubTypes>(subtype));
			break;

		case ItemType::ITEM_TREASURE_BOX:
			return "0";

		case ItemType::ITEM_TREASURE_KEY:
			return "0";

		case ItemType::ITEM_SKILLFORGET:
			return "0";

		case ItemType::ITEM_GIFTBOX:
			sv = util::enum_to_sv(static_cast<GiftBoxSubTypes>(subtype));
			break;

		case ItemType::ITEM_PICK:
			return "0";

		case ItemType::ITEM_HAIR:
			return "0";

		case ItemType::ITEM_TOTEM:
			return "0";

		case ItemType::ITEM_BLEND:
			return "0";

		case ItemType::ITEM_COSTUME:
			sv = util::enum_to_sv(static_cast<CostumeSubTypes>(subtype));
			break;

		case ItemType::ITEM_DS:
			sv = util::enum_to_sv(static_cast<DragonSoulSubTypes>(subtype));
			break;

		case ItemType::ITEM_SPECIAL_DS:
			sv = util::enum_to_sv(static_cast<DragonSoulSubTypes>(subtype));
			break;

		case ItemType::ITEM_EXTRACT:
			sv = util::enum_to_sv(static_cast<ExtractSubTypes>(subtype));
			break;

		case ItemType::ITEM_SECONDARY_COIN:
			return "0";

		case ItemType::ITEM_RING:
			return "0";

		case ItemType::ITEM_BELT:
			return "0";

		case ItemType::ITEM_PET:
			sv = util::enum_to_sv(static_cast<PetSubTypes>(subtype));
			break;

		case ItemType::ITEM_MEDIUM:
			sv = util::enum_to_sv(static_cast<MediumSubTypes>(subtype));
			break;

		case ItemType::ITEM_GACHA:
			sv = util::enum_to_sv(static_cast<GachaSubTypes>(subtype));
			break;

		case ItemType::ITEM_PASSIVE:
			sv = util::enum_to_sv(static_cast<PassiveSubTypes>(subtype));
			break;

		case ItemType::ITEM_MERCENARY:
			sv = util::enum_to_sv(static_cast<MercenarySubTypes>(subtype));
			break;

		case ItemType::ITEM_ALCHEMY:
			sv = util::enum_to_sv(static_cast<AlchemySubTypes>(subtype));
			break;

		case ItemType::ITEM_FORCE:
			sv = util::enum_to_sv(static_cast<ForceSubTypes>(subtype));
			break;

		default:
			return "UNK_SUBTYPE_" + std::to_string(subtype);
	}

	if (!sv.empty())
		return std::string{ sv };

	return "UNK_SUBTYPE_" + std::to_string(subtype);
}

std::string ItemTable::get_anti_flags_string() const
{
	return util::flags_to_string<ItemAntiFlag>(anti_flags, "UNK_ANTI_FLAG_", " | ", "NONE");
}

std::string ItemTable::get_flags_string() const
{
	return util::flags_to_string<ItemFlag>(flags, "UNK_FLAG_", " | ", "NONE");
}

std::string ItemTable::get_wear_flags_string() const
{
	return util::flags_to_string<ItemWearFlag>(wear_flags, "UNK_WEAR_FLAG_", " | ", "NONE");
}

std::string ItemTable::get_immune_flags_string() const
{
	return "NONE"; // immune flags not used.
}

std::string ItemTable::get_limit_type_string(uint8_t index) const
{
	if (index >= ITEM_LIMIT_MAX_NUM)
		return "INVALID";

	auto raw_value = limits[index].type;
	ItemLimitType limit_type = static_cast<ItemLimitType>(raw_value);

	std::string_view sv = util::enum_to_sv(limit_type);
	if (!sv.empty())
		return std::string{ sv };

	return "UNK_LIMIT_TYPE_" + std::to_string(raw_value);
}

long ItemTable::get_limit_type_value(uint8_t index) const
{
	if (index >= ITEM_LIMIT_MAX_NUM)
		return 0;

	return limits[index].value;
}

std::string ItemTable::get_apply_type_string(uint8_t index) const
{
	if (index >= ITEM_APPLY_MAX_NUM)
		return "INVALID";

	auto raw_value = applies[index].type;
	ApplyType apply_type = static_cast<ApplyType>(raw_value);

	std::string_view sv = util::enum_to_sv(apply_type);
	if (!sv.empty())
		return std::string{ sv };

	return "UNK_APPLY_TYPE_" + std::to_string(raw_value);
}

long ItemTable::get_apply_type_value(uint8_t index) const
{
	if (index >= ITEM_APPLY_MAX_NUM)
		return 0;

	return applies[index].value;
}

// hard code addon type by vnum range
static constexpr ItemAddonRange addon_type_vnum_range[] =
{
	{ 180, 189 },
	{ 190, 199 },
	{ 290, 299 },
	{ 300, 309 },
	{ 310, 319 },
	{ 1130, 1139 },
	{ 1170, 1179 },
	{ 1180, 1189 },
	{ 2150, 2159 },
	{ 2170, 2179 },
	{ 2200, 2209 },
	{ 3160, 3169 },
	{ 3210, 3219 },
	{ 3220, 3229 },
	{ 5110, 5119 },
	{ 5120, 5129 },
	{ 5160, 5169 },
	{ 6010, 6019 },
	{ 6060, 6069 },
	{ 6070, 6079 },
	{ 6120, 6129 },
	{ 7160, 7169 },
	{ 7300, 7309 },
};

int8_t ItemTable::has_addon_type() const
{
	for (const auto& range : addon_type_vnum_range)
	{
		if (vnum >= range.min && vnum <= range.max)
			return -1;
	}
	return 0;
}
