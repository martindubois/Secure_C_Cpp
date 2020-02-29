
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         03 - Interacting with the world
// Video          04 - Files
// Example        ClientList_0
// File           ClientList_0/ClientList_0.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32

    // ===== Windows ========================================================
    #include <Windows.h>

    // ===== Common =========================================================
    #include "../Common/LinuxOnWindows.h"

#else

    #include <fcntl.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>

    // ===== Common =========================================================
    #include "../Common/WindowsOnLinux.h"

#endif

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_CMD  (1)
#define ARG_ID   (2)
#define ARG_ADDR (3)
#define ARG_FREQ (4)

#define ARG_ADD_QTY    (5)
#define ARG_REMOVE_QTY (3)

#ifndef _WIN32
    #define FILE_CURRENT (SEEK_CUR)
    #define FILE_END     (SEEK_END)
#endif

#define RECORD_SIZE_byte (64)

// Static function declaration
/////////////////////////////////////////////////////////////////////////////

static void Add_Abort(HANDLE aHandle, unsigned int aOffset);

#ifndef _WIN32
    static bool     ReadFile      (int aHandle, void* aOut, unsigned int aOutSize_byte, unsigned int* aInfo_byte, void*);
    static uint32_t SetFilePointer(int aHandle, int aOffset, void*, int aMode);
    static bool     WriteFile     (int aHandle, const void* aIn, unsigned int aInSize_byte, unsigned int* aInfo_byte, void*);
#endif

// ===== Commands ===========================================================
static int Add   (HANDLE aHandle, int aCount, const char** aVector);
static int Remove(HANDLE aHandle, int aCount, const char** aVector);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    printf("Example - ClientList_0\n\n");

    if (ARG_CMD >= aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command\n");
        fprintf(stderr, "Usage  ClientList_0 ADD {Id} {Addr} {Freq}\n");
        fprintf(stderr, "                    REMOVE { Id }\n");
        return __LINE__;
    }

    HANDLE lHandle;

    #ifdef _WIN32
        lHandle = CreateFileA("Data.bin", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);
        if (INVALID_HANDLE_VALUE == lHandle)
        {
            fprintf(stderr, "ERROR  CreateFileA( , , , , , ,  )  failed\n");
            return __LINE__;
        }
    #else
        lHandle = open("Data.bin", O_RDWR | O_CREAT, 0600);
        if (0 > lHandle)
        {
            fprintf(stderr, "ERROR  open(  )  failed - %d\n", lHandle);
            return __LINE__;
        }
    #endif

    int lResult;

    if      (0 == strcmp("ADD"   , aVector[ARG_CMD])) { lResult = Add   (lHandle, aCount, aVector); }
    else if (0 == strcmp("REMOVE", aVector[ARG_CMD])) { lResult = Remove(lHandle, aCount, aVector); }
    else
    {
        fprintf(stderr, "USER ERROR  Invalid command\n");
        lResult = __LINE__;
    }

    #ifdef _WIN32
        CloseHandle(lHandle);
    #else
        close(lHandle);
    #endif

    return lResult;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void Add_Abort(HANDLE aHandle, unsigned int aOffset)
{
    assert(INVALID_HANDLE_VALUE != aHandle);

    #ifdef _WIN32

        DWORD lOffset = SetFilePointer(aHandle, aOffset, NULL, FILE_BEGIN);
        assert(aOffset == lOffset);

        BOOL lRetB = SetEndOfFile(aHandle);
        assert(lRetB);

    #else

        int lRet = ftruncate(aHandle, aOffset);
        assert(0 == lRet);

    #endif
}

#ifndef _WIN32

    // aOut       [---;-W-]
    // aInfo_byte [---;-W-]
    bool ReadFile(int aHandle, void* aOut, unsigned int aOutSize_byte, unsigned int* aInfo_byte, void*)
    {
        assert(INVALID_HANDLE_VALUE != aHandle      );
        assert(NULL                 != aOut         );
        assert(0                    <  aOutSize_byte);
        assert(NULL                 != aInfo_byte   );

        ssize_t lSize_byte = read(aHandle, aOut, aOutSize_byte);
        if (0 >= lSize_byte)
        {
            return false;
        }

        assert(aOutSize_byte >= lSize_byte);

        *aInfo_byte = lSize_byte;

        return true;
    }

    uint32_t SetFilePointer(int aHandle, int aOffset, void*, int aMode)
    {
        assert(INVALID_HANDLE_VALUE != aHandle);

        return lseek(aHandle, aOffset, aMode);
    }

    // aIn        [---;R--]
    // aInfo_byte [---;-W-]
    bool WriteFile(int aHandle, const void* aIn, unsigned int aInSize_byte, unsigned int* aInfo_byte, void*)
    {
        assert(INVALID_HANDLE_VALUE != aHandle     );
        assert(NULL                 != aIn         );
        assert(                   0 <  aInSize_byte);
        assert(NULL                 != aInfo_byte  );

        ssize_t lSize_byte = write(aHandle, aIn, aInSize_byte);
        if (0 >= lSize_byte)
        {
            return false;
        }

        assert(aInSize_byte >= lSize_byte);

        *aInfo_byte = lSize_byte;

        return true;
    }

