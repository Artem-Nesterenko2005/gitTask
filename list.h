#pragma once

//struct for list
typedef struct Node Node;

//function to add data to a list
const Node* push(Node* list, const int data);

//function to remove data from a list
const Node* pop(Node* list, const int data);

//returns data from the top of the list
const unsigned int top(Node* const list);

//returns data from the node after the top of the list
const unsigned int nextNodeData(Node* const list);

//returns data by cell number
const unsigned int symbolFromList(Node* list, int data);
