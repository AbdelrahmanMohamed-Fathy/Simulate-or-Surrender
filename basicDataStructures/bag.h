#pragma once
#include "../utils/generateNumber.cpp"

template<typename T>
class bag {
private:
	T* elements[100];
	unsigned int count = 0;
public:
	bag();

	bool isEmpty();

	bool isFull();

	bool addElement(T& element);

	bool remove(T& element);

	~bag();
};
