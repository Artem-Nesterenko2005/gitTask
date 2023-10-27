#pragma once

//Меняет закрывавшую скобку на открывавшую скобку
char changeBrackets(char symbol);

//Проверяет баланс скобок в строке
int bracketsBalance(char string[], int length);

//Тесты для bracketsBalance и changeBrackets
int test();