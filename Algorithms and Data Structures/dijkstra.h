#include "graph2.h"
#include <vector>
#include <queue>
#include <numeric>

struct nc
{
	unsigned long long node;
	long long cost;
};

/*
* Returns cost vector to all nodes in graph g from node start.
* Edges should have a cost and a dest and a cost table.
*/
template <class Edge>
std::vector<long long> shortest_paths(Graph<Edge> g, unsigned long long start)
{
	std::vector<long long> costs(g.size(), MAX_COST);
	std::vector<bool> visited(g.size(), false);
	std::vector<long long> prev(g.size());
	std::iota(begin(prev), end(prev), 0);
	costs[start] = 0;
	/*auto cmp = [&](unsigned long long& n1, unsigned long long& n2){return costs[n1] > costs[n2];};
	std::priority_queue<unsigned long long, std::vector<unsigned long long>, decltype(cmp)> pq(cmp);*/
	auto cmp = [](nc& nc1, nc& nc2){return nc1.cost > nc2.cost;};
	std::priority_queue<nc, std::vector<nc>, decltype(cmp)> pq(cmp);
	
	pq.push({start, 0});
	
	while(!pq.empty())
	{
		unsigned long long current = pq.top().node;
		pq.pop();
		if(!visited[current])
		{
			visited[current] = true;
			for(auto t: g.node(current))
			{
				long long cost = t.get_cost(costs[current]);
				if(cost < costs[t.dest])
				{
					costs[t.dest] = cost;
					pq.push({t.dest, cost});
					prev[t.dest] = current;
				}
			}
		}
	}
	return costs;
}