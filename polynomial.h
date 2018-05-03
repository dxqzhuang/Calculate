#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include "term.h"
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include "term.h"

using namespace std;

class Polynomial
{
public:
    Polynomial();
    ~Polynomial();
    Polynomial(const Polynomial &p);
    Polynomial(string expr);
    Polynomial& operator=(const Polynomial &p);
    Polynomial differentiate(int n=1);
    void enableUnicode(bool choice);   //set unicodeEnabled to true/false
    string toString();

    Fraction operator()(Fraction x);

    friend Polynomial operator+(const Polynomial& a, const Polynomial &b);
    friend Polynomial operator-(const Polynomial& a, const Polynomial &b);
    friend Polynomial operator*(const Polynomial& a, const Polynomial &b);
    friend Polynomial operator-(const Polynomial& other);   //negation operator
    friend ostream& operator<<(ostream& out, const Polynomial &p);
    friend istream& operator>>(istream& in, Polynomial &p);

private:
    vector<Term> poly;  //vector of terms
    bool unicodeEnabled = false;
    void copy(const Polynomial& p);
    void deleteAll();
    void order();
    void combineLikeTerms();
    bool compare(const Term &x, const Term &y);
    void reduce();
    void beautify(string& term);
};

#endif // POLYNOMIAL_H
