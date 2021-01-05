#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "adventofcode.h"

struct MemoryGame
{
	std::unordered_map<int64_t, int64_t> memory; // stores numbers and most recent round they were spoken
	int64_t last_spoken = 0;					 // stores the previously spoken number
	int64_t seen_before = 0;					 // stores the age of the previous number
	int64_t round = 0;							 // stores the current round number

	void speak_number(int64_t n)
	{
		if (memory[n] == 0)
			seen_before = 0;
		else
			seen_before = memory[n];

		memory[n] = ++round;
		last_spoken = n;
	}

	void next_round()
	{
		int64_t n;
		if (seen_before != 0)
			n = round - seen_before;
		else
			n = 0;
		speak_number(n);
	}

	int64_t find_nth_number(std::istream &input, int64_t n)
	{
		std::string num_str;

		while (std::getline(input, num_str, ','))
			speak_number(std::stoi(num_str));

		while (round < n)
			next_round();

		return last_spoken;
	}
};

int64_t day15_1(std::istream &file)
{
	MemoryGame game;
	return game.find_nth_number(file, 2020);
}

int64_t day15_2(std::istream &file)
{
	MemoryGame game;
	return game.find_nth_number(file, 30000000);
}
