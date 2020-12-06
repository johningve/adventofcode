#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>

#include "adventofcode.h"

void day5_1(std::ifstream &file)
{
	int highest_id = 0;
	std::string line;
	while (std::getline(file, line))
	{
		int row_lower = 0, row_upper = 127, column_lower = 0, column_upper = 7;

		for (char &c : line)
		{
			switch (c)
			{
			case 'F':
				row_upper /= 2;
				break;
			case 'B':
				row_lower = row_upper / 2 + 1;
				break;
			case 'L':
				column_upper /= 2;
				break;
			case 'R':
				column_lower = column_upper / 2 + 1;
				break;
			}
		}

		int id = std::min(row_lower, row_upper) * 8 + std::max(column_lower, column_upper);
		if (id > highest_id)
		{
			highest_id = id;
		}
	}

	std::cout << highest_id << std::endl;
}
