#include <stdlib.h>
#include <stdbool.h>

#include "quickSort.h"
#include "modulesAndFiles.h"
#include "errorCodes.h"
#include "test.h"

static bool checkSort(const int* const array, const int length)
{
    for (size_t i = 0; i < length; ++i)
    {
        if (array[i] > array[i + 1])
        {
            return false;
        }
    }
    return true;
}

bool test(void)
{
    const int* const errorCode = OK_CODE;
    const char* const string = readFile(&errorCode, "test.txt");
    if (errorCode != OK_CODE)
    {
        return false;
    }

    const int length = 0;
    const int* array = fillingArray(string, &length, &errorCode);
    if (errorCode != OK_CODE)
    {
        return false;
    }

    array = quickSort(array, 0, length);
    const bool result = checkSort(array, length) && mostCommon(array, length) == 2;
    free(string);
    free(array);
    return result;
}
