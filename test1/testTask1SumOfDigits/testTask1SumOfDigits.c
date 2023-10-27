#include <stdio.h>
#include <math.h>

#define LENGTH_ARRAY 8

int numberSearch(int array[], int maxSumArray[])
{
    int counterOfSymbol = 0;
    int maxSum = 0;
    int sumArray[LENGTH_ARRAY] = { 0 };
    for (int numberSymbol = 0; numberSymbol < LENGTH_ARRAY; ++numberSymbol)
    {
        int sumOfDigits = 0;
        int number = abs(array[numberSymbol]);
        while (number > 9)
        {
            sumOfDigits = sumOfDigits + number % 10;
            number /= 10;
        }
        sumOfDigits += number;
        maxSum = maxSum < sumOfDigits ? sumOfDigits : maxSum;
        sumArray[numberSymbol] = sumOfDigits;
    }
    for (int sumCounter = 0; sumCounter < LENGTH_ARRAY; ++sumCounter)
    {
        if (sumArray[sumCounter] == maxSum)
        {
            maxSumArray[counterOfSymbol] = array[sumCounter];
            ++counterOfSymbol;
        }
    }
    return maxSumArray;
}

int arrayOfZeros(int array[])
{
    int counterOfZeros = 0;
    for (int counter = 0; counter < LENGTH_ARRAY; ++counter)
    {
        while (array[counter] == 0)
        {
            ++counterOfZeros;
            break;
        }
    }
    if (counterOfZeros == LENGTH_ARRAY)
    {
        return 1;
    }
    return 0;
}

int test()
{
    int testArray1[LENGTH_ARRAY] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    int testMaxSumArray1[LENGTH_ARRAY] = { 0 };
    numberSearch(testArray1, testMaxSumArray1);
    int numberZeros1 = arrayOfZeros(testMaxSumArray1);
    for (int testNumberSymbol1 = 0; testNumberSymbol1 < LENGTH_ARRAY; ++testNumberSymbol1)
    {
        if (testMaxSumArray1[testNumberSymbol1] == 0)
        {
            continue;
        }
        printf("Error test number 1\n");
        return 0;
    }

    int testArray2[LENGTH_ARRAY] = { -81, 9, 30, 63 };
    int testMaxSumArray2[LENGTH_ARRAY] = { 0 };
    numberSearch(testArray2, testMaxSumArray2);
    int numberZeros2 = arrayOfZeros(testMaxSumArray2);
    if (testMaxSumArray2[0] != -81 || testMaxSumArray2[1] != 9 || testMaxSumArray2[2] != 63)
    {
        printf("Error test number 2\n");
        return 0;
    }

    return 1;
}

int main()
{
    if (test() != 1)
    {
        printf("Error test");
        return 0;
    }
    int array[LENGTH_ARRAY] = { 27, -9, -81, 0, 23, 62, 71, 45 };
    printf("Source array: ");
    for (int counter = 0; counter < LENGTH_ARRAY; ++counter)
    {
        printf("%d ", array[counter]);
    }
    int maxSumArray[LENGTH_ARRAY] = { 0 };
    numberSearch(array, maxSumArray);
    int numberZeros = arrayOfZeros(maxSumArray);
    int numberSymbol = 0;
    printf("\nNumbers with the greatest sum of digits: ");
    if (numberZeros == 0)
    {
        while (maxSumArray[numberSymbol] != 0)
        {
            printf("%d ", maxSumArray[numberSymbol]);
            ++numberSymbol;
            continue;
        }
        return 0;
    }
    for (numberSymbol; numberSymbol < LENGTH_ARRAY; ++numberSymbol)
    {
        printf("%d  ", maxSumArray[numberSymbol]);
    }
}