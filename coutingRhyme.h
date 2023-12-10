#pragma once

#include "list.h"

//fills a list with elements up to a given number
Node* listFilling(Node* list, const unsigned int numberOfWarriors, int* const errorCode);

//calculating the position of the last warrior
const unsigned int survivorStartingPosition(const unsigned int numberKilled, const unsigned int numberOfWarriors, int* const errorCode);
