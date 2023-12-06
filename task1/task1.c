#include <stdio.h>
#include <stdlib.h>

#include"list.h"
#include "removeOddIndex.h"
#include "test.h"

#define ERROR_TEST -1

int main(void)
{
    if (test() != true)
    {
        printf("Error test");
        return ERROR_TEST;
    }
    Node* list = NULL;
    list = push(list, 24);
    list = push(list, 1);
    list = push(list, 534);
    list = push(list, 2);
    list = push(list, 72);
    list = push(list, 84);
    print(list);
    removeOddIndexes(list);
    removeOddIndexes(list);
    print(list);
}


