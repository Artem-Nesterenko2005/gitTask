#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Lexer.h"
#include "ReadFile.h"
#include "ErrorCodes.h"

static bool testCommonFile()
{
    int errorCode = OK_CODE;
    char* fileData = readString(&errorCode, "TestComment.c");
    char* result = commentLexer("table.txt", fileData, &errorCode);
    return !strcmp(result, "/*123\n45\n6*//*7*/") && errorCode == OK_CODE;
}

static bool testTwoSlashFile()
{
    int errorCode = OK_CODE;
    char* fileData = readString(&errorCode, "TestTwoSlash.c");
    char* result = commentLexer("table.txt", fileData, &errorCode);
    return !strcmp(result, "/*///3*/") && errorCode == OK_CODE;
}

static bool testNonCommentsFile()
{
    int errorCode = OK_CODE;
    char* fileData = readString(&errorCode, "TestNonComments.c");
    char* result = commentLexer("table.txt", fileData, &errorCode);
    return result == NULL && errorCode == OK_CODE;
}

bool test()
{
    return testCommonFile() && testTwoSlashFile() && testNonCommentsFile();
}
