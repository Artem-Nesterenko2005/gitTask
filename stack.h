#pragma once

#include <stdbool.h>

//Struct for stack
typedef struct Stack Stack;

//Places an element on the top of the stack
Stack* push(const Stack* top, int const data, int* const errorCode);

//Checks the stack for elements content
bool isEmpty(const Stack* const top);

//Removes an element from the top of the stack
Stack* pop(const Stack* top);

//Points to data from the top of the stack
int top(const Stack* const stack);

//Return next node of stack
Stack* nextNode(const Stack* const stack);

//clear steack
void clearStack(const Stack* stack);
