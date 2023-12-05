#pragma once

#include <stdlib.h>

typedef struct Tree Tree;

//make left child for node
static Tree* makeLeftNode(Tree* tree);

//make right child for node
static Tree* makeRightNode(Tree* tree);

//make root for tree
Tree* makeRoot(Tree* tree, const char* data, const int key);

//return to root
Tree* root(Tree* tree);

//checks the tree for the presence of a key identical to the one entered
static Tree* matchChecking(Tree* tree, const int key, const char* data);

//recursively searches for a node for a child
static Tree* childNode(Tree* tree, const int key, const char* data);

//add data with key
Tree* addData(Tree* tree, const char* data, const int key);

//search for data by key 
char* searchData(Tree* tree, const int key);

//check existence of node with entered key
bool existence(Tree* tree, const int key);

//search node with entered key
static Tree* searchKey(Tree* tree, const int key);

//delete node without children
static Tree* deleteNonChildren(Tree* tree, const int key);

//delete node with one child
static Tree* deleteOneChildren(Tree* tree, const int key);

//delete node wuth two children
static Tree* deleteTwoChildren(Tree* tree, const int key);

//delete node
Tree* deleteNode(Tree* tree, const int key);

//return data of node
Tree* checkData(Tree* tree);

//return key of node
Tree* checkKey(Tree* tree);

//return left child of node
Tree* checkLeftChild(Tree* tree);

//return right child of node
Tree* checkRightChild(Tree* tree);

//return parent of node
Tree* checrParent(Tree* tree);

