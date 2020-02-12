
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         04 - Error handling
// Video          04 - Signal
// Example        Signal
// File           Signal/Signal.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== Common =============================================================
#include "../Common/Protocol.h"
#include "../Common/Socket.h"

#ifndef _WIN32
    #include "../Common/WindowsOnLinux.h"
#endif

// Static variables
/////////////////////////////////////////////////////////////////////////////

static SOCKET sSocket = INVALID_SOCKET;
static bool   sStop   = false;

// Static function declaration
/////////////////////////////////////////////////////////////////////////////

static int ProcessRequest          (SOCKET aSocket, Protocol_Header* aHeader, const sockaddr_in& aFrom);
static int ReceiveAndProcessRequest(SOCKET aSocket);

static void SignalHandler(int aSignal);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Example - Signal_0_Safe\n\n");

    Socket_Startup();

    _crt_signal_t lRegSig;

    lRegSig = signal(SIGABRT, SignalHandler);
    lRegSig = signal(SIGFPE , SignalHandler);
    lRegSig = signal(SIGILL , SignalHandler);
    lRegSig = signal(SIGINT , SignalHandler);
    lRegSig = signal(SIGSEGV, SignalHandler);
    lRegSig = signal(SIGTERM, SignalHandler);

    sSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    assert(INVALID_SOCKET != sSocket);

    sockaddr_in lAddr;

    memset(&lAddr, 0, sizeof(lAddr));

    lAddr.sin_addr.s_addr = INADDR_ANY;
    lAddr.sin_family = AF_INET;

    int lResult = bind(sSocket, reinterpret_cast<sockaddr*>(&lAddr), sizeof(lAddr));
    if (0 == lResult)
    {
        socklen_t lAddrSize_byte = sizeof(lAddr);

        getsockname(sSocket, reinterpret_cast<sockaddr*>(&lAddr), &lAddrSize_byte);

        printf("The server listen on port %u\n", ntohs(lAddr.sin_port));

        do
        {
            lResult = ReceiveAndProcessRequest(sSocket);
        }
        while ((0 == lResult) && (!sStop));

        if (!sStop)
        {
            Socket_Close(sSocket);
        }
    }
    else
    {
        fprintf(stderr, "ERROR  bind( , ,  )  failed - %d\n", lResult);
    }

    Socket_Cleanup();

    return lResult;
}

// Static function
/////////////////////////////////////////////////////////////////////////////

int ProcessRequest(SOCKET aSocket, Protocol_Header* aHeader, unsigned int aSize_byte, const sockaddr_in& aFrom)
{
    assert(NULL !=   aHeader   );
    assert(0    <    aSize_byte);
    assert(NULL != (&aFrom)    );

    if (sizeof(Protocol_Header) > aSize_byte)
    {
        fprintf(stderr, "REQUEST ERROR  Too short\n");
        return 0;
    }

    if (aSize_byte != aHeader->mSize_byte)
    {
        fprintf(stderr, "REQUEST ERROR  Invalid size information\n");
        return 0;
    }

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

    int lSize_byte = recvfrom(aSocket, lBuffer, sizeof(lBuffer), 0, reinterpret_cast<sockaddr*>(&lAddr), &lAddrSize_byte);
    if (sStop)
    {
        return 0;
    }
    if ((0 >= lSize_byte) || (sizeof(lBuffer) < lSize_byte))
    {
        fprintf(stderr, "ERROR  recvfrom( , , , , ,  )  failed - %d\n", lSize_byte);
        return __LINE__;
    }

    return ProcessRequest(aSocket, lHeader, lSize_byte, lAddr);
}

void SignalHandler(int aSignal)
{
    switch (aSignal)
    {
    case SIGABRT: fprintf(stderr, "SIGNAL  SIGABRT\n"); exit(__LINE__);
    case SIGFPE : fprintf(stderr, "SIGNAL  SIGFPE\n" ); exit(__LINE__);
    case SIGILL : fprintf(stderr, "SIGNAL  SIGILL\n" ); exit(__LINE__);
    case SIGINT : printf("SIGNAL  SIGINT\n" ); break;
    case SIGSEGV: fprintf(stderr, "SIGNAL  SIGEGV\n" ); exit(__LINE__);
    case SIGTERM: printf("SIGNAL  SIGTERM\n"); break;

    default: fprintf(stderr, "SIGNAL  Unknown\n"); exit(__LINE__);
    }

    sStop = true;

    Socket_Close(sSocket);
}
