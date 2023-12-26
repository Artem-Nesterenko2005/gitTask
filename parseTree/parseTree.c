#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "tree.h"
#include "parseTree.h"
#include "errorCodes.h"

#define ENCODING_NUMBER 48

enum operations
{
    MULTIPLICATION = -6,
    ADDITION,
    SUBTRACTION = -3,
    DIVISION = -1
};

static Tree* addSymbol(Tree* tree, char data, int* const errorCode)
{
    switch (data)
    {
    case '+':
    case '-':
    case '/':
    case '*':
        tree = addParent(tree, data - ENCODING_NUMBER, errorCode);
        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
        return tree;

    case ')':
        tree = parent(tree);
        return tree;

    case ' ':
    case '(':
        return tree;

    default:
        if (!isdigit(data))
        {
            *errorCode = UNCORRECT_SYMBOL;
            return NULL;
        }

        tree = addData(tree, data - ENCODING_NUMBER, errorCode);
        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
        return tree;
    }
}

Tree* makeTree(const char* const string, int* const errorCode)
{
    Tree* tree = NULL;
    const char* const digit = NULL;
    size_t lengthString = strlen(string);
    if (lengthString == 0)
    {
        *errorCode = EMPTY_FILE;
        return NULL;
    }

    tree = makeNode(tree);
    if (*errorCode != OK_CODE || tree == NULL)
    {
        return NULL;
    }

    for (size_t i = 0; i < lengthString - 2; ++i)
    {
        tree = addSymbol(tree, string[i], errorCode);
        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
    }
    return tree;
}

int resultCalculation(Tree* tree, int* const errorCode)
{
    if (leftChildren(tree) == NULL)
    {
        return data(tree);
    }
    const int number1 = resultCalculation(leftChildren(tree), errorCode);
    const int number2 = resultCalculation(rightChildren(tree), errorCode);
    const char operation = data(tree);
    
    switch (operation)
    {
    case MULTIPLICATION:
        if (*errorCode != OK_CODE)
        {
            return 0;
        }
        return number1 * number2;
    
    case ADDITION:
        if (*errorCode != OK_CODE)
        {
            return 0;
        }
        return number1 + number2;

    case DIVISION:
        if (number2 == 0 || *errorCode != OK_CODE)
        {
            *errorCode = ZERO_DIVISOR;
            return 0;
        }
        return number1 / number2;
        
    case SUBTRACTION:
        if (*errorCode != OK_CODE)
        {
            return 0;
        }
        return number1 - number2;
    }

}
