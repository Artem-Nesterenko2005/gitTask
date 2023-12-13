#include <stdbool.h>
#include <string.h>

#include "errorCode.h"
#include "task1.h"

#define NUMBERS 10

bool test(void)
{
    const int* const errorCode = OK_CODE;
    const char* const string = "9032";
    return strcmp(transformation(string, &errorCode), "2039") == 0 && errorCode == OK_CODE;
}
