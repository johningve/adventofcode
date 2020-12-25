#pragma once

#include <cstdint>
#include <istream>
#include <vector>
#include <getopt.h>

typedef int64_t (*solution)(std::istream &file);

static std::vector<option> options;
static std::vector<solution> solutions;

#define define_solution(name) int64_t name(std::istream &file);

#define add_solution(name)                               \
	options.push_back({#name, required_argument, 0, 0}); \
	solutions.push_back(name);

define_solution(day1_1);
define_solution(day1_2);
define_solution(day2_1);
define_solution(day2_2);
define_solution(day3_1);
define_solution(day3_2);
define_solution(day4_1);
define_solution(day4_2);
define_solution(day5_1);
define_solution(day5_2);
define_solution(day6_1);
define_solution(day6_2);
define_solution(day7_1);
define_solution(day7_2);
define_solution(day8_1);
define_solution(day8_2);
define_solution(day9_1);
define_solution(day9_2);
define_solution(day10_1);
define_solution(day10_2);
define_solution(day11_1);
define_solution(day11_2);
define_solution(day12_1);
define_solution(day12_2);
define_solution(day13_1);
define_solution(day13_2);
define_solution(day14_1);
define_solution(day14_2);
define_solution(day15_1);
define_solution(day15_2);

inline void init_solutions()
{
	add_solution(day1_1);
	add_solution(day1_2);
	add_solution(day2_1);
	add_solution(day2_2);
	add_solution(day3_1);
	add_solution(day3_2);
	add_solution(day4_1);
	add_solution(day4_2);
	add_solution(day5_1);
	add_solution(day5_2);
	add_solution(day6_1);
	add_solution(day6_2);
	add_solution(day7_1);
	add_solution(day7_2);
	add_solution(day8_1);
	add_solution(day8_2);
	add_solution(day9_1);
	add_solution(day9_2);
	add_solution(day10_1);
	add_solution(day10_2);
	add_solution(day11_1);
	add_solution(day11_2);
	add_solution(day12_1);
	add_solution(day12_2);
	add_solution(day13_1);
	add_solution(day13_2);
	add_solution(day14_1);
	add_solution(day14_2);
	add_solution(day15_1);
	add_solution(day15_2);

	// need an extra empty item for getopt
	options.push_back({});
}
