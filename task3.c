#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#include "errorCode.h"

char* readFile(int* const errorCode, const char* const fileName)
{
    size_t length = 0;
    size_t capacity = 1;
    FILE* file;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return ERROR_FILE;
    }

    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        *errorCode = ERROR_MEMORY;
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
                *errorCode = ERROR_MEMORY;
                return NULL;
            }
            string = tmp;
        }

        symbol = getc(file);
    }

    *errorCode = OK_CODE;
    string[length] = '\0';
    return string;
}

void stringProcessing(int* const errorCode, const char* const string)
{
    const size_t length = strlen(string);
    char* const newString = (char*)malloc(length);
    if (newString == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }

    newString[0] = string[0];
    size_t counter = 1;
    for (size_t i = 0; i < length; ++i)
    {
        if (newString != NULL && string[i] == newString[counter - 1])
        {
            continue;
        }
        newString[counter] = string[i];
        ++counter;
    }

    if (newString != NULL && counter < length)
    {
        newString[counter] = '\0';
        strcpy_s(string, length, newString);
    }
    free(newString);
    return string;
}
