
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         02 - C/C++ particularities
// Video          07 - Security-Enhanced Version of CRT Functions
// Example        Scan_0_a_Safe
// File           Scan_0_a_Safe/Scan_0_a_Safe.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_FILE_NAME (1)

#define ARG_QTY (2)

// Static function declaration
/////////////////////////////////////////////////////////////////////////////

static int Get (const char* aAddress, const char* aFileName);
static int Post(const char* aAddress, const char* aFileName);

static int ProcessFile(FILE* aFile);

static bool ValidateAddress (const char* aAddress );
static bool ValidateFileName(const char* aFileName);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    printf("Example - Scan_0_a_Safe\n\n");

    if (ARG_QTY > aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        return __LINE__;
    }

    // TODO  Validate the filename before using it!

    FILE* lFile;

    errno_t lErr = fopen_s(&lFile, aVector[ARG_FILE_NAME], "r");
    if (0 != lErr)
    {
        fprintf(stderr, "USER ERROR  Cannot open %s - %d\n", aVector[ARG_FILE_NAME], lErr);
        return __LINE__;
    }

    assert(NULL != lFile);

    int lResult = ProcessFile(lFile);

    int lRet = fclose(lFile);
    if (0 != lRet)
    {
        fprintf(stderr, "WARNING  Error when closing %s\n", aVector[ARG_FILE_NAME]);
    }

    return lResult;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

int Get(const char* aAddress, const char* aFileName)
{
    assert(NULL != aAddress);
    assert(NULL != aFileName);

    printf("GET %s ==> %s\n", aAddress, aFileName);

    return 0;
}

int Post(const char* aAddress, const char* aFileName)
{
    assert(NULL != aAddress);
    assert(NULL != aFileName);

    printf("POST %s <== %s\n", aAddress, aFileName);

    return 0;
}

int ProcessFile(FILE* aFile)
{
    assert(NULL != aFile);

    int lResult = 0;

    while (0 == lResult)
    {
        char lAddress[64];
        char lCommand[64];
        char lFileName[64];
        char lLine[64];

        if (NULL == fgets(lLine, sizeof(lLine), aFile))
        {
            fprintf(stderr, "USER ERROR  Invalid file format\n");
            return __LINE__;
        }

        if (2 != sscanf_s(lLine, "%s %s", lCommand, sizeof(lCommand), lAddress, sizeof(lAddress)))
        {
            fprintf(stderr, "USER ERROR  Invalid command format\n");
            return __LINE__;
        }

        if (NULL == fgets(lLine, sizeof(lLine), aFile))
        {
            fprintf(stderr, "USER ERROR  Incomplete command\n");
            return __LINE__;
        }

        if (1 != sscanf_s(lLine, "%s", lFileName, sizeof(lFileName)))
        {
            fprintf(stderr, "USER ERROR  No file name\n");
            return __LINE__;
        }

        if (!ValidateAddress(lAddress))
        {
            fprintf(stderr, "USER ERROR  %s is not an allowed address\n", lAddress);
            return __LINE__;
        }

        if (!ValidateFileName(lFileName))
        {
            fprintf(stderr, "USER ERROR  %s is not an allowed filename\n", lFileName);
            return __LINE__;
        }

        if      (0 == strcmp("END" , lCommand)) { break; }
        else if (0 == strcmp("GET" , lCommand)) { lResult = Get (lAddress, lFileName); }
        else if (0 == strcmp("POST", lCommand)) { lResult = Post(lAddress, lFileName); }
        else
        {
            fprintf(stderr, "USER ERROR  %s is not a valid command\n", lCommand);
            return __LINE__;
        }
    }

    return lResult;
}

bool ValidateAddress(const char* aAddress)
{
    assert(NULL != aAddress);

    return true;
}

bool ValidateFileName(const char* aFileName)
{
    assert(NULL != aFileName);

    return true;
}
