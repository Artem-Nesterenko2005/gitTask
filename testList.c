#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "testList.h"
#include "errorCodes.h"

const unsigned int testList(void)
{
    Node* testList = NULL;
    const int* const errorCode = OK_CODE;

    testList = push(testList, 5, &errorCode);
    if (errorCode != OK_CODE)
    {
        clearList(testList);
        printf("Error test 1\n");
        return false;
    }

    testList = push(testList, 3, &errorCode);
    if (top(testList) != 5 || errorCode != OK_CODE)
    {
        clearList(testList);
        printf("Error test 2\n");
        return false;
    }

    testList = deleteNext(testList, &errorCode);
    if (top(testList) != 5 || errorCode != OK_CODE)
    {
        clearList(testList);
        printf("Error test 3\n");
        return false;
    }

    clearList(testList);
    return true;
}
