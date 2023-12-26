#pragma once

// read data from file
char* readFile(int* const errorCode, const char* const fileName);

// filling a string with data from a file 
int* fillingArray(char* string, size_t* const length, int* const errorCode);

// finding the most common element in an array
size_t mostCommon(int* const array, const size_t length);

// print array
void printArray(const int* const array, const size_t const length);
