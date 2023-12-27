#include <stdlib.h>
#include <stdio.h>

#include "HashTable.h"
#include "errorCodes.h"
#include "test.h"
#include "workWithFile.h"

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }

    const int* const errorCode = OK_CODE;
    Table* table = workWithFile("file.txt", &errorCode);
    if (errorCode != OK_CODE)
    {
        if (errorCode == ERROR_FILE)
        {
            printf("Error file");
            return ERROR_FILE;
        }

        printf("Error memory");
        return ERROR_MEMORY;
    }

    printTable(table);
    printf("\nDuty cycle: %lf\n", dutyCycle(table));
    printf("Average length: %f\n", averageLength(table));
    printf("Max length: %d", maxLength(table));
    freeTable(table);
    return OK_CODE;
}
