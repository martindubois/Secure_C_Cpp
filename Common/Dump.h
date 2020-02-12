
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           Includes/Dump.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Common =============================================================
#include "../Common/Protocol.h"

// Functions
/////////////////////////////////////////////////////////////////////////////

extern void Dump(char aC);
extern void Dump(const void* aIn, unsigned int aInSize_byte);
extern void Dump(const void* aIn, unsigned int aInSize_byte, unsigned int aLineSize_byte, int aStartOffset);
extern void Dump(const Protocol_Header& aIn);
