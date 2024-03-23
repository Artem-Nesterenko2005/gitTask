#include <stdio.h>
#include <stdlib.h>

#include "errorCodes.h"
#include "readString.h"

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
