#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "tree.h"
#include "errorCodes.h"

typedef struct Tree
{
    int key;
    char* data;
    Tree* leftChild;
    Tree* rightChild;
    Tree* parent;
} Tree;

static Tree* makeLeftNode(Tree* tree, int* const errorCode)
{
    Tree* parent = tree;
    Tree* pointer = (Tree*)malloc(sizeof(Tree));
    if (pointer == NULL)
    {
        *errorCode = MEMORY_ERROR;
        return NULL;
    }
    tree->leftChild = pointer;
    tree = tree->leftChild;
    tree->leftChild = NULL;
    tree->rightChild = NULL;
    tree->parent = parent;
    return tree->parent;
}

static Tree* makeRightNode(Tree* tree, int* const errorCode)
{
    Tree* parent = tree;
    Tree* pointer = (Tree*)malloc(sizeof(Tree));
    if (pointer == NULL)
    {
        *errorCode = MEMORY_ERROR;
        return NULL;
    }
    tree->rightChild = pointer;
    tree = tree->rightChild;
    tree->leftChild = NULL;
    tree->rightChild = NULL;
    tree->parent = parent;
    return tree->parent;
}

Tree* root(const Tree* const tree)
{
    if (tree->parent == NULL)
    {
        return tree;
    }
    return root(tree->parent);
}

static Tree* childNode(Tree* tree, const int key, const char* const data)
{
    if (tree->key == key)
    {
        tree->data = data;
    }

    if (tree->leftChild != NULL && tree->key > key)
    {      
        tree = tree->leftChild;
        tree = childNode(tree, key, data);
    }

    if (tree->rightChild != NULL && tree->key < key)
    {
        tree = tree->rightChild;
        tree = childNode(tree, key, data);
    }
    return tree;
}

Tree* addData(Tree* tree, const char* const data, const int key, int* const errorCode)
{
    if (tree == NULL)
    {
        Tree* root = (Tree*)malloc(sizeof(Tree));
        if (root == NULL)
        {
            *errorCode = MEMORY_ERROR;
            return NULL;
        }

        if (root == NULL)
        {
            return tree;
        }
        root->data = data;
        root->key = key;
        tree = root;
        tree->parent = NULL;
        tree->leftChild = NULL;
        tree->rightChild = NULL;
        return tree;
    }

    tree = childNode(tree, key, data);
    if (tree->key == key)
    {
        tree->data = data;
        return root(tree);
    }
    if (tree->key > key)
    {
        tree = makeLeftNode(tree, errorCode);
        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
        tree = tree->leftChild;
    }
    else
    {
        tree = makeRightNode(tree, errorCode);
        if (*errorCode != OK_CODE)
        {
            return NULL;
        }
        tree = tree->rightChild;
    }
    tree->data = data;
    tree->key = key;
    return root(tree);
}

char* searchData(Tree* tree, const int key)
{
    if (tree == NULL)
    {
        return "NULL\n";
    }

    if (tree->key == key)
    {
        return tree->data;
    }
    tree = tree->key > key ? tree->leftChild : tree->rightChild;
    return(searchData(tree, key));
    
    return tree->data;
}

bool existence(const Tree* const tree, const int key)
{
    return searchData(tree, key) != "NULL\n";
}

static Tree* searchKey(const Tree* tree, const int key)
{
    while (tree != NULL)
    {
        if (tree->key == key)
        {
            return tree;
        }
        tree = tree->key > key ? tree->leftChild : tree->rightChild;
        return (searchKey(tree, key));
    }
    return NULL;
}

void clearTree(const Tree* const tree)
{
    if (tree)
    {
        clearTree(tree->leftChild);
        clearTree(tree->rightChild);
        free(tree->data);
        free(tree);
    }
}

static Tree* deleteNonChildren(Tree* tree, const int key)
{
    if (tree->parent == NULL)
    {
        free(tree->data);
        free(tree);
        return NULL;
    }
    tree = tree->parent;
    if (tree->rightChild != NULL)
    {
        if (tree->rightChild->key == key)
        {
            free(tree->rightChild->data);
            free(tree->rightChild);
            tree->rightChild = NULL;
            return root(tree);
        }
    }
    free(tree->leftChild->data);
    free(tree->leftChild);
    tree->leftChild = NULL;
    return root(tree);
}

static Tree* deleteOneChildren(Tree* tree, const int key)
{
    if (tree->parent == NULL)
    {
        Tree* pointer = tree;
        tree = tree->leftChild != NULL ? tree->leftChild : tree->rightChild;
        tree->parent = NULL;
        free(pointer->data);
        free(pointer);
        return root(tree);
    }
    if (tree->leftChild != NULL)
    {
        tree->leftChild->parent = tree->parent;
        if (tree->key > tree->parent->key)
        {
            tree->parent->rightChild = tree->leftChild;
            Tree* pointer = tree->parent;
            free(tree->data);
            free(tree);
            return root(pointer);
        }

        tree->parent->leftChild = tree->leftChild;
        Tree* pointer = tree->parent;
        free(tree->data);
        free(tree);
        return root(pointer);
    }

    tree->rightChild->parent = tree->parent;
    if (tree->leftChild == NULL)
    {
        tree->parent->leftChild = tree->rightChild;
        Tree* pointer = tree->parent;
        free(tree->data);
        free(tree);
        return root(pointer);
    }
    tree->parent->rightChild = tree->leftChild;
    Tree* pointer = tree->parent;
    free(tree->data);
    free(tree);
    return root(pointer);
}

static Tree* deleteTwoChildren(Tree* tree, const int key)
{
    if (tree->parent == NULL)
    {
        tree->leftChild->rightChild = tree->rightChild;
        tree->rightChild->parent = tree->leftChild;
        tree = tree->leftChild;
        tree->parent = NULL;
        return root(tree);
    }
    Tree* pointer = tree;
    tree = tree->leftChild;
    while (tree->rightChild != NULL)
    {
        tree = tree->rightChild;
    }

    if (tree->leftChild != NULL)
    {
        tree->leftChild->parent = tree->parent;
    }
    tree->parent->rightChild = tree->leftChild;
    tree->parent = pointer->parent;
    if (pointer->parent->leftChild->key == pointer->key)
    {
        pointer->parent->leftChild = tree;
    }
    else
    {
        pointer->parent->rightChild = tree;
    }
    tree->leftChild = pointer->leftChild;
    tree->rightChild = pointer->rightChild;
    tree->leftChild->parent = tree;
    if (tree->rightChild != NULL)
    {
        tree->rightChild->parent = tree;
    }

    free(pointer->data);
    free(pointer);
    return root(tree);
}

Tree* deleteNode(const Tree* tree, const int key)
{
    Tree* pointer = searchKey(tree, key);
    if (pointer == NULL)
    {
        return NULL;
    }
    tree = pointer;
    if (tree->leftChild == NULL && tree->rightChild == NULL)
    {
        return deleteNonChildren(tree, key);
    }

    if ((tree->leftChild == NULL && tree->rightChild != NULL) || (tree->leftChild != NULL && tree->rightChild == NULL))
    {
        return deleteOneChildren(tree, key);
    }

    return deleteTwoChildren(tree, key);

}

char* checkData(const Tree* const tree)
{
    return tree->data;
}

int checkKey(const Tree* const tree)
{
    return tree->key;
}

Tree* checkLeftChild(const Tree* const tree)
{
    return tree->leftChild;
}

Tree* checkRightChild(const Tree* const tree)
{
    return tree->rightChild;
}

Tree* checkParent(const Tree* const tree)
{
    return tree->parent;
}
