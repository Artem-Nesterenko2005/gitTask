#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#define LENGTH_AUXILIARY 2
#define NUMBERS_FOR_RANDOMISER 50
#define LENGTH_MAIN 10
#define START_ARRAY 0

enum errorCodes
{
    OK_CODE,
    MEMORY_ERROR,
    ERROR_TEST
};

static void randomizer(int* const mainArray, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        mainArray[i] = rand() % NUMBERS_FOR_RANDOMISER;
    }
}

static int quickSort(int* const array, const int firstLimitation, const int secondLimitation)
{
    if (firstLimitation > secondLimitation)
    {
        return;
    }

    int largeIndex = firstLimitation;
    int lowIndex = secondLimitation;
    int elementForСomparison = array[(secondLimitation + firstLimitation) / 2];

    while (largeIndex <= lowIndex)
    {
        while (array[largeIndex] < elementForСomparison)
        {
            ++largeIndex;
        }
        while (array[lowIndex] > elementForСomparison)
        {
            --lowIndex;
        }
        if (largeIndex <= lowIndex)
        {
            const int swapVariablesCounter = array[largeIndex];
            array[largeIndex] = array[lowIndex];
            array[lowIndex] = swapVariablesCounter;
            --lowIndex;
            ++largeIndex;
        }
    }

    quickSort(array, firstLimitation, lowIndex);
    quickSort(array, largeIndex, secondLimitation);
}



static bool binSearch(int* const array, const size_t number, const size_t length)
{
    size_t right = length - 1;
    size_t left = 0;
    size_t middle = 0;
    while (left <= right)
    {
        middle = (left + right) / 2;
        if (number < array[middle])
        {
            right = middle - 1;
        }

        else if (number > array[middle])
        {
            left = middle + 1;
        }
        else
        {
            return true;
        }
    }
    return false;
}

static bool checkSort(int* const array, const size_t length)
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

static testCase(int* array, const int numberTest, const size_t length, const size_t number)
{
    quickSort(array, 0, length - 1);
    if (!checkSort(array, length))
    {
        return false;
    }

    if (!binSearch(array, number, length))
    {
        return false;
    }
    return true;
}

static bool test(void)
{
    int testMainArray1[LENGTH_MAIN] = { 8, 2, 10, 4, 5, 1, 3, 6, 11, 9 };
    const bool result1 = !testCase(testMainArray1, 1, LENGTH_MAIN, 7);

    int testMainArray2[LENGTH_MAIN] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const bool result2 = testCase(testMainArray2, 2, LENGTH_MAIN, 9);

    int testMainArray3[LENGTH_MAIN] = { 9, 10, 8, 2, 4, 1, 3, 6, 7, 5 };
    const bool result3 = testCase(testMainArray3, 3, LENGTH_MAIN, 6);

    return result1 && result2 && result3;
}

static void printArray(int* const array, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }
    srand(time(NULL));

    size_t length = 0;
    printf("Enter a number to generate an array ");
    scanf_s("%Iu", &length);

    int* mainArray =(int*)malloc(length * sizeof(int));
    if (mainArray == NULL)
    {
        printf("Error: no memory allocated");
        return MEMORY_ERROR;
    }

    size_t number = 0;
    printf("Enter the number of numbers to check ");
    scanf_s("%Iu", &number);

    int* checkNumbers =(int*)malloc(number * sizeof(int));
    if (checkNumbers == NULL)
    {
        printf("Error: no memory allocated");
        free(mainArray);
        return MEMORY_ERROR;
    }

    randomizer(mainArray, length);
    randomizer(checkNumbers, number);

    printf("\nMain array ");
    printArray(mainArray, length);

    printf("Numbers to check their presence in the array ");
    printArray(checkNumbers, number);

    quickSort(mainArray, 0, length - 1);

    for (size_t i = 0; i < number; ++i)
    {
        if (binSearch(mainArray, checkNumbers[i], length, START_ARRAY))
        {
            printf("The number %d is included in the main array \n\n", checkNumbers[i]);
            continue;
        }
        printf("The number %d is not included in the main array\n\n", checkNumbers[i]);
    }

    free(mainArray);
    free(checkNumbers);
}
