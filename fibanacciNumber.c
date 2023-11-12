#include <stdio.h>
#include <time.h>

#define END_OF_PROGRAM 1

int static iterativeFindFibanacciNumbers(int counter)
{
    unsigned numberFibanacci1 = 1;
    unsigned numberFibanacci2 = 1;
    unsigned numberFibanacci3 = 1;
    for (unsigned start = 0; start < counter; ++start)
    {
        numberFibanacci3 = numberFibanacci2 + numberFibanacci1;
        numberFibanacci1 = numberFibanacci2;
        numberFibanacci2 = numberFibanacci3;
    }
    return numberFibanacci3;
}

int static recursionFindFibanacciNumbers(int counter)
{
    if (counter <= 0)
    {
        return 1;
    }
    return recursionFindFibanacciNumbers(counter - 1) + recursionFindFibanacciNumbers(counter - 2);
}

void main(void)
{
    for (unsigned number = 0; number < 100; ++number)
    {
        printf("%d - Iteration result %d\n", number, iterativeFindFibanacciNumbers(number));
        double tickForIteration = clock();
        printf("%d - Recursion result %d\n\n", number, recursionFindFibanacciNumbers(number));
        double tickForRecursion = clock();
        if (tickForRecursion / tickForIteration > 1.5 || tickForIteration / tickForRecursion > 1.5)
        {
            printf("The difference in implementation methods is visible with %d number", number);
            return END_OF_PROGRAM;
        }
    }
}