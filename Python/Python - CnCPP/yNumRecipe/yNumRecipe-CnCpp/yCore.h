/******************************************************************************

       File: yCore.h
Description: Essential defintions
    Creator: Kim, Yongshik (copyRight)
       Date: 43230910-43231217
   Revision: Kim, Yongshik
     Update: 5/07/93, 43300917, 43310130,43310918, 43320223, 43320431
Last Update: 20160325

*******************************************************************************/

#ifndef yCore_header_INSTALLED
#define yCore_header_INSTALLED 1
/*////////////////////////////////////////////////////////////////////////////*/
/*
 Command line options: /wd4996

 C4996 occurs when the compiler encounters a function or variable that is marked
 as deprecated. Several functions, member functions, template functions, and 
 global variables in the libraries in Visual Studio are marked as deprecated. 
 These functions may have a different preferred name, may be insecure or have a 
 more secure variant, or may be obsolete. The error message may include a 
 suggested replacement for the deprecated function or global variable. You can 
 turn this warning off with the warning pragma or the /wd4996 command line option. 
 You can also use preprocessor macros to turn off certain classes of deprecation
 warnings.

 https://msdn.microsoft.com/query/dev14.query?appId=Dev14IDEF1&l=EN-US&k=k(C4996)&rd=true
 
 Deprecated functions: strncpy, sprintf
*/

/*
 Compiler directives in header files

 _MSVSC_
          6    .. MS Visual Studio C++ 6.0
          2015 .. MS Visual Studio Community 2015
*/

#undef  _HP715C_
#undef  _UNIXC_
#define _MSVSC_     2015
#define _VERSION_   "Build 2016.3.26"


/*//////////////////////////////////////////u//////////////////////////////////*/

#ifdef _UNIXC_
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
#elif defined(_MSVSC_)
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
/* Error and Warning                                                          */

void  errWarning _((const char*));
void  errExit    _((const char*));
const char *errMessage _(( ));

/******************************************************************************/
#endif /* yCore.h */
