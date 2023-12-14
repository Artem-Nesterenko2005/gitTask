#pragma once

#include "tree.h"

//read line from file
char* readString(int* const errorCode, const char* const fileName);

//add symbol in tree
Tree* addSymbol(Tree* tree, char data, int* const errorCode);

//make tree
Tree* makeTree(const char* const string, int* const errorCode);

//calculate the value of an expression from a tree
int resultCalculation(Tree* tree);
