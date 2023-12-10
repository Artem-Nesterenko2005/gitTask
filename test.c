#include <stdbool.h>
#include <stdlib.h>

#include "sortedList.h"
#include "errorCode.h"

static bool testPush(void)
{
    const int* const errorCode = OK_CODE;
    Node* testList = NULL;
    testList = push(testList, 10, &errorCode);
    if (errorCode != OK_CODE)
    {
        clearList(&testList);
        printf("Error test number 1: push function\n");
        return false;
    }
    const bool result = dataNode(testList) == 10;
    free(testList);
    return result;
}

static bool testPop(void)
{
    const int* const errorCode = OK_CODE;
    Node* testList = NULL;
    testList = push(testList, 10, &errorCode);
    if (errorCode != OK_CODE)
    {
        clearList(&testList);
        printf("Error test number 2: push function\n");
        return false;
    }

    if (dataNode(testList) != 10)
    {
        clearList(&testList);
        printf("Error test number 2: push function\n");
        return false;
    }

    testList = push(testList, 20, &errorCode);
    if (errorCode != OK_CODE)
    {
        clearList(&testList);
        printf("Error test number 2: push function\n");
        return false;
    }

    if (dataNode(nextNode(testList)) != 20)
    {
        clearList(&testList);
        printf("Error test number 2: push function\n");
        return false;
    }

    testList = pop(testList, 10, &errorCode);
    testList = pop(testList, 15, &errorCode);
    const bool result = dataNode(testList) == 20 && errorCode == SYMBOL_MISSING;
    if (!result)
    {
        printf("Error test number 2: pop function\n");
    }
    clearList(&testList);
    return result;
}

bool test(void)
{
    return testPush() && testPop();
}
