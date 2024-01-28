#pragma once

#include <stdbool.h>

// struct for node
struct Node;

// struct for list
typedef struct List List;

// add data for node 
List* addData(List* const list, const char* const key, int* const errorCode);

// print list
void printList(const List* const list);

// checks nodes with the same field data
bool checkNodes(const List* const list, const char* const key);

// delete list
void deleteList(List* const list);

// return length of node
size_t length(const List* const list);

// change data of node
void newData(List* list, const char* const word);

// check string of the list
size_t checkList(List* const list);
