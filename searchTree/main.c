#include <stdio.h>
#include <stdbool.h>

#include "tree.h";
#include "searchTree.h"
#include "errorCodes.h"
#include "test.h"

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }
    int* const errorCode = OK_CODE;
    unsigned int numberOperation = 0;
    const Tree* tree = NULL;
    while (numberOperation != 5)
    {
        if (errorCode != OK_CODE)
        {
            printf("Memory error");
            return MEMORY_ERROR;
        }
        printf("\n1 - add data\n");
        printf("2 - get data by key\n");
        printf("3 - check for the presence of a key\n");
        printf("4 - delete data by key and key\n");
        printf("5 - exit\n");
        printf("Enter number of operation ");
        scanf_s("%d", &numberOperation);
        tree = operation(numberOperation, &errorCode, tree);
    }
    clearTree(tree);
    return OK_CODE;
}
