#pragma once

#include <stdbool.h>

// struct for tree
typedef struct Tree Tree;

// add new node
Tree* addData(Tree* tree, const char* const key, const char* const value, int* const errorCode);

// search date by key
char* searchData(Tree* tree, char* key);

// checking the key for existence
bool keyExiste(Tree* tree, char* key);

// delete node
Tree* deleteData(Tree* tree, const char* const key);

// delete tree
void deleteTree(Tree* tree);

// check data of node
bool checkData(const Tree* const tree, const char* data);

// check key of node
bool checkKey(const Tree* const tree, const char* key);
