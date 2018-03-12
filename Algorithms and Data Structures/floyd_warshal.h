#include <vector>

using Graph = std::vector<std::vector<int>>;
const int MAX_COST = 10000000;

Graph apsp(Graph &g)
{
	// Floyd Warshal
	unsigned n = g.size();
	for(unsigned k = 0; k < n; ++k)
	{
		for(unsigned i = 0; i < n; ++i)
		{
			for(unsigned j = 0; j<n; ++j)
			{
				/*int b, c, d;
				c = g[i][k];
				d = g[k][j];
				b = (c!= MAX_COST && d != MAX_COST) ? c + d : MAX_COST;*/
				if(g[i][k]!= MAX_COST && g[k][j] != MAX_COST &&
					g[i][j] > g[i][k] + g[k][j]) g[i][j] = g[i][k] + g[k][j];
			}
		}
	}
	
	// Find all nodes reachable from a node inside a negative loop
	for(unsigned k = 0; k < n; ++k)
	{
		if(g[k][k] < 0)
		{
			for(unsigned i = 0; i < n; ++i)
			{
				for(unsigned j = 0; j<n; ++j)
				{
					if(g[i][k] != MAX_COST && g[k][j] != MAX_COST) g[i][j] = -MAX_COST;
				}
			}
		}
	}
	return g;
}