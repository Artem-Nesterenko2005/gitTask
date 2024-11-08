#pragma once

#include <stdlib.h>

#include "list.h"

// struct for table
typedef struct Table Table;

// create hash table
Table* createHashTable(const size_t size, int* errorCode);

// add word into hash table
Table* addWord(Table* const table, char* word, int* errorCode);

// return load factor
double loadFactor(const Table* const table);

// return average length of lists
double averageLength(const Table* const table);

// return maximum length of lists
size_t maxLength(const Table* const table);

// print hash table
void printTable(const Table* const table);

// delete hash table
void freeTable(Table* const table);

// check string number 
bool checkTable(Table* const table, const size_t rightResult);
