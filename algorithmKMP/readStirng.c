#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>

#include "errorCodes.h"
#include "readString.h"

char* readLine(int* const errorCode, char* file)
{
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        *errorCode = MEMORY_ERROR;
        return NULL;
    }

    char symbol = getc(file);

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
                *errorCode = MEMORY_ERROR;
                return NULL;
            }
            string = tmp;
        }
        symbol = getc(file);
        if (symbol == '\n')
        {
            break;
        }
    }

    *errorCode = OK_CODE;
    string[length] = '\0';
    return string;
}
