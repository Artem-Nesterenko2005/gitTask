#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "test.h"

#define LIMITATION_OF_STRING 1000

bool test(void)
{
    char const testString1[LIMITATION_OF_STRING] = { "(((((" };
    if (bracketsBalance(testString1, strlen(testString1)))
    {
        printf("Error test number 1\n");
        return false;
    }

    char const testString2[LIMITATION_OF_STRING] = { "({[]})" };
    if (!bracketsBalance(testString2, strlen(testString2)))
    {
        printf("Error test number 2\n");
        return false;
    }

    char const testString3[LIMITATION_OF_STRING] = { "]]]]]" };
    if (!bracketsBalance(testString3, strlen(testString3)))
    {
        printf("Error test number 3\n");
        return false;
    }

    char const testString4[LIMITATION_OF_STRING] = { "{(})" };
    if (bracketsBalance(testString4, strlen(testString4)))
    {
        printf("Error test number 4\n");
        return false;
    }

    char const testString5[LIMITATION_OF_STRING] = { "()[{}]({}[])" };
    if (!bracketsBalance(testString5, strlen(testString5)))
    {
        printf("Error test number 5\n");
        return false;
    }

    return true;
}
