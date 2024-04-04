#pragma once
#include "nodes/priNode.h"


//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
private:
    priNode<T>* head = nullptr;
    unsigned int count = 0;
public:
    bool enqueue(const T& data, double priority);

    int getCount();

    bool dequeue(T& topEntry, double& pri);

    bool peek(T& topEntry, double& pri);

    bool isEmpty() const;

    void print();

    ~priQueue();
};
