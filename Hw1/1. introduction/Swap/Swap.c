#include <stdio.h>
#include <stdlib.h>

int main()
{
    int variable1 = 0;
    int variable2 = 0;
    printf("Enter the first integer variable ");
    scanf_s("%d", &variable1);
    printf("Enter the second integer variable ");
    scanf_s("%d", &variable2);
    variable1 = variable1 + variable2;
    variable2 = variable1 - variable2;
    variable1 = variable1 - variable2;
    printf("First variable = %d\n", variable1);
    printf("Second variable = %d", variable2);
}