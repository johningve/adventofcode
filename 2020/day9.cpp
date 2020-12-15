#include <string>
#include <algorithm>

#include "adventofcode.h"
#include "util.h"

#ifdef TEST
#include <catch2/catch.hpp>
#include <sstream>
#define preamble_length 5
#else
#define preamble_length 25
#endif

long day9_1(std::istream &file)
{
	std::vector<int> numbers;
	std::string line;

	while (std::getline(file, line))
	{
		int n = std::stoi(line);
		numbers.push_back(n);
		if (numbers.size() <= preamble_length)
			continue;
		auto subset = std::vector<int>(numbers.end() - preamble_length - 1, numbers.end() - 1);
		bool valid = false;
		for (int i = 0; i < (int)subset.size(); i++)
		{
			int j = find_subset_sum(n, subset[i], subset);
			if (j != i && j != -1)
			{
				valid = true;
				break;
			}
		}
		if (!valid)
		{
			return n;
		}
	}

	return -1;
}

long day9_2(std::istream &file)
{
	long target = day9_1(file);
	// reset the input stream
	file.seekg(0, std::ios::beg);
	file.clear();

	int set_size = 2;
	auto numbers = read_numbers(file);

	while (set_size < (int)numbers.size())
	{
		int top = 0, bottom = set_size - 1;
		long sum = 0;
		for (int i = top; i <= bottom; i++)
			sum += numbers[i];
		bool found = false;
		while (bottom < (int)numbers.size() - 1)
		{
			if (sum == target)
			{
				found = true;
				break;
			}

			// move the subset
			sum -= numbers[top++];
			sum += numbers[++bottom];
		}
		if (found)
		{
			int min = *std::min_element(numbers.begin() + top, numbers.begin() + bottom + 1);
			int max = *std::max_element(numbers.begin() + top, numbers.begin() + bottom + 1);
			return min + max;
		}
		set_size++;
	}

	return -1;
}

#ifdef TEST
TEST_CASE("Test day9 part1 and part2", "[day9]")
{
	std::istringstream iss(R"(35
20
15
25
47
40
62
55
65
95
102
117
150
182
127
219
299
277
309
576)");
	REQUIRE(day9_1(iss) == 127);
	iss.seekg(0, std::ios::beg);
	iss.clear();
	REQUIRE(day9_2(iss) == 62);
}
#endif
