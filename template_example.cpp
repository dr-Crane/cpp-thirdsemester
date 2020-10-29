#include <iostream>
#include <cstring>

using namespace std;
 
template <typename T>
class Stack
{
private:
    T *stackPtr; // указатель на стек
    int size; // размер стека
    T top; // вершина стека
public:
    Stack(int = 10);// по умолчанию размер стека равен 10 элементам
    ~Stack(); // деструктор
    bool push(const T  ); // поместить элемент в стек
    bool pop(); // удалить из стека элемент
    void printStack();
};
 
 // конструктор
template <typename T>
Stack<T>::Stack(int s)
{
    size = s;
    stackPtr = new T[size]; 
    top = -1; // значение -1 говорит о том, что стек пуст
}
 
// деструктор
template <typename T>
Stack<T>::~Stack()
{
    delete [] stackPtr; 
}
 
template <typename T>
bool Stack<T>::push(const T value)
{
    if (top == size - 1)
        return false; // стек полон
 
    top++;
    stackPtr[top] = value; 
 
    return true; 
}
 
template <typename T>
bool Stack<T>::pop()
{
    if (top == - 1)
        return false; // стек пуст
 
    stackPtr[top] = 0; // удаляем элемент из стека
    top--;
 
    return true; // успешное выполнение операции
}

template <typename T>
void Stack<T>::printStack()
{
    for (int i = size - 1; i >= 0; i--)
        cout << "|" << setw(4) << stackPtr[i] << endl;
}

int main()
{
    Stack <int> myStack(5);
 
    // заполняем стек
    cout << "Push elements in stack :";
    int current = 0;
    while (current++ != 5)
    {
        int temp;
        cin >> temp;
        myStack.push(temp);
    }
 
    myStack.printStack(); // вывод стека на экран
 
    cout << "\nRemove them :\n";
 
    myStack.pop(); // удаляем элемент из стека
    myStack.pop(); // удаляем элемент из стека
    myStack.printStack(); // вывод стека на экран
 
    return 0;
}
 

 
