/*
* Gustav Gränsbo, gusgr644
*/


#include <vector>

using namespace std;

/*
* Returns indexes of longest increasing subsequence.
* Complexity is O(nlogn)
*/
template<unsigned int N, typename T_it>
vector<unsigned int> longincsubseq(T_it v, unsigned int n)
{
	unsigned int L[N]; // L[k] is the index of the end element of sequence with k+1 elements.
	unsigned int P[N]; // P[k] is the previous index in the longest subsequence that ends at index k. 
	
	L[0] = 0;
	unsigned int longest = 1;
	
	
	/*
	* Loop over all elements of v.
	*/
	for(T_it it = v; it != v + n; ++it)
	{
		//We found a new smallest element.
		if(*it <= *(v+L[0]))
		{
			if(*it < *(v+L[0])) L[0] = it - v;
		}
		//We found an element that can increase the longest sequence.
		else if(*it > *(v+L[longest-1]))
		{
			P[it-v] = L[longest - 1];
			L[longest++] = it - v;
		}
		//Binary search for the longest sequence whos last element is larger than current element.
		else
		{
				
			unsigned int l = 1;
			unsigned int r = longest;
			unsigned int m;
			while(l <= r)
			{
				m = ceil((l+r)/2);
				
				if(*(v+L[m]) < *it)
				{
					l = m + 1;
				}
				else
				{
					r = m - 1;
				}
			}
			P[it-v] = L[l-1];
			L[l] = it - v;
		}
	}
	
	//Backtrack to find indexes on longest sequence.
	vector<unsigned int> res(longest);
	int k = L[longest-1];
	for(int i = longest-1; i >= 0; --i)
	{
		res[i] = k;
		k = P[k];
	}
	
	return res;
	
}
