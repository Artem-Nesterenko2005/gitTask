#include <stdlib.h>
#include <stdbool.h>

#include "quickSort.h"
#include "modulesAndFiles.h"
#include "errorCodes.h"
#include "test.h"

static bool checkSort(const int* array, const int length)
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
    int errorCode = OK_CODE;
    int length = 0;
    const int* array = readFile(&errorCode, "test.txt", &length);
    if (errorCode != OK_CODE)
    {
        return false;
    }
    array = quickSort(array, 0, length);
    const bool result = checkSort(array, length) && mostCommon(array, length) == 2;
    free(array);
    return result;
}
