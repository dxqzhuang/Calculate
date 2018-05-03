#include "polynomial.h"

//==================con/destructors==================
Polynomial::Polynomial()
{
    poly.push_back(Term());
}

Polynomial::~Polynomial()
{
    deleteAll();
}

Polynomial::Polynomial(string expr)
{
    /**
      * @brief constructor based on a string
      */
    if(expr[0] != '+')
        expr.insert(expr.begin(), '+');
    stringstream ss;
        ss << expr;
    ss >> *this;
}

Polynomial::Polynomial(const Polynomial &p)
{
    copy(p);
}

//==================helpers==================
void Polynomial::copy(const Polynomial& p)
{
    poly = p.poly;
}

void Polynomial::deleteAll()
{
    poly.clear();
}

void Polynomial::reduce()
{
    order();
    combineLikeTerms();
}

void Polynomial::order()
{
     /**
      * @brief sort poly vector in increasing order
      */

    cout << "order fired!! \n";
    for(size_t i = 0; i < poly.size(); ++i)
        for(size_t j = 0; j < poly.size(); ++j)
            if(poly[i] > poly[j])
            {
                Term temp = poly[i];
                poly[i] = poly[j];
                poly[j] = temp;
            }
    cout << "order finished!!\n";
}

void Polynomial::combineLikeTerms()
{
    /**
     * @brief
     * @return none
     */
    cout << "combine" << endl;
    vector<Term> ans;
    Term temp;
    int i=0;
    order();    //sort in order
    while(!poly.empty())
    {
        cout << endl << "i: " << i << endl;
        //cout << "not empty" << endl;
        temp = poly[0]; //store first element in a variable
        poly.erase(poly.begin(),poly.begin()+1);    //erase first element from vector
        cout << "temp: " << temp << endl;
        cout << "poly: ";
        for(size_t i=0; i<poly.size(); i++)
            cout << poly[i] << " ";
        while(!poly.empty() && temp.getPower() == poly[0].getPower())
        {
            temp += poly[0];
            //cout << "temp: " << temp << endl;
            poly.erase(poly.begin(), poly.begin()+1);
        }
        ans.push_back(Term(temp));
        i++;
    }
    cout << "combine finished" << endl;
    poly = ans;
}

Polynomial Polynomial::differentiate(int n)
{
    /***
     *
     * @param n: number of times to differentiate
     */
    if(n == 0) return Polynomial();
    else if(n == 1)
    {
        vector <Term> temp;
        Polynomial ans;
        for(size_t i=0; i<poly.size(); i++)
        {
            temp.push_back(poly[i].differentiate());
        }
        ans.poly = temp;
        return ans;
    }
    else return differentiate(n-1).differentiate(1);
}

string Polynomial::toString()
{
    /***
     * @brief does literally what the name says. Converts to string
     *
     */
    string ans;
    for(size_t i=0; i<poly.size(); i++)
    {
        ans += poly[i].toString(false);
    }
    return ans;
}

void Polynomial::enableUnicode(bool choice)
{
    /**
      * @brief set the private variable "unicodeEnabled" to
      *  true/false. When false, display format will be like this:
      *     "4x^2". When true, superscript will be used.
      */
    for(size_t i=0; i<poly.size(); i++)
    {
        poly[i].enableUnicode(choice);
    }
}


void Polynomial::beautify(string& term)
{
    /***
     * @brief correctly format the inputted term
     *  in preparation for input operator.
     * @ note: correct term format:
     *      [coefficient][space][x][^][power]
     * @example "-4/1 x^2/3"
     */

    //add power of 1 if user didn't say power
    int x_pos;
    if((x_pos = term.find("x")) == string::npos)
    {
        return;
    }else
    {
        string substr = term.substr(x_pos);
        if(substr.find("^") == string::npos)
        {
            term.insert(x_pos+1, "^1/1");
        };
    }


}

//==================operators==================
//------I\O-------
ostream& operator<<(ostream& out, const Polynomial &p)
{
    stringstream ss;
    string line;
    if(p.poly.empty()){
        ss<<0;
    }
    else{
        for(size_t i = 0; i <p.poly.size(); i++)
        {
            ss<<p.poly[i];
            if(i<p.poly.size()-1)
                 ss<< " + ";
        }
    }

    getline(ss,line);
    if(line[0] == '+')
    line.erase(line.begin());
    out << "(" << line <<")";
    return out;
}

