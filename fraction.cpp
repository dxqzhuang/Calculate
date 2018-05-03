#include "Fraction.h"

Fraction::Fraction(int n, int d) //Two argument constructor
{
    whole = 0;
    num = n;
    denom = d;
    reduce();
    load_inputter_list();
}

Fraction::Fraction(int w, int n, int d)
{
    whole = w;
    num = n;
    denom = d;
    reduce();
    load_inputter_list();
}

Fraction::~Fraction() // Destructor
{

}

Fraction::Fraction(const Fraction& other) // Copy constructor
{
    whole = other.whole;
    num = other.num;
    denom = other.denom;
    inputter_list = other.inputter_list;
}


//========operators=========

//==============NOT TESTED!!!!=============
Fraction::Fraction(double x, int len_after_dot)
{
    /**
     * @brief given a double, construct Fraction object
     * @example 4.2 ==> 21/5
     * @pre size of x cannot exceed size limit of integers.
     * @param len_after_dot: how many digits after dot;
     *      ex: 4.2 ==> 1 digit after dot
     */

    //if decimal places is not given, count it yourself
    if(len_after_dot == -1)
        len_after_dot = count_decimal_places(x);
    whole = 0;
    num = x * pow(10, len_after_dot);
    denom = pow(10, len_after_dot);
    reduce();
    load_inputter_list();
}

int Fraction::count_decimal_places(double x)
{
    /**
     * @brief count how many digits after "."
     * @example 3.345 ==> 3 decimal places
     */
    int ans = 0;
    stringstream ss;
    string line;
    ss << std::fixed <<x;
    getline(ss,line);
    int dot_pos = line.find(".");
    ans = line.length() - dot_pos - 2;
    return ans;
}


string Fraction::toString()
{
    string ans;
    stringstream ss;
    ss << *this;
    getline(ss,ans);
    /*
    ans += to_string(num);
    ans += "/";
    ans += to_string(denom);*/
    return ans;
}

//======setter/getters=========
void Fraction::set(int n, int d)
{
    /**
      @brief 2 argument mutator
      */
    whole = floor(n/d);
    num = n-whole*denom;
    denom = d;
    reduce();
}


//========helpers=========
void Fraction::reduce() //Helper function
{
    /**
     * @brief div
     */


    int div = gcd(num,denom);
    num /= div;
    denom /= div;
    if(denom < 0)
    {
        num *= -1;
        denom *= -1;
    }
    if(num==denom){
        whole++;
        num=0;
        denom=1;
    }
}

void Fraction::set(int w, int n, int d)
{
    /**
      @brief 3 argument mutator
      */
    whole = w;
    num = n;
    denom = d;
    reduce();
}

Fraction& Fraction::operator=(const Fraction &other)
{
    /**
      @brief equal operator
      */
    if(this != &other)
        this->set(other.whole,other.num,other.denom);
    return *this;
}

Fraction Fraction::stringToFraction(string line)
{
    /* Reads from a string and create a fraction accordingly
    *
    */
    Fraction ans;
    switch(type(line)){
        case 0:
        ans=mixedInput(line);
            break;
        case 1:
        ans=regularInput(line);
            break;
        case 2:
            ans=doubleInput(line);
            break;
        case 3:
            ans=integerInput(line);
            break;
        default:
            cout<<"Unable to turn this string into fraction, check input /n";
    }
    return ans;
}


int Fraction::getNum() const//Accessor
{
    /**
     * @brief return numerator */
    int ans = num;
    ans += whole*denom;
    return ans;
}

int Fraction::getDenom() const//Accessor
{
    return denom;
}


Fraction& Fraction:: operator -()const
{
    /**
      @brief negation operator
      @example 2 2/3 ==> -(2*3 + 2) / 3 = -8/3
    */
    Fraction ans(-(whole * denom + num), denom);
    return ans;
}

int Fraction::gcd(int p, int q) //Helper function
{
    return q==0? p : gcd(q, p%q);
}

void Fraction::inputRegular(string line, Fraction& f)
{
    /**
      @brief input a regular fraction
      @param line: "3/2", etc
      @pre
            1. see @pre of "type" function
            2. line contains a regular fraction
      @post 1. f has been set
      @example "1123/234" ==> 1123, 234, => 1123/234
    */

    //cout << " "-----inputRegular fired!-----" << endl;
    int div_pos = line.find("/");
    f = Fraction(
                stoi(line.substr(0, div_pos)),
                stoi(line.substr(div_pos+1))
        );
}

