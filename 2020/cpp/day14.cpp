#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <unordered_map>
#include <cassert>

#include "adventofcode.h"

#ifdef TEST
#include <catch2/catch.hpp>
#include <sstream>
#endif

const uint64_t mask = 0xFFFFFFFFF;
const uint64_t msb = 0x800000000;

struct BitMask
{
	uint64_t ones = 0;
	uint64_t zeros = mask;
	std::vector<uint64_t> floating_bits;

	BitMask(std::string mask)
	{
		for (int i = 0; i < 36; i++)
		{
			char c = mask[i];
			if (c == '1')
				ones |= msb >> i;
			else if (c == '0')
				zeros &= ~(msb >> i);
			else if (c == 'X')
				floating_bits.push_back(35 - i);
		}
	}

	BitMask() : BitMask("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")
	{
	}

	uint64_t apply(uint64_t n)
	{
		return (n | ones) & zeros;
	}

	uint64_t last_floating()
	{
		return (1 << (uint64_t)floating_bits.size()) - 1;
	}

	uint64_t apply_floating(uint64_t n, uint64_t i)
	{
		assert(i <= last_floating());
		uint64_t floating = n | ones;
		int j = floating_bits.size() - 1;
		for (auto &bit_number : floating_bits)
		{
			uint64_t bitmask = ((uint64_t)1) << bit_number;
			if (i & (1 << j--))
				floating |= bitmask;
			else
				floating &= ~bitmask;
		}

		return floating;
	}
};

int64_t day14_1(std::istream &file)
{
	uint64_t sum = 0;
	BitMask bm;
	std::string line;
	std::unordered_map<uint64_t, uint64_t> mem;
	std::regex mask_reg(R"(mask = ([01X]{36}))");
	std::regex mem_reg(R"(mem\[(\d+)\] = (\d+))");

	while (std::getline(file, line))
	{
		std::smatch matches;
		if (std::regex_match(line, matches, mask_reg))
		{
			bm = BitMask(matches[1]);
		}
		else if (std::regex_match(line, matches, mem_reg))
		{
			mem[std::stoi(matches[1])] = bm.apply(std::stoi(matches[2]));
		}
	}

	for (auto &n : mem)
		sum += n.second;

	return sum;
}

int64_t day14_2(std::istream &file)
{
	uint64_t sum = 0;
	BitMask bm;
	std::string line;
	std::unordered_map<uint64_t, uint64_t> mem;
	std::regex mask_reg(R"(mask = ([01X]{36}))");
	std::regex mem_reg(R"(mem\[(\d+)\] = (\d+))");

	while (std::getline(file, line))
	{
		std::smatch matches;
		if (std::regex_match(line, matches, mask_reg))
		{
			bm = BitMask(matches[1]);
		}
		else if (std::regex_match(line, matches, mem_reg))
		{
			uint64_t address = std::stoi(matches[1]);
			uint64_t value = std::stoi(matches[2]);
			for (uint64_t i = 0; i <= bm.last_floating(); i++)
			{
				mem[bm.apply_floating(address, i)] = value;
			}
		}
	}

	for (auto &n : mem)
		sum += n.second;

	return sum;
}

#ifdef TEST
TEST_CASE("Test that bitmask works correctly", "[day14]")
{
	BitMask bm("XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X");
	REQUIRE(bm.apply(11) == 73);
	REQUIRE(bm.apply(101) == 101);
	REQUIRE(bm.apply(0) == 64);

	bm = BitMask("XXXXXXXXXXXXXXXXXXXXXXXXXX1XXXXXXXXX");
	REQUIRE(bm.apply(0) == 512);

	bm = BitMask("1XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
	REQUIRE(bm.apply(0) == 0x800000000);
}

TEST_CASE("Test that the sum is calculated correctly", "[day14]")
{
	std::istringstream iss(R"(mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X
mem[8] = 11
mem[7] = 101
mem[8] = 0)");
	REQUIRE(day14_1(iss) == 165);
}

TEST_CASE("Test that floating addresses are generated correctly", "[day14]")
{
	BitMask bm("X00000000000000000000000000000000001");
	REQUIRE(bm.last_floating() == 1);
	REQUIRE(bm.apply_floating(1, 0) == 1);
	REQUIRE(bm.apply_floating(1, 1) == 0x800000001);

	bm = BitMask("000000000000000000000000000000X1001X");
	REQUIRE(bm.apply_floating(42, 0) == 26);
	REQUIRE(bm.apply_floating(42, 1) == 27);
	REQUIRE(bm.apply_floating(42, 2) == 58);
	REQUIRE(bm.apply_floating(42, 3) == 59);
}
#endif
