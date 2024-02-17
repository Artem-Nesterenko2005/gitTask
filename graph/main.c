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
    Graph* graph = readFile(&errorCode, "file.txt");
    if (errorCode != OK_CODE)
    {
        if (errorCode == ERROR_MEMORY)
        {
            printf("Error memory");
            return ERROR_MEMORY;
        }
        printf("Error file");
        return ERROR_FILE;
    }

    graph = assignmentCities(graph);
    print(graph);
    deleteStruct(graph);
    return OK_CODE;
}
