#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"
#include "errorCodes.h"

typedef struct Stack
{
    int data;
    struct Stack* next;
} Stack;

Stack* push(const Stack* top, int const data, int* const errorCode)
{
    Stack* pointer = malloc(sizeof(Stack));
    if (pointer == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return top;
    }
    pointer->data = data;
    pointer->next = top;
    *errorCode = OK_CODE;
    return pointer;
}

bool isEmpty(const Stack* const top)
{
    return top == NULL;
}

Stack* pop(const Stack* top)
{
    if (isEmpty(top))
    {
        return top;
    }
    Stack* pointer = top;
    top = top->next;
    free(&pointer->data);
    return top;
}

int top(const Stack* const stack)
{
    return stack->data;
}

Stack* nextNode(const Stack* const stack)
{
    return stack->next;
}

void clearStack(const Stack* stack)
{
    while (!isEmpty(stack))
    {
        stack = pop(&stack->data);
    }
}
