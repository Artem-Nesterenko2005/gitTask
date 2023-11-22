#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "removeOddIndex.h"

const bool test(void)
{
    Node* list = NULL;
    list = push(list, 10);
    if (data(list) != 10)
    {
        printf("Error test number 1\n");
        return false;
    }

    list = pop(list);
    if (list != NULL)
    {
        printf("Error test number 2\n");
        return false;
    }

    list = push(list, 5);
    list = push(list, 15);
    list = push(list, 4);
    removeOddIndexes(list);
    if (data(nextNode(list)) != 4)
    {
        printf("Error test number 3\n");
        return false;
    }

    return true;
}

