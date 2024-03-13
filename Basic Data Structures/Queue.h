#pragma once
#include "Node.h"
#include "../ADTs/QueueADT.h"
template<class T>
class Queue : public QueueADT<T>
{
private:
   Node<T>* Head = NULL;
   Node<T>* Tail = NULL;
public:
   virtual bool isEmpty() const;
   
   virtual bool enqueue(const T& newEntry);

   virtual bool dequeue(T& FrontEntry);
   
   virtual bool peek(T& FrontEntry) const;
   
   virtual ~Queue();
};