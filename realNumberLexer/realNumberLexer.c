#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "realNumberLexer.h"

enum States
{
    firstNumber,
    wholePart,
    fraction,
    fractionAndE,
    sign,
    degree
};

bool realNumberLexer(const char* const string)
{
    size_t state = 0;
    const size_t length = strlen(string);
    for (size_t i = 0; i < length; ++i)
    {
        switch (state)
        {
        case firstNumber:
            if (isdigit(string[i]))
            {
                state = wholePart;
                break;
            }
            return false;

        case wholePart:
            if (isdigit(string[i]))
            {
                state = wholePart;
                break;
            }

            if (string[i] == '.')
            {
                state = fraction;
                break;
            }
            return false;

        case fraction:
            if (isdigit(string[i]))
            {
                state = fractionAndE;
                break;
            }
            return false;

        case fractionAndE:
            if (isdigit(string[i]))
            {
                state = fractionAndE;
                break;
            }

            if (string[i] == 'E')
            {
                state = sign;
                break;
            }
            return false;

        case sign:
            if (string[i] == '+' || string[i] == '-')
            {
                state = degree;
                break;
            }
            return false;

        case degree:
            if (isdigit(string[i]))
            {
                state = degree;
                break;
            }
            return false;
        }
    }
    return true;
}
