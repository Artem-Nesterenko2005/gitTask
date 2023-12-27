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
    if (!(numberOccurence(string1, subString1, &errorCode) == 0 && errorCode == OK_CODE))
    {
        free(string1);
        return false;
    }

    const char* const string2 = readFile(&errorCode, "test2.txt");
    const char subString2[3] = "oo\0";
    if (!(numberOccurence(string2, subString2, &errorCode) == NO_SUBSTRING && errorCode == OK_CODE))
    {
        free(string2);
        return false;
    }

    const char* const string3 = readFile(&errorCode, "test3.txt");
    const char subString3[2] = "7\0";
    if (!(numberOccurence(string3, subString3, &errorCode) == NO_SUBSTRING && errorCode == OK_CODE))
    {
        free(string3);
        return false;
    }

    const char* const string4 = readFile(&errorCode, "test4.txt");
    const char subString4[6] = "aaaaa\0";
    if (!(numberOccurence(string4, subString4, &errorCode) == NO_SUBSTRING && errorCode == OK_CODE))
    {
        free(string3);
        return false;
    }

    const char* const string5 = readFile(&errorCode, "test5.txt");
    const char subString5[3] = "45\0";
    if (!(numberOccurence(string5, subString5, &errorCode) == 3 && errorCode == OK_CODE))
    {
        free(string3);
        return false;
    }
    return true;
}
