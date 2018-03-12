#include <vector>

using namespace std;

template <typename T, class ForwardIt>
class Fenwick_tree
{
public:
	Fenwick_tree(ForwardIt it, unsigned n)
	{
		this->n = n;
		v.assign(n+1, 0);
		for(unsigned i = 1; i <= n; ++i)
		{
			add(i, *it);
			++it;
		}
	}
	Fenwick_tree(unsigned n)
	{
		this->n = n;
		v.assign(n+1, 0);
	}
	
	//Adds delta to v[i]. Updates affected nodes.
	void add(unsigned i, T delta)
	{
		i++;
		while(i <= n)
		{
			v[i] += delta;
			i += i & (-i);
		}
	}
	
	//Returns sum of v[0] + v[1] + ... + v[i-1]
	T sum(unsigned i)
	{
		T res {};
		i++;
		while(i>0)
		{
			res += v[i];
			i -= i & (-i);
		}
		return res;
	}
	
private:
	vector<T> v;
	unsigned n;
};