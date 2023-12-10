#include <stdio.h>
#include <stdlib.h>

#include "sortedList.h"
#include "listOperation.h"
#include "test.h"
#include "errorCode.h"

#define ORIGINAL_MEANING 1
#define EXIT_NUMBER 0

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }
    size_t transactionNumber = ORIGINAL_MEANING;
    const Node* list = NULL;
    const int* const errorCode = OK_CODE;
    while (transactionNumber != EXIT_NUMBER && errorCode == OK_CODE)
    {
        printf("0 - exit\n");
        printf("1 - add value to sorted list\n");
        printf("2 - remove value from list\n");
        printf("3 - print list\n");
        printf("Select operation: ");
        scanf_s("%Iu", &transactionNumber);
        list = listOperations(transactionNumber, list, &errorCode);
    }

    if (errorCode == ERROR_MEMORY)
    {
        clearList(&list);
        printf("Error memory");
        return ERROR_MEMORY;
    }
    clearList(&list);
    return OK_CODE;
}
