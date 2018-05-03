#include "fraction.h"

//=======operators========

//======NOT TESTED!!!!!!!===============



//=============HALF TESTED ================
//* when testing these functions, mainly test edge cases.


Fraction& operator*=(Fraction &x, const Fraction &y)
{
    x = x*y;
    return x;
}

Fraction& operator/=(Fraction &x, const Fraction &y)
{
    x = x/y;
    return x;
}

Fraction& operator-=(Fraction &x, const Fraction &y)
{
    x = x-y;
    return x;
}

Fraction& operator+=(Fraction &x, const Fraction &y)
{
    x = x +y;
    return x;
}

Fraction operator/(const Fraction &x, const Fraction &y)
{
    /**
      @brief divide operator
      @example (2 1/2) / (3 2/3) = (2 1/2) * (3/11)
    */
    Fraction ans = x * Fraction(y.denom, y.num+y.whole * y.denom);
    return ans;
}

Fraction operator*(const Fraction &x, const Fraction &y)
{
    /**
     * @brief multiply operator
     * @example 2 1/2 * 3 2/3 ==> 5/2 * 11/3 = 55/6
     */
    int num = (x.num+x.whole*x.denom)*(y.num+y.whole*y.denom) ,
        denom = x.denom*y.denom;
    Fraction ans(num,denom);
    return ans;
}

Fraction operator+(const Fraction &x, const Fraction &y)
{
    /**
     * @brief add whole part, then add regular part, then add result together
     * @example 4 2/3 + 0 1/3 = 4 3/3
     */
    int whole = x.whole + y.whole;
    int num = x.num*y.denom + x.denom*y.num,
        denom = x.denom*y.denom;
    Fraction ans(whole, num,denom);
    return ans;
}

Fraction operator-(const Fraction &x, const Fraction &y)
{
    /**
     * @brief minus operator
     */

    int whole = x.whole - y.whole;
    int num = x.num*y.denom - x.denom*y.num,
        denom = x.denom*y.denom;
    Fraction ans(whole, num,denom);
    return ans;
}

ostream& operator<<(ostream& out, const Fraction &f)
{
    /**
        @brief output regular fraction ONLY.
            Any mixed fraction will be converted to regular
            before outputting.
        @example "3 1/2" ==> "7/2"
    */
    out<<(f.whole*f.denom)+f.num;
    if(f.denom != 1) out<<"/"<<f.denom;
    return out;
}

istream& operator>>(istream& in,  Fraction &f)
{
    /**
     * @brief input a fraction
     * @pre
     *  1. in is an inputstream that contains one of four
     *      types of "fraction"s, and nothing more.
     *  2. see @pre of "type" method of Fraction class.
     * @example content stored in in:
     *  "4 2/3", or "2.3", or "2/3", "4"
     */
    string line;
    getline(in, line);

    //1. check type (mixed, regular, double, int)
    int type = f.type(line);

    //2. call input helpers according to type
    (*f.inputter_list[type])(line, f);

    return in;
}

bool operator==(const Fraction &x, const Fraction &y)
{
    /**
      @brief comparison operator
      */


    return x.getNum()*y.denom == x.denom*y.getNum();
}

bool operator!=(const Fraction &x, const Fraction &y)
{
    return !(x == y);
}

bool operator<(const Fraction &x, const Fraction &y)
{
    return x.getNum()*y.denom < x.denom*y.getNum();
}

bool operator>(const Fraction &x, const Fraction &y)
{
    return (x != y) && !(x<y);
}

bool operator<=(const Fraction &x, const Fraction &y)
{
    return !(x > y);
}

bool operator>=(const Fraction &x, const Fraction &y)
{
    return !(x < y);
}

