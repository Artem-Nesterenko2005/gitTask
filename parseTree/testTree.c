#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "testTree.h"
#include "errorCodes.h"

bool testTree(void)
{
    Tree* tree = NULL;
    tree = makeNode(tree);
    if (parent(tree) != NULL || leftChildren(tree) != NULL || rightChildren(tree) != NULL)
    {
        printf("Error test number 1");
        return false;
    }

    const int* const errorCode = OK_CODE;
    tree = addData(tree, 1, &errorCode);
    if (data(leftChildren(tree)) != 1 || errorCode != OK_CODE)
    {
        printf("Error test number 2");
        return false;
    }
    return true;
}
