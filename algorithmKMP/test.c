#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "algorithmKMP.h"
#include "readString.h"
#include "errorCodes.h"
#include "test.h"

static int testCase(const char* const fileName, const char* const substring)
{
    int* const errorCode = OK_CODE;
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    const char* const string = readLine(&errorCode, file);
    if (errorCode != OK_CODE)
    {
        fclose(file);
        free(string);
        return TEST_MEMORY_ERROR;
    }
    const int result = numberOccurence(string, substring, &errorCode);
    if (errorCode != OK_CODE)
    {
        fclose(file);
        free(string);
        return TEST_MEMORY_ERROR;
    }
    fclose(file);
    free(string);
    return result;
}

bool test(void)
{
    const bool result1 = testCase("test1.txt", "123") == 0;

    const bool result2 = testCase("test2.txt", "oo") == NO_SUBSTRING;

    const bool result3 = testCase("test3.txt", "7") == NO_SUBSTRING;

    const bool result4 = testCase("test4.txt", "aaaaa") == NO_SUBSTRING;

    const bool result5 = testCase("test5.txt", "45") == 3;
    
    return result1 && result2 && result3 && result4 && result5;
}
