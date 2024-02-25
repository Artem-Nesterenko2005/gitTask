#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "tree.h"
#include "parseTree.h"
#include "errorCodes.h"
#include "readString.h"

static Tree* addSymbol(Tree* tree, char* data, int* errorCode)
{
    switch (*data)
    {
    case '+':
    case '-':
    case '/':
    case '*':
        tree = addOperation(tree, data[0], errorCode);
        free(data);
        return tree;

    case ')':
        if (checkParentNode(checkParentNode(tree)) != NULL)
        {
            tree = returnParent(tree);
        }
        free(data);
        return tree;

    case ' ':
    case '(':
        free(data);
        return tree;

    default:
        if (!isdigit(*data))
        {
            free(data);
            *errorCode = INCORRECT_SYMBOL;
            return tree;
        }

        tree = addNumber(tree, atoi(data), errorCode);
        free(data);
        return tree;
    }
}

Tree* makeTree(char* filename, int* errorCode)
{
    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    if (file == NULL)
    {
        *errorCode = ERROR_FILE;
        return NULL;
    }
    Tree* tree = makeNode();
    if (tree == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }

    while (!feof(file))
    {
        char* string = readString(errorCode, file);
        if (*errorCode != OK_CODE)
        {
            return tree;
        }
        tree = addSymbol(tree, string, errorCode);
        if (*errorCode != OK_CODE)
        {
            return tree;
        }
    }
    return tree;
}
