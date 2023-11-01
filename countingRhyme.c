#include <stdio.h>
#include <stdlib.h>

#include "coutingRhyme.h"
#include "list.h"
#include "testList.h"
#include "testCountingRhyme.h"

#define ERROR_CODE 0
#define END_PROGRAM 1
#define ERROR_TEST -1

const Node* listFilling(Node* list, const unsigned int numberOfWarriors)
{
    for (size_t i = 1; i <= numberOfWarriors; ++i)
    {
        list = push(list, i);
    }
    return list;
}

const unsigned int survivorStartingPosition(const unsigned int numberKilled, const unsigned int numberOfWarriors)
{
    Node* list = NULL;
    list = listFilling(list, numberOfWarriors);
    unsigned int position = 1;
    unsigned int counterSymbol = 1;
    while (top(list) != nextNodeData(list) && top(list) != -1)
    {
        if (position % numberKilled == 0)
        {
            const unsigned int deletedSymbol = symbolFromList(list, counterSymbol);
            list = pop(list, deletedSymbol);
            position = 1;
            counterSymbol = 1;
            continue;
        }
        ++position;
        ++counterSymbol;
    }
    return top(list);
}

int main(void)
{
    const unsigned int listTestResult = testList();
    if (listTestResult)
    {
        printf("Error list test %d", listTestResult);
        return ERROR_TEST;
    }

    const unsigned int countingRhymeTestResult = testCountingRhyme();
    if (countingRhymeTestResult)
    {
        printf("Error list test %d", countingRhymeTestResult);
        return ERROR_TEST;
    }

    Node* const list = NULL;
    const unsigned int numberOfWarriors = 0;
    printf("Enter number of warriors ");
    scanf_s("%d", &numberOfWarriors);
    if (numberOfWarriors == 0)
    {
        printf("Error: the number of warriors is zero");
        return ERROR_CODE;
    }

    const unsigned int numberKilled = 0;
    printf("Enter number of killed ");
    scanf_s("%d", &numberKilled);
    if (numberKilled == 0)
    {
        printf("Error: the number of killed warriors is zero");
        return ERROR_CODE;
    }
    const unsigned int position = survivorStartingPosition(numberKilled, numberOfWarriors);
    printf("The warrior numbered %d will be last", position);
    return END_PROGRAM;
}