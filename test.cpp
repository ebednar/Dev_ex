#include <iostream>
#include <vector>

using namespace std;

struct s_obj
{
	int *a;
};

int main()
{
	s_obj* ex = new s_obj();
	ex->a = new int[1000];
	ex->a[0] = 14;
	cout << (*(ex->a)) << endl;
	return 0;
}