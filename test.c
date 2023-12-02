#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test.h"
#include "postfixCalculator.h"

#define ERROR_VALIDATION -999

static bool caseTest(const char* const string, size_t const numberTest, size_t const rightResult)
{
    if (postfixCalculator(string, strlen(string)) != rightResult)
    {
        printf("Error test number %d\n", numberTest);
        return false;
    }

    return true;
}

bool test(void)
{
    const char testString1[3] = { "11" };
    if (!caseTest(testString1, 1, ERROR_VALIDATION))
    {
        return false;
    }

    const char testString2[6] = { "9 6 -" };
    if (!caseTest(testString2, 2, 3))
    {
        return false;
    }

    const char testString3[14] = { "2 3 + 4 * 2 /" };
    if (!caseTest(testString3, 3, 10))
    {
        return false;
    }

    return true;
}
