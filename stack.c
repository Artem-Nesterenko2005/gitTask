#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#include "stack.h"

typedef struct Stack
{
    size_t data;
    struct Stack* next;
}Stack;

Stack* push(Stack* top, size_t const data)
{
    Stack* pointer = malloc(sizeof(Stack));
    if (pointer == NULL)
    {
        return top;
    }
    pointer->data = data;
    pointer->next = top;
    return pointer;
}

bool isEmpty(Stack* top)
{
    return top == NULL;
}

Stack* pop(Stack* top)
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

int top(Stack* stack)
{
    return stack->data;
}
