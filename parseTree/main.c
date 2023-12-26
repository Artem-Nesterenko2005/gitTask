#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "parseTree.h"
#include "testTree.h"
#include "errorCodes.h"
#include "testPareseTree.h"
#include "readString.h"

int main(void)
{
    if (!testTree())
    {
        printf("Error test\n");
        return ERROR_TEST;
    }

    if (!testParseTree())
    {
        printf("Error parse tree test\n");
        return ERROR_TEST;
    }
    Tree* tree = NULL;
    const int* const errorCode = OK_CODE;
    const char* const string = readString(&errorCode, "expression.txt");
    if (errorCode != OK_CODE)
    {
        free(string);
        printf("Error memory");
        return ERROR_MEMORY;
    }

    tree = makeTree(string, &errorCode);
    if (errorCode == EMPTY_FILE)
    {
        clearTree(tree);
        free(string);
        printf("Parsing error\n");
        return EMPTY_FILE;
    }

    printf("Expression: ");
    printTree(tree);

    printf("\nResult of expression: %d ", resultCalculation(tree, &errorCode));
    clearTree(tree);
}
