#pragma once
#include"Queue.h"

template<typename T>
class DEQueue : public Queue<T>
{
public:
	virtual bool isEmpty() const;

	virtual bool enqueue(const T& newEntry);

	virtual bool dequeue(T& FrontEntry, T& BackEntry);

	virtual bool peek(T& FrontEntry) const;

	virtual ~DEQueue();
};
