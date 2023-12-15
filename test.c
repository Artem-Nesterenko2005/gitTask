#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "task3.h"
#include "errorCode.h"

bool test(void)
{
    const int* const errorCode = OK_CODE;
    const char* const string = readFile(&errorCode, "test.txt");
    if (errorCode != OK_CODE)
    {
        return false;
    }

    stringProcessing(&errorCode, string);
    const bool result = errorCode == OK_CODE && !strcmp(string, "ai92ikikm");
    free(string);
    return result;
}
