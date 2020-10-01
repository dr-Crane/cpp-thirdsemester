#include <iostream>
#include <cstring>

using std::cout;
using std::cin;
using std::ostream;
using std::endl;

class route
{
    int amount;
    int *trip;
    public:
    route(int a=0)
    {
        amount = a;
        trip = new int [amount];
        for(int i=0; i<amount; i++)
        {
            trip[i] = i;
        }
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
    void make_shift(int amount);
    int get_cost(int **matrix, int amount);
    void operator = (const route &obj)
    {
        amount = obj.amount;
        trip = new int [amount];
        for(int i=0; i<amount; i++)
        {
            trip[i] = obj.trip[i];
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

void route::make_shift(int amount)
{
    int space = 0;

    int i = amount-2;
    int j = amount-1;
    while(i!=0)
    {
        if(trip[i]<trip[i+1]) break;
        i--;
    }
    while(i<j)
    {
        if(trip[i]<trip[j]) break;
        j--;
    }
    space = trip[i];
    trip[i] = trip[j];
    trip[j] = space;
    int low = i+1;
    int high = amount-1;
    while(low<high)
    {
        space = trip[low];
        trip[low] = trip[high];
        trip[high] = space;
        low++;
        high--;
    }
}

int route:: get_cost(int **matrix, int amount)
{
    int result = 0;
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

int **make_matrix(int amount)
{
    int **matrix = new int* [amount];
    for(int i=0; i<amount; i++)
    {
        matrix[i] = new int [amount];
    }
    return matrix;
}

void fill_matrix(int **matrix, int amount)
{
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
}

void print_matrix(int **matrix, int amount)
{
    for(int i=0; i<amount; i++)
    {
        for(int j=0; j<amount; j++)
        {
            cout<<matrix[i][j]<<"\t";
        }
        cout<<endl;
    }
}

void true_solve(int amount)
{
    int **matrix = make_matrix(amount);
    fill_matrix(matrix, amount);
    print_matrix(matrix, amount);
    int range =1;
    for(int i=1; i<amount; i++)
    {
        range = range*i;
    }
    route lowest = amount;
    route space = amount;

    int cost = lowest.get_cost(matrix, amount);
    int num = 0;
    cout<<space<<"   = "<<cost<<endl;

    for(int i=0; i<range-1; i++)
    {
        space.make_shift(amount);
        num = space.get_cost(matrix, amount);
        cout<<space<<"   = "<<num<<endl;
        if(num<cost)
        {
            cost = num;
            lowest = space;
        }
    }
    cout<<"\n\n"<<"Optimal trip:\n"<<lowest<<"   = "<<cost<<endl;

    delete[] matrix;
}

int main()
{
    int amount=0;

    cout<<"Amount of the cities: ";
    cin>>amount;
    if((amount==0)||(amount==1)||(amount==2)) return 1;

    true_solve(amount);

    return 0;
}
