#pragma once

#include <unordered_map>
#include <unordered_set>

class Graph
{
	std::unordered_map<int, std::unordered_set<int>> graph;

public:
	void add_edge(int from, int to);
	const std::unordered_set<int> &get_neighbors(int node);
};
