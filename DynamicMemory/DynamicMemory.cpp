
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         02 - C++ particularities
// Video          04 - Memory management
// Example        DynamicMemory
// File           DynamicMemory/DynamicMemory.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================

#define _CRT_SECURE_NO_WARNINGS

#include <assert.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// ===== Common =============================================================
#include "../Common/Dump.h"

// Constants
/////////////////////////////////////////////////////////////////////////////

#define BUFFER_SIZE_byte (40)

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void Test_malloc();
static void Test_new   ();

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
	printf("Example - DynamicMemory\n\n");

	Test_malloc();
	Test_new   ();

	return 0;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

void Test_malloc()
{
	printf("===== First malloc =====\n");

	char* lPtr = reinterpret_cast<char*>(malloc(BUFFER_SIZE_byte));
	assert(NULL != lPtr);

	Dump(lPtr, BUFFER_SIZE_byte);

	strcpy(lPtr, "Some very important information 0123456");

	free(lPtr);

	printf("===== Second malloc =====\n");

	lPtr = reinterpret_cast<char*>(malloc(BUFFER_SIZE_byte));
	assert(NULL != lPtr);

	Dump(lPtr, BUFFER_SIZE_byte);

	free(lPtr);
}

void Test_new()
{
	printf("===== First new =====\n");

	char* lPtr = new char[BUFFER_SIZE_byte];
	assert(NULL != lPtr);

	Dump(lPtr, BUFFER_SIZE_byte);

	strcpy(lPtr, "Some very important information 0123456");

	delete[] lPtr;

	printf("===== Second malloc =====\n");

	lPtr = new char[BUFFER_SIZE_byte];

	Dump(lPtr, BUFFER_SIZE_byte);

	delete[] lPtr;
}
