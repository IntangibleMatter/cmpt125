#include "binarytree.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main() { return 0; }

BTree *createBTree() {
	BTree *newTree = malloc(sizeof(BTree));
	newTree->root = NULL;
	return newTree;
}

BTreeNode *createBTreeNode(int value) {
	BTreeNode *newNode = malloc(sizeof(BTreeNode));

	newNode->value = value;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;

	return newNode;
}

int getDepth(BTreeNode *node) {
	if (node == NULL) {
		return -1;
	}
	return max(getDepth(node->left), getDepth(node->right)) + 1;
}

int getSize(BTreeNode *node) {
	if (node == NULL) {
		return 0;
	}

	return (getSize(node->left) + getSize(node->right) + 1);
}

void printTree(BTreeNode *node) {
	if (node == NULL) {
		return;
	}

	printTree(node->left);
	printf("%d ", node->value);
	printTree(node->right);
}

bool isDescendant(BTreeNode *descendant, BTreeNode *ancestor) {
	if (descendant == ancestor) {
		return true;
	}
	if (descendant->parent == NULL) {
		return false;
	}

	BTreeNode *currparent = descendant->parent;

	while (currparent != NULL) {
		if (currparent == ancestor) {
			return true;
		}
		currparent = currparent->parent;
	}
	return false;
}

// section: BST
BTreeNode *findNode(BTreeNode *node, int value) {
	if (node == NULL) {
		return NULL;
	}
	if (node->value == value) {
		return node;
	}
	if (node->value > value) {
		return findNode(node->left, value);
	} else {
		return findNode(node->right, value);
	}
}

BTreeNode *insertNode(BTreeNode *node, int value) {
	if (node == NULL) {
		return createBTreeNode(value);
	}
	if (node->value > value) {
		node->left = insertNode(node->left, value);
	} else {
		node->right = insertNode(node->right, value);
	}
	return node;
}
