#include <stdlib.h>
#include <stdbool.h>

#include "../postfixCalculator/stack.h"
#include "testStack.h"

static bool testPushAndTopStack(Stack* stack)
{
    stack = push(stack, 1);
    const bool result = !isEmpty(stack) && top(stack) == 1;
    free(stack);
    return result;

    return false;
}

static bool testPopAndTopStack(Stack* stack)
{
    stack = push(stack, 1);
    if (stack == NULL)
    {
        return false;
    }

    stack = push(stack, 2);
    if (stack == NULL)
    {
        return false;
    }

    stack = pop(stack);
    const bool result = top(stack) == 1;
    free(stack);
    return result;
}

static bool testIsEmpty(Stack* stack)
{
    return isEmpty(stack);
}

bool testStack(void)
{
    Stack* stack = NULL;
    if (!testPushAndTopStack(stack))
    {
        return false;
    }

    if (!testPopAndTopStack(stack))
    {
        return false;
    }

    if (!testIsEmpty(stack))
    {
        return false;
    }

    return true;
}
