#include <iostream>
#include <sstream>
#include <exception>
using namespace std;

int nod(int new_numerator, int new_denominator)
{
while (new_numerator != 0 && new_denominator != 0) {
		if (new_numerator > new_denominator) {
			new_numerator %= new_denominator;
		}
		else {
			new_denominator %= new_numerator;
		}
	}
	return new_denominator + new_numerator;
}

class Rational {
private:
	int numerator, denominator;
public:
    Rational(int numerator = 0, int denominator = 1) 
	{
		int s = 1;
		if (denominator == 0)
			throw invalid_argument("Invalid argument");
		if (numerator < 0 || denominator < 0)
		{
			if (numerator < 0 && denominator < 0)
				;
			else
				s = -1;
			numerator = abs(numerator);
			denominator = abs(denominator);
		}
		int n = nod(numerator, denominator);
		this->numerator = s * numerator / n;
		this->denominator = denominator / n;
    }
    int Numerator() const {return numerator;}
    int Denominator() const {return denominator;}
	bool operator==(const Rational& a) const
	{
		if (this->numerator == a.numerator && this->denominator == a.denominator)
			return true;
		return false;
	}
	bool operator!=(const Rational& a) const
	{
		if (this->numerator != a.numerator || this->denominator != a.denominator)
			return true;
		return false;
	}
	Rational operator+(const Rational& a)
	{
		Rational b, c;
		b = a;
		c = *this;
		int tmp = b.denominator;
		b.denominator *= c.denominator;
		b.numerator *= c.denominator;
		c.denominator *= tmp;
		c.numerator *= tmp;
		return {c.numerator + b.numerator, b.denominator};
	}
	Rational operator-(const Rational& a)
	{
		Rational b, c;
		b = a;
		c = *this;
		int tmp = b.denominator;
		b.denominator *= c.denominator;
		b.numerator *= c.denominator;
		c.denominator *= tmp;
		c.numerator *= tmp;
		return {c.numerator - b.numerator, b.denominator};
	}
	Rational operator*(const Rational& a)
	{
		return {numerator * a.numerator, denominator * a.denominator};
	}
	Rational operator/(const Rational& a)
	{
		if (a.Numerator() == 0)
			throw domain_error("Division by zero");
		return {numerator * a.denominator, denominator * a.numerator};
	}
};

ostream& operator<<(ostream& out, const Rational& a)
	{
		out << a.Numerator() << '/' << a.Denominator();
		return out;
	}
istream& operator>>(istream& in, Rational& a)
	{
		int n = 0, d = 0;
		if (!(in >> n))
		{
			string str;
			getline(in, str);
			return in;
		}
		if (in.peek() != '/')
		{
			string str;
			in >> str;
			return in;
		}
		in.ignore(1);
		if (!(in >> d))
		{
			string str;
			in >> str;
			return in;
		}
		a = Rational(n ,d);
		return in;
	}

int main() 
{
	Rational r1, r2, r3;
	char c;
	try {
	cin >> r1 >> c >> r2;
	}
	catch (invalid_argument& e) {cout << "Invalid argument" << endl; exit(1);}
	if (c == '+')
		r3 = r1 + r2;
	else if (c == '-')
		r3 = r1 - r2;
	else if (c == '*')
		r3 = r1 * r2;
	else if (c == '/')
	{
		try {
			r3 = r1 / r2;
		}
		catch (domain_error& e) {cout << "Division by zero" << endl; exit(1);}
	}
	cout << r3 << endl;
    return 0;
}