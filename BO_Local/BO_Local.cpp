
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         02 - C/C++ particularities
// Video          05 - Buffer overflow
// Example        BO_Local
// File           BO_Local/BO_Local.cpp

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

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void OtherFunction();

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
	printf("Example - BO_Local\n\n");

	char lA[BUFFER_SIZE_byte];
	char lB[BUFFER_SIZE_byte];
	char lC[BUFFER_SIZE_byte];

	memset(lA, 'A', BUFFER_SIZE_byte);
	memset(lB, 'B', BUFFER_SIZE_byte);
	memset(lC, 'C', BUFFER_SIZE_byte);

	if (ARG_OFFSET < aCount)
	{
		* reinterpret_cast<void **>(lB + atoi(aVector[ARG_OFFSET])) = OtherFunction;
	}

	Dump(lB - (BUFFER_SIZE_byte * 12), BUFFER_SIZE_byte * 25, BUFFER_SIZE_byte, -(BUFFER_SIZE_byte * 12));

	Verify(lA, BUFFER_SIZE_byte, 'A');
	Verify(lB, BUFFER_SIZE_byte, 'B');
	Verify(lC, BUFFER_SIZE_byte, 'C');

	return 0;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void OtherFunction()
{
	printf("Executing OtherFunction!\n");
	exit(0);
}
