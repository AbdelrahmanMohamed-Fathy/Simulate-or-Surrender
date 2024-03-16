#pragma once

template<typename T>
class Bag {
private:
	T* Elements[100];
	int count = 0;
public:
	Bag();

	bool IsEmpty();

	bool IsFull();

	bool AddElement(T& element);

	bool remove(T& element);

	~Bag();
};
