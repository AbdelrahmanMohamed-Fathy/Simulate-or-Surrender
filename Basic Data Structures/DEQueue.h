#pragma once
#include"Queue.h"

template<typename T>
class DEQueue : public Queue<T>
{
public:
	virtual bool dequeue(T& FrontEntry, T& BackEntry) override;
};
