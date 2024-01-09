#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

#include "errorCodes.h"
#include "hashTable.h"

static char* readString(int* const errorCode, const FILE* file)
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
        fclose(file);
        *errorCode = ERROR_FILE;
        return NULL;
    }

    while (symbol != EOF && symbol != ' ')
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

Table* workWithFile(const int* const fileName, int* const errorCode, const size_t size)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        *errorCode = ERROR_FILE;
        if (file != NULL)
        {
            fclose(file);
        }
        return NULL;
    }
    Table* table = NULL;
    char* string = NULL;
    while (!feof(file))
    {
        string = readString(errorCode, file);
        if (string == NULL)
        {
            fclose(file);
            return table;
        }
        table = addWord(table, string, errorCode, size);
        if (*errorCode != OK_CODE)
        {
            fclose(file);
            return NULL;
        }
    }

    fclose(file);
    return table;
}
