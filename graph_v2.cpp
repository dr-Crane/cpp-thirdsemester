#include <iostream>

using namespace std;
struct trailer;


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

bool circle_exist (leader *graph, int vx, int vy, int vz)
{
    if(vx<0||vy<0||vz<0) //Проверяю существование вершины
    {
        cout<<"Vertex doesn't exist"<<endl;
        return false;
    }

    bool chek = false;

    leader *space = graph;

    int num = 0;
    while(space) // Узнаю количество вершин 
    {
        num++;
        space = space->nextlead;
    }

    if(vx>num||vy>num||vz>num)// Проверяю существование вершин
    {
        return false;
    }

    leader *ptrVX = nullptr;
    leader *ptrVY = nullptr;
    leader *ptrVZ = nullptr;

    // Создаю указатели на вершины и назначаю вершину соответсвующему указателю
    for(int i=0; i<vx; i++)
    {
        ptrVX = space->nextlead;
        space = space->nextlead;
    }
    for(int i=0; i<vy; i++)
    {
        ptrVY = space->nextlead;
        space = space->nextlead;
    }    
    for(int i=0; i<vz; i++)
    {
        ptrVZ = space->nextlead;
        space = space->nextlead;
    }

    // Проверяю наличие входящих дуг, если отсутсвуют, то задача решена
    if(ptrVX->st==0||ptrVY->st==0||ptrVZ->st==0)
    {
        return false;
    }

    leader *tmpVX = ptrVX;

    trailer *list_1 = tmpVX->list;
    
    //Цикл делает обход по следующему правилу. Берём первую вершину, в последователях ищем вторую,
    //в последователях второго ищем третью, а после первую. Если цикл существует, то данный обход
    //имееи место быть.
    while(list_1)
    {
        if(list_1->vert == ptrVY || list_1->vert == ptrVZ)
        {
            leader *tmpVY = list_1->vert;
            trailer *list_2 = tmpVY->list;
            while(list_2)
            {
                if(list_2->vert == ptrVX)
                {
                    return true;
                }
                if(list_2->vert == ptrVZ)
                {
                    leader *tmpVZ = ptrVZ;
                    trailer *list_3 = tmpVZ->list;
                    while(list_3)
                    {
                        if(list_3->vert==ptrVX)
                        {
                            return true;
                        }
                        list_3 = list_3->next;
                    }
                }
                    list_2 = list_2->next;
            }
        }
        list_1 = list_1->next;
    }


    return false;

}



int main()
{
    
    

}
