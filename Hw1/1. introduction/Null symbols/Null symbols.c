#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define limitation 5

int main()
{
    srand(time(NULL));
    printf("Array numbers - ");
    int array[5] = { 0,0,0,0,0 };
    int counter = 0;
    for (int symbolNumber = 0; symbolNumber < limitation; symbolNumber++)
    {
        array[symbolNumber] = rand() % 3;
        printf("%d, ", array[symbolNumber]);
        if (array[symbolNumber] == 0)
        {
            counter = counter + 1;
        }
    }
    printf("\nNumber of zeroes - %d", counter);
}