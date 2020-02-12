
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           BaseLib/Socket.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>
#include <unistd.h>

// ===== Common =============================================================
#include "../Common/Socket.h"

// Functions
/////////////////////////////////////////////////////////////////////////////

void Socket_Close(SOCKET aSocket)
{
    int lRet;

    #ifdef _WIN32
        lRet = closesocket(aSocket);
    #else
        lRet = close(aSocket);
    #endif

    if (0 != lRet)
    {
        fprintf(stderr, "WARNING  close(  )  or  closesocket(  )  failed - %d\n", lRet);
    }
}

void Socket_Startup()
{
    #ifdef _WIN32

        WSADATA lWS;

        int lRet = WSAStartup(MAKEWORD(2, 2), &lWS);
        if (0 != lRet)
        {
            fprintf(stderr, "FATAL ERROR  WSAStartup( ,  )  failed - %d\n", lRet);
            exit(__LINE__);
        }

    #endif
}

void Socket_Cleanup()
{
    #ifdef _WIN32

        int lRet = WSACleanup();
        if (0 != lRet)
        {
            fprintf(stderr, "WARNING  WSACleanup()  failed - %d\n", lRet);
        }

    #endif
}
