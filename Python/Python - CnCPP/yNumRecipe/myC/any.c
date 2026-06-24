/******************************************************************************/
/*                           file name : any.h                                */
/*                         description : Any Type of Double Linked List       */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43260207                             */
/* 4328 0411,0416,0501,0701,0706,1121,____,____,____,____,____,____,____,____ */
/* 4329 0320,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4330 0423-0428,0824,____,____,____,____,____,____,____,____,____,____,____ */
/* 4331 0930,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0714,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0403-0410,0828,0907,1012,____,____,____,____,____,____,____,____,____ */
/* 4334 0305,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "myCore.h"
#include "number.h"
#include "str.h"
#include "tools.h"
#include "any.h"

/******************************************************************************/

int AnyOpenLinkedObject( ppList,nSize )
   ANYLIST **ppList;
   int nSize;
{
   if (nSize>0) {
      (*ppList)=(ANYLIST*)malloc(nSize);
      memset((char*)(*ppList),0,nSize);
      /* (*ppList)->head=(*ppList)->tail=(ANYNODE*)0; */
      return TRUE;
   } else {
      (*ppList)=0;
      return FALSE;
   }
}

int AnyCloseLinkedObject( pList,pDeleteFn )
   ANYLIST *pList;
   IPTRFN pDeleteFn;
{
   ANYNODE *pNode,*pNext;

   pNode=pList->head;
   while (pNode) {
      if (pDeleteFn) (*pDeleteFn)(pNode);
      pNext=pNode->next;
      free(pNode);
      pNode=pNext;
   }
   pList->head=pList->tail=NULL;
   free(pList);
   return TRUE;
}

int AnyAddSLObject( pList,pNode )
   ANYLIST *pList;
   ANYNODE *pNode; 
{
   if (pList->head) {
      pList->tail->next = pNode;
      pList->tail = pNode;
      pList->tail->next = NULL;
   } else {
      pList->head =
      pList->tail = pNode;
      pList->tail->next = NULL;
   }
   return TRUE;
}

int AnyDelSLObject( pList,pNode )
   ANYLIST *pList;
   ANYNODE *pNode; 
{
   ANYNODE *pAnyNode;

   if (pNode==pList->head) {
      pList->head = pNode->next;
      if (!pList->head)
         pList->tail=(ANYNODE*)0;
   } else if (pNode==pList->tail) {
      pAnyNode=pList->head;
      while (pAnyNode->next!=pNode) pAnyNode=pAnyNode->next;
      pList->tail = pAnyNode;
      pList->tail->next=(ANYNODE*)0;
   } else {
      pAnyNode=pList->head;
      while (pAnyNode->next!=pNode) pAnyNode=pAnyNode->next;
      pAnyNode->next=pNode->next;
   }
   return TRUE;
}

int AnyAddDLObject( pList,pNode )
   ANYLIST *pList;
   ANYNODE *pNode; 
{
   if (pList->head) {
      pNode->prev=pList->tail;
      pList->tail->next=pNode;
      pList->tail=pNode;
      pList->tail->next=NULL;
   } else {
      pList->head=pList->tail=pNode;
      pList->head->prev=pList->tail->next=NULL;
   }
   return TRUE;
}

int AnyAddDLObjects( pList,objs )
   ANYLIST *pList;
   ANYLIST *objs;
{
   if (pList->head) {
      pList->tail->next=objs->head;
      objs->head->prev=pList->tail; 
      pList->tail=objs->tail;
   } else {
      pList->head=objs->head;
      pList->tail=objs->tail;
   }
   return TRUE;
}

int AnyInsDLObject( pList,insNode,nextNode )
   ANYLIST *pList;
   ANYNODE *insNode,*nextNode;
{
   if (nextNode) {
      insNode->prev=nextNode->prev;
      insNode->next=nextNode;
      nextNode->prev=insNode;
      if (insNode->prev)
         insNode->prev->next=insNode;
      if (nextNode==pList->head)
         pList->head=insNode;
   } else { /* pList->tail + insNode */
      insNode->prev=pList->tail;
      insNode->next=NULL;
      if (insNode->prev)
         insNode->prev->next=insNode;
      else
         pList->head=insNode;
      pList->tail=insNode;
   }
   return TRUE;
}

int AnyMovDLObject( pList,movNode,nextNode )
   ANYLIST *pList;
   ANYNODE *movNode,*nextNode;
{
   int i,j;

   if (movNode==nextNode)
      return TRUE;
   i=AnyDelDLObject(pList,movNode);
   j=AnyInsDLObject(pList,movNode,nextNode);
   return (i&j ? 1:0);
}

