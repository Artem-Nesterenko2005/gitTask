#include <stdio.h>
#include <time.h>
#include <malloc.h>

#define NUMBER_COUNTERS_IN_RANDOMISER 100
#define LENGTH_ARRAY 10

void randomizer(int *array, int lengthArray)
{
    srand(time(NULL));
    for (int randomizerCounter = 0; randomizerCounter < lengthArray; ++randomizerCounter)
    {
        array[randomizerCounter] = rand() % NUMBER_COUNTERS_IN_RANDOMISER;
    }
}

int searchForTheMostCommonSymbol(int array[], int lengthArray)
{
    int maxIndexNumber = 0;
    int maxCounter = 0;
    int auxiliaryArray[NUMBER_COUNTERS_IN_RANDOMISER] = { 0 };
    for (int indexFillingArray = 0; indexFillingArray < lengthArray; ++indexFillingArray)
    {
        int number = array[indexFillingArray];
        ++auxiliaryArray[number];
    }
    for (int indexAuxiliaryArray = 0; indexAuxiliaryArray < NUMBER_COUNTERS_IN_RANDOMISER; ++indexAuxiliaryArray)
    {
        if (auxiliaryArray[indexAuxiliaryArray] > maxIndexNumber)
        {
            maxIndexNumber = auxiliaryArray[indexAuxiliaryArray];
            maxCounter = indexAuxiliaryArray;
        }
    }
    return maxCounter;
}

int test()
{
    int testArray1[LENGTH_ARRAY] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int resultOfTest1 = 0;
    resultOfTest1 = searchForTheMostCommonSymbol(testArray1, LENGTH_ARRAY);
    if (resultOfTest1 != 1)
    {
        printf("Error: test 1 is not correct\n");
        return 0;
    }

    int testArray2[LENGTH_ARRAY] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int resultOfTest2 = 0;
    resultOfTest2 = searchForTheMostCommonSymbol(testArray2, LENGTH_ARRAY);
    if (!resultOfTest2)
    {
        printf("Error: test 2 is not correct\n");
        return 0;
    }

    int testArray3[1] = { 1 };
    int resultOfTest3 = 0;
    resultOfTest3 = searchForTheMostCommonSymbol(testArray3, 1);
    if (resultOfTest3 != 1)
    {
        printf("Error: test 3 is not correct\n");
        return 0;
    }
}

int main()
{
    if (test() != 1)
    {
        printf("Error test");
        return 0;
    }
    int* array = 0;
    array = malloc(LENGTH_ARRAY * sizeof(int));
    if (!array)
    {
        printf("Error: no memory allocated");
        return;
    }
    randomizer(array, LENGTH_ARRAY);
    printf("Array: ");
    for (int numberSymbol = 0; numberSymbol < LENGTH_ARRAY; ++numberSymbol)
    {
        printf("%d ", array[numberSymbol]);
    }
    int mostCommonElement = searchForTheMostCommonSymbol(array, LENGTH_ARRAY);
    printf("\nMost common element - %d", mostCommonElement);
    free(array);
}