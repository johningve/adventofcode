#include <string>
#include <limits>
#include <numeric>

#include "adventofcode.h"

#ifdef TEST
#include <catch2/catch.hpp>
#include <sstream>
#endif

long day13_1(std::istream &file)
{
	int arrival;
	int earliest_departure = std::numeric_limits<int>::max();
	int best_id = 0;

	file >> arrival;

	if (file.peek() == '\n')
		file.ignore();

	std::string id_str;
	while (std::getline(file, id_str, ','))
	{
		if (id_str == "x")
			continue;
		int id = std::stoi(id_str);
		int departure = 0;
		while (departure < arrival)
			departure += id;
		if (departure < earliest_departure)
		{
			best_id = id;
			earliest_departure = departure;
		}
	}

	return best_id * (earliest_departure - arrival);
}

long gcd(std::vector<int> numbers)
{
}

long lcm()

	long day13_2(std::istream &file)
{
	std::string line;
	std::getline(file, line); // ignore first line
	std::getline(file, line);

	return 0;
}

#ifdef TEST
TEST_CASE("Correct bus is found", "[day13]")
{
	std::istringstream iss(R"(939
7,13,x,x,59,x,31,19)");
	REQUIRE(day13_1(iss) == 295);
}
#endif
