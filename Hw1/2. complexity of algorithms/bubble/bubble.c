#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>

#define ARRAY_LENGTH 100000
#define AUXILIARY_ARRAY_LENGTH 10
#define ARRAY_FOR_COUNT_SORT 100

int main()
{
    int resultBubbleSortTest = bubbleSortTest(); 
    int resultCountSortTest = countSortTest();
    if (resultBubbleSortTest + resultCountSortTest != 18)
    {
        printf("Error test");
        return 0;
    }
    int array[100000] = { 0 };
    bubbleSort(array, ARRAY_LENGTH);
 }

int bubbleSort(int array[], int length)
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
    return array;
}

int countSort(int array[], int length)
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
    return array;
}

int bubbleSortTest()
{
    int array[AUXILIARY_ARRAY_LENGTH] = { 543,12,34,54,85,12,543,65,12,43 };
    bubbleSort(array, AUXILIARY_ARRAY_LENGTH);
    int testCounter = 0;
    int testResult = 0;
    for (int testCounter = 0; testCounter < AUXILIARY_ARRAY_LENGTH; ++testCounter)
    {
        if (array[testCounter] <= array[testCounter + 1])
        {
            ++testResult;
        }
    }
    return testResult;
}

int countSortTest()
{
    int array[AUXILIARY_ARRAY_LENGTH] = { 53,12,34,54,85,12,53,65,12,43 };
    countSort(array, AUXILIARY_ARRAY_LENGTH);
    int testCounter = 0;
    int testResult = 0;
    for (int testCounter = 0; testCounter < AUXILIARY_ARRAY_LENGTH; ++testCounter)
    {
        if (array[testCounter] <= array[testCounter + 1])
        {
            ++testResult;
        }
    }
    return testResult;
}