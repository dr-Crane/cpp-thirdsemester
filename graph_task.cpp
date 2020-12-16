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

bool circle_exist (leader *vx, leader *vy, leader *vz)
{
    if(!vx||!vy||!vz)
    {
        cout<<"Vertex doesn't exist"<<endl;
        return false;
    }

    bool chek = false;

    leader *ptrVX = vx;
    leader *ptrVY = vy;
    leader *ptrVZ = vz;

    if(ptrVX->st==0&&ptrVY->st==0&&ptrVZ->st==0)
    {
        return false;
    }

    leader *tmpVX = ptrVX;

    while(tmpVX)
    {
        trailer *list_1 = tmpVX->list;
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
    }

    return false;

}



int main()
{
    
    

}
