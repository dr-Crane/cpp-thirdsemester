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
    void shaker_sort();
    void hoares_sort();
    void byte_sort();
    void heap_sort();

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

Array :: Array(int amount, int type, int area)
{
    len = amount;
    line = new int [len+1];
    line[len] = 0;
    if(type == 1)
    {
        for(int i=0; i<len; i++)
        {
            line[i] = rand() % area;
        }
    }
    if(type == 2)
    {
        int space = 10;
        line[0]=rand() % 10;
        for(int i=1; i<len; i++)
        {
            while(line[i-1]>line[i])
            {
                line[i]=rand() % space;
            }
            space++;
        }
    }
    if(type==3)
    {
        int space = 100;
        line[0]=rand() % 100;
        for(int i=1; i<len; i++)
        {
            do
            {
                line[i] = rand() % space;
            } while (line[i-1]<line[i]);
            
            if(space>10) space--;
        }
    }
}

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

void print_line(int *line, int len)
{
    for(int i=0; i<len; i++)
    {
        cout<<line[i]<<"  ";
    }
    cout<<endl;
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

void Array :: shaker_sort()
{
    clock_t start = clock();
    int left = 0, right = len-1; 
    int last_right = left,  last_left = right;

    while(left<right)
    {
        int space = 0;
        int i=left;
        while(i<right)
        {
            if(line[i]>line[i+1])
            {
                space = line[i];
                line[i] = line[i+1];
                line[i+1] = space;
                last_right = i;
            }
            i++;
        }
        right = last_right;

        int j=right;
        while(j>left)
        {
            if(line[j]<line[j-1])
            {
                int space = line[j];
                line[j] = line[j-1];
                line[j-1] = space;
                last_left = j;
            }
            j--;
        }
        left = last_left;
        if((left+1)==right) break;

    }

    clock_t end = clock();
    double time = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"Time = "<< time<<endl;

}

void rec_for_hoares(int *line, int left, int right)
{
    if(left>=right) return;
    
    int i=left, j=right, x=line[(left+right)/2];

    while(i<=j)
    {
        while(line[i]<x) i++;
        while(line[j]>x) j--;
        if(i<=j)
        {
            int space = line[i];
            line[i] = line[j];
            line[j] = space;
            i++;
            j--;
        }
    }

    rec_for_hoares(line, left, j);
    rec_for_hoares(line, i, right);
}

void Array :: hoares_sort()
{
    clock_t start = clock();
    rec_for_hoares(line, 0, len-1);
    clock_t end = clock();
    double time = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"Time = "<< time<<endl;
}

void rec_for_byte(int* line, int left, int right, int k)
{
    if(left>=right || k<0) return;

    unsigned int mask = 1;
    mask = mask<<k;

    int i=left, j=right;
    while(i<=j)
    {
        while((i<=j)&&((mask|line[i])!=line[i])) i++;
        while((i<=j)&&((mask|line[j])==line[j])) j--;
        if(i<j)
        {
            int space = line[i];
            line[i] = line[j];
            line[j] = space;
            i++;
            j--;
        }
    }

    int new_k = k-1;
    rec_for_byte(line, left, j, new_k);
    rec_for_byte(line, i, right, new_k);

}

void Array :: byte_sort()
{
    clock_t start = clock();
    int max = 0, k = 31;
    for(int i=0; i<len; i++)
    {
        if(line[i]>max) max = line[i];
    }
    unsigned int mask = 1;
    mask = mask<<31;
    while(mask!=0)
    {
        if((mask|max) == max)  break;
        k--;
        mask = mask>>1;
    }

    rec_for_byte(line, 0, len-1, k);
    clock_t end = clock();
    double time = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"Time = "<< time<<endl;
}

void rec_for_heap(int *line, int len, int pos)
{
    int biggest = pos;
    // l-левый последователь, r-правый, biggest- корень
    int l = 2*pos+1;
    int r = 2*pos+2;

    if((l<len) && (line[l]>line[biggest])) biggest = l; // На случай, если левый последователь больше корня
    if((r<len) && (line[r]>line[biggest])) biggest = r; // если правый

    if(pos!=biggest)
    {
        int num = line[biggest];
        line[biggest] = line[pos];
        line[pos] = num;
        
        // print_line(line, len);

        rec_for_heap(line, len, biggest);
    }

}

void Array :: heap_sort()
{
    clock_t start = clock();

    for(int i=(len/2-1); i>=0; i--)
    {
        rec_for_heap(line, len, i);
    }
    int num = 0;
    for(int i=len-1; i>=0; i--)
    {
        num = line[i];
        line[i] = line[0];
        line[0] = num;
        rec_for_heap(line, i, 0); // Используем рекурсию на уменьшенной куче
    }

    clock_t end = clock();
    double time = (double)(end-start)/CLOCKS_PER_SEC;
    cout<<"Time = "<< time<<endl;
}

int main()
{
    
    Array test(10, 1, 10);
    Array test_2 = test;
    // cout<<test<<endl;

    test.heap_sort();
    if(test.test_increment()) cout<<"Ok"<<endl;
    else cout<<"Error"<<endl;

    // test_2.byte_sort();
    // if(test_2.test_increment()) cout<<"Ok"<<endl;
    // else cout<<"Error"<<endl;

    // test.hoares_sort();
    // if(test.test_increment()) cout<<"Ok"<<endl;
    // else cout<<"Error"<<endl;

    // test.shaker_sort();
    // if(test.test_increment()) cout<<"Ok"<<endl;
    // else cout<<"Error"<<endl;

    // test_2.shells_sort();
    // if(test_2.test_increment()) cout<<"Ok"<<endl;
    // else cout<<"Error"<<endl;
    

    return 0;
}
