#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "codes.h"
#include "sotringStation.h"

static bool testCase(const char* string, const int* errorCode, const char* const rightString, const size_t number)
{
    string = stringProcessing(string, errorCode);

    if (strcmp(string, rightString) || *errorCode != OK_CODE)
    {
        free(string);
        printf("Error test number %Iu\n", number);
        return false;
    }
    free(string);
    return true;
}

bool test(void)
{
    const int* const errorCode = OK_CODE;

    const char* const testString1 = "1 / 2 / 3 / 4 / 5 / 6";
    const char* const rightString1 = "1 2 / 3 / 4 / 5 / 6 / ";
    const bool result1 = testCase(testString1, &errorCode, rightString1, 1);

    const char* const testString2 = "( 1 - 2 * 3 ) *  4- 5";
    const char* const rightString2 = "1 2 3 * - 4 * 5 - ";
    const bool result2 = testCase(testString2, &errorCode, rightString2, 2);

    const char* const testString3 = "1 - 2 / 3 + 4";
    const char* const rightString3 = "1 2 3 / - 4 + ";
    const bool result3 = testCase(testString3, &errorCode, rightString3, 3);

    return result1 && result2 && result3;
}
