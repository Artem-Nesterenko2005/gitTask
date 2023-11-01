#include <stdlib.h>

#include "list.h"
#include "testList.h"

#define RIGHT_TESTS 0


const unsigned int testList(void)
{
    Node* testList = NULL;
    testList = push(testList, 5);
    testList = push(testList, 3);
    if (top(testList) != 5)
    {
        return 1;
    }
    testList = pop(testList, 5);
    if (top(testList) != 3)
    {
        return 2;
    }
    testList = push(testList, 7);
    if (nextNodeData(testList) != 7)
    {
        return 3;
    }
    testList = push(testList, 10);
    if (symbolFromList(testList, 3) != 10)
    {
        return 4;
    }
    return RIGHT_TESTS;
}

