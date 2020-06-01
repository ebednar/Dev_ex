#include <iostream>
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
    }
    int Numerator() const {
		return numerator;
    }
    int Denominator() const {
		return denominator;
    }
private:
	int numerator, denominator;
};
