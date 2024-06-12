#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../postfixCalculator/testStack.h"
#include "test.h"
#include "bracketsBalance.h"
#include "codes.h"

int main(void)
{
   if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }

    if (!testStack())
    {
        printf("Error stack test");
        return ERROR_TEST;
    }

    const int* const errorCode = OK_CODE;

    printf("Enter string (no more than 1000 symbols): ");
    const char* const string = readString(&errorCode);
    if (errorCode == ERROR_MEMORY)
    {
        printf("Error memory");
        return ERROR_MEMORY;
    }
    const size_t length = strlen(string);

    const bool result = bracketsBalance(string, length, &errorCode);

    if (errorCode == ERROR_MEMORY)
    {
        printf("Error memory");
        return ERROR_MEMORY;
    }

    if (errorCode == ERROR_STACK)
    {
        printf("Error stack");
        return ERROR_STACK;
    }

    printf(result && errorCode == OK_CODE ? "String is correct" : "String is not correct");
    return OK_CODE;
}
