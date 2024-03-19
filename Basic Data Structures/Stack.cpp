#include "Stack.h"

template<typename T>
bool Stack<T>::isEmpty() const
{
    if (Head) return false;
    return true;
}

template<typename T>
bool Stack<T>::push(const T & newEntry)
{
    Node<T>* TempNode = new Node<T>;
    if (!TempNode) return false;
    TempNode->Data = newEntry;
    TempNode->Next = Head;
    Head = TempNode;
    count++;
    return true
}

template<typename T>
bool Stack<T>::pop(T & TopEntry)
{
    if(isEmpty())
    {
        TopEntry=NULL;
        return false;
    }
    TopEntry = Head->Data;
    Node<T>* TempHolder = Head;
    Head = Head->Next;
    delete TempHolder;
    count--;
    return true;
}

template <typename T>
bool Stack<T>::peek(T &TopEntry) const
{
    if(isEmpty())
    {
        TopEntry=NULL;
        return false;
    }
    TopEntry = Head->Data;
    return true;
}

template <typename T>
Stack<T>::~Stack()
{
    while(Head)
    {
        Node<T>* TempHolder = Head->Next;
        delete Head;
        Head = TempHolder;
    }
}
