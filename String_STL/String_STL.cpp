
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         02 - C/C++ particularities
// Video          08 - C++ string
// Example        String_STL
// File           String_STL/String_STL.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// ===== C++ ================================================================
#include <iostream>
#include <string>

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
static const std::string COURSE("C/C++ particularities");

// #3 - Defining a global variable
static std::string sStudent("John Smith");

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main()
{
    printf("Example - String_STL\n\n");

    int lRet;

    // #4 - Definint a local variable
    std::string lShortAnswer("");
    std::string lString;

    // #5 - std::getline - Reading a string from the keyboard (stdin)
    // * No EOS.
    printf("Please, enter as many letter you want and press Enter\n");
    std::getline(std::cin, lShortAnswer);

    // #6 - std::cout - Displaying a string to the screen (stdout)
    std::cout << sStudent;

    // #7 - std::string::size - Retrieve the length of a string
    // * Do not count the EOS mark.
    lRet = COURSE.size();

    // #8 - strcmp - Compare string
    bool lBool = (sStudent == "John Smith");

    // #9 - std::string::= - Copy a string
    // * Returns a reference to the std::string
    lString = LEARNING_PATH;

    // #11 - std::string::+= - Concaten strings
    lString += " - " ;
    lString += COURSE;

    return 0;
}
