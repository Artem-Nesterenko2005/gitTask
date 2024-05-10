#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "errorCode.h"
#include "test.h"

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }
    int errorCode = OK_CODE;
    StartData* startData = NULL;
    Graph* graph = readFile(&errorCode, "file.txt", &startData);
    if (errorCode != OK_CODE)
    {
        if (errorCode == ERROR_MEMORY)
        {
            printf("Error memory");
            return ERROR_MEMORY;
        }
        if (errorCode == INCORRECT_SYMBOL)
        {
            printf("Incorrect symbol in file");
            return INCORRECT_SYMBOL;
        }
        printf("Error file");
        return ERROR_FILE;
    }

    char* result = assignCities(graph, startData, &errorCode);
    deleteStruct(&graph);
    free(startData);
    printf("%s", result);
    free(result);
    return OK_CODE;
}
