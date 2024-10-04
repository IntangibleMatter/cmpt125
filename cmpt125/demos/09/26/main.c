#include "selection.h"
#include <stdio.h>

void printIntArray(int *array, unsigned int size) {
	printf("[");
	for (int i = 0; i < size; i++) {
		printf("%d", array[i]);
		if (i < size - 1) {
			printf(", ");
		}
	}
	printf("]\n");
}

int main() {
	int arr[] = {19, 444, 0, -31, 324, 1, 2, 6, 4, 23, 11, 013, -99, 99, 0xFF};

	selectionSort_iter(arr, 15);

	printIntArray(arr, 15);

	return 0;
}
