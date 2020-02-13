
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         02 - C/C++ particularities
// Video          07 - Security-Enhanced Version of CRT Functions
// Example        Format_0_Safe
// File           Format_0_Safe/Format_0_Safe.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

// ===== Common =============================================================
#include "../Common/Dump.h"

#ifndef _WIN32
    #include "../Common/WindowsOnLinux.h"
#endif

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_FILE_NAME (1)

#define ARG_QTY (2)

#define BLOCK_SIZE_byte (128)

// Static function declaration
/////////////////////////////////////////////////////////////////////////////

static char* RetrieveSecretKey();

static void UncryptBlock(char* aInOut, const char* aSecretKey);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    printf("Example - Format_0_Safe\n\n");

    if (ARG_QTY > aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        return __LINE__;
    }

    char* lSecretKey = RetrieveSecretKey();
    assert(NULL != lSecretKey);

    int lResult;

    FILE* lFile;

    errno_t lErr = fopen_s(&lFile, aVector[ARG_FILE_NAME], "r");
    if (0 != lErr)
    {
        fprintf(stderr, "USER ERROR  Cannot open ");
        fprintf(stderr, aVector[ARG_FILE_NAME]);
        fprintf(stderr, " - %d\n", lErr);
        lResult = __LINE__;
    }
    else
    {
        assert(NULL != lFile);

        int lRet;

        do
        {
            char lBuffer[BLOCK_SIZE_byte];

            memset(&lBuffer, 0, BLOCK_SIZE_byte);

            lRet = fread(lBuffer, 1, BLOCK_SIZE_byte, lFile);

            UncryptBlock(lBuffer, lSecretKey);

            Dump(lBuffer, lRet);
        } while (BLOCK_SIZE_byte == lRet);

        lRet = fclose(lFile);
        if (0 != lRet)
        {
            fprintf(stderr, "WARNING  Error when closing the input file - %d\n", lRet);
        }

        lResult = 0;
    }

    free(lSecretKey);

    return lResult;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

char* RetrieveSecretKey()
{
    return _strdup("This is the very important secret key");
}

void UncryptBlock(char* aInOut, const char* aSecretKey)
{
    assert(NULL != aInOut    );
    assert(NULL != aSecretKey);
}
