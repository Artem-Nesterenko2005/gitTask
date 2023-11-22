#include <malloc.h>
#include <stdbool.h>

#include "stack.h"

typedef struct Stack
{
    int data;
    struct Stack* next;
}Stack;

Stack* push(Stack* top, int data)
{
    Stack* pointer = malloc(sizeof(Stack));
    if (pointer == NULL)
    {
        return 0;
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
    return top->next;
}

int top(Stack* stack)
{
    return stack->data;
}

