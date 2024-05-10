#pragma once

#include <stdbool.h>

// struct for a number cities, number paths and number states
typedef struct StartData StartData;

// struct for a graph
typedef struct Graph Graph;

// delete graph
void deleteStruct(Graph** graph);

// filling a graph with data from a file
Graph* readFile(int* errorCode, char* filename, StartData** startData);

// distribution of cities by state
char* assignCities(Graph* graph, StartData* startData, int* errorCode);
