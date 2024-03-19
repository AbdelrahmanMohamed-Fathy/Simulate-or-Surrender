#pragma once
#include "Node.h"
#include "ADTs/QueueADT.h"

template<typename T>
class Queue : public QueueADT<T>
{
private:
   Node<T>* Head = NULL;
   Node<T>* Tail = NULL;
   unsigned int count = 0;
public:
   virtual bool isEmpty() const;
   
   virtual bool enqueue(const T& newEntry);

   virtual bool dequeue(T& FrontEntry);
   
   virtual bool peek(T& FrontEntry) const;
   
   virtual ~Queue();
};