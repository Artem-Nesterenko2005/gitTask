#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../stack/stack.h"
#include "postfixCalculator.h"

#define ENCODING_CONVERSION 48
#define STACK_ERROR -1


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

size_t postfixCalculator(char* const string, const size_t length)
{
    Stack* stack = NULL;
    size_t number1 = 0;
    size_t number2 = 0;
    for (size_t i = 0; i < length; ++i)
    {
        switch (string[i])
        {
        case '+':
        case '-':
        case '/':
        case '*':
            if (stack == NULL)
            {
                return STACK_ERROR;
            }
            number1 = top(stack);
            stack = pop(stack);

            if (stack == NULL)
            {
                return STACK_ERROR;
            }
            number2 = top(stack);
            stack = pop(stack);

            stack = push(stack, transactionProcessing(string[i], number1, number2));
            break;

        case ' ':
            break;

        default:
            stack = push(stack, string[i] - ENCODING_CONVERSION);
            break;
        }
    }
    if (stack == NULL)
    {
        return STACK_ERROR;
    }
    return top(stack);

}

bool stringValidation(char* const string, const size_t lengthString)
{
    size_t numberOfDigits = 0;
    size_t numberOfOperations = 0;
    for (size_t i = 0; i < lengthString; ++i)
    {
        switch (string[i])
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            ++numberOfDigits;
            break;

        case '-':
        case '+':
        case '/':
        case '*':
            ++numberOfOperations;
            break;

        case ' ':
            break;

        default:
            return false;
        }
    }
    if (numberOfDigits - numberOfOperations == 1)
    {
        return true;
    }
    return false;
}
