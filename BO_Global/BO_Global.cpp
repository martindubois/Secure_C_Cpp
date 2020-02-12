
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         02 - C/C++ particularities
// Video          05 - Buffer overflow
// Example        BO_Global
// File           BO_Global/BO_Global.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

// ===== Common =============================================================
#include "../Common/Dump.h"
#include "../Common/Verify.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_OFFSET (1)

#define BUFFER_SIZE_byte (10)

// Static variables
/////////////////////////////////////////////////////////////////////////////

static char sA[BUFFER_SIZE_byte];
static char sB[BUFFER_SIZE_byte];
static char sC[BUFFER_SIZE_byte];

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    printf("Example - BO_Global\n\n");

	memset(sA, 'A', BUFFER_SIZE_byte);
	memset(sB, 'B', BUFFER_SIZE_byte);
	memset(sC, 'C', BUFFER_SIZE_byte);

	if (ARG_OFFSET < aCount)
	{
		sB[atoi(aVector[ARG_OFFSET])] = 'D';
	}

	Dump(sB - (BUFFER_SIZE_byte * 12), BUFFER_SIZE_byte * 25, BUFFER_SIZE_byte, -(BUFFER_SIZE_byte * 12));

	Verify(sA, BUFFER_SIZE_byte, 'A');
	Verify(sB, BUFFER_SIZE_byte, 'B');
	Verify(sC, BUFFER_SIZE_byte, 'C');

	return 0;
}
