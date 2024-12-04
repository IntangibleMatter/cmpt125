#include "linked.h"

LList_t *LL_create() {
	LList_t *newList = malloc(sizeof(LList_t));

	if (newList == NULL) {
		return NULL;
	}

	newList->head = NULL;
	newList->tail = NULL;
	newList->length = 0;
	return newList;
}

void LL_free(LList_t *list) {
	if (list == NULL) {
		return;
	}
	Node_t *item = list->head;

	if (item == NULL) {
		free(list);
		return;
	}

	while (item != NULL) {
		Node_t *curr_item = item;
		item = item->next;
		free(curr_item);
	}

	list->head = NULL;
	list->tail = NULL;
	free(list);
}

void LL_insertFront(LList_t *list, int value) {
	if (list == NULL) {
		return;
	}

	Node_t *node = malloc(sizeof(Node_t));

	if (node == NULL) {
		return;
	}

	node->value = value;

	if (list->head == NULL) {
		list->head = node;
		list->tail = node;
		node->next = NULL;
	} else {
		node->next = list->head;
		list->head = node;
	}

	list->length++;
}

bool LL_insertAt(LList_t *list, int value, int position) {
	if (list == NULL || list->length < position) {
		return false;
	}

	if (position == 0) {
		LL_insertFront(list, value);
		return true;
	}

	Node_t *newNode = malloc(sizeof(Node_t));
	if (newNode == NULL) {
		return false;
	}
	Node_t *currnode = list->head;
	for (int i = 0; i < position; i++) {
		currnode = currnode->next;
	}

	newNode->next = currnode->next;
	currnode->next = newNode;

	return true;
}

void LL_insertEnd(LList_t *list, int value) {
	if (list == NULL) {
		return;
	}

	Node_t *node = malloc(sizeof(Node_t));

	if (node == NULL) {
		return;
	}

	node->value = value;
	node->next = NULL;

	if (list->tail == NULL) {
		list->head = node;
		list->tail = node;
	} else {
		list->tail->next = node;
		list->tail = node;
	}
	list->length++;
}

int LL_removeAt(LList_t *list, int at) {
	int out = 0xFFFF;
	if (list == NULL || list->head == NULL) {

	} else if (at < list->length) {
		Node_t *node = list->head;
		for (int i = 0; i < at - 1; i++) {
			node = node->next;
		}
		Node_t *to_free = node->next;
		node->next = to_free->next;
		out = to_free->value;
		to_free->next = NULL;
		free(to_free);
		list->length--;
	}
	return out;
}

int LL_removeFront(LList_t *list) {
	int out = 0xFFFF;
	if (list == NULL || list->head == NULL) {
		// do nothing, return error code
	} else if (list->head == list->tail) { // one item
		out = list->head->value;
		free(list->head);
		list->head = NULL;
		list->tail = NULL;
		list->length = 0;
	} else {
		out = list->head->value;
		Node_t *newHead = list->head->next;
		free(list->head);
		list->head = newHead;
		list->length--;
	}
	return out;
}

int LL_removeEnd(LList_t *list) {
	int out = 0xFFFF;
	if (list == NULL || list->head == NULL) {
		// return error code
	} else if (list->head == list->tail) {
		out = list->tail->value;
		free(list->tail);
		list->head = NULL;
		list->tail = NULL;
		list->length = 0;
	} else {
		Node_t *currnode = list->head;
		out = list->tail->value;
		while (currnode->next != list->tail) {
			currnode = currnode->next;
		}
		// currnode must now be penultimate node
		free(list->tail);
		list->tail = currnode;
		list->length--;
	}

	return out;
}

bool LL_isEmpty(LList_t *list) { return list->length == 0; }

void LL_printList(LList_t *list) {
	if (list == NULL) {
		return;
	}
	Node_t *currnode = list->head;

	while (currnode != NULL) {
		printf("%d", currnode->value);
		if (currnode->next != NULL) {
			printf(", ");
		}
	}
}

int main() { return 0; }
