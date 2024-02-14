#pragma once

#include "workWithFile.h"

enum userSelection
{
    byName = -2,
    byNumber,
    exits,
    createNew,
    printAll,
    findByNames,
    findByPhones,
    save
};

// read user string or file string
char* readString(int* errorCode, FILE* file);

// users commands
Phonebook* phonebookCommand(int userSelection, int* errorCode, FILE* file, Phonebook** newData, Phonebook* phonebook);
