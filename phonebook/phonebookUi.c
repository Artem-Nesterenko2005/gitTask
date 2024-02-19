#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#include "errorCode.h"
#include "phonebook.h"
#include "phonebookUi.h"

#define LIMITATION 100

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
    if (strcmp(string, "") == 0)
    {
        free(string);
        *errorCode = EMPTY_STRING;
        return NULL;
    }
    return string;
}

Phonebook* phonebookCommand(enum UserSelection userSelection, int* errorCode, char* fileName, Phonebook* phonebook)
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
            delete(&phonebook);
            return phonebook;
        }
        printf("Enter number of new contact ");
        char* number = readString(errorCode, stdin);
        if (*errorCode != OK_CODE)
        {
            free(name);
            delete(&phonebook);
            return phonebook;
        }
        phonebook = addData(phonebook, name, number, errorCode);
        if (*errorCode != OK_CODE)
        {
            free(name);
            free(number);
        }
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
            free(name);
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
            free(number);
            break;
        }
        printf("%s - %s\n", number, result);
        free(number);
        break;
    }

    case save:
    {
        if (phonebook == NULL)
        {
            return phonebook;
        }
        if (!checkLimitation(phonebook))
        {
            printf("Not enough space, 100 records limit exceeded\n");
            return phonebook;
        }
        FILE* file = NULL;
        fopen_s(&file, fileName, "w");
        if (file == NULL)
        {
            *errorCode = ERROR_FILE;
            return phonebook;
        }
        saveData(&phonebook, file);
        if (file != NULL)
        {
            fclose(file);
        }
        return phonebook;
    }

    default:
    {
        printf("There is no command with this number\n");
    }
    }
    return phonebook;
}
