///////////////////////////////////////////////////////////////////////
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#pragma once

#define MAGIC_ENUM_RANGE_MAX 512
#include <magic_enum/magic_enum.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/stdout_sinks.h>

#include <chrono>
#include <string>
#include <type_traits>

inline std::shared_ptr<spdlog::logger> main_logger()
{
	auto logger = spdlog::get("main");
	return logger ? logger : spdlog::default_logger();
}

inline std::shared_ptr<spdlog::logger> detail_logger()
{
	auto logger = spdlog::get("detail");
	return logger ? logger : spdlog::default_logger();
}

inline std::shared_ptr<spdlog::logger> header_logger()
{
	auto logger = spdlog::get("header");
	return logger ? logger : spdlog::default_logger();
}

namespace util
{
	template <typename Enum>
	constexpr std::string_view enum_to_sv(Enum value)
	{
		static_assert(std::is_enum_v<Enum>, "Enum must be an enum type");
		return magic_enum::enum_name(value);
	}

	template <typename Enum>
	std::string flags_to_string(uint32_t flags, std::string_view prefix_unknown, std::string_view sep = ",", std::string_view empty = "")
	{
		static_assert(std::is_enum_v<Enum>, "Enum must be enum");

		using underlying_t = std::underlying_type_t<Enum>;
		using index_t = std::make_unsigned_t<underlying_t>;

		std::string out;
		uint32_t known_mask = 0;

		// known flags
		for (Enum e : magic_enum::enum_values<Enum>())
		{
			index_t idx = static_cast<index_t>(e);
			if (idx >= 32)
				continue;

			uint32_t bit = (1u << idx);
			known_mask |= bit;

			if ((flags & bit) == 0)
				continue;

			std::string_view sv = magic_enum::enum_name(e);
			if (sv.empty())
				continue;

			if (!out.empty() && !sep.empty())
				out.append(sep);

			out.append(sv);
		}

		// unknown flags
		uint32_t unknown = flags & ~known_mask;

		while (unknown)
		{
			unsigned long idx = 0;

			_BitScanForward(&idx, unknown);

			uint32_t bit = 1u << idx;
			unknown &= ~bit;

			if (!out.empty() && !sep.empty())
				out.append(sep);

			out.append(prefix_unknown);
			out.append(std::to_string(idx));
		}

		return out.empty() ? std::string(empty) : out;
	}
}

class Timer
{
public:
	Timer() { reset(); }
	void reset() { start = std::chrono::steady_clock::now(); }
	double elapsed_seconds() const
	{
		auto now = std::chrono::steady_clock::now();
		std::chrono::duration<double> diff = now - start;
		return diff.count();
	}
private:
	std::chrono::steady_clock::time_point start;
};
