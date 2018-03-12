#include <bitset>
#include <vector>
#include <cmath>

using namespace std;

const unsigned MAX_SIZE = 100000010;
bitset<MAX_SIZE> bits;
unsigned n_primes {};
vector<int> primes;

int sieve_size;

unsigned sieve(long long upper_bound)
{
    sieve_size = upper_bound+1;
    bits.reset();
    bits.flip();
    bits.set(0, false);
    bits.set(1, false);
    
    for(long long i = 2; i<=sieve_size; ++i)
    {
        if(bits.test(static_cast<size_t>(i)))
        {
            for(long long j = i*i; j<=sieve_size; j+=i)
            {
                bits.set(static_cast<size_t>(j), false);
            }
			// Uncomment to store each prime
			//primes.push_back(static_cast<int>(i));
            ++n_primes;
        }
    }
    return n_primes;
}

bool is_prime(long long n)
{
    if(n < sieve_size) return bits.test(static_cast<size_t>(n));
	
	// To handle n larger than sieve_size, primes should be stored and used here.
    /*for(auto it = begin(primes); it != end(primes); ++it)
    {
        if(n%(*it) == 0) return false;
        if(*it > sqrt(n)) break;
    }*/
    return true;
}