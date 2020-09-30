#include <iostream>
#include <cstring>

using namespace std;

class String
{
    char *line;
    int len;
public:
    String();
    String(char *arr);
    String(const String &obj);
   ~String();
    
    char &operator [] (int pos);
    String &operator + (String &obj);
    String &operator = (String &obj);

    int *table();
    int bm_search(String word);
    int kmp_search (String &obj);

    friend ostream & operator << (ostream &os, const String &obj);
};

ostream & operator << (ostream &os, const String &obj)
{
    for(int i=0; i<obj.len; i++)
    {
        os<<obj.line[i];
    }
    return os;
}

String :: String()
{
    line = nullptr;
    len = 0;
}

String :: String(char *arr)
{
    int arr_len = strlen(arr);
    len = arr_len;
    line = new char [len+1]; // may be error cause len+1 }} change to len
    line[len] = '\n';
    for(int i=0; i<len; i++)
    {
        line[i] = arr[i];
    }
}

String ::~String()
{
    delete[] line;
}

String :: String(const String &obj)
{
    len = obj.len;
    line = new char [len+1];
    line[len] = '\n';
    for(int i=0; i<len; i++)
    {
        line[i] = obj.line[i];
    }
}

char& String ::operator [] (int pos)
{
    return line[pos];
}

String& String :: operator + (String &obj)
{
    char *space = new char [len];
    for(int i=0; i<len; i++)
    {
        space[i] = line[i];
    }
    int new_len = len+obj.len;
    delete[] line;
    line = new char [new_len];
    line[new_len] = '\n';
    for(int i=0; i<len; i++)
    {
        line[i] = space[i];
    }
    int i=len, j=0;
    while(i<new_len)
    {
        line[i] = obj.line[j];
        i++;
        j++;
    }
    len = new_len;

    delete[] space;
    return *this;
}

String& String :: operator = (String &obj)
{
    delete[] line;
    len = obj.len;
    line = new char [len+1];
    line[len] = '\n';
    for(int i=0; i<len; i++)
    {
        line[i] = obj.line[i];
    }
    return *this;
}

int* String :: table() 
{
    int *mass= new int [len];

    for(int i=1; i<len; i++)
    {
        mass[len-i-1]=i;
        for(int j=len-i; j<len-1; j++)
        {
            if(line[len-i-1]==line[j] && i!=1) mass[len-i-1]=mass[len-i];
        }
    }
    for(int i=0; i<len-1; i++)
    {
        if(line[i]==line[len-1])
        {
            mass[len-1]=mass[i];
            break;
        }
        else mass[len-1]=1 + mass[0];
    }

    return mass;
}

int String :: bm_search(String word)
{
    int *tablew = word.table();
    int space = 0;
    for(int i=word.len-1; i<=len; )
    {
        for(int j=1; j<word.len; j++){
            if(line[i-j+1]!=word[word.len-j])
            {
                int t=0;
                for(int k=0; k<word.len; k++)
                {
                    if(line[i-j+1]==word[k])
                    {
                        t = tablew[k];
                        break;
                    }
                    else t=0;
                }
                if(t) 
                {
                    i = i + t;
                    break;
                }
                else i = i+word.len-1;
                break;
            }
            else if((word.len-j-1)==0)
            {
                space = i-word.len+1;
                return space;
            }
        }
    }
    return space;
}

int main()
{
    
    char a[] = "na dwore drowar, na trawe drowa";
    char b[] = "drowa";

    String arr_1 = a;
    String arr_2 = b;

//  Example for bm_search();
    // int pos = arr_1.bm_search(arr_2);
    // for(int i=0; i<strlen(b); i++)
    // {
    //     arr_1[pos+i] = ' ';
    // }
    // cout<<arr_1<<endl;


    return 0;
}
