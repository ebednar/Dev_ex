#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool strSort(string str1, string str2)
{
	for(char& c : str1)
	{
		c = tolower(c);
	}
	for(char& c : str2)
		c = tolower(c);
	return (str1 < str2);
}

int main()
{
	int n, i;
	vector<string> mas;

	cin >> n;
	i = 0;
	while (i++ < n)
	{
		string a;
		cin >> a;
		mas.push_back(a);
	}
	sort(begin(mas), end(mas), strSort);
	for (const auto& j : mas)
		cout << j << ' ';
	cout << endl;
	return 0;
}
