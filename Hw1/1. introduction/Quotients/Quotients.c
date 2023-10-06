#include <stdlib.h>
#include <stdio.h>

int main()
{
    int divisible = 0;
    int divider = 0;
    printf("Enter divisible ");
    scanf_s("%d", &divisible);
    printf("Enter divider ");
    scanf_s("%d", &divider);
    if (divider == 0)
    {
        printf("Error: you can't divide by zero");
    }
    else
    {
        int sign = 1;
        if (divisible * divider < 0)
        {
            sign = -1;
        }
        int negativeNumber = 0;
        if ((divisible < 0) && (divisible % divider != 0))
        {
            negativeNumber = 1;
        }
        divisible = abs(divisible);
        divider = abs(divider);
        int incompleteQuotient = 0;
        while (divisible >= divider)
        {
            divisible = divisible - divider;
            ++incompleteQuotient;
        }
        printf("Incomplete quotient - %d", sign * (incompleteQuotient + negativeNumber));
    }
}