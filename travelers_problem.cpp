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
        if(trip!=NULL)
        {
            delete[] trip;
        }
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
    friend int get_cost(int **matrix, int amount, route obj);
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

int get_cost(int **matrix, int amount, route obj)
{
    int result = 0;
    int *trip = new int [amount];
    for(int i=0; i<amount; i++)
    {
        trip[i] = obj.trip[i];
    }
    int i=0, j=0, m=0;
    while(m<amount)
    {
        i = trip[m];
        j = trip[m+1];
        result += matrix[i][j];
        m++;
    }
    result += matrix[j][0];

    return result;
}

int main()
{
    int amount=0;
    int range=1;

    cout<<"Amount of the cities: ";
    cin>>amount;
    if((amount==0)||(amount==1)) return 1;


    int **matrix = new int* [amount];
    for(int i=0; i<amount; i++)
    {
        matrix[i] = new int [amount];
    }

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


    cout<<"Costs of trips:"<<endl;
    int space=0, m=0, n=0;
    while(m<amount)
    {
        n = 0;
        while(n<amount)
        {
            if(m==n)
            {
                matrix[m][n]=0;
                n++;
                continue;
            }
            cout<<m<<"->"<<n<<"  = ";
            cin>>space;
            matrix[m][n] = space;
            n++;
        }
        m++;
    }

    for(int i=0; i<amount; i++)
    {
        for(int j=0; j<amount; j++)
        {
            cout<<matrix[i][j]<<"\t";
        }
        cout<<endl;
    }

    show_all_shifts(variants, amount);

    int cost = 0;
    route lowest = variants[0];
    int num = get_cost(matrix, amount, variants[0]);
    for(int i=0; i<range; i++)
    {
        cout<<variants[i]<<"  =   ";
        cost = get_cost(matrix, amount, variants[i]);
        if(cost<num)
        {
            num = cost;
            lowest = variants[i];
        }
        cout<<cost<<endl;
    }

    cout<<"\n"<<"optimal trip is: "<<lowest<<"  cost  =   "<<num<<endl;

    delete[] variants;
    for(int i=0; i<amount; i++)
    {
        delete[] matrix[i];
    }
    return 0;
}
