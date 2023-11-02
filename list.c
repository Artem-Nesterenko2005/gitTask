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
    Node* newElement = NULL;
    newElement = malloc(sizeof(Node));
    if (newElement == NULL)
    {
        return list;
    }
    newElement->data = data;
    if (list == NULL)
    {
        newElement->next = newElement;
        return newElement;
    }
    const Node* head = list;
    while (list->next->data != head->data)
    {
        list = list->next;
    }
    list->next = newElement;
    list->next->next = head;
    return head;
}

const Node* pop(Node* list, const unsigned int data)
{
    if (list == NULL)
    {
        return list;
    }
    const unsigned int topData = list->data;

    while (list->next->data != topData)
    {
        if (list->next->data == data)
        {
            list->next = list->next->next;
            return list->next;
        }
        list = list->next;
    }

    if (list->next->data == topData)
    {
        list->next = list->next->next;
    }
    return list->next;
}

const unsigned int top(Node* const list)
{
    if (list != NULL)
    {
        return list->data;
    }
    return ERROR_LIST;
}

const unsigned int nextNodeData(Node* list)
{
    if (list != NULL)
    {
        return list->next->data;
    }
    return ERROR_LIST;
}

const Node* nextNode(Node* list)
{
    list = list->next;
    return list;
}

