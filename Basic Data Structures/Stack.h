#pragma once
#include "Node.h"
template<typename T>
class Stack
{
private:
   Node<T>* Head = NULL;
public:
   /** checks whether this stack is empty.
    @return  True if the stack is empty, or false if not. */
   virtual bool isEmpty() const;
   
   /** Adds a new entry to the top of this stack.
    @post  If the operation was successful, newEntry is at the top of the stack.
    @param newEntry  The object to be added as a new entry. */
   virtual void push(const T& newEntry);
   
   /** Copies the top item of the stack to the passed parameter and removes it from stack
    @pre  The stack is not empty.
    @post  If the operation was successful, the top item of the stack
       has been copied to TopEntry parameter.
    @return  True if the removal is successful or false if not. */
   virtual bool pop(T& TopEntry);
   
   /** Copies the top item of the stack to the passed parameter without removing it from stack
    @pre  The stack is not empty.
    @post  If the operation was successful, the top item of the stack
       has been copied to TopEntry parameter.
    @return  True if stack is not empty or false if not. */
   virtual bool peek(T& TopEntry) const;
   
   /** Destroys this stack and frees its assigned memory. */
   virtual ~Stack();
};