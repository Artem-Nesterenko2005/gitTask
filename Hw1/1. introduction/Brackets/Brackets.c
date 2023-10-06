#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char string[100] = "0";
    printf("Enter string ");
    fgets(string, 99, stdin);
    int counter = 0;
    int limitation = strlen(string);
    for (int symbolNumber = 0; symbolNumber < limitation; ++symbolNumber)
    {
        if ((string[symbolNumber] == '(') || (string[symbolNumber] == ')'))
        {
            string[symbolNumber] == '(' ? ++counter : --counter;
        }
        if (counter < 0)
        {
            break;
        }
    }
    printf(counter == 0 ? "String is correct" : "String is not correct");
}