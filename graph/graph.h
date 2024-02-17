#pragma once

#include <stdbool.h>

// struct for a states
typedef struct State State;

// struct for a paths
typedef struct Path Path;

// struct for a number cities, number paths and number states
typedef struct startData startData;

// struct for a graph
typedef struct Graph Graph;

// delete graph
void deleteStruct(Graph* graph);

// filling a graph with data from a file
Graph* readFile(int* errorCode, char* filename);

// distribution of cities by state
Graph* assignmentCities(Graph* graph);

// print result
void print(Graph* graph);

// checking the graph under test
bool checkTest(Graph* graph);
