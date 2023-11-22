#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

#include "tree.h"

#define LIMITATION 100
#define ENCODING_CONVERSION 48

typedef struct Tree
{
    char data;
    Tree* leftChild;
    Tree* rightChild;
    Tree* parent;
} Tree;

Tree* makeRoot(Tree* tree)
{
    Tree* root = (Tree*)malloc(sizeof(Tree));
    if (root == NULL)
    {
        return tree;
    }
    tree = root;
    tree->parent = NULL;
    tree->leftChild = makeLeftNode(tree);
    tree->rightChild = makeRightNode(tree);
    return tree;
}

Tree* makeLeftNode(Tree* tree)
{
    if (tree == NULL)
    {
        tree = makeRoot(tree);
    }
    Tree* parent = tree;
    Tree* pointer = (Tree*)malloc(sizeof(Tree));
    tree->leftChild = pointer;
    tree = tree->leftChild;
    tree->parent = parent;
    tree->leftChild = NULL;
    tree->rightChild = NULL;
    return tree;
}

Tree* makeRightNode(Tree* tree)
{
    if (tree == NULL)
    {
        tree = makeRoot(tree);
    }
    Tree* parent = tree;
    Tree* pointer = (Tree*)malloc(sizeof(Tree));
    tree->rightChild = pointer;
    tree = tree->rightChild;
    tree->parent = parent;
    tree->leftChild = NULL;
    tree->rightChild = NULL;
    return tree;
}

Tree* addData(Tree* tree, const char data)
{
    if (tree->leftChild->data == tree->rightChild->data)
    {
        tree->leftChild->data = data;
        return tree;
    }
    tree->rightChild->data = data;
    return tree;
}

Tree* parent(Tree* tree)
{
    if (tree->parent == NULL)
    {
        return tree;
    }
    return tree->parent;
}

Tree* addParent(Tree* tree, const char data)
{
    if (tree->leftChild->data != tree->rightChild->data)
    {
        tree = tree->rightChild;
        tree->leftChild = makeLeftNode(tree);
        tree->rightChild = makeRightNode(tree);
        tree->data = data;
        return tree;
    }

    if (tree->parent == NULL)
    {
        tree->data = data;
        tree->parent = !NULL;
        return tree;
    }

    tree = tree->leftChild;
    tree->leftChild = makeLeftNode(tree);
    tree->rightChild = makeRightNode(tree);
    tree->data = data;
    return tree;
}

void printTree(Tree* tree)
{
    if (tree->data == '+' || tree->data == '*' || tree->data == '-' || tree->data == '/')
    {
        printf("( %c ", tree->data);
    }

    else
    {
        printf("%c ", tree->data);
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

void postfixNotation(Tree* tree, char string[])
{
    static size_t i = 0;
    if (tree)
    {
        postfixNotation(tree->leftChild, string);
        postfixNotation(tree->rightChild, string);
        string[i] = tree->data;
        ++i;
    }
}

Tree* leftChildren(Tree* tree)
{
    return tree->leftChild;
}

Tree* rightChildren(Tree* tree)
{
    return tree->rightChild;
}

Tree* data(Tree* tree)
{
    return tree->data;
}
