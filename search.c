#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

#define LENGTH_AUXILIARY 2
#define NUMBERS_FOR_RANDOMISER 50
#define ERROR_TEST -1
#define ERROR_MEMORY -2
#define LENGTH_MAIN 10
#define START_ARRAY 0

static void randomizer(int* const mainArray, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        mainArray[i] = rand() % NUMBERS_FOR_RANDOMISER;
    }
}

static int quickSort(int* const array, const size_t firstLimitation, const size_t secondLimitation)
{
    if (firstLimitation > secondLimitation)
    {
        return;
    }

    size_t largeIndex = firstLimitation;
    size_t lowIndex = secondLimitation;
    size_t elementForСomparison = array[(secondLimitation + firstLimitation) / 2];

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

static bool binSearch(int* const mainArray, size_t number, const size_t lengthMain, const size_t start)
{
    size_t k = (lengthMain + start) / 2;
    if (mainArray[k] == number)
    {
        return true;
    }
    
    if (k == start)
    {
        return false;
    }
    mainArray[k] < number ? binSearch(mainArray, number, lengthMain, k) : binSearch(mainArray, number, k, start);
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

static bool test(void)
{
    int testMainArray1[LENGTH_MAIN] = { 8, 2, 10, 4, 5, 1, 3, 6, 7, 9 };

    quickSort(testMainArray1, 0, LENGTH_MAIN - 1);
    if (!checkSort(testMainArray1, LENGTH_MAIN))
    {
        printf("Error test number 1\n");
        return false;
    }
    if (!binSearch(testMainArray1, 1, LENGTH_MAIN, START_ARRAY) || binSearch(testMainArray1, 11, LENGTH_MAIN, START_ARRAY))
    {
        printf("Error test number 1\n");
        return false;
    }

    int testMainArray2[LENGTH_MAIN] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    quickSort(testMainArray2, 0, LENGTH_MAIN - 1);
    if (!checkSort(testMainArray2, LENGTH_MAIN))
    {
        printf("Error test number 2\n");
        return false;
    }
    if (binSearch(testMainArray2, 11, LENGTH_MAIN, START_ARRAY) || binSearch(testMainArray2, 12, LENGTH_MAIN, START_ARRAY))
    {
        printf("Error test number 2\n");
        return false;
    }

    int testMainArray3[LENGTH_MAIN] = { 9, 10, 8, 2, 4, 1, 3, 6, 7, 5 };

    quickSort(testMainArray3, 0, LENGTH_MAIN - 1);
    if (!checkSort(testMainArray3, LENGTH_MAIN))
    {
        printf("Error test number 3\n");
        return false;
    }
    if (!binSearch(testMainArray3, 1, LENGTH_MAIN, START_ARRAY) || !binSearch(testMainArray3, 2, LENGTH_MAIN, START_ARRAY))
    {
        printf("Error test number 3\n");
        return false;
    }

    return true;
}

static void printArray(int* const array, size_t length)
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
        return ERROR_MEMORY;
    }

    size_t number = 0;
    printf("Enter the number of numbers to check ");
    scanf_s("%Iu", &number);

    int* checkNumbers =(int*)malloc(number * sizeof(int));
    if (checkNumbers == NULL)
    {
        printf("Error: no memory allocated");
        free(mainArray);
        return ERROR_MEMORY;
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
