#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "errorCodes.h"
#include "modulesAndFiles.h"

int* readFile(int* const errorCode, char* fileName, int* lengthArray)
{
    int length = 0;
    size_t capacity = 1;
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        *errorCode = ERROR_FILE;
        return NULL;
    }

    int* array = (int*)malloc(sizeof(int));
    if (array == NULL)
    {
        fclose(file);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    int symbol = 0;
    fscanf_s(file, "%d", &symbol);

    while (!feof(file))
    {
        array[length++] = symbol;

        if (length >= capacity)
        {
            capacity *= 2;
            int* tmp = (int*)realloc(array, capacity * sizeof(int));
            if (tmp == NULL)
            {
                free(array);
                fclose(file);
                *errorCode = ERROR_MEMORY;
                return NULL;
            }
            array = tmp;
        }

        fscanf_s(file, "%d", &symbol);
    }

    *errorCode = OK_CODE;
    array[length] = '\0';
    fclose(file);
    *lengthArray = length;
    return array;
}

size_t mostCommon(const int* array, const size_t length)
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

void printArray(const int* const array, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        printf("%d ", array[i]);
    }
}
