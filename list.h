#pragma once

//struct for list
typedef struct Node Node;

//fills a list with elements up to a given number
Node* listFilling(const unsigned int numberOfWarriors, int* const errorCode);

//function to remove data from a list, if list is empty, return list
const Node* deleteNext(Node* const list);

//returns data from the top of the list
const unsigned int top(const Node* const list);

//return next node of list
const Node* nextNode(const Node* const list);

//clear list
void clearList(Node* list);
