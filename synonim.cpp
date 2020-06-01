#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main()
{
	int q,i;
	string command;
	set<set<string>> syn;
	string word1, word2;
	map<string, int> count;
	i = 0;
	cin >> q;
	while(i++ < q)
	{
		cin >> command;
		if (command == "ADD")
		{		
			cin >> word1 >> word2;
			set<string> tmp;
			tmp.insert(word1);
			tmp.insert(word2);
			if (syn.count(tmp))
				continue;	
			syn.insert(tmp);
			count[word1] += 1;
			count[word2] += 1;
		}
		else if (command == "COUNT")
		{
			cin >> word1;
			cout << count[word1] << endl;
		}
		else if (command == "CHECK")
		{
			cin >> word1 >> word2;
			set<string> tmp;
			tmp.insert(word1);
			tmp.insert(word2);
			if (syn.count(tmp))
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
		}
	}
	return 0;
}