#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::ostream;
using std::istream;

class complex 
{
private:
    double re;
    double im;
public:
//  Default constructor
    complex (double a=0, double b=0)
    {
        re = a;
        im = b;
    }
//  Get module
    double mod()
    {
        return sqrt(re*re+im*im);
    }
//  Get real part    
    double get_re()
    {
        return re;
    }
//  Set real part
    void set_re(double a)
    {
        re = a;
    }
//  Get imaginary part
        double get_im()
    {
        return im;
    }
//  Set imaginary part
    void set_im(double a)
    {
        im = a;
    }
//  Operator +
    complex operator + (const complex &obj)
    {
        complex result;
        result.re = re + obj.re;
        result.im = im + obj.im;
        return result;
    }
// Operator -
    complex operator - (const complex &obj)
    {
        complex result;
        result.re = re - obj.re;
        result.im = im - obj.im;
        return result;
    }
//  Operator *
    complex operator * (const complex &obj)
    {
        complex result;
        result.re = re*obj.re-im*obj.im;
        result.im = re*obj.im+obj.re*im;
        return result;
    }

    friend ostream &operator << (ostream &os, const complex &obj);
    friend istream &operator >> (istream &is, const complex &obj);
};

ostream &operator << (ostream &os, const complex &obj)
{
    os<<obj.re;
    if(obj.im>0) os<<"+"<<obj.im;
    else os<<obj.im;
    os<<"i";
    return os;
}

istream &operator >> (istream &is, const complex &obj)
{
    is >> obj.re;
    is >> obj.im;
    return is;
}

int main()
{
    complex a, b(4, 5), c(7, 6);

//  Example for =
    a = b;
    cout<<a<<endl;

//  Example for +
    a = b + c;
    cout<<a<<endl;

//  Example for -
    a = b - c;
    cout<<a<<endl;

//  Example for *
    a = b*c;
    cout<<a<<endl;

    return 0;
}
