#include <stdbool.h>
#include <stdlib.h>

#include "test.h"
#include "realNumberLexer.h"

bool test(void)
{
    const char* const string1 = { "6.7E-23" };

    const char* const string2 = { "123.EE+5" };

    const char* const string3 = { "1111111111111111.22222222222222222E+333333333" };

    const char* const string4 = { ".EE+123" };

    const char* const string5 = { "E+4" };

    return realNumberLexer(string1) && !realNumberLexer(string2) && realNumberLexer(string3) && !realNumberLexer(string4) && !realNumberLexer(string5);
}
