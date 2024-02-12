#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "errorCode.h"
#include "workWithFile.h"
#include "phonebook.h"

static char* readString(int* errorCode, FILE* file)
{
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }

    char symbol = NULL;
    char trash = getc(file);
    if (trash == '\n')
    {
        symbol = getc(file);
    }
    else
    {
        symbol = trash;
    }

    while (symbol != EOF)
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
        if (symbol == '\n')
        {
            break;
        }
    }

    *errorCode = OK_CODE;
    string[length] = '\0';
    return string;
}

Phonebook* phonebookComand(int userSelection, int* errorCode, FILE* file, Phonebook** newData, Phonebook* phonebook)
{
    char* name = NULL;
    char* number = NULL;
    switch (userSelection)
    {
    case exits:
        break;

    case createNew:
        printf("Enter name of new contact ");
        name = readString(errorCode, stdin);
        if (*errorCode != OK_CODE)
        {
            delete(*newData);
            return phonebook;
        }
        printf("Enter number of new contact ");
        number = readString(errorCode, stdin);
        if (*errorCode != OK_CODE)
        {
            delete(*newData);
            return phonebook;
        }
        *newData = addData(*newData, name, number, errorCode);
        break;

    case printAll:
        printPhonebook(phonebook);
        break;

    case findByNames:
        printf("Enter name ");
        name = readString(errorCode, stdin);
        if (*errorCode != OK_CODE)
        {
            return phonebook;
        }
        findBy(phonebook, name, byName);
        break;

    case findByPhones:
        printf("Enter number ");
        number = readString(errorCode, stdin);
        if (*errorCode != OK_CODE)
        {
            return phonebook;
        }
        findBy(phonebook, number, byNumber);
        break;

    case save:
        fopen_s(file, "phonebook.txt", "a");
        saveData(*newData, phonebook, file);
        fopen_s(&file, "phonebook.txt", "r");
        *newData = NULL;
        phonebook = NULL;
        phonebook = workWithFile(phonebook, file, errorCode);
        return phonebook;

    default:
        printf("There is no comand with this number\n");
    }
    return phonebook;
}
