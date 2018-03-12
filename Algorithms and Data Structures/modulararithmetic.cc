#include <iostream>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/modulararithmetic
*/

using namespace std;

long long gcd(long long const & a, long long const & b, long long & x, long long & y)
{
	if(a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}
	long long x1, y1;
	long long res = gcd(b%a, a, x1, y1);
	
	x = y1 -(b/a) * x1;
	y = x1;
	
	return res;
}

long long modular_multiplication(long long & a, long long & b, long long const &n)
{	
	if(a >= n) a%= n;
	if(b >= n) b%= n;
	long long msp; // Will hold the most significant part of product
	long double A = a;
	msp = A * b / n; // Operations on float will not overflow, instead it will discard least siginificant bits.
	long long result = static_cast<long long>(a * b - msp * n)%n;
	return result >= 0 ? result : result + n;  
}

long long modular_division (long long & a, long long const & b, long long const &n)
{
	long long x, y;
	if(gcd(b, n, x, y) != 1) return -1;
	else return modular_multiplication(a, x, n);
}

long long modular_addition(long long const & a, long long const & b, long long const &n)
{
	return (a % n + b % n) % n;
}

long long modular_subtraction(long long const & a, long long const & b, long long const &n)
{
	long long res = (a % n - b % n) % n;
	return res >= 0 ? res : res + n;
}

int main()
{
	long long n, x, y;
	unsigned t;
	char op;
	cin >> n >> t;
	while(n || t)
	{
		while(t--)
		{
			cin >> x >> op >> y;
			if(op == '*') cout << modular_multiplication(x, y, n) << endl;
			else if(op == '+') cout << modular_addition(x, y, n) << endl;
			else if(op == '-') cout << modular_subtraction(x, y, n) << endl;
			else cout << modular_division(x, y, n) << endl;
		}
		cin >> n >> t;
	}
	
}