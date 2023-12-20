#include <stdbool.h>
#include <string.h>

#include "errorCodes.h"
#include "stack.h"

bool test(void)
{
    int* const errorCode = OK_CODE;
    Queue* queue = NULL;
    queue = createQueue(queue);
    if (errorCode != OK_CODE)
    {
        return false;
    }

    queue = push(queue, 10, &errorCode);
    if (errorCode != OK_CODE || checkData(queue) != 10)
    {
        return false;
    }

    return true;
}
