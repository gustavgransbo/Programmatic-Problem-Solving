#include <vector>
#include <iostream>
#include "../Algorithms and Data Structures/union_find.h"
#include <algorithm>
#include <cmath>
#include <iomanip>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/arcticnetwork
*/

const unsigned N_max = 500;

using namespace std;

struct point {
	unsigned x, y;
};

struct edge{
	unsigned v1, v2;
	double distance;
};

double distance(point const & p1, point const & p2)
{
	
	return sqrt((p1.x-p2.x) * (p1.x-p2.x) + (p1.y-p2.y) * (p1.y-p2.y));
}

int main(){
		
	unsigned n;
	cout << fixed;
    cout << setprecision(2);
	ios::sync_with_stdio(false);
	cin >> n;
	
	// Solve n cases
	while(n--)
	{
		/*
		*	Read input and construct edgelist graph as well as union find.
		*/
		unsigned S, P;
		cin >> S >> P;
		
		// Store outposts represented by their x and y coordinates
		vector<point> outposts (P);
		
		// Construct union find representing which outposts are connected.
		// Initially all outposts are only connected to themselves.
		element unions [N_max];
		for(unsigned i = 0; i < P; ++i)
		{
			unions[i].parent = i;
			cin >> outposts[i].x >> outposts[i].y;
		}
		
		// Store the distance between all outposts as edges
		vector<edge> edges (P * (P-1));
		for(unsigned i = 0; i < P; ++i)
			for(unsigned j = i+1; j < P; ++j)
			{
				edges[i*P+j] = {i, j, distance(outposts[i], outposts[j])};
			}
		
		/*
		*	Solve problem using modified version of Kruskals MST algorithm:
		*	
		*	Choose the shortest distance available to connect two outposts that are not connected.
		*	Repeat until P-S-1 edges have been chosen. Now there are S disjoint sets of outposts.
		*	Connect these with the satellite channels. 
		*/
		auto cmp = [](edge& e1, edge& e2){return e1.distance < e2.distance;};
		sort(begin(edges), end(edges), cmp);
		
		
		unsigned i = 0;
		unsigned e = 0;
		double cost = 0;
		while(e < P-S)
		{
			auto current_edge = edges[i++];
			if(find(unions, current_edge.v1) != find(unions, current_edge.v2))
			{
				Union(unions, current_edge.v1, current_edge.v2);
				++e;
				cost = current_edge.distance;
			}
		}
		cout << cost << "\n";
	}
	
}