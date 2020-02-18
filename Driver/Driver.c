
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         07 - Driver development
// Video          03 - Read, Write and IoCtl
// File           Driver/Driver.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Linux kernel =======================================================
#include <linux/fs.h>
#include <linux/module.h>

// ===== Driver =============================================================
#include "Device.h"

#include "Driver.h"

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================
static char      * DevNode( struct device * aDev, umode_t * aMode );
static void __exit Exit   ( void );
static int  __init Init   ( void );

// Constants
/////////////////////////////////////////////////////////////////////////////

#define DEVICE_COUNT_MAX (1)

#define MODULE_NAME "Driver"

// Data type
/////////////////////////////////////////////////////////////////////////////

typedef struct
{
    dev_t  mChrDev;
    void * mDevice;
}
DriverContext;

// Global variables
/////////////////////////////////////////////////////////////////////////////

// Static variables
/////////////////////////////////////////////////////////////////////////////

struct class       * sClass = NULL;
static DriverContext sThis;

// Functions
/////////////////////////////////////////////////////////////////////////////

void * Driver_FindDevice( unsigned char aMinor )
{
    return sThis.mDevice;
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================

char * DevNode( struct device * aDev, umode_t * aMode )
{
    printk( KERN_DEBUG "DevNode( ,  )\n" );

    if ( NULL != aMode )
    {
        ( * aMode ) =  0666;
    }

    return NULL;
}

void Exit()
{
    printk( KERN_DEBUG "Exit()\n" );

    if ( NULL != sThis.mDevice )
    {
        // Device_Create ==> Device_Delete  See Init
        Device_Delete( sThis.mDevice );
    }

    // class_create ==> class_destroy  See Init
    class_destroy( sClass );

    // alloc_chrdev_region ==> unregister_chrdev_region  See Init
    unregister_chrdev_region( sThis.mChrDev, DEVICE_COUNT_MAX );
}

module_exit( Exit );

int Init()
{
    int lRet;

    printk( KERN_DEBUG "Init()\n" );

    // class_create ==> class_destroy  See Exit
    sClass = class_create( THIS_MODULE, "Driver" );
    if ( NULL == sClass )
    {
        printk( KERN_ERR "Init - class_create( ,  ) failed\n" );
        return ( - __LINE__ );
    }

    sClass->devnode = DevNode;

    // alloc_chrdev_region ==> unregister_chrdev_region  See Exit
    lRet = alloc_chrdev_region( & sThis.mChrDev, 0, DEVICE_COUNT_MAX, MODULE_NAME );
    if ( 0 != lRet )
    {
        printk( KERN_ERR "Init - alloc_chrdev_region( , , ,  ) failed - %d\n", lRet );
        goto Error0;
    }

    sThis.mDevice = Device_Create( MAJOR( sThis.mChrDev ), MINOR( sThis.mChrDev ), sClass );
    if ( NULL == sThis.mDevice )
    {
        printk( KERN_ERR "Init - Device_Create( , , ,  ) failed\n" );
        goto Error1;
    }

    return 0;

Error1:
    unregister_chrdev_region( sThis.mChrDev, DEVICE_COUNT_MAX );

Error0:
    class_destroy( sClass );
    return ( - __LINE__ );
}

module_init( Init );

// License
/////////////////////////////////////////////////////////////////////////////

MODULE_LICENSE( "GPL" );

MODULE_AUTHOR( "Martin Dubois <mdubois@kms-quebec.com>");
MODULE_DESCRIPTION( "Example - Driver" );
