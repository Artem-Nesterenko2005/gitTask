#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../stack/stack.h"
#include "../testStack/testStack.h"

#define LIMITATION_OF_STRING 1000

char changeBrackets(char symbol)
{
    switch (symbol)
    {
    case ']':
        return '[';
    case ')':
        return '(';
    case '}':
        return '{';
    }
}

int bracketsBalance(char string[], int length)
{
    Stack* stack = NULL;
    for (int numberSymbol = 0; numberSymbol < length; ++numberSymbol)
    {
        switch (string[numberSymbol])
        {
        case '[':
        case '{':
        case '(':

            stack = push(stack, string[numberSymbol]);
            break;

        case ']':
        case '}':
        case ')':
            if (stack == NULL)
            {
                return 0;
            }
            if (changeBrackets(string[numberSymbol]) != top(stack))
            {
               return 0;
            }
          stack = pop(stack);
          break;
        }
    }
    if (stack != NULL)
    {
        return 0;
    }
    return 1;
}

int test()
{
    char testString1[LIMITATION_OF_STRING] = { "(((((" };
    int lengthTestString1 = strlen(testString1);
    int resultTest1 = bracketsBalance(testString1, lengthTestString1);
    if (resultTest1 == 1)
    {
        printf("Error test number 1\n");
        return 0;
    }

    char testString2[LIMITATION_OF_STRING] = { "({[]})" };
    int lengthTestString2 = strlen(testString2);
    int resultTest2 = bracketsBalance(testString2, lengthTestString2);
    if (resultTest2 == 0)
    {
        printf("Error test number 2\n");
        return 0;
    }

    char testString3[LIMITATION_OF_STRING] = { "]]]]]" };
    int lengthTestString3 = strlen(testString3);
    int resultTest3 = bracketsBalance(testString3, lengthTestString3);
    if (resultTest3 == 1)
    {
        printf("Error test number 3\n");
        return 0;
    }

    char testString4[LIMITATION_OF_STRING] = { "{(})" };
    int lengthTestString4 = strlen(testString4);
    int resultTest4 = bracketsBalance(testString4, lengthTestString4);
    if (resultTest4 == 1)
    {
        printf("Error test number 4\n");
        return 0;
    }

    char testString5[LIMITATION_OF_STRING] = { "()[{}]({}[])" };
    int lengthTestString5 = strlen(testString5);
    int resultTest5 = bracketsBalance(testString5, lengthTestString5);
    if (resultTest5 == 0)
    {
        printf("Error test number 5\n");
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
    char string[LIMITATION_OF_STRING] = { '\0' };
    printf("Enter string (no more than 10000 symbols): ");
    fgets(string, LIMITATION_OF_STRING, stdin);
    int length = strlen(string);
    int result = bracketsBalance(string, length);
    printf(result == 0 ? "String is not correct" : "String is correct");
}