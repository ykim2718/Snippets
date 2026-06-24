/******************************************************************************/
/*                           file name : plotse.c                             */
/*                         description : plot script editor                   */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43300423                             */
/* 4330 0423-0606,0618,0625,0814-0824,____,____,____,____,____,____,____,____ */
/* 4333 0331-0412,0502,0507,0626,0830-0924-1029,1114-1123,____,____,____,____ */
/* 4334 0209-0321,0815-0817,0824,____,____,____,____,____,____,____,____,____ */
/* 4336 0217,0907,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#if defined(_MSC_)
#include <assert.h>
#include <stdarg.h>
#endif
#include "myCore.h"
#include "str.h"
#include "tools.h"
#include "any.h"
#include "number.h"
#include "plot.h"
#include "plotse.h"

/******************************************************************************/

static
struct {
   char *name;
   enum { RW_LEVEL0=0,RW_LEVEL1=1,RW_LEVEL2=2,RW_LEVEL3=3,RW_LEVEL4=4,
      RW_LEVEL_MAX=4
   } level;
} RESERVEDWORDS[]={
   PLOTSCRIPT_BEGINNING, RW_LEVEL0, /* beginning block command => RWORDS[0] */
   PLOTSCRIPT_END,       RW_LEVEL0, /* endding block command   => RWORDS[1] */
   PLOTSCRIPT_GLOB,      RW_LEVEL1,
   PLOTSCRIPT_PLOT,      RW_LEVEL1,
   PLOTSCRIPT_GXFM,      RW_LEVEL2,
   PLOTSCRIPT_GTXT,      RW_LEVEL2,
   PLOTSCRIPT_GOUT,      RW_LEVEL2,
   PLOTSCRIPT_EXEC,      RW_LEVEL2,
   PLOTSCRIPT_ATTR,      RW_LEVEL2,
   PLOTSCRIPT_DATA,      RW_LEVEL2,
   PLOTSCRIPT_XYZB,      RW_LEVEL2,
   PLOTSCRIPT_SLCT,      RW_LEVEL2,
   PLOTSCRIPT_UFUN,      RW_LEVEL2,
   PLOTSCRIPT_AXIS,      RW_LEVEL2,
   PLOTSCRIPT_TEXT,      RW_LEVEL2,
   PLOTSCRIPT_VIEW,      RW_LEVEL2,
   PLOTSCRIPT_4UNDERSCORES,RW_LEVEL3,
   PLOTSCRIPT_TYPE,      RW_LEVEL3
};

static
char *ANTONYMTABLE[] = {
   "landscape","portrait",0,
   "genetic","moment","area","bar","pie","flat3d",0,
   "back","nbck",0,
   "xlin","xlog","xnormal","xserial",0,
   "ylin","ylog","ynormal",0,
   "zlin","zlog",0,
   "solid","hollow",0
};

static
struct {
   const char *qSource,*qTarget;
} PREDEFINEDMACROTABLE[] = {
   {"legn.t.size", "legn.t.height"},  /* slct */
   {"label.t.size","label.t.height"}, /* axis */
   {"title.t.size","title.t.height"}, /* axis */
   {"t.size",      "t.height"}        /* text */
};

#define PLOTSCRIPT_LINEEND "\r\n"

static SEDEFLIST *SEMacroList=NULL;
static SECMDTABLE *SECommandTable=NULL;

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

int SEOpen( pStream,ppList )
   const char *pStream;
   DLL **ppList;
{
   int nResult,nLineStart,nLineEnd,nLine,j;
   DLN *node,*pNext,*pDln;
   DLL *pDll;
   char *pAddr;
   
   if (!pStream || !*pStream) return FALSE;

   nResult=DLLGetItFrStreamEx(
      pStream,PLOTSCRIPT_BEGINNING,PLOTSCRIPT_END,ppList,&nLineStart,&nLineEnd);
   if (!nResult) return FALSE;
   for (node=(*ppList)->head,pNext=node->next,j=nLineStart;
        node;
        node=pNext,pNext=node?node->next:NULL,j++) {
      strtrim(node->tok);
      nResult=strlen(node->tok);
      if (!nResult) {
         DLLDelNodeWMA(*ppList,node);
         continue;
      }
      pAddr=strdplwid(node->tok,j);
      free(node->tok);
      node->tok=pAddr;
   }

   for (node=(*ppList)->head,pNext=node->next;node;
        node=pNext,pNext=node?node->next:NULL) { /* line */
      nLine=id_strwid(node->tok);
      if (!node->tok[0] ||
         (node->tok[0]==PLOTSCRIPT_COMMENT_CHAR && isspace(node->tok[1]))) {
         DLLDelNodeWMA(*ppList,node);
         continue;
      }
      j=strlen(node->tok);
      if ((node->tok)[j-1]=='\\'
         && (node->tok)[j-2]==' ') {
         if (node->next) {
            pAddr=node->next->tok;
            skipwhite(&pAddr);
            if (*pAddr=='\\') {
               (node->tok)[j-1]=0;
               strtrim(node->next->tok);
               pAddr=strvcat(node->tok,node->next->tok+1,NULL);
               DLLDelNodeWMA(*ppList,node->next);
               free(node->tok);
               node->tok=strdplwid(pAddr,nLine);
               free(pAddr);
               pNext=node->prev;
               continue;
            }
         }
      }
   }

   for (node=(*ppList)->head,pNext=node->next;node;
        node=pNext,pNext=node?node->next:NULL) { /* token */
      nLine=id_strwid(node->tok);
      DLLGetItFrStream(node->tok,PLOTSCRIPT_COMMENT_CHAR," \t\f\n",&pDll);
      switch (pDll->total) {
      case 0 : DLLCloseWMA(pDll);DLLDelNodeWMA(*ppList,node);continue;
      case 1 : DLLCloseWMA(pDll);continue;
      }
      for (pDln=pDll->head;pDln;pDln=pDln->next) {
         pAddr=strdplwid(pDln->tok,nLine);
         free(pDln->tok);
         pDln->tok=pAddr;
      }
      if (node==(*ppList)->head) {
         (*ppList)->head=pDll->head;
         pDll->tail->next=node;
         node->prev=pDll->tail;
      } else {
         pDll->head->prev=node->prev;
         pDll->tail->next=node;
         node->prev->next=pDll->head;
         node->prev=pDll->tail;
      }
      (*ppList)->total+=pDll->total;
      DLLDelNodeWMA(*ppList,node);
      free(pDll);
   }

   return TRUE;
}

int SEOpenThruFile( qFileName,ppList )
   const char *qFileName;
   DLL **ppList;
{
   char *pStream;
   int nResult;

   nResult=myFileToStream(qFileName,&pStream);
   if (!nResult) return nResult;
   nResult=SEOpen(pStream,ppList);
   free(pStream);
   return nResult;
}

int SEClose( pList )
   DLL *pList;
{
   return DLLCloseWMA(pList);
}

DLN *SEGetLastNodeUnderCurrentLevel( pList,pNodeCurrent,bIncludingCurrentLevel )
   DLL *pList;
   DLN *pNodeCurrent;
   int bIncludingCurrentLevel;
{
   DLN *node;
   int nLevelCurrent,nLevel;

   nLevelCurrent=SEGetReservedWordLevel(pNodeCurrent->tok);
   for (node=pNodeCurrent->next;node!=pList->tail;node=node->next) {
      nLevel=SEGetReservedWordLevel(node->tok);
      if (nLevel) {
         if (bIncludingCurrentLevel && nLevelCurrent>=nLevel)
            break;
         else if (!bIncludingCurrentLevel && nLevelCurrent>nLevel)
            break;
      }
   }
   return node->prev;
}

