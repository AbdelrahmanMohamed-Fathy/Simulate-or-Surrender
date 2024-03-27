#include "deQueue.h"

template  <typename T>
bool deQueue<T>::isEmpty() const
{
	return(!Head);
}

template<typename T>
bool deQueue<T>::enqueueFront(const T& frontentry)
{
	doublyNode<T>* front = new doublyNode<T>;
	if (!front)
	{
		return false;
	}
	if (isEmpty())
	{
		Head->data = frontentry;
		return true;
	}
	front->data = frontentry;
	front->next = Head;
	Head = front;
	return true;
}

template<typename T>
bool deQueue<T>::enqueueBack(const T& backentry)
{
	doublyNode<T>* back = new doublyNode<T>;
	if (!back)
	{
		return false;
	}
	if (!Tail)
	{
		Tail->data = backentry;
		return true;
	}
	back->data = backentry;
	back->prev = Tail;
	Tail = back;
	return true;
}

template<typename T>
bool deQueue<T>::dequeuefront(T& front)
{
	if (isEmpty())
	{
		front = NULL;
		return false;
	}
	front = Head->data;
	doublyNode<T>* delf = Head;
	Head = Head->next;
	delete delf;
	return true;
}

template<typename T>
bool deQueue<T>::dequeueback(T& back)
{
	if (!Tail)
	{
		back = NULL;
		return false;
	}
	back = Tail->data;
	doublyNode<T>* delb = Tail;
	Tail = Tail->prev;
	delete delb;
	return true;
}

template<typename T>
bool deQueue<T>::peek(T& front) const
{
	if (isEmpty())
	{
		return false;
	}
	front = Head->data;
	return true;
}

template<typename T>
deQueue<T>::~deQueue()
{
	while (Head)
	{
		doublyNode<T>* TempHolder = Head->next;
		delete Head;
		Head = TempHolder;
	}
}