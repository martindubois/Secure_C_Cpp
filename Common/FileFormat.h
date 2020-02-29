
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           Common/FileFormat.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdint.h>

// Data type
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    uint32_t mId;

    char mAddress[58];

    uint16_t mPerioid_Min;
}
ClientInfo;