int SERemoveMacros( pList )
   DLL *pList;
{
   DLN *pNode,*pNext;
   int nResult,nIndex;

   SEMacroOpen();

   nResult=noof(PREDEFINEDMACROTABLE);
   for (nIndex=1;nIndex<=nResult;nIndex++) {
      SEMacroDefine(
         PREDEFINEDMACROTABLE[nIndex-1].qSource,
         PREDEFINEDMACROTABLE[nIndex-1].qTarget);
   }

   for (pNode=pList->head,pNext=pNode->next;pNode;
        pNode=pNext,pNext=pNode?pNode->next:NULL) {
      if (strequ(pNode->tok,PLOTSCRIPT_DEFINE)) {
         if (pNode->next && pNode->next->next) {
            SEMacroDefine(pNode->next->tok,pNode->next->next->tok);
            pNode=pNode->next->next;
         }
      }
      nResult=SEMacroRun(&(pNode->tok));
      if (nResult) {
         DLL *pDll;
         DLN *pDln;
         DLLGetItFrStream(pNode->tok,PLOTSCRIPT_COMMENT_CHAR," \t\f\n",&pDll);
         for (pDln=pDll->head;pDln;pDln=pDln->next) {
            DLLInsToken(pList,pNode,strdpl(pDln->tok));
         }
         DLLCloseWMA(pDll);
         DLLDelNodeWMA(pList,pNode);
      }
   }
   SEMacroClose();

   for (pNode=pList->head;pNode;pNode=pNode->next) {
      if (strequ(pNode->tok,PLOTSCRIPT_DEFINE)) {
         pNode=pNode->next->next->next;
         DLLDelNodeWMA(pList,pNode->prev->prev->prev);
         DLLDelNodeWMA(pList,pNode->prev->prev);
         DLLDelNodeWMA(pList,pNode->prev);
         pNode=pNode->prev;
      }
      if (strequ(pNode->tok,PLOTSCRIPT_UNDEF)) {
         pNode=pNode->next->next->next;
         DLLDelNodeWMA(pList,pNode->prev->prev->prev);
         DLLDelNodeWMA(pList,pNode->prev->prev);
         DLLDelNodeWMA(pList,pNode->prev);
         pNode=pNode->prev;
      }
   }
   return TRUE;
}

int SEReorderLevel2nd( pList )
   DLL *pList;
{
   const char *qPlot=PLOTSCRIPT_PLOT,*qAttr=PLOTSCRIPT_ATTR;
   int nResult,nLevel;
   DLN *node,*nodeTarget,*nodeAttr;
   DLN *pNodeBegin,*pNodeEnd,*pNode;

   /* RW_LEVEL2 & RW_LEVEL2 */
   nodeTarget=0;
   for (node=pList->head;node;node=node->next) {
      nLevel=SEGetReservedWordLevel(node->tok);
      switch (nLevel) {
      case RW_LEVEL1 :
         nodeTarget=node;
         continue;
      case RW_LEVEL2 :
         if (!nodeTarget) return FALSE;
         pNodeBegin=node;
         pNodeEnd=SEGetLastNodeUnderCurrentLevel(pList,pNodeBegin,1);
         if (pNodeBegin==pNodeEnd) break;
         for (pNode=nodeTarget->next;pNode && pNode!=node;pNode=pNode->next) {
            if (strequ(pNode->tok,pNodeBegin->tok)) {
               pNode=SEGetLastNodeUnderCurrentLevel(pList,pNode,1);
               AnyMovDLObjects(pList,pNodeBegin->next,pNodeEnd,pNode->next);
               DLLDelNodeWMA(pList,pNodeBegin);
               break;
            }
         }
         node=pNodeEnd->prev;
         break;
      }
   }

   /* "attr" */
   nResult=0;
   nodeTarget=0;
   for (node=pList->head;node;node=node->next) {
      if (strequ(node->tok,qPlot)) {
         nodeTarget=node;
         continue;
      }
      if (nodeTarget) {
         if (!strequ(node->tok,qAttr)) continue;
         nodeAttr=node;
         node=SEGetLastNodeUnderCurrentLevel(pList,nodeAttr,1);
         if (!node) continue;
         AnyMovDLObjects(pList,nodeAttr,node,nodeTarget->next);
         nResult++;
         nodeTarget=0;
      }
   }
   return nResult;
}

static
int IsExclusiveAmbiguity( const char *pOption,int nOptLength,const char *pString )
{
   int nIndex,nTotal,nFound;

   if (nOptLength<=0) nOptLength=strlen(pOption);
   nTotal=sizeof(ANTONYMTABLE)/sizeof(ANTONYMTABLE[0]);
   nFound=-1;
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      if (!ANTONYMTABLE[nIndex])
         continue;
      if (strnequ(pOption,ANTONYMTABLE[nIndex],nOptLength)) {
         nFound=nIndex;
         break;
      }
   }
   if (nFound==-1) return FALSE;
   for (nIndex=nFound,nIndex++;nIndex<nTotal;nIndex++) {
      if (!ANTONYMTABLE[nIndex])
         break;
      if (strnequ(pString,ANTONYMTABLE[nIndex],nOptLength))
         return TRUE;
   }
   for (nIndex=nFound,nIndex--;0<=nIndex;nIndex--) {
      if (!ANTONYMTABLE[nIndex])
         return FALSE;
      if (strnequ(pString,ANTONYMTABLE[nIndex],nOptLength))
         return TRUE;
   }
   return FALSE;
}

/* static */
int SEDeleteLevel4thAmbiguity ( pList )
   DLL *pList;
{
   DLN *node;
   int nLevel,nLength,nLengthOfTracerToken,bRepetition,bExclusive;
   DLN *pNode,*pNodeEnd,*pNodePrev,*pTracer;

   for (node=pList->head;node;node=node->next) {
      nLevel=SEGetReservedWordLevel(node->tok);
      if (nLevel==(int)RW_LEVEL4) {
         if (strnequ(node->tok,"file=",5)) continue; /* 2000.1122 */
         pNodeEnd=SEGetLastNodeUnderCurrentLevel(pList,node,0);
         nLength=SEGetOptionNameLength(node->tok,0);
         for (pNode=node;pNode!=pNodeEnd;pNode=pNode->next) {
            pTracer=pNode->next;
            nLengthOfTracerToken=SEGetOptionNameLength(pTracer->tok,0);
            if (nLength!=nLengthOfTracerToken) continue;
            bExclusive=IsExclusiveAmbiguity(node->tok,nLength,pTracer->tok);
            bRepetition=strnequ(pTracer->tok,node->tok,nLength);
            if (bRepetition || bExclusive) {
               pNodePrev=pTracer->prev;
               DLLDelNodeWMA(pList,pTracer);
               if (pTracer==pNodeEnd) pNodeEnd=pNodePrev;
               pNode=pNode->prev;
            }
         }
      }
   }
   return 0;
}

static
int SEStripPathOfTilde( char *pScript,int nScript )
{
   /* Remove ~ (Tilde:Home-Directory Mark) in path */

   char *pAddr,*pTilde,*p1st,*p2nd,*p3rd;
   int nIndex;

   pAddr=(char*)SEGetOptionValueString(
      NULL,pScript,
      PLOTSCRIPT_GLOB,1,
      PLOTSCRIPT_EXEC,1,"home=",1,
      0);
   if (!pAddr) return FALSE;
   pTilde=pAddr;
   if (pTilde[0]=='\"') {
      strdelete(pTilde,0,1);
      strdelete(pTilde,strlen(pTilde)-1,1);
   }
   strinsert(&pTilde,strlen(pTilde),"\\");
   for (nIndex=1;;nIndex++) {
      pAddr=(char*)SEGetOptionValueString(
         NULL,pScript,
         PLOTSCRIPT_GLOB,1,
         PLOTSCRIPT_EXEC,1,"file=",nIndex,
         0);
      if (!pAddr) break;
      strdelete(pAddr,0,1);
      strdelete(pAddr,strlen(pAddr)-1,1);
      p1st=strtokbyindex(pAddr,PLTOSCRIPT_PATH_DELIMITER,0);
      p2nd=strtokbyindex(pAddr,PLTOSCRIPT_PATH_DELIMITER,1);
      p3rd=strtokbyindex(pAddr,PLTOSCRIPT_PATH_DELIMITER,2);
      strtrim(p1st);
      strtrim(p2nd);
      strtrim(p3rd);
      if (p1st[0]==PLTOSCRIPT_HOMEPATH_CHAR) {
         strdelete(p1st,0,2);
         strinsert(&p1st,0,pTilde);
      }
      if (p2nd[0]==PLTOSCRIPT_HOMEPATH_CHAR) {
         strdelete(p2nd,0,2);
         strinsert(&p2nd,0,pTilde);
      }
      freeEx(pAddr);
      pAddr=strvcat(
         "file=\"",
         p1st,PLTOSCRIPT_PATH_DELIMITER,
         p2nd,PLTOSCRIPT_PATH_DELIMITER,
         p3rd,
         "\"",0);
      free(p1st);
      free(p2nd);
      free(p3rd);
      SESetOptionParameter(
         pScript,nScript,
         PLOTSCRIPT_GLOB,1,
         PLOTSCRIPT_EXEC,1,pAddr,nIndex,
         0);
      free(pAddr);
   }
   SESetOptionParameter(
      pScript,nScript,
      PLOTSCRIPT_GLOB,1,
      PLOTSCRIPT_EXEC,1,"home=*",1,
      0);
   free(pTilde);
   return TRUE;
}

