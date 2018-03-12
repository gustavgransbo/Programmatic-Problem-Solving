#include <iostream>
#include <iterator>
#include "polynom.h"

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/polymul2
*
* Algorithm used: Fast Fourier Tranform, FFT
*/ 


using namespace std;

int main()
{
	unsigned cases, deg_a, deg_b;
	double real;
	scanf("%u", &cases);
	while(cases--)
	{
		unsigned n=1;
		scanf("%u", &deg_a);
		vector<Complex> a (deg_a+1);
		for(unsigned i = 0; i<= deg_a; ++i)
		{
			scanf("%lf", &real);
			a[i] = {real, 0};
		}
		scanf("%u", &deg_b);
		
		unsigned max_deg = deg_a > deg_b ? deg_a : deg_b;
		while(n < max_deg + 1) n<<=1; // n should be a power of 2, atleast twice as large as max(deg_a, deg_b) + 1
		n <<= 1;
		vector<Complex> b (n);
		for(unsigned i = 0; i<= deg_b; ++i)
		{
			scanf("%lf", &real);
			b[i] = real;
		}
		// Pad a with zeros.
		a.resize(n);
		
		// Transform a and b into point representation.
		vector<Complex> A = fft(a, n);
		vector<Complex> B = fft(b, n);
		
		// Multiply A and B
		vector<Complex> multiplied (n);
		for(unsigned i = 0; i < n; ++i) multiplied[i] = A[i] * B[i];
			
		// Inverse transform A*B
		vector<Complex> res = fft(multiplied, n, true);
		
		// Check for uneccesary padding.
		unsigned padding = n;
		for(unsigned i = n-1; i > 0 && round(res[i].real()) == 0; --i)
		{
			padding = i;
		}
		
		// Print results
		printf("%u\n", padding-1);
		for(unsigned i = 0; i < padding; ++i) printf("%d ", int(round(res[i].real())));
		printf("\n");
		
	}
}