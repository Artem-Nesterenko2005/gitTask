#include <stdio.h>
#include <stdlib.h>

#include "errorCodes.h"
#include "list.h"
#include "coutingRhyme.h"
#include "testCountingRhyme.h"
#include "testList.h"

int main(void)
{
    
    if (!testList())
    {
        printf("Error list test");
        return ERROR_LIST_TEST;
    }

    if (!testCountingRhyme())
    {
        printf("Error countingRhyme module test");
        return ERROR_TEST;
    }

    const int* const errorCode = OK_CODE;

    const unsigned int numberOfWarriors = 0;
    printf("Enter number of warriors ");
    scanf_s("%d", &numberOfWarriors);
    if (numberOfWarriors == 0)
    {
        printf("Error: the number of warriors is zero");
        return NULL_VARIABLES;
    }

    const unsigned int numberKilled = 0;
    printf("Enter number of killed ");
    scanf_s("%d", &numberKilled);
    if (numberKilled == 0)
    {
        printf("Number of the person being killed: %d", numberKilled);
        return NULL_VARIABLES;
    }
    const unsigned int position = survivorStartingPosition(numberKilled, numberOfWarriors, &errorCode);
    if (errorCode == ERROR_MEMORY)
    {
        printf("Error memory");
        return ERROR_MEMORY;
    }
    printf("The warrior numbered %d will be last", position);
    return OK_CODE;
}
