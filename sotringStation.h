#pragma once

//create a row based on user data
char* readString(int* const errorCode);

//processing an expression into postfix form
char* stringProcessing(char* const string, char* const finalString, const int* const errorCode);

//print string elements
void printString(char* const string, size_t const length);
