#pragma once
#include "nodes/node.h"
#include "ADTs/QueueADT.h"

template<typename T>
class queue : public QueueADT<T>
{
private:
	node<T>* Head = nullptr;
	node<T>* Tail = nullptr;
	unsigned int count = 0;
public:
	virtual bool isEmpty() const;
	
	virtual bool enqueue(const T& newEntry);
	
	virtual bool dequeue(T& FrontEntry);
	
	virtual bool peek(T& FrontEntry) const;
	
	virtual ~queue();
};