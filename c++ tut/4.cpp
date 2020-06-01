#include <iostream>
#include <sstream>
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
public:
    Rational(int numerator = 0, int denominator = 1) 
	{
		int s = 1;
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
		//cout << this->numerator << ' ' << this->denominator << endl;
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
	Rational operator*(const Rational& a)
	{
		return {numerator * a.numerator, denominator * a.denominator};
	}
	Rational operator/(const Rational& a)
	{
		return {numerator * a.denominator, denominator * a.numerator};
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
private:
	int numerator, denominator;
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
		cout << in.peek() << endl;
		in.ignore(1);
		cout << in.peek() << endl;
		if (!(in >> d))
		{
			cout << in.peek() << endl;
			string str;
			in >> str;
			cout << str << endl;
			return in;
		}
		//if (n != 0 && d != 0)
			a = Rational(n ,d);
		return in;
	}

