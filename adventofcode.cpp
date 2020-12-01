#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>

#include "adventofcode.h"

int main(int argc, char *argv[])
{
	init_solutions();

	while (true)
	{
		int option_index = 0;
		int c = getopt_long(argc, argv, "", &options[0], &option_index);
		if (c == -1)
			break;
		if (!optarg)
			break;

		// run the solution
		solutions[option_index](optarg);
	}
}
