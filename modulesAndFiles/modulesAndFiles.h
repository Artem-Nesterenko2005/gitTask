#pragma once

// read data from file
int* readFile(int* const errorCode, char* fileName, int* lengthArray);

// finding the most common element in an array
size_t mostCommon(const int* array, const size_t length);

// print array
void printArray(const int* const array, const size_t length);
