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
    DIVISION,
    SUBTRACTION
};

char* readString(int* const errorCode, const char* const fileName)
{
    size_t length = 0;
    size_t capacity = 1;
    FILE* expression;
    fopen_s(&expression, fileName, "r");
    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    char symbol = getc(expression);

    while (symbol != EOF)
    {
        string[length++] = symbol;

        if (length >= capacity)
        {
            capacity *= 2;
            char* tmp = (char*)realloc(string, capacity * sizeof(char));
            if (tmp == NULL)
            {
                free(string);
                *errorCode = ERROR_MEMORY;
                return NULL;
            }
            string = tmp;
        }

        symbol = getc(expression);
    }

    *errorCode = OK_CODE;
    string[length] = '\0';
    return string;
}

Tree* addSymbol(Tree* tree, char data, int* const errorCode)
{
    switch (data)
    {
    case '+':
    case '-':
    case '/':
    case '*':
        tree = addParent(tree, data - ENCODING_NUMBER, errorCode);
        if (errorCode != OK_CODE)
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
        tree = addData(tree, data - ENCODING_NUMBER, errorCode);
        if (errorCode != OK_CODE)
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

    tree = makeRoot(tree);
    if (*errorCode != OK_CODE)
    {
        return NULL;
    }

    for (size_t i = 0; i < lengthString - 2; ++i)
    {
        tree = addSymbol(tree, string[i], *errorCode);
        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
    }
    return tree;
}

int resultCalculation(Tree* tree)
{
    if (leftChildren(tree) == NULL)
    {
        return data(tree);
    }
    const int number1 = resultCalculation(leftChildren(tree));
    const int number2 = resultCalculation(rightChildren(tree));
    const char operation = data(tree);
    
    switch (operation)
    {
    case MULTIPLICATION:
        return number1 * number2;
    
    case ADDITION:
        return number1 + number2;

    case DIVISION:
        return number1 / number2;
        
    case SUBTRACTION:
        return number1 - number2;
    }

}
