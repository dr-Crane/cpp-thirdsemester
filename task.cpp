#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
struct Trailer;
struct Lider
{
    int key;        //   Номер вершины
    int count;      //   (     ) Число предшественников число входящих дуг
    Lider   *nx;    //             (Lider) Указатель на следующий элемент в списке вершин
    Trailer *tr;    //     RAILER (       ,    указатель на Т список указателей на вершины к
                    //которым ведут исходящие дуги       )
};
struct Trailer
{
    Lider   *ld;    //           LEADER,      указатель на вершину в списке к которой ведет
                    //        ,       TRAILER исходящая дуга из вершины к которой прикреплен
    Trailer *nx;    //       указатель на следующий элемент
};
/*
 * AddEdge ­          добавление ребра в граф
 *    : Входные параметры
 * vertexes ­      список вершин графа
 *          (vertexA,vertexB) Ребро графа определяется парой вершин
  */


void AddEdge(Lider *& vertexes, int vertexA, int vertexB)
{
    Lider *ptrA = NULL, *ptrB=NULL;
    for(ptrA = vertexes;ptrA && ptrA->key!= vertexA; ptrA = ptrA->nx);
    for(ptrB = vertexes;ptrB && ptrB->key!= vertexB;ptrB = ptrB->nx);
    bool setEdge = true;
    if(ptrA && ptrB){
     Trailer * trTmp = ptrA->tr;
     for(Trailer * trTmp = ptrA->tr;trTmp && trTmp->ld!=ptrB;trTmp = trTmp->nx);
        setEdge = (bool)trTmp;
    }
    else{
        //     ,         vertexes Создаем вершину А добавляем в голову списка
     if(!ptrA){
         ptrA = new Lider;
         ptrA->key = vertexA;
         ptrA->count = 0;
         ptrA->nx = NULL;
         ptrA->tr = NULL;
         
         ptrA->nx = vertexes;
         vertexes = ptrA;
    }
     //    B ,         vertexes Создаем вершину добавляем в голову списка
     if(!ptrB){
         ptrB = new Lider;
         ptrB->key = vertexB;
         ptrB->count = 0;
         ptrB->nx = NULL;
         ptrB->tr = NULL;
         ptrB->nx = vertexes;
         vertexes = ptrB;}
      
    }
     //     Устанавливаем ребро
    if(setEdge){
        ptrB->count++;
        Trailer* elemTr = new Trailer;
        elemTr->ld = ptrB;
        elemTr->nx = ptrA->tr;
        ptrA->tr = elemTr;            
    }
}



/*
 * PrintGraph ­    Вывод графа
 *    : Входные параметры
 * vertexes ­      список вершин графа
 * 
 */
void PrintGraph(Lider*vertexes){
    if(vertexes == NULL)
        printf("Graph is Empty");
    else
    while(vertexes){
        Trailer* trTmp = vertexes->tr;
        while(trTmp){
            printf("(%d,%d)\n",vertexes->key,trTmp->ld->key);
            trTmp = trTmp->nx;
        }
        vertexes = vertexes->nx;
    }
}
/*
 * DeleteGraph ­    удаление графа
 *    : Входные параметры
 * vertexes ­      список вершин графа
 * 
 */
void DeleteGraph(Lider*&vertexes){
    while(vertexes){
        while(vertexes->tr){
        Trailer*tmp = vertexes->tr;    
        vertexes->tr = vertexes->tr->nx;
        delete tmp;
        }
        Lider*tmp = vertexes;
        vertexes = vertexes->nx;
        delete tmp;
    }
    
}
/*
 * ExcludeEdge ­          Функция удаления ребра из графа
 *    : Входные пареметры
 * vertexes ­      список вершин графа
 *          (vertexA,vertexB) Ребро графа определяется парой вершин
 *    : Возвращаемое значение
 * true  ­    ребро удалено
 * false ­        ребро не удалено
 * 
 */
bool ExcludeEdge(Lider *& vertexes, int vertexA, int vertexB){
    Lider *ptrA = NULL, *ptrB=NULL;
    for(ptrA = vertexes;ptrA && ptrA->key != vertexA;ptrA = ptrA->nx);
    for(ptrB = vertexes;ptrB && ptrB->key!= vertexB;ptrB = ptrB->nx);
    if(ptrA && ptrA->tr && ptrB){
        if(ptrA->tr->ld == ptrB){
            Trailer * t = ptrA->tr;
            ptrA->tr = ptrA->tr->nx;
            delete t;
            ptrB->count--;
           
        } 
     else{
     Trailer * trTmp;
     for(trTmp = ptrA->tr;trTmp->nx && trTmp->nx->ld!=ptrB;trTmp = trTmp->nx);
        if(trTmp->nx){
           Trailer * t = trTmp->nx;
           trTmp->nx = trTmp->nx->nx;
           delete t;
           ptrB->count--;
         }
    }
        return true;
    }
    return false;
}
/*
 *           graph.dat Исходный граф хранится в файле
 *    ,  :  списком ребер например
 * 1 2
 * 1 3
 * 1 5
 * 4 5
 * 2 4
 * 
 */
int main(int argc, char** argv) {
    
    FILE*graphInFile = fopen("graph.dat","r");
    Lider *graph = NULL;
    int vertexA = 0, vertexB = 0;
    int k=0;
    if(graphInFile)
    {
        while(k = fscanf(graphInFile,"%d%d",&vertexA,&vertexB)> 0){
            printf("(%d,%d)\n",vertexA,vertexB);
            AddEdge(graph,vertexA,vertexB);
        }
               
        fclose(graphInFile);
        puts("Print Graph");
        PrintGraph(graph);
        ExcludeEdge(graph,1,5);
        ExcludeEdge(graph,4,5);
        ExcludeEdge(graph,5,3);
        PrintGraph(graph);
        DeleteGraph(graph);
        PrintGraph(graph);
        
    }else
        puts("File is not open");
    return 0;
}
