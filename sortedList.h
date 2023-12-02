#pragma once

//struct for list
typedef struct Node Node;

//function to add data to a list
static Node* push(Node* list, const int data);

//function to remove data from a list
static Node* pop(Node* list, const int data);

//function to display list data
static void printList(Node* list);

//function to perform an operation selected by the user
static Node* listOperations(int numberOperation, Node* list);

//Test for push and pop function
static bool test(void);

