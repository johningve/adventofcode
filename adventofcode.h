#pragma once

#include <string>
#include <vector>
#include <getopt.h>

typedef void (*solution)(std::string file_path);

static std::vector<option> options;
static std::vector<solution> solutions;

#define define_solution(name) void name(std::string file_path);

#define add_solution(name)                               \
	options.push_back({#name, required_argument, 0, 0}); \
	solutions.push_back(name);

define_solution(day1_1);
define_solution(day1_2);

inline void init_solutions()
{
	add_solution(day1_1);
	add_solution(day1_2);

	// need an extra empty item for getopt
	options.push_back({});
}
