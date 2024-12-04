#ifndef _LINKED_H_
#define _LINKED_H_
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
} Node_t;

typedef struct {
	Node_t *head;
	Node_t *tail;
	// instead of this you could do a function that gets the list size
	int length;
} LList_t;

LList_t *LL_create();
void LL_free(LList_t *list);
void LL_insertFront(LList_t *list, int value);
// If position exists it'll insert it at the point, otherwise return false
bool LL_insertAt(LList_t *list, int value, int position);
void LL_insertEnd(LList_t *list, int value);
int LL_removeFront(LList_t *list);
// removes node at index if exists, otherwise returns an error code
int LL_removeAt(LList_t *list, int at);
int LL_removeEnd(LList_t *list);
bool LL_isEmpty(LList_t *list);

void LL_printList(LList_t *list);

#endif
