#include <iostream>
#include <cmath>
#include <ctime>

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
    void shells_sort();

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

void Array :: shells_sort()
{
    clock_t start = clock();
    int len_table = log2(len);
    int *table = new int [len_table+1];
    table[len_table] = 0;
    for(int i=0; i<len_table; i++)
    {
        table[i] = pow(2, i) - 1;
    }
    for(int i=0; i<= len_table; i++)
    {
        int s = table[i];
        int b = 0;
        while(b<s)
        {
            int j = b+s;
            while (j<len)
            {
                int x = line[j];
                int k = j-s;
                while (k>=0&&line[k]>x)
                {
                    line[s+k] = line[k];
                    k = k-s;
                }
                line[k+s] = x;
                j = j+s;
            }
            b++;
        }
    }
    clock_t end = clock();
    double time = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"Time = "<< time<<endl;
    delete[] table;
}



int main()
{
    int a[] = {4, 3, 1, 4, 5, 2, 1, 4};
    
    Array test_1(a, 8);
    
    test_1.shells_sort();
    cout<<test_1<<endl;
    

    return 0;
}
