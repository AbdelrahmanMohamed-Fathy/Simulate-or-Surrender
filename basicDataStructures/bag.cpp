#include "Bag.h"

template<typename T>
bag<T>::bag()
{
	for (int i = 0; i < 400; i++)
	{
		elements[i] = nullptr;
	}
}

template<typename T>
int bag<T>::getCount()
{
	return count;
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
	if (count == 400)
		return true;
	return false;
}

template<typename T>
bool bag<T>::addElement(T& element)
{
	if (!isFull())
	{
		elements[count++] = &element;
		return true;
	}
	return false;
}

template<typename T>
bool bag<T>::remove(T& element)
{
	if (isEmpty())
		return false;
	int x = generateNumber(0, count);
	element = *elements[x];
	elements[x] = elements[count--];
	return true;
}

template<typename T>
void bag<T>::print()
{
	cout << "[";
	if (elements[0])
		cout << *elements[0];

	for (int i = 1; i < count; i++) {
		cout << ","  << *elements[i];
	}
	cout << "]" << endl;
}

template<typename T>
bag<T>::~bag()
{}