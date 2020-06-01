#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

struct Date
{
	int year = 0, month = 0, day = 0;
	bool operator<(const Date& other) const
	{
		if (year < other.year)
			return true;
		if (year == other.year)
		{
			if (month < other.month)
				return true;
			if (month == other.month)
				if (day < other.day)
					return true;
		}
		return false;
	}
	bool operator==(const Date& other) const
	{
		if (year == other.year && month == other.month && day == other.day)
			return true;
		return false;
	}
};

ostream& operator<<(ostream& out, const Date& d)
{
	cout << setfill('0');
	out << setw(4) << d.year << '-' << setw(2) << d.month << '-' << setw(2) << d.day;
	return out;
}

class Database
{
private:
	map<Date, set<string>> data;
public:
	void AddEvent(const Date& d, const string& event);
	void Print() const;
	void Find(const Date& d) const;
	int DeleteDate(const Date& d);
	bool DeleteEvent(const Date& d, const string& event);
};

void Database::AddEvent(const Date& d, const string& event)
{
	if (!data[d].count(event))
		data[d].insert(event);
}

void Database::Print() const
{
	for (auto i : data)
		for (auto j : i.second)
			cout << i.first << ' ' << j << endl;
}

void Database::Find(const Date& d) const
{
	try
	{
		if (data.count(d))
			for (auto i : data.at(d))
				cout << i << endl;
	}
	catch (out_of_range& e) {}
}

int Database::DeleteDate(const Date& d)
{
	int n = 0;
	try
	{
		if (data.count(d))
		{
			for (auto i : data.at(d))
				n++;
			data.erase(d);
		}
	}
	catch (out_of_range& e) {}
	return n;
}

bool Database::DeleteEvent(const Date& d, const string& event)
{
	if (data.count(d))
	{
		for (auto i : data[d])
		{
			if (i == event)
			{
				data[d].erase(i);
				return (true);
			}
		}
	}
	return false;
}

void is_valid(const Date& d, const char c1, const char c2, const string& date)
{
	if (c1 != '-' || c2 != '-')
	{
		cout << "Wrong date format: " + date << endl;
		exit(1);
	}
	if (d.month < 1 || d.month > 12)
	{
		cout << "Month value is invalid: " + to_string(d.month) << endl;
		exit(1);
	}
	if (d.day < 1 || d.day > 31)
	{
		cout << "Day value is invalid: " + to_string(d.day) << endl;
		exit(1);
	}
}

int main()
{
	Database db;
	Date d;
	string command;
	while (getline(cin, command))
	{
		if (command.length() == 0)
			continue;
		string action, date, event;
		char c1, c2;
		int old_pos = 0;
		int pos = command.find(' ', old_pos);
		action.assign(command, old_pos, pos - old_pos);
		if (action != "Print" && action != "Find" && action != "Del" && action != "Add")
		{
			cout << "Unknown command: " << action << endl;
			exit (1);
		}
		old_pos = pos + 1;
		if (action == "Print")
		{
			db.Print();
			continue;
		}
		if (pos == -1)
		{
			cout << "Wrong date format: " << endl;
			exit(1);
		}
		pos = command.find(' ', old_pos);
		date.assign(command, old_pos, pos - old_pos);
		old_pos = pos + 1;
		istringstream stream(date);
		stream >> d.year >> c1 >> d.month >> c2 >> d.day;
		if (!stream.eof() || stream.fail())
		{
			cout << "Wrong date format: " << date << endl;
			exit(1);
		}
		is_valid(d, c1, c2, date);
		if (action == "Find")
		{
			db.Find(d);
			continue;
		}
		if (action == "Del" && pos == -1)
		{
			cout << "Deleted " << db.DeleteDate(d) << " events" << endl;
			continue;
		}
		pos = command.length();
		event.assign(command, old_pos, pos - old_pos);
		old_pos = pos + 1;
		if (action == "Add")
		{
			db.AddEvent(d, event);
			continue;
		}
		if (action == "Del")
		{
			if (db.DeleteEvent(d, event))
				cout << "Deleted successfully" << endl;
			else
				cout << "Event not found" << endl;
			continue;
		}
	}
	return 0;
}