#include <stdio.h>

#include "sortedList.h"
#include "errorCode.h"

enum userOperations
{
    exit,
    addValue,
    deleteNode,
    print
};

Node* listOperations(const int numberOperation, const Node* list, int* const errorCode)
{
    int data = 0;
    switch (numberOperation)
    {
    case exit:
        break;

    case addValue:
        printf("Enter number ");
        scanf_s("%d", &data);
        printf("\n");
        list = push(list, data, errorCode);
        if (errorCode != OK_CODE)
        {
            return list;
        }
        break;

    case deleteNode:
        printf("Enter number ");
        scanf_s("%d", &data);
        list = pop(list, data, errorCode);
        if (*errorCode == SYMBOL_MISSING)
        {
            printf("Symbol missing\n");
            *errorCode = OK_CODE;
        }
        printf("\n");
        break;

    case print:
        printf("Sorted list: ");
        printList(list);
        break;

    default:
        printf("The transaction with this number does not exist\n\n");
    }
    return list;
}
