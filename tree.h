#pragma once

typedef struct Tree Tree;

//create root of tree
Tree* makeRoot(Tree* tree);

//create left child of parent
Tree* makeLeftNode(Tree* tree);

//create right child of parent
Tree* makeRightNode(Tree* tree);

//add numbers
Tree* addData(Tree* tree, const char data);

//return to parent
Tree* parent(Tree* tree);

//add operation
Tree* addParent(Tree* tree, const char data);

//print tree
void printTree(Tree* tree);

//count sum 
void postfixNotation(Tree* tree, char string[]);

//return left children of node
Tree* leftChildren(Tree* tree);

//return right children of node
Tree* rightChildren(Tree* tree);

//return data of node
Tree* data(Tree* tree);


