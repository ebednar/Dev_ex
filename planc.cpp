#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	int q, i, j, m;
	vector<vector<string>> plans(31);
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	string command, s;

	cin >> q;
	j = 0;
	m = 0;
	while (j < q)
	{
		cin >> command;
		if (command == "ADD")
		{
			cin >> i >> s;
			plans[i - 1].push_back(s);
		}
		else if (command == "DUMP")
		{
			cin >> i;
			cout << plans[i - 1].size() << ' ';
			vector<string>& ptr = plans[i - 1];
			for(vector<string>::iterator it = ptr.begin(); it != ptr.end(); it++)
			{
				cout << *it;
				if (it != ptr.end() - 1)
					cout << ' ';
			}
			cout << endl;
		}
		else if (command == "NEXT")
		{
			int tmp = m;
			m++;
			m %= 12;
			if (days[tmp] > days[m])
			{
				for(int k = days[m]; k < days[tmp]; k++)
				{
					for (auto l : plans[k])
					{
						plans[days[m] - 1].push_back(l);
					}
				}
			}
			plans.resize(days[m]);
		}
		j++;
	}
}
