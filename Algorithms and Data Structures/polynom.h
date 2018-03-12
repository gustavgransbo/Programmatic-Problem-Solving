#include <vector>
#include <complex>
#include <cmath>

#define M_PI 3.14159265358979323846

using namespace std;

typedef complex<double> Complex;

// Struct used to iterate from index i.i incrementing with i.steps for each step
struct IndexIterator
{
	unsigned i;
	unsigned steps;
	
	void operator++(){
		i += steps;
	}

};

// Convert polynom from coefficient representation to point representation.
// Polynom needs to be padded with zeros so that it's length is a power of 2.
// Inverse transform by calling with inverse = true 
vector<Complex> fft(vector<Complex> const &coef, unsigned const &n, bool invert = false, IndexIterator i = {0,1})
{
	if(n==1)
	{
		return {coef[i.i]};
	}
	vector<Complex> res(n);
	vector<Complex> even = fft(coef, ceil(double(n)/2), invert, {i.i, i.steps*2});
	vector<Complex> odd = fft(coef,ceil(double(n)/2), invert, {i.i+i.steps, i.steps*2});
	
	for(unsigned k = 0; k < n/2; ++k)
	{
		Complex w = polar(1.0, (invert ? 1 : -1) * 2.0 * M_PI * k/n);
		res[k] = even[k] + w*odd[k];
		res[k+n/2] = even[k] - w*odd[k];
		if(invert)
		{
			res[k] /= 2;
			res[k+n/2] /= 2;
		}
	}
	
	return res;
}
