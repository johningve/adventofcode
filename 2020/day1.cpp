#include <iostream>
#include <cstdio>

#include "adventofcode.h"
#include "util.h"

int day1_1(std::istream &file)
{
	int result = -1;
	// find two numbers in input that add up to 2020 exactly, then multiply those numbers
	auto numbers = read_numbers(file);

	for (int i = 0; i < (int)numbers.size(); i++)
	{
		int j = find_subset_sum(2020, numbers[i], numbers);
		if (j != i && j != -1)
		{
			result = numbers[i] * numbers[j];
			break;
		}
	}

	std::cout << result << std::endl;
	return 0;
}

int day1_2(std::istream &file)
{
	int result = -1;
	// find two numbers in input that add up to 2020 exactly, then multiply those numbers

	auto numbers = read_numbers(file);

	for (int i = 0; i < (int)numbers.size(); i++)
	{
		for (int j = 0; j < (int)numbers.size(); j++)
		{
			int k = find_subset_sum(2020, numbers[i] + numbers[j], numbers);
			if (k != -1 && k != i && k != j && i != j)
			{

				result = numbers[i] * numbers[j] * numbers[k];
				break;
			}
		}
	}

	std::cout << result << std::endl;
	return 0;
}
