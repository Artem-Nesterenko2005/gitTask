#include <stdlib.h>
#include <stdio.h>

#include "errorCodes.h"
#include "hashTable.h"

Table* workWithFile(const int* const fileName, int* const errorCode)
{
    FILE* file = NULL;
    fopen_s(&file, fileName, "r");
    if (file == NULL)
    {
        *errorCode = ERROR_FILE;
        fclose(file);
        return NULL;
    }
    Table* table = NULL;
    char word[100] = { '\0' };
    while (fscanf_s(file, "%s", word, 100) != -1)
    {
        table = makeTable(table, word, errorCode);
        if (*errorCode != OK_CODE)
        {
            fclose(file);
            return NULL;
        }
    }
    fclose(file);
    return table;
}
