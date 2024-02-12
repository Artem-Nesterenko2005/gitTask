#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "workWithFile.h"
#include "errorCode.h"

bool test(void)
{
    Phonebook* phonebook = NULL;
    int errorCode = OK_CODE;
    phonebook = addData(phonebook, "a", "1", &errorCode);
    phonebook = addData(phonebook, "b", "2", &errorCode);
    if (errorCode != OK_CODE || !checkPhonebook(phonebook))
    {
        return false;
    }
    free(phonebook);
    phonebook = NULL;
    FILE* file = NULL;
    fopen_s(&file, "test.txt", "r");
    phonebook = workWithFile(phonebook, file, &errorCode);
    if (errorCode != OK_CODE || !checkPhonebook(phonebook))
    {
        if (file != NULL)
        {
            fclose(file);
        }
        return false;
    }
    if (file != NULL)
    {
        fclose(file);
    }
    delete(phonebook);
    return true;
}
