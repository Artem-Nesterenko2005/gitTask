#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../stack/stack.h"
#include "../testStack/testStack.h"
#include "postfixCalculator.h"

#define LIMITATION_OF_STRING 1000
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

bool stringValidation(char string[], int lengthString)
{
    int numberOfDigits = 0;
    int numberOfOperations = 0;
    for (int counter = 0; counter < lengthString; ++counter)
    {
        switch (string[counter])
        {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
            ++numberOfDigits;
            break;

        case '-':
        case '+':
        case '/':
        case '*':
            ++numberOfOperations;
            break;

        case ' ':
            break;

        default:
            return false;
        }
    }
    if (numberOfDigits - numberOfOperations == 1)
    {
        return true;
    }
    return false;
}

int test()
{
    char testString1[LIMITATION_OF_STRING] = { "11" };
    int lengthTestString1 = strlen(testString1);
    if (stringValidation(testString1, lengthTestString1) == true)
    {
        printf("Test number 1 is incorrect");
        return 0;
    }

    char testString2[LIMITATION_OF_STRING] = { "9 6 -" };
    int lengthTestString2 = strlen(testString2);
    if (stringValidation(testString2, lengthTestString2) == false)
    {
        printf("Test number 2 is incorrect");
        return 0;
    }
    if (postfixCalculator(testString2, lengthTestString2) != 3)
    { 
        printf("Test number 2 is incorrect");
        return 0;
    }

    char testString3[LIMITATION_OF_STRING] = { "9 6 - +" };
    int lengthTestString3 = strlen(testString3);
    if (stringValidation(testString3, lengthTestString3) == true)
    {
        printf("Test number 3 is incorrect");
        return 0;
    }

    char testString4[LIMITATION_OF_STRING] = { "2 3 + 4 * 2 /" };
    int lengthTestString4 = strlen(testString4);
    if (stringValidation(testString4, lengthTestString4) == false)
    {
        printf("Test number 4 is incorrect");
        return 0;
    }
    if (postfixCalculator(testString4, lengthTestString4) != 10)
    {
        printf("Test number 4 is incorrect");
        return 0;
    }

    char testString5[LIMITATION_OF_STRING] = { "23+4*2/" };
    int lengthTestString5 = strlen(testString5);
    if (stringValidation(testString5, lengthTestString5) == false)
    {
        printf("Test number 5 is incorrect");
        return 0;
    }
    if (postfixCalculator(testString5, lengthTestString5) != 10)
    {
        printf("Test number 5 is incorrect");
        return 0;
    }
    return 1;
}

int main()
{
    if (test() != 1)
    {
        printf("Error test");
        return 0;
    }
    if (!testStack())
    {
        printf("Error stack test");
        return 0;
    }

    printf("Enter the string (the first 1000 symbols are counted) ");
    char string[LIMITATION_OF_STRING] = { '\0' };
    fgets(string, LIMITATION_OF_STRING, stdin);
    int lengthString = strlen(string);
    if (stringValidation(string, lengthString - 1) == false)
    {
        printf("Unknown symbols in string or the number of operations and symbols is incorrect");
        return 0;
    }
    int result = postfixCalculator(string, lengthString - 1);
    printf("%d", result);
}