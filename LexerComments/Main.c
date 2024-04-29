#include <stdio.h>
#include <stdlib.h>

#include "Lexer.h"
#include "ReadFile.h"
#include "ErrorCodes.h"
#include "TestLexer.h"

void main()
{
    if (!test())
    {
        printf("Error tests");
        return;
    }
    int errorCode = 0;
    char* fileData = readString(&errorCode, "Comment.c");
    char* result = commentLexer("", fileData, &errorCode);
    if (errorCode == ERROR_MEMORY)
    {
        printf("Memory error");
        return;
    }

    if (errorCode == ERROR_FILE)
    {
        printf("Error file");
        return;
    }

    printf(result);
}
