#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "errorCode.h"
#include "workWithFile.h"

#define BY_NAME -2
#define LIMITATION 100

typedef struct Node
{
    char* name;
    char* number;
    struct Node* next;
} Node;

typedef struct Phonebook
{
    Node* head;
    Node* tail;
    size_t number;
} Phonebook;

Phonebook* addData(Phonebook* phonebook, char* name, char* number, int* const errorCode)
{
    if (phonebook == NULL)
    {
        phonebook = (Phonebook*)calloc(1, sizeof(Phonebook));
        if (phonebook == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return phonebook;
        }

        phonebook->head = (Node*)calloc(1, sizeof(Node));
        if (phonebook->head == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return phonebook;
        }

        phonebook->tail = (Node*)calloc(1, sizeof(Node));
        if (phonebook->tail == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return phonebook;
        }

        phonebook->head->name = name;
        phonebook->head->number = number;
        phonebook->tail = phonebook->head;
        ++phonebook->number;
        return phonebook;
    }

    phonebook->tail->next = (Node*)calloc(1, sizeof(Node));
    if (phonebook->tail->next == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return phonebook;
    }

    phonebook->tail->next->name = name;
    phonebook->tail->next->number = number;
    phonebook->tail = phonebook->tail->next;
    ++phonebook->number;
    return phonebook;
}

void printPhonebook(Phonebook* phonebook)
{
    Node* printBook = phonebook->head;
    while (printBook != NULL)
    {
        printf("%s - %s\n", printBook->name, printBook->number);
        printBook = printBook->next;
    }
}

static char* readFile(int* const errorCode, FILE* file)
{
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    char symbol = getc(file);

    if (symbol == EOF)
    {
        free(string);
        return NULL;
    }

    while (symbol != '\n' && symbol != ' ')
    {
        string[length++] = symbol;

        if (length >= capacity)
        {
            capacity *= 2;
            char* tmp = (char*)realloc(string, capacity * sizeof(char));
            if (tmp == NULL)
            {
                free(string);
                *errorCode = ERROR_MEMORY;
                return NULL;
            }
            string = tmp;
        }

        symbol = getc(file);
    }

    *errorCode = OK_CODE;
    string[length] = '\0';
    return string;
}

Phonebook* workWithFile(Phonebook* phonebook, FILE* file, int* errorCode)
{
    while (!feof(file))
    {
        char* name = readFile(errorCode, file);
        if (name == NULL)
        {
            break;
        }
        char* dash = readFile(errorCode, file);
        char* number = readFile(errorCode, file);
        phonebook = addData(phonebook, name, number, errorCode);
        if (phonebook->number >= LIMITATION)
        {
            break;
        }
    }
    return phonebook;
}

void findBy(Phonebook* phonebook, char* string, int userSelection)
{
    if (userSelection == BY_NAME)
    {
        Node* node = phonebook->head;
        while (node != NULL && strcmp(node->name, string) != 0)
        {
            node = node->next;
        }

        if (node == NULL)
        {
            printf("No contact with that name\n");
            return;
        }
        printf("%s - %s\n", node->name, node->number);
        return;
    }

    Node* node = phonebook->head;
    while (node != NULL && strcmp(node->number, string) != 0)
    {
        node = node->next;
    }

    if (node == NULL)
    {
        printf("No contact with that number\n");
        return;
    }
    printf("%s - %s\n", node->name, node->number);
}

void delete(Phonebook* phonebook)
{
    if (phonebook == NULL)
    {
        return;
    }
    Node* node = phonebook->head;
    while (node)
    {
        free(node->name);
        free(node->number);
        Node* trash = node;
        node = node->next;
        free(trash);
    }
    free(phonebook);
}

void saveData(Phonebook* newData, Phonebook* phonebook, FILE* file)
{
    if (newData == NULL)
    {
        return;
    }
    if (newData->number + phonebook->number > LIMITATION)
    {
        printf("Not enough space, 100 records limit exceeded\n");
        return;
    }
    Node* node = newData->head;
    phonebook->tail->next = node;
    phonebook->tail = newData->tail;
    while (node != NULL)
    {
        fprintf(&(*file), "%s - %s\n", node->name, node->number);
        node = node->next;
    }
    delete(phonebook);
    free(newData);
}

bool checkPhonebook(Phonebook* phonebook)
{
    return (strcmp(phonebook->head->name, "a") == 0 && strcmp(phonebook->head->number, "1") == 0
        && strcmp(phonebook->tail->name, "b") == 0 && strcmp(phonebook->tail->number, "2") == 0 && phonebook->number == 2);
}
