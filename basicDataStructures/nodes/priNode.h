#pragma once

template <typename T>
struct priNode
{
    T data;
    double priority;
    priNode<T>* next = nullptr;
};

