#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "errorCode.h"
#include "graph.h"
#include "test.h"

bool test(void)
{
    int errorCode = OK_CODE;
    StartData* startData = NULL;
    Graph* graph = readFile(&errorCode, "test.txt", &startData);
    if (errorCode != OK_CODE)
    {
        return false;
    }
    char* result = assignCities(graph, startData, &errorCode);
    deleteStruct(&graph);
    free(startData);
    return strcmp(result, "1: 1 2 \n3:3 ") && errorCode == OK_CODE;
}
