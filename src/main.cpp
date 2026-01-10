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

struct Arguments
{
	std::string item_proto_path;
	std::string mob_proto_path;
	std::string keys_path;
	std::string out_dir = ".";

	std::string mob_proto_ref_path;
	bool overwrite_mob_proto = false;

	bool show_help = false;
	bool show_version = false;
	bool verbose = false;
	bool silent = false;
};

Arguments parse_arguments(int argc, char** argv)
{
	Arguments args;

	for (int i = 1; i < argc; ++i)
	{
		std::string a = argv[i];

		if (a == "--item_proto" && i + 1 < argc)
			args.item_proto_path = argv[++i];

		else if (a == "--mob_proto" && i + 1 < argc)
			args.mob_proto_path = argv[++i];

		else if (a == "--keys" && i + 1 < argc)
			args.keys_path = argv[++i];

		else if (a == "--out" && i + 1 < argc)
			args.out_dir = argv[++i];

		else if (a == "--overwrite-mob-proto")
		{
			args.overwrite_mob_proto = true;

			if (i + 1 < argc && argv[i + 1][0] != '-')
				args.mob_proto_ref_path = argv[++i];
			else
				args.mob_proto_ref_path.clear();
		}

		else if (a == "--help")
			args.show_help = true;

		else if (a == "--version")
			args.show_version = true;

		else if (a == "--verbose")
			args.verbose = true;

		else if (a == "--silent")
			args.silent = true;
	}

	return args;
}

void init_loggers(bool verbose, bool silent)
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

	if (silent)
	{
		header->set_level(spdlog::level::err);
		main->set_level(spdlog::level::err);
		detail->set_level(spdlog::level::off);
	}
	else if (verbose)
	{
		header->set_level(spdlog::level::debug);
		main->set_level(spdlog::level::debug);
		detail->set_level(spdlog::level::debug);
	}
	else
	{
		header->set_level(spdlog::level::info);
		main->set_level(spdlog::level::info);
		detail->set_level(spdlog::level::info);
	}
}

void print_header()
{
	auto log = header_logger();

	log->info("Proto Unpacker v{}", VERSION_STRING);
	log->info("(c) {} Owsap. All rights reserved.", __DATE__ + 7);
	log->info("");
	log->info("Proto Schema Version : {}", SCHEMA_VER_STRING);
	log->info("Build Date : {}", __DATE__);
	log->info("");
}

void print_footer(double total_seconds)
{
	main_logger()->info("completed all tasks in {:.2f} seconds.", total_seconds);
}

void print_help()
{
	auto log = header_logger();

	log->info("Usage: m2-proto-unpacker [options]");
	log->info("");
	log->info("If no arguments are given, the tool searches in the current directory:");
	log->info("  item_proto");
	log->info("  mob_proto");
	log->info("  tea-keys.json");
	log->info("");
	log->info("Options:");
	log->info("  --item_proto [path]           Directory or full path to item_proto");
	log->info("  --mob_proto [path]            Directory or full path to mob_proto");
	log->info("  --keys [path]                 Directory or full path to tea-keys.json");
	log->info("  --out [path]                  Output directory for .txt files");
	log->info("  --overwrite-mob-proto [path]  Overwrite dumped mob_proto.txt fields using reference table.");
	log->info("                                If [path] is omitted, 'mob_proto_ref.txt' is used by default.");
	log->info("  --version                     Show version");
	log->info("  --help                        Show this help");
	log->info("  --verbose                     Show detailed debug logs");
	log->info("  --silent                      Only show errors (no header)");
}

int main(int argc, char** argv)
{
	Arguments args = parse_arguments(argc, argv);
	init_loggers(args.verbose, args.silent);

	if (args.show_help)
	{
		print_help();
		return 0;
	}

	if (args.show_version)
	{
		print_header();
		return 0;
	}

	print_header();

	ProtoUnpacker pu;

	if (!args.item_proto_path.empty())
		pu.set_item_proto_path(args.item_proto_path);

	if (!args.mob_proto_path.empty())
		pu.set_mob_proto_path(args.mob_proto_path);

	if (!args.keys_path.empty())
		pu.set_json_path(args.keys_path);

	if (!args.out_dir.empty())
		pu.set_output_dir(args.out_dir);

	if (args.overwrite_mob_proto)
		pu.set_mob_proto_reference(args.mob_proto_ref_path, true);

	Timer timer;
	pu.run();

	print_footer(timer.elapsed_seconds());

	return 0;
}
