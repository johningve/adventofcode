#include <iostream>
#include <vector>
#include <string>

#include "adventofcode.h"

#ifdef TEST
#include <catch2/catch.hpp>
#include <sstream>
#endif

class SeatingSystem
{
public:
	void print()
	{
		for (int i = 0; i < (int)grid.size(); i++)
		{
			if (i % width == 0)
				std::cout << std::endl;
			std::cout << grid[i];
		}
		std::cout << std::endl;
	}

	bool is_floor(int x, int y)
	{
		return grid[translate(x, y)] == '.';
	}

	int translate(int x, int y)
	{
		return y * width + x;
	}

	bool occupied(int x, int y)
	{
		if (x < 0 || x >= width)
			return false;
		if (y < 0 || y >= height)
			return false;
		return grid[translate(x, y)] == '#';
	}

	int width = 0, height = 0;
	std::vector<char> grid;

	SeatingSystem(std::istream &input)
	{
		std::string line;
		while (std::getline(input, line))
		{
			if (width == 0)
			{
				width = line.length();
			}
			else if (width != (int)line.length())
			{
				std::cerr << "Inconsistent line length!" << std::endl;
			}
			for (auto &c : line)
			{
				grid.push_back(c);
			}
			height++;
		}
	}

	virtual bool next_round()
	{
		bool changed = false;
		std::vector<char> next_grid(grid);
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				// floors never change
				if (is_floor(x, y))
					continue;

				bool self_occupied = occupied(x, y);
				int num_occupied = 0;
				num_occupied += occupied(x - 1, y);
				num_occupied += occupied(x + 1, y);
				num_occupied += occupied(x, y - 1);
				num_occupied += occupied(x, y + 1);
				num_occupied += occupied(x - 1, y - 1);
				num_occupied += occupied(x + 1, y - 1);
				num_occupied += occupied(x - 1, y + 1);
				num_occupied += occupied(x + 1, y + 1);

				// unoccupied with no adjacent occupied becomes occupied
				if (!self_occupied && num_occupied == 0)
				{
					next_grid[translate(x, y)] = '#';
					changed = true;
				}
				// occupied with at least 4 adjacent occupied becomes unoccupied
				else if (self_occupied && num_occupied >= 4)
				{
					next_grid[translate(x, y)] = 'L';
					changed = true;
				}
			}
		}
		grid = next_grid;
		return changed;
	}
};

enum Direction
{
	NORTH,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST
};

class SeatingSystemV2 : public SeatingSystem
{
public:
	bool occupied_visible(Direction dir, int x, int y)
	{
		do
		{
			switch (dir)
			{
			case NORTH:
				y--;
				break;
			case NORTH_EAST:
				x++;
				y--;
				break;
			case EAST:
				x++;
				break;
			case SOUTH_EAST:
				x++;
				y++;
				break;
			case SOUTH:
				y++;
				break;
			case SOUTH_WEST:
				x--;
				y++;
				break;
			case WEST:
				x--;
				break;
			case NORTH_WEST:
				x--;
				y--;
				break;
			}
		} while (x >= 0 && x < width && y >= 0 && y < height && is_floor(x, y));

		return occupied(x, y);
	}

	SeatingSystemV2(std::istream &input) : SeatingSystem(input)
	{
	}

	virtual bool next_round()
	{
		bool changed = false;
		std::vector<char> next_grid(grid);
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				if (is_floor(x, y))
					continue;

				bool self_occupied = occupied(x, y);
				int num_occupied = 0;
				num_occupied += occupied_visible(NORTH, x, y);
				num_occupied += occupied_visible(NORTH_EAST, x, y);
				num_occupied += occupied_visible(EAST, x, y);
				num_occupied += occupied_visible(SOUTH_EAST, x, y);
				num_occupied += occupied_visible(SOUTH, x, y);
				num_occupied += occupied_visible(SOUTH_WEST, x, y);
				num_occupied += occupied_visible(WEST, x, y);
				num_occupied += occupied_visible(NORTH_WEST, x, y);

				// unoccupied with no adjacent occupied becomes occupied
				if (!self_occupied && num_occupied == 0)
				{
					next_grid[translate(x, y)] = '#';
					changed = true;
				}
				// occupied with at least 5 adjacent occupied becomes unoccupied
				else if (self_occupied && num_occupied >= 5)
				{
					next_grid[translate(x, y)] = 'L';
					changed = true;
				}
			}
		}
		grid = next_grid;
		return changed;
	}
};

long day11_1(std::istream &file)
{
	SeatingSystem ss(file);

	while (ss.next_round())
	{
	}

	int num_occupied = 0;
	for (auto &seat : ss.grid)
	{
		if (seat == '#')
			num_occupied++;
	}

	return num_occupied;
}

long day11_2(std::istream &file)
{
	SeatingSystemV2 ss(file);

	while (ss.next_round())
	{
	}

	int num_occupied = 0;
	for (auto &seat : ss.grid)
	{
		if (seat == '#')
			num_occupied++;
	}

	return num_occupied;
}

#ifdef TEST
TEST_CASE("occupied_visible all true", "[day11]")
{
	std::istringstream iss(R"(.......#.
...#.....
.#.......
.........
..#L....#
....#....
.........
#........
...#.....)");
	SeatingSystemV2 ss(iss);
	REQUIRE(ss.occupied_visible(NORTH, 3, 4));
	REQUIRE(ss.occupied_visible(NORTH_EAST, 3, 4));
	REQUIRE(ss.occupied_visible(EAST, 3, 4));
	REQUIRE(ss.occupied_visible(SOUTH_EAST, 3, 4));
	REQUIRE(ss.occupied_visible(SOUTH, 3, 4));
	REQUIRE(ss.occupied_visible(SOUTH_WEST, 3, 4));
	REQUIRE(ss.occupied_visible(WEST, 3, 4));
	REQUIRE(ss.occupied_visible(NORTH_WEST, 3, 4));
}

TEST_CASE("occupied_visible all false", "[day11]")
{
	std::istringstream iss(R"(.##.##.
#.#.#.#
##...##
...L...
##...##
#.#.#.#
.##.##.)");
	SeatingSystemV2 ss(iss);
	REQUIRE(!ss.occupied_visible(NORTH, 3, 3));
	REQUIRE(!ss.occupied_visible(NORTH_EAST, 3, 3));
	REQUIRE(!ss.occupied_visible(EAST, 3, 3));
	REQUIRE(!ss.occupied_visible(SOUTH_EAST, 3, 3));
	REQUIRE(!ss.occupied_visible(SOUTH, 3, 3));
	REQUIRE(!ss.occupied_visible(SOUTH_WEST, 3, 3));
	REQUIRE(!ss.occupied_visible(WEST, 3, 3));
	REQUIRE(!ss.occupied_visible(NORTH_WEST, 3, 3));
}

TEST_CASE("day11", "[day11]")
{
	std::string input = R"(L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL)";
	std::istringstream iss1(input);
	std::istringstream iss2(input);

	REQUIRE(day11_1(iss1) == 37);
	REQUIRE(day11_2(iss2) == 26);
}
#endif
