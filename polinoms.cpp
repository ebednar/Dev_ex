#include <iostream>
#include <vector>

using namespace std;

bool IsPalindrom(string str)
{
	int i;
	int j;

	i = 0;
	j = str.length() - 1;
	while (j >= i)
	{
		if (str[i] != str [j])
			return false;
		i++;
		j--;
	}
	return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength)
{
	vector<string> polinoms;

	for (auto i : words)
		if (IsPalindrom(i) && i.length() >= minLength)
			polinoms.push_back(i);
	return polinoms;
}
