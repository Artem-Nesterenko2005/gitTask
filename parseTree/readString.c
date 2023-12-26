#include <stdio.h>
#include <stdlib.h>

#include "errorCodes.h"
#include "readString.h"

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

    if (symbol == EOF)
    {
        *errorCode = EMPTY_FILE;
        return NULL;
    }

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
