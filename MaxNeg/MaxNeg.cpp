
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         02 - C++ particularities
// Video          02 - Integer manipulation
// Example        Integer_Size
// File           Integer_Size/Integer_Size.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <memory.h>
#include <stdint.h>
#include <stdio.h>

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
	printf("Example - MaxNeg\n\n");

	char   lData[12];
	int8_t lSize_byte;

	memset(&lData, 0, sizeof(lData));

	// fread(lSize_byte, 1, sizeof(lSize_byte), lFile);
	lSize_byte = -128;

	if (0 > lSize_byte)
	{
		lSize_byte = -lSize_byte;
	}

	if (12 < lSize_byte)
	{
		lSize_byte = sizeof(lData);
	}

	// fwrite(lData, 1, lSize_byte, lFile);

	printf("We wrote %u bytes\n", (size_t)(lSize_byte));
}
