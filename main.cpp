#include <iostream>
#include "expression.h"
#include <string>
//#include "fraction.h"

using namespace std;

int process(string& input);

int main()
{
//    ExpressionManager manager;
//    cout << "COMMAND: ";
//    string line;
//    getline(cin, line);
//    if(line.find("LET") != string::npos)
//        line.erase(0,4);
//    manager << line;
//    cout << "F = " << manager[0];

//    Expression x;
//    cout << ": ";
//    cin >> x;
//    cout << "x: " << x << endl;


    Fraction frac;
    Polynomial _pol;

    Expression manager;
    stringstream ss;
    cout << "COMMAND: ";
    string line;
    getline(cin, line);
    int _command = process(line);
    string junk;
    while(true)
    {

        switch(_command)
        {
        case 1:

            break;
        case 2:
            line.erase(0, 2);
            line.erase(line.size()-1, 2);
            ss << line;
            cout <<manager[0](frac.stringToFraction(line));
            break;
        case 3:
            manager << line;
            cout << "F = " << manager[0] << endl;
            break;
        default:
            cout << "UNKNOWN INPUT";
            break;
        }
        cout << "COMMAND: ";
        line = "";
        getline(cin, line);
        _command = process(line);
        junk = "";
        ss = stringstream();
    }





    return 0;
}


int process(string &input)
{
    //PRINT: RETURN 1
    if(input.find("PRINT") != string::npos)
    {
        input.erase(0, 6);
        return 1;
    }
    //EVAL: RETURN 2
    if(input.find("EVAL") != string::npos)
    {
        input.erase(0, 5);

        return 2;
    }

    //LET: RETURN 3
    {
        if(input.find("LET") != string::npos)
        {
            input.erase(0, 4);
            int x_pos = input.find('X');
            if(x_pos != string::npos)
            {
                input[x_pos] = 'x';
            }
            return 3;
        }
    }
}

