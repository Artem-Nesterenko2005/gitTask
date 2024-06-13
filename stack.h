#pragma once

// struct for queue
typedef struct Queue Queue;

// struct for stack
typedef struct Stack Stack;

// create queue
Queue* createQueue(Queue* queue);

// push data to stack
Queue* push(Queue* const stack, const int data, int* const errorCode);

// pop data to stack
Queue* pop(Queue* queue, int* const errorCode);

// check data from top of stack
Stack* checkData(Queue* queue);
