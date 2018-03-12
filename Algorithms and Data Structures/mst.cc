#include "prim.h"

using namespace std;

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/minspantree
*/

int main()
{
	unsigned long long n, m, u, v;
	int w;
	
	while(true)
	{
		scanf("%llu %llu", &n, &m);
		if(n == 0) break;
		Graph g(n);
		while(m--)
		{
			scanf("%llu %llu %d", &u, &v, &w);
			g.add_edge(u, {u, v, w});
			g.add_edge(v, {v, u, w});
		}
		minspantree res = mst(g);
		sort(begin(res.edges), end(res.edges), [](Edge e1, Edge e2){return e1.from < e2.from || (e1.from == e2.from && e1.dest < e2.dest);});
		if(res.edges.size() + 1 == n && !res.edges.empty())
		{
			printf("%lld\n", res.cost);
			for(Edge e: res.edges)
			{
				printf("%llu %llu\n", e.from, e.dest);
			}
		}else printf("Impossible\n");
	}
}