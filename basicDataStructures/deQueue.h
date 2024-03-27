#pragma once
#include "nodes/doublyNode.h"

template<typename T>
class deQueue
{
private:
	doublyNode<T>* Head = nullptr;
	doublyNode<T>* Tail = nullptr;
	unsigned int count = 0;
public:
	virtual bool isEmpty() const;

	int getCount();

	virtual bool enqueueFront(const T& newEntry);

	virtual bool enqueueBack(const T& newEntry);

	virtual bool dequeuefront(T& FrontEntry);

	virtual bool dequeueback(T& backEntry);

	virtual bool peek(T& FrontEntry) const;
	
	virtual void print();

	virtual ~deQueue();
};;
