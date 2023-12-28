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

    FILE* file = NULL;
    fopen_s(&file, "file.txt", "r");
    const char* const string = readLine(&errorCode, file);
    fclose(file);
    if (errorCode != OK_CODE)
    {
        free(string);
        if (errorCode == FILE_ERROR)
        {
            printf("File error");
            return FILE_ERROR;
        }
        printf("Memory error");
        return MEMORY_ERROR;
    }

    printf("Enter string ");
    const char* const subString = readLine(&errorCode, stdin);
    if (errorCode != OK_CODE)
    {
        free(string);
        printf("Memory error");
        return MEMORY_ERROR;
    }
    const int result = numberOccurence(string, subString, &errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Memory error");
        return MEMORY_ERROR;
    }

    if (result == NO_SUBSTRING)
    {
        printf("No substring");
        return OK_CODE;
    }
    printf("Position of the first occurrence of the substring: %d - %Iu", result, result + strlen(subString));
    return OK_CODE;
}
