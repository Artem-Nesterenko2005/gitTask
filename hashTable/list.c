#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "errorCodes.h"
#include "hashTable.h"
#include "list.h"

#define LIMITATION 100
#define START_NUMBER 1

typedef struct Node
{
    char key[LIMITATION];
    int data;
    Node* next;
} Node;

typedef struct List
{
    Node* head;
    Node* tail;
    size_t length;
} List;

List* addData(List* list, const char* const key, int* const errorCode)
{
    if (list == NULL)
    {
        list = (List*)calloc(1, sizeof(Node));
        if (list == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
    }
    Node* node = calloc(1, sizeof(Node));
    if (node == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    strcpy_s(node->key, LIMITATION, key);
    node->data = START_NUMBER;
    ++list->length;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node; 
        return list;
    }
    list->tail->next = node;
    list->tail = node;
    return list;
}

void printList(const List* const list)
{
    Node* node = list->head;
    while (node != NULL)
    { 
        printf("%s - %d\n", node->key, node->data);
        node = node->next;
    }
}

bool checkNodes(const List* const list, const char* const key)
{
    Node* node = list->head;
    while (node != NULL && strcmp(node->key, key) != 0)
    {
        node = node->next;
    }
    return node == NULL;
}

List* deleteList(List* list)
{
    while (list->head != NULL)
    {
        Node* node = list->head;
        list->head = node->next;
        free(node->key);
    }
    return NULL;
}

int data(const Node* const list)
{
    return list->data;
}

size_t length(const List* const list)
{

    return list->length;
}

void newData(List* list)
{
    ++list->head->data;
}