#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "stack.h"
#include "testStack.h"
#include "postfixCalculator.h"
#include "test.h"
#include "errorCodes.h"

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
        return ERROR_STACK_TEST;
    }

    printf("Enter the string ");
    const int* const errorCode = OK_CODE;
    char* const string = readString(&errorCode);
    if (errorCode == ERROR_MEMORY)
    {
        printf("Error memory");
        return ERROR_MEMORY;
    }

    size_t const lengthString = strlen(string);
    int const result = postfixCalculator(string, lengthString, &errorCode);
    if (errorCode == ERROR_VALIDATION)
    {
        printf("Unknown symbols in string or the number of operations and symbols is incorrect");
        return ERROR_VALIDATION;
    }

    if (errorCode == ERROR_STACK)
    {
        printf("Error stack");
        return ERROR_STACK;
    }

    if (errorCode == ERROR_MEMORY)
    {
        printf("Error memory");
        return ERROR_MEMORY;
    }

    printf("Result: %d", result);
    return OK_CODE;
}
