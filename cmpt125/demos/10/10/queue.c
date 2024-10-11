#include <stdbool.h>
#include <stdlib.h>
typedef struct {
	int end;
	int data[10];
} Size10Queue;

bool isEmpty(Size10Queue *queue) { return queue->end == -1; }

Size10Queue *create() {
	Size10Queue *queue = malloc(sizeof(Size10Queue));

	if (queue == NULL) {
		return NULL;
	}
	queue->end = -1;
	return queue;
}

int enqueue(Size10Queue *queue, int item) {
	if (queue->end == 9) {
		return -1;
	}
	queue->data[++queue->end] = item;
	return 0;
}

int dequeue(Size10Queue *queue) {
	if (isEmpty(queue)) {
		return 0xFFFF;
	}
	int toReturn = queue->data[0];
	for (int i = 1; i < queue->end; i++) {
		queue->data[i - 1] = queue->data[i];
	}
	queue->end--;
	return toReturn;
}
