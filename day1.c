#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <glib.h>

#include "adventofcode.h"

int day1(char *input, char *output, size_t n)
{
	int result = -1;
	GArray *numbers = g_array_new(false, false, sizeof(int));
	// find two numbers in input that add up to 2020 exactly, then multiply those numbers
	FILE *fp = fopen(input, "r");

	char *line;
	size_t len = 0;
	while (getline(&line, &len, fp) != -1)
	{
		int num = atoi(line);
		g_array_append_val(numbers, num);
	}
	free(line);

	if (errno)
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
