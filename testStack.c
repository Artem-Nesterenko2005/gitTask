#include <stdlib.h>
#include <stdbool.h>

#include "../postfixCalculator/stack.h"
#include "testStack.h"
#include "errorCodes.h"

static bool testPushAndTopStack(void)
{
    int* const errorCode = OK_CODE;
    Stack* stack = NULL;
    stack = push(stack, 1, errorCode);
    const bool result = !isEmpty(stack) && top(stack) == 1 && errorCode == OK_CODE;
    clearStack(stack);
    return result;
}

static bool testPopAndTopStack(void)
{
    int* const errorCode = OK_CODE;
    Stack* stack = NULL;
    stack = push(stack, 1, errorCode);
    if (stack == NULL || errorCode != OK_CODE)
    {
        return false;
    }

    stack = push(stack, 2, errorCode);
    if (stack == NULL || errorCode != OK_CODE)
    {
        return false;
    }

    stack = pop(stack);
    const bool result = top(stack) == 1 && errorCode == OK_CODE;
    clearStack(stack);
    return result;
}

static bool testIsEmpty(void)
{
    Stack* stack = NULL;
    return isEmpty(stack);
}

bool testStack(void)
{
    return testPushAndTopStack() && testPopAndTopStack() && testIsEmpty();
}
