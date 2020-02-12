
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// File           BaseLib/Dump.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Common =============================================================
#include "../Common/Dump.h"

// Functions
/////////////////////////////////////////////////////////////////////////////

void Dump(char aC)
{
	if ((' ' <= aC) && ('~' >= aC))
	{
		printf("%c", aC);
	}
	else
	{
		printf(".");
	}
}

void Dump(const void* aIn, unsigned int aInSize_byte)
{
	assert(NULL != aIn);

	const unsigned char* lIn = reinterpret_cast<const unsigned char*>(aIn);

	for (unsigned int i = 0; i < aInSize_byte; i += 16)
	{

		unsigned int lCount = aInSize_byte - i;

		if (16 < lCount)
		{
			lCount = 16;
		}

		unsigned int j;

		for (j = 0; j < 16; j++)
		{
			if (0 == (j % 4)) { printf(" "); }
			if (0 == (j % 8)) { printf(" "); }

			if (j < lCount) { printf(" %02x", lIn[i + j]); }
			else            { printf("   "); }
		}

		printf("    ");

		for (j = 0; j < lCount; j++)
		{
			if (0 == (j % 8)) { printf(" "); }

			Dump(lIn[i + j]);
		}

		printf("\n");
	}
}

void Dump(const void* aIn, unsigned int aInSize_byte, unsigned int aLineSize_byte, int aStartOffset)
{
	assert(NULL != aIn         );
	assert(   0 <  aInSize_byte);

	const char* lIn     = reinterpret_cast<const char*>(aIn);
	      int   lOffset = aStartOffset;

	for (unsigned int i = 0; i < aInSize_byte; i++)
	{
		if (0 == (i % aLineSize_byte))
		{
			printf("\n%5d ", lOffset);
		}

		printf(" ");

		Dump(lIn[i]);

		lOffset++;
	}

	printf("\n");
}

void Dump(const Protocol_Header& aIn)
{
	printf("Request code   : ");

	switch (aIn.mRequestCode)
	{
	case PROTOCOL_REQUEST_DO_NOTHING: printf("DO_NOTHING"); break;

	default: printf("%u - Not valid", aIn.mRequestCode);
	}

	printf("\n");

	printf("Request result : ");

	switch (aIn.mResultCode)
	{
	case PROTOCOL_RESULT_INVALID_REQUEST_CODE: printf("INVALID_REQUEST_CODE"); break;
	case PROTOCOL_RESULT_OK                  : printf("OK"                  ); break;
	case PROTOCOL_RESULT_REQUEST             : printf("REQUEST"             ); break;

	default: printf("%u - Not valid", aIn.mResultCode);
	}

	printf("\n");

	printf("Serial         : %u\n"      , aIn.mSerial   );
	printf("Size           : %u bytes\n", aIn.mSize_byte);
}
