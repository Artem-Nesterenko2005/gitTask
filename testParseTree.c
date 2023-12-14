#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "parseTree.h"
#include "errorCodes.h"
#include "tree.h"

bool testParseTree(void)
{
    Tree* tree = NULL;
    const int* const errorCode = OK_CODE;
    const char* const string = readString(&errorCode, "testFile.txt");
    if (errorCode != OK_CODE)
    {
        return false;
    }

    tree = makeTree(string, &errorCode);
    if (errorCode != OK_CODE)
    {
        return false;
    }

    if (resultCalculation(tree) != 9)
    {
        return false;
    }

    return true;
}
