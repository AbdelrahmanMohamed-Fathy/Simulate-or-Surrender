#include "Bag.h"

template<typename T>
bag<T>::bag()
{
	for (int i = 0; i < 100; i++)
	{
		elements[i] = nullptr;
	}
}

template<typename T>
bool bag<T>::isEmpty()
{
	if(count == 0)
		return true;
	return false;
}

template<typename T>
bool bag<T>::isFull()
{
	if (count == 100)
		return true;
	return false;
}

template<typename T>
bool bag<T>::addElement(T& element)
{
	if (!IsFull())
	{
		elements[count++] = element;
		return true;
	}
	return false;
}

template<typename T>
bool bag<T>::remove(T& element)
{
	int x = generateNumber(0, count);
	element = elements[x];
	elements[x] = elements[count--];
}

template<typename T>
bag<T>::~bag()
{}