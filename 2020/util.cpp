#include <sstream>
#include <string>

#include "util.h"

int read_numbers(std::istream &file, std::vector<int> &arr)
{
	int n = -1;
	std::string line;
	while (std::getline(file, line))
	{
		int num;
		std::istringstream iss(line);
		if (!(iss >> num))
			break;
		arr.push_back(num);
		n++;
	}
	return n;
}
