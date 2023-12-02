#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>

#include "stack.h"
#include "postfixCalculator.h"

#define ENCODING_CONVERSION 48

enum errorCode
{
    STACK_ERROR = -998,
    ERROR_VALIDATION = -999
};

char* createString(void)
{
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)malloc(sizeof(char));

    char symbol = getchar();

    while (symbol != '\n')
    {
        string[length++] = symbol;

        if (length >= capacity)
        {
            capacity *= 2;
            string = (char*)realloc(string, capacity * sizeof(char));
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

static bool stringValidation(const char* const string, const size_t lengthString)
{
    size_t numberOfDigits = 0;
    size_t numberOfOperations = 0;
    for (size_t i = 0; i < lengthString; ++i)
    {

        if (isdigit(string[i]))
        {
            ++numberOfDigits;
        }

        else if (string[i] == '-' || string[i] == '+' || string[i] == '/' || string[i] == '*')
        {
            ++numberOfOperations;
        }

        else if (string[i] != ' ')
        {
            return false;
        }

        if (numberOfOperations >= numberOfDigits)
        {
            return false;
        }
    }
    if (numberOfDigits - numberOfOperations == 1)
    {
        return true;
    }
    return false;
}

int postfixCalculator(const char* const string, const size_t length)
{
    if (!stringValidation(string, length))
    {
        return ERROR_VALIDATION;
    }
    Stack* stack = NULL;
    int number1 = 0;
    int number2 = 0;
    for (size_t i = 0; i < length; ++i)
    {
        if (isdigit(string[i]))
        {
            stack = push(stack, string[i] - ENCODING_CONVERSION);
            if (stack == NULL)
            {
                return STACK_ERROR;
            }
        }

        else if (string[i] != ' ')
        {
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
            if (stack == NULL)
            {
                return STACK_ERROR;
            }
        }
    }

    if (isEmpty(nextNode(stack)) && !isEmpty(stack))
    {
        int result = top(stack);
        free(stack);
        return result;
    }
    return STACK_ERROR;
}
