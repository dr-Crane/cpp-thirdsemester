#include <iostream>

using namespace std;

struct leader
{
    int key;
    int st;
    trailer *list;
    leader *nextlead;
};

struct trailer
{
    leader *vert;
    trailer *next;
};

bool circle_exist (leader *& head)
{
    if(!head)
    {
        cout<<"Graph is not exist"<<endl;
        return false;
    }
    bool chek = true;
    leader * ptrLD = nullptr, *ptrTMP = head;
    leader **list;
    int size = 0;
    while(ptrTMP)
    {
        size++;
        ptrTMP->nextlead;
    }
    list = new leader* [size];
    if(!list)
    {
        cout<<"Graph is too big"<<endl;
        return false;
    }
    int count = 0;
    int x = 0;
    while(chek)
    {
        chek = false;
        ptrLD = head;
        while(ptrLD)
        {
            if(ptrLD->st == 0) // если нет входящих дуг
            {
                ptrLD->st = -1;// вычёркиваем вершину
                chek = true;
                list[x] = ptrLD;
                x++;
                trailer *ptrTR = ptrLD->list;
                while(ptrTR)
                {
                    ptrTR->vert->st--;
                    ptrTR = ptrTR->next;
                }

            }
            ptrLD = ptrLD->nextlead;
        }
    }

    count = x;
    for(x = 0; x<count; x++)
    {
        list[x]->st = 0;
    }
    for(x = 0; x<count; x++)
    {
        trailer *ptrTR = list[x]->list;
        while(ptrTR)
        {
            ptrTR->vert->st++;
            ptrTR = ptrTR->next;
        }
    }

    delete[] list;

    if(size==count) return false;
    return true;



}



int main()
{
    
}
