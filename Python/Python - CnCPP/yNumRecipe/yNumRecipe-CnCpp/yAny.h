/******************************************************************************

       File: yAny.h
Description: Any Type of Double Linked List
    Creator: Kim, Yongshik
       Date: 43260207    
   Revision: Kim, Yongshik (copyRight)
     Update: 4328 0411,0706,
	 4329 0320,
	 4330 0423-0428,0824,
	 4332 0309,0431,
	 4333 0403-0410,0710,0830,0907,1012,
	 4334 0305
Last Update: 20160325

*******************************************************************************/

#ifndef yAny_header_INSTALLED
#define yAny_header_INSTALLED 1
/******************************************************************************/
#include "yCore.h"

typedef struct _ANYNODE {
   struct _ANYNODE *next,*prev;
} ANYNODE;

typedef struct _ANYLIST {
   struct _ANYNODE *head,*tail;
} ANYLIST;

typedef struct _DoubleLinkedNode {
   struct _DoubleLinkedNode *next;
   struct _DoubleLinkedNode *prev;
   char                     *tok;
} DLN;

typedef struct _DoubleLinkedList {
   DLN *head,*tail;
   int total;
} DLL;

/******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif


int AnyOpenLinkedObject _((
   /* ANYLIST **list,int size */
   ));
int AnyCloseLinkedObject _((
   /* ANYLIST *list,IPTRFN delete */
   ));
int AnyAddSLObject _((
   /* ANYLIST *list,ANYNODE *node */
   ));
int AnyDelSLObject _((
   /* ANYLIST *list,ANYNODE *node */
   ));
int AnyAddDLObject _((
   /* ANYLIST *list,ANYNODE *node */
   ));
int AnyAddDLObjects _((
   /* ANYLIST *list,ANYLIST *objs */
   ));
int AnyInsDLObject _((
   /* ANYLIST *list,ANYNODE *insNode,ANYNODE *nextNode */
   ));
int AnyMovDLObject _((
   /* ANYLIST *list,ANYNODE *movNode,ANYNODE *nextNode */
   ));
int AnyMovDLObjects _((
   /* ANYLIST*,ANYNODE *movNode1st,ANYNODE *moveNodeLast,ANYNODE *nextNode */
   ));
int AnyDelDLObject _((
   /* ANYLIST *list,ANYNODE *node */
   ));

int AnyFindDLObject _((
   /* ANYLIST *list,ANYNODE **obj,IPTRFN find */
   ));
int AnySortDLObject _((
   /* ANYLIST *list,IPTRFN compare,IPTRFN exchange,int sortingMethod */
   ));
int AnyCompDLObject _((
   /* ANYLIST *list,IPTRFN compare */
   ));

int DLLOpen                _((DLL**));
int DLLClose               _((DLL*));
int DLLCloseWMA            _((DLL*)); /* With Memory Allocated (Token) */
int DLLAddToken            _(( ));
int DLLAddTokenWMA         _(( )); /* With Memory Allocation */
int DLLAddTokens           _(( ));
int DLLAddTokensWMA        _(( )); /* With Memory Allocation */
int DLLDelNode             _(( ));
int DLLDelNodeWMA          _((DLL*,DLN*)); /* With Memory Allocation */
int DLLDelCommentNode      _(( ));
int DLLDelCommentNodeWMA   _(( )); /* With Memory Allocation */
int DLLDelInvalidNodeWMA   _(( ));
int DLLInsToken            _((DLL*,DLN*,const char*));
int DLLInsTokenWMA         _((DLL*,DLN*,const char*)); /* With Memory Allocation */

int DLLGetStringLength     _(( ));
int DLLDuplicate           _(( ));
int DLLGetItFrStream       _((const char *stream,
                              const char comment,const char *delimiter,
                              DLL **list));
int DLLGetItFrStreamEx     _((const char *stream,char *sStart,char *sEnd,
                              DLL **list,int *nLineStart,int *nLineEnd));
int DLLPutItToStream       _((DLL *list,char **ppStream));
int DLLGetItFrFile         _(( ));
int DLLPutItToFile         _(( ));
int DLLRun                 _(( ));
int DLLPrintToStdout       _((DLL *list));
int DLLPrintToFile         _((DLL *list,const char *fileName));

int DLLGetTokensV1         _(( ));
int DLLGetMaxTokNoByWhite  _(( ));

#if defined(__cplusplus)
}
#endif
/******************************************************************************/
#endif /* yAny.h */
