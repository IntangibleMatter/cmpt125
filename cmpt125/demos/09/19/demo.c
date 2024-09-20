#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned int capacity;
	unsigned int size;
	int *items;

} ArrayWithInfo;

ArrayWithInfo *newArrayWithInfo(unsigned int capacity) {
	ArrayWithInfo *newArr = malloc(sizeof(ArrayWithInfo));
	if (newArr == NULL) {
		return NULL;
	}
	newArr->capacity = capacity;
	newArr->size = 0;
	newArr->items = malloc(sizeof(int) * capacity);

	return newArr;
}

void freeArrayWithInfo(ArrayWithInfo *array) {
	free(array->items);
	free(array);
}

int main() {
	ArrayWithInfo *myArr = newArrayWithInfo(20);

	for (int i = 0; i < myArr->capacity; i++) {
		myArr->items[i] = 42;
		myArr->size++;
	}

	for (int i = 0; i < myArr->size; i++) {
		printf("%d ", myArr->items[i]);
	}
	printf("\n");

	return 0;
}
