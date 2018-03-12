#include <iostream>
#include "sieve.h"

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/primesieve
*/

using namespace std;

int main()
{
    long long n, x;
    unsigned q;
    scanf("%lld", &n);
    scanf("%u", &q);
    printf("%lu\n", sieve(n));
    while(q--)
    {
        scanf("%lld", &x);
        printf("%d\n", is_prime(x));
    }
}