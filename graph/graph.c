#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

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

typedef struct StartData
{
    size_t pathsNumber;
    size_t citiesNumber;
    size_t statesNumber;
} StartData;

typedef struct Graph
{
    State* states;
    Path* paths;
    bool* nonStates;
} Graph;

void deleteStruct(Graph** graph)
{
    free((*graph)->states);
    free((*graph)->nonStates);
    free((*graph)->paths);
    free(*graph);
    *graph = NULL;
}

static bool checkFile(char* filename)
{
    char symbol = '\0';
    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    if (file == NULL)
    {
        return false;
    }

    while (!feof(file))
    {
        fscanf_s(file, "%c", &symbol);
        if (symbol != ' ' && symbol != '\n' && !isdigit(symbol))
        {
            return false;
        }
    }
    return true;
}

Graph* readFile(int* errorCode, char* filename, StartData** startData)
{
    if (!checkFile(filename))
    {
        *errorCode = INCORRECT_SYMBOL;
        return NULL;
    }
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
    *startData = (StartData*)calloc(1, sizeof(StartData));
    if (startData == NULL)
    {
        fclose(file);
        free(graph);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    fscanf_s(file, "%Iu", (&(*startData)->citiesNumber));
    fscanf_s(file, "%Iu", (&(*startData)->pathsNumber));

    graph->nonStates = (bool*)calloc((*startData)->citiesNumber, sizeof(int));
    if (graph->nonStates == NULL)
    {
        fclose(file);
        free(startData);
        free(graph);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    graph->paths = (Path*)calloc((*startData)->pathsNumber, sizeof(Path));
    if (graph->paths == NULL)
    {
        fclose(file);
        free(startData);
        deleteStruct(&graph);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    for (size_t i = 0; i < (*startData)->pathsNumber; ++i)
    {
        fscanf_s(file, "%Iu", &graph->paths[i].first);
        fscanf_s(file, "%Iu", &graph->paths[i].second);
        fscanf_s(file, "%Iu", &graph->paths[i].length);
    }

    fscanf_s(file, "%Iu", (&(*startData)->statesNumber));

    graph->states = (State*)calloc((*startData)->statesNumber, sizeof(State));
    if (graph->states == NULL)
    {
        fclose(file);
        free(startData);
        deleteStruct(&graph);
        *errorCode = ERROR_MEMORY;
        return NULL;
    }

    graph->states->numberStates = (int*)calloc((*startData)->statesNumber, sizeof(int));
    if (graph->states->numberStates == NULL)
    {
        fclose(file);
        free(startData);
        deleteStruct(&graph);
        graph = NULL;
        *errorCode = ERROR_MEMORY;
        return graph;
    }

    int state = 0;
    size_t l = 0;
    for (size_t i = 0; i < (*startData)->statesNumber; ++i)
    {
        fscanf_s(file, "%d ", &state);

        graph->states[i].cities = (int*)calloc((*startData)->statesNumber, sizeof(int));
        if (graph->states[i].cities == NULL)
        {
            fclose(file);
            free(startData);
            deleteStruct(&graph);
            *errorCode = ERROR_MEMORY;
            return NULL;
        }

        graph->states[i].cities[0] = state;
        graph->states[i].numberCities = 1;
        graph->nonStates[state - 1] = true;
        graph->states->numberStates[l] = state;
        ++l;
    }
    if (file != NULL)
    {
        fclose(file);
    }
    return graph;
}

char* assignCities(Graph* graph, StartData* startData, int* errorCode)
{
    for (size_t cityNumber = 0; cityNumber < startData->citiesNumber - startData->statesNumber; ++cityNumber)
    {
        for (size_t stateNumber = 0; stateNumber < startData->statesNumber; ++stateNumber)
        {
            size_t startNumber = START_NUMBER;
            int* stateCity = graph->states[stateNumber].cities;
            int nearestCity = 0;

            for (int currentCity = 0; currentCity < startData->citiesNumber; ++currentCity)
            {
                if (graph->nonStates[currentCity])
                {
                    continue;
                }

                for (size_t ownCity = 0; ownCity < startData->citiesNumber; ++ownCity)
                {
                    if (stateCity[ownCity] == 0)
                    {
                        continue;
                    }

                    int numberPath = -1;
                    for (int pathNumber = 0; pathNumber < startData->pathsNumber; ++pathNumber)
                    {
                        if ((graph->paths[pathNumber].first == currentCity + 1 && graph->paths[pathNumber].second == stateCity[ownCity]) || (graph->paths[pathNumber].second == currentCity + 1 && graph->paths[pathNumber].first == stateCity[ownCity]))
                        {
                            numberPath = pathNumber;
                            break;
                        }
                    }

                    if (numberPath != -1 && graph->paths[numberPath].length < startNumber)
                    {
                        startNumber = graph->paths[numberPath].length;
                        nearestCity = currentCity + 1;
                    }
                }
            }
            if (nearestCity != 0)
            {
                graph->nonStates[nearestCity - 1] = true;
                graph->states[stateNumber].cities[graph->states[stateNumber].numberCities++] = nearestCity;
            }
        }
    }

    char* result = (char*)malloc(startData->citiesNumber * 4 * sizeof(char));
    if (result == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    size_t counter = 0;
    for (size_t i = 0; i < startData->statesNumber; ++i)
    {
        result[counter++] = graph->states->numberStates[i] + '0';
        result[counter++] = ':';
        for (size_t j = 0; j < graph->states[i].numberCities; ++j)
        {
            result[counter++] = graph->states[i].cities[j] + '0';
            result[counter++] = ' ';
        }
        result[counter++] = '\n';
    }
    result[counter] = '\0';
    return result;
}
