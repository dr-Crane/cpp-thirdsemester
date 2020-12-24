#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>

using namespace std;

class bool_vec
{
    unsigned int * line;
    int cells;
    int len;
public:
    bool_vec(int a=1);
    bool_vec(char *str);
    bool_vec(string str);
    bool_vec(const bool_vec& obj);
    ~bool_vec();

    void set_1 (int pos);
    void set_0 (int pos);
    bool operator [] (int pos);
    bool_vec& operator = (bool_vec obj);
    void operator = (string str);
    bool_vec operator | (bool_vec obj);
    bool_vec operator ~ ();
    bool operator == (bool_vec obj);
    bool_vec operator & (bool_vec obj);
    int weight ();

    friend ostream& operator <<(ostream &os, bool_vec &obj);
    friend istream& operator >>(istream &is, bool_vec &obj);
};

class bool_matrix
{
    bool_vec * line;
    int row;
    int col;
public:
    bool_matrix(int a = 1, int b = 1);
    bool_matrix(bool_matrix &obj);

    bool_vec &operator [] (int pos);
    bool_matrix &operator = (bool_matrix & obj);
    void topological_sort ();
 

    friend ostream &operator << (ostream &os, bool_matrix& obj);
    friend void change_line (string str, int i, bool_matrix &a);
};

bool_vec& bool_vec :: operator = (bool_vec obj)
{
    if(&obj==this) return *this;
    len = obj.len;
    cells = obj.cells;
    delete[] line;
    line = new unsigned int [obj.cells];
    for(int i=0 ;i<cells; i++)
    {
        line[i] = obj.line[i];
    }
    return *this;
}

bool_vec :: bool_vec (int a)
{
    len = a;
    cells = (len-1)/32+1;
    line = new unsigned int [cells];
}

bool_vec :: bool_vec (string str)
{
    len = str.length();
    cells = (len-1)/32+1;
    line = new unsigned int [cells];
    int num = 0;

    for(int i=0; i<cells; i++)
    {
        unsigned int mask = 1;
        mask = mask << 31;
        for(int j=0; j<32&&(num<len); j++)
        {
            if(str[num]!='0') 
            {
                line[i] = line[i]|mask;
            }
            mask = mask>>1;
            num++;
        }
    }
}

bool_vec :: ~bool_vec()
{
    delete[] line;
}

ostream& operator <<(ostream &os, bool_vec &obj)
{
    int num = 0;
    for(int i=0; i<obj.cells; i++)
    {
        unsigned int mask = 1;
        mask = mask<<31;
        for(int j=0; j<32&&(num<obj.len); j++)
        {
            if((obj.line[i]|mask)==obj.line[i])
            {
                os<<"1";
            }
            else 
            {
                os<<"0";
            }
            mask = mask>>1;
            num++;
        }
    }

    return os;
}

istream& operator >>(istream &is, bool_vec &obj)
{
    delete [] obj.line;
    string space;
    cin>>space;
    obj.len = space.length();
    obj.cells = (obj.len-1)/32+1;
    obj.line = new unsigned int [obj.cells];
    int num = 0;

    for(int i=0; i<obj.cells; i++)
    {
        unsigned int mask = 1;
        mask = mask << 31;
        for(int j=0; j<32&&(num<obj.len); j++)
        {
            if(space[num]!='0') 
            {
                obj.line[i] = obj.line[i]|mask;
            }
            mask = mask>>1;
            num++;
        }
    }


    return is;
}

ostream &operator << (ostream &os, bool_matrix& obj)
{
    for(int i=0; i<obj.col; i++)
    {
        os<<obj.line[i]<<endl;
    }
    return os;
}

bool bool_vec :: operator == (bool_vec obj)
{
    if(len!=len) return false;
    for(int i=0; i<cells; i++)
    {
        if(line[i]^obj.line[i]) return false; 
    }
    return true;
}

bool_vec :: bool_vec(char *str)
{
    len = strlen(str);
    cells = (len-1)/32+1;
    line = new unsigned int [cells];
    int num = 0;

    for(int i=0; i<cells; i++)
    {
        unsigned int mask = 1;
        mask = mask << 31;
        for(int j=0; j<32&&(num<len); j++)
        {
            if(str[num]!='0') 
            {
                line[i] = line[i]|mask;
            }
            mask = mask>>1;
            num++;
        }
    }

}

bool_vec :: bool_vec(const bool_vec& obj)
{
    len = obj.len;
    cells = obj.cells;
    line = new unsigned int [cells];
    for(int i=0; i<cells; i++)
    {
        line[i] = obj.line[i];
    }
}

