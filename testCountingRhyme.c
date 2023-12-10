#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "coutingRhyme.h"
#include "errorCodes.h"

const unsigned int testCountingRhyme(void)
{
    const int* const errorCode = OK_CODE;
     
    if (survivorStartingPosition(2, 10, &errorCode) != 5 || errorCode != OK_CODE)
    {
        printf("Error test 1\n");
        return false;
    }

    if (survivorStartingPosition(3, 41, &errorCode) != 31 || errorCode != OK_CODE)
    {
        printf("Error test 2\n");
        return false;
    }

    return true;
}
