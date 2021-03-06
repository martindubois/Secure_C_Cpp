
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           Common/WindowsOnLinux.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <signal.h>

// Constnts
/////////////////////////////////////////////////////////////////////////////

#define INVALID_HANDLE_VALUE     (-1)
#define INVALID_SET_FILE_POINTER (-1)
#define INVALID_SOCKET           (-1)

// Data type
/////////////////////////////////////////////////////////////////////////////

typedef int HANDLE;
typedef int SOCKET;

typedef int errno_t;

typedef sighandler_t _crt_signal_t;

typedef unsigned int DWORD;

// Macros
/////////////////////////////////////////////////////////////////////////////

#define SIZE_INFO(S)

// Function names
/////////////////////////////////////////////////////////////////////////////

#define _strdup strdup

#define fscanf_s fscanf

#define sscanf_s sscanf

#define strcat_s  strcat
#define strcpy_s  strcpy
#define strncpy_s strncpy

// Functions
/////////////////////////////////////////////////////////////////////////////

#define fopen_s(F,N,M) ( ( NULL != ( ( * (F) ) = fopen( (N), (M) ) ) ) ? 0 : -1 )
