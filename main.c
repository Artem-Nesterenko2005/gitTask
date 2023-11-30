#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../postfixCalculator/testStack.h"
#include "test.h"
#include "bracketsBalance.h"

#define OK_CODE 1
#define ERROR_TEST -1
#define LIMITATION_OF_STRING 1000

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

    char const string[LIMITATION_OF_STRING] = { '\0' };
    printf("Enter string (no more than 1000 symbols): ");
    fgets(string, LIMITATION_OF_STRING, stdin);
    size_t const length = strlen(string);
    printf(bracketsBalance(string, length) ? "String is correct" : "String is not correct");
    return OK_CODE;
}
