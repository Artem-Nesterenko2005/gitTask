#pragma once

#include <stdbool.h>

//create a row based on user data
char* readString(int* const errorCode);

//checking the balance of the bracket
bool bracketsBalance(const char* const string, const size_t length, int* const errorCode);
