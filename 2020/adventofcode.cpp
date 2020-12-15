#include <iostream>
#include <fstream>
#include <vector>
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
		std::ifstream file(optarg);
		if (file.fail())
		{
			perror(options[option_index].name);
			break;
		}
		long result = solutions[option_index](file);
		std::cout << result << std::endl;
	}
}
