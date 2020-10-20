#include <iostream>
#include <cstring>

using namespace std;

class String
{
    char *line;
    int len;
public:
    String(int a = 0);
    String(char *arr);
    String(const String &obj);
   ~String();
    
    char &operator [] (int pos);
    String &operator += (String &obj);
    String &operator = (String &obj);
    String operator + (String &obj);
    bool operator == (String &obj);
    bool operator != (String &obj);

    int *table();
    int bm_search(String word);
    int kmp_search (String word);
    int *table_kmp();
    int remove_word(String &word, int pos);

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

String :: String(int a)
{
    len = a;
    line = new char [len+1];
    line[0] = 0;
}

String :: String(char *arr)
{
    int arr_len = strlen(arr);
    len = arr_len;
    line = new char [len+1];
    line[len] = 0;
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
    line[len] = 0;
    for(int i=0; i<len; i++)
    {
        line[i] = obj.line[i];
    }
}

char& String ::operator [] (int pos)
{
    return line[pos];
}

String& String :: operator += (String &obj)
{
    char *space = new char [len];
    for(int i=0; i<len; i++)
    {
        space[i] = line[i];
    }
    int new_len = len+obj.len;
    delete[] line;
    line = new char [new_len];
    line[new_len] = 0;
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
    if(this==&obj)
    {
        return *this;
    }
    delete[] line;
    len = obj.len;
    line = new char [len+1];
    line[len] = 0;
    for(int i=0; i<len; i++)
    {
        line[i] = obj.line[i];
    }
    return *this;
}

String String :: operator + (String &obj)
{
    int new_len = obj.len + len;
    String space(new_len);
    space.len = new_len;
    space.line[new_len] = 0;
    for(int i=0; i<len; i++)
    {
        space.line[i] = line[i];
    }
    for(int i=len, j=0; i<new_len; i++, j++)
    {
        space.line[i] = obj.line[j];
    }
    return space;
}

int* String :: table()
{
    int *table = new int [256];
    for(int i=0; i<256; i++)
    {
        table[i] = len;
    }
    for(int i=0; i<len-1; i++)
    {
        table[line[i]] = len - i - 1;
    }

    return table;
}

int String :: bm_search(String word)
{
    int i=word.len-1, j=word.len-1, k=0;
    int *bm_table = word.table();
    while(i<len)
    {
        if(j<0)
        {
            return i+1-word.len;
        }
        k = i;
        j = word.len-1;
        while(j>=0)
        {
            if(line[k]==word.line[j])
            {
                j--;
                k--;
            }
            else
            {
                i = i+bm_table[line[i]];
                j = word.len-1;
                break;
            }
        }
    }
    return -1;
}

int* String :: table_kmp()
{
    int *table = new int [len];
    table[0] = -1;
    int j=0, k=-1;
    while(j<len-1)
    {
        while(1)
        {
            if((k>=0)&&(line[j]!=line[k]))
            {
                k = table[k];
            }
            else
            {
                k++;
                j++;
                if(line[j] == line[k])
                {
                    table[j] = table[k];
                }
                else
                {
                    table[j] = k;
                }
                break;
            }
        }
    }

    return table;

}

int String :: kmp_search (String word)
{
    int *table = word.table_kmp();
    int i=0, j=0;
    while(j<word.len)
    {
        if(i>len)
        {
            return -1;// there's no any members
        }
        while(1)
        {
            if((j>=0)&&(line[i]!=word.line[j]))
            {
                j = table[j];
            }
            else
            {
                i++;
                j++;
                break;
            }
        }

    }


    return i-word.len;
}

bool String :: operator == (String &obj)
{
    if(obj.len != len ) return false;
    for(int i=0; i<len; i++)
    {
        if(line[i]!=obj.line[i]) return false;
    }
    return true;
}

bool String :: operator != (String &obj)
{
    if(obj.len != len ) return true;
    for(int i=0; i<len; i++)
    {
        if(line[i]!=obj.line[i]) return true;
    }
    return false;
}


int main()
{
    
    char a[] = "na trawe drowa, na dwore drowa";
    char b[] = "drowa";

    String arr_1 = a;
    String arr_2 = b;

//  Example for bm_search

    // int pos = arr_1.bm_search(arr_2);
    // for(int i=0; i<strlen(b); i++)
    // {
    //     arr_1[pos+i] = ' ';
    // }
    // cout<<arr_1<<endl;

//  Example for kmp_search

    // int pos_kmp = arr_1.kmp_search(arr_2);
    // for(int i=0; i<strlen(b); i++)
    // {
    //     arr_1[pos_kmp+i] = ' ';
    // }
    // cout<<arr_1<<endl;


    return 0;
}
