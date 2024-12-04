#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <stdbool.h>
#include <stdlib.h>

#define min(a, b) ((a < b) ? a : b)
#define max(a, b) ((a > b) ? a : b)

typedef struct TreeNode {
	int value;
	struct TreeNode *left;
	struct TreeNode *right;
	struct TreeNode *parent;
} BTreeNode;

typedef struct {
	BTreeNode *root;
} BTree;

BTree *createBTree();
BTreeNode *createBTreeNode(int value);
int getDepth(BTreeNode *node);
int getSize(BTreeNode *node);
void printTree(BTreeNode *node);
bool isDescendant(BTreeNode *descendant, BTreeNode *ancestor);

// section: BST

BTreeNode *findNode(BTreeNode *node, int key);
BTreeNode *insertNode(BTreeNode *node, int value);

#endif
