
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         03 - Interacting with the world
// Video          06 - File name validation
// Example        Symlink_a
// File           SymLink_a/SymLink_a.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// ===== System =============================================================
#include <sys/stat.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_FILE_NAME (1)

#define ARG_QTY (2)

// Static fonction declaration
/////////////////////////////////////////////////////////////////////////////

static bool ValidateFileName( const char * aFileName );

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    printf("Example - SymLink_a\n\n");

    if (ARG_QTY > aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        fprintf(stderr, "Usage  SymLink_a {FileName}\n");
        return __LINE__;
    }

    if ( ! ValidateFileName( aVector[ ARG_FILE_NAME ] ) )
    {
        fprintf( stderr, "USER ERROR  Invalid file name\n" );
    }

    char lFileName[ 1024 ];

    memset( & lFileName, 0, sizeof( lFileName ) );

    strncpy( lFileName, aVector[ ARG_FILE_NAME ], sizeof( lFileName ) - 1 );

    for (;;)
    {
        struct stat lStat;

        int lRet = lstat( lFileName, & lStat );
        if ( 0 != lRet )
        {
            fprintf(stderr, "USER ERROR  lstat( ,  )  failed - %d\n", lRet );
            return __LINE__;
        }

        if ( ! S_ISLNK( lStat.st_mode ) )
        {
            break;
        }

        printf( " ==> " );

        size_t lSize_byte = readlink( lFileName, lFileName, sizeof( lFileName ) - 1 );
        if ( ( 0 >= lSize_byte ) || ( sizeof( lFileName ) <= lSize_byte ) )
        {
            fprintf( stderr, "ERROR  readlink( , ,  )  failed - %ld\n", lSize_byte );
            return __LINE__;
        }

        if ( ! ValidateFileName( lFileName ) )
        {
            fprintf( stderr, "USER ERROR  Invalid link destination\n" );
            return __LINE__;
        }
    }

    return 0;
}

// Static function
/////////////////////////////////////////////////////////////////////////////

bool ValidateFileName( const char * aFileName )
{
    assert( NULL != aFileName );

    printf( "%s\n", aFileName );

    return true;
}
