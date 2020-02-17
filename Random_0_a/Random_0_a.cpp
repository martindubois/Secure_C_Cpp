
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         05 - Random number generator
// Video          03 - Better random
// Example        Random_0_a
// File           Random_0_a/Random_0_a.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

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
    printf("Example - Random_0_a\n\n");

    int lRandom = open( "/dev/random", O_RDONLY );
    if ( 0 > lRandom )
    {
        fprintf( stderr, "FATAL ERROR  open(  )  failed - %d\n", lRandom );
        return __LINE__;
    }

    unsigned short lNumbers[ NUMBER_QTY ];

    ssize_t lSize_byte = read(lRandom, lNumbers, sizeof(lNumbers));
    if ( sizeof( lNumbers[ 0 ] ) <= lSize_byte)
    {
        unsigned int lCount = lSize_byte / sizeof( lNumbers[ 0 ] );

        Display( lNumbers, lCount );
    }
    else
    {
        fprintf( stderr, "ERROR  read( , ,  )  failed - %ld\n", lSize_byte);
    }

    int lRet = close(lRandom);
    if ( 0 != lRet)
    {
        fprintf( stderr, "WARNING  close(  )  failed - %d\n", lRet);
    }

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
