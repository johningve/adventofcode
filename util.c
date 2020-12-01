#include "util.h"

int read_numbers(FILE *fp, GArray *arr)
{
	int n = 0;
	char *line;
	size_t len = 0;
	while (getline(&line, &len, fp) != -1)
	{
		int num = atoi(line);
		g_array_append_val(arr, num);
		n++;
	}
	if (errno)
	{
		n = -1;
	}
	free(line);
	return n;
}
