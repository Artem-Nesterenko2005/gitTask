#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>

#include "errorCode.h"
#include "task1.h"

#define NUMBERS 10
#define ENCODING_NUMBER 48

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

    *errorCode = OK_CODE;
    string[length] = '\0';
    return string;
}

char* transformation(const char* const string, int* const errorCode)
{
    if (string[0] == '0' && string[1] != '\0')
    {
        *errorCode = UNVALIDATION_STRING;
        return NULL;
    }

    int array[NUMBERS] = { '\0' };
    const int length = strlen(string);
    for (size_t i = 0; i < length; ++i)
    {
        ++array[string[i] - ENCODING_NUMBER];
    }

    size_t counter = 0;
    char* const auxiliaryString = (char*)malloc(length);

    size_t index = 0;
    if (array[0] != 0)
    {
        while (array[index + 1] == 0)
        {
            ++index;
        }
        if (index != 9 && auxiliaryString != NULL)
        {
            auxiliaryString[counter] = index + 1 + ENCODING_NUMBER;
            --array[index + 1];
            ++counter;
        }
    }

    for (size_t i = 0; i < NUMBERS; ++i)
    {
        while (array[i] != 0)
        {
            auxiliaryString[counter] = i + ENCODING_NUMBER;
            --array[i];
            ++counter;
        }
    }
    if (auxiliaryString != NULL)
    {
        auxiliaryString[counter] = '\0';
    }
    return auxiliaryString;
}
