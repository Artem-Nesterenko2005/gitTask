#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK_CODE 0 
#define ERROR_TEST -1

static double iteration(double number, int degree)
{
    bool sign = degree < 0;
    degree = abs(degree);
    
    double result = 1;
    for (;degree > 0; --degree)
    {
        result = result * number;
    }
    return (sign && result != 0) ? 1 / result : result;
}

static double exponentiationLog(double number, int degree)
{
    bool sign = degree < 0;
    degree = abs(degree);

    if (degree == 0)
    {
        return 1;
    }

    if (degree % 2 == 0)
    {
        double halfPower = exponentiationLog(number, degree / 2);
        halfPower = halfPower * halfPower;
        return sign ? 1 / halfPower : halfPower;
    }

    else
    {
        double intermediateProduct = (exponentiationLog(number, degree - 1) * number);
        return sign ? 1 / intermediateProduct : intermediateProduct;
    }
}

static bool test(void)
{
    double number = 111;
    double degree = 11;
    return iteration(number, degree) == exponentiationLog(number, degree);
}

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }
    double number = 0;
    printf("Enter number ");
    scanf_s("%lf", &number);

    int degree = 0;
    printf("Enter degree ");
    scanf_s("%d", &degree);

    printf("Result of a program running in linear time %lf\n", iteration(number, degree));
    printf("Result of a program running in logarithmic time %lf", exponentiationLog(number, degree));
    return OK_CODE;
}
