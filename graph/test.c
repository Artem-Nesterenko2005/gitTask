#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "errorCode.h"
#include "graph.h"
#include "test.h"

bool test(void)
{
    int errorCode = OK_CODE;
    Graph* graph = readFile(&errorCode, "test.txt");
    if (errorCode != OK_CODE)
    {
        return false;
    }
    graph = assignmentCities(graph);
    bool result = checkTest(graph);
    deleteStruct(graph);
    return result;
}
