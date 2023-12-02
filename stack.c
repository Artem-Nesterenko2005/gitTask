#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"

#define ERROR_MEMORY NULL

typedef struct Stack
{
    int data;
    struct Stack* next;
} Stack;

Stack* push(const Stack* const top, int const data)
{
    Stack* pointer = malloc(sizeof(Stack));
    if (pointer == NULL)
    {
        return ERROR_MEMORY;
    }
    pointer->data = data;
    pointer->next = top;
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
    free(pointer);
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
