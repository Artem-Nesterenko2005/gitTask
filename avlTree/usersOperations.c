#include <stdlib.h>
#include <stdio.h>

#include "readString.h"
#include "errorCodes.h"
#include "avlTree.h"

#define VALUE_SIZE 100

enum Operations
{
    exitProgram,
    addNode,
    checkDataByKey,
    checkKeys,
    deleteNode
};

Tree* usersOperations(const size_t numberOperation, int* const errorCode, const Tree* tree)
{
    char* trash = getchar();
    char* key = NULL;
    char* data = NULL;
    switch (numberOperation)
    {
    case exitProgram:
        break;

    case addNode:   
        printf("Enter key: ");
        key = readString(errorCode);
        if (*errorCode != OK_CODE)
        {
            break;
        }

        printf("Enter data: ");
        data = readString(errorCode);
        if (*errorCode != OK_CODE)
        {
            break;
        }

        tree = addData(tree, key, data, errorCode);
        break;
    
    case checkDataByKey:    
        printf("Enter key: ");
        key = readString(errorCode);
        if (*errorCode != OK_CODE)
        {
            break;
        }
        const char* const data = searchData(tree, key);
        printf(data != NULL ? "Data: %s\n", data : "Data not found\n");
        free(key);
        break;
    
    case checkKeys:
        printf("Enter key: ");
        key = readString(errorCode);
        if (*errorCode != OK_CODE)
        {
            break;
        }
        printf(keyExiste(tree, key) ? "The key exists\n" : "The key does not exists\n");
        free(key);
        break;

    case deleteNode:
        printf("Enter key: ");
        key = readString(errorCode);
        if (*errorCode != OK_CODE)
        {
            break;
        }
        deleteData(tree, key);
        free(key);
        break;

    default:
        printf("There is no operation with this number\n");
    }
    return tree;
}
