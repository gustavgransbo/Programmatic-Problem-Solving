#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>
#include <algorithm>
#include <set>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/brickwall
*/

using namespace std;

struct requirement
{
	unsigned c1, c2, c3;
};


bool operator<(const requirement lhs, const requirement rhs)
{
	return lhs.c1 < rhs.c1 || (lhs.c1 == rhs.c1 && lhs.c2 < rhs.c2) || (lhs.c1 == rhs.c1 && lhs.c2 == rhs.c2 && lhs.c3 < rhs.c3);
}

ostream& operator<<(ostream& os, requirement const & r)
{
	os << "C1: " << r.c1 << endl
	   << "C2: " << r.c2 << endl
	   << "C3: " << r.c3 << endl;
	  return os;
}


int main()
{
    unsigned n, c1, c2, c3;
    cin >> n >> c1 >> c2 >> c3;
	
	if(n==0)
	{
		cout << "YES";
		return 0;
	}
	
    vector<unsigned> connections(n);
    partial_sum(istream_iterator<unsigned>{cin}, istream_iterator<unsigned>{}, begin(connections));
	unsigned goal = connections[n-1];
    connections.pop_back();
	vector<bool> impossible (goal +1);
	for(unsigned i: connections) impossible[i] = true;
	
	vector<set<requirement>> dp (goal + 1);
	dp[0].insert({0, 0, 0});
	
	for(unsigned i = 1; i <= goal; ++i)
	{
		if(impossible[i]) continue;
		for(requirement const & r: dp[i-1])
		{
			if(r.c1 < c1) dp[i].insert({r.c1 + 1, r.c2, r.c3});
		}
		if(i > 1)
		{
			for(requirement const & r: dp[i-2])
			{
				if(r.c2 < c2) dp[i].insert({r.c1, r.c2+ 1, r.c3});
			}
		}
		if(i > 2)
		{
			for(requirement const & r: dp[i-3])
			{
				if(r.c3 < c3) dp[i].insert({r.c1, r.c2, r.c3 + 1});
			}
		}
	}
	
	cout << (!dp[goal].empty() ? "YES" : "NO") << endl;
	
	
	
}