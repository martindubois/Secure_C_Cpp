
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         05 - Random number generator
// Video          02 - rand function
// Example        Random_0
// File           Random_0/Random_0.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Example - Random_0\n\n");

    time_t lTime;

    srand(static_cast<unsigned int>(time(&lTime)));

    for (unsigned int i = 0; i < 20; i++)
    {
        printf("%5u\n", rand());
    }

	return 0;
}
