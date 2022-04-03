#include <iostream>

#include "mergeSort.hpp"
#include "heapSort.hpp"

void printArray(int* A, int N)
{
	std::cout << "\n";

	for (int i = 0; i < N; i++) {
		std::cout << A[i] << "\t";
	}

	std::cout << "\n";
}

int main()
{
	int const size = 8;
	int arr[size] = { 23, 32, 232, 7, 8, 3, 4, 9 };


	//ms::mergeSort_recursive(arr,0,size-1);
	//ms::mergeSort_iterative(arr, size);

	//hs::heapSort(arr, size);

	printArray(arr, size);

}