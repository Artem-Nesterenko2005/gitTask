#include <stdlib.h>
#include <stdbool.h>

#include "../stack/stack.h"
#include "testStack.h"

bool testPushAndTopStack(void)
{
    Stack* stack = NULL;
    stack = push(stack, 1);
    return top(stack) == 1;
}

bool testPopAndTopStack(void)
{
    Stack* stack = NULL;
    stack = push(stack, 1);
    stack = push(stack, 2);
    stack = pop(stack);
    return top(stack) == 1;
}

bool testIsEmpty(void)
{
    Stack* stack = NULL;
    return isEmpty(stack);
}

bool testStack(void)
{
    bool test1 = testPushAndTopStack();
    bool test2 = testPopAndTopStack();
    bool test3 = testIsEmpty();
    if (!test1 || !test2 || !test3)
    {
        return false;
    }
    return true;
}

