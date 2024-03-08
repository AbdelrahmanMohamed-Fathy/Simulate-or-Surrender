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
    Node<T>* TempHolder = new Node<T>
    TempHolder->Data = newEntry;
    if(isEmpty())
    {
        Head=TempHolder;
        return;
    }
    
}

template <class T>
bool Queue<T>::dequeue(T &FrontEntry)
{
    return false;
}

template <class T>
bool Queue<T>::peek(T &FrontEntry) const
{
    return false;
}

template <class T>
Queue<T>::~Queue()
{
}
