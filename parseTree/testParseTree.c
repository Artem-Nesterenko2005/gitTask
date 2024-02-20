#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "parseTree.h"
#include "errorCodes.h"
#include "tree.h"
#include "readString.h"

bool testParseTree(void)
{
    Tree* tree = NULL;
    int errorCode = OK_CODE;
    tree = makeNode();
    if (errorCode != OK_CODE)
    {
        return false;
    }

    tree = makeTree("testFile.txt", &errorCode);
    if (errorCode != OK_CODE)
    {
        clearTree(tree);
        return false;
    }

    if (resultCalculation(tree, &errorCode) != 9 || errorCode != OK_CODE)
    {
        clearTree(tree);
        return false;
    }

    clearTree(tree);
    return true;
}
