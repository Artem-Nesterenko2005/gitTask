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
    Node* newElement = (Node*)malloc(sizeof(Node));
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

Node* listFilling(Node* list, const unsigned int numberOfWarriors, int* const errorCode)
{
    for (unsigned int i = 1; i <= numberOfWarriors; ++i)
    {
        list = push(list, i, errorCode);
        if (*errorCode != OK_CODE)
        {
            clearList(list, *errorCode);
            return NULL;
        }
    }
    return list;
}

const Node* deleteNext(Node* const list)
{
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

const Node* nextNode(const Node* const list)
{
    return list->next;
}

void clearList(Node* list)
{
    while (list->next->data != list->data)
    {
        deleteNext(list);
    }
    free(list);
}
