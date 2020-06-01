#include <map>
#include <iostream>

using namespace std;

class Person {
public:
	void ChangeFirstName(int year, const string& first_name) {
		history[year][0] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		history[year][1] = last_name;
	}
	string GetFullName(int year) 
	{
		if (year < history.begin()->first)
			return ("Incognito");
		string str1 = "";
		for (auto s : history)
		{
			if (s.first > year)
				break;
			if (str1 != s.second[0] && s.second[0] != "")
				str1 = s.second[0];
		}
		string str2 = "";
		for (auto s : history)
		{
			if (s.first > year)
				break;
			if (str2 != s.second[1] && s.second[1] != "")
				str2 = s.second[1];
		}
		if (str1 == "")
			return (str2 + " with unknown first name");
		else if (str2 == "")
			return (str1 + " with unknown last name");
		else
			return (str1 + ' ' + str2);
	}
private:
	map<int, string[2]> history;
};


