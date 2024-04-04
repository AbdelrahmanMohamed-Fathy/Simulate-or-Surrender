#pragma once
#include "../utils/generateNumber.cpp"

template<typename T>
class randomBag {
private:
	T* elements[400];
	unsigned int count = 0;
public:
	randomBag();

	int getCount();

	bool isEmpty();

	bool isFull();

	bool addElement(T& element);

	bool remove(T& element);

	void print();

	~randomBag();
};
