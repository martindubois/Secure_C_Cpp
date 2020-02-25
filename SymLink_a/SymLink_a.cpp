
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

#ifdef _WIN32

    // ===== Windows ========================================================
    #include <Windows.h>

#else

    #include <unistd.h>

    // ===== System =========================================================
    #include <sys/stat.h>

#endif

// Data type
/////////////////////////////////////////////////////////////////////////////

typedef enum
{
    FOLLOW_LINK      ,
    FOLLOW_NOT_A_LINK,

    FOLLOW_ERROR,

    FOLLOW_QTY
}
FollowResult;

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_FILE_NAME (1)

#define ARG_QTY (2)

// Static fonction declaration
/////////////////////////////////////////////////////////////////////////////

static FollowResult FollowLink(char* aFileName, unsigned int aSize_byte);

#ifdef _WIN32
    bool RetrieveLinkDestination(char* aOut, unsigned int aOutSize_byte, HANDLE aFile);
#else
    bool RetrieveLinkDestination(char* aOut, unsigned int aOutSize_byte, const char* aIn);
#endif

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

    printf("\n");

    if ( ! ValidateFileName( aVector[ ARG_FILE_NAME ] ) )
    {
        fprintf( stderr, "USER ERROR  Invalid file name\n" );
        return __LINE__;
    }

    char lFileName[ 1024 ];

    memset( & lFileName, 0, sizeof( lFileName ) );

    strncpy_s( lFileName, aVector[ ARG_FILE_NAME ], sizeof( lFileName ) - 1 );

    FollowResult lFR;

    while (FOLLOW_LINK == ( lFR = FollowLink(lFileName, sizeof(lFileName))))
    {
        printf(" ==> ");

        if ( ! ValidateFileName( lFileName ) )
        {
            fprintf( stderr, "USER ERROR  Invalid link destination\n" );
            return __LINE__;
        }
    }

    switch (lFR)
    {
    case FOLLOW_ERROR:
        fprintf(stderr, "ERROR  FollowLink( ,  )  failed\n");
        return __LINE__;

    case FOLLOW_NOT_A_LINK :
        printf("\nThe real input file is %s\n", lFileName);
        break;

    default: assert(false);
    }

    return 0;
}

// Static function
/////////////////////////////////////////////////////////////////////////////

FollowResult FollowLink(char* aFileName, unsigned int aSize_byte)
{
    assert(NULL != aFileName );
    assert(   0 <  aSize_byte);

    bool lRetB;

    #ifdef _WIN32

        HANDLE lFile = CreateFileA(aFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_OPEN_REPARSE_POINT, NULL);
        if (INVALID_HANDLE_VALUE == lFile)
        {
            fprintf(stderr, "ERROR  CreateFileA( , , , , , ,  )  failed\n");
            return FOLLOW_ERROR;
        }

        BY_HANDLE_FILE_INFORMATION lInfo;

        if (!GetFileInformationByHandle(lFile, &lInfo))
        {
            fprintf(stderr, "ERROR  GetFileInformationByHandle( ,  )  failed\n");
            CloseHandle(lFile);
            return FOLLOW_ERROR;
        }

        if (0 == (lInfo.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
        {
            CloseHandle(lFile);
            return FOLLOW_NOT_A_LINK;
        }

        lRetB = RetrieveLinkDestination(aFileName, aSize_byte, lFile);

        CloseHandle(lFile);

    #else

        struct stat lStat;

        int lRet = lstat( aFileName, & lStat );
        if (0 != lRet)
        {
            fprintf(stderr, "ERROR  lstat( ,  )  failed - %d\n", lRet);
            return FOLLOW_ERROR;
        }

        if (!S_ISLNK(lStat.st_mode))
        {
            return FOLLOW_NOT_A_LINK;
        }

        lRetB = RetrieveLinkDestination(aFileName, aSize_byte, aFileName);

    #endif

    return lRetB ? FOLLOW_LINK : FOLLOW_ERROR;
}

#ifdef _WIN32

    typedef struct
    {
        ULONG  mTag      ;
        USHORT mSize_byte;
        USHORT mReserved0;

        // Symbolic link
        USHORT mSubstNameOffset_byte;
        USHORT mSubstNameLength_byte;
        USHORT mPrintNameOffset_byte;
        USHORT mPrintNameLength_byte;
        ULONG  mFlags;
        WCHAR  mData[1];
    }
    ReparseInfo;

    bool RetrieveLinkDestination(char* aOut, unsigned int aOutSize_byte, HANDLE aFile)
    {
        assert(NULL                 != aOut         );
        assert(                   0 <  aOutSize_byte);
        assert(INVALID_HANDLE_VALUE != aFile        );

        DWORD         lSize_byte;
        unsigned char lOutput[2048];

        if (!DeviceIoControl(aFile, FSCTL_GET_REPARSE_POINT, NULL, 0, lOutput, sizeof(lOutput), &lSize_byte, NULL))
        {
            fprintf(stderr, "ERROR  DeviceIoControl( , , , , , ,  )  failed");
            return false;
        }

        assert(sizeof(ReparseInfo) <= lSize_byte);
        assert(sizeof(lOutput    ) >= lSize_byte);

        ReparseInfo* lRI = reinterpret_cast<ReparseInfo*>(lOutput);

        unsigned int lCount = lRI->mPrintNameLength_byte / sizeof(WCHAR);
        unsigned int lStart = lRI->mPrintNameOffset_byte / sizeof(WCHAR);

        if (aOutSize_byte < lCount)
        {
            lCount = aOutSize_byte - 1;
        }

        for (unsigned int i = 0; i < lCount; i++)
        {
            aOut[i] = static_cast< char >( lRI->mData[lStart + i] );
        }

        aOut[lCount] = '\0';

        return true;
    }

#else

    bool RetrieveLinkDestination( char * aOut, unsigned int aOutSize_byte, const char * aIn )
    {
        assert(NULL != aOut         );
        assert(   0 <  aOutSize_byte);
        assert(NULL != aIn          );

        size_t lSize_byte = readlink(aIn, aOut, aOutSize_byte - 1);
        if ((0 >= lSize_byte) || (aOutSize_byte <= lSize_byte))
        {
            fprintf(stderr, "ERROR  readlink( , ,  )  failed - %ld\n", lSize_byte);
            return false;
        }

        return true;
    }

#endif

bool ValidateFileName( const char * aFileName )
{
    assert( NULL != aFileName );

    printf( "%s\n", aFileName );

    return true;
}
