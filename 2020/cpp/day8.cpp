#include <vector>
#include <string>
#include <unordered_set>

#ifdef TEST
#include <catch2/catch.hpp>
#include <sstream>
#endif

#include "adventofcode.h"

class Handheld
{
public:
	long accumulator = 0;
	long ip = 0;
	std::vector<std::pair<std::string, int>> instructions;

	Handheld(std::istream &file)
	{
		std::string line;
		while (std::getline(file, line))
		{
			int sep = line.find(' ');
			auto opstr = line.substr(0, sep);
			auto arg = std::stoi(line.substr(sep + 1));
			instructions.push_back(std::make_pair(opstr, arg));
		}
	}

	void execute_instruction()
	{
		auto &instruction = instructions[ip];
		if (instruction.first == "acc")
			accumulator += instruction.second;
		else if (instruction.first == "jmp")
			ip += instruction.second - 1;
		else if (instruction.first == "nop")
		{
		}
		ip++;
	}
};

int64_t day8_1(std::istream &file)
{
	std::unordered_set<int> executed_set;
	Handheld hh(file);
	while (hh.ip >= 0 && hh.ip < (long)hh.instructions.size())
	{
		if (executed_set.count(hh.ip))
			break;
		executed_set.insert(hh.ip);
		hh.execute_instruction();
	}
	return hh.accumulator;
}

int64_t day8_2(std::istream &file)
{
	Handheld hh(file);
	for (int i = 0; i < (int)hh.instructions.size(); i++)
	{
		auto tmp = hh.instructions[i].first;
		if (hh.instructions[i].first == "jmp")
			hh.instructions[i].first = "nop";
		else if (hh.instructions[i].first == "nop")
			hh.instructions[i].first = "jmp";
		else
			continue;

		// attempt to execute
		bool success = true;
		std::unordered_set<int> executed_set;
		while (hh.ip >= 0 && hh.ip < (long)hh.instructions.size())
		{
			if (executed_set.count(hh.ip))
			{
				success = false;
				break;
			}
			executed_set.insert(hh.ip);
			hh.execute_instruction();
		}
		if (success)
			break;

		hh.ip = 0;
		hh.accumulator = 0;
		hh.instructions[i].first = tmp;
	}
	return hh.accumulator;
}

#ifdef TEST
TEST_CASE("Detects infinite loop and returns accumulator value", "[day8]")
{
	std::istringstream iss(R"(nop +0
acc +1
jmp +4
acc +3
jmp -3
acc -99
acc +1
jmp -4
acc +6)");
	REQUIRE(day8_1(iss) == 5);
}

TEST_CASE("Attempts to fix infinite loop and returns the final accumulator value", "[day8]")
{
	std::istringstream iss(R"(nop +0
acc +1
jmp +4
acc +3
jmp -3
acc -99
acc +1
jmp -4
acc +6)");
	REQUIRE(day8_2(iss) == 8);
}
#endif
