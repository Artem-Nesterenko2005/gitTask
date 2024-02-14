#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "errorCode.h"
#include "workWithFile.h"
#include "phonebook.h"

char* readString(int* errorCode, FILE* file)
{
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }

    char symbol = 0;
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
        if (symbol == '\n' || symbol == ' ')
        {
            break;
        }
    }

    *errorCode = OK_CODE;
    string[length] = '\0';
    return string;
}

Phonebook* phonebookCommand(int userSelection, int* errorCode, FILE* file, Phonebook** newData, Phonebook* phonebook)
{
    switch (userSelection)
    {
    case exits:
    {
        break;
    }

    case createNew:
    {
        printf("Enter name of new contact ");
        char* name = readString(errorCode, stdin);
        if (*errorCode != OK_CODE)
        {
            delete(*newData);
            return phonebook;
        }
        printf("Enter number of new contact ");
        char* number = readString(errorCode, stdin);
        if (*errorCode != OK_CODE)
        {
            free(name);
            delete(*newData);
            return phonebook;
        }
        *newData = addData(*newData, name, number, errorCode);
        break;
    }

    case printAll:
    {
        printPhonebook(phonebook);
        break;
    }

    case findByNames:
    {
        printf("Enter name ");
        char* name = readString(errorCode, stdin);
        if (*errorCode != OK_CODE)
        {
            return phonebook;
        }
        char* result = findBy(phonebook, name, byName);
        if (result == NULL)
        {
            printf("No contact with that name\n");
            break;
        }
        printf("%s - %s\n", name, result);
        free(name);
        break;
    }

    case findByPhones:
    {
        printf("Enter number ");
        char* number = readString(errorCode, stdin);
        if (*errorCode != OK_CODE)
        {
            return phonebook;
        }
        char* result = findBy(phonebook, number, byNumber);
        if (result == NULL)
        {
            printf("No contact with that number\n");
            break;
        }
        printf("%s - %s\n", number, result);
        free(number);
        break;
    }

    case save:
    {
        fopen_s(file, "phonebook.txt", "a");
        saveData(*newData, phonebook, file);
        if (file != NULL)
        {
            fclose(file);
        }
        fopen_s(file, "phonebook.txt", "r");
        *newData = NULL;
        phonebook = NULL;
        phonebook = workWithFile(file, errorCode);
        if (file != NULL)
        {
            fclose(file);
        }
        return phonebook;
    }

    default:
    {
        printf("There is no comand with this number\n");
    }
    }
    return phonebook;
}
