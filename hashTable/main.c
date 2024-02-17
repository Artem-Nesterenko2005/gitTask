#include <stdlib.h>
#include <stdio.h>

#include "hashTable.h"
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

    int errorCode = OK_CODE;
    Table* table = workWithFile("file.txt", &errorCode, 174);
    if (errorCode != OK_CODE)
    {
        if (errorCode == ERROR_FILE)
        {
            printf("Error file");
            freeTable(table);
            return ERROR_FILE;
        }

        printf("Error memory");
        freeTable(table);
        return ERROR_MEMORY;
    }

    printTable(table);
    printf("\nLoad factor: %lf\n", loadFactor(table));
    printf("Average length: %f\n", averageLength(table));
    printf("Max length: %Iu", maxLength(table));
    freeTable(table);
    return OK_CODE;
}
