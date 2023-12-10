#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "stack.h"
#include "../bracketsBalance/codes.h"
#include "sotringStation.h"
#include "testStack.h"
#include "test.h"

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

    const int* const errorCode = OK_CODE;

    printf("Enter an expression: ");
    const char* const string = readString(&errorCode);
    if (string == NULL)
    {
        printf("Error memory");
        return ERROR_MEMORY;
    }

    const char* const finalString = (char*)calloc(strlen(string) + 1, sizeof(char));
    if (finalString == NULL)
    {
        printf("Error memory");
        free(string);
        return ERROR_MEMORY;
    }

    stringProcessing(string, finalString, &errorCode);

    if (errorCode == ERROR_MEMORY)
    {
        free(string);
        free(finalString);
        printf("Error memory");
        return ERROR_MEMORY;
    }

    printf("Postfix form: ");
    printString(finalString, strlen(finalString));
    free(string);
    free(finalString);
    return OK_CODE;
}
