#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "test.h"
#include "codes.h"

#define LIMITATION_OF_STRING 1000

static bool testCase(const char* const string, const size_t number, const bool rightResult)
{
    int* const errorCode = OK_CODE;
    const bool result = bracketsBalance(string, strlen(string), &errorCode);
    if ((errorCode == OK_CODE && result) != rightResult)
    {
        printf("Error test number %Iu\n", number);
        return false;
    }
    return true;
}

bool test(void)
{
    const char const testString1[LIMITATION_OF_STRING] = { "(((((" };
    const bool result1 = testCase(testString1, 1, false);

    const char const testString2[LIMITATION_OF_STRING] = { "({[]})" };
    const bool result2 = testCase(testString2, 2, true);
  
    const char const testString3[LIMITATION_OF_STRING] = { "]]]]]" };
    const bool result3 = testCase(testString3, 3, false);

    const char const testString4[LIMITATION_OF_STRING] = { "{(})" };
    const bool result4 = testCase(testString4, 4, false);

    const char const testString5[LIMITATION_OF_STRING] = { "()[{}]({}[])" };
    const bool result5 = testCase(testString5, 5, true);

    return result1 && result2 && result3 && result4 && result5;
}
