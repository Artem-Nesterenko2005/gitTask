#include <stdio.h>
#include <stdlib.h>

#include "coutingRhyme.h"
#include "list.h"
#include "errorCodes.h"

const unsigned int survivorStartingPosition(const unsigned int numberKilled, const unsigned int numberOfWarriors, int* const errorCode)
{
    Node* list = NULL;
    list = listFilling(numberOfWarriors, errorCode);
    if (list == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return 0;
    }
    unsigned int position = 1;
    while (list != list->next)
    {
        if ((position + 1) % numberKilled == 0)
        {
            list = deleteNext(list, errorCode);
            position = 0;
            list = nextNode(list);
        }
        ++position;
        list = nextNode(list);
    }
    const unsigned int result = top(list);
    free(list);
    return result;
}
