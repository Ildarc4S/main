#pragma once

namespace ms // merge sort
{
    typedef int T; // value type
    typedef unsigned int Q; // quantity type

    enum struct Version : unsigned int {
        RECURSIVE,
        ITERATIVE
    };

    void mergeSort_recursive(T* const array, const Q& leftIndex, const Q& rightIndex);
    void mergeSort_iterative(T* const array, const Q& size);

    void merge(T* const array, const Q& leftIndex, const Q& middleIndex, const Q& rightIndex);
}

void ms::mergeSort_recursive(T* const array, const Q& leftIndex, const Q& rightIndex)
{
    if (leftIndex >= rightIndex) return;
    int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

    mergeSort_recursive(array, leftIndex, middleIndex);
    mergeSort_recursive(array, middleIndex + 1, rightIndex);
    merge(array, leftIndex, middleIndex, rightIndex);

}
void ms::mergeSort_iterative(T* const array, const Q& size)
{
    for (int width = 1; width < size; width *= 2)
    {
        int i;
        for (i = 0; i + 2 * width <= size; i += 2 * width)
        {
            merge(array, i, i + width - 1, i + 2 * width - 1);
        }

        if (i + width <= size)
        {
            merge(array, i, i + width - 1, size - 1);
        }
    }
}

void ms::merge(T* const array, const Q& leftIndex, const Q& middleIndex, const Q& rightIndex)
{
    int* C = new int[rightIndex - leftIndex + 1];
    int a = leftIndex;
    int b = middleIndex + 1;
    int c = 0;

    while (a <= middleIndex && b <= rightIndex)
    {
        if (array[a] < array[b])
        {
            C[c++] = array[a++];
        }
        else
        {
            C[c++] = array[b++];
        }
    }

    while (a <= middleIndex)
    {
        C[c++] = array[a++];
    }
    while (b <= rightIndex)
    {
        C[c++] = array[b++];
    }

    for (int i = leftIndex; i <= rightIndex; i++)
    {
        array[i] = C[i - leftIndex];
    }

}



