
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

// Data type
/////////////////////////////////////////////////////////////////////////////

//           +--> STOPPED <--+
//           |               |
//           |   +--> COMPLETING <--+
//           |   |                  |
// INIT --> WAITING <--+            |
//               |     |            |
//               +--> EXECUTING ----+
typedef enum
{
    STATE_INIT,

    STATE_ABORTING  ,
    STATE_COMPLETING,
    STATE_EXECUTING ,
    STATE_STOPPED   ,
    STATE_WAITING   ,
}
State;

// Static variables
/////////////////////////////////////////////////////////////////////////////

static volatile SOCKET sSocket = INVALID_SOCKET;
static volatile State  sState  = STATE_INIT;

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

        while ((0 == lResult) && ((STATE_INIT == sState) || (STATE_WAITING == sState)))
        {
            lResult = ReceiveAndProcessRequest(sSocket);
        }

        if (INVALID_SOCKET != sSocket)
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
    int              lSize_byte;

    // POSSIBLE RACE CONDITION  In a real program, we need to verify sState
    //                          and set it at the same time or while holding
    //                          a gate protecting the variable.
    switch (sState)
    {
    case STATE_INIT     :
    case STATE_EXECUTING:
        sState = STATE_WAITING; break;

    case STATE_STOPPED: return 0;

    default: assert(false);
    }

    lSize_byte = recvfrom(aSocket, lBuffer, sizeof(lBuffer), 0, reinterpret_cast<sockaddr*>(&lAddr), &lAddrSize_byte);

    // POSSIBLE RACE CONDITION  In a real program, we need to verify sState
    //                          and set it at the same time or while holding
    //                          a gate protecting the variable.
    switch(sState)
    {
    case STATE_STOPPED: return 0;

    case STATE_WAITING: sState = STATE_EXECUTING; break;

    default: assert(false);
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
    case SIGINT : printf("SIGNAL  SIGINT\n" ); break;
    case SIGTERM: printf("SIGNAL  SIGTERM\n"); break;

    case SIGABRT: fprintf(stderr, "SIGNAL  SIGABRT\n"); exit(__LINE__);
    case SIGFPE : fprintf(stderr, "SIGNAL  SIGFPE\n" ); exit(__LINE__);
    case SIGILL : fprintf(stderr, "SIGNAL  SIGILL\n" ); exit(__LINE__);
    case SIGSEGV: fprintf(stderr, "SIGNAL  SIGEGV\n" ); exit(__LINE__);

    default: fprintf(stderr, "SIGNAL  Unknown\n"); exit(__LINE__);
    }

    // POSSIBLE RACE CONTITION  In a real program, we need to verify sState
    //                          and set it at the same time or while holding
    //                          a gate protecting both variables.
    switch (sState)
    {
    case STATE_EXECUTING: sState = STATE_COMPLETING; break;

    case STATE_INIT: sState = STATE_STOPPED; break;

    case STATE_WAITING: sState = STATE_STOPPED; Socket_Close(sSocket); sSocket = INVALID_SOCKET; break;

    default: assert(false);
    }
}
