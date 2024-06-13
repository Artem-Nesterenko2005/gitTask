#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#include "errorCodes.h"
#include "stack.h"
#include "test.h"

int main(void)
{
    if (!test())
    {
        printf("Erorr test");
        return ERROR_TEST;
    }
    int* const errorCode = OK_CODE;
    Queue* queue = NULL;
    queue = createQueue(queue);
    if (errorCode != OK_CODE)
    {
        printf("Memory error");
        return ERROR_MEMORY;
    }

    queue = push(queue, 10, &errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Memory error");
        return ERROR_MEMORY;
    }

    queue = push(queue, 12, &errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Memory error");
        return ERROR_MEMORY;
    }

    queue = pop(queue, &errorCode);
    if (errorCode != OK_CODE)
    {
        printf("Memory error");
        return ERROR_MEMORY;
    }
    return OK_CODE;
}
