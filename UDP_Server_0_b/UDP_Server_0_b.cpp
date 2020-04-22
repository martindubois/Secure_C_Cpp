
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         03 - Interacting with the world
// Video          08 - Network address validation
// Example        UDP_Server_0_b
// File           UDP_Server_0_b/UDP_Server_0_b.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== C++ ================================================================
#include <list>

// ===== Common =============================================================
#include "../Common/Protocol.h"
#include "../Common/Socket.h"

// Data types
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    unsigned int mAddress;
    unsigned int mMask   ;
}
AddressListEntry;

typedef std::list<AddressListEntry> AddressList;

// Static function declaration
/////////////////////////////////////////////////////////////////////////////

static void InitWhiteList();

static int ProcessRequest          (SOCKET aSocket, Protocol_Header* aHeader, unsigned int aSize_byte, const sockaddr_in& aFrom);
static int ReceiveAndProcessRequest(SOCKET aSocket);

static bool SearchInAddressList(const AddressList& aList, const sockaddr_in& aAddr);

static bool ValidateAddress(const sockaddr_in    & aAddr  , socklen_t    aAddrSize_byte);
static bool ValidateHeader (const Protocol_Header& aHeader, unsigned int aSize_byte    );

// Static variables
/////////////////////////////////////////////////////////////////////////////

static AddressList sWhiteList;

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Example - UDP_Server_0_b\n\n");

    InitWhiteList();

    Socket_Startup();

    SOCKET lSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    sockaddr_in lAddr;

    memset(&lAddr, 0, sizeof(lAddr));

    lAddr.sin_addr.s_addr = INADDR_ANY;
    lAddr.sin_family      = AF_INET   ;

    int lResult = bind(lSocket, reinterpret_cast<sockaddr*>(&lAddr), sizeof(lAddr));
    if (0 == lResult)
    {
        socklen_t lAddrSize_byte = sizeof(lAddr);

        getsockname(lSocket, reinterpret_cast<sockaddr*>(&lAddr), &lAddrSize_byte);

        printf("The server listen on port %u\n", ntohs(lAddr.sin_port));

        do
        {
            lResult = ReceiveAndProcessRequest(lSocket);
        }
        while (0 == lResult);

        Socket_Close(lSocket);
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

void InitWhiteList()
{
    AddressListEntry lEntry;
    int              lRet;

    lRet = inet_pton(AF_INET, "127.0.0.1"      , &lEntry.mAddress); assert(1 == lRet);
    lRet = inet_pton(AF_INET, "255.255.255.255", &lEntry.mMask   ); assert(1 == lRet);
    sWhiteList.push_back(lEntry);

    lRet = inet_pton(AF_INET, "192.168.0.0"  , &lEntry.mAddress); assert(1 == lRet);
    lRet = inet_pton(AF_INET, "255.255.255.0", &lEntry.mMask   ); assert(1 == lRet);
    sWhiteList.push_back(lEntry);
}

int ProcessRequest(SOCKET aSocket, Protocol_Header* aHeader, unsigned int aSize_byte, const sockaddr_in& aFrom)
{
    assert(NULL !=   aHeader   );
    assert(   0 <    aSize_byte);
    assert(NULL != (&aFrom)    );

    if (ValidateHeader(*aHeader, aSize_byte))
    {
        switch (aHeader->mRequestCode)
        {
        case PROTOCOL_REQUEST_DO_NOTHING: aHeader->mResultCode = PROTOCOL_RESULT_OK; break;

        default: aHeader->mResultCode = PROTOCOL_RESULT_INVALID_REQUEST_CODE; break;
        }

        sendto(aSocket, reinterpret_cast<char*>(aHeader), aHeader->mSize_byte, 0, reinterpret_cast<const sockaddr*>(&aFrom), sizeof(aFrom));
    }

    return 0;
}

int ReceiveAndProcessRequest(SOCKET aSocket)
{
    sockaddr_in      lAddr;
    socklen_t        lAddrSize_byte = sizeof(lAddr);
    char             lBuffer[1024];
    Protocol_Header* lHeader = reinterpret_cast<Protocol_Header*>(lBuffer);

    int lSize_byte = recvfrom(aSocket, lBuffer, sizeof(lBuffer), 0, reinterpret_cast<sockaddr*>(&lAddr), &lAddrSize_byte);
    if ((0 >= lSize_byte) || (sizeof(lBuffer) < lSize_byte))
    {
        fprintf(stderr, "ERROR  recvfrom( , , , , ,  )  failed - %d\n", lSize_byte);
        return __LINE__;
    }

    if (!ValidateAddress(lAddr, lAddrSize_byte))
    {
        fprintf(stderr, "ERROR  ValidateAddress( ,  )  failed\n");
        return 0;
    }

    return ProcessRequest(aSocket, lHeader, lSize_byte, lAddr);
}

bool SearchInAddressList(const AddressList& aList, const sockaddr_in& aAddr)
{
    assert(NULL != (&aList));
    assert(NULL != (&aAddr));

    for (AddressList::const_iterator lIt = aList.begin(); lIt != aList.end(); lIt++)
    {
        if (lIt->mAddress == (lIt->mMask & aAddr.sin_addr.S_un.S_addr))
        {
            return true;
        }
    }

    return false;
}

bool ValidateAddress(const sockaddr_in& aAddr, socklen_t aAddrSize_byte)
{
    assert(NULL          != (&aAddr)        );
    assert(sizeof(aAddr) ==   aAddrSize_byte);

    return SearchInAddressList(sWhiteList, aAddr);
}

bool ValidateHeader(const Protocol_Header& aHeader, unsigned int aSize_byte)
{
    assert(NULL != (&aHeader));

    if (PROTOCOL_RESULT_REQUEST != aHeader.mResultCode)
    {
        fprintf(stderr, "REQUEST ERROR  Invalid result\n");
        return false;
    }

    if (sizeof(Protocol_Header) > aHeader.mSize_byte)
    {
        fprintf(stderr, "REQUEST ERROR  Invalid size\n");
        return false;
    }

    if (aHeader.mSize_byte != aSize_byte)
    {
        fprintf(stderr, "REQUEST ERROR  Wrong size\n");
        return false;
    }

    return true;
}
