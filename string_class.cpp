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

    int bm_search (String &obj);
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

int main()
{
    
    char a[] = "Hello World, it's me , again. ";
    char b[] = "Second line";
    String arr_1 = a;
    String arr_2 = b;
    cout<<arr_1<<endl;


    return 0;
}
