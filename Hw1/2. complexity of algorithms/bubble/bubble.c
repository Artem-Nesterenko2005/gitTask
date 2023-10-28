#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>

#define ARRAY_LENGTH 100000
#define AUXILIARY_ARRAY_LENGTH 10
#define ARRAY_FOR_COUNT_SORT 100
#define END_OF_PROGRAM 1
#define ERROR_TESTS -1
#define MEMORY_ERROR -2

void static bubbleSort(int array[], int length)
{
    for (int iterationCounter = 0; iterationCounter < length - 1; ++iterationCounter)
    {
        for (int numberSymbol = 0; numberSymbol < length - 1 - iterationCounter; ++numberSymbol)
        {
            if (array[numberSymbol] > array[numberSymbol + 1])
            {
                int swapSymbols = array[numberSymbol];
                array[numberSymbol] = array[numberSymbol + 1];
                array[numberSymbol + 1] = swapSymbols;
            }
        }
    }
}

void static countSort(int array[], int length)
{
    int auxiliaryArray[ARRAY_FOR_COUNT_SORT] = { 0 };
    for (int indexFillingArray = 0; indexFillingArray <= length - 1; ++indexFillingArray)
    {
        int number = array[indexFillingArray];
        ++auxiliaryArray[number];
    }
    int counter = 0;
    int indexNumber = 0;
    for (int auxiliaryArrayIndex = 0; auxiliaryArrayIndex < ARRAY_FOR_COUNT_SORT; ++auxiliaryArrayIndex)
    {
        int variblesAuxiliaryArray = auxiliaryArrayIndex;
        while (auxiliaryArray[auxiliaryArrayIndex] > 0)
        {
            array[indexNumber] = counter;
            --auxiliaryArray[auxiliaryArrayIndex];
            ++indexNumber;
        }
        ++counter;
        auxiliaryArrayIndex = variblesAuxiliaryArray;
    }
}

bool static bubbleSortTest(void)
{
    int testArray1[AUXILIARY_ARRAY_LENGTH] = { 543,12,34,54,85,12,543,65,12,43 };
    bubbleSort(testArray1, AUXILIARY_ARRAY_LENGTH);
    int testResult = 0;
    for (int testCounter = 0; testCounter < AUXILIARY_ARRAY_LENGTH; ++testCounter)
    {
        if (testArray1[testCounter] <= testArray1[testCounter + 1])
        {
            ++testResult;
        }
    }
    int testArray2[AUXILIARY_ARRAY_LENGTH] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    bubbleSort(testArray2, AUXILIARY_ARRAY_LENGTH);
    for (int testCounter = 0; testCounter < AUXILIARY_ARRAY_LENGTH; ++testCounter)
    {
        if (testArray2[testCounter] <= testArray2[testCounter + 1])
        {
            ++testResult;
        }
    }
    return testResult;
}

bool static countSortTest(void)
{
    int testArray1[AUXILIARY_ARRAY_LENGTH] = { 53,12,34,54,85,12,53,65,12,43 };
    countSort(testArray1, AUXILIARY_ARRAY_LENGTH);
    int testResult = 0;
    for (int testCounter = 0; testCounter < AUXILIARY_ARRAY_LENGTH; ++testCounter)
    {
        if (testArray1[testCounter] <= testArray1[testCounter + 1])
        {
            ++testResult;
        }
    }

    int testArray2[AUXILIARY_ARRAY_LENGTH] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    countSort(testArray2, AUXILIARY_ARRAY_LENGTH);
    for (int testCounter = 0; testCounter < AUXILIARY_ARRAY_LENGTH; ++testCounter)
    {
        if (testArray2[testCounter] <= testArray2[testCounter + 1])
        {
            ++testResult;
        }
    }
    return testResult;
}

int main(void)
{
    int resultBubbleSortTest = bubbleSortTest();
    int resultCountSortTest = countSortTest();
    if (resultBubbleSortTest && resultCountSortTest)
    {
        printf("Error test");
        return ERROR_TESTS;
    }

    int* arrayForBubbleSort = 0;
    arrayForBubbleSort = malloc(ARRAY_LENGTH * sizeof(int));
    if (!arrayForBubbleSort)
    {
        printf("Error: no memory allocated");
        return MEMORY_ERROR;
    }
    double startTickForBubbleSort = clock();
    bubbleSort(arrayForBubbleSort, ARRAY_LENGTH);
    double finishTickForBubbleSort = clock();
    printf("Bubble sort running time on an array of 100,000 elements: %.3lf seconds\n", (finishTickForBubbleSort - startTickForBubbleSort) / CLOCKS_PER_SEC);
    free(arrayForBubbleSort);

    int* arrayForCountSort = 0;
    arrayForCountSort = calloc(ARRAY_LENGTH, sizeof(int));
    if (!arrayForCountSort)
    {
        printf("Error: no memory allocated");
        return MEMORY_ERROR;
    }
    double startTickForCountSort = clock();
    countSort(arrayForCountSort, ARRAY_LENGTH);
    double finishTickForCountSort = clock();
    printf("Count sort running time on an array of 100,000 elements: %.3lf seconds", (finishTickForCountSort - startTickForCountSort) / CLOCKS_PER_SEC);
    free(arrayForCountSort);
    return END_OF_PROGRAM;
}