/******************************************************************************/
/*                           file name : myAlloc.h                            */
/*                    descriptive name : myAllocation for debug               */
/*                            compiler : any.cc                               */
/*                         produced by : Kim,YongShik                         */
/*                       creating date : 43260817                             */
/*                         update date : 930817,0501,0515                     */
/*                         update date : 970602                               */
/*                         update date : 990225-0407                          */
/*                         update date : 43320501                             */
/*                         update date : 43360615                             */
/*                                                                            */
/******************************************************************************/

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
#endif /* myAlloc.h */
