#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH_ARRAY 20

int main()
{
    int programmTest = test();
    if (programmTest != 1)
    {
        printf("Error programm test");
        return 1;
    }
    srand(time(NULL));
    int array[LENGTH_ARRAY] = { 0 };
    printf("Initial Array ");
    for (int symbolNumber = 0; symbolNumber < LENGTH_ARRAY; ++symbolNumber)
    {
        array[symbolNumber] = rand() % 100;
        printf("%d, ", array[symbolNumber]);
    }
    qsorting(array, LENGTH_ARRAY);
    printf("\nConverted array ");
    for (int counter = 0; counter < LENGTH_ARRAY; ++counter)
    {
        printf("%d, ", array[counter]);
    }
}

int qsorting(int array[], int length)
{
    int largeNumberCounter = 0;
    int lowNumberCounter = length - 1;
    const int nullElement = array[0];
    while (lowNumberCounter > largeNumberCounter)
    {
        if (array[largeNumberCounter] < nullElement)
        {
            ++largeNumberCounter;
        }
        else if (array[lowNumberCounter] >= nullElement)
        {
            --lowNumberCounter;
        }
        else
        {
            int swapVariablesCounter = array[largeNumberCounter];
            array[largeNumberCounter] = array[lowNumberCounter];
            array[lowNumberCounter] = swapVariablesCounter;
            --lowNumberCounter;
            ++largeNumberCounter;
        }
    }
    return array;
}

int test()
{
    int testArray1[LENGTH_ARRAY] = { 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
    int testArray2[LENGTH_ARRAY] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int testArray3[LENGTH_ARRAY] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
    qsorting(testArray1, 20);
    int correctTestArray1 = 0;
    int checkingTheTest1 = 0;
    for (int counterForTest1 = 1; counterForTest1 < LENGTH_ARRAY - 1; ++counterForTest1)
    {
        if (testArray1[counterForTest1] == counterForTest1)
        {
            ++checkingTheTest1;
        }
        if (checkingTheTest1 == 18 && testArray1[0] == 19 && testArray1[19] == 20)
        {
            correctTestArray1 = 1;
        }
    }
    qsorting(testArray2, 20);
    int correctTestArray2 = 0;
    if (testArray2)
    {
        correctTestArray2 = 1;
    }
    qsorting(testArray3, 20);
    int correctTestArray3 = 0;
    int checkingTheTest3 = 0;
    for (int counterForTest3 = 0; counterForTest3 < LENGTH_ARRAY - 1; ++counterForTest3)
    {
        if (testArray3[counterForTest3] + 1 == testArray3[counterForTest3 + 1])
        {
            ++checkingTheTest3;
        }
        if (checkingTheTest3 == 19)
        {
            correctTestArray3 = 1;
        }
    }
    int resultTest = correctTestArray1 * correctTestArray2 * correctTestArray3;
    return resultTest;
}