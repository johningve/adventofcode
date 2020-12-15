#include "graph.h"

void Graph::add_edge(int from, int to)
{
	graph[from].insert(to);
}

const std::unordered_set<int> &Graph::get_neighbors(int node)
{
	return graph[node];
}
