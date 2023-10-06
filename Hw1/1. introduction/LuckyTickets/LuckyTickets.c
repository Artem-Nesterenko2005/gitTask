﻿#include <stdio.h>
#include <stdlib.h>

int main()
{
    int summCounter[28] = {0};
    for (int number1 = 0; number1 < 10; number1++)
    {
        for (int number2 = 0; number2 < 10; number2++)
        {
            for (int number3 = 0; number3 < 10; number3++)
            {
                summCounter[number1 + number2 + number3]++;
            }
        }
    }
    int tickets = 0;
    int numberArraySymbol = 0;
    for (numberArraySymbol; numberArraySymbol < 28; numberArraySymbol++)
    {
        summCounter[numberArraySymbol] = summCounter[numberArraySymbol] * summCounter[numberArraySymbol];
        tickets += summCounter[numberArraySymbol];
    }
    printf("Number of lucky tickets %d", tickets);
}