int AnyMovDLObjects( pList,movNode1st,movNodeLast,nextNode )
   ANYLIST *pList;
   ANYNODE *movNode1st,*movNodeLast,*nextNode;
{
   ANYNODE *pNode1stPrev,*pNodeLastNext;

   if (movNode1st==nextNode)
      return TRUE;
   if (movNode1st==movNodeLast)
      return AnyMovDLObject(pList,movNode1st,nextNode);

   pNode1stPrev=movNode1st->prev;
   pNodeLastNext=movNodeLast->next;
   if (nextNode) {
      if (nextNode==pList->head) {
         pList->head=movNode1st;
      } else {
         nextNode->prev->next=movNode1st;
         movNode1st->prev=nextNode->prev;
      }
      movNodeLast->next=nextNode;
      nextNode->prev=movNodeLast;
   } else {
      movNodeLast=pList->tail->next;
      pList->tail->next=movNode1st;
      movNode1st->prev=pList->tail;
      pList->tail=movNodeLast;
   }
   if (pNode1stPrev)  pNode1stPrev->next=pNodeLastNext;
   if (pNodeLastNext) pNodeLastNext->prev=pNode1stPrev;
   return TRUE;
}

int AnyDelDLObject( pList,pNode )
   ANYLIST *pList;
   ANYNODE *pNode;
{
   if (pNode==pList->head) {
      if (pNode->next) {
         pNode->next->prev=NULL;
         pList->head=pNode->next;
      } else {
         pList->head=
         pList->tail=NULL;
      }
   } else {
      pNode->prev->next=pNode->next;
      if (pNode->next)
         pNode->next->prev=pNode->prev;
      else
         pList->tail=pNode->prev;
   }
   return TRUE;
}

int AnyFindDLObject( pList,obj,find )
   ANYLIST *pList;
   ANYNODE **obj;
   IPTRFN find;
{
   ANYNODE *pNode;
   int i;

   *obj=NULL;
   i=0;
   pNode=pList->head;
   while (pNode) {
      i++;
      if ((*find)(pNode)) {
         *obj=pNode;
         break;
      }
      pNode=pNode->next;
   }
   return i;
}

int AnySortDLObject( pList,compare,exchange,sortingMethod) /* bubble sort */
   ANYLIST *pList;
   IPTRFN  compare,exchange;
   int sortingMethod; /* 1=ascending:..,3,2,1 ,0=descending:1,2,3,.. */
{
   register ANYNODE *pNode,*tail;

   sortingMethod=sortingMethod ? 1:-1;
   for (tail=pList->tail;pList->head!=tail;) {
      for (pNode=pList->head;pNode->next!=tail;) {
         if ((*compare)(pNode,pNode->next)*sortingMethod>0)
            (*exchange)(pList,pNode,pNode->next);
         else
            pNode=pNode->next;
      }
      if ((*compare)(pNode,tail)*sortingMethod>0)
         (*exchange)(pList,pNode,tail);
      else
         tail=pNode;
   }
   return TRUE;
}

int AnyCompDLObject( pList,compare )
/* return value is same as strcmp()
 */
   ANYLIST *pList;
   IPTRFN  compare;
{
   ANYNODE *tail,*pNode;
   int i=0;

   tail=pList->tail;
   while (tail) {
      pNode=pList->head;
      while (pNode
      &&     pNode!=tail) {
         if ((*compare)(pNode,pNode->next))  /* different */
            i++;
         pNode=pNode->next;
      }
      tail=tail->prev;
   }
   return i; /* 0: equal case, n: different node total */
}

/******************************************************************************/

static
int FreeToken( pNode )
   DLN *pNode;
{
   if (pNode->tok) free(pNode->tok);
   return TRUE;
}

int DLLOpen( ppList )
   DLL **ppList;
{
   int i;
   i=AnyOpenLinkedObject(ppList,sizeof(DLL));
   (*ppList)->total=0;
   return (i);
}

int DLLClose( pList )
   DLL *pList;
{
   return AnyCloseLinkedObject(pList,NULL);
}

int DLLCloseWMA( pList )
   DLL *pList;
{
   return AnyCloseLinkedObject(pList,FreeToken);
}

int DLLAddToken( pList,token )
   DLL *pList;
   char *token;
{
   DLN *pNode;
   int i;

   pNode=(DLN*)malloc(sizeof(DLN));
   pNode->tok=token;
   i=AnyAddDLObject(pList,pNode);
   pList->total++;
   return (i);
}

