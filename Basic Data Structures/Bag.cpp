#include "Bag.h"

template<typename T>
Bag<T>::Bag()
{
	for (int i = 0; i < 100; i++)
	{
		Elements[i] = nullptr;
	}
}

template<typename T>
bool Bag<T>::IsEmpty()
{
	if(count == 0)
		return true;
	return false;
}

template<typename T>
bool Bag<T>::IsFull()
{
	if (count == 100)
		return true;
	return false;
}

template<typename T>
bool Bag<T>::AddElement(T& element)
{
	if (!IsFull())
	{
		Elements[count++] = element;
		return true;
	}
	return false;
}

template<typename T>
bool Bag<T>::remove(T& element)
{
	int x = GenerateNumber(0, count);
	element = Elements[x];
	Elements[x] = Elements[count--];
}

template<typename T>
Bag<T>::~Bag()
{}