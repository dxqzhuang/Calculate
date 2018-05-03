#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <fstream>
#include <iostream>
#include "polynomial.h"

using namespace std;

enum ERRORS{LIST_FULL};

class Expression
{
public:
    Expression();
    ~Expression();

    //file io
    void load(string fileName);
    void save(string fileName);

    //overloaded operators
    Expression operator <<(string& expr);    //insertion operator
    Polynomial operator [](int which);   //return an expression

private:
    vector<Polynomial> list;
    const int MAX_LIST_SIZE = 26;
};





#endif // EXPRESSION_H
