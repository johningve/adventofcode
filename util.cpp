#include "util.h"

int read_numbers(std::FILE *fp, std::vector<int> &arr)
{
	int n = 0;
	char *line = NULL;
	size_t len = 0;
	while (getline(&line, &len, fp) != -1)
	{
		int num = atoi(line);
		arr.push_back(num);
		n++;
	}
	if (errno)
	{
		n = -1;
	}
	free(line);
	return n;
}
