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

    int errorCode = OK_CODE;
    int length = 0;
    int* array = readFile(&errorCode, "file.txt", &length);
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
    
    printf("Array: ");
    printArray(array, length);
    array = quickSort(array, 0, length);

    printf("\nMost common element - %Iu\n", mostCommon(array, length));
    free(array);
    return OK_CODE;
    
}
