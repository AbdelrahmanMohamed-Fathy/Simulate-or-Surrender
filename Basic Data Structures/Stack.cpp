#include "Stack.h"

template<typename T>
bool Stack<T>::isEmpty() const
{
    if (Head) return false;
    return true;
}

template<typename T>
void Stack<T>::push(const T & newEntry)
{
    Node<T>* TempNode = new Node<T>;
    TempNode->Data = newEntry;
    TempNode->Next = Head;
    Head = TempNode;
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
