#include "../stack/stack.h"
#include "testStack.h"

#include <stdlib.h>

bool testPushAndTopStack()
{
    Stack* stack = NULL;
    stack = push(stack, 'h');
    return top(stack) == 'h';
}

bool testPopAndTopStack()
{
    Stack* stack = NULL;
    stack = push(stack, 'h');
    stack = push(stack, 'b');
    stack = pop(stack);
    return top(stack) == 'h';
}

bool testIsEmpty()
{
    Stack* stack = NULL;
    return isEmpty(stack);
}

bool testStack()
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