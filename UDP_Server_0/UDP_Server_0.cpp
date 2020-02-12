
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         02 - C++ particularities
// Video          03 - Local variables
// Example        UDP_Server_0
// File           UDP_Server_0/UDP_Server_0.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <string.h>

// ===== Common =============================================================
#include "../Common/Protocol.h"
#include "../Common/Socket.h"

// Static function declaration
/////////////////////////////////////////////////////////////////////////////

static int ProcessRequest          (SOCKET aSocket, Protocol_Header* aHeader, const sockaddr_in& aFrom);
static int ReceiveAndProcessRequest(SOCKET aSocket);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Example - UDP_Server_0\n\n");

    Socket_Startup();

    SOCKET lSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    assert(INVALID_SOCKET != lSocket);

    sockaddr_in lAddr;

    memset(&lAddr, 0, sizeof(lAddr));

    lAddr.sin_addr.s_addr = INADDR_ANY;
    lAddr.sin_family      = AF_INET   ;

    int lResult = bind(lSocket, reinterpret_cast<sockaddr *>(&lAddr), sizeof(lAddr));
    if (0 == lResult)
    {
        socklen_t lAddrSize_byte = sizeof(lAddr);

        getsockname(lSocket, reinterpret_cast<sockaddr*>(&lAddr), &lAddrSize_byte);

        printf("The server listen on port %u\n", ntohs(lAddr.sin_port));

        do
        {
            lResult = ReceiveAndProcessRequest(lSocket);
        }
        while( 0 == lResult);
    }
    else
    {
        fprintf(stderr, "ERROR  bind( , ,  )  failed - %d\n", lResult);
        lResult = __LINE__;
    }

    Socket_Close(lSocket);

    Socket_Cleanup();

    return lResult;
}

// Static function
/////////////////////////////////////////////////////////////////////////////

int ProcessRequest(SOCKET aSocket, Protocol_Header* aHeader, const sockaddr_in& aFrom)
{
    switch (aHeader->mRequestCode)
    {
    case PROTOCOL_REQUEST_DO_NOTHING: aHeader->mResultCode = PROTOCOL_RESULT_OK; break;

    default: aHeader->mResultCode = PROTOCOL_RESULT_INVALID_REQUEST_CODE; break;
    }

    sendto(aSocket, reinterpret_cast<char*>(aHeader), aHeader->mSize_byte, 0, reinterpret_cast<const sockaddr*>(&aFrom), sizeof(aFrom));

    return 0;
}

int ReceiveAndProcessRequest(SOCKET aSocket)
{
    sockaddr_in      lAddr;
    socklen_t        lAddrSize_byte = sizeof(lAddr);
    char             lBuffer[1024];
    Protocol_Header* lHeader = reinterpret_cast<Protocol_Header*>(lBuffer);

    recvfrom(aSocket, lBuffer, sizeof(lBuffer), 0, reinterpret_cast<sockaddr *>(&lAddr), &lAddrSize_byte);

    return ProcessRequest(aSocket, lHeader, lAddr);
}
