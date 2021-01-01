#pragma once

#include <istream>
#include <vector>

std::vector<int> read_numbers(std::istream &file);

int find_subset_sum(int sum, int num, std::vector<int> &arr);

void swap(int &a, int &b);
