#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "avlTree.h"
#include "errorCodes.h"
#include "test.h"

bool test(void)
{
    Tree* tree = NULL;
    int* const errorCode = OK_CODE;
    tree = addData(tree, "1", "asd", &errorCode);
    if (!(checkData(tree, "asd") && checkKey(tree, "1")))
    {
        deleteTree(tree);
        return false;
    }

    if (strcmp(searchData(tree, "1"), "asd") != 0)
    {
        deleteTree(tree);
        return false;
    }

    if (keyExiste(tree, "10"))
    {
        deleteTree(tree);
        return false;
    }

    deleteTree(tree);
    return true;
}
