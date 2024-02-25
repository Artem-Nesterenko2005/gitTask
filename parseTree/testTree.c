#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "testTree.h"
#include "errorCodes.h"

bool testTree(void)
{
    Tree* tree = makeNode();
    if (tree == NULL)
    {
        printf("Error test number 1\n");
        return false;
    }
    int errorCode = OK_CODE;
    tree = addNumber(tree, 1, &errorCode);
    if (checkData(checkLeftChildren(tree)) != 1 || errorCode != OK_CODE)
    {
        printf("Error test number 2\n");
        clearTree(tree);
        return false;
    }
    clearTree(tree);
    return true;
}
