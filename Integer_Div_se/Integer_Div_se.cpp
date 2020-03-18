
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         04 - Error handling
// Video          02 - Structured exception
// Example        Interger_Div_se
// File           Interger_Div_se/Interger_Div_se.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <excpt.h>
#include <stdio.h>
#include <stdlib.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_A (1)
#define ARG_B (2)

#define ARG_QTY (3)

// Class definition
/////////////////////////////////////////////////////////////////////////////

class Test
{

public:

    Test();

    ~Test();

};

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    printf("Example - Integer_Div_se\n\n");

    if (ARG_QTY > aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        fprintf(stderr, "Usage  Integer_Div_se {A} {B}\n");
        return __LINE__;
    }

    int lA = atoi(aVector[ARG_A]);
    int lB = atoi(aVector[ARG_B]);

    __try
    {
        // Test lTest;

        int lR = lA / lB;

        printf("%d / %d = %d\n", lA, lB, lR);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        fprintf(stderr, "STRUCTURED EXCEPTION  0x%08x\n", GetExceptionCode());
    }

    return 0;
}

// Public
/////////////////////////////////////////////////////////////////////////////

Test::Test()
{
    printf("Test::Test()\n");
}

Test::~Test()
{
    printf("Test::~Test()\n");
}
