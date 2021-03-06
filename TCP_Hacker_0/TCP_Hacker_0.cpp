
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         03 - C++ particularities
// Video          07 - Socket
// Example        TCP_Hacker_0
// File           TCP_Hacker_0/TCP_Hacker_0.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== Common =============================================================
#include "../Common/Dump.h"
#include "../Common/Socket.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_ADDRESS  (1)
#define ARG_PORT     (2)
#define ARG_REQUESTS (3)

#define ARG_QTY (4)

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void Request(const char* aIn, unsigned int aInSize_byte, const sockaddr_in& aAddr);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    printf("Example - TCP_Hacker_0\n\n");

    if (ARG_QTY > aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        fprintf(stderr, "Usage  TCP_Hacker_0 {IP_Addr} {Port} {Requests}\n");
        fprintf(stderr, "       N = No request\n");
        fprintf(stderr, "       S = Short request\n");
        fprintf(stderr, "       V = Valid request\n");
        return __LINE__;
    }

    Socket_Startup();

    sockaddr_in lAddr;

    memset(&lAddr, 0, sizeof(lAddr));

    int lRet = inet_pton(AF_INET, aVector[ARG_ADDRESS], &lAddr.sin_addr.s_addr);
    if (1 != lRet)
    {
        fprintf(stderr, "USER ERROR  inet_pton( , \"%s\",  )  failed - %d\n", aVector[1], lRet);
        return __LINE__;
    }

    lAddr.sin_family = AF_INET;
    lAddr.sin_port   = htons(static_cast<uint16_t>(strtoul(aVector[ARG_PORT], NULL, 10)));

    char             lBuffer[64];
    Protocol_Header* lHeader = reinterpret_cast<Protocol_Header*>(lBuffer);

    if (NULL != strchr(aVector[ARG_REQUESTS], 'V')) // V = Valid request
    {
        printf("Sending valid request...\n");

        memset(&lBuffer, 0, sizeof(lBuffer));

        lHeader->mRequestCode = PROTOCOL_REQUEST_DO_NOTHING;
        lHeader->mResultCode  = PROTOCOL_RESULT_REQUEST;
        lHeader->mSerial      = 1;
        lHeader->mSize_byte   = sizeof(lBuffer);

        strcpy_s(lBuffer + sizeof(Protocol_Header) SIZE_INFO( sizeof(lBuffer) - sizeof(Protocol_Header) ), "Very important data 0123456789abcdefghijklmnopqrstuvwxy");

        Request(lBuffer, sizeof(lBuffer), lAddr);
    }

    if (NULL != strchr(aVector[ARG_REQUESTS], 'S')) // S = Short request
    {
        printf("Sending short request...\n");

        memset(&lBuffer, 0, sizeof(lBuffer));

        lHeader->mRequestCode =  99;
        lHeader->mResultCode  = PROTOCOL_RESULT_REQUEST;
        lHeader->mSerial      =   1;
        lHeader->mSize_byte   = 128;

        Request(lBuffer, sizeof(Protocol_Header), lAddr);
    }

    if (NULL != strchr(aVector[ARG_REQUESTS], 'N')) // N = No request
    {
        printf("Connecting without sending request...\n");

        Request(NULL, 0, lAddr);
    }

    Socket_Cleanup();

    return 0;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void Request(const char* aIn, unsigned int aInSize_byte, const sockaddr_in& aAddr)
{
    assert(NULL != (&aAddr));

    SOCKET lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    assert(INVALID_SOCKET != lSocket);

    int lRet = connect(lSocket, reinterpret_cast<const sockaddr*>(&aAddr), sizeof(aAddr));
    if (0 != lRet)
    {
        fprintf(stderr, "ERROR  connect( , ,  )  failed - %d\n", lRet);
        return;
    }

    #ifdef _WIN32

        int lTimeout = 60000; // ms

    #else

        struct timeval lTimeout;

        memset(&lTimeout, 0, sizeof(lTimeout));

        lTimeout.tv_sec = 60;

    #endif

    lRet = setsockopt(lSocket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&lTimeout), sizeof(lTimeout));
    assert(0 == lRet);

    if (0 < aInSize_byte)
    {
        assert(NULL != aIn);

        lRet = send(lSocket, aIn, aInSize_byte, 0);
        printf("sendto returned %d\n", lRet);
    }

    char lBuffer[1024];

    lRet = recv(lSocket, lBuffer, sizeof(lBuffer), MSG_WAITALL);
    printf("recv returned %d\n", lRet);

    if (lRet >= sizeof(Protocol_Header))
    {
        Dump(*reinterpret_cast<Protocol_Header*>(lBuffer));
    }

    if (0 < lRet)
    {
        Dump(lBuffer, lRet);
    }

    Socket_Close(lSocket);
}
