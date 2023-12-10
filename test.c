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
        printf("Error test number 1");
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
        return false;
        printf("Error test number 2");
    }

    if (dataNode(testList) != 10)
    {
        return false;
    }

    testList = push(testList, 20, &errorCode);
    if (errorCode != OK_CODE)
    {
        return false;
        printf("Error test number 2");
    }

    if (dataNode(nextNode(testList)) != 20)
    {
        return false;
        printf("Error test number 2");
    }

    testList = pop(testList, 15, &errorCode);
    testList = pop(testList, 10, &errorCode);
    return dataNode(testList) == 20 && errorCode == SYMBOL_MISSING;
}

bool test(void)
{
    return testPush() && testPop();
}
