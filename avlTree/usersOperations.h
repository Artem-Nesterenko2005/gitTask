#pragma once

#include "avlTree.h"

enum Operations;

// users operations
Tree* usersOperations(const size_t numberOperation, int* const errorCode, const Tree* tree);
