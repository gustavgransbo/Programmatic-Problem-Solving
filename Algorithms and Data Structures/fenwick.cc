#include <iostream>
#include <vector>
#include "fenwick.h"

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/fenwick
*/

int main()
{
	unsigned N, Q, i;
	char op;
	long delta;
	
	scanf("%u %u", &N, &Q);
	Fenwick_tree<long, long*> ft(N);
	
	while(Q--)
	{
		scanf("%s", &op);
		if(op == '+')
		{
			scanf("%u %ld", &i, &delta);
			ft.add(i, delta);
		}
		else
		{
			scanf("%u", &i);
			printf("%ld\n", ft.sum(i));
		}
	}
	
	
}