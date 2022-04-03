#pragma once

namespace qs
{
    typedef int T; // value
    typedef unsigned int Q; // quantity
    typedef std::array<Q, 2> P; // pair

    enum struct Version : unsigned int {
        DOUBLE,
        TRIPLE
    };

    void quickSort_double(T* const array, const Q& size, const Q& leftIndex,const Q& rightIndex);
    void quickSort_triple(T* const array, const Q& size, const Q& leftIndex,const Q& rightIndex);

    Q splitting_double(T* const array, const Q& size, const Q& leftIndex,const Q& rightIndex);
    P splitting_triple(T* const array, const Q& size, const Q& leftIndex,const Q& rightIndex);

    void swap(T& left, T& right);
}

void qs::swap(T& left, T& right)
{
    T tmp = right;
    right = left;
    left = tmp;
}