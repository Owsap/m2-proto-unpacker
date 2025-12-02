///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <protos/mob_proto.h>
#include <utils.h>

std::string MobProto::get_rank_string() const
{
	std::string_view sv = util::enum_to_sv(static_cast<MobRank>(rank));
	if (!sv.empty())
		return std::string{ sv };

	return "UNK_RANK_" + std::to_string(rank);
}

std::string MobProto::get_type_string() const
{
	std::string_view sv = util::enum_to_sv(static_cast<MobType>(type));
	if (!sv.empty())
		return std::string{ sv };

	return "UNK_TYPE_" + std::to_string(type);
}

std::string MobProto::get_battle_type_string() const
{
	std::string_view sv = util::enum_to_sv(static_cast<MobBattleType>(battle_type));
	if (!sv.empty())
		return std::string{ sv };

	return "UNK_BATTLE_TYPE_" + std::to_string(battle_type);
}

std::string MobProto::get_ai_flags_string() const
{
	return util::flags_to_string<MobAIFlag>(ai_flags, "UNK_AI_FLAG_", ",", "");
}

std::string MobProto::get_race_flags_string() const
{
	return util::flags_to_string<MobRaceFlag>(race_flags, "UNK_RACE_FLAG_", ",", "");
}

std::string MobProto::get_immune_flags_string() const
{
	return util::flags_to_string<MobImmuneFlag>(immune_flags, "UNK_IMMUNE_FLAG_", ",", "");
}