static
int SEBlowOffGargamelGarbage( const char *qScript,int nScript )
{
   int nPlotCount,nIndex,bResult,nIndex2,nIndex3;
   char *pAddr;
   int *pGargamelIndexes,nGargamels;
   char **ppGargamels;

   nPlotCount=SEGetPlotCount(qScript);
   pGargamelIndexes=salloc(int,nPlotCount);
   for (nIndex=0;nIndex<nPlotCount;nIndex++) pGargamelIndexes[nIndex]=-1;

   /* pGargamelIndexes :
      Set up for Gargamel script execution index. */
   for (nIndex=0;nIndex<nPlotCount;nIndex++) {
      pAddr=(char*)SEGetOptionValueString(
         NULL,qScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_PLOT,nIndex+1,
         PLOTSCRIPT_DATA,1,"type=",1,
         0);
      bResult=pAddr ? tolower(*pAddr)=='s':FALSE;
      freeEx(pAddr);
      if (!bResult) continue;
      pGargamelIndexes[nIndex]=SEGetOptionValueInteger(
         -1,qScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_PLOT,nIndex+1,
         PLOTSCRIPT_DATA,1,"type=",1,"file=",1,
         0);
   }
   
   nGargamels=pGargamelIndexes[0];
   for (nIndex=0;nIndex<nPlotCount;nIndex++)
      nGargamels=MAX(nGargamels,pGargamelIndexes[nIndex]);
   nGargamels++;
   ppGargamels=salloc(char*,nGargamels);
   memset(ppGargamels,0,sizeof(char*)*nGargamels);

   /* ppGargamels :
      1. Set up for Gargamel script execution name.
      2. Clean up a futile script execution (Put an useless Gargamel script aside). */
   for (nIndex=0;nIndex<nPlotCount;nIndex++) {
      if (pGargamelIndexes[nIndex]<0) continue;
      nIndex2=pGargamelIndexes[nIndex];
      ppGargamels[nIndex2]=(char*)SEGetOptionValueString(
         NULL,qScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_GLOB,1,
         PLOTSCRIPT_EXEC,1,"file=",nIndex2+1,
         0);
   }

   /* Cast away a duplicated script execution */
   for (nIndex=0;nIndex<nGargamels;nIndex++) {
      if (!ppGargamels[nIndex]) continue;
      for (nIndex2=nIndex+1;nIndex2<nGargamels;nIndex2++) {
         if (!ppGargamels[nIndex2]) continue;
         if (strequ(ppGargamels[nIndex],ppGargamels[nIndex2])) {
            freeEx(ppGargamels[nIndex2]);
            for (nIndex3=0;nIndex3<nPlotCount;nIndex3++) {
               if (pGargamelIndexes[nIndex3]==nIndex2) {
                  pGargamelIndexes[nIndex3]=nIndex;
               }
            }
         }
      }
   }

   /* pGargamelIndexes :
      Sort and Normalize pGargamelIndexes to base 0. */
   {
   int nMin,nMax,nMin2;
   nMin=nMax=pGargamelIndexes[0];
   for (nIndex=0;nIndex<nPlotCount;nIndex++) {
      if (pGargamelIndexes[nIndex]<0) continue;
      nMin=MIN(nMin,pGargamelIndexes[nIndex]);
      nMax=MAX(nMax,pGargamelIndexes[nIndex]);
   }
   for (nIndex=0;nIndex<nPlotCount && nMin>=0;nIndex++) {
      pGargamelIndexes[nIndex]-=nMin;
   }
   nMax-=nMin;
   nMin=0+1;
   while (nMin<nMax) {
      nMin2=nMax;
      for (nIndex=0;nIndex<nPlotCount;nIndex++) {
         if (pGargamelIndexes[nIndex]<nMin) continue;
         nMin2=MIN(nMin2,pGargamelIndexes[nIndex]);
      }
      if (nMin2==nMin) { /* 2001.0824 */
         nMin++;
         continue;
      }
      for (nIndex=0;nIndex<nPlotCount;nIndex++) {
         if (nMin<pGargamelIndexes[nIndex]) {
            pGargamelIndexes[nIndex]-=nMin2-nMin;
         }
      }
      nMax-=nMin2-nMin;
      nMin++;
   }
   }

   /* pGargamels : Squeeze empty. */
   for (nIndex=0;nIndex<nGargamels;nIndex++) {
      if (!ppGargamels[nIndex] &&
         (bResult=(nGargamels-nIndex-1))>0) {
         memmove(ppGargamels+nIndex,ppGargamels+nIndex+1,
            sizeof(char*)*bResult);
         ppGargamels[nIndex+bResult]=(char*)0; /* act as nGargamels-- */
         nGargamels--;
         nIndex--;
      }
   }

   /* pGargamelIndexes :
      Set up for each PLOTSCRIPT_PLOT block */
   for (nIndex=0;nIndex<nPlotCount;nIndex++) {
      char *pNumber;
      if (pGargamelIndexes[nIndex]<0) continue;
      pNumber=itostr(pGargamelIndexes[nIndex],"%02d");
      pAddr=strvcat("file=",pNumber,0);
      freeEx(pNumber);
      SESetOptionParameter(
         qScript,nScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_PLOT,nIndex+1,
         PLOTSCRIPT_DATA,1,"type=script",1,pAddr,1,
         0);
      freeEx(pAddr);
   }

   /* ppGargamels : Set up for the PLOTSCRIPT_GLOB block */
   do {
      bResult=SEDelOptionParameter(
         qScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_GLOB,1,
         PLOTSCRIPT_EXEC,1,"file=",1,
         0);
   } while (bResult);
   for (nIndex=0,nIndex2=1;nIndex<nGargamels;nIndex++) {
      if (!ppGargamels[nIndex]) continue;
      pAddr=strvcat("file=",ppGargamels[nIndex],0);
      SESetOptionParameter(
         qScript,nScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_GLOB,1,
         PLOTSCRIPT_EXEC,1,pAddr,nIndex2++,
         0);
      freeEx(pAddr);
   }

   free(pGargamelIndexes);
   while (nGargamels--) freeEx(ppGargamels[nGargamels]);
   free(ppGargamels);

   return TRUE;
}

int SEGetSimpleScript( qScript,ppScript )
   const char *qScript;
   char **ppScript;
{
   DLL *pList;
   int nResult,nScript;

   SEOpen(qScript,&pList);
   SERemoveMacros(pList);
   SEReorderLevel2nd(pList);
   SEDeleteLevel4thAmbiguity(pList);
   nResult=DLLPutItToStream(pList,ppScript);
   SEClose(pList);

   /* mySetHeapDebugger(TRUE);myChkHeapDebugger(); */

   nScript=strlen(*ppScript)*2;
   *ppScript=myReAlloc(*ppScript,nScript);

   SEStripPathOfTilde(*ppScript,nScript);
   SEBlowOffGargamelGarbage(*ppScript,nScript);

   nResult=SEBeautifyScript(*ppScript,nScript,80);
   if (!nResult) {
      myFree(*ppScript);
      *ppScript=NULL;
   }
   
   /* myExeHeapDebugger();myChkHeapDebugger(FALSE); */

   return nResult;
}

