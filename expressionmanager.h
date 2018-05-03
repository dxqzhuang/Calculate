#ifndef EXPRESSIONMANAGER_H
#define EXPRESSIONMANAGER_H

#include <vector>
#include <fstream>
#include <iostream>
#include "polynomial.h"

using namespace std;

enum ERRORS{LIST_FULL};

class ExpressionManager
{
public:
    ExpressionManager();
    ~ExpressionManager();

    //file io
    void load(string fileName);
    void save(string fileName);

    //overloaded operators
    ExpressionManager operator << (string& expr);    //insertion operator
    Polynomial operator[] (int);   //return an expression

private:
    vector<Polynomial> list;
    const int MAX_LIST_SIZE = 26;
};





#endif // EXPRESSIONMANAGER_H
