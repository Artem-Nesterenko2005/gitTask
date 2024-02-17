#pragma once

#include <stdbool.h>

// struct for node
typedef struct Node Node;

// struct for phonebook
typedef struct Phonebook Phonebook;

// add data in phonebook, the function takes ownership of the passed pointers and will delete them when the phonebook is deleted
Phonebook* addData(Phonebook* phonebook, char* name, char* number, int* errorCode);

// print phonebook
void printPhonebook(Phonebook* phonebook);

// read files data
Phonebook* workWithFile(FILE* file, int* errorCode);

// find data by name or by number
char* findBy(Phonebook* phonebook, char* string, enum UserSelection userSelection);

// delete phonebook
void delete(Phonebook** phonebook);

// save new data
void saveData(Phonebook* newData, Phonebook* phonebook, FILE* file);
