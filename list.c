#include <stdlib.h>
#include <malloc.h>

#include "list.h"
#include "errorCodes.h"

typedef struct Node
{
    unsigned int data;
    struct Node* next;
}Node;

Node* listFilling(const unsigned int numberOfWarriors, int* const errorCode)
{
    Node* list = (Node*)malloc(sizeof(Node));
    if (list == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    Node* head = list;
    for (unsigned int i = 1; i < numberOfWarriors; ++i)
    {
        list->data = i;
        list->next = (Node*)malloc(sizeof(Node));
        if (list->next == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        list = list->next;
    }
    list->data = numberOfWarriors;
    list->next = head;
    return list->next;
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
