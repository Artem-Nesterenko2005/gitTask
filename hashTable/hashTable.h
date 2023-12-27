#pragma once

#include <stdlib.h>

#include "list.h"

typedef struct Table Table;

// Hash-function, that returns num from 0 to size of hash
size_t hashFunction(const char* const key);

// Add word into hash table
Table* makeTable(Table* const table, const char* const word, int* const errorCode);

// return load factor
double dutyCycle(const Table* const table);

// return average length of lists
double averageLength(const Table* const table);

// return maximum length of lists
int maxLength(const Table* const table);

// print hash table
void printTable(const Table* const table);

//delete hash table
void freeTable(Table* const table);