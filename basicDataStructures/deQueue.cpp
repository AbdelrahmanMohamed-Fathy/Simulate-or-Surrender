#include "deQueue.h"

template  <typename T>
bool deQueue<T>::isEmpty() const
{
	return(!Head);
}

template<typename T>
int deQueue<T>::getCount()
{
	return count;
}

template<typename T>
bool deQueue<T>::enqueueFront(const T& frontentry)
{
	doublyNode<T>* front = new doublyNode<T>;

	if (!front)
	{
		return false;
	}
	front->data = frontentry;

	if (isEmpty())
	{
		Head = front;
		Tail = front;
		count++;
		return true;
	}
	front->next = Head;
	Head->prev = front;
	Head = front;
	count++;
	return true;
}

template<typename T>
bool deQueue<T>::enqueueBack(const T &backentry)
{
	doublyNode<T>* back = new doublyNode<T>;
	if (!back)
	{
		return false;
	}
	back->data = backentry;
	if (isEmpty())
	{
		Head = back;
		Tail = back;
		count++;
		return true;
	}
	Tail->next = back;
	back->prev = Tail;
	Tail = back;
	count++;
	return true;
}

template<typename T>
bool deQueue<T>::dequeuefront(T& front)
{
	if (isEmpty())
	{
		return false;
	}
	front = Head->data;
	doublyNode<T>* delf = Head;
	Head = Head->next;
	Head->prev = nullptr;
	delete delf;
	count--;
	return true;
}

template<typename T>
bool deQueue<T>::dequeueback(T& back)
{
	if (!Tail)
	{
		return false;
	}
	back = Tail->data;
	doublyNode<T>* delb = Tail;
	Tail = Tail->prev;
	Tail->next = nullptr;
	delete delb;
	count--;
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
void deQueue<T>::print()
{	
	doublyNode <T>* ptr = Head;
	cout << "[";
	if (ptr)
	{
		cout << ptr->data;
		ptr = ptr->next;
	}

	while (ptr) {
		cout << "," << ptr->data;
		ptr = ptr->next;
	}

	cout << "]" << endl;
}

template<typename T>
bool deQueue<T>::enqueue(const T& newEntry)
{
	return enqueueBack(newEntry);
}

template<typename T>
bool deQueue<T>::dequeue(T& FrontEntry)
{
	return dequeuefront(FrontEntry);
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