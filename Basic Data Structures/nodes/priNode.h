#pragma once
#include "node.h"

template <typename T>
struct priNode : public node<T>
{
	int priority;
};

