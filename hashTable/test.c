#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "errorCodes.h"
#include "hashTable.h"
#include "workWithFile.h"

bool test(void)
{
    const int* const errorCode = OK_CODE;
    Table* table = workWithFile("test.txt", &errorCode);
    bool result1 = dutyCycle(table) == 0.017241379310344827;
    bool result2 = maxLength(table) == 1;
    bool result3 = averageLength(table) == 1;
    freeTable(table);
    return result1 && result2 && result3 && errorCode == OK_CODE;
}
