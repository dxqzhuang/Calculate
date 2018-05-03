#ifndef TERM_H
#define TERM_H
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>
#include "fraction.h"
#include "term_error.h"

using namespace std;


class Term
{
    /**
    @example (2/1)x^(2/3)
    @brief Base class of TermExpr and TermVal

    */
public:
    Term(Fraction c = Fraction(0,1), Fraction p = Fraction(0,1));
    ~Term();
    Term(const Term &other);
    Fraction getPower() const;
    Fraction getCoeff() const;
    void set(Fraction c = 1, Fraction p = 0);
    string toString(bool super);
    void enableUnicode(bool choice);
    //-!!!!
    Fraction& operator()(const Fraction& x);    //evaluation operator
    Term differentiate();

    //======operators=========
    Term& operator=(const Term &other);
    Term& operator+=(const Term &other);
    Term& operator*=(double x);
    bool operator<(const Term &other);
    bool operator<=(const Term& other);
    bool operator==(const Term& other);
    bool operator!=(const Term& other);
    bool operator>=(const Term& other);
    bool operator>(const Term& other);
    Term operator+(const Term& other);
    Term operator-(const Term& other);
    Term operator*(const Term& other)const;
    Term operator-() const;   //negate operator

    friend ostream& operator<<(ostream& out, const Term &t);
    friend istream& operator>>(istream& in, Term &t);

protected:
    Fraction coeff, power;  //default 1x^1
    bool unicodeEnabled = false; //if true, display superscript instead of "^"
    string superScript(Fraction n) const;
    void copy(const Term &other);
    void deleteMe();
};

#endif // TERM_H
