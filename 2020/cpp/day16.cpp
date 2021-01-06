#include <cassert>
#include <string>
#include <sstream>
#include <regex>
#include <vector>

#include "adventofcode.h"

#ifdef TEST
#include <catch2/catch.hpp>
#endif

struct Range
{
	int min, max;

	Range(int min, int max) : min(min), max(max) {}

	bool validate(int n)
	{
		return n >= min && n <= max;
	}
};

struct Field
{
	std::string name;
	Range lower;
	Range upper;

	Field(std::string name, Range lower, Range upper) : name(name), lower(lower), upper(upper) {}

	bool validate(int n)
	{
		return upper.validate(n) || lower.validate(n);
	}
};

struct TicketValidation
{
	std::vector<Field> fields;

	bool validate_field(int field_number, int value)
	{
		assert(field_number < (int)fields.size());
		return fields[field_number].validate(value);
	}
};

typedef std::vector<int> Ticket;

std::pair<Ticket, bool> read_ticket(std::istream &input)
{
	Ticket output;
	std::string value_str;
	while (std::getline(input, value_str, ','))
	{
		int value;
		try
		{
			value = std::stoi(value_str);
		}
		catch (const std::invalid_argument &e)
		{
			return {output, false};
		}
		output.push_back(value);
	}
	return {output, true};
}

int64_t day16_1(std::istream &file)
{
	TicketValidation validator;
	int error_rate = 0;

	std::regex field_reg(R"(([\w ]+): (\d+)-(\d+) or (\d+)-(\d+))");
	std::smatch matches;
	std::string line;
	while (std::getline(file, line))
	{
		if (line == "your ticket:")
		{
			// skip for now
			std::getline(file, line);
			break;
		}

		if (!std::regex_match(line, matches, field_reg))
			continue;

		validator.fields.push_back(Field(matches[1],
										 Range(std::stoi(matches[2]), std::stoi(matches[3])),
										 Range(std::stoi(matches[4]), std::stoi(matches[5]))));
	}

	while (std::getline(file, line))
	{
		std::string value_str;
		std::istringstream iss(line);
	next_field:
		while (std::getline(iss, value_str, ','))
		{
			int value;
			try
			{
				value = std::stoi(value_str);
			}
			catch (const std::invalid_argument &e)
			{
				break;
			}
			for (int i = 0; i < (int)validator.fields.size(); i++)
			{
				if (validator.validate_field(i, value))
				{
					goto next_field;
				}
			}
			error_rate += value;
		}
	}

	return error_rate;
}

int64_t day16_2(std::istream &file)
{
	Ticket our_ticket;
	TicketValidation validator;
	std::vector<std::vector<int>> field_scores;
	int64_t answer = 1;

	std::regex field_reg(R"(([\w ]+): (\d+)-(\d+) or (\d+)-(\d+))");
	std::smatch matches;
	std::string line;
	while (std::getline(file, line))
	{
		if (line == "your ticket:")
		{
			break;
		}

		if (!std::regex_match(line, matches, field_reg))
			continue;

		validator.fields.push_back(Field(matches[1],
										 Range(std::stoi(matches[2]), std::stoi(matches[3])),
										 Range(std::stoi(matches[4]), std::stoi(matches[5]))));
	}

	while (std::getline(file, line))
	{
		if (line == "nearyby tickets:")
			break;

		std::string value_str;
		std::istringstream iss(line);

		auto [ticket, ok] = read_ticket(iss);
		if (ok)
			our_ticket = ticket;
	}

	while (std::getline(file, line))
	{
		std::string value_str;
		std::istringstream iss(line);

		auto [t, ok] = read_ticket(iss);
		if (!ok)
			continue;

		for (int i = 0; i < (int)t.size(); i++)
		{
			for (int j = 0; j < (int)validator.fields.size(); j++)
			{
				if (validator.validate_field(j, t[i]))
				{
					field_scores[j][i]++;
				}
			}
		}
	}

	for (int i = 0; i < (int)field_scores.size(); i++)
	{
		int max = 0;
		int field = 0;
		for (int j = 0; j < (int)field_scores[i].size(); j++)
		{
			if (field_scores[i][j] > max)
			{
				field = j;
				max = field_scores[i][j];
			}
		}
		if (validator.fields[field].name.find("departure") == 0)
		{
			answer *= our_ticket[field];
		}
	}

	return answer;
}

#ifdef TEST
TEST_CASE("Test day16 part1", "[day16]")
{
	std::string input = R"(class: 1-3 or 5-7
row: 6-11 or 33-44
seat: 13-40 or 45-50

your ticket:
7,1,14

nearby tickets:
7,3,47
40,4,50
55,2,20
38,6,12)";

	std::istringstream iss(input);
	REQUIRE(day16_1(iss) == 71);
}
#endif
