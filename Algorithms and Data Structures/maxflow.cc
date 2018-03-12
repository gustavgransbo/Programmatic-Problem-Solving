#include <iostream>
#include "maxflow.h"
#include <algorithm>
#include <vector>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/maxflow
*/

using namespace std;

struct ans
{
	int from, to;
	long long flow;
};

int main()
{
	int n, m, s, t, u, v, c;
	scanf("%d %d %d %d", &n, &m, &s, &t);
	graph g (n,vector<int>(n));
	adj_list adj (n, vector<int>());
	
	while(m--)
	{
		scanf("%d %d %d", &u, &v, &c);
		g[u][v] = c;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	Flow flow = max_flow(g, adj, s, t);
	vector<ans> edges;
	for(int i = 0; i < flow.g.size(); ++i)
	{
		for(int j = 0; j < flow.g.size(); ++j)
		{
			if(flow.g[i][j] > 0)
			{
				edges.push_back({i, j, flow.g[i][j]});
			}
		}
	}
	printf("%d %lld %lu\n", n, flow.flow, edges.size());
	for_each(begin(edges), end(edges),
		[](ans &a){printf("%d %d %lld\n", a.from, a.to, a.flow);});
	
}