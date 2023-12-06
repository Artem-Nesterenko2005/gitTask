#pragma once

#include <stdbool.h>

//create a row based on user data
char* readString(int* const errorCode);

//checking the balance of the bracket
bool bracketsBalance(const char* const string, size_t const length, int* const errorCode);
