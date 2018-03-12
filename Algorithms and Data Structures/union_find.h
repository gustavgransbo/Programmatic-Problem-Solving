using namespace std;

struct element
{
	unsigned long long parent;
	unsigned long long ranking; 
};

template<unsigned long long N_max>
unsigned long long find(element (&e)[N_max], unsigned long long i)
{
	if(e[i].parent==i) return i;
	else
	{ 
		e[i].parent = find(e, e[i].parent);
		return e[i].parent;
	}
}

template<unsigned long long N_max>
void Union(element (&e)[N_max], unsigned long long a, unsigned long long b)
{
	unsigned long long a_root = find<N_max>(e, a);
	unsigned long long b_root = find<N_max>(e, b);
	
	if(e[a_root].ranking > e[b_root].ranking)
	{
		e[b_root].parent = a_root;
	}
	else if(e[a_root].ranking < e[b_root].ranking)
	{
		e[a_root].parent = b_root;
	}
	else
	{
		e[b_root].parent = a_root;
		e[a_root].ranking++;
	}
}
