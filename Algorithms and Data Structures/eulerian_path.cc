#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <stack>
#include <cassert>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/eulerianpath
*/

using namespace std;

typedef vector<unsigned> Node;
typedef vector<Node> Graph;

struct Edge
{
	unsigned to, from;
};

void dfs(Graph const & g, vector<bool> & visited, unsigned const &i)
{
	visited[i] = true;
	for(unsigned const & u: g[i])
	{
		if(!visited[u]) dfs(g, visited, u);
	}
}

// Start must be one of two vertices where in-degree and out-degree 
// do not match. Of these two it must be the one that has higher
// out-degree than in-degree.
bool connected(Graph const & g, unsigned const & start)
{
	vector<bool> visited (g.size());
	visited[start] = true;
	dfs(g, visited, start);
	for(unsigned i = 0; i < g.size(); ++i) 
		if(!visited[i] && !g[i].empty()) return false;
	return true;
}


/*
* Implementation of Hierholzer’s Algorithm for finding eulerian paths.
*/
vector<unsigned> euler_path(Graph & g, vector<unsigned> const & in)
{
	// Determine if g is eulerian and find starpoint
	// Maximum of 2 vertices may have different in and out degrees.
	vector<unsigned> odd {};
	unsigned start {};
	for(unsigned i = 0; i < g.size(); ++i)
	{
		if(g[i].size()!=in[i])
		{
			odd.push_back(i);
			if(odd.size() > 2) return {};
		}
	}
	if(!odd.empty())
	{
		if(g[odd[0]].size() == in[odd[0]] + 1 && g[odd[1]].size() == in[odd[1]] - 1)
			start = odd[0];
		else if(g[odd[0]].size() == in[odd[0]] - 1 && g[odd[1]].size() == in[odd[1]] + 1)
			start = odd[1];
		else return {};
	} 
	if(!connected(g, start)) return {};
	stack<unsigned> path {};
	vector<unsigned> circuit {};
	path.push(start);
	
	while(!path.empty())
	{
		unsigned current = path.top();
		/*cout << "visiting: "<< current << endl;
		cout << "Circuit {";
		copy(begin(circuit), end(circuit), ostream_iterator<unsigned>(cout, " "));
		cout << "}" << endl;*/
		if(g[current].empty())
		{
			circuit.push_back(current);
			path.pop();
		}
		else
		{
			path.push(g[current].back());
			g[current].pop_back();
		}
	}
	return circuit;
}


int main()
{
	unsigned n, m, from, to;
	cin >> n >> m;
	while(n || m)
	{
		Graph g (n);
		vector<unsigned> in (n);
		while(m--)
		{
			cin >> from >> to;
			g[from].push_back(to);
			in[to]++;
		}
		vector<unsigned> reversed_circuit = euler_path(g, in);
		if(reversed_circuit.empty()) cout << "Impossible\n";
		else
		{
			
			copy(reversed_circuit.rbegin(), reversed_circuit.rend(), ostream_iterator<unsigned>(cout, " "));
			cout << "\n";
		}
		
		cin >> n >> m;
	}
}