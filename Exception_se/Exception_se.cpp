
// Author         Martin Dubois, P.Eng.
// Learning path  Secure_C_Cpp
// Course         04 - Error handling
// Video          04 - C++ exception
// Example        Exception_se
// File           Exception_se/Exception_se.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== C++ ================================================================
#include <exception>

// ===== Windows ============================================================
#include <Windows.h>
#include <eh.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define ARG_ERROR_TYPE (1)

#define ARG_QTY (2)

// Static functions declarations
/////////////////////////////////////////////////////////////////////////////

static void TranslateException(unsigned int aCode, struct _EXCEPTION_POINTERS* aStruct);

// Entry point
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char** aVector)
{
    printf("Example - Exception_se\n\n");

    if (ARG_QTY > aCount)
    {
        fprintf(stderr, "USER ERROR  Invalid command line\n");
        return __LINE__;
    }

    void * lTranslator = _set_se_translator(TranslateException);

    try
    {
        int  lIntA = 1;
        int  lIntB = 0;
        int* lIntP = NULL;
        int  lIntR;

        switch (atoi(aVector[ARG_ERROR_TYPE]))
        {
        case 0: printf("Integer divide by 0\n"); lIntR = lIntA / lIntB; break;
        case 1: printf("Access violation\n"   ); lIntR = * lIntP; break;

        default: fprintf(stderr, "USER ERROR  Invalid error type\n");
        }
    }
    catch (std::exception eE)
    {
        fprintf(stderr, "EXCEPTION  %s\n", eE.what());
    }

    void * lRet = _set_se_translator(reinterpret_cast<_se_translator_function>(lTranslator));
    assert(TranslateException == lRet);

	return 0;
}

// Static function
/////////////////////////////////////////////////////////////////////////////

void TranslateException(unsigned int aCode, struct _EXCEPTION_POINTERS* aStruct)
{
    char lMsg[64];

    sprintf_s(lMsg, "Structured exception 0x%08x", aCode);

    throw std::exception(lMsg);
}
