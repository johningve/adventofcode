#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>

#include "adventofcode.h"
#include "util.h"

int day1_1(char *input, char *output, size_t n)
{
	int result = -1;
	GArray *numbers = g_array_new(false, false, sizeof(int));
	// find two numbers in input that add up to 2020 exactly, then multiply those numbers
	FILE *fp = fopen(input, "r");
	if (fp == NULL)
	{
		perror("day1");
		goto exit;
	}

	if (read_numbers(fp, numbers) == -1)
	{
		perror("day1");
		goto exit;
	}

	for (int i = 0; i < numbers->len; i++)
	{
		for (int j = 0; j < numbers->len; j++)
		{
			if (i == j)
				continue;

			int vi = g_array_index(numbers, int, i);
			int vj = g_array_index(numbers, int, j);

			if (vi + vj == 2020)
			{
				result = vi * vj;
				goto exit;
			}
		}
	}

exit:
	g_array_free(numbers, true);
	if (result <= 0)
	{
		return -1;
	}
	snprintf(output, n, "%d\n", result);
	return 0;
}

int day1_2(char *input, char *output, size_t n)
{
	int result = -1;
	GArray *numbers = g_array_new(false, false, sizeof(int));
	// find two numbers in input that add up to 2020 exactly, then multiply those numbers
	FILE *fp = fopen(input, "r");
	if (fp == NULL)
	{
		perror("day1");
		goto exit;
	}

	if (read_numbers(fp, numbers) == -1)
	{
		perror("day1");
		goto exit;
	}

	for (int i = 0; i < numbers->len; i++)
	{
		for (int j = 0; j < numbers->len; j++)
		{
			for (int k = 0; k < numbers->len; k++)
			{
				if (i == j || j == k || i == k)
					continue;

				int vi = g_array_index(numbers, int, i);
				int vj = g_array_index(numbers, int, j);
				int vk = g_array_index(numbers, int, k);

				if (vi + vj + vk == 2020)
				{
					result = vi * vj * vk;
					goto exit;
				}
			}
		}
	}

exit:
	g_array_free(numbers, true);
	if (result <= 0)
	{
		return -1;
	}
	snprintf(output, n, "%d\n", result);
	return 0;
}
