#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "realNumberLexer.h"

enum States
{
    firstNumber,
    wholePart,
    fractionDigits,
    stateE,
    sign,
    degree
};

bool realNumberLexer(const char* const string)
{
    size_t state = firstNumber;
    const size_t length = strlen(string);
    for (size_t i = 0; i < length; ++i)
    {
        const char curChar = string[i];
        switch (state)
        {
        case firstNumber:
            if (isdigit(curChar))
            {
                state = wholePart;
                break;
            }
            return false;
        case wholePart:
            if (isdigit(curChar))
            {
                state = wholePart;
                break;
            }
            if (curChar == '.')
            {
                state = fractionDigits;
                break;
            }
            if (curChar == 'E');
            {
                state = stateE;
                break;
            }
            return false;
        case fractionDigits:
            if (isdigit(curChar))
            {
                state = fractionDigits;
                break;
            }
            if (curChar == 'E')
            {
                state = stateE;
                break;
            }
            return false;
        case stateE:
            if (curChar == '+' || curChar == '-')
            {
                state = sign;
                break;
            }
            return false;
        case sign:
            if (isdigit(curChar))
            {
                state = degree;
                break;
            }
            return false;
        case degree:
            if (isdigit(curChar))
            {
                state = degree;
                break;
            }
            return false;
        }
    }
    return true;
}
