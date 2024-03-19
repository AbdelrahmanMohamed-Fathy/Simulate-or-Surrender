#pragma once
#include"Queue.h"

template<typename T>
class DEQueue : public Queue<T>
{
public:
	virtual bool enqueue(const T& newEntry);

	virtual bool dequeue(T& FrontEntry, T& BackEntry);

	virtual ~DEQueue();
};
