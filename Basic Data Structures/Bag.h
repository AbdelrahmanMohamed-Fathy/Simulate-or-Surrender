#pragma once
#include "../Utils/GenerateNumber.cpp"

template<typename T>
class Bag {
private:
	T* Elements[100];
	unsigned int count = 0;
public:
	Bag();

	bool IsEmpty();

	bool IsFull();

	bool AddElement(T& element);

	bool remove(T& element);

	~Bag();
};
