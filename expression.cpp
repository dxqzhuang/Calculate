#include "expression.h"


Expression::Expression()
{
    for(int i=0; i<MAX_LIST_SIZE; i++)
    {
        const Polynomial x;
        list.push_back(x);
    }
}

Expression::~Expression()
{

}

void Expression::load(string fileName)
{
    /***
     * load expressions from a file
     * @pre: file must be in following format:
     *  [valid expression][\n]
     *  [valid expression][\n]
     *  [valid expression][\n]
     */
    vector<Polynomial> ans;
    string _fileName = fileName;
    if(_fileName.find(".exp") == string::npos)
    {
        _fileName += ".exp";
    }
    ifstream myFile;
    myFile.open(_fileName);
    while(ans.size() < MAX_LIST_SIZE)
    {
        Polynomial expr;
        myFile >> expr;
        ans.push_back(expr);
        if(myFile.eof()) break;
    }

    for(int i=ans.size(); i<MAX_LIST_SIZE; i++)
    {
        const Polynomial x;
        ans.push_back(x);
    }

    list = ans;
}

void Expression::save(string fileName)
{
    /***
     * save all expressions to a file
     */
    string _fileName = fileName;
    if(_fileName.find(".exp") == string::npos)
    {
        _fileName += ".exp";
    }
    ofstream myFile;
    myFile.open(_fileName);
    for(int i=0; i<list.size(); i++)
        myFile << list[i] << "\n";
    myFile.close();
}

Expression Expression::operator<<(string &expr)
{
    /***
     * @brief add a new expression into list
     * @pre string must be in the following format:
     *  "[LETTER A-Z][space][=][space][VALID EXPRESSION]"
     * @example "F = 2x + 4"
     */

    //if(list.size()+1 > MAX_LIST_SIZE) throw LIST_FULL;
    stringstream ss;
    char junk;
    char which = expr[0];
    Polynomial x;
    expr.erase(0, 4);
    ss << expr;
    ss >> x;
    list[tolower(which)-'a'] = x;
    return *this;
}

Polynomial Expression::operator[](char& which)
{
    /***
     * return one of the expressions from the list
     * @param which: char A-Z
     */
    which = tolower(which);
    if((which-'a') > list.size())
    {
        throw FUNCTION_NOT_FOUND;
    }
    //cout << "which-a: " << which-'a' << endl;
    return list[which-'a'];
}

void Expression::set(char& which, const Polynomial& what)
{
    //cout << "set fired!! " << endl;
    //cout << "which: " << which;
    which = tolower(which)-'a';
    //cout << which - 'a' << endl;
    list[which] = what;
    //cout << "new which: " << list[which-'a'] << endl;
}
