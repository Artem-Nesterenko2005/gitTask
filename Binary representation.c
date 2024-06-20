#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <math.h>

#define NUMBER_OF_DIGITS 8
#define LIMITATION 255

void conversionToBinaryRepresentation(int number1, int array[])
{   
    int numberSign = 0;
    numberSign = number1 < 0 ? 0 : 1;
    number1 = numberSign == 1 ? number1 : abs(number1) - 1;
    for (int numberSymbol = NUMBER_OF_DIGITS - 1; numberSymbol >= 0; --numberSymbol)
    {
        array[numberSymbol] = number1 % 2 == 1 ? 1 : 0;
        number1 /= 2;
    }
    if (numberSign == 0)
    {
        for (int counterChangeSymbol = 7; counterChangeSymbol >= 0; --counterChangeSymbol)
        {
            array[counterChangeSymbol] = array[counterChangeSymbol] == 1 ? 0 : 1;
        }
    }
}

void columnAddition(int array1[], int array2[], int summArray[])
{
    int numberTransfer = 0;
    for (int rankNumber = NUMBER_OF_DIGITS - 1; rankNumber >= 0; --rankNumber)
    {
        summArray[rankNumber] = array1[rankNumber] + array2[rankNumber] + numberTransfer;
        if (summArray[rankNumber] == 2)
        {
            numberTransfer = 1;
            summArray[rankNumber] = 0;
            continue;
        }
        if (summArray[rankNumber] == 3)
        {
            numberTransfer = 1;
            summArray[rankNumber] = 1;
            continue;
        }
        numberTransfer = 0;
    }
}
 
int conversionToDecimalRepresentation(int arrayWithBinaryRepresentation[])
{
    int decimalRepresentation = 0;
    for (int counterDecimalRepresentation = 0; counterDecimalRepresentation < NUMBER_OF_DIGITS; ++counterDecimalRepresentation)
    {
        decimalRepresentation = arrayWithBinaryRepresentation[counterDecimalRepresentation] * pow(2, NUMBER_OF_DIGITS - 1 - counterDecimalRepresentation) + decimalRepresentation;
    }
    return decimalRepresentation;
}

int test()
{
    int firstTestNumber1 = 5;
    int firstTestArray1[NUMBER_OF_DIGITS] = { 0 };

    int firstTestnumber2 = 3;
    int firstTestArray2[NUMBER_OF_DIGITS] = { 0 };

    conversionToBinaryRepresentation(firstTestNumber1, firstTestArray1);
    conversionToBinaryRepresentation(firstTestnumber2, firstTestArray2);
    int* firstTestSummArray = 0;
    firstTestSummArray = malloc(NUMBER_OF_DIGITS * sizeof(int));
    if (firstTestSummArray == NULL)
    {
        printf("Память не выделена");
        return 0;
    }
    columnAddition(firstTestArray1, firstTestArray2, firstTestSummArray);
    free(firstTestSummArray);

    int firstTestDecimalRepresentationFirstNumber = 0;
    firstTestDecimalRepresentationFirstNumber = conversionToDecimalRepresentation(firstTestArray1);

    int firstTestDecimalRepresentationSecondNumber = 0;
    firstTestDecimalRepresentationSecondNumber = conversionToDecimalRepresentation(firstTestArray2);
    int resultTest = 0;
    if ((firstTestDecimalRepresentationFirstNumber == firstTestNumber1) && (firstTestDecimalRepresentationSecondNumber == firstTestnumber2))
    {
        ++resultTest;
    }

    int secondTestNumber1 = -5;
    int secondTestArray1[NUMBER_OF_DIGITS] = { 0 };

    int secondTestnumber2 = -10;
    int secondTestArray2[NUMBER_OF_DIGITS] = { 0 };

    conversionToBinaryRepresentation(secondTestNumber1, secondTestArray1);
    conversionToBinaryRepresentation(secondTestnumber2, secondTestArray2);
    int* secondTestSummArray = 0;
    secondTestSummArray = malloc(NUMBER_OF_DIGITS * sizeof(int));
    if (secondTestSummArray == NULL)
    {
        printf("Память не выделена");
        return 0;
    }
    columnAddition(secondTestArray1, secondTestArray2, secondTestSummArray);
    free(secondTestSummArray);

    int secondTestDecimalRepresentationFirstNumber = 0;
    secondTestDecimalRepresentationFirstNumber = conversionToDecimalRepresentation(secondTestArray1);

    int secondTestDecimalRepresentationSecondNumber = 0;
    secondTestDecimalRepresentationSecondNumber = conversionToDecimalRepresentation(secondTestArray2);
    if ((secondTestDecimalRepresentationFirstNumber - 256 == secondTestNumber1) && (secondTestDecimalRepresentationSecondNumber - 256 == secondTestnumber2));
    {
        ++resultTest;
    }
    return resultTest;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    if (test() != 2)
    {
        printf("Ошибка в тестах");
        return 0;
    }
    int number1 = 0;
    printf("Введите первое число, меньшее 256 и большее -256 : ");
    scanf_s("%d", &number1);
    int array1[NUMBER_OF_DIGITS] = { 0 };
    if ((number1 > LIMITATION) || (number1 < -LIMITATION))
    {
        printf("Первое число не входит в заданный диапазон");
        return 0;
    }
    int number2 = 0;
    printf("Введите второе число, меньшее 256 и большее -256 : ");
    scanf_s("%d", &number2);
    int array2[NUMBER_OF_DIGITS] = { 0 };
    if ((number2 > LIMITATION) || (number2 < -LIMITATION))
    {
        printf("Второе число не входит в заданный диапазон");
        return 0;
    }

    conversionToBinaryRepresentation(number1, array1);
    printf("Первое число в дополнительном коде в двоичном представлении ");
    for (int printSymbolArray1 = 0; printSymbolArray1 < NUMBER_OF_DIGITS; ++printSymbolArray1)
    {
        printf("%d", array1[printSymbolArray1]);
    }

    conversionToBinaryRepresentation(number2, array2);
    printf("\nВторое число в дополнительном коде в двоичном представлении ");
    for (int printSymbolArray2 = 0; printSymbolArray2 < NUMBER_OF_DIGITS; ++printSymbolArray2)
    {
        printf("%d", array2[printSymbolArray2]);
    }

    int* summArray = 0;
    summArray = malloc(NUMBER_OF_DIGITS * sizeof(int));
    if (summArray == NULL)
    {
        printf("Память не выделена");
        return 0;
    }
    columnAddition(array1, array2, summArray);
    printf("\nСумма двух чисел в двоичном представлении ");
    for (int i = 0; i < 8; ++i)
    {
        printf("%d", summArray[i]);
    }
    free(summArray);

    int decimalRepresentationFirstNumber = 0;
    decimalRepresentationFirstNumber = conversionToDecimalRepresentation(array1);
    decimalRepresentationFirstNumber = number1 < 0 ? decimalRepresentationFirstNumber - 256 : decimalRepresentationFirstNumber;

    int decimalRepresentationSecondNumber = 0;
    decimalRepresentationSecondNumber = conversionToDecimalRepresentation(array2);
    decimalRepresentationSecondNumber = number2 < 0 ? decimalRepresentationSecondNumber - 256 : decimalRepresentationSecondNumber;

    int summDecimalNumbers = 0;
    summDecimalNumbers = decimalRepresentationFirstNumber + decimalRepresentationSecondNumber;
    printf("\nСумма двух чисел в десятичном представлении %d", summDecimalNumbers);
}