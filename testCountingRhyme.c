#include <stdbool.h>
#include <stdlib.h>

#include "list.h"
#include "testList.h"
#include "coutingRhyme.h"

#define RIGHT_LIST_TEST 0

bool listFillingTest(Node* list)
{
    for (size_t i = 1; i < 6; ++i)
    {
        if (i != top(list))
        {
            return false;
        }
        list = nextNode(list);
    }
    return true;
}

const unsigned int testCountingRhyme(void)
{
    if (testList() != RIGHT_LIST_TEST)
    {
        return 1;
    }
    Node* list = NULL;
     
    if (survivorStartingPosition(2, 10) != 5)
    {
        return 2;
    }
    list = pop(list, 5);

    if (survivorStartingPosition(3, 41) != 31)
    {
        return 3;
    }
    list = pop(list, 31);

    list = listFilling(list, 5);
    if (!listFillingTest(list))
    {
        return 4;
    }

    return 0;
}

