#pragma once

#include <stdbool.h>

//Struct for stack
typedef struct Stack Stack;

//Places an element on the top of the stack
Stack* push(Stack* top, int data);

//Checks the stack for elements content
bool isEmpty(Stack* top);

//Removes an element from the top of the stack
Stack* pop(Stack* top);

//Points to data from the top of the stack
int top(Stack* stack);

