#pragma once

//operation
enum operation;

//struct for tree
typedef struct Tree Tree;

//create root of tree
Tree* makeNode(int* const errorCode);

//add numbers
Tree* addData(Tree* tree, const int data, int* const errorCode);

//return to parent
Tree* parent(const Tree* const tree);

//add operation
Tree* addParent(Tree* tree, const int data, int* const errorCode);

//clear tree nodes
void clearTree(Tree* tree);

//print tree
void printTree(const Tree* const tree);

//return left children of node
Tree* leftChildren(const Tree* const tree);

//return right children of node
Tree* rightChildren(const Tree* const tree);

//return data of node
int data(const Tree* const tree);

//change node data 
void changeData(Tree* const tree, int const data);

//check for parent
Tree* checkParent(const Tree* const tree);
