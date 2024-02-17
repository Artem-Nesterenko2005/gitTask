#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>

enum errorCodes
{
    OK_CODE,
    ERROR_TEST,
    MEMORY_ERROR,
    NEGATIVE_NUMBER
};

#define ARRAY_LENGTH 100000
#define AUXILIARY_ARRAY_LENGTH 10
#define ARRAY_FOR_COUNT_SORT 100

typedef int* (SortMethod)(int* const, size_t);

static int bubbleSort(int* const array, const size_t length)
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
    return OK_CODE;
}

static int countSort(int* const array, const size_t length)
{
    int* const auxiliaryArray = (int*)calloc(length + 1, sizeof(int));
    if (auxiliaryArray == NULL)
    {
        printf("Error: no memory allocated");
        return MEMORY_ERROR;
    }
    for (size_t i = 0; i <= length - 1; ++i)
    {
        if (array[i] < 0)
        {
            printf("Array contains negative numbers");
            return NEGATIVE_NUMBER;
        }
        ++auxiliaryArray[array[i]];
    }
    size_t counter = 0;
    size_t indexNumber = 0;
    for (size_t i = 0; i < length; ++i)
    {
        int variblesAuxiliaryArray = i;
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
    return OK_CODE;
}

static bool sortingCheck(const int* const array)
{
    for (size_t i = 0; i < AUXILIARY_ARRAY_LENGTH - 1; ++i)
    {
        if (array[i] > array[i + 1])
        {
            false;
        }
    }
    return true;
}

static void random(int* const array)
{
    srand(time(NULL));
    for (size_t i = 0; i < ARRAY_LENGTH; ++i)
    {
        array[i] = rand() % 100;
    }
}

static bool testCase(SortMethod* sortMethod, const int* const array, size_t length)
{
    if (sortMethod(array, length) != OK_CODE)
    {
        return false;
    }
    return sortingCheck(array);
}

static bool test(void)
{
    const int testArray1[AUXILIARY_ARRAY_LENGTH] = { 543,12,34,54,85,12,543,65,12,43 };
    const int testArray2[AUXILIARY_ARRAY_LENGTH] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    return testCase(countSort, testArray1, AUXILIARY_ARRAY_LENGTH) && testCase(countSort, testArray2, AUXILIARY_ARRAY_LENGTH) &&
        testCase(bubbleSort, testArray1, AUXILIARY_ARRAY_LENGTH) && testCase(bubbleSort, testArray2, AUXILIARY_ARRAY_LENGTH);
}

static double calcDuration(SortMethod* sortMethod)
{
    int* const array = (int*)calloc(ARRAY_LENGTH, sizeof(int));
    if (array == NULL)
    {
        printf("Error: no memory allocated");
        return MEMORY_ERROR;
    }
    random(array);
    double startTickForBubbleSort = clock();
    sortMethod(array, ARRAY_LENGTH);
    double finishTickForBubbleSort = clock();
    free(array);
    return (finishTickForBubbleSort - startTickForBubbleSort) / CLOCKS_PER_SEC;
}

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }

    printf("Bubble sort running time on an array of 100,000 elements: %.3lf seconds\n", calcDuration(bubbleSort));
    printf("Count sort running time on an array of 100,000 elements: %.3lf seconds",  calcDuration(countSort));
    return OK_CODE;
}
