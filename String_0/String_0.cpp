
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         02 - C/C++ particularities
// Video          06 - C string
// Example        String_0
// File           String_0/String_0.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================

#define _CRT_SECURE_NO_WARNINGS

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

static bool RetrievePassword(const char * aUserName, char * aPassword);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char ** aVector)
{
    printf("Example - String_0\n\n");

    if (ARG_QTY > aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        return __LINE__;
    }

    char lExpected[8];

    if (RetrievePassword(aVector[ARG_USER_NAME], lExpected))
    {
        char lPassword[8];

        strcpy(lPassword, aVector[ARG_PASSWORD]);

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
        fprintf(stderr, "USER ERROR  The user name is not valid\n");
    }

	return 0;
}

// Static function
/////////////////////////////////////////////////////////////////////////////

bool RetrievePassword(const char* aUserName, char * aPassword)
{
    assert(NULL != aUserName);
    assert(NULL != aPassword);

    strcpy(aPassword, "Apple");

    return true;
}
