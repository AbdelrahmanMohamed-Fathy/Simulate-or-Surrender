#pragma once

template <typename T>
struct priNode
{
    T data;
    int priority;
    priNode<T>* next = nullptr;
};

