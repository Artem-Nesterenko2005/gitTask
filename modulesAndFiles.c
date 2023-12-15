#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "errorCodes.h"
#include "modulesAndFiles.h"

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

int* fillingArray(char* string, size_t* const length, int* const errorCode)
{
    int* array = NULL;
    for (size_t i = 0; *string != '\0'; ++i)
    {
        char* tmp = (int*)realloc(array, (i + 1) * sizeof(int));
        if (tmp == NULL)
        {
            free(string);
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        array = tmp;
        ++ *length;

        while (!isdigit(*string) && *string != '\0')
        {
            ++string;
        }

        array[i] = atoi(string);

        while (isdigit(*string) && *string != '\0')
        {
            ++string;
        }
    }
    return array;
}

size_t mostCommon(int* const array, const size_t length)
{
    size_t mostCommon = 0;
    size_t counterMostCommon = 1;
    size_t maxCounter = 0;
    for (size_t i = 0; i < length; ++i)
    {
        counterMostCommon = array[i] == array[i + 1] ? counterMostCommon + 1 : counterMostCommon;
        if (counterMostCommon > maxCounter)
        {
            mostCommon = array[i];
            maxCounter = counterMostCommon;
        }
    }
    return mostCommon;
}

void printArray(const int* const array, const size_t const length)
{
    for (size_t i = 0; i < length; ++i)
    {
        printf("%d ", array[i]);
    }
}
