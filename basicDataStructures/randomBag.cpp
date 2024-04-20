#include "randomBag.h"

template<typename T>
randomBag<T>::randomBag()
{
	for (int i = 0; i < 400; i++)
	{
		elements[i] = nullptr;
	}
}

template<typename T>
int randomBag<T>::getCount()
{
	return count;
}

template<typename T>
bool randomBag<T>::isEmpty()
{
	if(count == 0)
		return true;
	return false;
}

template<typename T>
bool randomBag<T>::isFull()
{
	if (count == 400)
		return true;
	return false;
}

template<typename T>
bool randomBag<T>::peek(T& element)
{
	if (isEmpty())
		return false;
	int x = generateNumber(0, count - 1);
	element = *elements[x];
	return true;
}

template<typename T>
bool randomBag<T>::addElement(const T& element)
{
	if (!isFull())
	{
		elements[count++] = &element;
		return true;
	}
	return false;
}

template<typename T>
bool randomBag<T>::remove(T& element)
{
	if (isEmpty())
		return false;
	int x = generateNumber(0, count-1);
	element = *elements[x];
	elements[x] = elements[--count];
	return true;
}

template<typename T>
void randomBag<T>::print()
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
randomBag<T>::~randomBag()
{
}