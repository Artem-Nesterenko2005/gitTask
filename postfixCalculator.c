#include <stdlib.h>

#include "stack.h"
#include "postfixCalculator.h"

#define ENCODING_CONVERSION 48

int transactionProcessing(char symbol, int number1, int number2)
{
    switch (symbol)
    {
    case '+':
        return (number1 + number2);

    case '-':
        return (number2 - number1);

    case '*':
        return (number1 * number2);

    case '/':
        return (number2 / number1);
    }
}

int postfixCalculator(char string[], int length)
{
    Stack* stack = NULL;
    int number1 = 0;
    int number2 = 0;
    for (int numberSymbol = 0; numberSymbol < length; ++numberSymbol)
    {
        switch (string[numberSymbol])
        {
        case '+':
        case '-':
        case '/':
        case '*':
            if (stack == NULL)
            {
                return 0;
            }
            number1 = top(stack);
            stack = pop(stack);

            if (stack == NULL)
            {
                return 0;
            }
            number2 = top(stack);
            stack = pop(stack);

            stack = push(stack, transactionProcessing(string[numberSymbol], number1, number2));
            break;

        case ' ':
            break;

        default:
            stack = push(stack, string[numberSymbol] - ENCODING_CONVERSION);
            break;
        }
    }
    if (stack == NULL)
    {
        return 0;
    }
    return top(stack);

}

