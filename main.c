#include <stdio.h>

#include "errorCode.h"
#include "task1.h"
#include "test.h"

#define NUMBERS 10

int main()
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }
    const int* const errorCode = OK_CODE;
    printf("Enter number ");
    const char* const string = readString(&errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Error memory");
        return ERROR_MEMORY;
    }

    const char* const resultString = transformation(string, &errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Error: unvalidation string");
        return UNVALIDATION_STRING;
    }

    printf("%s", resultString);
}
