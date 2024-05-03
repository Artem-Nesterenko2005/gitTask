#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "errorCode.h"

#define START_NUMBER 10000

typedef struct State
{
    int* cities;
    size_t numberCities;
    int* numberStates;
} State;

typedef struct Path
{
    size_t first;
    size_t second;
    size_t length;
} Path;

typedef struct startData
{
    size_t pathsNumber;
    size_t citiesNumber;
    size_t statesNumber;
} startData;

typedef struct Graph
{
    startData* startData;
    State* states;
    Path* paths;
    int* nonStates;
} Graph;

void deleteStruct(Graph* graph)
{
    free(graph->startData);
    free(graph->states);
    free(graph->nonStates);
    free(graph->paths);
    free(graph);
}

Graph* readFile(int* errorCode, char* filename)
{
    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    if (file == NULL)
    {
        *errorCode = ERROR_FILE;
        return NULL;
    }
    Graph* graph = (Graph*)calloc(1, sizeof(Graph));
    if (graph == NULL)
    {
        fclose(file);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    graph->startData = (startData*)calloc(1, sizeof(startData));
    if (graph->startData == NULL)
    {
        fclose(file);
        free(graph);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    fscanf_s(file, "%Iu", &graph->startData->citiesNumber);
    fscanf_s(file, "%Iu", &graph->startData->pathsNumber);

    graph->nonStates = (int*)calloc(graph->startData->citiesNumber, sizeof(int));
    if (graph->nonStates == NULL)
    {
        fclose(file);
        free(graph->startData);
        free(graph);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    graph->paths = (Path*)calloc(graph->startData->pathsNumber, sizeof(Path));
    if (graph->paths == NULL)
    {
        fclose(file);
        free(graph->nonStates);
        free(graph->startData);
        free(graph);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    for (size_t i = 0; i < graph->startData->pathsNumber; ++i)
    {
        fscanf_s(file, "%Iu", &graph->paths[i].first);
        fscanf_s(file, "%Iu", &graph->paths[i].second);
        fscanf_s(file, "%Iu", &graph->paths[i].length);
    }

    fscanf_s(file, "%Iu", &graph->startData->statesNumber);

    graph->states = (State*)calloc(graph->startData->statesNumber, sizeof(State));
    if (graph->states == NULL)
    {
        fclose(file);
        free(graph->paths);
        free(graph->nonStates);
        free(graph->startData);
        free(graph);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }

    graph->states->numberStates = (int*)calloc(graph->startData->statesNumber, sizeof(int));
    if (graph->states->numberStates == NULL)
    {
        fclose(file);
        deleteStruct(graph);
        graph = NULL;
        *errorCode = ERROR_MEMORY;
        return graph;
    }

    int state = 0;
    size_t l = 0;
    for (size_t i = 0; i < graph->startData->statesNumber; ++i)
    {
        fscanf_s(file, "%d ", &state);

        graph->states[i].cities = (int*)calloc(graph->startData->statesNumber, sizeof(int));
        if (graph->states[i].cities == NULL)
        {
            fclose(file);
            deleteStruct(graph);
            graph = NULL;
            *errorCode = ERROR_MEMORY;
            return NULL;
        }

        graph->states[i].cities[0] = state;
        graph->states[i].numberCities = 1;
        graph->nonStates[state - 1] = 1;
        graph->states->numberStates[l] = state;
        ++l;
    }
    if (file != NULL)
    {
        fclose(file);
    }
    return graph;
}

Graph* assignmentCities(Graph* graph)
{
    for (size_t i = 0; i < graph->startData->citiesNumber - graph->startData->statesNumber; ++i)
    {
        for (size_t j = 0; j < graph->startData->statesNumber; ++j)
        {
            size_t startNumber = START_NUMBER;
            int* stateCity = graph->states[j].cities;
            int nearestCity = 0;

            for (size_t t = 0; t < graph->startData->citiesNumber; ++t)
            {
                if (graph->nonStates[t] != 0)
                {
                    continue;
                }

                for (size_t m = 0; m < graph->startData->citiesNumber; ++m)
                {
                    if (stateCity[m] == 0)
                    {
                        continue;
                    }

                    int numberPath = -1;
                    for (size_t k = 0; k < graph->startData->pathsNumber; ++k)
                    {
                        if ((graph->paths[k].first == t + 1 && graph->paths[k].second == stateCity[m]) || (graph->paths[k].second == t + 1 && graph->paths[k].first == stateCity[m]))
                        {
                            numberPath = k;
                            break;
                        }
                    }

                    if (numberPath != -1 && graph->paths[numberPath].length < startNumber)
                    {
                        startNumber = graph->paths[numberPath].length;
                        nearestCity = t + 1;
                    }
                }
            }
            if (nearestCity != 0)
            {
                graph->nonStates[nearestCity - 1] = 1;
                graph->states[j].cities[graph->states[j].numberCities++] = nearestCity;
            }
        }
    }
    return graph;
}

void print(Graph* graph)
{
    for (size_t i = 0; i < graph->startData->statesNumber; ++i)
    {
        printf("State %d - ", graph->states->numberStates[i]);
        for (size_t j = 0; j < graph->states[i].numberCities; j++)
        {
            printf("%d ", graph->states[i].cities[j]);
        }
        printf("\n");
    }
}

bool checkTest(Graph* graph)
{
    return graph->states[0].cities[0] == 1 && graph->states[0].cities[1] == 2 && graph->states[1].cities[0] == 3;
}
