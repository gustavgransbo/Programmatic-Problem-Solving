#include <vector>
#include <queue>
#include <iostream>


using graph = std::vector<std::vector<int>>;
typedef std::vector<std::vector<int>> adj_list;

struct Flow
{
	graph g;
	long long flow;
};

int GRAPH_SIZE;
int MAX_FLOW = 1000000000;

std::vector<int> bfs(graph &g, adj_list &adj, int s, int t)
{
	std::vector<bool> visited (GRAPH_SIZE, false);
	std::vector<int> parent(GRAPH_SIZE, -2);
	std::queue<int> q;
	q.push(s);
	parent[s] = -1;
	visited[s] = true;
	while(!q.empty())
	{
		int cur = q.front();
		q.pop();
		for(int dest: adj[cur])
		{
			if(g[cur][dest] > 0 && !visited[dest])
			{
				q.push(dest);
				parent[dest] = cur;
				visited[dest] = true;
				if(dest == t) return parent;
			}
		}
	}
	return parent;
}

std::vector<bool> bfs2(graph &g, adj_list &adj, int s)
{
	std::vector<bool> visited (GRAPH_SIZE, false);
	std::vector<int> parent(GRAPH_SIZE, -2);
	std::queue<int> q;
	q.push(s);
	visited[s] = true;
	while(!q.empty())
	{
		int cur = q.front();
		q.pop();
		for(int dest: adj[cur])
		{
			if(g[cur][dest] > 0 && !visited[dest])
			{
				q.push(dest);
				visited[dest] = true;
			}
		}
	}
	return visited;
}

int path_flow(graph &g, std::vector<int> &path, int t)
{
	int res = MAX_FLOW;
	int cur = t;
	while(path[cur] != -1)
	{
		if(g[path[cur]][cur] < res) res = g[path[cur]][cur];
		cur = path[cur];
	}
	return res;
}



void update_flow(graph &g, graph &flow, std::vector<int> &path, int t, int path_flow)
{
	int cur = t;
	while(path[cur] != -1)
	{
		g[path[cur]][cur] -= path_flow;
		flow[path[cur]][cur] += path_flow;
		g[cur][path[cur]] += path_flow;
		flow[cur][path[cur]] -= path_flow;
		cur = path[cur];
	}
}

void update_flow2(graph &g, std::vector<int> &path, int t, int path_flow)
{
	int cur = t;
	while(path[cur] != -1)
	{
		g[path[cur]][cur] -= path_flow;
		g[cur][path[cur]] += path_flow;
		cur = path[cur];
	}
}

std::vector<int> min_cut(graph &g, adj_list &adj, int s, int t)
{
	GRAPH_SIZE = g.size();
	std::vector<int> res;
	std::vector<int> path;
	path = bfs(g, adj, s, t);
	while(path[t] != -2)
	{
		int p_flow = path_flow(g, path, t);
		update_flow2(g, path, t, p_flow);
		path = bfs(g, adj, s, t);
	}
	std::vector<bool> visited = bfs2(g, adj, s);
	for(int i = 0; i < visited.size(); ++i)
	{
		if(visited[i]) res.push_back(i);
	}
	return res;
}

Flow max_flow(graph &g, adj_list &adj, int s, int t)
{
	GRAPH_SIZE = g.size();
	graph flow(GRAPH_SIZE, std::vector<int>(GRAPH_SIZE));
	long long res = 0;
	std::vector<int> path;
	path = bfs(g, adj, s, t);
	while(path[t] != -2)
	{
		int p_flow = path_flow(g, path, t);
		update_flow(g, flow, path, t, p_flow);
		res += p_flow;
		path = bfs(g, adj, s, t);
	}
	return {flow, res};
	
}