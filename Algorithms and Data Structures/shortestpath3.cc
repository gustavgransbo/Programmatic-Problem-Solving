#include <iostream>
#include "bellman_ford.h"

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/shortestpath3
*/

using namespace std;

int main()
{
	unsigned long long n, m, q, s, a, b;
	long long c;
	
	
	while(true)
	{
		scanf("%llu %llu %llu %llu", &n, &m, &q, &s);
		if(n == 0) break;
		EdgeList<List_Edge> g(n);
		while(m--)
		{
			scanf("%llu %llu %lld", &a, &b, &c);
			g.add_edge({a, b, c});
		}
		
		vector<long long> costs = shortest_paths(g, s);
		while(q--)
		{
			scanf("%llu", &a);
			if(costs[a] >= MAX_COST) printf("Impossible");
			else if(costs[a] <= -MAX_COST) printf("-Infinity");
			else printf("%lld", costs[a]);
			printf("\n");
		}
		printf("\n");
	}
}