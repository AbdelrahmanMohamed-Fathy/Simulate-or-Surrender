#pragma once

template <typename T>
struct node
{
    T data = NULL;
    node<T>* next = NULL;
};