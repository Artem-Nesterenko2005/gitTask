#include <stdlib.h>

int* quickSort(int* const array, const int firstLimitation, const int secondLimitation)
{
    if (firstLimitation > secondLimitation)
    {
        return array;
    }

    int largeIndex = firstLimitation;
    int lowIndex = secondLimitation;
    int elementForComparison = array[(secondLimitation + firstLimitation) / 2];

    while (largeIndex <= lowIndex)
    {
        while (array[largeIndex] < elementForComparison)
        {
            ++largeIndex;
        }
        while (array[lowIndex] > elementForComparison)
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
