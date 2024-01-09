﻿#include <stdlib.h>
#include <string.h>

#include "errorCodes.h"
#include "hashTable.h"
#include "list.h"

#define NUMBER 174

typedef struct Table
{
    size_t quantity;
    List** hashes;
    size_t size;
} Table;

size_t hashFunction(const char* const key, const size_t size)
{
    size_t result = 0;
    size_t length = strlen(key);
    for (size_t i = 0; i < length; ++i)
    {
        result = key[i] + result * NUMBER / 10;
    }
    return result % size;
}

void sizeTable(Table* const table, const size_t size)
{
    table->size = size;
}

Table* addWord(Table* table, const char* const word, int* const errorCode, const size_t size)
{
    if (table == NULL)
    {
        table = (Table*)calloc(1, sizeof(Table));
        if (table == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        sizeTable(table, size);
        table->hashes = (List**)calloc(table->size, sizeof(List*));
        if (table->hashes == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
    }
    const int hashWord = hashFunction(word, table->size);
    if (table->hashes[hashWord] == NULL)
    {
        ++table->quantity;
        table->hashes[hashWord] = addData(table->hashes[hashWord], word, errorCode);
        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
        return table;
    }

    if (checkNodes(table->hashes[hashWord], word))
    {
        ++table->quantity;
        table->hashes[hashWord] = addData(table->hashes[hashWord], word, errorCode);
        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
        return table;
    }

    newData(table->hashes[hashWord], word);
    return table;
}

double loadFactor(const Table* const table)
{
    if (table == NULL)
    {
        return 0;
    }
    return (double)table->quantity / table->size;
}

double averageLength(const Table* const table)
{
    if (table == NULL)
    {
        return;
    }
    size_t numberLists = 0;
    size_t numberNodes = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] == NULL)
        {
            continue;
        }
        ++numberLists;
        numberNodes += length(table->hashes[i]);
    }
    return numberLists == 0 ? 0 : numberNodes / (double)numberLists;
}

int maxLength(const Table* const table)
{
    if (table == NULL)
    {
        return 0;
    }
    int tableLength = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] == NULL)
        {
            continue;
        }

        tableLength = length(table->hashes[i]) > tableLength ? length(table->hashes[i]) : tableLength;       
    }
    return tableLength;
}

void printTable(const Table* const table)
{
    if (table == NULL)
    {
        return;
    }

    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] == NULL)
        {
            continue;
        }
        printList(table->hashes[i]);
    }
}

void freeTable(Table* table)
{
    if (table == NULL)
    {
        return;
    }
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] == NULL)
        {
            free(table->hashes[i]);
            continue;
        }
        deleteList(table->hashes[i]);
        free(table->hashes[i]);
    }
    free(table);
}

bool checkTable(Table* const table, const size_t rightResult)
{
    size_t result = 0;
    for (size_t i = 0; i < table->size; ++i)
    {
        if (table->hashes[i] != NULL)
        {
            result += checkList(table->hashes[i]);
        }
    }

    return result == rightResult;
}
