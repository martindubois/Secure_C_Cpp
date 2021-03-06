
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         05 - Random number generator
// Video          02 - rand function
// Example        Random_0
// File           Random_0/Random_0.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define NUMBER_QTY (100)

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void Display( const unsigned short * aIn, unsigned int aCount );

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Example - Random_0\n\n");

    time_t lTime;

    srand(static_cast<unsigned int>(time(&lTime)));

    unsigned short lNumbers[ NUMBER_QTY ];

    for (unsigned int i = 0; i < NUMBER_QTY; i++)
    {
        lNumbers[ i ] = rand();
    }

    Display( lNumbers, NUMBER_QTY );

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
