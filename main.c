#include <stdio.h>
#include <stdlib.h>

#include "errorCode.h"
#include "task3.h"
#include "test.h"

int main()
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
        if (errorCode == ERROR_FILE)
        {
            printf("Error file");
            free(string);
            return ERROR_FILE;
        }

        printf("Error memory");
        free(string);
        return ERROR_MEMORY;

    }
    stringProcessing(&errorCode, string);
    if (errorCode != OK_CODE)
    {
        printf("Error memory");
        free(string);
        return ERROR_MEMORY;
    }
    printf("String without repetitions: %s", string);
    free(string);
    return OK_CODE;
}
