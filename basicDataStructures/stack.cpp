#include "stack.h"

template<typename T>
bool stack<T>::isEmpty() const
{
    return (!Head);
}

template<typename T>
int stack<T>::getCount()
{
    return count;
}

template<typename T>
bool stack<T>::push(const T & newEntry)
{
    node<T>* TempNode = new node<T>;
    if (!TempNode) return false;
    TempNode->data = newEntry;
    TempNode->next = Head;
    Head = TempNode;
    count++;
    return true;
}

template<typename T>
bool stack<T>::pop(T & TopEntry)
{
    if(isEmpty())
    {
        return false;
    }
    TopEntry = Head->data;
    node<T>* TempHolder = Head;
    Head = Head->next;
    delete TempHolder;
    count--;
    return true;
}

template <typename T>
bool stack<T>::peek(T &TopEntry) const
{
    if(isEmpty())
    {
        return false;
    }
    TopEntry = Head->data;
    return true;
}

template<typename T>
void stack<T>::print()
{
    node <T>* ptr = Head;
    cout << "[" << ptr->data;
    ptr = ptr->next;

    while (ptr) {
        cout << "," << ptr->data;
        ptr = ptr->next;
    }

    cout << "]" << endl;
}

template <typename T>
stack<T>::~stack()
{
    while(Head)
    {
        node<T>* TempHolder = Head->next;
        delete Head;
        Head = TempHolder;
    }
}
