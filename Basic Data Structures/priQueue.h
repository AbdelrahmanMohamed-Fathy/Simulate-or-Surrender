#pragma once
#include "nodes/priNode.h"


//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
    priNode<T>* head = NULL;
    unsigned int count = 0;
public:
    
    bool enqueue(const T& data, int priority);

    bool dequeue(T& topEntry, int& pri);

    bool peek(T& topEntry, int& pri);

    bool isEmpty() const;

    ~priQueue();
};
