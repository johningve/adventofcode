#include <iostream>
#include <istream>
#include <string>
#include <regex>

#include "adventofcode.h"

void day2_1(std::istream &file)
{
	int num_valid = 0;
	std::string line;
	std::regex reg(R"((\d+)-(\d+)\s([a-z]):\s([a-z]+))");
	while (std::getline(file, line))
	{
		std::smatch matches;
		if (!std::regex_search(line, matches, reg))
			continue;

		int min = std::stoi(matches[1].str());
		int max = std::stoi(matches[2].str());
		std::string rule = matches[3].str();
		std::string password = matches[4].str();

		// count occurrences of rule in password
		int occurrences = 0;
		std::size_t pos = 0;
		while ((pos = password.find(rule, pos)) != std::string::npos)
		{
			occurrences++;
			pos += rule.length();
		}

		if (min <= occurrences && occurrences <= max)
		{
			num_valid++;
		}
	}

	std::cout << num_valid << std::endl;
}

void day2_2(std::istream &file)
{
	int num_valid = 0;
	std::string line;
	std::regex reg(R"((\d+)-(\d+)\s([a-z]):\s([a-z]+))");
	while (std::getline(file, line))
	{
		std::smatch matches;
		if (!std::regex_search(line, matches, reg))
			continue;

		int pos1 = std::stoi(matches[1].str()) - 1;
		int pos2 = std::stoi(matches[2].str()) - 1;
		char rule = matches[3].str()[0];
		std::string password = matches[4].str();

		bool rule1 = password[pos1] == rule;
		bool rule2 = password[pos2] == rule;

		if (rule1 != rule2)
		{
			num_valid++;
		}
	}

	std::cout << num_valid << std::endl;
}
