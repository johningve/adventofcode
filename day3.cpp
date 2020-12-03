#include <iostream>
#include <string>

#include "adventofcode.h"

void day3_1(std::ifstream &file)
{
	int x = 0, num_trees = 0;
	std::string line;
	while ((std::getline(file, line)))
	{
		if (line[x % line.length()] == '#')
		{
			num_trees++;
		}
		x += 3;
	}
	std::cout << num_trees << std::endl;
}
