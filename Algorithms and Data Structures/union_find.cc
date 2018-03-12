#include <iostream>
#include "union_find.h"

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/unionfind
*/

using namespace std;

const unsigned N_max = 1000000;

int main()
{
	unsigned N, Q, a, b;
	char op;
	element e[N_max];
	
	scanf("%u", &N);
	scanf("%u", &Q);
	
	for(unsigned i = 0; i < N ; ++i)
	{
		e[i].parent = i;
		e[i].ranking = 0;
	}
	
	while(Q--)
	{
		scanf("%s %u %u", &op, &a, &b);
		if(op == '?') 
			printf("%s\n",(find<N_max>(e, a)==find<N_max>(e, b) ? "yes" : "no"));
		else
			Union(e, a, b);
	}
	
	
	
}