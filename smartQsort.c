#include <stdio.h>
#include <time.h>

#define LIMITATION_FOR_ARRAY 100
#define NUMBER_RIGHT_TESTS 3
#define LIMITATION_TEST_ARRAY 10
#define RANDOM_RANGE 200

int qsorting(int array[], int firstLimitation, int secondLimitation)
{
    if (firstLimitation > secondLimitation)
    {
        return;
    }
    if (secondLimitation - firstLimitation < 10)
    {
        insertionSort(array, secondLimitation - firstLimitation);
    }
    int largeNumberCounter = firstLimitation; 
    int lowNumberCounter = secondLimitation;
    int elementForСomparison = array[(secondLimitation + firstLimitation) / 2];
    while (largeNumberCounter <= lowNumberCounter)
    {
        while (array[largeNumberCounter] < elementForСomparison)
        {
            ++largeNumberCounter;
        }
        while (array[lowNumberCounter] > elementForСomparison)
        {
            --lowNumberCounter;
        }
        if (largeNumberCounter <= lowNumberCounter)
        {
            int swapVariablesCounter = array[largeNumberCounter];
            array[largeNumberCounter] = array[lowNumberCounter];
            array[lowNumberCounter] = swapVariablesCounter;
            --lowNumberCounter;
            ++largeNumberCounter;
        }
    }
    qsorting(array, firstLimitation, lowNumberCounter);
    qsorting(array, largeNumberCounter, secondLimitation);
}

int insertionSort(int array[], int length)
{
    for (int numberSymbol = 1; numberSymbol < length; ++numberSymbol)
    {
        int variables = numberSymbol;
        while (numberSymbol > 0)
        {
            if (array[numberSymbol] < array[numberSymbol - 1])
            {
                int swapSymbols = array[numberSymbol];
                array[numberSymbol] = array[numberSymbol - 1];
                array[numberSymbol - 1] = swapSymbols;
            }
            --numberSymbol;
        }
        numberSymbol = variables;
    }

}

int test()
{
    int testArray1[LIMITATION_TEST_ARRAY] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    qsorting(testArray1, 0, LIMITATION_TEST_ARRAY - 1);
    int resultTest = 0;
    resultTest = checkSort(testArray1, LIMITATION_TEST_ARRAY - 1);
    int testArray2[LIMITATION_TEST_ARRAY] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    qsorting(testArray2, 0, LIMITATION_TEST_ARRAY - 1) + resultTest;
    resultTest = checkSort(testArray2, LIMITATION_TEST_ARRAY - 1) + resultTest;
    int testArray3[LIMITATION_TEST_ARRAY] = { 4, 65, 32, 1, 63, 756, 23, 5, 12, 34 };
    qsorting(testArray3, 0, LIMITATION_TEST_ARRAY - 1);
    resultTest = checkSort(testArray3, LIMITATION_TEST_ARRAY - 1) + resultTest;
    return resultTest;
}

int checkSort(int array[], int length)
{
    int resultCounter = 0;
    for (int counter = 0; counter < length - 1; ++counter)
    {
        if (array[counter] <= array[counter + 1])
        {
            ++resultCounter;
        }
    }
if (resultCounter == length - 1)
{
    return 1;
}
return 0;
}

int randomiser(int array[], int length)
{
    srand(time(NULL));
    for (int counter = 0; counter < length; ++counter)
    {
        array[counter] = rand() % RANDOM_RANGE;
        printf("%d ", array[counter]);
    }
    return array;
}

int main()
{
    if (test() != NUMBER_RIGHT_TESTS)
    {
        printf("Error test");
        return 0;
    }
    int array[LIMITATION_FOR_ARRAY] = { 0 };
    printf("Source array: ");
    randomiser(array, LIMITATION_FOR_ARRAY);
    qsorting(array, 0, LIMITATION_FOR_ARRAY - 1);
    printf("\n\nSorted array: ");
    for (int i = 0; i < 100; ++i)
    {
        printf("%d ", array[i]);
    }
}

