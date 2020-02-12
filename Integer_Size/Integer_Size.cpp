
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

	printf("\n");

	printf("sizeof(          bool      ) = %u byte\n" , static_cast<unsigned int >(sizeof(         bool     )));
	printf("sizeof(          char      ) = %u byte\n" , static_cast<unsigned int >(sizeof(         char     )));
	printf("sizeof( unsigned char      ) = %u byte\n" , static_cast<unsigned int >(sizeof(unsigned char     )));
	printf("sizeof(          short     ) = %u bytes\n", static_cast<unsigned int >(sizeof(         short    )));
	printf("sizeof( unsigned short     ) = %u bytes\n", static_cast<unsigned int >(sizeof(unsigned short    )));
	printf("sizeof(          int       ) = %u bytes\n", static_cast<unsigned int >(sizeof(         int      )));
	printf("sizeof( unsigned int       ) = %u bytes\n", static_cast<unsigned int >(sizeof(unsigned int      )));
	printf("sizeof(          long      ) = %u bytes\n", static_cast<unsigned int >(sizeof(         long     )));
	printf("sizeof( unsigned long      ) = %u bytes\n", static_cast<unsigned int >(sizeof(unsigned long     )));
	printf("sizeof(          long long ) = %u bytes\n", static_cast<unsigned int >(sizeof(         long long)));
	printf("sizeof( unsigned long long ) = %u bytes\n", static_cast<unsigned int >(sizeof(unsigned long long)));

	printf("\n");

	printf("sizeof(   int8_t ) = %u byte\n" , static_cast<unsigned int >(sizeof(  int8_t)));
	printf("sizeof(  uint8_t ) = %u byte\n" , static_cast<unsigned int >(sizeof( uint8_t)));
	printf("sizeof(  int16_t ) = %u bytes\n", static_cast<unsigned int >(sizeof( int16_t)));
	printf("sizeof( uint16_t ) = %u bytes\n", static_cast<unsigned int >(sizeof(uint16_t)));
	printf("sizeof(  int32_t ) = %u bytes\n", static_cast<unsigned int >(sizeof( int32_t)));
	printf("sizeof( uint32_t ) = %u bytes\n", static_cast<unsigned int >(sizeof(uint32_t)));
	printf("sizeof(  int64_t ) = %u bytes\n", static_cast<unsigned int >(sizeof( int64_t)));
	printf("sizeof( uint64_t ) = %u bytes\n", static_cast<unsigned int >(sizeof(uint64_t)));

	printf("\n");

	printf("sizeof( size_t ) = %u byte\n" , static_cast<unsigned int >(sizeof(size_t)));

	printf("\n");

	return 0;
}
