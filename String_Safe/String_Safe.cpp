
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         02 - C/C++ particularities
// Video          07 - Security-Enhanced Version of CRT Functions
// Example        String_Safe
// File           String_Safe/String_Safe.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>
#include <string.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

// #1 - Defining a constant string using a define!
// + Can be used every where and string can be easily concatened at compile
//   time.
// - In some case, can cause the string to be present many times in the
//   memory.
#define LEARNING_PATH "Secure C/C++"

// #2 - Defining a constat variable
// + The string exist only once in memory in all cases.
// - Cannot be concatened at compile time.
//
// NOTE: Use the const keywork because the COURSE variable is initialized
//       with the address of a constant string.
static const char* COURSE = "C/C++ particularities";

// #3 - Defining a global variable
// * If the size if not specified, the variable is made just large enough to
//   containt the initial values and the EOS mark.
static char sStudent[64] = "John Smith";

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Example - String_Safe\n\n");

    errno_t lErr;
    int     lRet;

    // #4 - Definint a local variable
    char lShortAnswer[3] = "";
    char lString[128];

    // #5 - fgets - Reading a string from the keyboard (stdin)
    // * fgets returns NULL if it cannot read. On success, fget string
    //   returns the argument.
    // * When succeeding, fgets always return a string with an EOS.
    printf("Please, enter 1 letter and press Enter\n");
    fgets(lShortAnswer, sizeof(lShortAnswer), stdin);

    printf("Please, enter 2 letters and press Enter\n");
    fgets(lShortAnswer, sizeof(lShortAnswer), stdin);

    // * Here, the buffer was not large enough for the "Enter". This one
    //   stay in the stream buffer. The next fgets will retrieve it.

    fgets(lShortAnswer, sizeof(lShortAnswer), stdin);

    // #6 - puts - Displaying a string to the screen (stdout)
    // * puts returns EOF (-1) on error
    lRet = puts(sStudent);

    // #7 - strlen - Retrieve the length of a string
    // * strlen do not count the EOS mark.
    lRet = strlen(LEARNING_PATH);

    // #8 - strcmp - Compare string
    lRet = strcmp(sStudent, "John Smith");

    // #9 - strcpy - Copy a string
    // * strcpy_s returns the 0 on success
    lErr = strcpy_s(lString, LEARNING_PATH);

    // #10 - strncpy - A better way to copy string
    // - Can result in a non-terminated stirng!
    lErr = strncpy_s(lShortAnswer, "abc", sizeof(lShortAnswer));

    // Programmer should use strncpy this way!
    memset(&lShortAnswer, 0, sizeof(lShortAnswer));
    lErr = strncpy_s(lShortAnswer, "abc", sizeof(lShortAnswer) - 1);

    // #11 - strcat - Concaten strings
    lErr = strcat_s(lString, " - " );
    lErr = strcat_s(lString, COURSE);

    return 0;
}
