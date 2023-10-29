#include <stdio.h>
#include <time.h>

#define END_OF_PROGRAM 1
#define DIFFERENCE_IN_TIME 1.5

static int iterativeFindFibanacciNumbers(unsigned int counter)
{
    unsigned int numberFibanacci1 = 1;
    unsigned int numberFibanacci2 = 1;
    unsigned int numberFibanacci3 = 1;
    for (unsigned int start = 0; start < counter; ++start)
    {
        numberFibanacci3 = numberFibanacci2 + numberFibanacci1;
        numberFibanacci1 = numberFibanacci2;
        numberFibanacci2 = numberFibanacci3;
    }
    return numberFibanacci3;
}

static int recursionFindFibanacciNumbers(int counter)
{
    if (counter <= 0)
    {
        return 1;
    }
    return recursionFindFibanacciNumbers(counter - 1) + recursionFindFibanacciNumbers(counter - 2);
}

void main(void)
{
    for (unsigned int number = 0; number < 100; ++number)
    {
        printf("%d - Iteration result %d\n", number, iterativeFindFibanacciNumbers(number));
        double tickForIteration = clock();
        printf("%d - Recursion result %d\n\n", number, recursionFindFibanacciNumbers(number));
        double tickForRecursion = clock();
        if (tickForRecursion / tickForIteration > DIFFERENCE_IN_TIME || tickForIteration / tickForRecursion > DIFFERENCE_IN_TIME)
        {
            printf("The difference in implementation methods is visible with %d number", number);
            return END_OF_PROGRAM;
        }
    }
}