int DLLAddTokenWMA( pList,token )
   DLL *pList;
   char *token;
{
   DLN *pNode;
   int i;

   pNode=(DLN*)malloc(sizeof(DLN));
   pNode->tok=strdpl(token);
   i=AnyAddDLObject(pList,pNode);
   pList->total++;
   return (i);
}

int DLLAddTokens( pList,pLine,pSkip )
   DLL *pList;
   char *pLine,*pSkip;
{
   DLN *pNode;
   char *t;
   int i=0;

   do {
      t=strtok(pLine,pSkip);
      if (pLine) pLine=NULL;
      if (!t) break;
      pNode=(DLN*)malloc(sizeof(DLN));
      pNode->tok=t;
      AnyAddDLObject(pList,pNode);
      i++;
   } while(t);
   return pList->total=i;
}

int DLLAddTokensWMA( pList,pLine,pSkip ) /* with Memory Allocation */
   DLL *pList;
   char *pLine,*pSkip;
{
   DLN *pNode;
   char *t;
   int i=0;

   do {
      t=strtok(pLine,pSkip);
      if (pLine) pLine=NULL;
      if (!t) break;
      pNode=(DLN*)malloc(sizeof(DLN));
      pNode->tok=strdpl(t);
      AnyAddDLObject(pList,pNode);
      i++;
   } while(t);
   return pList->total=i;
}

int DLLDelNode( pList,pNode )
   DLL *pList;
   DLN *pNode;
{
   int bResult;

   bResult=AnyDelDLObject(pList,pNode);
   free(pNode);
   pList->total--;
   return bResult;
}

int DLLDelNodeWMA( pList,pNode )
   DLL *pList;
   DLN *pNode;
{
   FreeToken(pNode);
   return DLLDelNode(pList,pNode);
}

int DLLDelCommentNode( pList,comment )
   DLL *pList;
   char comment;
{
   DLN *pNode,*pNext;
   char *p;

   for (pNode=pList->head,
        pNext=pNode->next;
        pNode;
        pNode=pNext) {
      pNext=pNode->next;
      p=pNode->tok;
      skipwhite(&p);
      if (*p==comment) {
         if (!p[1] || isspace(p[1]))
            do {
               pNext=pNode->next;
               DLLDelNode(pList,pNode);
               pNode=pNext;
            } while (pNode);
         else
            DLLDelNode(pList,pNode);
      }
   }
   return TRUE;
}

int DLLDelCommentNodeWMA( pList,comment )
   DLL *pList;
   char comment;
{
   DLN *pNode,*pNext;
   char *p;

   for (pNode=pList->head,pNext=pNode->next;pNode;
        pNode=pNext,pNext=pNode?pNode->next:NULL) {
      p=pNode->tok;
      skipwhite(&p);
      if (*p==comment) {
         if (!p[1] || isspace(p[1]))
            do {
               pNext=pNode->next;
               DLLDelNode(pList,pNode);
               pNode=pNext;
            } while (pNode);
         else
            DLLDelNodeWMA(pList,pNode);
      }
   }
   return TRUE;
}

int DLLDelInvalidNodeWMA( pList,deleteBoolFn )
   DLL *pList;
   IPTRFN deleteBoolFn;
{
   DLN *pNode,*pNext;

   pNode=pList->head;
   while (pNode) {
      if ((*deleteBoolFn)(pNode)) { /* if return=true */
         pNext=pNode->next;
         DLLDelNodeWMA(pList,pNode);
         pNode=pNext;
      } else
         pNode=pNode->next;
   }
   return TRUE;
}

int DLLInsToken( pList,pNode,token )
   DLL *pList;
   DLN *pNode;
   const char *token;
{
   int i,j;
   i=DLLAddToken(pList,token);
   j=AnyMovDLObject(pList,pList->tail,pNode);
   return (i&j ? 1:0);
}

int DLLInsTokenWMA( pList,pNode,token )
   DLL *pList;
   DLN *pNode;
   const char *token;
{
   int i,j;
   i=DLLAddTokenWMA(pList,token);
   j=AnyMovDLObject(pList,pList->tail,pNode);
   return (i&j ? 1:0);
}

int DLLGetStringLength( pList )
   DLL *pList;
{
   DLN *pNode;
   int i,j;

   for (i=1,j=0,pNode=pList->head;
        i<=pList->total;
        i++,pNode=pNode->next)
     j+=strlen(pNode->tok);
   return j;
}

