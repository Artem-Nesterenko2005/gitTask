#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "stack.h"
#include "errorCodes.h"
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
    const char* string = readString(&errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Error memory");
        free(string);
        return ERROR_MEMORY;
    }

    string = stringProcessing(string, &errorCode);

    if (errorCode == ERROR_MEMORY)
    {
        free(string);
        printf("Error memory");
        return ERROR_MEMORY;
    }

    if (errorCode == UNVALIDATION_STRING)
    {
        free(string);
        printf("Unvalidation string");
        return UNVALIDATION_STRING;
    }

    printf("Postfix form: %s", string);
    free(string);
    return OK_CODE;
}
