#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "../stack/stack.h"
#include "../testStack/testStack.h"

#define LIMITATION_OF_STRING 1000

int priority(char symbol)
{
    int priority = 0;
    switch (symbol)
    {
    case '-':
    case '+':
        priority = 1;
        break;
    case '*':
    case '/':
        priority = 2;
        break;
    default:
        priority = 0;
        break;
    }
    return priority;
}

void stringProcessing(char string[], char finalString[], int lengthString)
{
    Stack* stack = NULL;
    int numberSymbolFinalString = 0;
    for (int numberSymbol = 0; numberSymbol < lengthString - 1; ++numberSymbol)
    {
        if (string[numberSymbol] == '(')
        {
            stack = push(stack, string[numberSymbol]);
            continue;
        }
        if (string[numberSymbol] == ')')
        {
            while (top(stack) != '(')
            {
                finalString[numberSymbolFinalString] = top(stack);
                stack = pop(stack);
                ++numberSymbolFinalString;
            }
            stack = pop(stack);
            continue;
        }
        int prioritySymbol = priority(string[numberSymbol]);
        switch (prioritySymbol)
        {

        case 0:
            finalString[numberSymbolFinalString] = string[numberSymbol];
            ++numberSymbolFinalString;
            break;

        case 1:
        case 2:
            if (isEmpty(stack) == 1)
            {
                stack = push(stack, string[numberSymbol]);
                break;
            }
            if (priority(top(stack)) < prioritySymbol)
            {
                stack = push(stack, string[numberSymbol]);
                break;
            }
            if (priority(top(stack)) == prioritySymbol)
            {
                finalString[numberSymbolFinalString] = top(stack);
                stack = pop(stack);
                stack = push(stack, string[numberSymbol]);
                ++numberSymbolFinalString;
                break;
            }
            while (priority(top(stack)) >= prioritySymbol)
            {
                finalString[numberSymbolFinalString] = top(stack);
                stack = pop(stack);
                ++numberSymbolFinalString;
                if (isEmpty(stack) == 1)
                {
                    stack = push(stack, string[numberSymbol]);
                    break;
                }
            }
        }
    }
    while (stack != NULL)
    {
        finalString[numberSymbolFinalString] = top(stack);
        stack = pop(stack);
       ++numberSymbolFinalString;
    }
}

int test()
{
    char testString1[LIMITATION_OF_STRING] = { "1/2/3/4/5/6\n" };
    char finalTestString1[LIMITATION_OF_STRING] = { '\0' };
    int lengthString1 = strlen(testString1);
    stringProcessing(testString1, finalTestString1, lengthString1);
    if (strcmp(finalTestString1, "12/3/4/5/6/") != 0)
    {
        printf("Error test number 1");
        return 0;
    }

    char testString2[LIMITATION_OF_STRING] = { "(1-2*3)*4-5\n" };
    char finalTestString2[LIMITATION_OF_STRING] = { '\0' };
    int lengthString2 = strlen(testString2);
    stringProcessing(testString2, finalTestString2, lengthString2);
    if (strcmp(finalTestString2, "123*-4*5-") != 0)
    {
        printf("Error test number 2");
        return 0;
    }

    char testString3[LIMITATION_OF_STRING] = { "1-2/3+4\n" };
    char finalTestString3[LIMITATION_OF_STRING] = { '\0' };
    int lengthString3 = strlen(testString3);
    stringProcessing(testString3, finalTestString3, lengthString3);
    if (strcmp(finalTestString3, "123/-4+") != 0)
    {
        printf("Error test number 3");
        return 0;
    }

    char testString4[LIMITATION_OF_STRING] = { "1*(2+3)-4/(5*6)\n" };
    char finalTestString4[LIMITATION_OF_STRING] = { '\0' };
    int lengthString4 = strlen(testString4);
    stringProcessing(testString4, finalTestString4, lengthString4);
    if (strcmp(finalTestString4, "123+*456*/-") != 0)
    {
        printf("Error test number 4");
        return 0;
    }

    char testString5[LIMITATION_OF_STRING] = { "" };
    char finalTestString5[LIMITATION_OF_STRING] = { '\0' };
    int lengthString5 = strlen(testString4);
    stringProcessing(testString5, finalTestString5, lengthString5);
    if (strcmp(finalTestString5, "") != 0)
    {
        printf("Error test number 5");
        return 0;
    }
    return 1;
}

int main()
{
    if (test() == 0)
    {
        printf("Error test");
        return 0;
    }
    if (!testStack())
    {
        printf("Error stack test");
        return 0;
    }
    printf("Enter an expression: ");
    char string[LIMITATION_OF_STRING] = { '\0' };
    fgets(string, LIMITATION_OF_STRING, stdin);
    int lengthString = strlen(string);
    char finalString[LIMITATION_OF_STRING] = { '\0' };
    stringProcessing(string, finalString, lengthString);
    int lengthFinalString = strlen(finalString);
    printf("Postfix form: ");
    for (int counter = 0; counter < lengthFinalString; ++counter)
    {
        printf("%c", finalString[counter]);
    }
}