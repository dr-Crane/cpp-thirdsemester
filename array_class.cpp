#include <iostream>
#include <cmath>

using namespace std;

class Array
{
    int *line;
    int len;
public:
    Array(int amount=1, int type=1, int area=10);
    Array(int *a, int b);
    Array(const Array &obj);
   ~Array();

    Array &operator = (Array &obj);
    int &operator [] (int pos);
    bool operator == (Array &obj);

    bool test_increment();

    friend istream &operator >> (istream &is, Array &obj);
    friend ostream &operator << (ostream &os, Array &obj);
};

ostream &operator << (ostream &os, Array &obj)
{
    for(int i=0; i<obj.len; i++)
    {
        os<<obj.line[i]<<"  ";
    }
    return os;
}

istream &operator >> (istream &is, Array &obj)
{
    cout<<"Len = "<<endl;
    is>>obj.len;
    cout<<"Members = "<<endl;
    delete[] obj.line;
    obj.line = new int [obj.len+1];
    obj.line[obj.len] = 0;
    for(int i=0; i< obj.len; i++)
    {
        is>>obj.line[i];
    }
    return is;
}

// Array :: Array(int amount=1, int type=1, int area=10)
// {
//     len = amount;
//     line = new int [len+1];
//     line[len] = 0;
//     for(int i=0; i<len; i++)
//     {
//         line[i] = rand() % area;
//     }
// }

Array :: ~Array()
{
    delete[] line;
}

Array :: Array(const Array& obj)
{
    len = obj.len;
    line = new int [len+1];
    line[len] = 0;
    for(int i=0; i<len; i++)
    {
        line[i] = obj.line[i];
    }
}

Array :: Array(int *a, int b)
{
    len = b;
    line = new int [len+1];
    line[len] = 0;
    for(int i=0; i<len; i++)
    {
        line[i] = a[i];
    }
}

Array& Array :: operator = (Array &obj)
{
    if(this == &obj) return *this;
    delete[] line;
    len = obj.len;
    line = new int [len+1];
    line[len] = 0;
    for(int i=0; i<len ; i++)
    {
        line[i] = obj.line[i];
    }
    
    return *this;

}

int& Array :: operator [] (int pos)
{
    return line[pos];
}

bool Array :: operator == (Array &obj)
{
    if(obj.len!=len) return false;
    for(int i=0; i<len; i++)
    {
        if(obj.line[i]!=line[i]) return false;
    }

    return true;
}

bool Array :: test_increment()
{
    for(int i=0; i<len-1; i++)
    {
        if(line[i]>line[i+1]) return false;
    }
    
    return true;
}



int main()
{
    int a[] = {4, 3, 1, 4, 5, 2, 1, 4};
    
    Array test_1(a, 8);
    
    

    cout<<test_1<<endl;
    

    return 0;
}
