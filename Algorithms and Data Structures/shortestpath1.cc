#include <iostream>
#include "dijkstra.h"

using namespace std;

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/shortestpath1
*/

const unsigned long long MAX_SIZE = 10000;

int main()
{
	unsigned long long n, m, q, s, a, b;
	long long c;
	
	
	while(true)
	{
		scanf("%llu %llu %llu %llu", &n, &m, &q, &s);
		if(n == 0) break;
		Graph<Edge> g(n);
		while(m--)
		{
			scanf("%llu %llu %lld", &a, &b, &c);
			Edge e {b ,c};
			g.add_edge(a, e);
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