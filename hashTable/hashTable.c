#include <stdlib.h>
#include <string.h>

#include "errorCodes.h"
#include "hashTable.h"
#include "list.h"

#define NUMBER 174

typedef struct Table
{
    size_t quantity;
    List* hashes[NUMBER];
} Table;

size_t hashFunction(const char* const key)
{
    size_t result = 0;
    size_t length = strlen(key);
    for (size_t i = 0; i < length; ++i)
    {
        result = key[i] + result * NUMBER / 10;
    }
    return result % NUMBER;
}

Table* makeTable(Table* table, const char* const word, int* const errorCode)
{
    if (table == NULL)
    {
        table = (Table*)calloc(1, sizeof(Table));
        if (table == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
    }
    const int hashWord = hashFunction(word);
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

    newData(table->hashes[hashWord]);
    return table;
}

double dutyCycle(const Table* const table)
{
    if (table == NULL)
    {
        return 0;
    }
    return (double)table->quantity / NUMBER;
}

double averageLength(const Table* const table)
{
    if (table == NULL)
    {
        return;
    }
    size_t numberList = 0;
    size_t numberNode = 0;
    for (size_t i = 0; i < NUMBER; ++i)
    {
        if (table->hashes[i] == NULL)
        {
            continue;
        }
        ++numberList;
        numberNode += length(table->hashes[i]);
    }
    return numberNode / (double)numberList;
}

int maxLength(const Table* const table)
{
    if (table == NULL)
    {
        return 0;
    }
    int tableLength = 0;
    for (size_t i = 0; i < NUMBER; ++i)
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

    for (size_t i = 0; i < NUMBER; ++i)
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
    for (size_t i = 0; i < NUMBER; ++i)
    {
        if (table->hashes[i] == NULL)
        {
            continue;
        }
        table->hashes[i] = deleteList(table->hashes[i]);
    }
}