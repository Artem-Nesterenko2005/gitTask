#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "realNumberLexer.h"
#include "test.h"
#include "errorCodes.h"
#include "readString.h"

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }

    int* const errorCode = OK_CODE;
    printf("Enter the string: ");
    const char* const string = readString(&errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Memory error");
        free(string);
        return ERROR_MEMORY;
    }

    printf(realNumberLexer(string) ? "Real number" : "Not a real number");
    free(string);
    return OK_CODE;
}
