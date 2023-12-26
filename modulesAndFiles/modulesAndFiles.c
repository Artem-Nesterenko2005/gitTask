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
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        return ERROR_FILE;
    }

    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        fclose(file);
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
                fclose(file);
                *errorCode = ERROR_MEMORY;
                return NULL;
            }
            string = tmp;
        }

        symbol = getc(file);
    }

    *errorCode = OK_CODE;
    string[length] = '\0';
    fclose(file);
    return string;
}

int* fillingArray(char* string, size_t* const length, int* const errorCode)
{
    int* array = NULL;
    size_t capacity = 1;
    for (size_t i = 0; *string != '\0'; ++i)
    {
        capacity *= 2;
        char* tmp = (int*)realloc(array, capacity * sizeof(int));
        if (tmp == NULL)
        {
            free(string);
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        array = tmp;
        ++*length;
        array[i] = atoi(string);
        while (*string != ' ')
        {
            ++string;
        }

        while (*string == ' ')
        {
            ++string;
        }
    }
    array = (int*)realloc(array, *length * sizeof(int));

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
