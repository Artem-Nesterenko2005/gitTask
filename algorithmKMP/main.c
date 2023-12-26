#include <stdio.h>
#include <string.h>

#include "errorCodes.h"
#include "readString.h"
#include "algorithmKMP.h"
#include "test.h"

int main(void)
{
    if (!test())
    {
       printf("Error test");
        return ERROR_TEST;
    }
    int* const errorCode = OK_CODE;

    const char* const string = readFile(&errorCode, "file.txt");
    if (errorCode != OK_CODE)
    {
        if (errorCode == FILE_ERROR)
        {
            printf("File error");
            return FILE_ERROR;
        }
        printf("Memory error");
        return MEMORY_ERROR;
    }

    printf("Enter string ");
    const char* const subString = readString(&errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Memory error");
        return MEMORY_ERROR;
    }
    const int result = numberOccurrences(string, subString, &errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Memory error");
        return MEMORY_ERROR;
    }

    if (result == -1)
    {
        printf("No substring");
        return OK_CODE;
    }
    printf("Position of the first occurrence of the substring: %d - %Iu", result, result + strlen(subString));
    return OK_CODE;
}
