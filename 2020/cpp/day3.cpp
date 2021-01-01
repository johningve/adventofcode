#include <string>

#include "adventofcode.h"

long trees_on_slope(std::istream &file, int slopeX, int slopeY)
{
	long x = 0, y = 0, num_trees = 0;
	std::string line;
	while (std::getline(file, line))
	{
		// increment y each time, but only check the position after
		// having moved down one step in the slope
		if (y++ % slopeY != 0)
			continue;
		if (line[x % line.length()] == '#')
		{
			num_trees++;
		}
		x += slopeX;
	}
	// reset stream state so that we can run this multiple times
	file.clear();
	file.seekg(0, std::ios::beg);
	return num_trees;
}

long day3_1(std::istream &file)
{
	return trees_on_slope(file, 3, 1);
}

long day3_2(std::istream &file)
{
	// int is too small
	long answer = 1;
	answer *= trees_on_slope(file, 1, 1);
	answer *= trees_on_slope(file, 3, 1);
	answer *= trees_on_slope(file, 5, 1);
	answer *= trees_on_slope(file, 7, 1);
	answer *= trees_on_slope(file, 1, 2);
	return answer;
}
