#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include "ErrorCodes.h"
#include "Lexer.h"

#define SIZE_TABLE 4

typedef struct Table
{
    char current[SIZE_TABLE];
    char symbol[SIZE_TABLE];
    char next[SIZE_TABLE];
} Table;


typedef enum States
{
    start,
    slash,
    star,
    endStar,
} States;

static Table* readTable(const char* const filename, int* errorCode)
{
    Table* table = (Table*)calloc(1, sizeof(Table));
    if (table == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    FILE* expression;
    fopen_s(&expression, filename, "r");
    if (expression == NULL)
    {
        *errorCode = ERROR_FILE;
        return NULL;
    }
    char symbol = '\0';
    for (size_t i = 0; i < SIZE_TABLE; ++i)
    {
        table->current[i] = getc(expression);
        table->symbol[i] = getc(expression);
        table->next[i] = getc(expression);
        symbol = getc(expression);
    }
    return table;
}

static char* allocateMemory(size_t length, char* string, int* errorCode, size_t* capacity)
{
    char* tmp = (char*)realloc(string, length * 2 * sizeof(char));
    if (tmp == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    *capacity *= 2;
    return tmp;
}


char* commentLexer(char* filename, char* fileData, int* errorCode)
{
    States state = start;
    Table* table = readTable("table.txt", errorCode);
    if (*errorCode != OK_CODE)
    {
        return NULL;
    }

    char* result = (char*)malloc(1 * sizeof(char));
    size_t length = 0;
    size_t capacity = 1;
    for (size_t i = 0; i < strlen(fileData); ++i)
    {
        switch (state)
        {
        case (start):
            if (fileData[i] == table->symbol[0])
            {
                state = slash;
            }
            break;

        case (slash):
            if (fileData[i] == table->symbol[0])
            {
                break;
            }

            if (fileData[i] == table->symbol[1])
            {
                state = star;
                if (length >= capacity || length == 0)
                {
                    result = allocateMemory(length + 1, result, errorCode, &capacity);
                    if (*errorCode != OK_CODE)
                    {
                        free(result);
                        return NULL;
                    }
                }
                result[length++] = '/';
                result[length++] = '*';
                break;
            }
            state = start;
            break;

        case (star):
            if (fileData[i] == table->symbol[2])
            {
                state = endStar;
            }

            if (length >= capacity)
            {
                result = allocateMemory(length, result, errorCode, &capacity);
                if (*errorCode != OK_CODE)
                {
                    free(result);
                    return NULL;
                }
            }
            result[length++] = fileData[i];
            break;

        case (endStar):
            if (fileData[i] == table->symbol[3])
            {
                state = start;
            }

            if (length >= capacity)
            {
                result = allocateMemory(length, result, errorCode, &capacity);
                if (*errorCode != OK_CODE)
                {
                    free(result);
                    return NULL;
                }
            }
            result[length++] = fileData[i];
        }
    }

    if (result != NULL)
    {
        result[length] = '\0';
        if (result[length - 1] != '/' && result[length - 2] != '*')
        {
            return NULL;
        }
    }
    return result;
}
