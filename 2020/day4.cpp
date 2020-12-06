#include <iostream>
#include <string>
#include <regex>
#include <unordered_set>
#include <memory>

#include "adventofcode.h"

class Passport
{
public:
	int byr, iyr, eyr;
	std::string hgt, hcl, ecl, pid, cid;

	virtual bool validate()
	{
		// ignore empty cid
		if (byr == 0 || iyr == 0 || eyr == 0 || hgt.empty() || hcl.empty() || ecl.empty() || pid.empty())
		{
			return false;
		}
		return true;
	}
};

class Passport2 : public Passport
{
public:
	std::unordered_set<std::string> valid_ecl = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};

	virtual bool validate()
	{
		std::size_t pos;
		if (!Passport::validate())
		{
			std::cerr << "Missing fields" << std::endl;
			return false;
		}
		if (byr < 1920 || byr > 2002)
		{
			std::cerr << "Invalid byr: " << byr << std::endl;
			return false;
		}
		if (iyr < 2010 || iyr > 2020)
		{
			std::cerr << "Invalid iyr: " << iyr << std::endl;
			return false;
		}
		if (eyr < 2020 || eyr > 2030)
		{
			std::cerr << "Invalid eyr: " << eyr << std::endl;
			return false;
		}
		if ((pos = hgt.find("cm")) != std::string::npos)
		{
			int h = std::stoi(hgt.substr(0, pos));
			if (h < 150 || h > 193)
			{
				std::cerr << "Invalid hgt (cm): " << h << std::endl;
				return false;
			}
		}
		else if ((pos = hgt.find("in")) != std::string::npos)
		{
			int h = std::stoi(hgt.substr(0, pos));
			if (h < 59 || h > 76)
			{
				std::cerr << "Invalid hgt (in): " << h << std::endl;
				return false;
			}
		}
		else
		{
			return false;
		}
		if (!std::regex_match(hcl, std::regex(R"(^#[\da-f]{6}$)")))
		{
			std::cerr << "Invalid hcl: " << hcl << std::endl;
			return false;
		}
		if (valid_ecl.find(ecl) == valid_ecl.end())
		{
			std::cerr << "Invalid ecl: " << hcl << std::endl;
			return false;
		}
		if (!std::regex_match(pid, std::regex(R"(^\d{9}$)")))
		{
			std::cerr << "Invalid pid: " << pid << std::endl;
			return false;
		}

		return true;
	}
};

template <class T>
void day4(std::istream &file)
{
	int num_valid = 0;
	std::string line;
	auto current = std::unique_ptr<Passport>(new T());
	std::regex reg(R"(([a-z]+):([a-z\d#]+))");
	while (std::getline(file, line))
	{
		// when we get to an empty line, we validate and go to the next passport
		if (line == "")
		{
			if (current->validate())
				num_valid++;
			current.reset(new T());
			continue;
		}

		std::smatch match;
		std::string::const_iterator it(line.begin());
		while (std::regex_search(it, line.cend(), match, reg))
		{
			it = match.suffix().first;

			auto field = match[1].str();
			auto value = match[2].str();
			if (field == "byr")
				current->byr = std::stoi(value);
			else if (field == "iyr")
				current->iyr = std::stoi(value);
			else if (field == "eyr")
				current->eyr = std::stoi(value);
			else if (field == "hgt")
				current->hgt = value;
			else if (field == "hcl")
				current->hcl = value;
			else if (field == "ecl")
				current->ecl = value;
			else if (field == "pid")
				current->pid = value;
			else if (field == "cid")
				current->cid = value;
		}
	}

	if (current->validate())
	{
		num_valid++;
	}

	std::cout << num_valid << std::endl;
}

void day4_1(std::istream &file)
{
	day4<Passport>(file);
}

void day4_2(std::istream &file)
{
	day4<Passport2>(file);
}
