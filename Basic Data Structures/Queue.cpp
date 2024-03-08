#include "Queue.h"

template<class T>
bool Queue<T>::isEmpty() const
{
    if(Tail && Head) return false;
    return true;
}

template <class T>
void Queue<T>::enqueue(const T &newEntry)
{
    Node<T>* TempHolder = new Node<T>;
    TempHolder->Data = newEntry;
    if(isEmpty())
    {
        Head = TempHolder;
        return;
    }
    Tail->Next = TempHolder;
    Tail = TempHolder;
}

template <class T>
bool Queue<T>::dequeue(T &FrontEntry)
{
    if (isEmpty())
    {
        FrontEntry = NULL;
        return false;
    }
    FrontEntry = Head->Data;
    Node<T>* TempHolder = Head;
    Head = Head->Next;
    delete TempHolder;
    return true;
}

template <class T>
bool Queue<T>::peek(T &FrontEntry) const
{
    if (isEmpty())
    {
        FrontEntry = NULL;
        return false;
    }
    FrontEntry = Head->Data;
    return true;
}

template <class T>
Queue<T>::~Queue()
{
    while(Head)
    {
        Node<T>* TempHolder = Head->Next;
        delete Head;
        Head = TempHolder;
    }
}
