#include <vector>

using namespace std;

/*
* Help function that returns an array with the indexes 
* to chosen items for the optimal solution.
*/

template<unsigned int N, unsigned int C>
vector<unsigned int> get_items(unsigned int (&weight)[N], unsigned int (&item)[N+1][C+1], unsigned int n, unsigned int capacity)
{
	unsigned int cur_capacity = capacity;
	vector<unsigned int> indexes {};
	for(unsigned int i = n; i > 0; --i)
	{
		if(item[i][cur_capacity] == 1){
			indexes.push_back(i-1);
			cur_capacity -= weight[i-1];
		}
	}
	return indexes;
}

/*
* DP solution.
* Builds the knap[i][c] array from bottom up. 
* If item is part of the optimal solution with i items and
* capacity c then item[i][c] is set to 1. We are done when
* we have found knap[n][capacity].
*
* Returns a vector with the indexes of the optimal picks.
*/
template<unsigned int N, unsigned int C>
vector<unsigned int> knapsack(unsigned int(&weight)[N], unsigned int (&value)[N], unsigned int (&knap)[N+1][C+1], unsigned int (&item)[N+1][C+1], unsigned int n, unsigned int capacity)
{
	unsigned int i, c;
	unsigned int x, y;
	
	for(c = 0; c <= capacity; ++c) knap[0][c] = 0;
	
	for(i = 1; i <= n; ++i){
		for(c = 0; c <= capacity; ++c)
		{
			if(weight[i-1] > c)
			{
				knap[i][c] = knap[i-1][c];
				item[i][c] = 0;
			}
			else
			{
				x = knap[i-1][c];
				y = knap[i-1][c-weight[i-1]] + value[i-1];
				if(x>=y)
				{
					knap[i][c] = x;
					item[i][c] = 0;
				}
				else
				{
					knap[i][c] = y;
					item[i][c] = 1;
				}
				
			}
		}
	}
	return get_items<N, C>(weight, item, n, capacity);
}