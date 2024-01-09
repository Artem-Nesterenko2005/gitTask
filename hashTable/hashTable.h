#pragma once

#include <stdlib.h>

#include "list.h"

typedef struct Table Table;

// hash function
size_t hashFunction(const char* const key, const size_t size);

//add size table
void sizeTable(Table* const table, const size_t size);

// Add word into hash table
Table* addWord(Table* const table, const char* const word, int* const errorCode, const size_t size);

// return load factor
double loadFactor(const Table* const table);

// return average length of lists
double averageLength(const Table* const table);

// return maximum length of lists
int maxLength(const Table* const table);

// print hash table
void printTable(const Table* const table);

//delete hash table
void freeTable(Table* const table);

//check string number 
bool checkTable(Table* const table, const size_t rightResult);
