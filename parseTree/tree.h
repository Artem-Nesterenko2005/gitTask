#pragma once

// struct for tree
typedef struct Tree Tree;

// create root of tree
Tree* makeNode(void);

// add numbers
Tree* addNumber(Tree* tree, const int data, int* errorCode);

// return to parent
Tree* returnParent(const Tree* const tree);

// add operation
Tree* addOperation(Tree* tree, char data, int* errorCode);

// clear tree nodes
void clearTree(Tree* tree);

// print tree
void printTree(const Tree* const tree);

// calculates the result of an expression by traversing the tree
int calculateResult(Tree* tree, int* const errorCode);

// return right child of node
Tree* checkRightChildren(Tree* tree);

// return left child of node
Tree* checkLeftChildren(Tree* tree);

// return data of node
int checkData(Tree* tree);

// return parent of node
Tree* checkParentNode(Tree* tree);
