#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "adventofcode.h"

static struct option options[] = {
	{"day1", required_argument, 0, 0},
	{0, 0, 0, 0},
};

static solution solutions[] = {
	day1,
};

int main(int argc, char *argv[])
{
	while (1)
	{
		int option_index = 0;
		int c = getopt_long(argc, argv, "", options, &option_index);
		if (c == -1)
			break;
		if (!optarg)
			break;

		// run the solution
		printf("%s", solutions[option_index](optarg));
	}
}
