#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test.h"
#include "postfixCalculator.h"
#include "errorCodes.h"

static bool caseTest(const char* const string, size_t const numberTest, size_t const rightResult, int const rightCode)
{
    int* const errorCode = 0;
    if ((postfixCalculator(string, strlen(string), &errorCode) != rightResult) || (errorCode != rightCode))
    {
        printf("Error test number %Iu\n", numberTest);
        return false;
    }

    return true;
}

bool test(void)
{
    const char testString1[3] = { "11" };

    const char testString2[6] = { "9 6 -" };

    const char testString3[14] = { "2 3 + 4 * 2 /" };

    return caseTest(testString1, 1, 0, ERROR_STACK) && caseTest(testString2, 2, 3, OK_CODE) && caseTest(testString3, 3, 10, OK_CODE);
}
