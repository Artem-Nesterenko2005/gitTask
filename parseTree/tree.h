#pragma once

//struct for tree
typedef struct Tree Tree;

//create root of tree
Tree* makeNode(void);

//add numbers
Tree* addData(Tree* tree, const int data, int* errorCode);

//return to parent
Tree* parent(const Tree* const tree);

//add operation
Tree* addParent(Tree* tree, char data, int* errorCode);

//clear tree nodes
void clearTree(Tree* tree);

//print tree
void printTree(const Tree* const tree);

// calculates the result of an expression by traversing the tree
int resultCalculation(Tree* tree, int* const errorCode);

// return right child of node
Tree* rightChildren(Tree* tree);

// return left child of node
Tree* leftChildren(Tree* tree);

// return data of node
int data(Tree* tree);

// return parent of node
Tree* parentNode(Tree* tree);
