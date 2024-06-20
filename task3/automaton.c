#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "automaton.h"
#include "errorCodes.h"

enum States
{
    firstOperator,
    secondOperator,
    point,
    thirdOperator
};

char* readString(int* const errorCode)
{
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        *errorCode = MEMORY_ERROR;
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
                *errorCode = MEMORY_ERROR;
                return NULL;
            }
            string = tmp;
        }

        symbol = getchar();
    }

    string[length] = '\0';
    return string;
}

bool automaton(const char* const string)
{
    size_t state = firstOperator;
    const size_t length = strlen(string);
    for (size_t i = 0; i < length; ++i)
    {
        const char curChar = string[i];
        switch (state)
        {
        case firstOperator:
            if (isdigit(curChar) || isalpha(curChar) || curChar == '.' || curChar == '%' || curChar == '+' || curChar == '-' || curChar == '_')
            {
                state = secondOperator;
                break;
            }
            return false;

        case secondOperator:
            if (isdigit(curChar) || isalpha(curChar))
            {
                state = point;
                break;
            }
            return false;

        case point:
            if (curChar == '.')
            {
                state = thirdOperator;
                break;
            }
            return false;

        case thirdOperator:
            if (isalpha(curChar))
            {
                return true;
            }
            return false;
        }
    }
}
