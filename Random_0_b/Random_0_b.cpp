
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         05 - Random number generator
// Video          03 - Better random
// Example        Random_0_b
// File           Random_0_b/Random_0_b.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Windows ============================================================
#include <Windows.h>
#include <bcrypt.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define NUMBER_QTY (100)

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void Display(const unsigned short * aIn, unsigned int aCount);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Example - Random_0_a\n\n");

    unsigned short lNumbers[NUMBER_QTY];

    NTSTATUS lStatus = BCryptGenRandom(NULL, reinterpret_cast<PUCHAR>(lNumbers), sizeof(lNumbers), BCRYPT_USE_SYSTEM_PREFERRED_RNG);
    if (0 != lStatus)
    {
        fprintf(stderr, "ERROR  BCryptGenRandom( , , ,  )  failed - 0x%08x\n", lStatus);
        return __LINE__;
    }

    Display(lNumbers, NUMBER_QTY);

	return 0;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void Display( const unsigned short * aIn, unsigned int aCount )
{
    assert( NULL != aIn );

    printf( "%u values\n", aCount );

    for (unsigned int i = 0; i < aCount; i++)
    {
        switch (i % 8)
        {
            case 0 : printf( "\n" ); break;
            case 4 : printf( "  " ); break;
            default: printf( " "  );
        }

        printf( "%5u", aIn[ i ] );
    }

    printf( "\n" );
}
