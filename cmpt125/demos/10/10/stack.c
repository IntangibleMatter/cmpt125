#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
	int end;
	int data[5];
} Size5Stack;

bool isEmpty(Size5Stack *stack) { return stack->end == -1; }

Size5Stack *createStack() {
	Size5Stack *stack = malloc(sizeof(Size5Stack));
	if (stack == NULL) {
		return NULL;
	}
	stack->end = -1;
	return stack;
}

int push(Size5Stack *stack, int item) {
	if (stack->end == 4) {
		return -1;
	}
	stack->data[++stack->end] = item;
	return 0;
}

int pop(Size5Stack *stack) {
	if (isEmpty(stack)) {
		return 0xFFFF;
	}
	return stack->data[stack->end--];
}
