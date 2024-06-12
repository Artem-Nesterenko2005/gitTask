#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NUMBER_OF_DIGITS 32
#define ERROR_TEST -1

static void binaryRepresentation(int number, int* const array)
{
    bool const numberSign = number < 0;
    number = !numberSign ? number : abs(number) - 1;
    for (size_t i = NUMBER_OF_DIGITS + 1; --i > 0;)
    {
        array[i - 1] = number % 2;
        number /= 2;
    }
    if (numberSign)
    {
        for (size_t i = NUMBER_OF_DIGITS + 1; --i > 0;)
        {
            array[i - 1] = array[i - 1] == 1 ? 0 : 1;
        }
    }
}

static void binarySum(int* const array1, int* const array2, int* const sumArray)
{
    size_t numberTransfer = 0;
    for (size_t i  = NUMBER_OF_DIGITS + 1; --i > 0;)
    {
        sumArray[i - 1] = array1[i - 1] + array2[i - 1] + numberTransfer;
        numberTransfer = sumArray[i - 1] / 2;
        sumArray[i - 1] %= 2;
    }
}

static int decimalRepresentation(int* const arrayWithBinaryRepresentation)
{
    int decimalRepresentation = 0;
    for (size_t i = 0; i < NUMBER_OF_DIGITS; ++i)
    {
        decimalRepresentation += arrayWithBinaryRepresentation[i] * (1 << NUMBER_OF_DIGITS - 1 - i);
    }
    return decimalRepresentation;
}

static bool testCase(const size_t number1, const size_t number2, int* const right1, int* const right2)
{
    int const testArray1[NUMBER_OF_DIGITS] = { 0 };
    int const testArray2[NUMBER_OF_DIGITS] = { 0 };

    binaryRepresentation(number1, testArray1);
    binaryRepresentation(number2, testArray2);

    if ((memcmp(testArray1, right1, NUMBER_OF_DIGITS) != 0) || (memcmp(testArray2, right2, NUMBER_OF_DIGITS) != 0))
    {
        return false;
    }

    int const testSum[NUMBER_OF_DIGITS] = { 0 };
    binarySum(testArray1, testArray2, testSum);
    int const rightSum[NUMBER_OF_DIGITS] = { 0 };
    binaryRepresentation(number1 + number2, rightSum);
    if (memcmp(testSum, rightSum, NUMBER_OF_DIGITS) != 0)
    {
        return false;
    }

    if (decimalRepresentation(testArray1) != number1 || decimalRepresentation(testArray2) != number2)
    {
        return false;
    }

    return true;
}

static bool test(void)
{
    const size_t firstTestNumber1 = 5;
    const size_t firstTestnumber2 = 3;

    int const rightArray1[NUMBER_OF_DIGITS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1};
    int const rightArray2[NUMBER_OF_DIGITS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1};

    if (!testCase(firstTestNumber1, firstTestnumber2, rightArray1, rightArray2))
    {
        printf("Ошибка в тесте номер 1\n");
        return false;
    }

    int const secondTestNumber1 = -5;
    int const secondTestnumber2 = -10;

    int const rightArray3[NUMBER_OF_DIGITS] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1 };
    int const rightArray4[NUMBER_OF_DIGITS] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0 };
    
    if (!testCase(secondTestNumber1, secondTestnumber2, rightArray3, rightArray4))
    {
        printf("Ошибка в тесте номер 2\n");
        return false;
    }

    return true;
}

static void printArray(int* const array)
{
    for (size_t i = 0; ++i < NUMBER_OF_DIGITS;)
    {
        printf("%d", array[i]);
    }
    printf("\n");
}

int main(void)
{
    setlocale(LC_ALL, "RUS");
    if (!test())
    {
        printf("Ошибка в тестах");
        return ERROR_TEST;
    }

    int number1 = 0;
    printf("Введите первое число: ");
    scanf_s("%d", &number1);
    int array1[NUMBER_OF_DIGITS] = { 0 };
  
    int number2 = 0;
    printf("Введите второе число: ");
    scanf_s("%d", &number2);
    int array2[NUMBER_OF_DIGITS] = { 0 };
  
    binaryRepresentation(number1, array1);
    printf("Первое число в дополнительном коде в двоичном представлении ");
    printArray(array1);

    binaryRepresentation(number2, array2);
    printf("Второе число в дополнительном коде в двоичном представлении ");
    printArray(array2);

    int sumArray[NUMBER_OF_DIGITS] = { 0 };
    binarySum(array1, array2, sumArray);
    printf("Сумма двух чисел в двоичном представлении ");
    printArray(sumArray);

    printf("Сумма двух чисел в десятичном представлении %d", decimalRepresentation(array1) + decimalRepresentation(array2));
}
