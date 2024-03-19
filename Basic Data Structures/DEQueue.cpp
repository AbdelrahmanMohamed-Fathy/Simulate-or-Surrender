#include "DEQueue.h"

template<typename T>
bool DEQueue<T>::dequeue(T& Front, T& Back)
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

	Front = Head->Data;
	Node<T>*delf = Head;
	Head = Head->Next;
	delete delf;

	Node<T>* temp = Head;
	while ((temp->Next)!=Tail)
	{
		temp = temp->Next;
	}
	Back = Tail->Data;
	Node<T>* dele = Tail;
	Tail = temp;
	delete dele;
	temp = nullptr;
	count -= 2;
	return true;
}

