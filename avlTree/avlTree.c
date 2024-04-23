#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#include "avlTree.h"
#include "errorCodes.h"

typedef struct Tree
{
    char* key;
    char* data;
    struct Tree* parent;
    struct Tree* leftChild;
    struct Tree* rightChild;
    size_t balance;
} Tree;

static int checkBalance(const Tree* const node)
{
    return node == NULL ? -1 : node->balance;
}

static void updateBalance(Tree* node)
{
    int leftBalance = checkBalance(node->leftChild);
    int rightBalance = checkBalance(node->rightChild);
    node->balance = (leftBalance > rightBalance ? leftBalance : rightBalance) + 1;
}

static int balance(Tree* node)
{
    return checkBalance(node->rightChild) - checkBalance(node->leftChild);
}

static Tree* rotateLeft(Tree* const node)
{
    Tree* auxiliaryNode = node->rightChild;
    node->rightChild = auxiliaryNode->leftChild;
    auxiliaryNode->parent = node->parent;
    if (auxiliaryNode->leftChild != NULL)
    {
        auxiliaryNode->leftChild->parent = node;
    }
    auxiliaryNode->leftChild = node;
    node->parent = auxiliaryNode;
    updateBalance(node);
    updateBalance(auxiliaryNode);
    return auxiliaryNode;
}

static Tree* rotateRight(Tree* const node)
{
    Tree* auxiliaryNode = node->leftChild;
    node->leftChild = auxiliaryNode->rightChild;
    auxiliaryNode->parent = node->parent;
    if (auxiliaryNode->rightChild != NULL)
    {
        auxiliaryNode->rightChild->parent = node;
    }
    auxiliaryNode->rightChild = node;
    node->parent = auxiliaryNode;
    updateBalance(node);
    updateBalance(auxiliaryNode);
    return auxiliaryNode;
}

static Tree* createBalance(Tree* const node)
{
    updateBalance(node);
    if (balance(node) == 2)
    {
        if (balance(node->rightChild) < 0)
        {
            node->rightChild = rotateRight(node->rightChild);
        }
        return rotateLeft(node);
    }
    if (balance(node) == -2)
    {
        if (balance(node->leftChild) > 0)
        {
            node->leftChild = rotateLeft(node->leftChild);
        }
        return rotateRight(node);
    }
    return node;
}

static void insert(Tree* const node, const char* const key, const char* const data, int* const errorCode)
{
    if (strcmp(key, node->key) == 0)
    {
        node->data = data;
        return;
    }
    if (strcmp(key, node->key) < 0)
    {
        if (node->leftChild == NULL)
        {
            Tree* newNode = (Tree*)calloc(1, sizeof(Tree));
            if (newNode == NULL)
            {
                *errorCode = MEMORY_ERROR;
                return;
            }
            newNode->parent = node;
            newNode->key = key;
            newNode->data = data;
            node->leftChild = newNode;
            return;
        }
        insert(node->leftChild, key, data, errorCode);
        node->leftChild = createBalance(node->leftChild);
    }
    if (strcmp(key, node->key) > 0)
    {
        if (node->rightChild == NULL)
        {
            Tree* newNode = (Tree*)calloc(1, sizeof(Tree));
            if (newNode == NULL)
            {
                *errorCode = MEMORY_ERROR;
                return;
            }
            newNode->parent = node;
            newNode->key = key;
            newNode->data = data;
            node->rightChild = newNode;
            return;
        }
        insert(node->rightChild, key, data, errorCode);
        node->rightChild = createBalance(node->rightChild);
    }
}

Tree* addData(Tree* tree, const char* const key, const char* const data, int* const errorCode)
{
    if (tree == NULL)
    {
        tree = (Tree*)calloc(1, sizeof(Tree));
        if (tree == NULL)
        {
            *errorCode = MEMORY_ERROR;
            return tree;
        }

        Tree* newNode =(Tree*)calloc(1, sizeof(Tree));
        if (newNode == NULL)
        {
            *errorCode = MEMORY_ERROR;
            return tree;
        }

        newNode->key = (char*)malloc(strlen(key) * sizeof(char));
        if (newNode->key == NULL)
        {
            *errorCode = MEMORY_ERROR;
            return tree;
        }
        newNode->key = key;

        newNode->data = (char*)malloc(strlen(data) * sizeof(char));
        if (newNode->data == NULL)
        {
            *errorCode = MEMORY_ERROR;
            return tree;
        }
        newNode->data = data;
        tree = newNode;
        return tree;
    }
    insert(tree, key, data, errorCode);
    if (*errorCode != OK_CODE)
    {
        return tree;
    }
    tree = createBalance(tree);
    return tree;
}