int DLLDuplicate( pList,ppCloneList )
   DLL *pList,**ppCloneList;
{
   DLN *pNode,*pCloneNode;
 
   (*ppCloneList)=(DLL*)malloc(sizeof(DLL));
   (*ppCloneList)->head=(*ppCloneList)->tail=NULL;
   (*ppCloneList)->total=pList->total;
   pNode=pList->head;
   while (pNode) {
      pCloneNode=(DLN*)malloc(sizeof(DLN));
      pCloneNode->tok=strdpl(pNode->tok);
      AnyAddDLObject(*ppCloneList,pCloneNode);
      pNode=pNode->next;
   }
   return TRUE;
}

int DLLGetItFrStream( qStream,cComment,qDelimiter,ppList )
   const char *qStream,cComment,*qDelimiter;
   DLL **ppList;
{
   char *pFence,*pStart,*pEnd,*pAddr;
   DLL *pList;
   DLN *pNode;

   DLLOpen(ppList);
   pFence=(char*)qStream+strlen(qStream);
   pStart=(char*)qStream;
   do {
      if (pEnd=strchr(pStart,'\n'))
         *pEnd=(char)0;
      else
         pEnd=pStart+strlen(pStart);
      DLLOpen(&pList);
      DLLGetTokensV1(pList,pStart,qDelimiter);
      for (pNode=pList->head;pNode;pNode=pNode->next) {
         pAddr=pNode->tok;
         skipwhite(&pAddr);
         if (*pAddr==cComment) {
            if (pAddr[1]) continue; /* comment for one token */
            else break;         /* comment up to end of pLine */
         }
         DLLAddTokenWMA(*ppList,pAddr);
      }
      DLLClose(pList);
      pStart=++pEnd;
      skipwhite(&pStart);
   } while (pStart<pFence);
   return TRUE;
}

int DLLGetItFrStreamEx( pStream,pStart,pEnd,ppList,nLineStart,nLineEnd )
   const char *pStream;
   char *pStart,*pEnd;
   DLL **ppList;
   int *nLineStart,*nLineEnd;
{
   int nSize;
   char *pTemp;
   DLN *pNode,*pOpen,*pClose;

   if (!strstr(pStream,pStart)) return FALSE;
   if (!strstr(pStream,pEnd)) return FALSE;

   DLLOpen(ppList);
   while (pStream[0]) {
      pTemp=strchr(pStream,'\n');
      nSize=pTemp ? pTemp-pStream:strlen(pStream);
      pNode=(DLN*)malloc(sizeof(DLN));
      if (nSize) {
         pNode->tok=(char*)malloc(nSize+1);
         memcpy(pNode->tok,pStream,nSize);
         pNode->tok[nSize]=(char)0;
      } else {
         pNode->tok=strdpl(" ");
      }
      AnyAddDLObject(*ppList,pNode);
      (*ppList)->total++;
      pStream+=nSize;
      pStream++;
      if (!pStream[-1]) break;
   }
   *nLineStart=0;
   *nLineEnd=0;
   pOpen=NULL;
   pClose=NULL;
   for (pNode=(*ppList)->head;pNode;pNode=pNode->next) {
      (*nLineStart)++;
      if (strstr(pNode->tok,pStart)) {
         *nLineEnd=*nLineStart-1;
         pOpen=pNode;
         for (;pNode;pNode=pNode->next) {
            (*nLineEnd)++;
            if (strstr(pNode->tok,pEnd)) {
               pClose=pNode;
               break;
            }
         }
         break;
      }
   }
   if (pOpen
   &&  pClose) {
      pNode=pOpen->prev;
      while (pNode) {
         AnyDelDLObject(*ppList,pNode);
         free(pNode->tok);         
         (*ppList)->total--;
         pNode=pNode->prev;
      }
      pNode=pClose->next;
      while (pNode) {
         AnyDelDLObject(*ppList,pNode);
         free(pNode->tok);
         (*ppList)->total--;
         pNode=pNode->next;
      }
      return TRUE;
   } else {
      DLLCloseWMA(*ppList);
      *ppList=NULL;
      *nLineStart=0;
      *nLineEnd=0;
      return FALSE;
   }
}

int DLLPutItToStream( pList,ppStream )
   DLL *pList;
   char **ppStream;
{
   int nLength;
   DLN *pNode;
   char *pStream;

   nLength=DLLGetStringLength(pList);
   nLength+=pList->total; /* space */
   pStream=*ppStream=salloc(char,nLength+1);
   for (pNode=pList->head;pNode!=pList->tail->next;pNode=pNode->next) {
      strcpy(pStream,pNode->tok);
      pStream+=strlen(pNode->tok);
      pStream[0]=' ';
      pStream++;
   }
   nLength=strlen(*ppStream);
   return nLength;
}

