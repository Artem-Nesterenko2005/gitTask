#include <stdlib.h>

int* quickSort(int* const array, const size_t firstLimitation, const size_t secondLimitation)
{
    if (firstLimitation > secondLimitation)
    {
        return array;
    }

    size_t largeIndex = firstLimitation;
    size_t lowIndex = secondLimitation;
    size_t elementForComparison = array[(secondLimitation + firstLimitation) / 2];

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
