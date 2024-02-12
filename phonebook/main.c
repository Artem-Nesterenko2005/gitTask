#include <stdio.h>
#include <stdlib.h>

#include "phonebook.h"
#include "workWithFile.h"
#include "errorCode.h"
#include "test.h"

int main(void)
{
    if (!test())
    {
        printf("Error test");
        return ERROR_TEST;
    }
    FILE* file = NULL;
    fopen_s(&file, "phonebook.txt", "r");
    int errorCode = OK_CODE;
    Phonebook* phonebook = NULL;
    Phonebook* newData = NULL;
    phonebook = workWithFile(phonebook, file, &errorCode);
    int userSelection = 1;
    while (userSelection != exits && errorCode == OK_CODE)
    {
        printf("\n0 - Exit\n");
        printf("1 - create new records(name and phonenumber)\n");
        printf("2 - print all existing records\n");
        printf("3 - find phone by name\n");
        printf("4 - find name by phone\n");
        printf("5 - save data\n");
        printf("Choose operation ");
        scanf_s("%d", &userSelection);
        phonebook = phonebookComand(userSelection, &errorCode, file, &newData, phonebook);
    }
    delete(phonebook);
    delete(newData);
    if (file != NULL)
    {
        fclose(file);
    }
    if (errorCode == ERROR_MEMORY)
    {
        printf("Error memory");
        return ERROR_MEMORY;
    }

    return OK_CODE;
}
