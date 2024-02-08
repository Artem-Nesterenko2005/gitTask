#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "avlTree.h"
#include "errorCodes.h"
#include "test.h"
#include "usersOperations.h"

#define VALUE_SIZE 100

int main()
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }
    int* const errorCode = OK_CODE;
    int number = 1;
    Tree* tree = NULL;
    while (number != 0 && errorCode == OK_CODE)
    {
        printf("\n0 - exit\n");
        printf("1 - add key and data\n");
        printf("2 - find data by key\n");
        printf("3 - check for key availability\n");
        printf("4 - delete a given key and its associated value\n");
        printf("Enter number of operation\n");
        scanf_s("%d", &number);
        tree = usersOperations(number, &errorCode, tree);
    }
    deleteTree(tree);
    if (&errorCode == MEMORY_ERROR)
    {
        printf("Error memory");
        return MEMORY_ERROR;
    }
    return OK_CODE;
}
