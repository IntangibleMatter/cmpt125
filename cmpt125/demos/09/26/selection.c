#include "selection.h"

void swap(int *a, int *b) {
	int temp = *b;
	*b = *a;
	*a = temp;
}

void selectionSort_iter(int *array, unsigned int size) {
	for (int i = 0; i < size - 1; i++) {
		int minIndex = i;
		for (int j = i + 1; j < size; j++) {
			if (array[j] < minIndex) {
				minIndex = j;
			}
		}
		swap(&array[i], &array[minIndex]);
	}
}

void selectionSort_recursive(int *array, unsigned int size) {
	if (size == 0)
		return;

	int minIndex = 0;

	for (int i = 0; i < size; i++) {
		if (array[i] < array[minIndex]) {
			minIndex = i;
		}
	}
	swap(&array[0], &array[minIndex]);
}
