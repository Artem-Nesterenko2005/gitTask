#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "errorCodes.h"
#include "hashTable.h"
#include "list.h"

#define START_NUMBER 1

struct Node
{
    char* key;
    int count;
    struct Node* next;
} Node;

typedef struct List
{
    struct Node* head;
    struct Node* tail;
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
    struct Node* node = calloc(1, sizeof(Node));
    if (node == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return list;
    }
    node->key = key;
    node->count = START_NUMBER;
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
    struct Node* node = list->head;
    while (node != NULL)
    { 
        printf("%s - %d\n", node->key, node->count);
        node = node->next;
    }
}

bool checkNodes(const List* const list, const char* const key)
{
    struct Node* node = list->head;
    while (node != NULL && strcmp(node->key, key) != 0)
    {
        node = node->next;
    }
    return node == NULL;
}

void deleteList(List* const list)
{
    while (list->head != NULL)
    {
        struct Node* node = list->head;
        list->head = node->next;
        free(node->key);
        free(node);
    }
}

int count(const struct Node* const list)
{
    return list->count;
}

size_t length(const List* const list)
{
    return list->length;
}

void newData(List* list, const char* const word)
{
    while (strcmp(list->head->key, word) != 0)
    {
        list->head = list->head->next;
    }
    ++list->head->count;
}

size_t checkList(List* const list)
{
    size_t result = 0;
    while (list->head != NULL)
    {
        result += list->head->count;
        struct Node* node = list->head;
        list->head = node->next;
    }
    return result;
}