void bool_vec :: set_1 (int pos)
{
    unsigned int mask = 1;
    int mod = pos%32 - 1;
    mask = mask<<(31-mod);
    int k = pos/32;
    line[k] = line[k]|mask;
}

void bool_vec :: set_0 (int pos)
{
    unsigned int mask = 1;
    int mod = pos%32 - 1;
    mask = mask<<(31-mod);
    mask = ~mask;
    int k = pos/32;
    line[k] = line[k]&mask;
}

bool bool_vec :: operator [] (int pos)
{
    if(pos>len||pos<0)
    {
        cout<<"error: 1"<<endl;
        exit(1);
    }
    if(pos>32)
    {
        pos = pos%32;
    }
    unsigned int mask = 1;
    mask = mask<<(32-pos);
    int cell = (pos-1)/32;
    unsigned int result = mask|line[cell];
    if(line[cell]==result)
    {
        return true;
    }
    
    return false;
} 

bool_vec bool_vec :: operator | (bool_vec obj)
{
    if(len!=obj.len)
    {
        cout<<"error"<<endl;
        exit(0);
    }
    bool_vec result(len);
    for(int i=0; i<cells; i++)
    {
        result.line[i] = line[i]|obj.line[i];
    }
    return result;

}

bool_vec bool_vec :: operator & (bool_vec obj)
{
    if(len!=obj.len)
    {
        cout<<"error"<<endl;
        exit(0);
    }
    bool_vec result(len);
    for(int i=0; i<cells; i++)
    {
        result.line[i] = line[i]&obj.line[i];
    }
    return result;
}

bool_vec bool_vec :: operator ~ ()
{
    for(int i=0; i<cells-1; i++)
    {
        line[i] = ~line[i];
    }
    int k = (cells-1)*32-len;
    k = k*(-1);
    unsigned int mask = 1;
    mask = mask<<31;
    for(int i=0; i<k; i++)
    {
        line[cells-1] = line[cells-1]^mask;
        mask = mask>>1;
    }

    return *this;
}

bool_matrix :: bool_matrix (int a, int b)
{
    row = a;
    col = b;
    line = new bool_vec [row];

    // cout<<"Please, fill the matrix:"<<endl;
    // for(int i=0; i<row; i++)
    // {
    //     cin>>line[i];
    // }
}

int bool_vec :: weight ()
{
    int num = 0;

    for(int i=0; i<cells; i++)
    {
        while(line[i])
        {
            line[i] = line[i]&(line[i]-1);
            num++;
        }
    }

    return num;
}

bool cheker (int *line, int pos, int row)
{
    for(int i=0; i<row; i++)
    {
        if(pos==line[i]) return true;
    }
    return false;
}

void bool_matrix :: topological_sort()
{
    bool_vec deleter(col);
    bool_vec vec_1(col);

    cout<<endl;

    int *empty = new  int [row];
    if(!empty) return ;

    for(int i=0; i<row; i++)
    {
        empty[i] = -1;
    }
    int num = 0;
    int flag = 0;

    while(num<col)
    {
        flag = 0;
        vec_1 = deleter;
        for(int i=0; i<row; i++)
        {
            if(cheker(empty, i, row)) continue;
            vec_1 = vec_1|line[i];
        }
        vec_1 = ~vec_1;
        for(int i=0; i<col; i++)
        {
            if(cheker(empty, i, row)) continue;
            if(vec_1[i+1])
            {
                flag = 1;
                cout<<i+1<<" ";
                empty[num] = i;
                num++;
            }
        }
        if(flag==0)
        {
            cout<<"there's cicle"<<endl;
            exit(0);
        }
    }

    cout<<endl;

}

void bool_vec :: operator = (string str)
{
    delete[] line;
    len = str.length();
    cells = (len-1)/32+1;
    line = new unsigned int [cells];

    int num = 0;
    for(int i=0; i<cells; i++)
    {
        unsigned int mask = 1;
        mask = mask << 31;
        for(int j=0; j<32&&(num<len); j++)
        {
            if(str[num]!='0') 
            {
                line[i] = line[i]|mask;
            }
            mask = mask>>1;
            num++;
        }
    }
}

void change_line (string str, int i, bool_matrix &a)
{
    a.line[i] = str;
}

int main()
{
    ifstream vec("graph.txt");
    if(!vec) return -1;

    std:: vector <string> line;

    string str;
    while(getline(vec, str))
    {
        line.push_back(str);
    }

    str = line[0];
    bool_matrix a(line.size(), str.length());

    for(int i=0; i<line.size(); i++)
    {
        cout<<line[i]<<endl;
    }

    for(int i=0; i<line.size(); i++)
    {
        str = line[i];
        change_line(str, i, a);
    }

    
    
    a.topological_sort();

    vec.close();


    return 0;
}
