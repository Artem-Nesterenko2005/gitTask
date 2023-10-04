#include <stdio.h>

#define LENGTH_ARRAY 9
#define TEST_LENGTH_ARRAY 10

int main()
{
    if (test() == 0)
    {
        printf("Error test");
        return;
    }
    int array[LENGTH_ARRAY] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    printf("Initial array: ");
    for (int symbolNumber = 0; symbolNumber < LENGTH_ARRAY; ++symbolNumber)
    {
        printf("%d ", array[symbolNumber]);
    }
    bubbleSort(array, LENGTH_ARRAY);
    printf("\nSorted array: ");
    for (int counterSortedArray = 0; counterSortedArray < LENGTH_ARRAY; ++counterSortedArray)
    {
        printf("%d ", array[counterSortedArray]);
    }
}

int bubbleSort(int array[], int length)
{
    for (int iterationCounter = 0; iterationCounter < length - 1; iterationCounter += 2)
    {
        for (int numberSymbol = 0; numberSymbol < length - 1 - iterationCounter; numberSymbol += 2)
        {
            if (LENGTH_ARRAY - numberSymbol <= 2)
            {
                break;
            }
            if (array[numberSymbol] > array[numberSymbol + 2])
            {
                int swapSymbols = array[numberSymbol];
                array[numberSymbol] = array[numberSymbol + 2];
                array[numberSymbol + 2] = swapSymbols;
            }
        }
    }
    return array;
}

int test()
{
    int testArray1[TEST_LENGTH_ARRAY] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    bubbleSort(testArray1, TEST_LENGTH_ARRAY);
    int rigthSymbol1 = 2;
    for (int testCounter1 = 0; testCounter1 < TEST_LENGTH_ARRAY - 1; testCounter1 += 2)
    {
        if (testArray1[testCounter1] != rigthSymbol1)
        {
            return 0;
        }
        rigthSymbol1 += 2;
    }

    int testArray2[TEST_LENGTH_ARRAY - 1] = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    bubbleSort(testArray2, TEST_LENGTH_ARRAY - 1);
    int rigthSymbol2 = 1;
    for (int testCounter2 = 0; testCounter2 < TEST_LENGTH_ARRAY - 1; testCounter2 += 2)
    {
        if (testArray2[testCounter2] != rigthSymbol2)
        {
            return 0;
        }
        rigthSymbol2 += 2;
    }
    return 1;
}