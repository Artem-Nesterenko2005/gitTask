#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

#include "../postfixCalculator/stack.h"
#include "bracketsBalance.h"
#include "codes.h"

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

    *errorCode = OK_CODE;
    string[length] = '\0';
    return string;
}

static char const oppositeBracket(const char symbol)
{
    switch (symbol)
    {
    case ']':
        return '[';
    case ')':
        return '(';
    case '}':
        return '{';
    default:
        return '0';
    }
}

bool bracketsBalance(const char* const string, const size_t length, int* const errorCode)
{
    Stack* stack = NULL;
    for (size_t i = 0; i < length; ++i)
    {
        switch (string[i])
        {
        case '[':
        case '{':
        case '(':

            stack = push(stack, string[i], errorCode);
            if (*errorCode != OK_CODE)
            {
                clearStack(stack);
                return false;
            }

            break;

        case ']':
        case '}':
        case ')':
            if (stack == NULL)
            {
                clearStack(stack);
                return false;
            }

            if (oppositeBracket(string[i]) != top(stack) || isEmpty(stack))
            {
                clearStack(stack);
                return false;
            }

            if (isEmpty(stack))
            {
                *errorCode = ERROR_STACK;
                clearStack(stack);
                return false;
            }
            stack = pop(stack);
            break;

        default:
            continue;
        }
    }
    const bool result = stack == NULL;
    clearStack(stack);
    return result;
}
