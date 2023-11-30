#include <stdlib.h>
#include <stdbool.h>

#include "../stack/stack.h"
#include "testStack.h"

static bool testPushAndTopStack(Stack* stack)
{
    stack = push(stack, 1);
    return top(stack) == 1;
}

static bool testPopAndTopStack(Stack* stack)
{
    stack = push(stack, 1);
    stack = push(stack, 2);
    stack = pop(stack);
    return top(stack) == 1;
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
        free(stack);
        return false;
    }

    if (!testPopAndTopStack(stack))
    {
        free(stack);
        return false;
    }

    if (!testIsEmpty(stack))
    {
        free(stack);
        return false;
    }

    free(stack);
    return true;
}
