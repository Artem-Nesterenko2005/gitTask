#pragma once

//struct for list
typedef struct Node Node;

//function to add data to a list
Node* push(Node* const list, const int data, int* const errorCode);

//function to remove data from a list
Node* pop(Node* list, const int data, int* const errorCode);

//function to display list data
void printList(const Node* const list);

//return data from the top list
int dataNode(const Node* const list);

//return next node of list
Node* nextNode(const Node* const list);

//clear list
void clearList(const Node** list);