#pragma once
#include "Node.h"
template<class T>
class Queue
{
private:
   Node<T>* Head = NULL;
   Node<T>* Tail = NULL;
public:
   /** Sees whether this queue is empty.
    @return  True if the queue is empty, or false if not. */
   virtual bool isEmpty() const;
   
   /** Adds a new entry to the back of this queue.
    @post  If the operation was successful, newEntry is at the
       back of the queue.
    @param newEntry  The object to be added as a new entry. */
   virtual void enqueue(const T& newEntry);
   
   /** Copies the front item of the queue to the passed parameter and removes it from queue
    @post  If the operation was successful, the front of the queue
       would be copied to FrontEntry parameter and removed from the queue.
    @return  True if the removal is successful or false if not. */
   virtual bool dequeue(T& FrontEntry);
   
   /** Copies the front item of the queue to the passed parameter without removing it from queue
    @pre  The queue is not empty.
    @post  The front of the queue has been copied to FrontEntry param , and the
       queue is unchanged.
    @return  The front of the queue. */
   virtual bool peek(T& FrontEntry) const;
   
   /** Destroys this queue and frees its memory. */
   virtual ~Queue();
};