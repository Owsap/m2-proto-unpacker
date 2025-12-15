#pragma once

#include <cstdint>
#include <string>
#include <csv-parser/csv.hpp>

namespace util
{
	inline int64_t csv_i64(const csv::CSVRow& row, const std::string& key)
	{
		return row[key].get<long long>();
	}
}
