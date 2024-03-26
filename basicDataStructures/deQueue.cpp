#include "deQueue.h"

template<typename T>
bool deQueue<T>::dequeue(T& Front, T& Back)
{
	if (isEmpty())
	{
		Front = NULL;
		Back = NULL;
		return false;
	}

	if (Head == Tail)
	{
		Front = NULL;
		Back = NULL;
		return false;
	}

	Front = Head->data;
	node<T>*delf = Head;
	Head = Head->next;
	delete delf;

	node<T>* temp = Head;
	while ((temp->next)!=Tail)
	{
		temp = temp->next;
	}
	Back = Tail->data;
	node<T>* dele = Tail;
	Tail = temp;
	delete dele;
	temp = nullptr;
	count -= 2;
	return true;
}

