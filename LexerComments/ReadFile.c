#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lexer.h"
#include "ErrorCodes.h"

char* readString(int* errorCode, const char* const fileName)
{
    size_t length = 0;
    size_t capacity = 1;
    FILE* expression;
    fopen_s(&expression, fileName, "r");
    if (expression == NULL)
    {
        *errorCode = ERROR_FILE;
        return NULL;
    }

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
