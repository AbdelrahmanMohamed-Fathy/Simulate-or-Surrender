#pragma once
#include "../utils/generateNumber.cpp"

template<typename T>
class bag {
private:
	T* Elements[100];
	unsigned int count = 0;
public:
	bag();

	bool IsEmpty();

	bool IsFull();

	bool AddElement(T& element);

	bool remove(T& element);

	~bag();
};
