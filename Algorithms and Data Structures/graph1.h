#include <list>
#include <algorithm>
#include <iostream>
#include <string.h>
#include <vector>
#include <unordered_set>

struct Basic_Edge
{
	unsigned long long dest;
	unsigned long long cost;
};

struct Time_Edge
{
	unsigned long long dest, t, P, cost;
};

struct Neg_Weight_Edge
{
	unsigned long long dest;
	long long cost;
};

struct List_Edge
{
	unsigned long long from, dest;
	long long cost;
};

template <typename Edge_Type>
using Node = std::vector<Edge_Type>;


/*
* Adjacency list representation of a graph.
*/
template <typename Edge_Type>
class Graph
{
public:
	Graph():end{}{}
	Graph(unsigned long long &_size):nodes{_size},end{_size}
	{
		//std::fill_n(begin(nodes), _size, Node());
	}
	void add_node(unsigned long long id)
	{
		nodes[end] = {};
		++end;
	}
	void add_edge(unsigned long long from, Edge_Type e)
	{
		nodes[from].push_back(e);
		//has_edges.insert(from);
	}
	
	unsigned long long size()
	{
		return end;
	}
	
	Node<Edge_Type> node(unsigned long long id)
	{
		return nodes[id];
	}
	
	void print()
	{
		for(unsigned long long i = 0; i < end; ++i)
		{
			printf("%llu: [", i);
			std::for_each(begin(nodes[i]), nodes[i].end(),
				[](Edge_Type &e){printf("(%llu %lld)", e.dest, e.cost);});
			printf("]\n");
		}
	}
	
private:
	std::vector<Node<Edge_Type>> nodes;
	//Post end index
	unsigned long long end;
};

template <typename Edge_Type>
class EdgeList
{
public:
	EdgeList(unsigned long long _size):end{_size}{}
	void add_edge(Edge_Type e)
	{
		edges.push_back(e);
		//has_edges.insert(from);
	}
	
	unsigned long long size()
	{
		return end;
	}
	std::vector<Edge_Type> edges;	
private:
	unsigned long long end;
	
};
