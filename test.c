#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "test.h"
#include "codes.h"

#define LIMITATION_OF_STRING 1000

static bool testCase(const char* const string, size_t const number)
{
    int* const errorCode = OK_CODE;
    const bool result = bracketsBalance(string, strlen(string), &errorCode);
    return errorCode == OK_CODE && result;
}

bool test(void)
{
    char const testString1[LIMITATION_OF_STRING] = { "(((((" };
    if (testCase(testString1, 1))
    {
        printf("Error test number 1\n");
        return false;
    }

    char const testString2[LIMITATION_OF_STRING] = { "({[]})" };
    if (testCase(testString1, 2))
    {
        printf("Error test number 2\n");
        return false;
    }

    char const testString3[LIMITATION_OF_STRING] = { "]]]]]" };
    if (testCase(testString1, 3))
    {
        printf("Error test number 3\n");
        return false;
    }

    char const testString4[LIMITATION_OF_STRING] = { "{(})" };
    if (testCase(testString4, 4))
    {
        printf("Error test number 4\n");
        return false;
    }

    char const testString5[LIMITATION_OF_STRING] = { "()[{}]({}[])" };
    if (testCase(testString1, 5))
    {
        printf("Error test number 5\n");
        return false;
    }

    return true;
}
