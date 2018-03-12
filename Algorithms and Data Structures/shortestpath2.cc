#include <iostream>
#include "dijkstra.h"

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/shortestpath
*/

using namespace std;

const unsigned long long MAX_SIZE = 10000;

int main()
{
	unsigned long long n, m, q, s, a, b, P;
	long long c, t;

	while(true)
	{
		scanf("%llu %llu %llu %llu", &n, &m, &q, &s);
		if(n == 0) break;
		
		Graph<TimeEdge> g(n);
		while(m--)
		{
			scanf("%llu %llu %lld %llu %lld", &a, &b, &t, &P, &c);
			g.add_edge(a, {b, c, t, P});
		}
		
		vector<long long> paths = shortest_paths(g, s);
		while(q--)
		{
			scanf("%llu", &a);
			if(paths[a] < MAX_COST)
				printf("%lld", paths[a]);
			else printf("Impossible");
			printf("\n");
		}
		printf("\n");
	}
}