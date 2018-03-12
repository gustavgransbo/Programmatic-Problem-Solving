#include <iostream>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/rationalarithmetic
*/

using namespace std;


template<typename T>
T find_gcd(T const & a, T const & b)
{
	if(b == 0) return a;
	else return find_gcd(b, a%b);
}

template<typename T>
class Rational
{
public:
	Rational(T const & numerator_, T const & denominator_):
		numerator{numerator_}, denominator{denominator_}{}

	T numerator;
	T denominator;
	
	void normalize()
	{
		T gcd = find_gcd(numerator, denominator);
		while(gcd != 1)
		{
			numerator /= gcd;
			denominator /= gcd;
			gcd = find_gcd(numerator, denominator);
		}
		if(denominator < 0)
		{
			numerator *= -1;
			denominator *= -1;
		}
	}
	
	friend Rational operator+(Rational lhs, Rational const & rhs)
	{
		T  gcd = find_gcd(lhs.denominator, rhs.denominator);
		lhs.numerator *= rhs.denominator / gcd;
		lhs.numerator += rhs.numerator * lhs.denominator / gcd;
		lhs.denominator *= rhs.denominator / gcd;
		lhs.normalize();
		
		return lhs;
	}
	
	friend Rational operator-(Rational lhs, Rational rhs)
	{
		rhs.numerator *= -1;
		return lhs + rhs;
	}
	
	friend Rational operator*(Rational lhs, Rational const & rhs)
	{
		lhs.numerator *= rhs.numerator;
		lhs.denominator *= rhs.denominator;
		lhs.normalize();
		return lhs;
	}
	
	friend Rational operator/(Rational lhs, Rational rhs)
	{
		T temp = rhs.numerator;
		rhs.numerator = rhs.denominator;
		rhs.denominator = temp;
		return lhs * rhs;
	}

};


template<typename T>
ostream & operator<<(ostream & os, Rational<T> r)
{
	os << r.numerator << " / " << r.denominator;
	return os;
}

int main()
{
	unsigned n;
	long x1, y1, x2, y2;
	char op;
	cin >> n;
	while(n--)
	{
		cin >> x1 >> y1 >> op >> x2 >> y2;
		if(op == '+') cout << (Rational<long>(x1, y1) + Rational<long>(x2, y2)) << endl;
		if(op == '-') cout << (Rational<long>(x1, y1) - Rational<long>(x2, y2)) << endl;
		if(op == '*') cout << (Rational<long>(x1, y1) * Rational<long>(x2, y2)) << endl;
		if(op == '/') cout << (Rational<long>(x1, y1) / Rational<long>(x2, y2)) << endl;
	
	}
}