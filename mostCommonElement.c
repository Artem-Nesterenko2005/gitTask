#include <stdio.h>
#include <time.h>
#include <malloc.h>
#include <stdbool.h>

#define NUMBER_COUNTERS_IN_RANDOMISER 100
#define LENGTH_ARRAY 10
#define ERROR_TEST -1
#define ERROR_MEMORY -2
#define OK_CODE 0

static void randomizer(int* const array, const size_t lengthArray)
{
    srand(time(NULL));
    for (int randomizerCounter = 0; randomizerCounter < lengthArray; ++randomizerCounter)
    {
        array[randomizerCounter] = rand() % NUMBER_COUNTERS_IN_RANDOMISER;
    }
}

static int* quickSort(int* const array, const size_t firstLimitation, const size_t secondLimitation)
{
    if (firstLimitation > secondLimitation)
    {
        return array;
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
            const size_t swapVariablesCounter = array[largeIndex];
            array[largeIndex] = array[lowIndex];
            array[lowIndex] = swapVariablesCounter;
            --lowIndex;
            ++largeIndex;
        }
    }

    quickSort(array, firstLimitation, lowIndex);
    quickSort(array, largeIndex, secondLimitation);
}

static size_t mostCommon(int* const array)
{
    size_t mostCommon = 0;
    size_t counterMostCommon = 1;
    size_t maxCounter = 0;
    for (size_t i = 0; i < LENGTH_ARRAY - 1; ++i)
    {
        counterMostCommon = array[i] == array[i + 1] ? counterMostCommon + 1 : counterMostCommon;
        if (counterMostCommon > maxCounter)
        {
            mostCommon = array[i];
            maxCounter = counterMostCommon;
        }
    }
    return mostCommon;
}

static void printArray(int* const array)
{
    for (size_t i = 0; i < LENGTH_ARRAY; ++i)
    {
        printf("%d ", array[i]);
    }
}

static bool checkSort(int* const array)
{
    for (size_t i = 0; i < LENGTH_ARRAY - 1; ++i)
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
    int testArray1[LENGTH_ARRAY] = { 8, 20, 81, 43, 33, 27, 90, 33, 4, 1 };
    quickSort(testArray1, 0, LENGTH_ARRAY - 1);
    
    if (!checkSort(testArray1) || mostCommon(testArray1) != 33)
    {
        printf("Error: test 1 is not correct\n");
        return false;
    }

    int testArray2[LENGTH_ARRAY] = { 30, 20, 91, 23, 1, 3, 4, 8, 5, 24 };
    quickSort(testArray2, 0, LENGTH_ARRAY - 1);

    if (!checkSort(testArray2) || mostCommon(testArray2) != 1)
    {
        printf("Error: test 2 is not correct\n");
        return false;
    }

    return true;
}

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }

    int* array = malloc(LENGTH_ARRAY * sizeof(int));
    if (array == NULL)
    {
        printf("Error: no memory allocated");
        return ERROR_MEMORY;
    }

    randomizer(array, LENGTH_ARRAY);
    quickSort(array, 0, LENGTH_ARRAY - 1);

    printf("Array: ");
    printArray(array);

    printf("\nMost common element - %Iu", mostCommon(array));
    free(array);
    return OK_CODE;
}
