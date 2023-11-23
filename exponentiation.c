#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LIMITATION 0
#define END 0 
#define ERROR_TEST -1

static double iteration(double number, int degree)
{
    if (degree >= 0)
    {
        double result = 1;
        for (degree; degree > LIMITATION; --degree)
        {
            result = result * number;
        }
        return result;
    }
    else
    {
        return 0;
    }
}

static double exponentiationLog(double number, int degree)
{
    if (degree == 0)
    {
        return 1;
    }
    if (degree % 2 == 0)
    {
        double halfPower = exponentiationLog(number, degree / 2);
        return halfPower * halfPower;
    }
    else
    {
        return  exponentiationLog(number, degree - 1) * number;
    }
}

static bool test(void)
{
    double number = 111;
    double degree = 11;
    if (iteration(number, degree)&& exponentiationLog(number, degree, 1))
    {
        return true;
    }
    return false;
}

int main(void)
{
    if (test() != true)
    {
        printf("Error test");
        return ERROR_TEST;
    }
    double number = 0;
    printf("Enter number ");
    scanf_s("%lf", &number);
    int degree = 0;
    printf("Enter a positive degree ");
    scanf_s("%d", &degree);
    double iterationResult = iteration(number, abs(degree));
    double logNResult = exponentiationLog(number, abs(degree));
    if (degree < 0)
    {
        iterationResult = 1 / iterationResult;
        logNResult = 1 / logNResult;
    }
    printf("Result of a program running in linear time %lf\n", iterationResult);
    printf("Result of a program running in logarithmic time %lf", logNResult);
    return END;
}

