#include <stdio.h>
#include <time.h>
#include <malloc.h>

#define LENGTH_ARRAY 10
void randomizer(int *array)
{
    srand(time(NULL));
    for (int randomizerCounter = 0; randomizerCounter < 10; ++randomizerCounter)
    {
        array[randomizerCounter] = rand() % 10;
    }
}

int searchForTheMostCommonSymbol(int array[])
{
    int maxIndexNumber = 0;
    int maxCounter = 0;
    int auxiliaryArray[10] = { 0 };
    for (int indexFillingArray = 0; indexFillingArray < 10; ++indexFillingArray)
    {
        int number = array[indexFillingArray];
        ++auxiliaryArray[number];
    }
    for (int indexAuxiliaryArray = 0; indexAuxiliaryArray < 10; ++indexAuxiliaryArray)
    {
        if (auxiliaryArray[indexAuxiliaryArray] > maxIndexNumber)
        {
            maxIndexNumber = auxiliaryArray[indexAuxiliaryArray];
            maxCounter = indexAuxiliaryArray;
        }
    }
    return maxCounter;
}

int main()
{
    int* array = 0;
    array = malloc(10 * sizeof(int));
    if (!array)
    {
        printf("Error: no memory allocated");
        return;
    }
    randomizer(array);
    for (int i = 0; i < 10; ++i)
    {
        printf("%d ", array[i]);
    }
    int ff = searchForTheMostCommonSymbol(array);
    printf("\n%d", ff);
    free(array);
}