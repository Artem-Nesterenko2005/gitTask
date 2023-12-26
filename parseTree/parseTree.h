#pragma once

#include "tree.h"

//make tree
Tree* makeTree(const char* const string, int* const errorCode);

//calculate the value of an expression from a tree
int resultCalculation(Tree* tree, int* const errorCode);
