#pragma once

#include <stdbool.h>

//Струкутра для стека
typedef struct Stack Stack;

//Помещает элемент на верх стека
Stack* push(Stack* top, char data);

//Проверяет стек на содержаение элементов
bool isEmpty(Stack* top);

//Удаляет элемент с верха стека
Stack* pop(Stack* top);

//Указывает на данные с верха стека
int top(Stack* stack);
