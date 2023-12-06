#include <stdlib.h>

#include "list.h"

#define ERROR_LIST -1

typedef struct Node
{
    unsigned int data;
    struct Node* next;
}Node;

const Node* push(Node* list, const unsigned int data)
{

    Node* pointer = malloc(sizeof(Node));
    if (pointer == NULL)
    {
        return list;
    }

    if (list == NULL)
    {
        pointer->data = data;
        pointer->next = NULL;
        list = pointer;
        return list;
    }

    pointer->data = data;
    pointer->next = NULL;

    Node* head = list;

    while (nextNode(list) != NULL)
    {
        list = nextNode(list);
    }
    list->next = pointer;
    return head;
}

const Node* pop(Node* list)
{
    if (list == NULL)
    {
        return list;
    }

    if (nextNode(list) == NULL)
    {
        free(list);
        list = NULL;
        return list;
    }
    Node* pointer = list->next;

    list->next = list->next->next;
    free(pointer);
    return list;
}

const Node* nextNode(Node* list)
{
    return list->next;
}

const Node* data(Node* list)
{
    return list->data;
}

void print(Node* list)
{
    while (list != NULL)
    {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

