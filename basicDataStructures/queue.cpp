#include "queue.h"

template<typename T>
bool queue<T>::isEmpty() const
{
    return (!Head);
}

template<typename T>
int queue<T>::getCount()
{
    return count;
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
        Tail = TempHolder;
        count++;
        return true;
    }
    Tail->next = TempHolder;
    Tail = TempHolder;
    count++;
    return true;
}

template <typename T>
bool queue<T>::dequeue(T &FrontEntry)
{
    if (isEmpty())
    {
        return false;
    }
    FrontEntry = Head->data;
    if (!(Head->next))
    {
        delete Head;
        Head = nullptr;
        Tail = nullptr;
        count--;
        return true;
    }
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

template<typename T>
void queue<T>::print()
{
    node <T>* ptr = Head;
    cout << "[";
    if (ptr)
    {
        cout << ptr->data;
        ptr = ptr->next;
    }

    while (ptr) {
        cout << "," << ptr->data;
        ptr = ptr->next;
    }

    cout << "]" << endl;
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
