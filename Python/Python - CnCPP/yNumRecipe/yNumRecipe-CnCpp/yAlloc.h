/******************************************************************************

       File: yAlloc.h
Description: Allocation debugger
    Creator: Kim, Yongshik
       Date: 43260817
   Revision: Kim, Yongshik (copyRight)
     Update: 930817,0501,0515,
             970602,
			 990225-0407,
			 43320501,
			 43360615
Last Update: 20160325

*******************************************************************************/

#ifndef myAlloc_header_INSTALLED
#define myAlloc_header_INSTALLED 1
/******************************************************************************/
#include <stdlib.h>

#define my_aligner(size)                                                       \
        (((size) & (sizeof(int)-1) ) ? sizeof(int)-(size)%sizeof(int) : 0)

#if defined(_UNIXC_)
#   define _(a) ()
#else
#   define _(a) a
#endif

#define salloc(type,no)   (type*)malloc((unsigned int)((no)*sizeof(type)))
#define noof(obj) (sizeof(obj)/sizeof((obj)[0]))

/*----------------------------------------------------------------------------*/
#if defined(__cplusplus)
extern "C" {
#endif

#define malloc(x)    myAlloc(x)
#define realloc(x,y) myReAlloc((x),(y))
#define free(x)      myFree(x)

int  mySetHeapDebugger _((int)); /* TRUE=>execute,FALSE=>sleep */
int  myChkHeapDebugger _((void));

void *myAlloc _((size_t));
void *myReAlloc _((void*,size_t));
void myFree _((void*));

void *sysAlloc _((size_t));
void sysFree _((void*));

#if defined(__cplusplus)
}
#endif
/******************************************************************************/
#endif /* yAlloc.h */
