#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>

#ifdef TEST
#include <catch2/catch.hpp>
#endif

#include "adventofcode.h"

int get_boarding_id(std::string pass)
{
	int row_lower = 0, row_upper = 127, column_lower = 0, column_upper = 7;

	for (char &c : pass)
	{
		switch (c)
		{
		case 'F':
			row_upper = (row_upper + row_lower) / 2;
			break;
		case 'B':
			row_lower = (row_upper + row_lower) / 2 + 1;
			break;
		case 'L':
			column_upper = (column_upper + column_lower) / 2;
			break;
		case 'R':
			column_lower = (column_upper + column_lower) / 2 + 1;
			break;
		}
	}

	return std::min(row_lower, row_upper) * 8 + std::max(column_lower, column_upper);
}

int day5_1(std::istream &file)
{
	int highest_id = 0;
	std::string pass;
	while (std::getline(file, pass))
	{
		int id = get_boarding_id(pass);
		if (id > highest_id)
		{
			highest_id = id;
		}
	}

	std::cout << highest_id << std::endl;
	return 0;
}

#ifdef TEST
TEST_CASE("Boarding id calculated correctly", "[day5]")
{
	REQUIRE(get_boarding_id("FBFBBFFRLR") == 357);
	REQUIRE(get_boarding_id("BFFFBBFRRR") == 567);
	REQUIRE(get_boarding_id("FFFBBBFRRR") == 119);
	REQUIRE(get_boarding_id("BBFFBBFRLL") == 820);
}
#endif

int day5_2(std::istream &file)
{
	bool seats[1024] = {false};
	std::string pass;
	while (std::getline(file, pass))
	{
		int id = get_boarding_id(pass);
		seats[id] = true;
	}
	int middle = 512;
	for (int i = 0; middle + i < 1023; i++)
	{
		if (!seats[middle - i])
		{
			if (seats[middle - i - 1] && seats[middle - i + 1])
			{
				std::cout << middle - i << std::endl;
				return 0;
			}
		}

		if (!seats[middle + i])
		{
			if (seats[middle + i - 1] && seats[middle + i + 1])
			{
				std::cout << middle + i << std::endl;
				return 0;
			}
		}
	}
	return 0;
}
