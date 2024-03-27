#pragma once

template <typename T>
struct doublyNode
{
	T data;
	doublyNode<T>* next = nullptr;
	doublyNode<T>* prev = nullptr;
};