/* Each script must be modified by SEGetSimpleScript() before SEMixUpScripts() */
int SEMixUpScripts( pScripts,ppScript,bRelayout )
   const char *pScripts;
   char **ppScript;
   int bRelayout;
{
   int nScriptLength,nScriptCount,nPlotCount,nScriptIndex,nPlotIndex,
      nPos,nLength,nIndex,bResult;
   char *pScript,*pAddr,*pTokBefore,*pTokAfter;

   *ppScript=0;
   nScriptLength=strlen(pScripts)*2;
   pScript=salloc(char,nScriptLength);
   strcpy(pScript,pScripts);

   nScriptCount=strcount(pScript,PLOTSCRIPT_BEGINNING);
   if (nScriptCount!=strcount(pScript,PLOTSCRIPT_END)) {
      freeEx(pScript);
      return FALSE;
   }

   /* Change the global text */
   SESetOptionParameter(
      pScript,nScriptLength,
      PLOTSCRIPT_BEGINNING,1,
      PLOTSCRIPT_GLOB,1,
      PLOTSCRIPT_GTXT,1,
      "txt=\"This sheet is reproduced by Gr. Mixer.\"",1,
      0);

   /* Change the plot data file into the full path */
   for (nScriptIndex=1;nScriptIndex<=nScriptCount;nScriptIndex++) {
      nPos=SEGetOptionPosition(pScript,PLOTSCRIPT_BEGINNING,nScriptIndex,0);
      nPlotCount=SEGetPlotCount(pScript+nPos);
      for (nPlotIndex=1;nPlotIndex<=nPlotCount;nPlotIndex++) {
         pAddr=(char*)SEGetOptionValueString(
            NULL,pScript,
            PLOTSCRIPT_BEGINNING,nScriptIndex,
            PLOTSCRIPT_PLOT,nPlotIndex,
            PLOTSCRIPT_DATA,1,"type=",1,
            0);
         bResult=pAddr ? strequ(pAddr,"script"):FALSE;
         freeEx(pAddr);
         if (!bResult) continue;
         pTokBefore=(char*)SEGetOptionValueString(
            NULL,pScript,
            PLOTSCRIPT_BEGINNING,nScriptIndex,
            PLOTSCRIPT_PLOT,nPlotIndex,
            PLOTSCRIPT_DATA,1,"type=",1,"file=",1,
            0);
         if (!pTokBefore) continue;
         nIndex=atoi(pTokBefore)+1; /* Always isnumstr(pTokBefore)==TRUE */
         pAddr=(char*)SEGetOptionValueString(
            NULL,pScript,
            PLOTSCRIPT_BEGINNING,nScriptIndex,
            PLOTSCRIPT_GLOB,1,
            PLOTSCRIPT_EXEC,1,"file=",nIndex,
            0);
         pTokAfter=strvcat("file=",pAddr,0);
         freeEx(pAddr);
         SESetOptionParameter(
            pScript,nScriptLength,
            PLOTSCRIPT_BEGINNING,nScriptIndex,
            PLOTSCRIPT_PLOT,nPlotIndex,
            PLOTSCRIPT_DATA,1,"type=script",1,pTokAfter,1,
            0);
         freeEx(pTokAfter);
         freeEx(pTokBefore);
      }
   }

   /* Remove the PLOTSCRIPT_GLOB block except first */
   pAddr=pScript;
   for (nScriptIndex=1;nScriptIndex<=nScriptCount;nScriptIndex++) {
      if (nScriptIndex==1) {
         do {
            bResult=SEDelOptionParameter(
               pScript,
               PLOTSCRIPT_BEGINNING,nScriptIndex,
               PLOTSCRIPT_GLOB,1,
               PLOTSCRIPT_EXEC,1,"file=",1,
               0);
         } while (bResult);
         continue;
      }
      nPos=SEGetOptionPosition(
         pAddr,
         PLOTSCRIPT_BEGINNING,nScriptIndex,
         PLOTSCRIPT_GLOB,1,0);
      nLength=SEGetOptionBlockLength(pAddr,nPos);
      strdelete(pAddr,nPos,nLength);
   }

   /* Remove the PLOTSCRIPT_BEGINNING and PLOTSCRIPT_END in the middle */
   pAddr=pScript;
   for (nScriptIndex=1;nScriptIndex<=nScriptCount;nScriptIndex++) {
      pAddr=strstr(pAddr,PLOTSCRIPT_BEGINNING);
      if (nScriptIndex==1) {
         pAddr++;
         continue;
      }
      strdel(pAddr,pAddr,strlen(PLOTSCRIPT_BEGINNING));
   }
   pAddr=pScript;
   for (nScriptIndex=1;nScriptIndex<nScriptCount;nScriptIndex++) {
      pAddr=strstr(pAddr,PLOTSCRIPT_END);
      strdel(pAddr,pAddr,strlen(PLOTSCRIPT_END));
   }

   /* Modify "file=" of each PLOTSCRIPT_PLOT */
   nPos=SEGetOptionPosition(pScript,PLOTSCRIPT_BEGINNING,1,0);
   nPlotCount=SEGetPlotCount(pScript+nPos);
   for (nPlotIndex=1,nIndex=1;nPlotIndex<=nPlotCount;nPlotIndex++) {
      pAddr=(char*)SEGetOptionValueString(
         NULL,pScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_PLOT,nPlotIndex,
         PLOTSCRIPT_DATA,1,"type=",1,
         0);
      bResult=pAddr ? strequ(pAddr,"script"):FALSE;
      freeEx(pAddr);
      if (!bResult) continue;
      pTokBefore=(char*)SEGetOptionValueString(
         NULL,pScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_PLOT,nPlotIndex,
         PLOTSCRIPT_DATA,1,"type=",1,"file=",1,
         0);
      strinsert(&pTokBefore,0,"file=");
      SESetOptionParameter(
         pScript,nScriptLength,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_GLOB,1,
         PLOTSCRIPT_EXEC,1,pTokBefore,nIndex,
         0);
      pTokAfter=strvcat("file=",pAddr=itostr(nIndex-1,"%02d"),0);
      freeEx(pAddr);
      nIndex++;
      SESetOptionParameter(
         pScript,nScriptLength,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_PLOT,nPlotIndex,
         PLOTSCRIPT_DATA,1,"type=script",1,pTokAfter,1,
         0);
      freeEx(pTokAfter);
      freeEx(pTokBefore);
   }

   if (bRelayout) {
      double dLeft,dRight,dTop,dBottom;
      char qBuffer[256];
      nPos=SEGetOptionPosition(pScript,PLOTSCRIPT_BEGINNING,1,0);
      nPlotCount=SEGetPlotCount(pScript+nPos);
      for (nPlotIndex=1;nPlotIndex<=nPlotCount;nPlotIndex++) {
         SEGetIndexedViewportForGrWizard(
            nPlotIndex,nPlotCount,&dLeft,&dRight,&dTop,&dBottom);
         sprintf(qBuffer,"x1=%1.2f",dLeft);
         SESetOptionParameter(
            pScript,nScriptLength,
            PLOTSCRIPT_BEGINNING,1,
            PLOTSCRIPT_PLOT,nPlotIndex,
            PLOTSCRIPT_VIEW,1,qBuffer,1,
            0);
         sprintf(qBuffer,"x2=%1.2f",dRight);
         SESetOptionParameter(
            pScript,nScriptLength,
            PLOTSCRIPT_BEGINNING,1,
            PLOTSCRIPT_PLOT,nPlotIndex,
            PLOTSCRIPT_VIEW,1,qBuffer,1,
            0);
         sprintf(qBuffer,"y1=%1.2f",dBottom);
         SESetOptionParameter(
            pScript,nScriptLength,
            PLOTSCRIPT_BEGINNING,1,
            PLOTSCRIPT_PLOT,nPlotIndex,
            PLOTSCRIPT_VIEW,1,qBuffer,1,
            0);
         sprintf(qBuffer,"y2=%1.2f",dTop);
         SESetOptionParameter(
            pScript,nScriptLength,
            PLOTSCRIPT_BEGINNING,1,
            PLOTSCRIPT_PLOT,nPlotIndex,
            PLOTSCRIPT_VIEW,1,qBuffer,1,
            0);
      }
   }

   SEGetSimpleScript(pScript,ppScript);
   freeEx(pScript);

   return TRUE;
}

char *SEGetDelegateName()
{
   return 0;
}

char *SEGetPlotName( qScript,nPlotIndex )
   const char *qScript;
   int nPlotIndex;
{
   char *pString,*pTemp;
   int nResult,nNameLength,nValueLength,nStart,nEnd;

   pString=salloc(char,16);
   sprintf(pString,"%d) ",nPlotIndex);
   /*
   switch (nPlotIndex%10) {
   case 1 : sprintf(pString,"%dst ",nPlotIndex);break;
   case 2 : sprintf(pString,"%dnd ",nPlotIndex);break;
   case 3 : sprintf(pString,"%drd ",nPlotIndex);break;
   default: sprintf(pString,"%dth ",nPlotIndex);break;
   }
   */

   nResult=SEGetOptionPosition(qScript,
      PLOTSCRIPT_PLOT,nPlotIndex,"axis",1,"type=x",1,"title=",1,0);
   if (nResult>=0) {
      nNameLength=SEGetOptionNameLength(qScript,nResult);
      nValueLength=SEGetOptionValueLength(qScript,nResult);
      nStart=nResult+nNameLength+1;
      nEnd=nStart+nValueLength-1;
      pTemp=strmid(qScript,nStart,nEnd);
   } else {
      pTemp=0;
   }
   pString=strvcat(pString,"X=",pTemp,0);
   freeEx(pTemp);

   nResult=SEGetOptionPosition(qScript,
      PLOTSCRIPT_PLOT,nPlotIndex,"axis",1,"type=y",1,"title=",1,0);
   if (nResult>=0) {
      nNameLength=SEGetOptionNameLength(qScript,nResult);
      nValueLength=SEGetOptionValueLength(qScript,nResult);
      nStart=nResult+nNameLength+1;
      nEnd=nStart+nValueLength-1;
      pTemp=strmid(qScript,nStart,nEnd);
   } else {
      pTemp=0;
   }
   pString=strvcat(pString,"  Y=",pTemp,0);
   freeEx(pTemp);

   nResult=SEGetOptionPosition(qScript,
      PLOTSCRIPT_PLOT,nPlotIndex,"text",1,"type=",1,"txt=",1,0);
   if (nResult>=0) {
      nNameLength=SEGetOptionNameLength(qScript,nResult);
      nValueLength=SEGetOptionValueLength(qScript,nResult);
      nStart=nResult+nNameLength+1;
      nEnd=nStart+nValueLength-1;
      pTemp=strmid(qScript,nStart,nEnd);
   } else {
      pTemp=0;
   }
   pString=strvcat(pString,"  Text=",pTemp,0);
   freeEx(pTemp);

   strtrim(pString);

   return pString;
}