void Fraction::inputInt(string line, Fraction& f)
{
    /**
      @brief input a regular fraction
      @param line: "32", etc
      @pre
            1. see @pre of "type" function
            2. line contains an integer
      @post 1. f has been set
      @example "42"
    */
    f.whole = stoi(line);
    f.num = 0;
    f.denom = 1;
}

void Fraction::inputMix(string line, Fraction& f)
{
    /**
      @brief input a mix fraction
      @param line: "4 3/2", etc
      @pre
            1. see @pre of "type" function
            2. line contains a mixed fractions
            3. the content contained in line MUST
                follow exactly the same format as shown in example.
                No extra whitespace allowed.
      @post f has been set
      @example "31 1/2"
    */

    //cout << "----inputMix fired-----" << endl;
    int space_pos = line.find(" "), div_pos = line.find("/");
    int whole = stoi(line.substr(0, space_pos)),
        num = stoi(line.substr(space_pos+1, div_pos-2)),
        denom = stoi(line.substr(div_pos+1));
    f = Fraction(whole, num, denom);
}

void Fraction::inputDouble(string line, Fraction& f)
{
    /**
      @brief input a regular fraction
      @param line: "3.2", etc
      @pre
            1. see @pre of "type" function
            2. line contains a double(decimal)
      @post 1. f has been set
      @example "2.2"
    */
    //cout << " "-----inputDouble fired------" <<endl;
    int dot_pos = line.find(".");
    // ---- ex: "2.3" ==> "2", "3" => 2 + 3/10 = 2.3
    string  before_dot = line.substr(0, dot_pos),
            after_dot = line.substr(dot_pos+1);
    double whole = stod(before_dot),
           frac = stod(after_dot) / pow(10, after_dot.length());
    f = Fraction(whole + frac, after_dot.length());
}

//Following functions return fractions for stringToFraction======
Fraction Fraction::regularInput(string line){
    int div_pos = line.find("/");
    return Fraction(stoi(line.substr(0, div_pos)),
                    stoi(line.substr(div_pos+1)));
}

Fraction Fraction::integerInput(string line){
    return Fraction(stoi(line),0,1);
}

Fraction Fraction::mixedInput(string line){
    int space_pos = line.find(" "), div_pos = line.find("/");
    return Fraction(stoi(line.substr(0, space_pos)),
                    stoi(line.substr(space_pos+1, div_pos-2)),
                    stoi(line.substr(div_pos+1)));
}

Fraction Fraction::doubleInput(string line){
    int dot_pos = line.find(".");
    // ---- ex: "2.3" ==> "2", "3" => 2 + 3/10 = 2.3
    string before_dot = line.substr(0, dot_pos),
           after_dot = line.substr(dot_pos+1);
    double whole = stod(before_dot),
           frac = stod(after_dot) / pow(10, after_dot.length());
    return Fraction(whole + frac, after_dot.length());
}
//end of stringToFraction helpers=============================



int Fraction::type(string str)
{
    /**
     * @brief given a string, return 0,1,2,3
     *  for mix fraction, regular fraction, double, int, respectively
     * @example "4 3/2" ==> 0, "3/2" ==> 1, "3.2" ==> 2, "3" ==> 3
     * @pre str has to be trimmed at the head and tail.
     *      Ex: " 4.2" is NOT allowed because of white space in front.
     */
    int ans;
    int div_pos = str.find("/"); //position of "/"
    int dot_pos = str.find(".");    //position of "."
    if(div_pos == string::npos)
    {
        if(dot_pos == string::npos)
            return 3;   //this is an integer because no "." is found
        return 2;   //this is a double
    }

    else
    {
        //cout << " "---type:------" << endl;
        string sub = str.substr(0, div_pos); //"4 3/2" ==> "4 3"
        //cout << " "type ------" << endl;
        int whiteSpace_pos = sub.find(" "); //position of white space. "4 3" ==> 1
        //cout << " "type ------" << endl;
        if(whiteSpace_pos != string::npos)
        {
            //cout << " "white space found" << endl;
            //if white space found in string
            return 0;
        }
        else
        {
            //cout << " "no white space found. type exiting" << endl;
            return 1;
        }
    }
}

void Fraction::load_inputter_list()
{
    /**
        @brief push all four inputters into list.
            this function is to be used in constructors.
    */
    inputter_list.push_back(inputMix);
    inputter_list.push_back(inputRegular);
    inputter_list.push_back(inputDouble);
    inputter_list.push_back(inputInt);
}


//==============TRASH CAN =================
