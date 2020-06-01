#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Person {
public:
	Person(const string& first_name, const string& last_name, int year){
		history[year][0] = first_name;
		history[year][1] = last_name;
	};
	void ChangeFirstName(int year, const string& first_name) {
		if (year < history.begin()->first)
			return ;
		history[year][0] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		if (year < history.begin()->first)
			return ;
		history[year][1] = last_name;
	}
	string GetFullNameWithHistory(int year) const
	{
		if (year < history.begin()->first)
			return ("No person");
		vector<string> str1;

			for (auto s : history)
			{
				if (s.first > year)
					break;
				if ((!str1.size() || str1.back() != s.second[0]) && s.second[0] != "")
					str1.push_back(s.second[0]);
	//			cout << "check " << s.first << " : " << s.second[0];
			}
		vector<string> str2;

			for (auto s : history)
			{
				if (s.first > year)
					break;
				if ((!str2.size() || str2.back() != s.second[1]) && s.second[1] != "")
					str2.push_back(s.second[1]);
			}
		//cout << year << " test3 " << str1.size() << " : " << str2.size() << endl;
		string result;
		if (!str1.size())
		{
			result = str2.back();
			if (str2.size() == 2)
				result += " (" + str2[str2.size() - 2];
			else
				for (int i = (int)str2.size() - 2; i > -1 ; i--)
				{
					result += str2[i];
					if (i < (int)str2.size() - 2)
						result += ", ";
				}
			if (str2.size() > 1)
				result += ")";
			result += " with unknown first name";
			return result;
		}
		else if (!str2.size())
		{
			result = str1.back();
			if (str1.size() == 2)
				result += " (" + str1[str1.size() - 2];
			else
				for (int i = (int)str1.size() - 2; i > - 1; i--)
				{
					result += str1[i];
					if (i < (int)str1.size() - 2)
						result += ", ";
				}
			if (str1.size() > 1)
				result += ")";
			result += " with unknown last name";
			return result;
		}
		else
		{
			result = str1.back();
			if (str1.size() >= 2)
				result += " (" + str1[str1.size() - 2];
			if (str1.size() > 2)
				for (int i = (int)str1.size() - 3; i > -1; i--)
				{
					result += ", ";
					result += str1[i];
				}
			if (str1.size() > 1)
				result += ")";
			result += ' ' + str2.back();
			if (str2.size() >= 2)
				result += " (" + str2[str2.size() - 2];
			if (str2.size() > 2)
				for (int i = (int)str2.size() - 3; i > -1; i--)
				{
					result += ", ";
					result += str2[i];
				}
			if (str2.size() > 1)
				result += ")";
			return result;
		}
	}
	string GetFullName(int year) const
	{
		if (year < history.begin()->first)
			return ("No person");
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


