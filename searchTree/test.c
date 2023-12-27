#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "searchTree.h"
#include "tree.h"
#include "test.h"
#include "errorCodes.h"

bool test(void)
{
    Tree* tree = NULL;
    int* const errorCode = OK_CODE;
    tree = addData(tree, "a", 10, &errorCode);
    if (checkData(tree) != "a" || errorCode != OK_CODE)
    {
        return false;
    }

    if (checkKey(tree) != 10 || errorCode != OK_CODE)
    {
        return false;
    }

    if (!existence(tree, 10) || errorCode != OK_CODE)
    {
        return false;
    }

    if (existence(tree, 15) || errorCode != OK_CODE)
    {
        return false;
    }

    if (checkKey(tree) != 10 || errorCode != OK_CODE)
    {
        return false;
    }

    free(tree);
    return true;
}
