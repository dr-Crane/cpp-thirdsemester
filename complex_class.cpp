#include <iostream>
#include <string>
#include <cmath>

using std::cout;
using std::endl;

class complex
{
    double re, im;
public:
// Default value is zero
    complex()
    {
        re=0;
        im=0;
    }
    complex(double a, double b)
    {
        re = a;
        im = b;
    }
// For mod() of two complex nums
    double mod()
    {
        return sqrt(re*re+im*im);
    }
// Output    
    void output()
    {
        cout<<re;
        if(im>0) cout<<"+"<<im;
        else cout<<im;
        cout<<"i"<<endl;
    }
// Get real part    
    double get_re()
    {
        return re;
    }
// Set real part
    void set_re(double a)
    {
        re = a;
    }
// Get imaginary part
        double get_im()
    {
        return re;
    }
// Set imaginary part
    void set_im(double a)
    {
        im = a;
    }
// Adding two complex numbers
    void add(complex a, complex b)
    {
        re = a.re+b.re;
        im = a.im+b.im;
    }
// Substracts two complex numbers
    void sub(complex a, complex b)
    {
        re = a.re-b.re;
        im = a.im-b.im;
    }  
// Multiplys two complex nums
    void mul(complex a, complex b)
    {
        re = a.re*b.re-a.im*b.im;
        im = a.re*b.im+b.re*a.im;
    }
};

int main()
{

    complex a(2 , 2), b(-4, -6);
    complex c;
    c.mul(a,b);
    c.output();

    return 0;
}
