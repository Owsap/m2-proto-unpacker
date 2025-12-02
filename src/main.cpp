///////////////////////////////////////////////////////////////////////
// Proto Unpacker
//
// Loads item_proto and mob_proto binary files, optionally decrypts
// their contents using TEA, and decompresses them using Snappy.
// The decoded data is then parsed into structures and exported as
// human-readable TXT tables (names and full proto dumps).
//
// Copyright (c) 2025 Owsap.
// All rights reserved.
//
// Email: admin@owsap.dev
// Web: https://owsap.dev/
//

#include <iostream>

#include <proto_unpacker.h>
#include <utils.h>

void init_loggers()
{
	auto header = std::make_shared<spdlog::logger>("header", std::make_shared<spdlog::sinks::stdout_sink_mt>());
	header->set_pattern("%v");
	spdlog::register_logger(header);

	auto main = std::make_shared<spdlog::logger>("main", std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
	main->set_pattern("%^[%l]%$ %v");
	spdlog::set_default_logger(main); // main is default

	auto detail = std::make_shared<spdlog::logger>("detail", std::make_shared<spdlog::sinks::stdout_sink_mt>());
	detail->set_pattern("  %v");
	spdlog::register_logger(detail);
}

void print_header()
{
	header_logger()->info("Proto Unpacker v{}", VERSION_STRING);
	header_logger()->info("(c) 2025 Owsap. All rights reserved.");
	header_logger()->info("");
	header_logger()->info("Proto Version : {}", PROTO_VERSION_STRING);
	header_logger()->info("Build Date : Dec 1, 2025");
	header_logger()->info("");
}

void print_footer(double total_seconds)
{
	main_logger()->info("completed all tasks in {:.2f} seconds.", total_seconds);
}

int main()
{
	init_loggers();
	print_header();

	Timer timer;
	ProtoUnpacker pu;
	pu.run();

	print_footer(timer.elapsed_seconds());
	return 0;
}