int SEGetPlotCount( qScript )
   const char *qScript;
{
   int nPos;
   nPos=SEGetOptionPosition(qScript,PLOTSCRIPT_BEGINNING,1,0);
   nPos+=strlen(PLOTSCRIPT_BEGINNING);
   return SEGetOptionFrequencyInaRange(qScript,nPos,PLOTSCRIPT_PLOT);
}

int SEGetIndexedRectOnRect(
   double dWidth,double dHeight,double dWidthMargin,double dHeightMargin,
   int nIndexB1,int nTotal,
   double *pLeft,double *pRight,double *pTop,double *pBottom
   )
{
   double dUnitEdge,dRectWidth,dRectHeight,dXOrigin,dYOrigin;
   int nRow,nCol;

   dWidth-=dWidthMargin*2;
   dHeight-=dHeightMargin*2;

   dUnitEdge=sqrt(dWidth*dHeight/nTotal);
   nRow=(int)ceil(dHeight/dUnitEdge-0.5);
   nCol=(int)ceil(dWidth/dUnitEdge-0.5);
   while (nRow*nCol<nTotal) {
      dUnitEdge*=0.97;
      nRow=(int)ceil(dHeight/dUnitEdge-0.5);
      nCol=(int)ceil(dWidth/dUnitEdge-0.5);
   }

   dRectWidth=dWidth/nCol;
   dRectHeight=dHeight/nRow;
   if (dRectWidth<dRectHeight) dRectHeight=dRectWidth;
   else dRectWidth=dRectHeight;

   dXOrigin=dWidthMargin+(dWidth-dRectWidth*nCol)/2;
   dYOrigin=dHeight+dHeightMargin-(dHeight-dRectHeight*nRow)/2;

   *pLeft=dXOrigin+((nIndexB1-1)%nCol)*dRectWidth;
   *pRight=*pLeft+dRectWidth;
   *pTop=dYOrigin-((int)((nIndexB1-1)/nCol))*dRectHeight;
   *pBottom=*pTop-dRectHeight;

   return nRow*nCol;
}

int SEGetIndexedViewportForGrWizard(
   int nIndexB1,int nTotal,
   double *pLeft,double *pRight,double *pTop,double *pBottom
   )
{
   static struct {
      double x1,x2,y1,y2;
   }
   qViewport3x2[]={
      {0.20,0.45,0.70,0.90},
      {0.55,0.80,0.70,0.90},
      {0.20,0.45,0.40,0.60},
      {0.55,0.80,0.40,0.60},
      {0.20,0.45,0.10,0.30},
      {0.55,0.80,0.10,0.30}
   },
   qViewport2x2[]={
      {0.15,0.45,0.55,0.90},
      {0.55,0.85,0.55,0.90},
      {0.15,0.45,0.05,0.40},
      {0.55,0.85,0.05,0.40}
   },
   qViewport3x1[]={
      {0.30,0.70,0.70,0.97},
      {0.30,0.70,0.35,0.62},
      {0.30,0.70,0.00,0.27}
   },
   qViewport2x1[]={
      {0.30,0.70,0.55,0.90},
      {0.30,0.70,0.10,0.45}
   },
   qViewport1x1[]={
      {0.20,0.80,0.20,0.80}
   };
   double dOffset=(297./210-1)*0.5; /* portrait mode only */
   double dWidth,dHeight;
   int nResult;

   switch (nTotal) {
   case 1 :
      *pLeft=  qViewport1x1[0].x1;
      *pRight= qViewport1x1[0].x2;
      *pBottom=qViewport1x1[0].y1;
      *pTop=   qViewport1x1[0].y2;
      return 1;
   case 2 :
      nResult=(nIndexB1-1)%noof(qViewport2x1);
      *pLeft=  qViewport2x1[nResult].x1;
      *pRight= qViewport2x1[nResult].x2;
      *pBottom=qViewport2x1[nResult].y1;
      *pTop=   qViewport2x1[nResult].y2;
      return 2;
   case 3 :
      nResult=(nIndexB1-1)%noof(qViewport3x1);
      *pLeft=  qViewport3x1[nResult].x1;
      *pRight= qViewport3x1[nResult].x2;
      *pBottom=qViewport3x1[nResult].y1;
      *pTop=   qViewport3x1[nResult].y2;
      return 3;
   }

   nResult=SEGetIndexedRectOnRect(
      1.0,1.0+dOffset*2,0.1,0.1,nIndexB1,nTotal,
      pLeft,pRight,pTop,pBottom);
   *pBottom-=dOffset;
   *pTop-=dOffset;

   dWidth=*pRight-*pLeft;
   dHeight=*pTop-*pBottom;
   *pLeft+=dWidth*0.15;
   *pRight-=dWidth*0.1;
   *pTop-=dHeight*0.1;
   *pBottom+=dHeight*0.15;

   return nResult;
}

int SEDeleteIndexedPlotBlock(
   const char *qScript,int nPlotIndex
   )
{
   char *pPlotDataType,*pPlotDataFile;
   int nScript,nCount,nIndex;
   char *pAddr;

   nScript=strlen(qScript);
   pPlotDataType=(char*)SEGetOptionValueString(
      NULL,qScript,
      PLOTSCRIPT_BEGINNING,1,
      PLOTSCRIPT_PLOT,nPlotIndex,
      PLOTSCRIPT_DATA,1,
      PLOTSCRIPT_TYPE,1,
      0);
   pPlotDataFile=(char*)SEGetOptionValueString(
      NULL,qScript,
      PLOTSCRIPT_BEGINNING,1,
      PLOTSCRIPT_PLOT,nPlotIndex,
      PLOTSCRIPT_DATA,1,
      PLOTSCRIPT_TYPE,1,
      "file=",1,
      0);

   nIndex=SEGetOptionPosition(
      qScript,
      PLOTSCRIPT_BEGINNING,1,
      PLOTSCRIPT_PLOT,nPlotIndex,
      0);
   nCount=SEGetOptionBlockLength(qScript,nIndex);
   strdelete(qScript,nIndex,nCount);

   if (!pPlotDataFile) return TRUE; /* 20030224 */

   nCount=SEGetPlotCount(qScript);
   for (nIndex=1;nIndex<=nCount;nIndex++) {
      pAddr=(char*)SEGetOptionValueString(
         NULL,qScript,
         PLOTSCRIPT_BEGINNING,1,
         PLOTSCRIPT_PLOT,nIndex,
         PLOTSCRIPT_DATA,1,
         PLOTSCRIPT_TYPE,1,
         0);
      if (!pAddr) continue;
      switch (tolower(*pAddr)) {
      case 'f' : /* MATRIX_FILE */
      case 'u' : /* MATRIX_USERFUNCTION */
         freeEx(pAddr);
         break;
      case 'p' : /* MATRIX_PREVIOUS */
      case 'c' : /* MATRIX_CLONE */
         freeEx(pAddr);
         if (nIndex<nPlotIndex) continue;
         pAddr=(char*)SEGetOptionValueString(
            NULL,qScript,
            PLOTSCRIPT_BEGINNING,1,
            PLOTSCRIPT_PLOT,nPlotIndex,
            PLOTSCRIPT_DATA,1,
            PLOTSCRIPT_TYPE,1,
            "file=",1,
            0);
         if (strequ(pAddr,pPlotDataFile)) {
            freeEx(pAddr);
            pAddr=strvcat(PLOTSCRIPT_TYPE,"=",pPlotDataType,0);
            SESetOptionParameter(
               qScript,nScript,
               PLOTSCRIPT_BEGINNING,1,
               PLOTSCRIPT_PLOT,nIndex,
               PLOTSCRIPT_DATA,1,
               pAddr,1,
               0);
            nCount=0;
         }
         freeEx(pAddr);
         break;
      }
   }

   freeEx(pPlotDataType);
   freeEx(pPlotDataFile);

   SEBlowOffGargamelGarbage(qScript,nScript); /* 2001.0815 */

   return TRUE;
}

