#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include <exception>

#define all(c) c.begin(), c.end()
#define EPS 1E-7

using namespace std;

class Rational {
public:
    Rational(int new_numerator = 0, int new_denominator = 1) {
        this->numerator = new_numerator;
        this->denominator = new_denominator;

        if (this->denominator == 0)
            throw invalid_argument("Denominator = 0");

        if (this->numerator == 0)
            this->denominator = 1;

        if (denominator < 0) {
            this->numerator *= -1;
            this->denominator *= -1;
        }

        Reduce();
    }

    int Numerator() const {
        return this->numerator;
    }

    int Denominator() const {
        return this->denominator;
    }

    Rational invert() const {
        return Rational(this->denominator, this->numerator);
    }

private:
    int numerator;
    int denominator;

    int GCD(int a, int b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    int LCM(int a, int b) {
        return a * b / GCD(a, b);
    }

    void Reduce() {
        int gcd = GCD(abs(this->numerator), abs(this->denominator));

        this->numerator   /= gcd;
        this->denominator /= gcd;

        return;
    }
};

bool operator == (const Rational& lhs, const Rational& rhs) {
    return ((lhs.Numerator()   == rhs.Numerator()  ) &&
            (lhs.Denominator() == rhs.Denominator()));
}

bool operator != (const Rational& lhs, const Rational& rhs) {
    return (!(lhs == rhs));
}

bool operator < (const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator());
}

bool operator > (const Rational& lhs, const Rational& rhs) {
    return (lhs.Numerator() * rhs.Denominator() > rhs.Numerator() * lhs.Denominator());
}

Rational operator + (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator - (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator * (const Rational& lhs, const Rational& rhs) {
    return Rational(lhs.Numerator() * rhs.Numerator(), lhs.Denominator() * rhs.Denominator());
}

Rational operator / (const Rational& lhs, const Rational& rhs) {
    if (rhs.Numerator() == 0)
        throw domain_error("Division by zero");
    return lhs * rhs.invert();
}

ostream& operator << (ostream& stream, const Rational& rational) {
    stream << rational.Numerator() << "/" << rational.Denominator();
    return stream;
}

istream& operator >> (istream& is, Rational& r) {
  int n, d;
  char c;
  is >> n >> c >> d;
  if (is && c == '/') {
    r = Rational(n, d);
  }
  return is;
}

int main() {
//    freopen( "input.txt", "r+", stdin );
//    freopen("output.txt", "w+", stdout);

    try {
        Rational r1, r2, r3;
        char c = ' ', pass1 = ' ', pass2 = ' ';
        cin >> r1;
//        cerr << "r1 = " << r1 << endl;
//        cin >> pass1;
        cin >> c;
//        cin >> pass2;
//        cerr << "ATTENTION: " << "c1 = |" << pass1 << "|, c2 = |" << c << "|, c3 = |" << pass2 << "|" << endl;
//        string s = "";
//        cin >> s;
//        cerr << "s = " << s << endl;
       cin >> r2;
//        cerr << "r2 = " << r2 << endl;

        if (c == '+')
            r3 = r1 + r2;
        if (c == '-')
            r3 = r1 - r2;
        if (c == '*')
            r3 = r1 * r2;
        if (c == '/')
            r3 = r1 / r2;

//        cerr << "r3 = ";
        cout << r3;
    } catch (invalid_argument&) {
        cout << "Invalid argument";
    } catch (domain_error&) {
        cout << "Division by zero";
    }

    fclose(stdin);
    fclose(stdout);

    return 0;
}
