#pragma once

//Changes a closing parenthesis to an opening parenthesis
char changeBrackets(char symbol);

//Checks the balance of parentheses in a string
int bracketsBalance(char string[], int length);

//Tests for bracketsBalance and changeBrackets
int test();