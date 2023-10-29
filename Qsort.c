#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define LENGTH_ARRAY 20
#define ERROR_TESTS -1
#define RANDOM_RANGE 99

static void qsorting(int* const array, const size_t length)
{
    size_t leftIndex = 0;
    size_t rightIndex = length - 1;
    const int nullElement = array[0];
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
            int swapVariablesCounter = array[leftIndex];
            array[leftIndex] = array[rightIndex];
            array[rightIndex] = swapVariablesCounter;
            --rightIndex;
            ++leftIndex;
        }
    }
}

static bool compareArrays(int* const array1, int* const array2)
{
    for (size_t i = 0; i < LENGTH_ARRAY - 1; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

static void printErrorTest(int const testNumber)
{
    printf("Error test number %d\n", testNumber);
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
        return false;
    }
    int rightArray1[LENGTH_ARRAY] = { 19, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 20 };
    if (compareArrays(testArray1, rightArray1) == false)
    {
        printErrorTest(1);
        return false;
    }

    qsorting(testArray2, LENGTH_ARRAY);
    int rigthArray2[LENGTH_ARRAY] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    if (compareArrays(testArray2, rigthArray2) == false)
    {
        printErrorTest(2);
        return false;
    }

    qsorting(testArray3, LENGTH_ARRAY);
    int rigthArray3[LENGTH_ARRAY] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    if (compareArrays(testArray3, rigthArray3) == false)
    {
        printErrorTest(3);
        return false;
    }
    return true;
}

static void printArray(int array[], const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        printf("%d ", array[i]);
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
        array[i] = rand() % RANDOM_RANGE;
    }
    printArray(array, LENGTH_ARRAY);
    qsorting(array, LENGTH_ARRAY);
    printf("\nConverted array ");
    printArray(array, LENGTH_ARRAY);
}
