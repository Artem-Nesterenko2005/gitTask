#pragma once

// states
enum States;

// read users string
char* readString(int* const errorCode);

// automaton 
bool automaton(const char* const string);
