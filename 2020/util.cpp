#include <sstream>
#include <string>

#include "util.h"

std::vector<int> read_numbers(std::istream &file)
{
	std::vector<int> arr;
	std::string line;
	while (std::getline(file, line))
	{
		int num;
		std::istringstream iss(line);
		if (!(iss >> num))
			break;
		arr.push_back(num);
	}
	return arr;
}

int find_subset_sum(int sum, int num, std::vector<int> &arr)
{
	for (std::size_t j = 0; j < arr.size(); j++)
	{
		if (arr[j] + num == sum)
		{
			return j;
		}
	}
	return -1;
}

void swap(int &a, int &b)
{
	int t = a;
	a = b;
	b = t;
}
