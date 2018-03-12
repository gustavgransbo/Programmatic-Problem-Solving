#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include "knapsack.h"

/*
* Gustav Gränsbo, gusgr644
* https://open.kattis.com/problems/knapsack 
*/

using namespace std;

const unsigned int C = 2000;
const unsigned int N = 2000;

/* 
* Global static arrays to avoid passing arguments.
* 
* knap[i][c] is the maximum value we can fill the knapsack
* with only picking from the first i items and with capacity c.
* 
* item[i][c] tells us if item i should be picked when we are allowed
* to pick from the first i items with capacity c. 
*/
unsigned int value[N]; 
unsigned int weight[N];
unsigned int knap[N+1][C+1]; 
unsigned int item[N+1][C+1];
unsigned int n, capacity;

double cf;

/*
* main handles I/O. No array is cleared between cases as they
* are always filled from botom up. Resulting in all relevant values
* beeing overwritten.
*/

int main()
{
	while(scanf("%lf", &cf) == 1)
	{
		capacity = cf;
		scanf("%u", &n);
		for(unsigned int i = 0; i < n; ++i)
		{
			scanf("%u", &value[i]);
			scanf("%u", &weight[i]);
		}
		vector<unsigned int> indexes = knapsack<N, C>(weight, value, knap, item, n, capacity);
		printf("%lu\n", indexes.size());
		for_each(begin(indexes), end(indexes), 
			[](unsigned int i){printf("%d ", i);});
		printf("\n");
	}
	
}
