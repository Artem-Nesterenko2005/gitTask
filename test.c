#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "test.h"
#include "postfixCalculator.h"

#define LIMITATION_OF_STRING 1000

static bool caseTest(const char* string, size_t const length, size_t const rightResult)
{
    if (!stringValidation(string, length))
    {
        return false;
    }

    if (postfixCalculator(string, length) != rightResult)
    {
        return false;
    }

    return true;
}

bool test(void)
{
    const char testString1[LIMITATION_OF_STRING] = { "11" };
    size_t const lengthTestString1 = strlen(testString1);
    if (caseTest(testString1, lengthTestString1, 0))
    {
        printf("Error test number 1");
        return false;
    }

    const char testString2[LIMITATION_OF_STRING] = { "9 6 -" };
    size_t const lengthTestString2 = strlen(testString2);
    if (!caseTest(testString2, lengthTestString2, 3))
    {
        printf("Error test number 2");
        return false;
    }

    const char testString3[LIMITATION_OF_STRING] = { "2 3 + 4 * 2 /" };
    size_t const lengthTestString3 = strlen(testString3);
    if (!caseTest(testString3, lengthTestString3, 10))
    {
        printf("Error test number 3");
        return false;
    }

    return true;
}
