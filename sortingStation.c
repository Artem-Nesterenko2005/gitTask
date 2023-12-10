#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack.h"
#include "errorCodes.h"
#include "sotringStation.h"

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


static int priority(const char symbol)
{
    switch (symbol)
    {
    case '-':
    case '+':
        return 1;

    case '*':
    case '/':
        return 2;

    default:
        return isdigit(symbol) ? 0 : -1;
    }
}

char* stringProcessing(char* const string, int* const errorCode)
{
    Stack* stack = NULL;
    char* const finalString = (char*)calloc(strlen(string) + 2, sizeof(char));
    size_t indexFinalString = 0; 
    const size_t lengthString = strlen(string);
    for (size_t i = 0; i < lengthString; ++i)
    {
        if (string[i] == ' ')
        {
            continue;
        }

        if (string[i] == '(')
        {
            stack = push(stack, string[i], errorCode);
            if (*errorCode != OK_CODE)
            {
                clearStack(stack);
                return NULL;
            }
            continue;
        }
        if (string[i] == ')')
        {
            if (stack != NULL)
            {
                while (top(stack) != '(')
                {
                    finalString[indexFinalString] = top(stack);
                    stack = pop(stack);
                    ++indexFinalString;
                    finalString[indexFinalString] = ' ';
                    ++indexFinalString;
                }
            }
            stack = pop(stack);
            continue;
        }

        const int prioritySymbol = priority(string[i]);
        if (prioritySymbol == -1)
        {
            clearStack(stack);
            *errorCode = UNVALIDATION_STRING;
            return NULL;
        }
        switch (prioritySymbol)
        {

        case 0:
            finalString[indexFinalString] = string[i];
            ++indexFinalString;
            finalString[indexFinalString] = ' ';
            ++indexFinalString;
            break;

        case 1:
        case 2:
            if (isEmpty(stack) || priority(top(stack)) < prioritySymbol)
            {
                stack = push(stack, string[i], errorCode);
                if (*errorCode != OK_CODE)
                {
                    clearStack(stack);
                    return NULL;
                }
                break;
            }

            if (priority(top(stack)) == prioritySymbol)
            {
                finalString[indexFinalString] = top(stack);
                ++indexFinalString;
                finalString[indexFinalString] = ' ';
                stack = pop(stack);
                stack = push(stack, string[i], errorCode);
                if (*errorCode != OK_CODE)
                {
                    clearStack(stack);
                    return NULL;
                }
                ++indexFinalString;
                break;
            }

            while (priority(top(stack)) >= prioritySymbol)
            {
                finalString[indexFinalString] = top(stack);
                stack = pop(stack);
                ++indexFinalString;

                finalString[indexFinalString] = ' ';
                ++indexFinalString;

                if (isEmpty(stack))
                {
                    stack = push(stack, string[i], errorCode);
                    if (*errorCode != OK_CODE)
                    {
                        clearStack(stack);
                        return NULL;
                    }
                    break;
                }
            }
        }
    }

    while (!isEmpty(stack))
    {
        finalString[indexFinalString] = top(stack);
        stack = pop(stack);
        ++indexFinalString;
        finalString[indexFinalString] = ' ';
        ++indexFinalString;
    }
    finalString[indexFinalString] = '\0';

    clearStack(stack);
    return finalString;
}
