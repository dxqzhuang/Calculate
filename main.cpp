#include <iostream>
#include "expression.h"
#include <string>

using namespace std;

enum options {PRINT,EVAL,LET,LOAD,SAVE,PLUS,MINUS,DIFF};
int process(string& input);
//Fraction string_to_fraction(string line);
void extract_operand(string line, char& assign_to, char& LHS,char& RHS);
void extract_original_function(string line, int& n, char& assign_to, char& func);

int main()
{
    Fraction frac;
    Polynomial _pol;

    Expression manager;
    stringstream ss;
    char which;
    char assign_to, LHS, RHS, func;
    int n;
    cout << "COMMAND: ";
    string line;
    getline(cin, line);
    int _command = process(line);
    string junk;
    while(true)
    {

        switch(_command)
        {
        case PRINT:
            try{
                which = line[0];
                //cout << "You are printing: "<< line[0] << endl;
                cout << which << " = " << manager[which] << endl;
            }
            catch(ERRORS e)
            {
                cout << "\nYou have not entered " << line[0] << ".\n";
            }
            break;
        case EVAL:
            which = line[0];
            line.erase(0, 2);
            line.erase(line.size()-1, 1);
            ss << line;
            cout << which<<"("<<line<<") = ";
            cout << manager[which](frac.stringToFraction(line)) << endl;
            break;
        case LET:
            try
            {
                manager << line;
            }
            catch(ERRORS e)
            {
                if(e == LIST_FULL) cout << ": List is full\n";
            }
            break;
        case LOAD:
            manager.load(line);
            break;
        case SAVE:
            manager.save(line);
            break;
        case PLUS:
            try
            {
                extract_operand(line, assign_to, LHS, RHS);
                manager.set(assign_to, manager[LHS]+manager[RHS]);
            }
            catch(ERRORS e)
            {
                cout <<"\nYou have not entered one of these functions.\n";
            }
            break;
        case MINUS:
            try
            {
                extract_operand(line, assign_to, LHS, RHS);
                manager.set(assign_to, manager[LHS]-manager[RHS]);
            }
            catch(ERRORS e)
            {
                cout <<"\nYou have not entered one of these functions.\n";
            }
            break;
        case DIFF:
            try
            {
                extract_original_function(line, n, assign_to, func);
                manager.set(assign_to, manager[func].differentiate(n));
            }
            catch(ERRORS e)
            {
                cout <<"\nYou have not entered one of these functions.\n";
            }
            break;
        }
        cout << "\nCOMMAND: ";
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
        return PRINT;
    }
    //EVAL: RETURN 2
    else if(input.find("EVAL") != string::npos)
    {
        input.erase(0, 5);

        return EVAL;
    }

    //LET: RETURN 3
    else if(input.find("LET") != string::npos)
    {
        input.erase(0, 4);
        int x_pos = input.find('X');
        if(x_pos != string::npos)
        {
            input[x_pos] = 'x';
        }
        return LET;
    }
    //LOAD :RETURN 4
    else if(input.find("LOAD") != string::npos)
    {
        input.erase(0, 5);
        return LOAD;
    }
    //SAVE : RETURN 5
    else if(input.find("SAVE") != string::npos)
    {
        input.erase(0, 5);
        return SAVE;
    }
    //OTHER :
    else {
        //F+G : RETURN 6
        if(input.find("+")!= string::npos)
        {
            return PLUS;
        }
        //F-G: RETURN 7
        else if(input.find("-") != string::npos)
        {
            return MINUS;
        }
        //G': RETURN 8
        else if(input.find("'") != string::npos)
        {
            return DIFF;
        }
    }
}

void extract_operand(string line,char& assign_to, char& LHS,char& RHS)
{
    /***
     * "F = G + H" ==> F:assign_to, G:LHS, H: RHS
     *
     */
    assign_to = line[0];
    LHS = line[4];
    RHS = line[8];
}

void extract_original_function(string line, int& n, char &assign_to, char& func)
{
    /***
     * "F = G'" ==> F: assign_to, func: G, n: 1(order of derivative)
     *
     */
    n = 0;
    assign_to = line[0];
    func = line[4];
    string substr = line.substr(5);
    //cout << "substr: " << substr << endl;
    while(substr.size() > 0)
    {
        //cout << substr.size() << endl;
        n += 1;
        substr.erase(0, 1);
    }
}

