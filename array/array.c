#include <stdio.h>
#include <malloc.h>

#define MEMORY_ERROR -1
#define OK_CODE 0

static void flipArray(int* array, int leftLimitation, int rightLimitation)
{
    while (leftLimitation < rightLimitation)
    {
        int swap = array[leftLimitation];
        array[leftLimitation] = array[rightLimitation];
        array[rightLimitation] = swap;
        leftLimitation++;
        rightLimitation--;
    }
}

static void fillingArray(int* array, int length)
{
    for (int i = 0; i < length; ++i)
    {
        array[i] = i;
    }
}

static void printArray(int* array, int length)
{
    for (int i = 0; i < length; ++i)
    {
        printf("%d ", array[i]);
    }
}

int main(void)
{
    int firstLength = 0;
    printf("Enter first length ");
    scanf_s("%d", &firstLength);

    int secondLength = 0;
    printf("Enter second length ");
    scanf_s("%d", &secondLength);

    int* array = (int*)calloc(firstLength + secondLength, sizeof(int));
    if (array == NULL)
    {
        return MEMORY_ERROR;
    }
    fillingArray(array, firstLength + secondLength);
    flipArray(array, 0, firstLength - 1);
    flipArray(array, firstLength, firstLength + secondLength - 1);
    flipArray(array, 0, firstLength + secondLength - 1);
    printf("Inverted array: ");
    printArray(array, firstLength + secondLength);
    return OK_CODE;
}
