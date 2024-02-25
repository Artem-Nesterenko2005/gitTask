#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

#include "tree.h"
#include "errorCodes.h"

typedef struct Tree
{
    int data;
    char operation;
    Tree* leftChild;
    Tree* rightChild;
    Tree* parent;
} Tree;

Tree* makeNode(void)
{
    return (Tree*)calloc(1, sizeof(Tree));
}

Tree* addNumber(Tree* tree, const int data, int* errorCode)
{
    if (tree->leftChild == NULL)
    {
        tree->leftChild = (Tree*)calloc(1, sizeof(Tree));
        if (tree->leftChild == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        tree->leftChild->data = data;
        tree->leftChild->parent = tree;
        return tree;
    }

    if (tree->rightChild == NULL)
    {
        tree->rightChild = (Tree*)calloc(1, sizeof(Tree));
        if (tree->rightChild == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        tree->rightChild->data = data;
        tree->rightChild->parent = tree;
        return tree;
    }
}

Tree* returnParent(const Tree* const tree)
{
    return tree->parent;
}

Tree* addOperation(Tree* tree, char data, int* errorCode)
{
    if (tree->leftChild == NULL)
    {
        tree->leftChild = (Tree*)calloc(1, sizeof(Tree));
        if (tree->leftChild == NULL)
        {
            *errorCode = ERROR_MEMORY;
            return NULL;
        }
        tree->leftChild->parent = tree;
        tree = tree->leftChild;
        tree->operation = data;
        return tree;
    }

    tree->rightChild = (Tree*)calloc(1, sizeof(Tree));
    if (tree->rightChild == NULL)
    {
        *errorCode = ERROR_MEMORY;
        return NULL;
    }
    tree->rightChild->parent = tree;
    tree = tree->rightChild;
    tree->operation = data;
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
    if (tree->operation != 0)
    {
        switch (tree->operation)
        {
        case '*':
            printf("( * ");
            break;

        case '+':
            printf("( + ");
            break;

        case '/':
            printf("( / ");
            break;

        case '-':
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

int calculateResult(Tree* tree, int* errorCode)
{
    if (tree->leftChild == NULL)
    {
        return tree->data;
    }
    const int number1 = calculateResult(tree->leftChild, errorCode);
    if (*errorCode != OK_CODE)
    {
        return 0;
    }
    const int number2 = calculateResult(tree->rightChild, errorCode);
    if (*errorCode != OK_CODE)
    {
        return 0;
    }
    const char operation = tree->operation;

    switch (operation)
    {
    case '*':
        return number1 * number2;

    case '+':
        return number1 + number2;

    case '/':
        if (number2 == 0)
        {
            *errorCode = ZERO_DIVISOR;
            return 0;
        }
        return number1 / number2;

    case '-':
        return number1 - number2;

    default:
        *errorCode = INCORRECT_SYMBOL;
        return 0;
    }
}

Tree* checkRightChildren(Tree* tree)
{
    return tree->rightChild;
}

Tree* checkLeftChildren(Tree* tree)
{
    return tree->leftChild;
}

int checkData(Tree* tree)
{
    return tree->data;
}

Tree* checkParentNode(Tree* tree)
{
    return tree->parent;
}
