#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

struct Edge
{
	unsigned long long from, dest;
	long long cost;
};


using Node = std::vector<Edge>;
class Graph
{
public:
	Graph():end{}{}
	Graph(unsigned long long &_size):nodes{_size},end{_size}
	{}
	void add_edge(unsigned long long from, const Edge &e)
	{
		nodes[from].push_back(e);
	}
	
	unsigned long long size()
	{
		return end;
	}
	
	Node* node(unsigned long long id)
	{
		return &nodes[id];
	}
	
	void print()
	{
		for(unsigned long long i = 0; i < end; ++i)
		{
			printf("%llu: [", i);
			std::for_each(begin(nodes[i]), nodes[i].end(),
				[](Edge &e){printf("(%llu %lld)", e.dest, e.cost);});
			printf("]\n");
		}
	}
	
private:
	std::vector<Node> nodes;
	//Post end index
	unsigned long long end;
};

struct minspantree
{
	std::vector<Edge> edges;
	long long cost = 0;
};


minspantree mst(Graph &g)
{
	unsigned long long n = g.size();
	std::vector<bool> included (n, false);
	minspantree res {};
	auto cmp = [](Edge *e1, Edge *e2){return e1->cost > e2->cost;};
	std::priority_queue<Edge*, std::vector<Edge*>, decltype(cmp)> pq(cmp);
	
	included[0] = true;
	for(Edge& e: *g.node(0))
	{
		if(!included[e.dest]) pq.push(&e);
	}
	
	while(res.edges.size()+1 < n && !pq.empty())
	{
		//while(!pq.empty() && included[pq.top()->dest]) pq.pop();
		if(included[pq.top()->dest])
		{
			pq.pop();
			continue;
		}
		Edge* current = pq.top();
		pq.pop();
		included[current->dest] = true;
		if(current->from < current->dest) res.edges.push_back(*current);
		else res.edges.push_back({current->dest, current->from, current->cost});
		res.cost += current->cost;
		Node* node = g.node(current->dest);
		for(Edge& e: *node)
		{
			if(!included[e.dest]) pq.push(&e);
		}
	}
	return res;
}