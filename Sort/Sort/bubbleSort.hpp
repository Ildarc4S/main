#pragma once

namespace bs // bubble sort
{
    typedef int T; // value type
    typedef unsigned int Q; // quantity type

    void bubbleSort_oneWay(T* const array, const Q& size);
    void bubbleSort_twoWay(T* const array, const Q& size);

    void forward(T* const array, const Q& lowerBound, Q& upperBound, bool& condition);
    void backward(T* const array, Q& lowerBound, const Q& upperBound, bool& condition);
    void swap(T& left, T& right);
}


void bs::bubbleSort_oneWay(T* const array, const Q& size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (array[j] > array[j + 1])
                bs::swap(array[j], array[j + 1]);
        }
    }
}
void bs::bubbleSort_twoWay(T* const array, const Q& size)
{
    bool  sortOrNo = false;
    Q upperBound = size - 1;
    Q lowerBound = 1;

    while (sortOrNo == 0)
    {
        sortOrNo = true;
        bs::forward(array, lowerBound, upperBound, sortOrNo);
        bs::backward(array, lowerBound, upperBound, sortOrNo);
    }
}

void bs::forward(T* const array, const Q& lowerBound, Q& upperBound, bool& condition)
{
    for (int i = 0; i < upperBound; i++)
    {
        if (array[i] > array[i + 1])
        {
            bs::swap(array[i], array[i + 1]);
            condition = false;
        }
    }
    upperBound--;
}
void bs::backward(T* const array, Q& lowerBound, const Q& upperBound, bool& condition)
{
    for (int j = upperBound; j >= lowerBound; j--)
    {
        if (array[j] < array[j - 1])
        {
            bs::swap(array[j], array[j - 1]);
        }
    }
    lowerBound++;
}

void bs::swap(T& left, T& right)
{
    T tmp = left;
    left = right;
    right = tmp;
}
