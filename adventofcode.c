#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>

#include "adventofcode.h"

static size_t output_size = 100;

static struct option options[] = {
	{"day1_1", required_argument, 0, 0},
	{"day1_2", required_argument, 0, 0},
	{0, 0, 0, 0},
};

static solution solutions[] = {
	day1_1,
	day1_2,
};

int main(int argc, char *argv[])
{
	while (true)
	{
		char output[output_size];
		int option_index = 0;
		int c = getopt_long(argc, argv, "", options, &option_index);
		if (c == -1)
			break;
		if (!optarg)
			break;

		// run the solution
		int rc = solutions[option_index](optarg, output, output_size);
		if (rc)
			continue;
		printf("%s", output);
	}
}
