#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "sortedList.h"
#include "errorCode.h"

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

Node* push(Node* const list, const int data, int* const errorCode)
{
    *errorCode = OK_CODE;
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return list;
    }
    node->data = data;
    node->next = NULL;

    if (list == NULL)
    {
        return node;
    }

    if (list->next == NULL)
    {
        if (list->data > data)
        {
            node->next = list;
            return node;
        }
        list->next = node;
        return list;
    }

    if (list->data > data)
    {
        node->next = list;
        return node;
    }

    Node* auxiliaryList = list;
    while(auxiliaryList->next != NULL)
    {
        if (auxiliaryList->next->data < data)
        {
            auxiliaryList = auxiliaryList->next;
            continue;
        }
        break;
    }

    node->next = auxiliaryList->next;
    auxiliaryList->next = node;
    return list;
}

Node* pop(Node* list, const int data, int* const errorCode)
{
    *errorCode = OK_CODE;
    if (list == NULL)
    {
        *errorCode = SYMBOL_MISSING;
        return list;
    }
    Node* deletingNode = list;
    Node* previous = NULL;
    if (deletingNode != NULL && deletingNode->data == data)
    {
        list = deletingNode->next;
        free(deletingNode);
        return list;
    }

    while (deletingNode != NULL && deletingNode->data != data)
    {
        previous = deletingNode;
        deletingNode = deletingNode->next;
    }

    if (deletingNode == NULL)
    {
        *errorCode = SYMBOL_MISSING;
        return list;
    }
    previous->next = deletingNode->next;
    free(deletingNode);
    return list;
}

void printList(const Node* list)
{
    while (list)
    {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n\n");
}

int dataNode(const Node* const list)
{
    return list->data;
}

Node* nextNode(const Node* const list)
{
    return list->next;
}

void clearList(const Node** list)
{
    while ((*list) != NULL)
    {
        Node* deleteNode = *list;
        *list = (*list)->next;
        free(deleteNode);
    }
}