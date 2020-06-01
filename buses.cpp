#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int q, i, count;
	map<string, vector<string>> busMap;
	map<string, vector<string>> stopMap;
	string command, bus, stop;

	cin >> q;
	i = 0;
	while (i++ < q)
	{
		cin >> command;
		if (command == "NEW_BUS")
		{
			cin >> bus >> count;
			int j = 0;
			while (j++ < count)
			{
				cin >> stop;
				busMap[bus].push_back(stop);
				stopMap[stop].push_back(bus);
			}		
		}
		else if (command == "BUSES_FOR_STOP")
		{
			cin >> stop;
			if (stopMap.count(stop))
				for (string s : stopMap[stop])
						cout << s << ' ';
			else
				cout << "No stop";
			cout << endl;
		}
		else if (command == "STOPS_FOR_BUS")
		{
			cin >> bus;
			if (!busMap.count(bus))
			{
				cout << "No bus" << endl;
				continue;
			}
			for (string s : busMap[bus])
			{
				cout << "Stop " << s << ':';
				if (stopMap[s].size() == 1)
				{
					cout << " no interchange" << endl;
					continue;
				}
				for (string b : stopMap[s])
					if (b != bus)
						cout << ' ' << b;
				cout << endl;
			}
		}
		else if (command == "ALL_BUSES")
		{
			if (busMap.size() == 0)
			{
				cout << "No buses" << endl;
				continue;
			}
			for (auto m : busMap)
			{
				cout << "Bus " << m.first << ':';
				for (string s : m.second)
					cout << ' ' << s;
				cout << endl;
			}
		}
	}
	return 0;
}
