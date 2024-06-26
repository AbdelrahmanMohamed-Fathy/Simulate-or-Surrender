#include "priQueue.h"

template<typename T>
bool priQueue<T>::enqueue(const T& data,double priority)
{
    priNode<T>* newNode = new priNode<T>;
    if (!newNode) return false;
    newNode->data = data;
    newNode->priority = priority;

    if (head == nullptr || (priority > head->priority)) {

        newNode->next = head;
        head = newNode;
        count++;
        return true;
    }

    priNode<T>* current = head;
    while (current->next && (priority <= (current->next)->priority)) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
    count++;
    return true;
}

template<typename T>
int priQueue<T>::getCount()
{
    return count;
}

template<typename T>
bool priQueue<T>::dequeue(T& topEntry, double& pri)
{
    if (isEmpty())
        return false;

    topEntry = head->data;
    pri = head->priority;
    priNode<T>* temp = head;
    head = head->next;
    delete temp;
    count--;
    return true;
}

template<typename T>
bool priQueue<T>::peek(T& topEntry, double& pri)
{
    if (isEmpty())
        return false;

    topEntry = head->data;
    pri = head->priority;
    return true;
}

template<typename T>
bool priQueue<T>::isEmpty() const
{
    return (!head);
}

template<typename T>
void priQueue<T>::print()
{
    priNode <T>* ptr = head;
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

template<typename T>
priQueue<T>::~priQueue()
{
    T tmp;
    double p;
    while (dequeue(tmp, p));
}
