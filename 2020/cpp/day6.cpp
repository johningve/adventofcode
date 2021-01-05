#include <unordered_set>
#include <unordered_map>

#ifdef TEST
#include <sstream>
#include <catch2/catch.hpp>
#endif

#include "adventofcode.h"

int64_t day6_1(std::istream &file)
{
	int sum = 0;
	std::unordered_set<char> answered_questions;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			sum += answered_questions.size();
			answered_questions.clear();
			continue;
		}
		for (char &c : line)
		{
			answered_questions.insert(c);
		}
	}
	sum += answered_questions.size();
	return sum;
}

int64_t day6_2(std::istream &file)
{
	int sum = 0;
	int group_size = 0;
	std::unordered_map<char, int> answered_questions;
	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			for (auto const &question : answered_questions)
				if (group_size == question.second)
					sum++;

			answered_questions.clear();
			group_size = 0;
			continue;
		}
		group_size++;
		for (char &c : line)
		{
			// the [] operator inserts a new element if it does not exist in the map
			answered_questions[c]++;
		}
	}
	for (auto const &question : answered_questions)
		if (group_size == question.second)
			sum++;
	return sum;
}

#ifdef TEST
TEST_CASE("Day 6 part 2", "[day6]")
{
	std::string input = R"(abc

a
b
c

ab
ac

a
a
a
a

b)";
	std::istringstream iss(input);
	REQUIRE(day6_2(iss) == 6);
}
#endif
