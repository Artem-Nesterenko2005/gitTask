#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

#include "tree.h"
#include "errorCodes.h"

#define ENCODING_CONVERSION 48

enum operations
{
    MULTIPLICATION = -6,
    ADDITION,
    DIVISION,
    SUBTRACTION
};

typedef struct Tree
{
    int data;
    Tree* leftChild;
    Tree* rightChild;
    Tree* parent;
} Tree;

Tree* makeRoot(int* const errorCode)
{
    Tree* root = (Tree*)malloc(sizeof(Tree));
    if (root == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    root->parent = NULL;
    root->leftChild = NULL;
    root->rightChild = NULL;
    return root;
}

Tree* addData(Tree* tree, const int data, int* const errorCode)
{
    if (tree->leftChild == NULL)
    {
        tree->leftChild = (Tree*)malloc(sizeof(Tree));
        if (tree->leftChild == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        tree->leftChild->data = data;
        tree->leftChild->parent = tree;
        tree->leftChild->leftChild = NULL;
        tree->leftChild->rightChild = NULL;
        return tree;
    }
    tree->rightChild = (Tree*)malloc(sizeof(Tree));
    if (tree->rightChild == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    tree->rightChild->data = data;
    tree->rightChild->parent = tree;
    tree->rightChild->leftChild = NULL;
    tree->rightChild->rightChild = NULL;
    return tree;
}

Tree* parent(const Tree* const tree)
{
    return tree->parent;
}

Tree* addParent(Tree* tree, const int data, int* const errorCode)
{
    if (tree->parent == NULL && tree->data != MULTIPLICATION && tree->data != ADDITION && tree->data != DIVISION && tree->data != SUBTRACTION)
    {
        tree->data = data;
        return tree;
    }

    if (tree->leftChild == NULL)
    {
        tree->leftChild = (Tree*)malloc(sizeof(Tree));
        if (tree->leftChild == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        tree->leftChild->parent = tree;
        tree = tree->leftChild;
        tree->data = data;
        tree->leftChild = NULL;
        tree->rightChild = NULL;
        return tree;
    }

    tree->rightChild = (Tree*)malloc(sizeof(Tree));
    if (tree->rightChild == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    tree->rightChild->parent = tree;
    tree = tree->rightChild;
    tree->data = data;
    tree->leftChild = NULL;
    tree->rightChild = NULL;
    return tree;
}

void clearTree(Tree* tree)
{
    if (tree)
    {
        clearTree(tree->leftChild);
        clearTree(tree->rightChild);
        free(tree);
    }
}

void printTree(const Tree* const tree)
{
    if (tree->data == MULTIPLICATION || tree->data == ADDITION || tree->data == DIVISION || tree->data == SUBTRACTION)
    {
        switch (tree->data)
        {
        case MULTIPLICATION:
            printf("( * ");
            break;

        case ADDITION:
            printf("( + ");
            break;

        case DIVISION:
            printf("( / ");
            break;

        case SUBTRACTION:
            printf("( - ");
            break;
        }
    }

    else
    {
        printf("%d ", tree->data);
    }

    if (tree->leftChild != NULL)
    {
        printTree(tree->leftChild);
    }

    if (tree->rightChild != NULL)
    {
        printTree(tree->rightChild);
        printf(") ");
    }
}

Tree* leftChildren(const Tree* const tree)
{
    return tree->leftChild;
}

Tree* rightChildren(const Tree* const tree)
{
    return tree->rightChild;
}

int data(const Tree* const tree)
{
    return tree->data;
}

void changeData(Tree* const tree, int const data)
{
    tree->data = data;
}

Tree* checkParent(const Tree* const tree)
{
    return tree->parent;
}
