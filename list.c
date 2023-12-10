#include <stdlib.h>

#include "list.h"
#include "errorCodes.h"

typedef struct Node
{
    unsigned int data;
    struct Node* next;
}Node;

const Node* push(Node* list, const unsigned int data, int* const errorCode)
{
    *errorCode = OK_CODE;
    Node* newElement = NULL;
    newElement = malloc(sizeof(Node));
    if (newElement == NULL)
    {
        *errorCode = ERROR_MEMORY;
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

const Node* deleteNext(Node* list, int* const errorCode)
{
    *errorCode = OK_CODE;
    if (list == NULL)
    {
        return list;
    }
    Node* deleteNode = list->next;
    list->next = list->next->next;
    free(deleteNode);
    return list;
}

const unsigned int top(const Node* const list)
{
    if (list != NULL)
    {
        return list->data;
    }
    return NULL;
}

const unsigned int nextNodeData(const Node* const list)
{
    if (list != NULL)
    {
        return list->next->data;
    }
    return NULL;
}

const Node* nextNode(const Node* list)
{
    list = list->next;
    return list;
}
