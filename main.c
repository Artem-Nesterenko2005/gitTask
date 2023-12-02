#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "testStack.h"
#include "postfixCalculator.h"
#include "test.h"

#define ERROR_VALIDATION -999
#define STACK_ERROR -998

enum exitCode
{
    ERROR_TEST,
    ERROR_CALCULATOR,
    ERROR_STACK,
    OK_CODE
};

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

    printf("Enter the string ");
    char* const string = createString();
    size_t const lengthString = strlen(string);

    int const result = postfixCalculator(string, lengthString);
    if (result == ERROR_VALIDATION)
    {
        printf("Unknown symbols in string or the number of operations and symbols is incorrect");
        return ERROR_CALCULATOR;
    }

    if (result == STACK_ERROR)
    {
        printf("Error stack");
        return ERROR_STACK;
    }
    printf("Result: %d", result);
    return OK_CODE;
}
