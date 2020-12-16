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

    if(ptrVX->st==0||ptrVY->st==0||ptrVZ->st==0)
    {
        return false;
    }

    leader *tmp = ptrVX;
    if(tmp->list->vert->list->vert == ptrVX) return true;
    if(tmp->list->vert->list->vert->list->vert == ptrVX) return true;

    if(tmp->list->vert->st==2)
    {
        if(tmp->list->next->vert == ptrVX) return true;
        if(tmp->list->next->vert->list->vert == ptrVX) return true;
    }

    return false;

}



int main()
{
    
}
