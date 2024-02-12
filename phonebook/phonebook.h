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

// users comands
Phonebook* phonebookComand(int userSelection, int* errorCode, FILE* file, Phonebook** newData, Phonebook* phonebook);
