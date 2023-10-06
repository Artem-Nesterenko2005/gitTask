#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int number = 0;
    printf("Enter a number greater than one ");
    scanf_s("%d", &number);
    if (number > 1)
    {
        for (; number > 0; --number)
        {
            int counter = 0;
            for (int divider = 2; divider <= sqrt(number + 1); ++divider)
            {
                if (number % divider == 0)
                {
                    ++counter;
                }
            }
            if (counter == 0)
            {
                printf("%d, ", number);
            }
        }
    }
    else
    {
        printf("Error");
    }
}


