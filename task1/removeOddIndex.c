#include <stdlib.h>

#include "list.h"
#include "removeOddIndex.h"

void removeOddIndexes(Node* list)
{
    {
        Node* pointer = list;
        while (list != NULL)
        {
            if (nextNode(list) == NULL)
            {
                break;
            }
            list = pop(list);
            list = nextNode(list);
        }
    }
}

