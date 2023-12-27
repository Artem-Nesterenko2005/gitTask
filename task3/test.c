#include <stdlib.h>
#include <stdbool.h>

#include "automaton.h"
#include "test.h"
#include "errorCodes.h"

bool test(void)
{
	int* const errorCode = OK_CODE;
	const char* const string1 = "12.a";
	const bool result1 = automaton(string1);

	const char* const string2 = ".v.G";
	const bool result2 = automaton(string2);

	const char* const string3 = "123";
	const bool result3 = automaton(string3);

	return result1 && result2 && !result3;
}