/******************************************************************************/


int SEMacroOpen()
{
   if (SEMacroList) SEMacroClose();
   SEMacroList=salloc(SEDEFLIST,1);
   SEMacroList->head=NULL;
   SEMacroList->tail=NULL;
   SEMacroList->nTotal=0;
   return TRUE;
}

int SEMacroClose()
{
   SEDEFNODE *node,*next;

   if (!SEMacroList) return FALSE;
   node=SEMacroList->head;
   while (node) {
      next=node->next;
      freeEx(node->src);
      freeEx(node->dst);
      free(node);
      node=next;
   }
   free(SEMacroList);
   SEMacroList=NULL;
   return TRUE;
}

int SEMacroDefine( src,dst )
   const char *src,*dst;
{
   SEDEFNODE *node;

   if (!SEMacroList) return FALSE;
   if (!src || !*src || !dst || !*dst) return FALSE;
   node=salloc(SEDEFNODE,1);
   node->next=NULL;
   node->src=strdpl(src);
   node->dst=strdpl(dst);
   strtrim(node->src);
   strtrim(node->dst);
   if ((node->src)[0]=='\"') {
      char *pAddr=node->src;
      int i=strlen(pAddr)-1;
      pAddr[0]=' ';
      if (pAddr[i]=='\"') pAddr[i]=' ';
      strtrim(pAddr);
   }
   if ((node->dst)[0]=='\"') {
      char *pAddr=node->dst;
      int i=strlen(pAddr)-1;
      pAddr[0]=' ';
      if (pAddr[i]=='\"') pAddr[i]=' ';
      strtrim(pAddr);
   }
   SEMacroRun(&(node->dst));
   AnyAddSLObject(SEMacroList,node);
   (SEMacroList->nTotal)++;
   return SEMacroList->nTotal;
}

int SEMacroRun( ppStringWID )
   char **ppStringWID;
{
   SEDEFNODE *node;
   int ID,nResult;
   char *pAddr;

   nResult=0;
   for (node=SEMacroList->head;node;node=node->next) {
      if (strstr(*ppStringWID,node->src)) {
         ID=id_strwid(*ppStringWID);
         strreplace(ppStringWID,node->src,node->dst);
         pAddr=strdplwid(*ppStringWID,ID);
         free(*ppStringWID);
         *ppStringWID=pAddr;
         nResult++;
      }
   }
   return nResult;
}

/******************************************************************************/

int SECmdOpen( total )
   int total;
{
   if (total<=0) total=32;
   SECommandTable=salloc(SECMDTABLE,1);
   SECommandTable->nTotal=(total>0) ? total:32;
   SECommandTable->pArray=salloc(SECMDELEM,SECommandTable->nTotal);
   memset(SECommandTable->pArray,0,sizeof(SECMDELEM)*SECommandTable->nTotal);
   return TRUE;
}

int SECmdClose()
{
   free(SECommandTable->pArray);
   free(SECommandTable);
   SECommandTable=NULL;
   return TRUE;
}


#if defined(_MSC_)
int SECmdSetProcedure( int first, ... ) 
{
   int id=first;
   va_list pArgs;

   va_start(pArgs,first);
   while (id>=0
   &&     id<SECommandTable->nTotal) {
      SECommandTable->pArray[id].pCommand=va_arg(pArgs,char *);
      SECommandTable->pArray[id].nSignificant=strlen(SECommandTable->pArray[id].pCommand);
      SECommandTable->pArray[id].pFunc=va_arg(pArgs,IPTRFN);
      id=va_arg(pArgs,int);
   }
   va_end(pArgs);
   return TRUE;
}
#elif defined(_UNIXC_) || defined(_HP715C_)
int SECmdSetProcedure( va_alist ) 
   va_dcl
{
   va_list pArgs;
   int id;

   va_start(pArgs);
   id=va_arg(pArgs,int);
   while (id>=0
   &&     id<SECommandTable->nTotal)) {
      SECommandTable->pArray[id].command=va_arg(pArgs,char *);
      SECommandTable->pArray[id].significant=strlen(SECommandTable->pArray[id].command);
      SECommandTable->pArray[id].fn=va_arg(pArgs,IPTRFN);
      id=va_arg(pArgs,int);
   }
   va_end(pArgs);
   return TRUE;
}
#else
#error Compiler type (_MSC_,_UNIXC_,...) should be defined.
#endif

int SECmdRun( pList,pClientData,pError )
   DLL *pList; /* input */
   char *pClientData; /* output */
   IPTRFN pError;
{
   DLN *node;
   char *tokString,*tokStr;
   int lastCommand=-1;
   int i;

   DLLRun(pList,(IPTRFN)strtrimwid);
   node=pList->head;
   while (node) {
      tokString=strdpl(node->tok);
      for (i=0;i<SECommandTable->nTotal;i++) {
         if (!SECommandTable->pArray[i].pCommand) continue;
         if (strnequ(tokString,SECommandTable->pArray[i].pCommand,
                               SECommandTable->pArray[i].nSignificant))
            break;
      }
      if (i>=SECommandTable->nTotal) {
         if (lastCommand<0
            || !SECommandTable->pArray[lastCommand].pCommand) {
            (*pError)(id_strwid(node->tok),tokString);
            free(tokString);
            return FALSE;
         }
         i=lastCommand;
         tokStr=tokString;
      } else {
         lastCommand=i;
         tokStr=tokString+strlen(SECommandTable->pArray[i].pCommand);
      }
      if (!(*(SECommandTable->pArray[i].pFunc))(pClientData,tokStr)) {
         (*pError)(id_strwid(node->tok),tokString);
         free(tokString);
         return FALSE;
      }
      node=node->next;
      free(tokString);
   }
   return TRUE;
}

/******************************************************************************/

int SEGetReservedWordLevel( pString )
   const char *pString;
{
   int nTotal=sizeof(RESERVEDWORDS)/sizeof(RESERVEDWORDS[0]);
   int nIndex,bResult;
   
   for (nIndex=0;nIndex<nTotal;nIndex++) {
      bResult=strnequ(
         pString,RESERVEDWORDS[nIndex].name,strlen(RESERVEDWORDS[nIndex].name));
      if (bResult)
         return RESERVEDWORDS[nIndex].level;
   }
   return RW_LEVEL_MAX;
}

char *SEGetNextOptionAddress _((
   const char *pScript
   ))
{
   char *pAddr=(char*)pScript;
   int nPos;

   switch (pAddr[0]) {
   case ' ' : case '\r' : case '\n' :
      skipwhite(&pAddr);
      break;
   case '\"' :
      while (1) {
         skipblack(&pAddr);
         if (!*pAddr) break;
         if (pAddr[-1]=='\"' && pAddr[-2]!='\\') {
            skipwhite(&pAddr);
            break;
         }
         skipwhite(&pAddr);
      }
      break;
   case '!' :
      if (isspace(pAddr[1])) {
         while (*pAddr && *pAddr!='\n') pAddr++;
         skipwhite(&pAddr);
      } else {
         pAddr++;
         nPos=SEGetOptionLength(pAddr,0);
         if (nPos>0) pAddr+=nPos;
      }
      break;
   default :
      /* 2001.0219
      if (strnequ(pAddr,PLOTSCRIPT_END,strlen(PLOTSCRIPT_END))) {
         return NULL;
      }
      */
      nPos=SEGetOptionLength(pAddr,0);
      if (nPos>0) {
         pAddr+=nPos;
         skipwhite(&pAddr);
      } else {
         return NULL;
      }
   }

   if (pAddr[0]=='!') pAddr=SEGetNextOptionAddress(pAddr);
   return pAddr;
}

