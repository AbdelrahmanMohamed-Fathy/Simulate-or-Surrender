#pragma once
#include "../utils/generateNumber.cpp"

template<typename T>
class bag {
private:
	T* elements[400];
	unsigned int count = 0;
public:
	bag();

	int getCount();

	bool isEmpty();

	bool isFull();

	bool addElement(const T& element);

	bool remove(T& element);

	void print();

	~bag();
};
