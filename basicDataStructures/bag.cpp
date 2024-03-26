#include "Bag.h"

template<typename T>
bag<T>::bag()
{
	for (int i = 0; i < 100; i++)
	{
		Elements[i] = nullptr;
	}
}

template<typename T>
bool bag<T>::IsEmpty()
{
	if(count == 0)
		return true;
	return false;
}

template<typename T>
bool bag<T>::IsFull()
{
	if (count == 100)
		return true;
	return false;
}

template<typename T>
bool bag<T>::AddElement(T& element)
{
	if (!IsFull())
	{
		Elements[count++] = element;
		return true;
	}
	return false;
}

template<typename T>
bool bag<T>::remove(T& element)
{
	int x = generateNumber(0, count);
	element = Elements[x];
	Elements[x] = Elements[count--];
}

template<typename T>
bag<T>::~bag()
{}