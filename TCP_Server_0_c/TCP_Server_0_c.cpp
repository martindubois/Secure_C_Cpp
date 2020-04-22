
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         03 - Interacting with the world
// Video          08 - Network address validation
// Example        TCP_Server_0_c
// File           TCP_Server_0_c/TCP_Server_0_c.cpp

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
    unsigned int mMask;
}
AddressListEntry;

typedef std::list<AddressListEntry> AddressList;

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void InitBlackList();

static int ProcessRequest(SOCKET aSocket, const Protocol_Header& aHeader, const char* aData);
static int ReceiveAndProcessRequest(SOCKET aSocket);

static bool SearchInAddressList(const AddressList& aList, const sockaddr_in& aAddr);

static bool ValidateAddress(const sockaddr_in& aAddr, socklen_t    aAddrSize_byte);
static bool ValidateHeader (const Protocol_Header& aHeader);

// Static variables
/////////////////////////////////////////////////////////////////////////////

static AddressList sBlackList;

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Example - TCP_Server_0_c\n\n");

    InitBlackList();

    Socket_Startup();

    SOCKET lSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    assert(INVALID_SOCKET != lSocket);

    sockaddr_in lAddr;

    memset(&lAddr, 0, sizeof(lAddr));

    lAddr.sin_addr.s_addr = INADDR_ANY;
    lAddr.sin_family = AF_INET;

    int lResult = bind(lSocket, reinterpret_cast<sockaddr*>(&lAddr), sizeof(lAddr));
    if (0 == lResult)
    {
        lResult = listen(lSocket, 1);
        if (0 == lResult)
        {
            socklen_t lAddrSize_byte = sizeof(lAddr);

            getsockname(lSocket, reinterpret_cast<sockaddr*>(&lAddr), &lAddrSize_byte);

            printf("The server listen on port %u\n", ntohs(lAddr.sin_port));

            do
            {
                lResult = ReceiveAndProcessRequest(lSocket);
            } while (0 == lResult);
        }
        else
        {
            fprintf(stderr, "ERROR  listen( ,  )  failed - %d\n", lResult);
            lResult = __LINE__;
        }
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

// Static functions
/////////////////////////////////////////////////////////////////////////////

void InitBlackList()
{
    AddressListEntry lEntry;
    int              lRet;

    lRet = inet_pton(AF_INET, "127.0.0.1", &lEntry.mAddress); assert(1 == lRet);
    lRet = inet_pton(AF_INET, "255.255.255.255", &lEntry.mMask); assert(1 == lRet);
    sBlackList.push_back(lEntry);
}

int ProcessRequest(SOCKET aSocket, const Protocol_Header& aHeader, const char* aData)
{
    assert(INVALID_SOCKET != aSocket);
    assert(NULL != (&aHeader));

    Protocol_Header lHeader = aHeader;

    switch (aHeader.mRequestCode)
    {
    case PROTOCOL_REQUEST_DO_NOTHING: lHeader.mResultCode = PROTOCOL_RESULT_OK; break;

    default: lHeader.mResultCode = PROTOCOL_RESULT_INVALID_REQUEST_CODE; break;
    }

    send(aSocket, reinterpret_cast<char*>(&lHeader), sizeof(lHeader), 0);

    if (NULL != aData)
    {
        unsigned int lDataSize_byte = aHeader.mSize_byte - sizeof(Protocol_Header);

        send(aSocket, aData, lDataSize_byte, 0);
    }

    return 0;
}

int ReceiveAndProcessRequest(SOCKET aSocket)
{
    assert(INVALID_SOCKET != aSocket);

    sockaddr_in lAddr;
    socklen_t   lAddrSize_byte = sizeof(lAddr);

    SOCKET lSocket = accept(aSocket, reinterpret_cast<sockaddr*>(&lAddr), &lAddrSize_byte);
    if (INVALID_SOCKET == lSocket)
    {
        fprintf(stderr, "ERROR  accept( , ,  )  failed\n");
        return __LINE__;
    }

    int lResult = 0;

    if (ValidateAddress(lAddr, lAddrSize_byte))
    {
        int lTimeout_ms = 1000;

        int lRet = setsockopt(lSocket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&lTimeout_ms), sizeof(lTimeout_ms));
        assert(0 == lRet);

        Protocol_Header lHeader;

        int lSize_byte = recv(lSocket, reinterpret_cast<char*>(&lHeader), sizeof(lHeader), 0);
        if (sizeof(lHeader) == lSize_byte)
        {
            if (ValidateHeader(lHeader))
            {
                char* lData = NULL;
                unsigned int lDataSize_byte = lHeader.mSize_byte - sizeof(Protocol_Header);

                if (0 < lDataSize_byte)
                {
                    lData = new char[lDataSize_byte];
                    assert(NULL != lData);

                    lSize_byte = recv(lSocket, lData, lDataSize_byte, 0);
                    if (lDataSize_byte != lSize_byte)
                    {
                        fprintf(stderr, "REQUEST ERROR  Not enough data - %d bytes\n", lSize_byte);
                    }
                }
                else
                {
                    lSize_byte = 0;
                }

                if (lDataSize_byte == lSize_byte)
                {
                    lResult = ProcessRequest(lSocket, lHeader, lData);
                }
            }
        }
        else
        {
            fprintf(stderr, "REQUEST ERROR  Invalid request - %d bytes\n", lSize_byte);
        }
    }
    else
    {
        fprintf(stderr, "CONNEXION ERROR  Invalid address\n");
    }

    Socket_Close(lSocket);

    return lResult;
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

    return ( ! SearchInAddressList(sBlackList, aAddr) );
}

bool ValidateHeader(const Protocol_Header& aHeader)
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

    return true;
}
