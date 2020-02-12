
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           Common/Socket.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Windows ============================================================
#include <WinSock2.h>
#include <WS2tcpip.h>

// Functions
/////////////////////////////////////////////////////////////////////////////

extern void Socket_Close  (SOCKET aSocket);
extern void Socket_Startup();
extern void Socket_Cleanup();
