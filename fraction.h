#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;

class Fraction
{
    typedef void (*fptr)(string, Fraction&);
    /*
     * Fraction class that converts:
     *     int;double; mixed fraction; regular fraction
     *  to Fraction object.
     */
    public:
       // fraction();  // Default constructor
        Fraction(int n = 1, int d = 1); //Two argument constructor
        Fraction(int w, int n, int d);
        Fraction(double x, int len_after_dot=-1);
        ~Fraction(); // Destructor
        Fraction(const Fraction& other); // Copy constructor
        Fraction stringToFraction(string line);
        Fraction regularInput(string line);
        Fraction integerInput(string line);
        Fraction mixedInput(string line);
        Fraction doubleInput(string line);

        //fraction accessors and mutators
        void set(int n, int d); //Mutator - 2 argument
        void set(int w, int n, int d); //Mutator - 3 arguments
        int getNum() const; //Accessor
        int getDenom() const;//Accessor
        string toString();  //return a stringified fraction

        //fraction operators
        Fraction& operator -()const;
        Fraction& operator=(const Fraction &other);
        friend Fraction& operator+=(Fraction &x, const Fraction &y);
        friend Fraction& operator-=(Fraction &x, const Fraction &y);
        friend Fraction& operator/=(Fraction &x, const Fraction &y);
        friend Fraction& operator*=(Fraction &x, const Fraction &y);
        friend ostream& operator<<(ostream& out, const Fraction &f);
        friend istream& operator>>(istream& in, Fraction &f);
        friend Fraction operator+(const Fraction &x, const Fraction &y);
        friend Fraction operator-(const Fraction &x, const Fraction &y);
        friend Fraction operator*(const Fraction &x, const Fraction &y);
        friend Fraction operator/(const Fraction &x, const Fraction &y);
        friend bool operator==(const Fraction &x, const Fraction &y);
        friend bool operator!=(const Fraction &x, const Fraction &y);
        friend bool operator<(const Fraction &x, const Fraction &y);
        friend bool operator>(const Fraction &x, const Fraction &y);
        friend bool operator<=(const Fraction &x, const Fraction &y);
        friend bool operator>=(const Fraction &x, const Fraction &y);


    private:
        //=====variables======
        int num, denom, whole;  //ex: 3 4/2
        vector<fptr> inputter_list; //list of 4 different input methods



        //=====methods=====
        void reduce(); //Helper function
        int gcd(int p, int q);//Helper function
        int type(string str); //0,1,2 ==> mix,regular,double
        void load_inputter_list();
        int count_decimal_places(double x); //9.345 ==> 3 decimal places
        //input 4 different kinds
        static void inputMix(string line, Fraction& f);
        static void inputRegular(string line, Fraction& f);
        static void inputDouble(string line, Fraction& f);
        static void inputInt(string line, Fraction& f);



    //  =======trash can ==========

};

#endif // FRACTION_H
