
// Author         Martin Dubois, P.Eng.
// Learning path  Secure C/C++
// Course         07 - Driver development
// Video          03 - Read, Write and IoCtl
// File           Driver/Device.c

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Linux kernel =======================================================
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

// ===== Driver =============================================================
#include "Driver.h"

#include "Device.h"

// Data type
/////////////////////////////////////////////////////////////////////////////

typedef struct
{

    // ===== Pointer to Linux structures ====================================
    struct cdev   * mCDev  ;
    struct class  * mClass ;
    struct device * mDevice;

    // ===== Data buffer ====================================================
    char mData[4096];

    // ===== Other ==========================================================
    dev_t mDevId;

}
Device_Context;

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================
static long    IoCtl  ( struct file  * aFile , unsigned int aCode, unsigned long aArg_UA );
static int     Open   ( struct inode * aINode, struct file * aFile );
static ssize_t Read   ( struct file  * aFile , char * aBuffer_UA, size_t aSize_byte, loff_t * aOffset );
static int     Release( struct inode * aInode, struct file * aFile );
static ssize_t Write  ( struct file  * aFile , const char * aBuffer_UA, size_t aSize_byte, loff_t * aOffset );

// Static variables
/////////////////////////////////////////////////////////////////////////////

static struct file_operations sOperations =
{
    .owner          = THIS_MODULE,
    .open           = Open       ,
    .read           = Read       ,
    .release        = Release    ,
    .unlocked_ioctl = IoCtl      ,
    .write          = Write      ,
};

// Functions
/////////////////////////////////////////////////////////////////////////////

void * Device_Create( unsigned char aMajor, unsigned char aMinor, struct class * aClass )
{
    Device_Context * lResult;
    int              lRet;

    printk( KERN_DEBUG "Device_Create( %u, %u,  )\n", aMajor, aMinor );

    // kalloc ==> kfree  See Device_Delete
    lResult = kmalloc( sizeof( Device_Context ), GFP_KERNEL );
    if ( NULL == lResult )
    {
        printk( KERN_ERR "Device_Create - kalloc(  ) failed\n" );
        return NULL;
    }

    memset( lResult, 0, sizeof( Device_Context ) );

    lResult->mClass = aClass;
    lResult->mDevId = MKDEV( aMajor, aMinor );

    // cdev_alloc ==> cdef_del  See Device_Delete
    lResult->mCDev = cdev_alloc();
    if ( NULL == lResult->mCDev )
    {
        printk( KERN_ERR "Device_Create - cdev_alloc() failed\n" );
        goto Error0;
    }

    lResult->mCDev->owner = THIS_MODULE;

    cdev_init( lResult->mCDev, & sOperations );

    lRet = cdev_add( lResult->mCDev, lResult->mDevId, 1 );
    if ( 0 != lRet )
    {
        printk( KERN_ERR "Device_Create - cdev_add( , ,  ) failed - %d\n", lRet );
        goto Error1;
    }

    // device_create ==> device_destroy  See Device_Delete
    lResult->mDevice = device_create( lResult->mClass, NULL, lResult->mDevId, NULL, "Driver%u", 0 );
    if ( NULL == lResult->mDevice )
    {
        printk( KERN_ERR "Device_Create( , , , , ,  ) failed\n" );
        goto Error1;
    }

    return lResult;

Error1:
    cdev_del( lResult->mCDev );

Error0:
    kfree( lResult );
    return NULL;
}

void Device_Delete( void * aThis )
{
    Device_Context * lThis = aThis;

    printk( KERN_DEBUG "Device_Delete(  )\n" );

    // device_create ==> device_destroy  See Device_Create
    device_destroy( lThis->mClass, lThis->mDevId );

    // cdev_alloc ==> cdev_del  See Device_Create
    cdev_del( lThis->mCDev );

    // kalloc ==> kfree  See Device_Create;
    kfree( lThis );
}

// Static functions
/////////////////////////////////////////////////////////////////////////////

// ===== Entry points =======================================================

long IoCtl( struct file * aFile, unsigned int aCode, unsigned long aArg_UA )
{
    printk( KERN_DEBUG "IoCtl( , 0x%08x, 0x%lx )\n", aCode, aArg_UA );

    return 0;
}

int Open( struct inode * aINode, struct file * aFile )
{
    printk( KERN_DEBUG "Open( ,  )\n" );

    aFile->private_data = Driver_FindDevice( iminor( aINode ) );

    return 0;
}

ssize_t Read( struct file * aFile, char * aBuffer_UA, size_t aSize_byte, loff_t * aOffset )
{
    unsigned int     lRet ;
    Device_Context * lThis;

    printk( KERN_DEBUG "Read( , , %lu bytes,  )\n", aSize_byte );

    lThis = aFile->private_data;

    if ( sizeof( lThis->mData ) < aSize_byte )
    {
        printk( KERN_ERR "Read - Invalid size - %lu bytes\n", aSize_byte );
        return ( - __LINE__ );
    }

    lRet = copy_to_user( aBuffer_UA, lThis->mData, aSize_byte );
    if ( aSize_byte <= lRet )
    {
        printk( KERN_ERR "Read - Invalid address\n" );
        return ( - __LINE__ );
    }

    return ( aSize_byte - lRet );
}

int Release( struct inode * aINode, struct file * aFile )
{
    printk( KERN_DEBUG "Release( ,  )\n" );

    return 0;
}

ssize_t Write( struct file * aFile, const char * aBuffer_UA, size_t aSize_byte, loff_t * aOffset )
{
    unsigned int     lRet ;
    Device_Context * lThis;

    printk( KERN_DEBUG "Write( , , %lu bytes,  )\n", aSize_byte );

    lThis = aFile->private_data;

    if ( sizeof( lThis->mData ) < aSize_byte )
    {
        printk( KERN_ERR "Read - Invalid size - %lu bytes\n", aSize_byte );
        return ( - __LINE__ );
    }

    lRet = copy_from_user( lThis->mData, aBuffer_UA, aSize_byte );
    if ( aSize_byte <= lRet )
    {
        printk( KERN_ERR "Read - Invalid address\n" );
        return ( - __LINE__ );
    }

    return ( aSize_byte - lRet );
}
