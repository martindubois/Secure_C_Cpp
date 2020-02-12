
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         02 - C/C++ particularities
// Video          05 - Buffer overflow
// Example        BO_Dynamic
// File           BO_Dynamic/BO_Dynamic.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>

// ===== Includes ===========================================================
#include "../Common/Dump.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_OFFSET (1)

#define BUFFER_QTY       ( 3)
#define BUFFER_SIZE_byte (10)

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
	printf("Example - BO_Dynamic\n\n");

	char* lPointers[3];

	unsigned int i;

	for (i = 0; i < BUFFER_QTY; i++)
	{
		lPointers[i] = reinterpret_cast<char*>(malloc(BUFFER_SIZE_byte));
		assert(NULL != lPointers[i]);

		memset(lPointers[i], 'A' + i, BUFFER_SIZE_byte);
	}

	if (ARG_OFFSET < aCount)
	{
		lPointers[1][atoi(aVector[ARG_OFFSET])] = 'D';
	}

	Dump(lPointers[1] - (BUFFER_SIZE_byte * 12), BUFFER_SIZE_byte * 25, BUFFER_SIZE_byte, -(BUFFER_SIZE_byte * 12));

	for (i = 0; i < BUFFER_QTY; i++)
	{
		free(lPointers[i]);
	}

	return 0;
}
