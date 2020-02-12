
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           BaseLib/Verify.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Common =============================================================
#include "../Common/Dump.h"

#include "../Common/Verify.h"

// Functions
/////////////////////////////////////////////////////////////////////////////

void Verify(const char* aIn, unsigned int aInSize_byte, char aExpected)
{
	assert(NULL != aIn);

	for (unsigned int i = 0; i < aInSize_byte; i++)
	{
		if (aIn[i] != aExpected)
		{
			printf("Corrupted at index %u, expected (0x%02x) %c, read (0x%02x)", i, aExpected, aExpected, aIn[i]);
			Dump(aIn[i]);
			printf("\n");
		}
	}
}