
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           BaseLib/Socket.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// ===== Common =============================================================
#include "../Common/Socket.h"

// Functions
/////////////////////////////////////////////////////////////////////////////

void Socket_Close(SOCKET aSocket)
{
    int lRet = closesocket(aSocket);
    if (0 != lRet)
    {
        fprintf(stderr, "WARNING  closesocket(  )  failed - %d\n", lRet);
    }
}

void Socket_Startup()
{
    WSADATA lWS;

    int lRet = WSAStartup(MAKEWORD(2, 2), &lWS);
    if (0 != lRet)
    {
        fprintf(stderr, "FATAL ERROR  WSAStartup( ,  )  failed - %d\n", lRet);
        exit(__LINE__);
    }
}

void Socket_Cleanup()
{
    int lRet = WSACleanup();
    if (0 != lRet)
    {
        fprintf(stderr, "WARNING  WSACleanup()  failed - %d\n", lRet);
    }
}
