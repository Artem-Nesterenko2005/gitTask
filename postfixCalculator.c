#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>

#include "stack.h"
#include "postfixCalculator.h"
#include "errorCodes.h"

#define ENCODING_CONVERSION 48

char* readString(int* const errorCode)
{
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    char symbol = getchar();

    while (symbol != '\n')
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

        symbol = getchar();
    }

    string[length] = '\0';
    return string;
}

static size_t transactionProcessing(char const symbol, const size_t number1, const size_t number2)
{
    switch (symbol)
    {
    case '+':
        return (number1 + number2);

    case '-':
        return (number2 - number1);

    case '*':
        return (number1 * number2);

    case '/':
        return (number2 / number1);
    }
}

static bool isOperation(char const symbol)
{
    return symbol == '*' || symbol == '/' || symbol == '-' || symbol == '+';
}

int postfixCalculator(const char* const string, const size_t length, int* const errorCode)
{
    Stack* stack = NULL;
    int number1 = 0;
    int number2 = 0;
    for (size_t i = 0; i < length; ++i)
    {
        if (isdigit(string[i]))
        {
            stack = push(stack, string[i] - ENCODING_CONVERSION, errorCode);
            if (*errorCode == ERROR_MEMORY)
            {
                clearStack(stack);
                return NULL_EXPRESSION;
            }
            continue;
        }

        else if (isOperation(string[i]))
        {
            if (isEmpty(stack))
            {
                clearStack(stack);
                *errorCode = ERROR_VALIDATION;
                return NULL_EXPRESSION;
            }
            number1 = top(stack);
            stack = pop(stack);

            if (isEmpty(stack))
            {
                clearStack(stack);
                *errorCode = ERROR_VALIDATION;
                return NULL_EXPRESSION;
            }
            number2 = top(stack);
            stack = pop(stack);

            if (!isEmpty(stack))
            {
                clearStack(stack);
                *errorCode = ERROR_VALIDATION;
                return NULL_EXPRESSION;
            }

            stack = push(stack, transactionProcessing(string[i], number1, number2), errorCode);
            if (*errorCode == ERROR_MEMORY)
            {
                clearStack(stack);
                return NULL_EXPRESSION;
            }
            continue;
        }
    }

    if (isEmpty(nextNode(stack)) && !isEmpty(stack))
    {
        int result = top(stack);
        clearStack(stack);
        return result;
    }

    clearStack(stack);
    *errorCode = ERROR_STACK;
    return NULL_EXPRESSION;
}
