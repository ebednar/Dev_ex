#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	int q, i, j, w_count;
	vector<bool> queue;
	string command;

	cin >> q;
	j = 0;
	while (j < q)
	{
		cin >> command;
		w_count = 0;
		if (command == "COME")
		{
			cin >> i;
			if (i >= 0)
				for (int k = 0; k < i; k++)
					queue.push_back(false);
			else
				for (int k = 0; k < -i; k++)
					queue.pop_back();
		}
		else if (command == "WORRY")
		{
			cin >> i;
			queue[i] = true;
		}
		else if (command == "QUIET")
		{
			cin >> i;
			queue[i] = false;
		}
		else if (command == "WORRY_COUNT")
		{
			for (bool k : queue)
				if (k == true)
					w_count++;
			cout << w_count << endl;
		}
		j++;
	}
}
