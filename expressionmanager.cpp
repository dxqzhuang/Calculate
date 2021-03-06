#include "expressionmanager.h"


ExpressionManager::ExpressionManager()
{

}

ExpressionManager::~ExpressionManager()
{

}

void ExpressionManager::load(string fileName)
{
    /***
     * load expressions from a file
     * @pre: file must be in following format:
     *  [valid expression][\n]
     *  [valid expression][\n]
     *  [valid expression][\n]
     */
    ifstream myFile;
    myFile.open(fileName);
    while(true)
    {
        Polynomial expr;
        myFile >> expr;
        if(myFile.eof()) break;
    }
}

void ExpressionManager::save(string fileName)
{
    /***
     * save all expressions to a file
     */
    ofstream myFile;
    myFile.open(fileName);
    for(int i=0; i<list.size(); i++)
        myFile << list[i] << "\n";
    myFile.close();
}

ExpressionManager ExpressionManager::operator << (string &expr)
{
    /***
     * @brief add a new expression into list
     * @pre string must be in the following format:
     *  "[LETTER A-Z][space][=][space][VALID EXPRESSION]"
     * @example "F = 2x + 4"
     */

    if(list.size()+1 > MAX_LIST_SIZE) throw LIST_FULL;
    stringstream ss;
    char junk;
    Polynomial x;
    expr.erase(0, 4);
    ss << expr;
    ss >> x;
    list.push_back(x);
    cout << "just pushed in: " << x << endl;
    return *this;
}

Polynomial ExpressionManager::operator[] (int which)
{
    /***
     * return one of the expressions from the list
     * @param which: char A-Z
     */
    return list[which];
}

