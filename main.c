#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../stack/stack.h"
#include "../testStack/testStack.h"
#include "postfixCalculator.h"
#include "test.h"

#define LIMITATION_OF_STRING 1000
#define OK_CODE 2

enum errorCode
{
    ERROR_TEST,
    ERROR_STRING
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

    printf("Enter the string (the first 1000 symbols are counted) ");
    char string[LIMITATION_OF_STRING] = { '\0' };
    fgets(string, LIMITATION_OF_STRING, stdin);
    size_t const lengthString = strlen(string);
    if (stringValidation(string, lengthString - 1) == false)
    {
        printf("Unknown symbols in string or the number of operations and symbols is incorrect");
        return ERROR_STRING;
    }

    printf("%Iu", postfixCalculator(string, lengthString - 1));
    return OK_CODE;
}
