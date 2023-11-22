#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "tree.h"
#include "parseTree.h"


#define LIMITATION 100

#pragma warning(disable : 4996)

Tree* addSymbol(Tree* tree, char data)
{
    switch (data)
    {
    case '+':
    case '-':
    case '/':
    case '*':
        tree = addParent(tree, data);
        return tree;

    case ')':
        tree = parent(tree);
        return tree;

    case ' ':
    case '(':
        return tree;

    default:
        tree = addData(tree, data);
        return tree;
    }
}

Tree* makeTree(Tree* tree, char string[])
{
    size_t lengthString = strlen(string);
    if (lengthString == 0)
    {
        return NULL;
    }
    tree = makeRoot(tree);
    for (size_t i = 0; i < lengthString - 2; ++i)
    {
        tree = addSymbol(tree, string[i]);
    }
    return tree;
}

void readingFile(char string[])
{
    FILE* expression;
    expression = fopen("expression.txt", "r");
    fgets(string, LIMITATION, expression);
    fclose(expression);
}


