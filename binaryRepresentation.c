#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUMBER_OF_DIGITS 8
#define LIMITATION 255
#define ERROR_TEST -1
#define BEYOND_LIMIT -2

static void binaryRepresentation(char number, int* const array)
{
    bool numberSign = 0;
    numberSign = number < 0 ? 0 : 1;
    number = numberSign == 1 ? number : abs(number) - 1;
    for (size_t i = NUMBER_OF_DIGITS; i > 0; --i)
    {
        array[i - 1] = number % 2;
        number /= 2;
    }
    if (!numberSign)
    {
        for (size_t i = NUMBER_OF_DIGITS; i > 0; --i)
        {
            array[i - 1] = array[i - 1] == 1 ? 0 : 1;
        }
    }
}

static void columnAddition(int* const array1, int* const array2, int* const sumArray)
{
    size_t numberTransfer = 0;
    for (size_t i  = NUMBER_OF_DIGITS; i > 0; --i)
    {
        sumArray[i - 1] = array1[i - 1] + array2[i - 1] + numberTransfer;
        if (sumArray[i - 1] == 2)
        {
            numberTransfer = sumArray[i - 1] / 2;
            sumArray[i - 1] %= 2;
            continue;
        }
        if (sumArray[i - 1] == 3)
        {
            numberTransfer = sumArray[i - 1] / 2;
            sumArray[i - 1] %= 2;
            continue;
        }
        numberTransfer = 0;
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

static bool test(void)
{
    size_t firstTestNumber1 = 5;
    int firstTestArray1[NUMBER_OF_DIGITS] = { 0 };

    size_t firstTestnumber2 = 3;
    int firstTestArray2[NUMBER_OF_DIGITS] = { 0 };

    binaryRepresentation(firstTestNumber1, firstTestArray1);
    binaryRepresentation(firstTestnumber2, firstTestArray2);
    if (firstTestArray1[5] != 1 || firstTestArray1[7] != 1 || firstTestArray2[6] != 1 || firstTestArray2[7] != 1)
    {
        printf("Error test number 1\n");
        return false;
    }

    int firstTestSumArray[NUMBER_OF_DIGITS] = { 0 };
    columnAddition(firstTestArray1, firstTestArray2, firstTestSumArray);
    if (firstTestSumArray[4] != 1)
    {
        printf("Error test number 1\n");
        return false;
    }

    if (decimalRepresentation(firstTestArray1) != firstTestNumber1)
    {
        printf("Error test number 1\n");
        return false;
    }

    if (decimalRepresentation(firstTestArray2) != firstTestnumber2)
    {
        printf("Error test number 1\n");
        return false;
    }

    int secondTestNumber1 = -5;
    int secondTestArray1[NUMBER_OF_DIGITS] = { 0 };

    int secondTestnumber2 = -10;
    int secondTestArray2[NUMBER_OF_DIGITS] = { 0 };

    binaryRepresentation(secondTestNumber1, secondTestArray1);
    binaryRepresentation(secondTestnumber2, secondTestArray2);
    if (secondTestArray1[5] != 0 || secondTestArray2[4] != 0 || secondTestArray2[7] != 0)
    {
        printf("Error test number 2\n");
        return false;
    }

    int secondTestSumArray[NUMBER_OF_DIGITS] = { 0 };
    columnAddition(secondTestArray1, secondTestArray2, secondTestSumArray);
    if (secondTestSumArray[4] != 0 || secondTestSumArray[5] != 0 || secondTestSumArray[6] != 0)
    {
        printf("Error test number 2\n");
        return false;
    }

    return true;
}

static void printArray(int* const array)
{
    for (size_t i = 0; i < NUMBER_OF_DIGITS; ++i)
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
    printf("Введите первое число, меньшее 256 и большее -256 : ");
    scanf_s("%d", &number1);
    int array1[NUMBER_OF_DIGITS] = { 0 };
    if ((number1 > LIMITATION) || (number1 < -LIMITATION))
    {
        printf("Первое число не входит в заданный диапазон");
        return BEYOND_LIMIT;
    }

    int number2 = 0;
    printf("Введите второе число, меньшее 256 и большее -256 : ");
    scanf_s("%d", &number2);
    int array2[NUMBER_OF_DIGITS] = { 0 };
    if ((number2 > LIMITATION) || (number2 < -LIMITATION))
    {
        printf("Второе число не входит в заданный диапазон");
        return BEYOND_LIMIT;
    }

    binaryRepresentation(number1, array1);
    printf("Первое число в дополнительном коде в двоичном представлении ");
    printArray(array1);

    binaryRepresentation(number2, array2);
    printf("Второе число в дополнительном коде в двоичном представлении ");
    printArray(array2);

    int sumArray[NUMBER_OF_DIGITS] = { 0 };
    columnAddition(array1, array2, sumArray);
    printf("Сумма двух чисел в двоичном представлении ");
    printArray(sumArray);

    int decimalRepresentation1 = 0;
    decimalRepresentation1 = decimalRepresentation(array1);
    decimalRepresentation1 = number1 < 0 ? decimalRepresentation1 - 256 : decimalRepresentation1;

    int decimalRepresentation2 = 0;
    decimalRepresentation2 = decimalRepresentation(array2);
    decimalRepresentation2 = number2 < 0 ? decimalRepresentation2 - 256 : decimalRepresentation2;

    printf("Сумма двух чисел в десятичном представлении %d", decimalRepresentation1 + decimalRepresentation2);
}