#if defined(_MSC_)
int SEGetOptionPosition _((
   const char *pScript,
   const char *pOption,int nOption,
   ...
   ))
{
   va_list pArgs;
   int nOptLevel,nLevel,bResult,nLength,nLengthTemp,nPosition;
   char *pPointer;

   va_start(pArgs,pScript);
   pOption=(char*)va_arg(pArgs,const char*);
   nOption=va_arg(pArgs,int);
   nOptLevel=SEGetReservedWordLevel(pOption);
   nLength=0;
   pPointer=(char*)pScript;
   while (pOption && *pOption && nOption>0) {
      while (nOption--) {
         nLength=SEGetOptionNameLength(pOption,0);
         bResult=strnequ(pPointer,pOption,nLength);
         while (!bResult) {
            pPointer=SEGetNextOptionAddress(pPointer);
            if (!pPointer || !*pPointer) return -1;
            nLevel=SEGetReservedWordLevel(pPointer);
            if (nOptLevel>nLevel) return -1;
            nLengthTemp=SEGetOptionNameLength(pPointer,0);
            if (nLength!=nLengthTemp) continue;
            bResult=strnequ(pPointer,pOption,nLength);
         }
         nLength=SEGetOptionLength(pPointer,0);
         pPointer+=nLength;
      }
      pOption=va_arg(pArgs,char*);
      if (pOption) {
         nOption=va_arg(pArgs,int);
         if (!nOption) return -1; /* Y.Kim,20030217 */
         nOptLevel=SEGetReservedWordLevel(pOption);
      }
   }
   va_end(pArgs);
   nPosition=(int)(pPointer-pScript)-nLength;
   return nPosition;
}
#elif defined(_UNIXC_) || defined(_HP715C_)
int SEGetOptionPosition _((
   va_dcl
   ))
{
   return 0;
}
#else
#error Compiler type (_MSC_,_UNIXC_,...) should be defined.
#endif

int SEGetSafeOptionPosition _((
   const char *pScript,
   const char *pOption,int nOption,
   ...
   ))
{
   va_list pArgs;
   int nOptLevel,nLevel,bResult,nLength,nPosition;
   char *pPointer,*pTmp;

   va_start(pArgs,pScript);
   pOption=(char*)va_arg(pArgs,const char*);
   nOption=va_arg(pArgs,int);
   nOptLevel=SEGetReservedWordLevel(pOption);
   nLength=0;
   pPointer=(char*)pScript;
   while (pOption && *pOption && nOption>0) {
      nLength=SEGetOptionNameLength(pOption,0);
      while (nOption--) {
         bResult=strnequ(pPointer,pOption,nLength);
         while (!bResult) {
            pTmp=SEGetNextOptionAddress(pPointer);
            if (!pTmp || !*pTmp) {
               pPointer=pTmp;
               nLength=0;
               goto R;
            }
            pPointer=pTmp;
            nLevel=SEGetReservedWordLevel(pPointer);
            if (nOptLevel>nLevel) {
               nLength=0;
               goto R;
            }
            bResult=strnequ(pPointer,pOption,nLength);
         }
         nLength=SEGetOptionLength(pPointer,0);
         pPointer+=nLength;
      }
      pOption=va_arg(pArgs,char*);
      if (pOption) {
         nOption=va_arg(pArgs,int);
         nOptLevel=SEGetReservedWordLevel(pOption);
      }
   }
   va_end(pArgs);
R: nPosition=(int)(pPointer-pScript)-nLength;
   return nPosition;
}

int SEGet1stOptionPosition (
   const char *pScript,
   const char *pOption,
   int nStart /* The zero-based index of the first character */
   )
{
   int bResult;
   char *pPointer;

   pPointer=(char*)(pScript+nStart);
   if (!pOption || !*pOption) return -1;
   bResult=strnequ(pPointer,pOption,strlen(pOption));
   while (!bResult) {
      pPointer=SEGetNextOptionAddress(pPointer+1);
      if (!pPointer || !*pPointer) return -1;
      bResult=strnequ(pPointer,pOption,strlen(pOption));
   }
   return (int)(pPointer-pScript);
}

int SEGetOptionLength _((
   /* Option (Parameter) = OptionName + OptionValue */
   const char *pScript,
   int nStart
   ))
{
   char *pAddr=(char*)pScript+nStart;
   if (!pAddr[0] || isspace(pAddr[0])) return 0;
   while (pAddr[0] && !isspace(pAddr[0]) && pAddr[0]!='=') pAddr++;
   if (!pAddr[0]) {
      return (int)(pAddr-pScript);
   } else if (pAddr[0]=='=') {
      if (pAddr[1]=='\"') {
         while (1) {
            skipblack(&pAddr);
            if (!*pAddr) break;
            if (pAddr[-1]=='\"' && pAddr[-2]!='\\') break;
            skipwhite(&pAddr);
         }
      } else {
         skipblack(&pAddr);
      }
   } else {
      skipblack(&pAddr);
   }
   return (int)(pAddr-(pScript+nStart));
}

int SEGetOptionNameLength _((
   /* Option (Parameter) = OptionName + OptionValue */
   const char *pScript,
   int nStart
   ))
{
   char *pAddr=(char*)pScript+nStart;
   if (!pAddr || !pAddr[0] || isspace(pAddr[0])) return 0;
   while (pAddr[0] && !isspace(pAddr[0]) && pAddr[0]!='=') pAddr++;

   return (int)(pAddr-pScript)-nStart; /* excluding '=' */
}

int SEGetOptionValueLength _((
   /* Option (Parameter) = OptionName + OptionValue */
   const char *pScript,
   int nStart
   ))
{
   int nOptLength=SEGetOptionLength(pScript,nStart);
   int nNameLength=SEGetOptionNameLength(pScript,nStart)+1;

   return (nOptLength-nNameLength);
}

int SEGetOptionBlockLength _((
   const char *pScript,
   int nStart
   ))
{
   int nLength;
   char *pPointer,*pNext;
   int nBaseLevel,nLevel;

   assert(nStart>=0);

   nLength=strlen(pScript);
   if (nLength<=nStart) return 0;
   pPointer=(char*)pScript+nStart;
   if (isspace(pPointer[0])) return 0;
   nBaseLevel=SEGetReservedWordLevel(pPointer);
   nLevel=nBaseLevel+1;
   while (nBaseLevel<nLevel) {
      pNext=SEGetNextOptionAddress(pPointer);
      if (!pNext) goto R;
      pPointer=pNext;
      nLevel=SEGetReservedWordLevel(pPointer);
   }
R: nLength=(int)(pPointer-((char*)pScript+nStart));
   return nLength;
}

int SEGetOptionFrequencyInaRange(
   const char *pScript,
   int nStart,
   const char *pOption
   )
{
   int bSet,nCount,nOptionLevel,nOptionLength,nLevel;
   char *pAddr=(char*)pScript+nStart,*pNext;

   bSet=0;
   nCount=0;
   nOptionLevel=SEGetReservedWordLevel(pOption);
   nOptionLength=strlen(pOption);
   pNext=pAddr;
   while (pNext) {
      pAddr=pNext;
      if (strnequ(pAddr,pOption,nOptionLength))
         nCount++;
      nLevel=SEGetReservedWordLevel(pAddr);
      if (nLevel<nOptionLevel && bSet) return nCount;
      bSet=1;
      pNext=SEGetNextOptionAddress(pAddr);
   }
   return nCount;
}

