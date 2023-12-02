#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "sortedList.h"

#define ORIGINAL_MEANING 1
#define EXIT_NUMBER 0
#define ERROR_TEST 0

typedef struct Node
{
    int data;
    struct Node* next;
}Node;

static Node* push(Node* list, const int data)
{
    Node* pointer = malloc(sizeof(Node));
    if (pointer == NULL)
    {
        return list;
    }
    pointer->data = data;

    if (list == NULL || list->data > data)
    {
        pointer->next = list;
        return pointer;
    }

    pointer->next = NULL;
    Node * head = list;
    while (head->next != NULL && head->next->data > data)
    {
        head = head->next;
    }
    while (list->next != NULL)
    {
        list = list->next;
    }
    list->next = pointer;
    return head;
}

static Node* pop(Node* list, const int data)
{
    if (list == NULL)
    {
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
        return list;
    }
    previous->next = deletingNode->next;
    free(deletingNode);
    return list;
}

static void printList(Node* list)
{
    while (list)
    {
        printf("%d ", list->data);
        list = list->next;
    }
    printf("\n");
}

static Node* listOperations(int numberOperation, Node* list)
{
    int data = 0;
    switch (numberOperation)
    {
    case 0:
        break;

    case 1:
        printf("Enter number ");
        scanf_s("%d", &data);
        printf("\n");
        list = push(list, data);
        break;

    case 2:
        printf("Enter number ");
        scanf_s("%d", &data);
        printf("\n");
        list = pop(list, data);
        break;

    case 3:
        printf("Sorted list: ");
        printList(list);
        printf("\n");
        break;
    default:
        printf("The transaction with this number does not exist\n\n");
    }
    return list;
}

static bool test(void)
{
    Node* testList = NULL;
    testList = push(testList, 10);
    bool pushTest1 = 0;
    pushTest1 = testList->data == 10 ? true : false;
    if (!pushTest1)
    {
        return false;
    }

    testList = push(testList, 20);
    bool pushTest2 = 0;
    pushTest2 = testList->next->data == 20 ? true : false;
    if (!pushTest2)
    {
        return false;
    }

    testList = pop(testList, 20);
    bool popTest1 = 0;
    popTest1 = testList->data == 10 ? true : false;
    if (!popTest1)
    {
        return false;
    }

    testList = pop(testList, 3);
    bool popTest2 = 0;
    popTest2 = testList->data == 10 ? true : false;
    if (!popTest2)
    {
        return false;
    }
    free(testList);
    return true;
}

void main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }
    unsigned int transactionNumber = ORIGINAL_MEANING;
    Node* list = NULL;
    while (transactionNumber != EXIT_NUMBER)
    {
        printf("0 - exit\n");
        printf("1 - add value to sorted list\n");
        printf("2 - remove value from list\n");
        printf("3 - print list\n");
        printf("Select operation: ");
        scanf_s("%d", &transactionNumber);
        list = listOperations(transactionNumber, list);
    }
}

