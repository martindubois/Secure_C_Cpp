
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         02 - C++ particularities
// Video          02 - Integer manipulation
// Example        Integer_Compare
// File           Integer_Compare/Integer_Compare.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void Test_32();
static void Test_8 ();

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
	printf("Example - Integer_Compare\n\n");

	Test_32();
	Test_8 ();

	return 0;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void Test_32()
{
	printf("===== 32 bits =====\n");

	int          lS;
	unsigned int lU;

	lS =  0; lU =          0; printf("%2d == %10u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
	lS = -1;                  printf("%2d == %10u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
			                  printf("%2d <= %10u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
		     lU = 0x7fffffff; printf("%2d <= %10u --> %s\n", lS, lU, (lS <= lU) ? "true" : "false");
			 lU = 0x80000000; printf("%2d == %10u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
			                  printf("%2d <= %10u --> %s\n", lS, lU, (lS <= lU) ? "true" : "false");
			 lU = 0xffffffff; printf("%2d == %10u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
							  printf("%2d <  %10u --> %s\n", lS, lU, (lS <  lU) ? "true" : "false");

	printf("\n");
}

void Test_8()
{
	printf("===== 8 bits =====\n");

	char          lS;
	unsigned char lU;

	lS =  0; lU =    0; printf("%2d == %3u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
	lS = -1;            printf("%2d == %3u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
			            printf("%2d <= %3u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
		     lU = 0x7f; printf("%2d <= %3u --> %s\n", lS, lU, (lS <= lU) ? "true" : "false");
			 lU = 0x80; printf("%2d == %3u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
			            printf("%2d <= %3u --> %s\n", lS, lU, (lS <= lU) ? "true" : "false");
			 lU = 0xff; printf("%2d == %3u --> %s\n", lS, lU, (lS == lU) ? "true" : "false");
						printf("%2d <  %3u --> %s\n", lS, lU, (lS <  lU) ? "true" : "false");

	printf("\n");
}
