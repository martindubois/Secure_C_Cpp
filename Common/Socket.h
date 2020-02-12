
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           Common/Socket.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32

    // ===== Windows ========================================================
    #include <WinSock2.h>
    #include <WS2tcpip.h>

    // ===== Common =========================================================
    #include "LinuxOnWindows.h"

#else

    // ===== System =========================================================
    #include <sys/socket.h>

    // ===== Network ========================================================
    #include <netinet/in.h>

    // ===== ARPA ===========================================================
    #include <arpa/inet.h>

    // ===== Common =========================================================
    #include "WindowsOnLinux.h"

#endif

// Functions
/////////////////////////////////////////////////////////////////////////////

extern void Socket_Close  (SOCKET aSocket);
extern void Socket_Startup();
extern void Socket_Cleanup();
