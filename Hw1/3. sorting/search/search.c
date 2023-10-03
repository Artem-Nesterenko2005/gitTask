#include <stdio.h>
#include <time.h>
#include <malloc.h>

#define LENGTH 2
#define NUMBERS_FOR_RANDOMISER 50

int randomizer(int mainArray[], int length, int auxiliaryArray[], int number)
{
    srand(time(NULL));
    for (int randomizerCounter = 0; randomizerCounter < length; ++randomizerCounter)
    {
        mainArray[randomizerCounter] = rand() % NUMBERS_FOR_RANDOMISER;
    }
    for (int randomizerCounter = 0; randomizerCounter < number; ++randomizerCounter)
    {
        auxiliaryArray[randomizerCounter] = rand() % NUMBERS_FOR_RANDOMISER;
    }
}

int quickSort(int array[], int firstLimitation, int secondLimitation )
{
    if (firstLimitation > secondLimitation)
    {
        return;
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

    quickSort(array, firstLimitation, lowNumberCounter);
    quickSort(array, largeNumberCounter, secondLimitation);
}

void sorting(int mainArray[], int auxiliaryArray[], int lengthMainArray, int  lengthAuxiliaryArray, int *array)
{
    for (int counter = 0; counter < lengthAuxiliaryArray; ++counter)
    {
        int numberCheck = 1;
        int middle = (lengthMainArray - 1) / 2;
        while (mainArray[middle] != auxiliaryArray[counter])
        {
            int firstSymbolNumber = middle;
            mainArray[middle] < auxiliaryArray[counter] ? ++middle : --middle;
            int secondSymbolNumber = middle;
            if ((middle == -1 || middle == lengthMainArray) || (mainArray[firstSymbolNumber] > auxiliaryArray[counter] && mainArray[secondSymbolNumber] < auxiliaryArray[counter]) || (mainArray[firstSymbolNumber] < auxiliaryArray[counter] && mainArray[secondSymbolNumber] > auxiliaryArray[counter]))
            {
                numberCheck = 0;
                array[counter] = 0;
                break;
            }
        }
        if (numberCheck)
        {
            array[counter] = 1;
        }
    }
}


int test()
{
    int testing = 0;
    int resultTest = 0;
    int testArray[10] = { 0 };

    int testMainArray1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int testAuxiliaryArray1[2] = { 1, 11 };

    quickSort(testMainArray1, 0, 9);
    sorting(testMainArray1, testAuxiliaryArray1, 10, 2, testArray);
    if (testArray)
    {
        ++testing;
    }

    int testMainArray2[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int testAuxiliaryArray2[2] = { 11, 12 };

    quickSort(testMainArray2, 0, 9);
    sorting(testMainArray2, testAuxiliaryArray2, 10, 2, testArray);
    if (testArray)
    {
        ++testing;
    }

    int testMainArray3[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int testAuxiliaryArray3[2] = { 1, 2 };

    quickSort(testMainArray3, 0, 9);
    sorting(testMainArray3, testAuxiliaryArray3, 10, 2, testArray);
    if (testArray)
    {
        ++testing;
    }

    return testing;
} 

int main()
{
    if (test() != 3)
    {
        printf("Error test");
        return;
    }
    int length = 0;
    printf("Enter a number to generate an array ");
    scanf_s("%d", &length);

    int* mainArray = 0;
    mainArray = malloc(length * sizeof(int));

    int number = 0;
    printf("Enter the number of numbers to check ");
    scanf_s("%d", &number);

    int* auxiliaryArray = 0;
    auxiliaryArray = malloc(number * sizeof(int));

    randomizer(mainArray, length, auxiliaryArray, number);
    printf("Main array ");
    for (int arrayOutput = 0; arrayOutput < length; ++arrayOutput)
    {
        printf("%d ", mainArray[arrayOutput]);
    }

    printf("\nNumbers to check their presence in the array ");
    for (int numbersOutput = 0; numbersOutput < number; ++numbersOutput)
    {
        printf("%d ", auxiliaryArray[numbersOutput]);
    }

    quickSort(mainArray, 0, length - 1);

    int* checkArray = 0;
    checkArray = malloc(number * sizeof(int));

    sorting(mainArray, auxiliaryArray, length, number, checkArray);

    for (int i = 0; i < number; ++i)
    {
        if (checkArray[i] == 1)
        {
            printf("\n\nThe number %d is included in the main array", auxiliaryArray[i]);
            continue;
        }
        printf("\n\nThe number %d is not included in the main array", auxiliaryArray[i]);
    }

    free(mainArray);
    free(auxiliaryArray);
    free(checkArray);
}