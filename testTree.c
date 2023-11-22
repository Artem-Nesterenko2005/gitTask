#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "testTree.h"

bool testTree(void)
{
    Tree* tree = NULL;
    tree = makeRoot(tree);
    if (leftChildren(leftChildren(tree)) != NULL || rightChildren(rightChildren(tree)) != NULL)
    {
        printf("Error test number 1");
        return false;
    }

    tree = addData(tree, 'a');
    if (data(leftChildren(tree)) != 'a')
    {
        printf("Error test number 2");
        return false;
    }
    return true;
}

