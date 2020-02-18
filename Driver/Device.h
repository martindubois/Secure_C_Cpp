
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         07 - Driver development
// Video          03 - Read, Write and IoCtl
// File           Driver/Device.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Linux kernel =======================================================
#include <linux/cdev.h>

// Functions
/////////////////////////////////////////////////////////////////////////////

extern void * Device_Create( unsigned char aMajor, unsigned char aMinor, struct class * aClass );
extern void   Device_Delete( void * aThis );
