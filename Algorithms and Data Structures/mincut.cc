#include <iostream>
#include "maxflow.h"
#include <algorithm>
#include <vector>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/mincut
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
	vector<int> cut = min_cut(g, adj, s, t);
	printf("%lu\n", cut.size());
	for_each(begin(cut), end(cut),
		[](int &i){printf("%d\n", i);});
	
}