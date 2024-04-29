#pragma once

// struct for table
typedef struct Table Table;

// enum states for automat
typedef enum States States;

// lexer returning comments from a file.c
char* commentLexer(char* filename, char* string, int* errorCode);
