#include <stdbool.h>

#include "algorithmKMP.h"
#include "readString.h"
#include "errorCodes.h"
#include "test.h"

bool test(void)
{
    int* const errorCode = OK_CODE;

    const char* const string1 = readFile(&errorCode, "test1.txt");
    const char subString1[4] = "123\0";
    if (!(numberOccurrences(string1, subString1, &errorCode) == 0 && errorCode == OK_CODE))
    {
        return false;
    }

    const char* const string2 = readFile(&errorCode, "test2.txt");
    const char subString2[3] = "oo\0";
    if (!(numberOccurrences(string2, subString2, &errorCode) == NO_SUBSTRING && errorCode == OK_CODE))
    {
        return false;
    }

    const char* const string3 = readFile(&errorCode, "test3.txt");
    const char subString3[2] = "7\0";
    if (!(numberOccurrences(string3, subString3, &errorCode) == NO_SUBSTRING && errorCode == OK_CODE))
    {
        return false;
    }

    return true;
}
