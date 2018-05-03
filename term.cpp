#include "term.h"


//=====DANGEROUS!! FIX THESE ==============
Fraction& Term::operator()(const Fraction& x)
{
    /**
      @brief parenthesis operator. Evaluate
        term at given value.
      @example (1/2)x^(1/2) evaluated at (1) ==> 1/2
      */
//    cout<<"coeff: "<<coeff<<endl;
//    cout<<"power: "<<(double)power.getNum()/(double)power.getDenom()<<endl;
    Fraction ans(coeff *
                 Fraction(pow(((double)x.getNum()/(double)x.getDenom()),
                          ((double)power.getNum()/(double)power.getDenom())
                                  )));
    return ans;
}

Term::Term(const Term& other)
{
    if(this!=&other)
    {
        this->coeff = other.coeff;
        this->power = other.power;
    }
}

Term Term::differentiate(){
    /**
      * @brief get the derivative of current Term
      * @return a Term object
      */
    return Term(coeff*power, power-Fraction(1,1));
}






//==========================con/destructors=========================
Term::Term(Fraction c, Fraction p)
{
    coeff = c;
    power = p;
}

Term::~Term()
{
    /**
     * @brief deleteMe
     */
    deleteMe();
}



//==========================helpers=========================
void Term::enableUnicode(bool choice)
{
    unicodeEnabled = choice;
}

string Term::toString(bool super)
{
    /**
     * @brief convert current Term to a string
     * @param super: if true, string contains superscript
     *  as opposed to "^power"
     */
    string ans = "";
    //if coefficient = 0, exit


    //else
    if(coeff == 0)
    {
        ans += coeff.toString();
        return ans;
    }
    else
    {
        if(coeff >0) ans += "+";
        ans += coeff.toString()
            += "x";
        if(super)
            ans += superScript(power);
        else
            ans += "^" + power.toString();
    }

    return ans;
}

void Term::copy(const Term &other)
{
    coeff = other.coeff;
    power = other.power;
}

void Term::deleteMe()
{
    coeff = power = 0;
}

string Term::superScript(Fraction n)const
{
    stringstream ss;
    char num;
    string ans = "";
    return ans;
//    switch (n) {
//    case 0: return "⁰";
//            break;
//    case 1: return "¹";
//            break;
//    case 2: return "²";
//            break;
//    case 3: return "³";
//            break;
//    case 4: return "⁴";
//            break;
//    case 5: return "⁵";
//            break;
//    case 6: return "⁶";
//            break;
//    case 7: return "⁷";
//            break;
//    case 8: return "⁸";
//            break;
//    case 9: return "⁹";
//            break;
//    default:
//            ss << n;    //dump into stringstream
//            while(ss >> num)
//            {
//                ans += this->superScript(num -= '0');
//            }
//            return ans;
//    }
}




//==========================setter/getters==================
Fraction Term::getPower() const
{
    return power;
}

Fraction Term::getCoeff() const
{
    return coeff;
}

void Term::set(Fraction c, Fraction p)
{
    coeff = c;
    power = p;
}




//==========================operators=======================
//--arithmetic----
Term Term:: operator+(const Term& other)
{
    return (this->power == other.power) ?
                Term(this->coeff+other.coeff,this->power) :
                 Term(Fraction(0,1));
}

Term Term:: operator-(const Term& other)
{
    return (this->power == other.power) ?
                Term(this->coeff-other.coeff,this->power): Term(0);
}

Term Term:: operator*(const Term& other)const
{
    return Term(this->coeff * other.coeff, this->power + other.power);
}

Term Term:: operator-()const
{
    /**
     * @brief negation operator
     */
    return Term(this->coeff*-1, this->power);
}

Term& Term::operator=(const Term &other)
{
    if(this != &other)
    {
        deleteMe();
        copy(other);
    }
    return *this;
}

Term& Term::operator+=(const Term &other)
{
    if(power == other.power)
        coeff += other.coeff;
    return *this;
}

Term& Term::operator*=(double x)
{
    coeff *= x;
    return *this;
}


//--I/O---------
istream& operator>>(istream& in, Term &t)
{
    /**
      @brief
      @example
            1. "-4/3 x ^ 1/2"
            2. "-4/2"
            3. "-4"
      @pre
        1. in contains only one term and nothing more.
        2. term must be in correct format:
            1. [sign][int]/[int][space][x][^][sign][int][/][int]
            2. [sign][int]/[int]
            3. [sign][int]
      */

    t.coeff = t.power = Fraction(0);
    char junk;
    string line;
    stringstream ss(line),ss_coeff,ss_power;
    getline(in, line);
    //cout << endl << "term >> fired! : " << line << endl;
    try{
        //1. dump the whole thing into ss
        //in.ignore('\n');
        if(line[0] != '+' && line[0] != '-')
        {
            line.insert(0, "+");
        }

        junk = line[0]; //this is the sign
        int x_pos = line.find("x");

        if(x_pos != string::npos)
        {
            //2. dump coefficient
            ss_coeff << line.substr(1, x_pos-1);
            ss_coeff >> t.coeff;
            if(junk == '-') t.coeff *= Fraction(-1);

            //3. dump power
            if(line[x_pos+2] != '+' && line[x_pos+2]!='-')
                line.insert(x_pos+2, "+");
            junk = line[x_pos+2];
            ss_power <<line.substr(x_pos+3);
            ss_power >> t.power;
            if(junk == '-') t.power *= Fraction(-1);
            return in;
        }else
        {
            // no "x" found
            //that means it's formatted in either "-4/2" or "-4"
            int delim_pos = line.find("/");
            int sign = line[0]=='-'? -1 : 1;
            line.erase(0,1);    //erase the sign
            ss = stringstream(line);
            ss >> t.coeff;
            ss_power = stringstream("0/1");
            ss_power >> t.power;
            t.coeff *= sign;
            return in;
        }
    }
    catch(...)
    {
        cout << "\nTerm says BAD FORMAT!==>" << line << endl;
        throw termErr::BAD_FORMAT;
    }
}

ostream& operator<<(ostream& out, const Term &t)
{
    //cout << "Term << fired!!!" << endl;
    //cout << "t.coeff" << t.coeff << "; t.power: " << t.power<<endl;
    out<<"("<<t.coeff<<")";
    if(t.power != 0 && t.coeff!=0)
    {
        out<<"X";
        if(t.power != 1)
        {
            if (!t.unicodeEnabled)
                out<<"^"<<"("<<t.power<<")";
            else
                out <<t.superScript(t.power);
        }
    }
    return out;
}


//--comparison-----

bool Term::operator<(const Term &other)
{
    return ((this->power == other.power) && (this->coeff < other.coeff))
            ||
            (this->power < other.power);
}

bool Term:: operator<=(const Term& other)
{
    return ((this->power == other.power) && (this->coeff <= other.coeff))
            ||
            (this->power <= other.power);
}

bool Term:: operator==(const Term& other)
{
    return ((this->power == other.power) && (this->coeff == other.coeff));
}

bool Term:: operator!=(const Term& other)
{
    return ((this->power == other.power) && (this->coeff != other.coeff))
            ||
            (this->power != other.power);
}

bool Term:: operator>=(const Term& other)
{
    return ((this->power == other.power) && (this->coeff >= other.coeff))
            ||
            (this->power >= other.power);
}

bool Term:: operator>(const Term& other)
{
    return ((this->power == other.power) && (this->coeff > other.coeff))
            ||
            (this->power > other.power);
}


//---other------




//=============HALF TESTED ================


