#pragma once

#define ERROR_LIST -1

//struct for list
typedef struct Node Node;

//function to add data to a list, return list if memory error
const Node* push(Node* list, const unsigned int data);

//function to remove data from a list, if list is empty, return list
const Node* pop(Node* list);

//return next node of list
const Node* nextNode(Node* list);

//return data of node
const Node* data(Node* list);

//print list
void print(Node* list);

