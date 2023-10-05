#include <stdio.h>
#include <stdlib.h>

#define LIMITATION 0

int iteration(int number, int degree)
{
    if (degree >= 0)
    {
        int result = 1;
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

int recursion(int number, int degree, int result)
{
    if (degree >= 0)
    {

        if (degree == LIMITATION)
        {
            return result;
        }
        else
        {
            result = result * number;
            return recursion(number, degree - 1, result);
        }
    }
    else
    {
        return 0;
    }
}

int test()
{
    int number = 111;
    int degree = 11;
    int correctTestIteration = iteration(number, degree);
    int correctTestRecursion = recursion(number, degree, 1);
    if (correctTestIteration && correctTestRecursion)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int result = test();
    if (result != 1)
    {
        printf("Error test");
        return 0;
    }
    int number = 0;
    printf("Enter number ");
    scanf_s("%d", &number);
    int degree = 0;
    printf("Enter a positive degree ");
    scanf_s("%d", &degree);
    int startNumber = 1;
    if (degree >= 0)
    {
        int lineTime = recursion(number, degree, startNumber);
        int logTime = iteration(number, degree);
        printf("Result of a program running in linear time %d\n", lineTime);
        printf("Result of a program running in logarithmic time %d", logTime);
    }
    else
    {
        printf("Error: degree in negative");
    }

}

