#pragma once
#include "nodes/node.h"
#include "ADTs/StackADT.h"

template<typename T>
class stack : public StackADT<T>
{
private:
   node<T>* Head = nullptr;
   unsigned int count = 0;
public:
   virtual bool isEmpty() const;

   int getCount();
   
   virtual bool push(const T& newEntry);
   
   virtual bool pop(T& TopEntry);
   
   virtual bool peek(T& TopEntry) const;

   virtual void print();
   
   virtual ~stack();
};