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
    int errorCode = OK_CODE;
    Tree* tree = makeTree("expression.txt", &errorCode);
    if (errorCode != OK_CODE)
    {
        clearTree(tree);
        if (errorCode == ERROR_FILE)
        {
            printf("Error file");
            return ERROR_FILE;
        }

        if (errorCode == ERROR_MEMORY)
        {
            printf("Error memory");
            return ERROR_MEMORY;
        }

        printf("Uncorrect symbol");
        return UNCORRECT_SYMBOL;
    }

    printf("Expression: ");
    printTree(tree);

    printf("\nResult of expression: %d ", resultCalculation(tree, &errorCode));
    if (errorCode != OK_CODE)
    {
        clearTree(tree);
        if (errorCode == UNCORRECT_SYMBOL)
        {
            printf("Uncorrect symbol");
            return UNCORRECT_SYMBOL;
        }
        printf("Error: you can't divide by zero");
        return ZERO_DIVISOR;
    }

    clearTree(tree);
    return OK_CODE;
}
