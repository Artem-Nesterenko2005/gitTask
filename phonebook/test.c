#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "phonebook.h"
#include "errorCode.h"
#include "phonebookUi.h"

static bool testFile1(void)
{
    int errorCode = OK_CODE;
    FILE* file = NULL;
    fopen_s(&file, "test1.txt", "r");
    Phonebook* phonebook = load(file, &errorCode);
    if (errorCode != OK_CODE)
    {
        delete(&phonebook);
        return false;
    }
    if (file != NULL)
    {
        fclose(file);
    }
    if (errorCode != OK_CODE || strcmp(findBy(phonebook, "1", byNumber), "a") != 0 || strcmp(findBy(phonebook, "b", byName), "2") != 0)
    {
        delete(&phonebook);
        return false;
    }
    delete(&phonebook);
    return true;
}

static bool testFile2(void)
{
    int errorCode = OK_CODE;
    FILE* file = NULL;
    fopen_s(&file, "test2.txt", "r");
    Phonebook* phonebook = load(file, &errorCode);
    if (errorCode != OK_CODE)
    {
        delete(&phonebook);
        return false;
    }
    if (file != NULL)
    {
        fclose(file);
    }
    if (errorCode != OK_CODE || strcmp(findBy(phonebook, "9230", byNumber), "gok") != 0 || strcmp(findBy(phonebook, "lof", byName), "123") != 0)
    {
        delete(&phonebook);
        return false;
    }
    delete(&phonebook);
    return true;
}

bool test(void)
{
    return testFile1() && testFile2();
}
