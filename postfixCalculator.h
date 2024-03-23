#pragma once

//create a row based on user data
char* readString(int* const errorCode);

//postfix calculator 
int postfixCalculator(const char* const string, const size_t length, int* const errorCode);
