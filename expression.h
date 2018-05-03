#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <vector>
#include <fstream>
#include <iostream>
#include "polynomial.h"

using namespace std;

enum ERRORS{LIST_FULL, FUNCTION_NOT_FOUND, CANNOT_OPEN_FILE};

class Expression
{
public:
    Expression();
    ~Expression();

    //getter/setter
    void set(char& which, const Polynomial& what);

    //file io
    void load(string fileName);
    void save(string fileName);

    //overloaded operators
    Expression operator<<(string& expr);    //insertion operator
    Polynomial operator[](char& which);   //return an expression

private:
    vector<Polynomial> list;
    const int MAX_LIST_SIZE = 26;
};





#endif // EXPRESSION_H
