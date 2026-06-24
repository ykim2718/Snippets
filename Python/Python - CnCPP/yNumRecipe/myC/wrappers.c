/******************************************************************************/
/*                          file name : wrappers.c                            */
/*                   descriptive name : wrappers                              */
/*                           compiler : cc                                    */
/*                        produced by : The C Users Journal                   */
/*                                    + Kim,YongShik                          */
/*                      creating date : 43260817 (930817)                     */
/*                        update date : 950124,0329,0501,0512-15              */
/*                        update date : 970602                                */
/*                        update date : 980918                                */
/*                        update date : 990331                                */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

/******************************************************************************/

#ifndef hwrapper_core_INSTALLED
#define hwrapper_core_INSTALLED 1

#undef __MYDEBUGPRINT__ 
#undef __MYDEBUGFPRINT__

/*
#define my_aligner(size) \
        (((size) & (sizeof(int)-1) ) ? sizeof(int)-(size)%sizeof(int) : 0)
*/
#if defined(_HP715C_) || defined(_UNIXC_)
#define my_aligner(size)                                                       \
        (((size)%sizeof(int)) ? sizeof(int)-(size)%sizeof(int):0)
#else
#define my_aligner(size) (0)
#endif

int     wrappers_mcount=0; /* count malloc calls */
int     wrappers_fcount=0; /* count free   calls */
FILE   *wrappers_log;

#define wrappers_log_name "/tmp/wrappers.log"
#define SIGWORD (unsigned int)0xAA55

/******************************************************************************/

void *myAlloc( size )
size_t size;
{
   void *temp;
   char *adjptr;
   size_t lsize;

#if defined(__MYDEBUGFPRINT__)
   if (wrappers_log==NULL) {
       wrappers_log=fopen(wrappers_log_name,"w");
       if (!wrappers_log) {
          fprintf(stderr,"Error, \"%s\" file open .. in myAlloc() !\n",
                  wrappers_log_name);
          exit(1);
       }
   }
#endif
   size+=my_aligner(size);
   lsize=sizeof(int)+sizeof(size_t)+size+sizeof(unsigned int);
   if (!(temp=(void *)malloc(lsize))) {
      fprintf(stderr,"Error, \"%d\" bytes allocation ... in myAlloc() !\n",
              lsize);
      exit(1);
   }
   memset(temp,0,lsize); /* shik */
#if defined(__MYDEBUGFPRINT__)
   fprintf(wrappers_log,"allo id=%5.5d ptr=%p size=%d\n",
           wrappers_mcount,temp,lsize);
#endif
#if defined(__MYDEBUGPRINT__)
   fprintf(stderr,"allo id=%5.5d ptr=%p size=%d\n",wrappers_mcount,temp,lsize);
#endif
   adjptr=(char *)temp;
   *((int *)adjptr)=wrappers_mcount++;
   adjptr+=sizeof(int);
   *((size_t *)adjptr)=size;
   temp=(void *)(adjptr+=sizeof(size_t));
   adjptr+=size;
   *((unsigned int *)adjptr)=SIGWORD;
   return temp;
}

void *myReAlloc( ptr,size ) /* shik */
   void *ptr;
   size_t size;
{
   char *new; 
   void myFree();

   new=(void *)myAlloc(size);
   if (!new) return (void *)0;
   memcpy(new,ptr,size);
   myFree(ptr);
   return (void *)new;
}

void myFree(tree)
void *tree;
{
   char *adjptr;
   char *fenceptr;
   size_t size;

   fenceptr=adjptr=(char *)tree;
   adjptr-=sizeof(size_t);
   size=*((size_t *)adjptr);
   fenceptr+=size;
   adjptr-=sizeof(int);
#if defined(__MYDEBUGFPRINT__)
   if (wrappers_log==NULL) {
      wrappers_log=fopen(wrappers_log_name,"w");
      if (!wrappers_log) {
         fprintf(stderr,"Error, \"%s\" file open .. in myFree() !\n",
                 wrappers_log_name);
         exit(1);
      }
   }
   fprintf(wrappers_log,"free id=%5.5d ptr=%p count=%d\n",
      *((int *)adjptr),adjptr,wrappers_fcount);
#endif
#if defined(__MYDEBUGPRINT__)
   fprintf(stderr,"free id=%5.5d ptr=%p count=%d\n",
      *((int *)adjptr),adjptr,wrappers_fcount);
#endif
   if (*((unsigned int *)fenceptr)!=SIGWORD) {
#if defined(__MYDEBUGFPRINT__)
      fprintf(wrappers_log,"%p %5.5d damaged object %d\n",
         adjptr,*((int *)adjptr),wrappers_fcount);
#endif
      fprintf(stderr,"Error, ... damaged object : id=%5.5d ptr=%p count=%d\n",
         *((int *)adjptr),adjptr,wrappers_fcount);
   }
   wrappers_fcount++;
   free((void *)adjptr);
}

void *allocInStdLib( size )
   size_t size;
{
   void *ptr;

   size+=my_aligner(size);
#if defined(malloc)
#undef malloc
#endif
   ptr=(void *)malloc(size);
   memset(ptr,0,size); /* shik */
   return ptr;
}

void freeInStdLib( ptr )
   void *ptr;
{
#if defined(free)
#undef free
   free(ptr);
#endif
}

/******************************************************************************/
#endif /* hwrapper_core_INSTALLED */
