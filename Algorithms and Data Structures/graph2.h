#include <list>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
#include <unordered_set>

/*
* Graph class and accompanying edge classes used by many of my other solutions.
*/

const long long MAX_COST = std::numeric_limits<unsigned long long>::max() / 4;

class Edge
{
public:
	Edge(unsigned long long _dest, long long _cost):dest{_dest},cost{_cost}{}
	unsigned long long dest;
	long long cost;
	virtual long long get_cost(long long prev_cost){return prev_cost + cost;}
};

class TimeEdge: public Edge
{
public:
	TimeEdge(unsigned long long _dest, long long _cost, long long _t, unsigned long long _p):Edge{_dest, _cost},t{_t},P{_p}{}
	long long t;
	unsigned long long P;
	
	long long get_cost(long long prev_cost) override
	{
		if(P == 0 and prev_cost > t) return MAX_COST;
		else if (prev_cost <= t) return t + cost;
		else if((prev_cost-t) % P == 0) return prev_cost + cost;
		else return P - ((prev_cost - t) % P) + cost + prev_cost; 
	}
};

template <class Edge>
using Node = std::vector<Edge>;

/*
* Adjacency list representation of a graph.
*/
template <class Edge>
class Graph
{
public:
	Graph():end{}{}
	Graph(unsigned long long &_size):nodes{_size},end{_size}
	{}
	void add_node()
	{
		nodes[end] = {};
		++end;
	}
	void add_edge(unsigned long long from, const Edge &e)
	{
		nodes[from].push_back(e);
		//has_edges.insert(from);
	}
	
	unsigned long long size()
	{
		return end;
	}
	
	Node<Edge> node(unsigned long long id)
	{
		return nodes[id];
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
	std::vector<Node<Edge>> nodes;
	//Post end index
	unsigned long long end;
};


