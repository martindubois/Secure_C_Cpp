
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         02 - C++ particularities
// Video          02 - Integer manipulation
// Example        Integer_Size
// File           Integer_Size/Integer_Size.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>
#include <stdint.h>

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
	printf("Example - Integer_Size\n\n");

	printf("sizeof(          bool      ) = %u byte\n" , sizeof(         bool     ));
	printf("sizeof(          char      ) = %u byte\n" , sizeof(         char     ));
	printf("sizeof( unsigned char      ) = %u byte\n" , sizeof(unsigned char     ));
	printf("sizeof(          short     ) = %u bytes\n", sizeof(         short    ));
	printf("sizeof( unsigned short     ) = %u bytes\n", sizeof(unsigned short    ));
	printf("sizeof(          int       ) = %u bytes\n", sizeof(         int      ));
	printf("sizeof( unsigned int       ) = %u bytes\n", sizeof(unsigned int      ));
	printf("sizeof(          long      ) = %u bytes\n", sizeof(         long     ));
	printf("sizeof( unsigned long      ) = %u bytes\n", sizeof(unsigned long     ));
	printf("sizeof(          long long ) = %u bytes\n", sizeof(         long long));
	printf("sizeof( unsigned long long ) = %u bytes\n", sizeof(unsigned long long));

	printf("\n");

	printf("sizeof(   int8_t ) = %u byte\n" , sizeof(  int8_t));
	printf("sizeof(  uint8_t ) = %u byte\n" , sizeof( uint8_t));
	printf("sizeof(  int16_t ) = %u bytes\n", sizeof( int16_t));
	printf("sizeof( uint16_t ) = %u bytes\n", sizeof(uint16_t));
	printf("sizeof(  int32_t ) = %u bytes\n", sizeof( int32_t));
	printf("sizeof( uint32_t ) = %u bytes\n", sizeof(uint32_t));
	printf("sizeof(  int64_t ) = %u bytes\n", sizeof( int64_t));
	printf("sizeof( uint64_t ) = %u bytes\n", sizeof(uint64_t));

	return 0;
}
