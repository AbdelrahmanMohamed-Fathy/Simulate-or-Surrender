#include "Queue.h"

template<typename T>
bool Queue<T>::isEmpty() const
{
    if(Tail && Head) return false;
    return true;
}

template <typename T>
bool Queue<T>::enqueue(const T &newEntry)
{
    Node<T>* TempHolder = new Node<T>;
    if (!TempHolder) return false;
    TempHolder->Data = newEntry;
    if(isEmpty())
    {
        Head = TempHolder;
        return true;
    }
    Tail->Next = TempHolder;
    Tail = TempHolder;
    return true
}

template <typename T>
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

template <typename T>
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

template <typename T>
Queue<T>::~Queue()
{
    while(Head)
    {
        Node<T>* TempHolder = Head->Next;
        delete Head;
        Head = TempHolder;
    }
}
