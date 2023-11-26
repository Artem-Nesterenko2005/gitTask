#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>

#define ERROR_MEMORY -2
#define ARRAY_LENGTH 100000
#define AUXILIARY_ARRAY_LENGTH 10
#define ARRAY_FOR_COUNT_SORT 100
#define OK_CODE 1
#define ERROR_TEST -1

static void bubbleSort(int array[], const size_t length)
{
    for (size_t i = 0; i < length - 1; ++i)
    {
        for (size_t k = 0; k < length - 1 - i; ++k)
        {
            if (array[k] > array[k + 1])
            {
                int swapSymbols = array[k];
                array[k] = array[k + 1];
                array[k + 1] = swapSymbols;
            }
        }
    }
}

static void countSort(int array[], const size_t length)
{
    int* const auxiliaryArray = (int*)calloc(100, sizeof(int));
    for (size_t i = 0; i <= length - 1; ++i)
    {
        ++auxiliaryArray[array[i]];
    }
    int counter = 0;
    int indexNumber = 0;
    for (size_t i = 0; i < ARRAY_FOR_COUNT_SORT; ++i)
    {
        size_t variblesAuxiliaryArray = i;
        while (auxiliaryArray[i] > 0)
        {
            array[indexNumber] = counter;
            --auxiliaryArray[i];
            ++indexNumber;
        }
        ++counter;
        i = variblesAuxiliaryArray;
    }
    free(auxiliaryArray);
}

bool sortingCheck(int* const array)
{
    size_t result = 0;
    for (size_t i = 0; i < AUXILIARY_ARRAY_LENGTH - 1; ++i)
    {
        if (array[i] <= array[i + 1])
        {
            ++result;
        }
    }
    return result == 9;
}

const int* random(int* const array)
{
    srand(time(NULL));
    for (size_t i = 0; i < ARRAY_LENGTH; ++i)
    {
        array[i] = rand() % 100;
    }
    return array;
}

static bool bubbleSortTest(void)
{
    const int testArray1[AUXILIARY_ARRAY_LENGTH] = { 543,12,34,54,85,12,543,65,12,43 };
    bubbleSort(testArray1, AUXILIARY_ARRAY_LENGTH);

    const int testArray2[AUXILIARY_ARRAY_LENGTH] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    bubbleSort(testArray2, AUXILIARY_ARRAY_LENGTH);

    if (!sortingCheck(testArray1))
    {
        printf("Error test bubble sort number 1");
        return false;
    }

    if (!sortingCheck(testArray2))
    {
        printf("Error test bubble sort number 2");
        return false;
    }

    return true;
}

static bool countSortTest(void)
{
    int const testArray1[AUXILIARY_ARRAY_LENGTH] = { 53,12,34,54,85,12,53,65,12,43 };
    countSort(testArray1, AUXILIARY_ARRAY_LENGTH);

    int const testArray2[AUXILIARY_ARRAY_LENGTH] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    countSort(testArray2, AUXILIARY_ARRAY_LENGTH);
  
    if (!sortingCheck(testArray1))
    {
        printf("Error test count sort number 1");
        return false;
    }

    if (!sortingCheck(testArray2))
    {
        printf("Error test count sort number 2");
        return false;
    }

    return true;
}

double calcDuration(void (*sortMethod)(void), int* const array)
{
    double startTickForBubbleSort = clock();
    sortMethod(array, ARRAY_LENGTH);
    double finishTickForBubbleSort = clock();
    return (finishTickForBubbleSort - startTickForBubbleSort) / CLOCKS_PER_SEC;
}

int main(void)
{
    if (!countSortTest() || !bubbleSortTest())
    {
        printf("Error test");
        return ERROR_TEST;
    }

    int* const arrayForBubbleSort = (int*)calloc(ARRAY_LENGTH, sizeof(int));
    if (!arrayForBubbleSort)
    {
        printf("Error: no memory allocated");
        return ERROR_MEMORY;
    }
    random(arrayForBubbleSort);
    printf("Bubble sort running time on an array of 100,000 elements: %.3lf seconds\n", calcDuration(bubbleSort, arrayForBubbleSort));
    free(arrayForBubbleSort);

    int* const arrayForCountSort = (int*)calloc(ARRAY_LENGTH, sizeof(int));
    if (!arrayForCountSort)
    {
        printf("Error: no memory allocated");
        return ERROR_MEMORY;
    }
    random(arrayForCountSort);
    printf("Count sort running time on an array of 100,000 elements: %.3lf seconds",  calcDuration(countSort, arrayForCountSort));
    free(arrayForCountSort);
    return OK_CODE;
}
