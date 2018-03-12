#include <iostream>
#include "floyd_warshal.h"

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/allpairspath
*/

using namespace std;

int main()
{
	unsigned n, m, q, u, v;
	int w;
	while(true)
	{
		scanf("%u %u %u", &n, &m, &q);
		if(n == 0) break;
		Graph g(n, vector<int>(n, MAX_COST));
		for(unsigned i = 0; i < n; ++i)
		{
			g[i][i] = 0;
		}
		while(m--)
		{
			scanf("%u %u %d", &u, &v, &w);
			if(w < g[u][v]) g[u][v] = w;
		}
		
		
		g = apsp(g);
		while(q--)
		{
			scanf("%u %u", &u, &v);
			int cost = g[u][v];
			if(cost == MAX_COST) printf("Impossible\n");
			// TODO: Need to recognize path passing by a negative cycle as well.
			else if(cost == - MAX_COST) printf("-Infinity\n");
			else printf("%d\n", cost);
		}
		printf("\n");
	}
	
}