static Tree* searchKey(Tree* tree, char* key)
{
    while (tree != NULL)
    {
        if (strcmp(tree->key, key) == 0)
        {
            return tree;
        }
        tree = strcmp(tree->key,key) > 0 ? tree->leftChild : tree->rightChild;
        return (searchKey(tree, key));
    }
    return NULL;
}

char* searchData(Tree* tree, char* key)
{
    tree = searchKey(tree, key);
    if (tree == NULL)
    {
        return NULL;
    }

    if (strcmp(tree->key, key) == 0)
    {
        return tree->data;
    }

    return NULL;
}

bool keyExiste(Tree* tree, char* key)
{
    return searchData(tree, key) != NULL;
}

static Tree* newNode(Tree* tree)
{
    tree = tree->rightChild;
    while (tree->leftChild != NULL && tree != NULL)
    {
        tree = tree->leftChild;
    }
    return tree;
}

static Tree* deleteNode(Tree* tree, const char* const key)
{
    if (tree == NULL)
    {
        return tree;
    }
    if (strcmp(key, tree->key) == 0)
    {
        if (tree->rightChild != NULL && tree->leftChild != NULL)
        {
            Tree* helpNode = newNode(tree);
            tree->key = helpNode->key;
            tree->data = helpNode->data;
            deleteNode(helpNode, helpNode->key);
            return tree;
        }
        if (tree->rightChild == NULL)
        {
            if (tree->leftChild != NULL)
            {
                tree->leftChild->parent = tree->parent;
            }
            if (tree->parent == NULL && tree->leftChild != NULL)
            {
                tree->leftChild->parent = NULL;
            }
            else if (tree->parent != NULL && strcmp(key, tree->parent->key) < 0)
            {
                tree->parent->leftChild = tree->leftChild;
            }
            else if (tree->parent != NULL)
            {
                tree->parent->rightChild = tree->leftChild;
            }
            Tree* newTree = tree->leftChild;
            free(tree->data);
            free(tree->key);
            free(tree);
            return newTree;
        }
        else
        {
            if (tree->rightChild != NULL)
            {
                tree->rightChild->parent = tree->parent;
            }
            if (tree->parent == NULL)
            {
                tree->rightChild->parent = NULL;
            }
            else if (strcmp(key, tree->parent->key) < 0)
            {
                tree->parent->leftChild = tree->rightChild;
            }
            else
            {
                tree->parent->rightChild = tree->rightChild;
            }
            Tree* newTree = tree->rightChild;
            free(tree->data);
            free(tree->key);
            free(tree);
            return newTree;
            
        }
        free(tree);
        return tree;
    }
    strcmp(key, tree->key) < 0 ? deleteNode(tree->leftChild, key) : deleteNode(tree->rightChild, key);
    if (tree->parent != NULL)
    {
        if (strcmp(tree->key, tree->parent->key) < 0)
        {
            tree->parent->leftChild = createBalance(tree);
            return tree;
        }
        tree->parent->rightChild = createBalance(tree);
    }
    return tree;
}


Tree* deleteData(Tree* tree, const char* const key)
{
    if (tree == NULL)
    {
        return tree;
    }
    tree = deleteNode(tree, key);
    tree = createBalance(tree);
    return tree;
}

void deleteTree(Tree* tree)
{
    if (tree)
    {
        deleteTree(tree->leftChild);
        deleteTree(tree->rightChild);
        free(tree->data);
        free(tree->key);
        free(tree);
    }
}

bool checkData(const Tree* const tree, const char* data)
{
    return strcmp(tree->data, data) == 0;
}

bool checkKey(const Tree* const tree, const char* key)
{
    return strcmp(tree->key, key) == 0;
}
