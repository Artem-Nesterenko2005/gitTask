#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "tree.h"

#define ERROR_MEMORY -1

typedef struct Tree
{
    int key;
    char* data;
    Tree* leftChild;
    Tree* rightChild;
    Tree* parent;
} Tree;

static Tree* makeLeftNode(Tree* tree)
{
    Tree* parent = tree;
    Tree* pointer = (Tree*)malloc(sizeof(Tree));
    if (pointer == NULL)
    {
        return ERROR_MEMORY;
    }
    tree->leftChild = pointer;
    tree = tree->leftChild;
    tree->leftChild = NULL;
    tree->rightChild = NULL;
    tree->parent = parent;
    tree = tree->parent;
    return tree;
}

static Tree* makeRightNode(Tree* tree)
{
    Tree* parent = tree;
    Tree* pointer = (Tree*)malloc(sizeof(Tree));
    if (pointer == NULL)
    {
        return ERROR_MEMORY;
    }
    tree->rightChild = pointer;
    tree = tree->rightChild;
    tree->leftChild = NULL;
    tree->rightChild = NULL;
    tree->parent = parent;
    tree = tree->parent;
    return tree;
}

Tree* makeRoot(Tree* tree, const char* data, const int key)
{
    Tree* root = (Tree*)malloc(sizeof(Tree));
    if (root == NULL)
    {
        return ERROR_MEMORY;
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

Tree* root(Tree* tree)
{
    if (tree->parent == NULL)
    {
        return tree;
    }
    tree = tree->parent;
    root(tree);
}

static Tree* matchChecking(Tree* tree, const int key, const char* data)
{
    if (tree->key == key)
    {
        tree->data = data;
    }
    return tree;
}

static Tree* childNode(Tree* tree, const int key, const char* data)
{
    tree = matchChecking(tree, key, data);
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

Tree* addData(Tree* tree, const char* data, const int key)
{
    tree = childNode(tree, key, data);
    if (tree->key == key)
    {
        return root(tree);
    }
    if (tree->key > key)
    {
        tree = makeLeftNode(tree);
        tree = tree->leftChild;
    }
    else
    {
        tree = makeRightNode(tree);
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

bool existence(Tree* tree, const int key)
{
    return searchData(tree, key) != "NULL\n" ? true : false;
}

static Tree* searchKey(Tree* tree, const int key)
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

static Tree* deleteNonChildren(Tree* tree, const int key)
{
    if (tree->parent == NULL)
    {
        free(tree);
        return NULL;
    }
    tree = tree->parent;
    if (tree->rightChild != NULL)
    {
        if (tree->rightChild->key == key)
        {
            free(tree->rightChild);
            tree->rightChild = NULL;
            return root(tree);
        }
    }
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
            free(tree);
            return root(pointer);
        }

        tree->parent->leftChild = tree->leftChild;
        Tree* pointer = tree->parent;
        free (tree);
        return root(pointer);
    }

    tree->rightChild->parent = tree->parent;
    if (tree->leftChild == NULL)
    {
        tree->parent->leftChild = tree->rightChild;
        Tree* pointer = tree->parent;
        free(tree);
        return root(pointer);
    }
    tree->parent->rightChild = tree->leftChild;
    Tree* pointer = tree->parent;
    free(tree);
    return root(pointer);
}

static Tree* deleteTwoChildren(Tree* tree, const int key)
{
    Tree* pointer = tree;
    if (tree->parent == NULL)
    {
        tree->leftChild->rightChild = tree->rightChild;
        tree->rightChild->parent = tree->leftChild;
        tree = tree->leftChild;
        tree->parent = NULL;
        free(pointer);
        return root(tree);
    }
    tree = tree->leftChild;
    while (tree->rightChild != NULL)
    {
        tree = tree->rightChild;
    }

    if (tree->leftChild != NULL)
    {
        tree->leftChild->parent = tree->parent;
    }
    if (tree == NULL)
    {
        return tree;
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

    free(pointer);
    return root(tree);
}

Tree* deleteNode(Tree* tree, const int key)
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

Tree* checkData(Tree* tree)
{
    return tree->data;
}

Tree* checkKey(Tree* tree)
{
    return tree->key;
}

Tree* checkLeftChild(Tree* tree)
{
    return tree->leftChild;
}

Tree* checkRightChild(Tree* tree)
{
    return tree->rightChild;
}

Tree* checrParent(Tree* tree)
{
    return tree->parent;
}

