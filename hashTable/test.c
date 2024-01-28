#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

#include "errorCodes.h"
#include "hashTable.h"
#include "workWithFile.h"

static bool randomStringsTest(void)
{
    Table* table = NULL;
    int* const errorCode = OK_CODE;
    table = createHashTable(table, 200, &errorCode);
    if (errorCode != OK_CODE)
    {
        freeTable(table);
        return false;
    }
    srand(time(NULL));
    double startTick = clock();
    for (size_t i = 0; i < 100000; ++i)
    {
        char* word = (char*)malloc(10 * sizeof(char));
        if (word == NULL)
        {
            freeTable(table);
            return false;
        }

        for (size_t j = 0; j < 10; ++j)
        {
            word[j] = rand() % 10000;
        }
        table = addWord(table, word, &errorCode, 200);
        if (errorCode != OK_CODE)
        {
            return false;
        }
    }
    double finishTick = clock();
    const bool result = (finishTick - startTick) / CLOCKS_PER_SEC <= 3;
    freeTable(table);
    return result;
}

bool test(void)
{
    const int* const errorCode = OK_CODE;
    Table* table =  workWithFile("test.txt", &errorCode, 5);
    const bool result = checkTable(table, 4) && errorCode == OK_CODE;
    freeTable(table);

    return randomStringsTest() && result;
}
