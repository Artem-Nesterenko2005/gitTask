#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../postfixCalculator/stack.h"
#include "bracketsBalance.h"

#define LIMITATION_OF_STRING 1000

static char const changeBrackets(char const symbol)
{
    switch (symbol)
    {
    case ']':
        return '[';
    case ')':
        return '(';
    case '}':
        return '{';
    }
}

bool bracketsBalance(char* string, size_t const length)
{
    Stack* stack = NULL;
    for (size_t i = 0; i < length; ++i)
    {
        switch (string[i])
        {
        case '[':
        case '{':
        case '(':

            stack = push(stack, string[i]);
            break;

        case ']':
        case '}':
        case ')':
            if (stack == NULL)
            {
                return false;
            }

            if (changeBrackets(string[i]) != top(stack))
            {
                return false;
            }

            stack = pop(stack);
            break;
        }
    }
    if (stack != NULL)
    {
        return false;
    }
    return true;
}
