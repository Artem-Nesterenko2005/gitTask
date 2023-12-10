#include <stdio.h>
#include <stdlib.h>

#include "coutingRhyme.h"
#include "list.h"
#include "errorCodes.h"

Node* listFilling(Node* list, const unsigned int numberOfWarriors, int* const errorCode)
{
    for (unsigned int i = 1; i <= numberOfWarriors; ++i)
    {
        list = push(list, i, errorCode);
        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
    }
    return list;
}

const unsigned int survivorStartingPosition(const unsigned int numberKilled, const unsigned int numberOfWarriors, int* const errorCode)
{
    Node* list = NULL;
    list = listFilling(list, numberOfWarriors, errorCode);
    if (list == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return 0;
    }
    unsigned int position = 1;
    while (top(list) != nextNodeData(list))
    {
        if ((position + 1 ) % numberKilled == 0)
        {
            list = deleteNext(list, errorCode);
            if (*errorCode != OK_CODE)
            {
                return 0;
            }
            position = 1;
            list = nextNode(list);
            continue;
        }
        ++position;
        list = nextNode(list);
    }
    const unsigned int result = top(list);
    free(list);
    return result;
}
