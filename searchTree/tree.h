#pragma once

#include <stdlib.h>

typedef struct Tree Tree;

//return to root
Tree* root(const Tree* const tree);

//add data with key
Tree* addData(Tree* tree, const char* const data, const int key, int* const errorCode);

//search for data by key 
char* searchData(Tree* tree, const int key);

//check existence of node with entered key
bool existence(const Tree* const tree, const int key);

void clearTree(Tree* tree);

//delete node
Tree* deleteNode(const Tree* tree, const int key);

//return data of node
char* checkData(const Tree* const tree);

//return key of node
int checkKey(const Tree* const tree);

//return left child of node
Tree* checkLeftChild(const Tree* const tree);

//return right child of node
Tree* checkRightChild(const Tree* const tree);

//return parent of node
Tree* checkParent(const Tree* const tree);