#endif

// ===== Commands ===========================================================
// aVector [---;R--]

int Add(HANDLE aHandle, int aCount, const char** aVector)
{
    assert(INVALID_HANDLE_VALUE != aHandle);
    assert(ARG_CMD              <= aCount );
    assert(NULL                 != aVector);

    if (ARG_ADD_QTY != aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        fprintf(stderr, "Usage  ClientList_0 ADD {Id} {Addr} {Freq}\n");
        return __LINE__;
    }

    assert(NULL != aVector[ARG_ADDR]);
    assert(NULL != aVector[ARG_FREQ]);
    assert(NULL != aVector[ARG_ID  ]);

    uint32_t lFreq = strtoul(aVector[ARG_FREQ], NULL, 10);
    uint32_t lId   = strtoul(aVector[ARG_ID  ], NULL, 10);

    unsigned int lOffset = SetFilePointer(aHandle, 0, NULL, FILE_END);
    if (INVALID_SET_FILE_POINTER == lOffset)
    {
        fprintf(stderr, "ERROR  SetFilePointer( , , ,  )  failed\n");
        return __LINE__;
    }

    unsigned int lInfo_byte;

    if (!WriteFile(aHandle, &lId, sizeof(lId), &lInfo_byte, NULL))
    {
        fprintf(stderr, "ERROR  WriteFile( , , , ,  )  failed\n");
        return __LINE__;
    }
    assert(sizeof(lId) == lInfo_byte);

    char lAddr[58];

    memset(&lAddr, 0, sizeof(lAddr));

    strncpy_s(lAddr, aVector[ARG_ADDR], sizeof(lAddr) - 1);

    int lResult;

    if (WriteFile(aHandle, &lAddr, sizeof(lAddr), &lInfo_byte, NULL))
    {
        assert(sizeof(lAddr) == lInfo_byte);

        uint16_t lPeriod_min = 24 * 60 / lFreq;

        if (WriteFile(aHandle, &lPeriod_min, sizeof(lPeriod_min), &lInfo_byte, NULL))
        {
            assert(sizeof(lPeriod_min) == lInfo_byte);

            lResult = 0;
        }
        else
        {
            fprintf(stderr, "ERROR  WriteFile( , , , ,  )  failed\n");
            lResult = __LINE__;
        }
    }
    else
    {
        fprintf(stderr, "ERROR  WriteFile( , , , ,  )  failed");
        lResult = __LINE__;
    }

    if (0 != lResult)
    {
        Add_Abort(aHandle, lOffset);
    }

    return lResult;
}

int Remove(HANDLE aHandle, int aCount, const char** aVector)
{
    assert(INVALID_HANDLE_VALUE != aHandle);

    if (ARG_REMOVE_QTY != aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        fprintf(stderr, "Usage  ClientList_0 REMOVE {Id}\n");
        return __LINE__;
    }

    uint32_t lId = strtoul(aVector[ARG_ID], NULL, 10);

    for (;;)
    {
        uint32_t     lReadId;
        unsigned int lInfo_byte;

        if (!ReadFile(aHandle, &lReadId, sizeof(lReadId), &lInfo_byte, NULL))
        {
            fprintf(stderr, "ERROR  Id not found\n");
            return __LINE__;
        }

        if (lId == lReadId)
        {
            int lOffset = 0;

            lOffset -= sizeof(uint32_t);

            if (INVALID_SET_FILE_POINTER == SetFilePointer(aHandle, lOffset, NULL, FILE_CURRENT))
            {
                fprintf(stderr, "FATAL ERROR  SetFilePointer( , , ,  )  failed\n");
                return __LINE__;
            }

            uint32_t lWriteId = 0;

            if (!WriteFile(aHandle, &lWriteId, sizeof(lWriteId), &lInfo_byte, NULL))
            {
                fprintf(stderr, "FATAL ERROR  WriteFile( , , , ,  )  failed\n");
                return __LINE__;
            }

            break;
        }

        if (INVALID_SET_FILE_POINTER == SetFilePointer( aHandle, RECORD_SIZE_byte - sizeof(uint32_t), NULL, FILE_CURRENT))
        {
            fprintf(stderr, "FATAL ERROR  SetFilePointer( , , ,  )  failed\n");
            return __LINE__;
        }
    }

    return 0;
}
