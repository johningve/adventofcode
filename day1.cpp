#include <iostream>
#include <cstdio>

#include "adventofcode.h"
#include "util.h"

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

void day1_1(std::ifstream &file)
{
	int result = -1;
	std::vector<int> numbers;
	// find two numbers in input that add up to 2020 exactly, then multiply those numbers
	if (read_numbers(file, numbers) == -1)
	{
		perror("day1");
		goto exit;
	}

	for (int i = 0; i < (int)numbers.size(); i++)
	{
		int j = find_subset_sum(2020, numbers[i], numbers);
		if (j == i || j == -1)
			continue;
		result = numbers[i] * numbers[j];
		goto exit;
	}

exit:
	std::cout << result << std::endl;
}

void day1_2(std::ifstream &file)
{
	int result = -1;
	std::vector<int> numbers;
	// find two numbers in input that add up to 2020 exactly, then multiply those numbers

	if (read_numbers(file, numbers) == -1)
	{
		perror("day1");
		goto exit;
	}

	for (int i = 0; i < (int)numbers.size(); i++)
	{
		for (int j = 0; j < (int)numbers.size(); j++)
		{
			int k = find_subset_sum(2020, numbers[i] + numbers[j], numbers);
			if (k == -1 || k == i || k == j || j == i)
				continue;
			result = numbers[i] * numbers[j] * numbers[k];
			goto exit;
		}
	}

exit:
	std::cout << result << std::endl;
}
