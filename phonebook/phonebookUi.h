#pragma once

#include "phonebook.h"

enum UserSelection
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
Phonebook* phonebookCommand(enum UserSelection userSelection, int* errorCode, char* fileName, Phonebook* phonebook);
