#include <iostream>

using std::cout;
using std::cin;
using std::ostream;
using std::endl;

class route
{
    int amount;
    int *trip;
public:
    route(int a=0, int *b=NULL)
    {
        amount = a;
        trip = new int [amount];
    }
    route(const route &obj)
    {
        amount = obj.amount;
        trip = new int [amount];
        for(int i=0; i<amount; i++)
        {
            trip[i] = obj.trip[i];
        }
    }
   ~route()
    {
        delete[] trip;
    }
    void operator = (int a)
    {
        amount = a;
        if(trip!=NULL)
        {
            delete[] trip;
        }
        trip = new int [amount];
    }
    void operator = (int *a)
    {
        if(trip!=NULL)
        {
            delete[] trip;
        }
        trip = new int [amount];
        for(int i=0; i<amount; i++)
        {
            trip[i] = a[i];
        }
    }

    friend ostream &operator << (ostream &os, const route &obj);
};

ostream &operator << (ostream &os, const route &obj)
{
    for(int i=0; i<obj.amount; i++)
    {
        os<<obj.trip[i];
        if((obj.amount-1)==i) break;
        os<<"->";
    }
    os<<"->0";
    return os;
}

void show_all_shifts (route *variants, int amount)
{
    int *first_trip = new int [amount];
    int range = 1;
    for(int i=1; i<amount; i++)
    {
        range = range*i;
    }
    for(int i=0; i<amount; i++)
    {
        first_trip[i] = i;
    }
    for(int i=0; i<amount; i++)
    {
        variants[0] = first_trip;
    }

    int count = 0, space = 0;
    
    while(count<(range-1))
    {
        int i = amount-2;
        int j = amount-1;
        while(i!=0)
        {
            if(first_trip[i]<first_trip[i+1]) break;
            i--;
        }
        while(i<j)
        {
            if(first_trip[i]<first_trip[j]) break;
            j--;
        }
        space = first_trip[i];
        first_trip[i] = first_trip[j];
        first_trip[j] = space;
        int low = i+1;
        int high = amount-1;
        while(low<high)
        {
            space = first_trip[low];
            first_trip[low] = first_trip[high];
            first_trip[high] = space;
            low++;
            high--;
        }
        count++;
        variants[count] = first_trip;
    }

}

int main()
{
    int amount=0;
    int range=1;

    cout<<"Amount of the cities:"<<endl;
    cin>>amount;
    if((amount==0)||(amount==1)) return 1;

    for(int i=1; i<amount; i++)
    {
        range = range*i;
    }
    cout<<"(n-1)! = "<<range<<endl;
    route *variants = new route [range];
    for(int i=0; i<range; i++)
    {
        variants[i] = amount;
    }
    
    show_all_shifts(variants, amount);


    for(int i=0; i<range; i++)
    {
        cout<<variants[i]<<endl;
    }

    delete[] variants;
    return 0;
}
