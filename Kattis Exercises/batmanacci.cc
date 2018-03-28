#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/batmanacci
*/

using namespace std;

const unsigned long long MAX = 1000000000000000000;

char find_char(vector<unsigned long long> const & fib, unsigned n, unsigned long long k)
{
	if(n < 2){
		return n == 0 ? 'N' : 'A';
	}
	else if(k <= fib[n-2]) return find_char(fib, n-2, k);
	else return find_char(fib, n-1, k - fib[n-2]); 
}

int main()
{
	unsigned N;
	unsigned long long K;
	cin >> N >> K;
	vector<unsigned long long> fib (max<unsigned long long>(N, 2));
	fib[0] = fib[1] = 1;
	for(unsigned i = 2; i < N; ++i)
	{
		fib[i] = fib[i-2] + fib[i-1];
		if(fib[i] > MAX) fib[i] = MAX;
	}
	cout << find_char(fib, N-1, K);
}