int DLLGetItFrFile( qFileName,comment,delimiter,pList )
   char *qFileName,comment,*delimiter;
   DLL *pList;
{
   FILE *f;
   char *buf1024,*p;
   DLL *l;
   DLN *n;

   f=fopen(qFileName,"r");
   if (!f)
      return FALSE;
   buf1024=(char*)malloc((unsigned int)(1024*sizeof(char)));
   DLLOpen(&l);
   while(fgets(buf1024,1024,f)) {
      DLLGetTokensV1(l,buf1024,delimiter);
      for (n=l->head;n;n=n->next) {
         p=n->tok;
         skipwhite(&p);
         if (*p==comment) {
            if (p[1]) continue; /* comment for one token */
            else break;         /* comment up to end of line */
         }
         DLLAddTokenWMA(pList,p);
         pList->total++;
      }
      l->total=0;
      l->head=l->tail=NULL;
   }
   DLLClose(l); 
   free(buf1024);
   fclose(f);
   return TRUE;
}

int DLLPutItToFile( pList,qFileName )
   DLL *pList;
   char *qFileName;
{
   char *pStream;
   pStream=0;
   return myStreamToFile(qFileName,pStream);
}

int DLLRun( pList,pFunc )
   DLL *pList;
   IPTRFN pFunc;
{
   DLN *pNode;

   pNode=pList->head;
   while (pNode) {
      (*pFunc)(pNode->tok);
      pNode=pNode->next;
   }
   return TRUE;
}

int DLLPrintToStdout( pList )
   DLL *pList;
{
   DLN *pNode;

   fprintf(stdout,"---------- DLL ----------\n");
   fprintf(stdout,"[head=%p][tail=%p] : total=%d\n",pList->head,pList->tail,pList->total);
   pNode=pList->head;
   while (pNode) {
      fprintf(stdout,"[%p] p=%p n=%p <%s>\n",
         pNode,pNode->prev,pNode->next,pNode->tok);
      pNode=pNode->next;
   }
   fprintf(stdout,"-------------------------\n");
   return TRUE;
}

int DLLPrintToFile( pList,qFileName )
   DLL *pList;
   const char *qFileName;
{
   FILE *pFile;
   DLN *pNode;
   int nIndex,nID;

   pFile=fopen(qFileName,"w");
   fprintf(pFile,"---------- DLL ----------\n");
   fprintf(pFile,"[head=%p][tail=%p] : total=%d\n",pList->head,pList->tail,pList->total);
   pNode=pList->head;
   while (pNode) {
      nIndex=strlen(pNode->tok)+1+sizeof(int);
      if ((pNode->tok)[nIndex]==0
         &&(pNode->tok)[nIndex+1]==0) {
         nID=*(int*)(pNode->tok+strlen(pNode->tok)+1);
         fprintf(pFile,"[%p] p=%p n=%p <%s>\tID=%d\n",
            pNode,pNode->prev,pNode->next,pNode->tok,nID);
      } else
         fprintf(pFile,"[%p] p=%p n=%p <%s>\n",
            pNode,pNode->prev,pNode->next,pNode->tok);
      pNode=pNode->next;
   }
   fprintf(pFile,"-------------------------\n");
   fclose(pFile);
   return TRUE;
}

int DLLGetTokensV1( pList,pLine,pSkip )
   DLL *pList;
   char *pLine,*pSkip;
{
   char *p[256];
   int i,j,bInside=FALSE;

   for (i=j=0;pLine[i];i++)
      switch (pLine[i]) {
      case '\"' :
         if (pLine[i-1]!='\\' && pLine[i-2]!='\\')
            bInside=(!bInside) ? TRUE:FALSE;
         break;
      case ' '  :
         if (bInside) {
            pLine[i]='?';
            p[j]=pLine+i;
            j++;
         }
      } 
   i=DLLAddTokens(pList,pLine,pSkip);
   for (j--;j>=0;j--)
      *(p[j])=' ';
   return i;
}

int DLLGetMaxTokNoByWhite( pList )
   DLL *pList;
{
   DLN *pNode;
   char *p;
   register int i,j,k=0;

   for (i=1,pNode=pList->head;
        i<=pList->total;
        i++,pNode=pNode->next) {
      p=pNode->tok;
      j=0;
      while (*p) {
         skipwhite(&p);
         j++;
         skipblack(&p);
      }
      k=MAX(j,k);
   }
   return k;
}

/******************************************************************************/
/* any.c */
