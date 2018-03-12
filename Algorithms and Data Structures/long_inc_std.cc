#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include "long_inc_std.h"

/*
* Gustav Gränsbo, gusgr644
* https://open.kattis.com/problems/longincsubseq
*/

const int N = 100000;

using namespace std;



int main()
{
	unsigned int n;
	long long v[N];
	
	while(scanf("%u", &n) == 1)
	{
		for(unsigned int i = 0; i < n; ++i)
		{
			scanf("%lld", &v[i]);
		}
		if(n != 0)
		{			
			vector<unsigned int> res = longincsubseq<N>(begin(v), n);
			printf("%lu\n", res.size());
			for_each(begin(res), end(res), [](unsigned int i){printf("%u ", i);});
		}else printf("%d", 0);
		
		printf("\n");
	}
}