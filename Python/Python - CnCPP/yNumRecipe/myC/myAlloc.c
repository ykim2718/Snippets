/******************************************************************************/
/*                                                                            */
/*                          file name : myAlloc.c                             */
/*                   descriptive name : allocation debugger                   */
/*                           compiler : cc + Visual C++                       */
/*                        produced by : C/C++Journal + Kim,YongShik           */
/*                      creating date : 43320417 (990417)                     */
/*                        update date : 990417-0501-                          */
/*                                                                            */
/* 4334 0220-0306,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

/******************************************************************************/

extern void errWarning();
extern void errExit();

#if defined(_HP715C_) || defined(_UNIXC_)
#define my_aligner(nSize)                                                       \
        (((nSize)%sizeof(int)) ? sizeof(int)-(nSize)%sizeof(int):0)
#else
#define my_aligner(nSize) (0)
#endif

#if defined(malloc)
#undef malloc
#endif
#if defined(free)
#undef free
#endif

#define noof(obj) (sizeof(obj)/sizeof((obj)[0]))
#define FENCEWORD (unsigned int)0xAA55

void *myAllocStack[10000]; /* in stack, not in heap */
int myAllocStackTotal=-1;
int myAllocCount=0;

/******************************************************************************/

static
void myPushPtr( pAddr ) /* malloc */
   void *pAddr;
{
   if (myAllocStackTotal<0) return;
   if (myAllocStackTotal>=noof(myAllocStack)) {
      errWarning("Warning, myAllocStack overflow .. in myPushPtr()\n");
      return;
   }
   myAllocStack[myAllocStackTotal++]=pAddr;
}

static
void myPopPtr( pAddr ) /* free */
   void *pAddr;
{
   int nIndex;
   char qBuffer[256];

   if (myAllocStackTotal<0) return;
   for (nIndex=0;nIndex<myAllocStackTotal;nIndex++) {
      if (myAllocStack[nIndex]==pAddr) {
         memcpy(myAllocStack+nIndex,myAllocStack+nIndex+1,
               (myAllocStackTotal-nIndex)*sizeof(void*));
         myAllocStackTotal--;
         return;
      }
   }
   sprintf(
      qBuffer,
      "Warning, Not-allocated object (%p) free in myPopPtr()\n",
      pAddr);
   errWarning(qBuffer);
}

int mySetHeapDebugger( flag )
   int flag; /* TRUE(1)=>execute,FALSE=>sleep */
{
   int TRUE=1;
   myAllocStackTotal=(flag==TRUE) ? 0:-1;
   return TRUE;
}

int myChkHeapDebugger()
{
   int nIndex,nSize,nBrokenObject;
   char *pAddr,*pAdjusted,*pFence;

   nBrokenObject=0;
   for (nIndex=0;nIndex<myAllocStackTotal;nIndex++) {
      pFence=pAdjusted=pAddr=myAllocStack[nIndex];
      pAdjusted-=sizeof(size_t);
      nSize=*((size_t *)pAdjusted);
      pFence=pAddr+nSize;
      /* pAdjusted-=sizeof(int); 2001.0305 */
      if (*((unsigned int *)pFence)!=FENCEWORD) {
         nBrokenObject--;
         /* Look at "pAddr" address. 20030615 */
      }
   }
   if (nBrokenObject) return nBrokenObject;
   return myAllocStackTotal;
   /* The best is zero-return. */
}

void *myAlloc( nSize ) /* sizeof(int)+sizeof(size_t)+pAddr+FENCEWORD(unsigned int) */
   size_t nSize;
{
   void *pAddr;
   char *pAdjusted;
   size_t lsize;
   char qBuffer[256];

   nSize+=my_aligner(nSize);
   lsize=sizeof(size_t)+nSize+sizeof(unsigned int);
   lsize=sizeof(int)+sizeof(size_t)+nSize+sizeof(unsigned int);
   if (!(pAddr=(void *)malloc(lsize))) {
      sprintf(
         qBuffer,
         "Error, \"%d\" bytes allocation ... in myAlloc() !\n",
         lsize);
      errExit(qBuffer);
   }
   pAdjusted=(char *)pAddr;
   *((int *)pAdjusted)=myAllocCount++;
   pAdjusted+=sizeof(int);
   *((size_t *)pAdjusted)=nSize;
   pAddr=(void *)(pAdjusted+=sizeof(size_t));
   pAdjusted+=nSize;
   *((unsigned int *)pAdjusted)=FENCEWORD;
   myPushPtr(pAddr);
   return pAddr;
}

void *myReAlloc( pAddr,nSize ) /* shik96@samsung.co.kr */
   void *pAddr;
   size_t nSize;
{
   char *pNew;
   void myFree();
   size_t nOldSize;

   pNew=(void*)myAlloc(nSize);
   memset(pNew,0,nSize);
   if (!pNew) return (void*)0;
   nOldSize=*(size_t*)((char*)pAddr-sizeof(size_t)); /* 2001.0306 */
   memcpy(pNew,pAddr,nSize>nOldSize ? nOldSize:nSize); /* 2001.0817 */
   myFree(pAddr);
   return (void*)pNew;
}

void myFree(pAddr)
   void *pAddr;
{
   char *pAdjusted;
   char *pFence;
   size_t nSize;
   char qBuffer[256];

   pFence=pAdjusted=(char *)pAddr;
   pAdjusted-=sizeof(size_t);
   nSize=*((size_t *)pAdjusted);
   pFence+=nSize;
   pAdjusted-=sizeof(int); /* DEBUG : *(size_t*)((char*)(myAllocStack[0])-8) */
   if (*((unsigned int *)pFence)!=FENCEWORD) {
      sprintf(
         qBuffer,
         "Error, Damaged object (%p) occurred : %s\n",
         pAdjusted,pAddr);
      errWarning(qBuffer);
   }
   myPopPtr(pAddr);
   free((void *)pAdjusted);
}

void *sysAlloc( nSize )
   size_t nSize;
{
   void *pAddr;

   nSize+=my_aligner(nSize);
   pAddr=(void *)malloc(nSize);
   return pAddr;
}

void sysFree( pAddr )
   void *pAddr;
{
   free(pAddr);
}

/******************************************************************************/
/* myAlloc.c */