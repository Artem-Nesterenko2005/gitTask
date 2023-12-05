#include <stdio.h>
#include <stdbool.h>

#include "tree.h";
#include "searchTree.h"
#include "test.h"

#define ERROR_TEST -1

void main(void)
{
    if (test() != true)
    {
        printf("Error test");
        return ERROR_TEST;
    }
    unsigned int numberOperation = 0;
    while (numberOperation != 5)
    {
        printf("\n1 - add data\n");
        printf("2 - get data by key\n");
        printf("3 - check for the presence of a key\n");
        printf("4 - delete data by key and key\n");
        printf("5 - exit\n");
        printf("Enter number of operation ");
        scanf_s("%d", &numberOperation);
        operation(numberOperation);
    }
}

