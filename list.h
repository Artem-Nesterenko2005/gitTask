#pragma once

//struct for list
typedef struct Node Node;

//function to add data to a list, return list if memory error
const Node* push(Node* list, const unsigned int data, int* const errorCode);

//function to remove data from a list, if list is empty, return list
const Node* deleteNext(Node* list, int* const errorCode);

//returns data from the top of the list
const unsigned int top(const Node* const list);

//returns data from the node after the top of the list
const unsigned int nextNodeData(const Node* const list);

//return next node of list
const Node* nextNode(const Node* list);
