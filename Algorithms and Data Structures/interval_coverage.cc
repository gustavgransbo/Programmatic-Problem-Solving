#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/intervalcover
*/

using namespace std;

typedef pair<double, double> interval;
typedef vector<interval>::iterator interval_it;
double a, b, current, longest;
int n;
vector<int> result {};
vector<interval> intervals {};


// cover returns a vector containing the indexes to the 
// intervals in intervals that represent the minimal cover
// of the interval ab. Returns an empty vector if ab can't 
// be covered.
vector<int> cover(interval ab, vector<interval> &intervals)
{
	int n = intervals.size();
	//Base case
	if(n == 0) return vector<int>();

	vector<int> indexes(n);
	iota(begin(indexes), end(indexes), 0);
	// O(nlogn)
	sort(begin(indexes), end(indexes),
			[&intervals](int first, int second)
			{return intervals[first].first < intervals[second].first;});
	vector<int> res{};
	
	double current = ab.first;
	int candidate = -1;
	double reach = numeric_limits<double>::lowest();
	
	// Loop across intervals untill we reach past the end of ab
	// or untill we reach the end.
	for(int i = 0; i < n && reach < ab.second; ++i)
	{
		// Look at the reach of all intervals with a starting point
		// befor the current reach. Add the one with the best reach
		// when we have looked through all.
		if(intervals[indexes[i]].first <= current){
			if(intervals[indexes[i]].second >= reach)
			{
				reach = intervals[indexes[i]].second;
				candidate = indexes[i];
			}
		}
		else if(reach > current)
		{
			res.push_back(candidate);
			current = reach;
			--i;
		}
		else break;
	}
	if(current <= reach ) res.push_back(candidate);
	if(reach >= ab.second) return res;
	else return vector<int>();
}	


// main is responsible for I/O and formating the indata.
int main()
{
	while(scanf("%lf", &a) == 1)
	{
		scanf("%lf", &b);
		scanf("%d", &n);
		vector<interval> intervals(n);
		interval goal = make_pair(a, b);
		for(int i = 0; i< n; ++i)
		{
			scanf("%lf", &a);
			scanf("%lf", &b);
			intervals[i] = make_pair(a, b);
		}
		result = cover(goal, intervals);
		if(!result.empty()){
			printf("%lu\n", result.size());
			for_each(begin(result), end(result), [](int i){printf("%d ", i);});
		}else printf("impossible");
		printf("\n");
	}
}