#include <sstream>
#include <string>

#include "util.h"

int read_numbers(std::ifstream &file, std::vector<int> &arr)
{
	int n = 0;
	std::string line;
	while (std::getline(file, line))
	{
		int num;
		std::istringstream iss(line);
		if (!(iss >> num))
			break;
		n++;
	}
	return n;
}
