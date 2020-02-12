
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         02 - C/C++ particularities
// Video          07 - Security-Enhanced Version of CRT Functions
// Example        String_0_Safe
// File           String_0_Safe/String_0_Safe.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_USER_NAME (1)
#define ARG_PASSWORD  (2)

#define ARG_QTY (3)

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static bool RetrievePassword(const char* aUserName, char* aPassword, unsigned int aPasswordSize_byte);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    printf("Example - String_0_Safe\n\n");

    if (ARG_QTY > aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        return __LINE__;
    }

    char lExpected[8];

    if (RetrievePassword(aVector[ARG_USER_NAME], lExpected, sizeof(lExpected)))
    {
        char lPassword[8];

        errno_t lErr = strcpy_s(lPassword, aVector[ARG_PASSWORD]);
        if (0 == lErr)
        {
            if (0 == strncmp(lPassword, lExpected, sizeof(lPassword)))
            {
                printf("Hello %s\n\n", aVector[ARG_USER_NAME]);
            }
            else
            {
                fprintf(stderr, "USER ERROR  Sorry, this is not your password\n\n");
            }
        }
        else
        {
            fprintf(stderr, "USER ERROR  strcpy_s( ,  )  failed - %d\n", lErr);
        }
    }
    else
    {
        fprintf(stderr, "USER ERROR  The user name is not valid\n");
    }

	return 0;
}


// Static function
/////////////////////////////////////////////////////////////////////////////

bool RetrievePassword(const char* aUserName, char* aPassword, unsigned int aPasswordSize_byte)
{
    assert(NULL != aUserName         );
    assert(NULL != aPassword         );
    assert(   0 <  aPasswordSize_byte);

    errno_t lErr = strcpy_s(aPassword, aPasswordSize_byte, "Apple");
    if (0 != lErr)
    {
        fprintf(stderr, "ERROR  strcpy_s( , )  failed - %d\n", lErr);
        return false;
    }

    return true;
}