int SEBeautifyScript(
   char *pScript,
   int nScriptLength, /* must have enough extra space. */
   int nLineLength
   )
{
   int nScriptCount,nLineCount,nInsert,nLength,nLevel,nIndex,bLastTurn;
   char *pCloneStart,*pCloneEnd,*pCloneTracer;
   char *pScriptTracer;

   if (!*pScript || !strlen(pScript) || !nScriptLength ) return 0;
   if ((int)strlen(pScript)>nScriptLength ) return 0;

   strtrim(pScript);
   pCloneStart=strdpl(pScript);
   pCloneEnd=strlen(pScript)+pCloneStart;
   pCloneTracer=pCloneStart;
   memset(pScript,0,nScriptLength);
   pScriptTracer=pScript;

   bLastTurn=FALSE;
   nLineCount=0;
   do {
      nLength=SEGetOptionLength(pCloneTracer,0);
      nLevel=SEGetReservedWordLevel(pCloneTracer);
      switch (nLevel) { /* Check beforehand. */
      case RW_LEVEL0 :
         nInsert=4; /* \r\n\r\n */
         nLineCount=nLength;
         break;
      case RW_LEVEL1 :
         nInsert=4; /* \r\n\r\n */
         nLineCount=nLength;
         break;
      case RW_LEVEL2 :
         nInsert=2+1;
         nLineCount=1+nLength;
         break;
      case RW_LEVEL3 :
         nInsert=2+3;
         nLineCount=3+nLength;
         break;
      default :
         nInsert=1;
         nLineCount+=nInsert+nLength;
         if (nLineCount>nLineLength) {
            nInsert=2+8;
            nLineCount=8+nLength; /* 20030907 */
         }
      }
      nScriptCount=(int)(pScriptTracer-pScript)+nInsert+nLength;
      if (nScriptCount>nScriptLength) {
         pScriptTracer[0]=0;
         return 0;
      }
      switch (nLevel) {
      case RW_LEVEL0 :
         if (!strncmp(pCloneTracer,PLOTSCRIPT_BEGINNING,nLength))
            break;
         bLastTurn=TRUE;
         pScriptTracer[0]='\r';
         pScriptTracer[1]='\n';
         pScriptTracer[2]='\r';
         pScriptTracer[3]='\n';
         pScriptTracer+=nInsert;
         break;
      case RW_LEVEL1 :
         pScriptTracer[0]='\r';
         pScriptTracer[1]='\n';
         pScriptTracer[2]='\r';
         pScriptTracer[3]='\n';
         pScriptTracer+=nInsert;
         break;
      case RW_LEVEL2 :
      case RW_LEVEL3 :
         if (pScriptTracer[-2]!='\r' &&
            pScriptTracer[-1]!='\n') {
            pScriptTracer[0]='\r';
            pScriptTracer[1]='\n';
         }
         for (nIndex=2;nIndex<nInsert;nIndex++) {
            pScriptTracer[nIndex]=' ';
         }
         pScriptTracer+=nInsert;
         break;
      default :
         if (nInsert==1) {
            pScriptTracer[0]=' ';
            pScriptTracer++;
            break;
         }
         pScriptTracer[0]='\r';
         pScriptTracer[1]='\n';
         for (nIndex=2;nIndex<nInsert;nIndex++) {
            pScriptTracer[nIndex]=' ';
         }
         pScriptTracer+=nInsert;
      }
      memcpy(pScriptTracer,pCloneTracer,nLength);
      pScriptTracer+=nLength;
      pScriptTracer[0]=0;
   } while (!bLastTurn && (pCloneTracer=SEGetNextOptionAddress(pCloneTracer)));

   free(pCloneStart);
   strtrim(pScript);
   return strlen(pScript);
}

const char *SEGetOptionValueAddress (
   const char *pScript,
   const char *pOption,int nOption,
   ...
   )
{
   va_list pArgs;
   int nPosition,nResult;

   nPosition=0;
   va_start(pArgs,nOption);
   while (pOption && *pOption) {
      nResult=SEGetOptionPosition(pScript+nPosition,pOption,nOption,0);
      if (nResult<0) return NULL;
      nPosition+=nResult;
      pOption=va_arg(pArgs,const char*);
      nOption=va_arg(pArgs,int);
   }
   va_end(pArgs);
   nResult=SEGetOptionNameLength(pScript,nPosition);
   return pScript+nPosition+nResult+1;
}

char *SEGetOptionValueString (
   const char *pDefault,
   const char *pScript,
   const char *pOption,int nOption,
   ...
   )
{
   va_list pArgs;
   int nPosition,nResult;

   nPosition=0;
   va_start(pArgs,nOption);
   while (pOption && *pOption) {
      nResult=SEGetOptionPosition(pScript+nPosition,pOption,nOption,0);
      if (nResult<0)
         return pDefault && *pDefault ? strdpl(pDefault):NULL;
      nPosition+=nResult;
      pOption=va_arg(pArgs,const char*);
      nOption=va_arg(pArgs,int);
   }
   va_end(pArgs);
   nPosition+=SEGetOptionNameLength(pScript,nPosition);
   nResult=SEGetOptionValueLength(pScript,nPosition);
   return strmiddle(pScript,nPosition+1,nResult);
}

double SEGetOptionValueFloating (
   double nDefault,
   const char *pScript,
   const char *pOption,int nOption,
   ...
   )
{
   va_list pArgs;
   int nPosition,nResult,nNameLength;
   char *pAddr;

   nPosition=0;
   va_start(pArgs,nOption);
   while (pOption && *pOption) {
      nResult=SEGetOptionPosition(pScript+nPosition,pOption,nOption,0);
      if (nResult<0) return nDefault;
      nPosition+=nResult;
      pOption=va_arg(pArgs,const char*);
      nOption=va_arg(pArgs,int);
   }
   va_end(pArgs);
   nNameLength=SEGetOptionNameLength(pScript,nPosition);
   pAddr=(char*)(pScript+nPosition+nNameLength+1);
   if (isnumstr(pAddr)) return atof(pAddr); /* 2001.0815 */
   else return nDefault;
}

int SEGetOptionValueInteger (
   int nDefault,
   const char *pScript,
   const char *pOption,int nOption,
   ...
   )
{
   va_list pArgs;
   int nPosition,nResult,nNameLength;
   char *pAddr;

   /*
   va_list pTemp;
   double dReturn;
   va_start(pArgs,nDefault);
   pScript=va_arg(pArgs,const char*);
   pOption=va_arg(pArgs,const char*);
   nOption=va_arg(pArgs,int);
   pTemp=va_arg(pArgs,va_list);
   pArgs-=(pTemp-pArgs);
   dReturn=SEGetOptionValueFloating(
      (double)nDefault,pScript,pOption,nOption,pArgs);
   va_end(pArgs);
   return (int)dReturn;
   */
   nPosition=0;
   va_start(pArgs,nOption);
   while (pOption && *pOption) {
      nResult=SEGetOptionPosition(pScript+nPosition,pOption,nOption,0);
      if (nResult<0) return nDefault;
      nPosition+=nResult;
      pOption=va_arg(pArgs,const char*);
      nOption=va_arg(pArgs,int);
   }
   va_end(pArgs);
   nNameLength=SEGetOptionNameLength(pScript,nPosition);
   pAddr=(char*)(pScript+nPosition+nNameLength+1);
   if (isnumstr(pAddr)) return (int)atof(pAddr); /* 2001.0815 */
   else return nDefault;
}

int SESetOptionParameter(
   const char *pScript,int nScript,
   const char *pOption,int nOption,
   ...)
{
   va_list pArgs;
   int nMargin,nResult,nIndex,nOptionNameLength;

   va_start(pArgs,pScript);
   nScript=va_arg(pArgs,int);
   nMargin=nScript-strlen(pScript)-1;
   if (nMargin<0) return FALSE;
   pOption=va_arg(pArgs,char*);
   nOption=va_arg(pArgs,int);
   nOptionNameLength=SEGetOptionNameLength(pOption,0);

   nIndex=0;
   while (pOption && *pOption) {
      nResult=SEGetOptionPosition(pScript+nIndex,pOption,nOption,0);
      if (nResult<0) {
         /* if (nOption!=1) return FALSE; 2000.1124 */
         nResult=SEGetSafeOptionPosition(pScript+nIndex,pOption,nOption,0);
         nIndex+=nResult;
         nMargin-=strlen(pOption)+1;
         if (nMargin<0) return FALSE;
         if (nIndex!=(int)strlen(pScript)) {
            strins(pScript,pScript+nIndex," ");
            strins(pScript,pScript+nIndex,pOption);
         } else {
            strins(pScript,pScript+nIndex,pOption);
            strins(pScript,pScript+nIndex," ");
         }
      } else {
         nIndex+=nResult;
         nResult=strnequ(pScript+nIndex,pOption,nOptionNameLength);
         if (nResult) {
            nResult=SEGetOptionLength(pScript,nIndex);
            nMargin-=strlen(pOption)-nResult;
            if (nMargin<0) return FALSE;
            strdel(pScript,pScript+nIndex,nResult);
            strins(pScript,pScript+nIndex,pOption);
         }
      }
      nIndex+=strlen(pOption);
      pOption=va_arg(pArgs,char*);
      nOption=va_arg(pArgs,int);
      nOptionNameLength=SEGetOptionNameLength(pOption,0);
   }
   va_end(pArgs);
#if defined(_MSC_)
   assert((int)(strlen(pScript)+1)==(nScript-nMargin));
#endif
   return TRUE;
}

int SEDelOptionParameter (
   const char *pScript,
   const char *pOption,int nOption,
   ...
   )
{
   va_list pArgs;
   int nPosition,nResult;

   nPosition=0;
   va_start(pArgs,nOption);
   while (pOption && *pOption) {
      nResult=SEGetOptionPosition(pScript+nPosition,pOption,nOption,0);
      if (nResult<0) return FALSE;
      nPosition+=nResult;
      pOption=va_arg(pArgs,const char*);
      nOption=va_arg(pArgs,int);
   }
   va_end(pArgs);
   nResult=SEGetOptionLength(pScript,nPosition);
   strdel(pScript,pScript+nPosition,nResult);
   return TRUE;
}

/******************************************************************************/
/* plotse.c */
