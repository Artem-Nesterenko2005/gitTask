#pragma once

#include <stdbool.h>

// struct for node
typedef struct Node Node;

// struct for phonebook
typedef struct Phonebook Phonebook;

// add data in phonebook
Phonebook* addData(Phonebook* phonebook, char* name, char* number, int* errorCode);

// print phonebook
void printPhonebook(Phonebook* phonebook);

// read files data
Phonebook* workWithFile(Phonebook* phonebook, FILE* file, int* errorCode);

// find data by name or by number
void findBy(Phonebook* phonebook, char* string, const int userSelection);

// delete phonebook
void delete(Phonebook* phonebook);

// save new data
void saveData(Phonebook* newData, Phonebook* phonebook, FILE* file);

// check phonebook for test
bool checkPhonebook(Phonebook* phonebook);
