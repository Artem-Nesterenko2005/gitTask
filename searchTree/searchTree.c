#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "tree.h"
#include "errorCodes.h"
#include "searchTree.h"

enum Operation
{
    add = 1,
    getData,
    checkForKey,
    delete,
    exitProgram
};

static char* readString(int* const errorCode)
{
    size_t length = 0;
    size_t capacity = 1;
    char* string = (char*)malloc(sizeof(char));
    if (string == NULL)
    {
        *errorCode = MEMORY_ERROR;
        return NULL;
    }
    char extraSymbol = getchar();
    char symbol = getchar();

    while (symbol != '\n')
    {
        string[length++] = symbol;

        if (length >= capacity)
        {
            capacity *= 2;
            char* tmp = (char*)realloc(string, capacity * sizeof(char));
            if (tmp == NULL)
            {
                free(string);
                *errorCode = MEMORY_ERROR;
                return NULL;
            }
            string = tmp;
        }

        symbol = getchar();
    }

    string[length] = '\0';
    return string;
}

Tree* operation(size_t numberOperation, int* const errorCode, Tree* tree)
{
    char* string = NULL;
    int key = 0;
    switch (numberOperation)
    {
    case add:
        printf("Enter key ");
        scanf_s("%d", &key);
        printf("Enter data ");
        string = readString(errorCode);
        if (*errorCode != OK_CODE)
        {
            clearTree(tree);
            return NULL;
        }
        tree = addData(tree, string, key, errorCode);
        if (*errorCode != OK_CODE)
        {
            clearTree(tree);
            return NULL;
        }
        return tree;

    case getData:
        printf("Enter a key ");
        scanf_s("%d", &key);
        printf("%s", searchData(tree, key));
        return tree;

    case checkForKey:
        printf("Enter a key ");
        scanf_s("%d", &key);
        printf(existence(tree, key) ? "The key exists\n" : "The key doesn't exist\n");
        return tree;

    case delete:
        printf("Enter key ");
        scanf_s("%d", &key);
        if (existence(tree, key))
        {
            tree = deleteNode(tree, key);
            return tree;
        }
        return tree;

    case exitProgram:
        return tree;

    default:
        printf("Operation does not exist");
        return tree;
    }

}
