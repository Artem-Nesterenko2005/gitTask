#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "phonebook.h"
#include "errorCode.h"
#include "phonebookUi.h"

static bool testFile(void)
{
    int errorCode = OK_CODE;
    Phonebook* phonebook = load("test1.txt", &errorCode);
    if (errorCode != OK_CODE)
    {
        delete(&phonebook);
        return false;
    }
    if (errorCode != OK_CODE || strcmp(findBy(phonebook, "1", byNumber), "a") != 0 || strcmp(findBy(phonebook, "b", byName), "2") != 0)
    {
        delete(&phonebook);
        return false;
    }
    delete(&phonebook);
    return true;
}

static bool testEmptyBook(void)
{
    int errorCode = OK_CODE;
    Phonebook* phonebook = load("emptyBook.txt", &errorCode);
    if (errorCode != OK_CODE)
    {
        delete(&phonebook);
        return false;
    }
    bool result = phonebook == NULL && findBy(phonebook, "23", byNumber) == NULL && findBy(phonebook, "woie", byName) == NULL;
    delete(&phonebook);
    return result;
}

bool test(void)
{
    return testFile() && testEmptyBook();
}
