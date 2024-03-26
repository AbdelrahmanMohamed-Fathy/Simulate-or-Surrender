#include "queue.h"

template<typename T>
bool queue<T>::isEmpty() const
{
    return (!Head);
}

template <typename T>
bool queue<T>::enqueue(const T &newEntry)
{
    node<T>* TempHolder = new node<T>;
    if (!TempHolder) return false;
    TempHolder->data = newEntry;
    if(isEmpty())
    {
        Head = TempHolder;
        return true;
    }
    Tail->next = TempHolder;
    Tail = TempHolder;
    count++;
    return true
}

template <typename T>
bool queue<T>::dequeue(T &FrontEntry)
{
    if (isEmpty())
    {
        return false;
    }
    FrontEntry = Head->data;
    node<T>* TempHolder = Head;
    Head = Head->next;
    delete TempHolder;
    count--;
    return true;
}

template <typename T>
bool queue<T>::peek(T &FrontEntry) const
{
    if (isEmpty())
    {
        return false;
    }
    FrontEntry = Head->data;
    return true;
}

template <typename T>
queue<T>::~queue()
{
    while(Head)
    {
        node<T>* TempHolder = Head->next;
        delete Head;
        Head = TempHolder;
    }
}