istream& operator>>(istream& in, Polynomial &p)
{
    /**
     * @brief
     * @pre string that in contains MUST follow the exact format
     *  as shown in example below.
     * @example "-4/1 x^1/2 + +5/4 x^2/3"
     */
    stringstream ss, ss1;
    char junk;
    Term test;
    string line;
    string err_line;
    string substr;
    string delimitor(" + "), delimitor1(" - ");
    int delim_pos=0;
    int sign;
    in >> ws;       //eat up all the leading whitespace first
    getline(in, line);
    //if leading character is not a sign, plug a positive sign in there
    if(line[0] != '+' && line[0] != '-')
        line = '+' + line;
    sign = (line[0] == '-') ? -1 : 1;
    p.poly.clear();


    while(
          (delim_pos=line.find(delimitor1))!=string::npos ||
          (delim_pos=line.find(delimitor))!=string::npos
    )
    {   //keep splitting the string until delimitor runs out
        int pos_1,pos_2;
        if(
        (pos_1=line.find(delimitor1))!=string::npos &&
        (pos_2=line.find(delimitor))!=string::npos)
            delim_pos = (pos_1 < pos_2)? pos_1 : pos_2;
        //1. slice out a segment(a.k.a a term)
        substr = line.substr(0, delim_pos);
        p.beautify(substr);
        ss << substr;
        try{
            //2. dump the term into stringstream then extract into Term
            ss >> test;
            //test *= sign;
            //3. push into list
            p.poly.push_back(Term(test));
        }
        catch(termErr::ERR e)
        {
            cout << "\nBAD FORMAT!!!CANNOT INPUT TERM\n";
            return in;
        }
        //2. cut the segment out
        sign = (line[delim_pos+1] == '-') ? -1 : 1;
        line.erase(0, delim_pos+delimitor.length());
        ss = stringstream();
    }

    p.beautify(line);
    ss << line;
    try{

        ss >> test;
        test *= sign;
        p.poly.push_back(Term(test));
    }
    catch(termErr::ERR e)
    {
        cout << "\nBAD FORMAT!!!CANNOT INPUT TERM\n";
        return in;
    }

    return in;
}


//------arithmetic----
Polynomial operator+(const Polynomial& a, const Polynomial &b)
{
    Polynomial ans;
    for(size_t i=0; i<a.poly.size(); i++)
        ans.poly.push_back(a.poly[i]);
    for(size_t i=0; i<b.poly.size(); i++)
        ans.poly.push_back(b.poly[i]);
    ans.reduce();
    return ans;
}

Polynomial operator-(const Polynomial& a, const Polynomial &b)
{
    /**
     * @brief subtraction operator
     */
    return a + (-b);    //LHS plus the negated RHS
}

Polynomial operator*(const Polynomial& a, const Polynomial &b)
{
    Polynomial ans;
    for(size_t i = 0; i < a.poly.size(); ++i)
        for(size_t j = 0; j < b.poly.size(); ++j)
            ans.poly.push_back(a.poly[i] * b.poly[j]);
    ans.reduce();
    return ans;
}

Polynomial operator-(const Polynomial& other)
{
    /**
     * @brief negation operator
     */
    Polynomial ans;
    for(int i=0; i<other.poly.size(); i++)
    {
        ans.poly.push_back(Term(-other.poly[i]));
    }
    ans.reduce();
    return ans;
}


//------other--------
Fraction Polynomial::operator()(Fraction x)
{
//    cout<<"here";
    Fraction ans(0,0,1);
//    cout<<"here2";
    for(size_t i = 0; i < poly.size(); ++i){
//        cout<<"here3";
        ans = ans + poly[i](x);
//        cout<<"here4";
    }
    return ans;
}

Polynomial& Polynomial::operator=(const Polynomial &other)
{
    if(this != &other)
    {
        deleteAll();
        copy(other);
    }
    return *this;
}






//==================HALF TESTED==================

