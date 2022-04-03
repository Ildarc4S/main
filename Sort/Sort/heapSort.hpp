#pragma once

void printArray(int* A, int N);

namespace hs
{
	typedef int T; // value type
	typedef unsigned int Q; // quantity type

	enum struct Version : unsigned int {
		RECURSIVE,
		ITERATIVE
	};

	void heapSort(T* const array, const Q& size, const bool& option = false);
	void buildHeap(T* const array, const Q& size, const bool& option = false);

	void maxHeapify_recursive(T* const array, const Q& size, const Q& index);
	void maxHeapify_iterative(T* const array, const Q& size, const Q& index);


	Q getLeftChildIndex(const Q& parentIndex);
	Q getRightChildIndex(const Q& parentIndex);

	void swap(T& left, T& right);
}


void hs::swap(T& left, T& right)
{
	T tmp = left;
	left = right;
	right = tmp;
}

hs::Q hs::getLeftChildIndex(const hs::Q& parentIndex)
{
	return 2 * parentIndex + 1;
}

hs::Q hs::getRightChildIndex(const hs::Q& parentIndex)
{
	return 2 * parentIndex + 2;
}

void hs::heapSort(T* const array, const Q& size, const bool& option)
{
	if (size > 0)
	{
		hs::buildHeap(array, size);
	}

	else
	{
		std::cout << "Size = 0!" << std::endl;
	}
}

void hs::buildHeap(T* const array, const Q& size, const bool& option)
{
	int i = size / 2 - 1;
	int j = size - 1;

	while (i >= 0)
	{
		hs::maxHeapify_iterative(array, size, i);
		i--;
	}


	while (j >= 0)
	{
		hs::swap(array[0], array[j]);
		hs::maxHeapify_iterative(array, j, 0);
		j--;
	}


}

void hs::maxHeapify_recursive(T* const array, const Q& size, const Q& index)
{
	const Q li = hs::getLeftChildIndex(index);
	const Q ri = hs::getRightChildIndex(index);

	Q max = index;

	if (li < size && array[li] > array[max])
	{
		max = li;
	}

	if (ri < size && array[ri] > array[max])
	{
		max = ri;
	}

	if (max != index)
	{
		hs::swap(array[index], array[max]);
		hs::maxHeapify_recursive(array, size, max);
	}



}

void hs::maxHeapify_iterative(T* const array, const Q& size, const Q& index)
{
	bool flag = false;

	Q max = index,
		I = index,
		li,
		ri;

	while (!flag)
	{
		li = hs::getLeftChildIndex(I);
		ri = hs::getRightChildIndex(I);

		if (li < size && array[li] > array[max]) max = li;
		if (ri < size && array[ri] > array[max]) max = ri;

		if (max != I)
		{
			hs::swap(array[max], array[I]);
			I = max;
		}
		else
		{
			flag = true;
		}
	}
}
