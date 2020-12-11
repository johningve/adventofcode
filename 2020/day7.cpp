#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "adventofcode.h"

typedef struct
{
	std::string name;
	int number;
} bag_rule_t;

class Day7
{
	std::unordered_set<std::string> compatible;
	std::unordered_map<std::string, std::vector<bag_rule_t>> bag_rules;

public:
	int run(std::istream &file, bool part1)
	{
		std::string line;
		std::regex parent_reg(R"(([\w ]+?) bags contain)"); // captures the name of the parent bag
		std::regex child_reg(R"((\d+) ([\w ]+?) bag)");		// captures the name and count of the child bags

		while (std::getline(file, line))
		{
			std::smatch matches;
			if (!std::regex_search(line, matches, parent_reg))
				continue;

			auto parent = matches[1].str();
			std::string suffix = matches.suffix().str();
			while (std::regex_search(suffix, matches, child_reg))
			{
				int count = std::stoi(matches[1].str());
				auto child = matches[2].str();
				if (part1)
					bag_rules[child].push_back({parent, count});
				else
					bag_rules[parent].push_back({child, count});
				suffix = matches.suffix().str();
			}
		}

		auto rules = bag_rules["shiny gold"];

		if (part1)
		{
			find_all_compatible(rules);
			return compatible.size();
		}
		else
		{
			return find_all_required(rules) - 1; // not counting the bag itself
		}
	}

private:
	void find_all_compatible(std::vector<bag_rule_t> &rules)
	{
		for (auto &rule : rules)
		{
			compatible.insert(rule.name);
			find_all_compatible(bag_rules[rule.name]);
		}
	}

	int find_all_required(std::vector<bag_rule_t> &rules)
	{
		int required = 1; // counting the bag itself
		// now find all bags required within this bag
		for (auto &rule : rules)
		{
			required += rule.number * find_all_required(bag_rules[rule.name]);
		}
		return required;
	}
};

int day7_1(std::istream &file)
{
	Day7 solution;
	std::cout << solution.run(file, true) << std::endl;
	return 0;
}

int day7_2(std::istream &file)
{
	Day7 solution;
	std::cout << solution.run(file, false) << std::endl;
	return 0;
}
