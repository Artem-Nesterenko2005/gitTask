#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "errorCodes.h"

typedef struct Stack
{
    int data;
    struct Stack* next;
} Stack;

typedef struct Queue
{
    Stack* enqueue;
    Stack* dequeue;
} Queue;

Queue* createQueue(Queue* queue)
{
    queue = (Queue*)malloc(sizeof(Queue));
    queue->dequeue = NULL;
    queue->enqueue = NULL;
    return queue;
}

Queue* push(Queue* queue, const int data, int* const errorCode)
{
    Stack* pointer = malloc(sizeof(Stack));
    if (pointer == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    pointer->data = data;
    pointer->next = queue->enqueue;
    queue->enqueue = pointer;
    return queue;
}

static Queue* stackCopy(Queue* queue, int* const errorCode)
{
    queue->dequeue = (Stack*)malloc(sizeof(Stack));
    queue->dequeue->data = queue->enqueue->data;
    queue->enqueue = queue->enqueue->next;
    while (queue->enqueue != NULL)
    {
        Stack* newStack = (Stack*)malloc(sizeof(Stack));
        if (newStack == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }

        newStack->data = queue->enqueue->data;
        Stack* delete = queue->enqueue;
        queue->enqueue = queue->enqueue->next;
        free(delete);
        queue->dequeue->next = (Stack*)malloc(sizeof(Stack));
        if (queue->dequeue->next == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        queue->dequeue->next->next = NULL;

        if (queue->enqueue == NULL)
        {
            newStack->next = NULL;
        }
        queue->dequeue->next->data = newStack->data;
        free(newStack);
    }
    return queue;
}

Queue* pop(Queue* queue, int* const errorCode)
{
    if (queue->dequeue == NULL)
    {
        if (queue->enqueue == NULL)
        {
            return NULL;
        }
        queue = stackCopy(queue, errorCode);

        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
    }
    Stack* newStack = queue->dequeue->next;
    free(queue->dequeue);
    queue->dequeue = newStack;
    return queue;
}

Stack* checkData(Queue* queue)
{
    return queue->enqueue->data;
}
