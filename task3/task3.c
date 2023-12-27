#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "errorCodes.h"
#include "automaton.h"
#include "test.h"

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }

    int* const errorCode = OK_CODE;
    printf("Enter string ");
    const char* const string = readString(&errorCode);

    if (errorCode != OK_CODE)
    {
        printf("Memory error");
        return MEMORY_ERROR; 
    }
    printf(automaton(string) ? "The string is correct " : "The string is not correct");
    free(string);
    return OK_CODE;
}
