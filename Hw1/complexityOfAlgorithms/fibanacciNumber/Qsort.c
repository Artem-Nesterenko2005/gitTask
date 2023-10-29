#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define LENGTH_ARRAY 20
#define ERROR_TESTS -1

static void qsorting(int array[], const size_t length)
{
    size_t leftIndex = 0;
    size_t rightIndex = length - 1;
    const size_t nullElement = array[0];
    while (rightIndex > leftIndex)
    {
        if (array[leftIndex] < nullElement)
        {
            ++leftIndex;
        }
        else if (array[rightIndex] >= nullElement)
        {
            --rightIndex;
        }
        else
        {
            size_t swapVariablesCounter = array[leftIndex];
            array[leftIndex] = array[rightIndex];
            array[rightIndex] = swapVariablesCounter;
            --rightIndex;
            ++leftIndex;
        }
    }
}

static bool test(void)
{
    int testArray1[LENGTH_ARRAY] = { 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    int testArray2[LENGTH_ARRAY] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int testArray3[LENGTH_ARRAY] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    qsorting(testArray1, LENGTH_ARRAY);
    if (testArray1[0] != 19 || testArray1[19] != 20)
    {
        printf("Error test 1");
        return 1;
    }
    for (size_t i = 1; i < LENGTH_ARRAY - 1; ++i)
    {
        if (testArray1[i] > testArray1[i + 1])
        {
            printf("Error test 1");
            return false;
        }
    }

    qsorting(testArray2, LENGTH_ARRAY);
    for (size_t j = 0; j < LENGTH_ARRAY - 1; ++j)
    {
        if (testArray2[j] != testArray2[j + 1])
        {
            printf("Error test 2");
            return false;
        }
    }

    qsorting(testArray3, LENGTH_ARRAY);
    for (size_t n = 1; n < LENGTH_ARRAY - 1; ++n)
    {
        if (testArray1[n] > testArray1[n + 1])
        {
            printf("Error test 3");
            return false;
        }
    }
    return true;
}

static void printArray(int array[], const size_t length)
{
    for (size_t j = 0; j < length; ++j)
    {
        printf("%d ", array[j]);
    }
}

void main(void)
{
    if (!test())
    {
        printf("Error programm test");
        return ERROR_TESTS;
    }
    srand(time(NULL));
    int array[LENGTH_ARRAY] = { 0 };
    printf("Initial Array ");
    for (size_t i = 0; i < LENGTH_ARRAY; ++i)
    {
        array[i] = rand() % 99;
    }
    printArray(array, LENGTH_ARRAY);
    qsorting(array, LENGTH_ARRAY);
    printf("\nConverted array ");
    printArray(array, LENGTH_ARRAY);
}

