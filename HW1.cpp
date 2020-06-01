// Convert this program to C++
// change to C++ io
// change to one line comments
// change defines of constants to const
// change array to vector<>
// inline any short function

#include <iostream>
#include <vector>
const int nb = 40;

using namespace std;

template <class sumable>
inline void sum(sumable& p, sumable n, vector<int>& d)
{
	p = 0;
	for(int i = 0; i < n; ++i)
		p = p + d[i];
}

int main()
{
	int accum = 0;
	vector<int> data(nb);
	for(int i = 0; i < nb; ++i)
		data[i] = i;
	sum(accum, nb, data);
	cout << "sum is " << accum << endl;
	return 0;
}