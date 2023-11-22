#include <stdlib.h>
#include <stdio.h>

#include "testStack.h"
#include "postfixCalculator.h"
#include "testStack.h"
#include "tree.h"
#include "parseTree.h"
#include "testTree.h"

#define ERROR_TEST -1
#define EMPTY_FILE -2
#define LIMITATION 100
#define END 0

int main(void)
{
    if (testStack() != true || testTree() != true)
    {
        printf("Error test");
        return ERROR_TEST;
    }
    Tree* tree = NULL;
    char string[LIMITATION] = { '\0' };
    readingFile(string);

    tree = makeTree(tree, string);
    if (tree == NULL)
    {
        printf("File is empty");
        return EMPTY_FILE;
    }

    printf("Expression: ");
    printTree(tree);

    char resultString[LIMITATION] = { '\0' };
    postfixNotation(tree, resultString);
    printf("\nResult of expression: %d", postfixCalculator(resultString, strlen(resultString)));
    free(tree);
    return END;
}

