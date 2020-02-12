
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           Common/Protocol.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdint.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define PROTOCOL_REQUEST_DO_NOTHING (0)

#define PROTOCOL_RESULT_REQUEST (0xffff)

#define PROTOCOL_RESULT_OK (0)

#define PROTOCOL_RESULT_INVALID_REQUEST_CODE (100)

// Data type
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    uint16_t mRequestCode; // See PROTOCOL_REQUEST_...
    uint16_t mSerial     ;
    uint16_t mResultCode ; // See PROTOCOL_RESULT_...
    uint16_t mSize_byte  ; // Total size, including the header.
}
Protocol_Header;
