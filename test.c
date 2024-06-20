#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "searchTree.h"
#include "tree.h"
#include "test.h"

bool test(void)
{
    Tree* tree = NULL;
    tree = makeRoot(tree, "a", 10);
    if (checkData(tree) != "a")
    {
        printf("Error test number 1");
        return false;
    }

    if (checkKey(tree) != 10)
    {
        printf("Error test number 2");
        return false;
    }

    tree = addData(tree, "b", 5);
    tree = addData(tree, "c", 20);

    if (existence(tree, 20) == false)
    {
        printf("Error test number 3");
        return false;
    }

    if (existence(tree, 15) == true)
    {
        printf("Error test number 4");
        return false;
    }

    tree = checkLeftChild(tree);
    if (checkData(tree) != "b")
    {
        printf("Error test number 5");
        return false;
    }

    if (checkKey(tree) != 5)
    {
        printf("Error test number 6");
        return false;
    }
    
    tree = root(tree);
    if (checkKey(tree) != 10)
    {
        printf("Error test number 7");
        return false;
    }

    tree = checkRightChild(tree);
    if (checkData(tree) != "c")
    {
        printf("Error test number 8");
        return false;
    }

    if (checkKey(tree) != 20)
    {
        printf("Error test number 9");
        return false;
    }
    
    tree = root(tree);
    tree = addData(tree, "d", 10);
    if (checkData(tree) != "d")
    {
        printf("Error test number 10");
        return false;
    }

    tree = deleteNode(tree, 10);
    if (checkData(tree) != "b")
    {
        printf("Error test number 11");
        return false;
    }

    tree = deleteNode(tree, 5);
    if (checkData(tree) != "c")
    {
        printf("Error test number 12");
        return false;
    }

    tree = deleteNode(tree, 20);
    if (tree != NULL)
    {
        printf("Error test number 13");
        return false;
    }

    free(tree);
    return true;
}

