#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LIMITATION_LENGTH_STRING 100

int calculatingOccurrencesOfSubstrings(char mainString[], char subString[])
{
    int const lengthMainString = strlen(mainString);
    int const lengthSubString = strlen(subString);
    int numberOccurrences = 0;
    for (int elementNumberMainString = 0; elementNumberMainString < lengthMainString; ++elementNumberMainString)
    {
        int counter = 0;
        for (int elementNumberSubString = 0; elementNumberSubString < lengthSubString; ++elementNumberSubString)
        {
            if (mainString[elementNumberMainString + elementNumberSubString] == subString[elementNumberSubString])
            {
                ++counter;
            }
            else
            {
                break;
            }
            if (counter == lengthSubString - 1)
            {
                ++numberOccurrences;
                break;
            }
        }
    }
    return numberOccurrences;
}

int testOfProgramm()
{
    char mainString[LIMITATION_LENGTH_STRING] = "123123\n";
    char subString[LIMITATION_LENGTH_STRING] = "123\n";
    int testResult = calculatingOccurrencesOfSubstrings(mainString, subString);
    return testResult;
}

int main()
{
    int test = testOfProgramm();
    if (!test)
    {
        printf("Test is error: the main string does not contain a substring");
        return 1;
    }
    char mainString[LIMITATION_LENGTH_STRING] ="";
    char subString[LIMITATION_LENGTH_STRING] = "";
    printf("Enter first string, no more than 100 symbols ");
    fgets(mainString, 99, stdin);
    printf("Enter second string, no more than 100 symbols ");
    fgets(subString, 99, stdin);
    int result = calculatingOccurrencesOfSubstrings(mainString, subString);
    printf("Number of occurrences %d", result);
}