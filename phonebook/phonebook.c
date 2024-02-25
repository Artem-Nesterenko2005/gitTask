#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "errorCode.h"
#include "phonebook.h"
#include "phonebookUi.h"

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
    if (phonebook == NULL)
    {
        return;
    }
    Node* printBook = phonebook->head;
    while (printBook != NULL)
    {
        printf("%s - %s\n", printBook->name, printBook->number);
        printBook = printBook->next;
    }
}

Phonebook* load(char* filename, int* errorCode)
{
    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    Phonebook* phonebook = NULL;
    if (file == NULL)
    {
        *errorCode = ERROR_FILE;
        return phonebook;
    }
    while (!feof(file))
    {
        char* name = readString(errorCode, file);
        if (name == NULL || *errorCode != OK_CODE)
        {
            if (*errorCode == EMPTY_STRING)
            {
                *errorCode = OK_CODE;
            }
            fclose(file);
            return phonebook;
        }
        char* dash = readString(errorCode, file);
        if (*errorCode != OK_CODE)
        {
            free(name);
            fclose(file);
            return phonebook;
        }
        char* number = readString(errorCode, file);
        if (*errorCode != OK_CODE)
        {
            free(name);
            free(dash);
            fclose(file);
            return phonebook;
        }
        phonebook = addData(phonebook, name, number, errorCode);
        if (*errorCode != OK_CODE)
        {
            free(name);
            free(dash);
            free(number);
            fclose(file);
            break;
        }
    }
    fclose(file);   
    return phonebook;
}

char* findBy(Phonebook* phonebook, char* string, enum UserSelection userSelection)
{
    if (phonebook == NULL)
    {
        return NULL;
    }
    if (userSelection == byName)
    {
        Node* node = phonebook->head;
        while (node != NULL && strcmp(node->name, string) != 0)
        {
            node = node->next;
        }
        if (node == NULL)
        {
            return NULL;
        }
        return node->number;
    }

    Node* node = phonebook->head;
    while (node != NULL && strcmp(node->number, string) != 0)
    {
        node = node->next;
    }
    if (node == NULL)
    {
        return NULL;
    }
    return node->name;
}

void delete(Phonebook** phonebook)
{
    if (*phonebook == NULL)
    {
        return;
    }
    Node* node = (*phonebook)->head;
    while (node)
    {
        free(node->name);
        free(node->number);
        Node* trash = node;
        node = node->next;
        free(trash);
    }
    free(*phonebook);
    *phonebook = NULL;
}

void saveData(Phonebook* phonebook, FILE* file)
{
    if (phonebook == NULL)
    {
        return;
    }
    Node* node = phonebook->head;
    while (node != NULL)
    {
        fprintf(file, "%s - %s\n", node->name, node->number);
        node = node->next;
    }
}

bool checkLimitation(Phonebook* phonebook)
{
    return phonebook->number <= LIMITATION;
}
