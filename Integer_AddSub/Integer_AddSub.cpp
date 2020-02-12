
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         02 - C++ particularities
// Video          02 - Integer manipulation
// Example        Integer_AddSub
// File           Integer_AddSub/Integer_AddSub.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdint.h>
#include <stdio.h>

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void Test_32();
static void Test_8();

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
	printf("Example - Integer_AddSub\n\n");

	Test_8 ();
	Test_32();

	return 0;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void Test_32()
{
	 int32_t lS = 0;
	uint32_t lU = 0;

	printf("===== 32 bits - Unsigned =====\n");

	lU +=          1; printf(" +          1 --> %10u\n", lU);
	lU += 0xfffffffe; printf(" + 0xfffffffe --> %10u\n", lU);
	lU +=          1; printf(" +          1 --> %10u\n", lU);
	lU -=          1; printf(" -          1 --> %10u\n", lU);

	printf("\n");

	printf("===== 32 - Signed =====\n");

	lS +=          1; printf(" +          1 --> %11d\n", lS);
	lS += 0x7ffffffe; printf(" + 0x7ffffffe --> %11d\n", lS);
	lS +=          1; printf(" +          1 --> %11d\n", lS);
	lS -=          1; printf(" -          1 --> %11d\n", lS);
	lS -= 0xfffffffe; printf(" + 0xfffffffe --> %11d\n", lS);
	lS -=          1; printf(" -          1 --> %11d\n", lS);
	lS -=          1; printf(" -          1 --> %11d\n", lS);

	printf("\n");
}

void Test_8()
{
	 int8_t lS = 0;
	uint8_t lU = 0;

	printf("===== 8 bits - Unsigned =====\n");

	lU +=    1; printf(" +   1 --> %3u\n", lU);
	lU += 0xfe; printf(" + 254 --> %3u\n", lU);
	lU +=    1; printf(" +   1 --> %3u\n", lU);
	lU -=    1; printf(" -   1 --> %3u\n", lU);

	printf("\n");

	printf("===== 8 bits - Signed =====\n");

	lS +=    1; printf(" +   1 --> %4d\n", lS);
	lS += 0x7e; printf(" + 126 --> %4d\n", lS);
	lS +=    1; printf(" +   1 --> %4d\n", lS);
	lS -=    1; printf(" -   1 --> %4d\n", lS);
	lS -= 0xfe; printf(" - 254 --> %4d\n", lS);
	lS -=    1; printf(" -   1 --> %4d\n", lS);
	lS -=    1; printf(" -   1 --> %4d\n", lS);

	printf("\n");
}
