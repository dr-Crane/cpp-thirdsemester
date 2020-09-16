#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

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
//  Copy constructor
    complex (const complex &obj)
    {
        re = obj.re;
        im = obj.im;
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
//  Operator =
    void operator = (const complex &obj)
    {
        re = obj.re;
        im = obj.im;
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

};

void print_num(complex num)
{
    cout<<num.get_re();
    if(num.get_im()>0) cout<<"+"<<num.get_im();
    else cout<<num.get_im();
    cout<<"i"<<endl;
}

int main()
{
    complex a, b(4, 5), c(7, 6);

//  Example for =
    // a = b;
    // print_num(a); 

//  Example for +
    // a = b + c;
    // print_num(a);

//  Example for -
    // a = b - c;
    // print_num(a);

//  Example for *
    // a = b*c;
    // print_num(a);

    return 0;
}
