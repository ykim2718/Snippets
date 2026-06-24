/******************************************************************************/
/*                                                                            */
/*                           file name : myCore.h                             */
/*                            producer : Kim,YongShik                         */
/*                       creating date : 43230910-43231217                    */
/*                         update date : 5/07/93                              */
/*                         update date : 43300917                             */
/*                         update date : 43310130,0918                        */
/*                         update date : 43320223                             */
#define                     __VERSION__ "43320431"    
/*                                                                            */
/******************************************************************************/

#ifndef myCore_header_INSTALLED
#define myCore_header_INSTALLED 1
/*******************************************************************************

   PreProcessor Definitions @ Compiling
    -> Compiler : _HP715C_,_UNIXC_,_MSC_(MSVisualC++)
    -> Window   : _SUNVIEW_,_XnMOTIF_,_MSWINDOW_

   Example)
     At VisualCPP 4.0,
        /D "_MSC_" /D "_MSWINDOW_"

*******************************************************************************/

#if defined(_UNIXC_)
#   define _(a) ()
#else
#   define _(a) a
#endif

#ifndef TRUE
#   define TRUE    (char)0x01
#endif
#ifndef FALSE
#   define FALSE   (char)0x00
#endif
#ifndef INVALID
#   define INVALID (char)-1
#endif
#ifndef OK
#   define OK      (char)0x01
#endif
#ifndef YES
#   define YES     TRUE
#endif
#ifndef NO
#   define NO      FALSE
#endif

/*----------------------------------------------------------------------------*/

#ifndef __VPTRFN
#define __VPTRFN 1
typedef void   (*VPTRFN)();
#endif
#ifndef __IPTRFN
#define __IPTRFN 1
typedef int    (*IPTRFN)();
#endif
#ifndef __FPTRFN
#define __FPTRFN 1
typedef float (*FPTRFN)();
#endif
#ifndef __DPTRFN
#define __DPTRFN 1
typedef double (*DPTRFN)();
#endif

/*----------------------------------------------------------------------------*/

#if defined(_UNIXC_)
#include <varargs.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h> /* <- (c)shik,941214 */
#define F_OPENMODE O_RDWR
#define F_CREATEMODE S_IREAD|S_IWRITE
#elif defined(_MSC_)
#include <stdio.h>
#include <stdarg.h>
#include <direct.h>
#include <sys\types.h>
#include <sys\stat.h>
#include <fcntl.h>
#include <io.h>
#define F_OPENMODE O_RDWR+O_BINARY
#undef  F_CREATEMODE
#define F_CREATEMODE S_IWRITE
#else
#error Compiler type shouble be defined.
#endif

/*----------------------------------------------------------------------------*/

#include "myAlloc.h"

extern void  errWarning _((const char*)); /* gecore.c */
extern void  errExit    _((const char*)); /* gecore.c */
extern const char *errMessage _(( ));     /* gecore.c */

/******************************************************************************/
#endif /* myCore.h */
