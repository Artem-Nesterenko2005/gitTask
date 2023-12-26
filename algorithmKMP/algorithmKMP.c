#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "algorithmKMP.h"
#include "errorCodes.h"

int* prefixFunction(const char* const string, int* const errorCode)
{
    const size_t length = strlen(string);
    int* array = (int*)calloc(length, sizeof(int));
    if (array == NULL)
    {
        *errorCode = MEMORY_ERROR;
        return NULL;
    }
    for (size_t i = 1; i < length; ++i)
    {
        size_t prefix = array[i - 1];
        while (prefix > 0 && string[prefix] != string[i])
        {
            prefix = array[prefix - 1];
        }

        if (string[prefix] == string[i])
        {
            array[i] = prefix + 1;
        }
    }
    return array;
}

int numberOccurrences(const char* const string, const char* const subString, int* const errorCode)
{
    int* array = prefixFunction(subString, errorCode);
    const size_t lengthString = strlen(string);
    const size_t lengthSubString = strlen(subString);

    for (size_t i = 0; i < lengthString; ++i)
    {
        size_t counter = 0;
        for (size_t j = 0; j < lengthSubString; ++j)
        {
            if (string[i + j] == subString[j])
            {
                ++counter;
            }
            else
            {
                i += array[counter];
                break;
            }
            if (counter == lengthSubString)
            {
                return i;
            }
        }
    }
    free(array);
    return NO_SUBSTRING;
}
