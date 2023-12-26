#include <stdio.h>
#include <stdlib.h>

#include "errorCodes.h"
#include "test.h"
#include "modulesAndFiles.h"
#include "quickSort.h"

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }

    const int* const errorCode = OK_CODE;
    const char* const string = readFile(&errorCode, "file.txt");
    if (errorCode != OK_CODE)
    {
        if (errorCode == ERROR_MEMORY)
        {
            printf("Error memory");
            return ERROR_MEMORY;
        }

        printf("Error file");
        return ERROR_FILE;
    }

    const size_t length = 0;
    const int* array = fillingArray(string, &length, &errorCode);
    if (errorCode != OK_CODE)
    {
        free(array);
        printf("Error memory");
        return ERROR_MEMORY;
    }
    printf("Array: ");
    printArray(array, length);
    array = quickSort(array, 0, length);

    printf("\nMost common element - %Iu\n", mostCommon(array, length));
    free(string);
    free(array);
    return OK_CODE;
}
