#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "test.h"
#include "codes.h"

static bool testCase(const char* const string, const size_t number, const bool rightResult, const int rightCode)
{
    int* const errorCode = OK_CODE;
    const bool result = bracketsBalance(string, strlen(string), &errorCode);
    if ((errorCode != rightCode) || (result != rightResult))
    {
        printf("Error test number %Iu\n", number);
        return false;
    }
    return true;
}

bool test(void)
{
    const char* const testString1 = "(((((";
    const bool result1 = testCase(testString1, 1, false, STRING_UNCORRECT);

    const char* const testString2 = "({[]})";
    const bool result2 = testCase(testString2, 2, true, OK_CODE);
  
    const char* const testString3 = "]]]]]";
    const bool result3 = testCase(testString3, 3, false, STRING_UNCORRECT);

    const char* const testString4 = "{(})";
    const bool result4 = testCase(testString4, 4, false, STRING_UNCORRECT);

    const char* const testString5 = "()[{}]({}[])";
    const bool result5 = testCase(testString5, 5, true, OK_CODE);

    return result1 && result2 && result3 && result4 && result5;
}
