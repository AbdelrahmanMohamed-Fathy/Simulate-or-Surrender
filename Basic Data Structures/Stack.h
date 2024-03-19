#pragma once
#include "Node.h"
#include "ADTs/StackADT.h"

template<typename T>
class Stack : public StackADT<T>
{
private:
   Node<T>* Head = NULL;
   int count = 0;
public:
   virtual bool isEmpty() const;
   
   virtual bool push(const T& newEntry);
   
   virtual bool pop(T& TopEntry);
   
   virtual bool peek(T& TopEntry) const;
   
   virtual ~Stack();
};