#pragma once
#include "node.h"

template <typename T>
struct doublyNode : public node<T>
{
	node<T>* prev = nullptr;
};