#include <iostream>
#include <string>

#include "adventofcode.h"
#include "util.h"

#ifdef TEST
#include <catch2/catch.hpp>
#include <sstream>
#endif

class NavigationComputer
{
public:
	int direction = 1; // e = 1, s = 2, w = 3, n = 4
	int north = 0;
	int east = 0;

	virtual void perform_maneuver(std::string maneuver)
	{
		int distance, rotation;
		switch (maneuver[0])
		{
		case 'F':
			distance = std::stoi(maneuver.substr(1));
			if (direction % 2 == 0)
				north += direction == 4 ? distance : -distance;
			if (direction % 2 == 1)
				east += direction == 1 ? distance : -distance;
			break;
		case 'L':
			rotation = std::stoi(maneuver.substr(1)) / 90;
			direction -= rotation;
			if (direction < 1)
				direction += 4;
			break;
		case 'R':
			rotation = std::stoi(maneuver.substr(1)) / 90;
			direction += rotation;
			if (direction > 4)
				direction -= 4;
			break;
		case 'N':
			distance = std::stoi(maneuver.substr(1));
			north += distance;
			break;
		case 'E':
			distance = std::stoi(maneuver.substr(1));
			east += distance;
			break;
		case 'S':
			distance = std::stoi(maneuver.substr(1));
			north -= distance;
			break;
		case 'W':
			distance = std::stoi(maneuver.substr(1));
			east -= distance;
			break;
		}
	}
};

class WaypointNavigationComputer
{
public:
	// waypoint coordinates
	int wnorth = 1;
	int weast = 10;
	// ship coordinates
	int north = 0;
	int east = 0;

	void perform_maneuver(std::string maneuver)
	{
		int distance, rotation;
		switch (maneuver[0])
		{
		case 'F':
			distance = std::stoi(maneuver.substr(1));
			north += wnorth * distance;
			east += weast * distance;
			break;
		case 'L':
			rotation = std::stoi(maneuver.substr(1));
			switch (rotation)
			{
			case 90:
				swap(wnorth, weast);
				weast = -weast;
				break;
			case 180:
				wnorth = -wnorth;
				weast = -weast;
				break;
			case 270:
				swap(wnorth, weast);
				wnorth = -wnorth;
				break;
			}
			break;
		case 'R':
			rotation = std::stoi(maneuver.substr(1));
			switch (rotation)
			{
			case 90:
				swap(wnorth, weast);
				wnorth = -wnorth;
				break;
			case 180:
				wnorth = -wnorth;
				weast = -weast;
				break;
			case 270:
				swap(wnorth, weast);
				weast = -weast;
				break;
			}
			break;
		case 'N':
			distance = std::stoi(maneuver.substr(1));
			wnorth += distance;
			break;
		case 'E':
			distance = std::stoi(maneuver.substr(1));
			weast += distance;
			break;
		case 'S':
			distance = std::stoi(maneuver.substr(1));
			wnorth -= distance;
			break;
		case 'W':
			distance = std::stoi(maneuver.substr(1));
			weast -= distance;
			break;
		}
	}
};

int64_t day12_1(std::istream &file)
{
	NavigationComputer nc;
	std::string line;
	while (std::getline(file, line))
	{
		nc.perform_maneuver(line);
	}
	return std::abs(nc.north) + std::abs(nc.east);
}

int64_t day12_2(std::istream &file)
{
	WaypointNavigationComputer nc;
	std::string line;
	while (std::getline(file, line))
	{
		nc.perform_maneuver(line);
	}
	return std::abs(nc.north) + std::abs(nc.east);
}

#ifdef TEST
TEST_CASE("Manhattan distance calculated correctly", "[day12]")
{
	std::string input = R"(F10
N3
F7
R90
F11)";
	std::istringstream iss1(input);
	REQUIRE(day12_1(iss1) == 25);
	std::istringstream iss2(input);
	REQUIRE(day12_2(iss2) == 286);
}
#endif
