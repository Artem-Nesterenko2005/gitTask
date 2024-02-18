include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

#define LIMITATION_FOR_ARRAY 100
#define LIMITATION_TEST_ARRAY 10
#define RANDOM_RANGE 200
#define DIFFERENCE_FOR_SORTING 10
#define ERROR_TESTS -1
#define OK_CODE 0

static void insertionSort(int* const array, const int length)
{
    for (int i = 1; i < length; ++i)
    {
        const int variables = i;
        for (int j = i; j > 0; --j)
        {
            if (array[j] < array[j - 1])
            {
                int swapSymbols = array[j];
                array[j] = array[j - 1];
                array[j - 1] = swapSymbols;
            }
        }
        i = variables;
    }
}

static void qsorting(int* const array, const int firstLimitation, const int secondLimitation)
{
    if (firstLimitation > secondLimitation)
    {
        return;
    }
    if (secondLimitation - firstLimitation < DIFFERENCE_FOR_SORTING)
    {
        insertionSort(array, secondLimitation - firstLimitation);
    }
    int leftIndex = firstLimitation;
    int rightIndex = secondLimitation;
    int elementСomparison = array[(secondLimitation + firstLimitation) / 2];
    while (leftIndex <= rightIndex)
    {
        while (array[leftIndex] < elementСomparison)
        {
            ++leftIndex;
        }
        while (array[rightIndex] > elementСomparison)
        {
            --rightIndex;
        }
        if (leftIndex <= rightIndex)
        {
            int swapVariablesCounter = array[leftIndex];
            array[leftIndex] = array[rightIndex];
            array[rightIndex] = swapVariablesCounter;
            --rightIndex;
            ++leftIndex;
        }
    }
    qsorting(array, firstLimitation, rightIndex);
    qsorting(array, leftIndex, secondLimitation);
}

static bool checkSort(int* const array, const int length)
{
    for (size_t i = 0; i < length - 1; ++i)
    {
        if (array[i] > array[i + 1])
        {
            return false;
        }
    }
    return true;
}

static void printErrorTest(const int numberTest)
{
    printf("Error test number %d\n", numberTest);
}

static bool test(void)
{
    int testArray1[LIMITATION_TEST_ARRAY] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    qsorting(testArray1, 0, LIMITATION_TEST_ARRAY - 1);
    bool resultTest1 = 0;
    if (!checkSort(testArray1, LIMITATION_TEST_ARRAY))
    {
        printErrorTest(1);
        return false;
    }

    int testArray2[LIMITATION_TEST_ARRAY] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    qsorting(testArray2, 0, LIMITATION_TEST_ARRAY - 1);
    bool resultTest2 = 0;
    if (!checkSort(testArray2, LIMITATION_TEST_ARRAY))
    {
        printErrorTest(2);
        return false;
    }

    int testArray3[LIMITATION_TEST_ARRAY] = { 4, 65, 32, 1, 63, 756, 23, 5, 12, 34 };
    qsorting(testArray3, 0, LIMITATION_TEST_ARRAY - 1);
    bool resultTest3 = 0;
    if (!checkSort(testArray3, LIMITATION_TEST_ARRAY))
    {
        printErrorTest(3);
        return false;
    }
    return true;
}

static void randomize(int* const array, int length)
{
    srand(time(NULL));
    for (size_t i = 0; i < length; ++i)
    {
        array[i] = rand() % RANDOM_RANGE;
    }
}

static void printArray(int* const array)
{
    for (size_t i = 0; i < LIMITATION_FOR_ARRAY; ++i)
    {
        printf("%d ", array[i]);
    }
}

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TESTS;
    }
    int array[LIMITATION_FOR_ARRAY] = { 0 };
    printf("\nSource array: ");
    randomize(array, LIMITATION_FOR_ARRAY);
    printArray(array);
    qsorting(array, 0, LIMITATION_FOR_ARRAY - 1);
    printf("\n\nSorted array: ");
    printArray(array);
    return OK_CODE;
}
