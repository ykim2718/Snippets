/******************************************************************************/
/*                           file name : anyfind.c                            */
/*                         description : anyfind                              */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43310711                             */
/* 4331 0711-0916,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0403-0505-1203-____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0418-0529,0614,0701,0710,0808,____,____,____,____,____,____,____,____ */
/* 4334 0210-0217,0318,0410-0411,____,____,____,____,____,____,____,____,____ */
/* 4336 0209,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "myCore.h"
#include "str.h"
#include "any.h"
#include "number.h"
#include "tools.h"
#include "anyfind.h"
#include "parser.h"
#include "nr.h"

extern void errWarning();

/*----------------------------------------------------------------------------*/

#define SkipBlackWhite(ptr) skipblack(ptr);skipwhite(ptr);
#define IS_TRACKING_NODE(node) ((node)->nFirst==0 && (node)->nLast==1)
#define IS_EQUATION_NODE(node) ((node)->nDividerType==AF_EQUATION &&           \
                                (node)->nFirst==0 && (node)->nLast==0)

static char *AFErrorMessage=NULL;

static void AFSetErrorMessage _((
   char *sMessage,int bAttach
   ));
static int AFGetString2dAbsolutely _((
   AFLIST *pList,char *pStream,
   char * ***string2D,
   int *nrl,int *nrh,int *ncl,int *nch
   ));
static int AFGetString2dSequentially _((
   AFLIST *pList,char *pStream,
   char * ***string2D,
   int *nrl,int *nrh,int *ncl,int *nch
   ));
static int AFExtractWildly _((
   AFLIST *pList,char *pStream,
   char ****ppppString2d,
   int *nrl,int *nrh,int *ncl,int *nch
   ));
static int AFGetString2dByBlock _((
   AFLIST *pList,char *pStream,
   char ****ppppString2d,
   int *nrl,int *nrh,int *ncl,int *nch
   ));
static char *AFFindString _((
   const char *qString,const char *qSearchString,
   int nSearchStringLength
   ));
static char *AFDuplicateString _((
   const char *string,const char *pFormat,const char *pEquation,
   double dLc,double dUc
   ));
static void AFGetFirstToLastStrings _((
   AFNODEONETOONE *node,char *ptr,char **str1d0,int nTotal
   ));
static int AFChkRowNumber _((
   AFLIST *pList,char *pStream
   ));
static int AFChkColNumber _((
   AFLIST *pList
   ));
static int AFChkColNumberOfNode _((
   AFNODEONETOONE *node
   ));
static int AFChkSearchString(
   );
static int AFSetNullStrToMatrix(
   );
static int AFAddAnotherStringMatrix _((
   char ***mtxS,
   int nrlS,int nrhS,int nclS,int nchS,
   char ****mtxD,
   int *nrlD,int *nrhD,int *nclD,int *nchD,
   int isBottomAttachment,
   char *nullStr
   ));
static int AFReallocStringMatrix _((
   char ****mtx,
   int nrl,int nrh,int ncl,int nch,
   int nrhNew,int nchNew
   ));
static int AFAddStrToStrArray _((
   char ***array,int *arrayLength,int *nTotal,
   char *str
   ));
static int AFGetXYNoOfMatrix _((
   char ***matrix,
   int nrl,int nrh,int ncl,int nch,char *x,char *y,
   int *nr,int *nc
   ));
static int pDeleteFuncForOneToOneNode(
   );
static int pDeleteFuncForOneToManyNode(
   );
static int AFPostNumericProcessOnEachColumn _((
   int nType,
   char *pFormat,char ***pppString2d,
   int nrl,int *pNrh,int ncl,int nch
   ));
static int AFPostCompositeProcessOnEachColumn _((
   int nType,int nBlock,
   char *pFormat,char ****ppppString2d,
   int nrl,int *pNrh,int ncl,int nch
   ));
static int AFGetMaxFileCountPerSplit _((
   const char *qFileNames
   ));
static double AFGetVectorValueByType _((
   double *pVecB1,
   int nCount,int nType
   ));

/******************************************************************************/

int AFOpen(
   ppList,nSearchType,nDataUnitType,nNumericPostProcessType,
   bCaseSensitive,bComposite
   )
   AFLIST **ppList;
   int nSearchType,nDataUnitType,nNumericPostProcessType;
   int bCaseSensitive,bComposite;
{
   AnyOpenLinkedObject(ppList,sizeof(AFLIST));
   (*ppList)->nSearchType=nSearchType;
   (*ppList)->nDataUnitType=nDataUnitType;
   (*ppList)->nNumPostProcessType=nNumericPostProcessType;
   (*ppList)->bCaseSensitive=bCaseSensitive;
   (*ppList)->bComposite=bComposite;
   (*ppList)->nTotal=0;
   AFErrorMessage=0;
   return (1);
}

int AFClose( pList )
   AFLIST *pList;
{
   switch (pList->nSearchType) {
   case AF_ABSOLUTE:
   case AF_SEQUENTIAL:
   case AF_WILD:
      AnyCloseLinkedObject(pList,pDeleteFuncForOneToOneNode);
      break;
   case AF_BLOCK:
      AnyCloseLinkedObject(pList,pDeleteFuncForOneToManyNode);
      break;
   }
   if (AFErrorMessage) free(AFErrorMessage);
   return (1);
}

int AFAddNode( pList,nSearchType,qPattern,nDividerType )
   AFLIST *pList;
   int nSearchType;
   const char *qPattern;
   int nDividerType;
{
   int bResult=FALSE;

   if (nSearchType==AF_ABSOLUTE ||
       nSearchType==AF_SEQUENTIAL ||
       nSearchType==AF_WILD) {
      char *sPattern,*sAlias,*s1stNo,*sLastNo,*pFormat,*pEquation,*sLC,*sUC;
      int nFirst,nLast;
      if (AFChkSearchString(qPattern,
         &sPattern,&sAlias,&s1stNo,&sLastNo,&pFormat,&pEquation,&sLC,&sUC)) {
         nFirst=atoi(s1stNo);
         nLast=atoi(sLastNo);
         if (nFirst<=nLast) {
            AFAddNodeOneToOne(
               pList,
               sPattern,sAlias,pFormat,pEquation,nDividerType,nFirst,nLast,
               atof(sLC),atof(sUC));
            bResult=TRUE;
         }
      }
      freeEx(sPattern);
      freeEx(sAlias);
      freeEx(s1stNo);
      freeEx(sLastNo);
      freeEx(pFormat);
      freeEx(sLC);
      freeEx(sUC);
   } else if (nSearchType==AF_BLOCK) {
      char *pBeginning,*pEnding,*pBlockSelections;
      char *sBlockSelectionAll,*s1stColumn,*pOtherColumns,*pFormat,*pEquation;
      char *sCutLow,*sCutHigh;
      char *pFound;

      if (!strstr(qPattern,AF_OPT_BEGINNING)) return bResult;
      if (!strstr(qPattern,AF_OPT_ENDING)) return bResult;
      if (!strstr(qPattern,AF_OPT_BLOCKSELECTIONS)) return bResult;
      if (!strstr(qPattern,AF_OPT_BLOCKSELECTIONALL)) return bResult;
      if (!strstr(qPattern,AF_OPT_FIRSTCOLUMN)) return bResult;
      if (!strstr(qPattern,AF_OPT_OTHERCOLUMNS)) return bResult;
      if (!strstr(qPattern,AF_OPT_FORMAT)) return bResult;
      if (!strstr(qPattern,AF_OPT_EQUATION)) return bResult;
      if (!strstr(qPattern,AF_OPT_CUTLOW)) return bResult;
      if (!strstr(qPattern,AF_OPT_CUTHIGH)) return bResult;

      pFound=strstr(qPattern,AF_OPT_BEGINNING)+strlen(AF_OPT_BEGINNING);
      pBeginning=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));
      pFound=strstr(qPattern,AF_OPT_ENDING)+strlen(AF_OPT_ENDING);
      pEnding=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));
      pFound=strstr(qPattern,AF_OPT_BLOCKSELECTIONS)+strlen(AF_OPT_BLOCKSELECTIONS);
      pBlockSelections=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));
      pFound=strstr(qPattern,AF_OPT_BLOCKSELECTIONALL)+strlen(AF_OPT_BLOCKSELECTIONALL);
      sBlockSelectionAll=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));
      pFound=strstr(qPattern,AF_OPT_FIRSTCOLUMN)+strlen(AF_OPT_FIRSTCOLUMN);
      s1stColumn=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));
      pFound=strstr(qPattern,AF_OPT_OTHERCOLUMNS)+strlen(AF_OPT_OTHERCOLUMNS);
      pOtherColumns=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));
      pFound=strstr(qPattern,AF_OPT_FORMAT)+strlen(AF_OPT_FORMAT);
      pFormat=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));
      pFound=strstr(qPattern,AF_OPT_EQUATION)+strlen(AF_OPT_EQUATION);
      pEquation=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));
      pFound=strstr(qPattern,AF_OPT_CUTLOW)+strlen(AF_OPT_CUTLOW);
      sCutLow=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));
      pFound=strstr(qPattern,AF_OPT_CUTHIGH)+strlen(AF_OPT_CUTHIGH);
      sCutHigh=strmidp(qPattern,pFound,strstr(pFound,AF_COMMAND_LINE_END));

      strtrim(pBeginning);
      strtrim(pEnding);
      strtrim(pBlockSelections);
      strtrim(sBlockSelectionAll);
      strtrim(s1stColumn);
      strtrim(pOtherColumns);
      strtrim(pFormat);
      strtrim(pEquation);
      strtrim(sCutLow);
      strtrim(sCutHigh);

      AFAddNodeOneToMany(
         pList,
         pBeginning,pEnding,pBlockSelections,
         atoi(sBlockSelectionAll),atoi(s1stColumn),pOtherColumns,
         pFormat,pEquation,
         atof(sCutLow),atof(sCutHigh)
         );
      bResult=TRUE;

      freeEx(pBeginning);
      freeEx(pEnding);
      freeEx(pBlockSelections);
      freeEx(sBlockSelectionAll);
      freeEx(s1stColumn);
      freeEx(pOtherColumns);
      freeEx(pFormat);
      freeEx(pEquation);
      freeEx(sCutLow);
      freeEx(sCutHigh);
   }

   return bResult;
}

int AFAddNodeOneToOne( pList,pPattern,pAlias,pFormat,pEquation,
                       nDividerType,nFirst,nLast,dLc,dUc )
   AFLIST *pList;
   char *pPattern,*pAlias,*pFormat,*pEquation;
   int nDividerType,nFirst,nLast;
   double dLc,dUc;
{
   AFNODEONETOONE *node;

   if (!pPattern) return FALSE;
   strtrim(pPattern);
   node=salloc(AFNODEONETOONE,1);
   AnyAddDLObject(pList,node);
   if (pAlias&&strlen(pAlias))
      node->pAlias=strdpl(pAlias);
   else {
      char buf8[8+1];
      int i,j;
      i=strlen(pPattern);
      strncpy(buf8,pPattern,i>8 ? 8:i);
      for (j=i;j<8;j++) buf8[j]='_';
      buf8[8]=0;
      node->pAlias=strdpl(buf8);
   }

   if (nFirst<0) nFirst=1;
   if (nLast<0) nLast=1;

   node->pPattern=strdpl(pPattern);
   node->pFormat=strdpl(pFormat);
   node->pEquation=strdpl(pEquation);
   node->nDividerType=(!nFirst && !nLast) ? AF_EQUATION:nDividerType; /* 2001.0213 */
   node->nFirst=(nDividerType!=AF_EQUATION) ? nFirst:0; /* 2001.0213 */
   node->nLast=(nDividerType!=AF_EQUATION) ? nLast:0; /* 2001.0213 */
   node->dLc=dLc;
   node->dUc=dUc;
   pList->nTotal++;
   return TRUE;
}

int AFAddNodeOneToMany(
    AFLIST *pList,
    char *pBeginning,char *pEnding,char *pBlockSelections,
    int bBlockSelectionAll,int n1stColumn,
    char *pOtherColumns,char *pFormat,char *pEquation,
    double dCutLow,double dCutHigh
    )
{
   AFNODEONETOMANY *node;

   node=salloc(AFNODEONETOMANY,1);
   AnyAddDLObject(pList,node);

   node->pBeginning=strdpl(pBeginning);
   node->pEnding=strdpl(pEnding);
   node->pBlockSelections=strdpl(pBlockSelections);
   node->bBlockSelectionAll=bBlockSelectionAll;
   node->n1stColumn=n1stColumn;
   node->pOtherColumns=strdpl(pOtherColumns);
   node->pFormat=strdpl(pFormat);
   node->pEquation=strdpl(pEquation);
   node->dCutLow=dCutLow;
   node->dCutHigh=dCutHigh;

   pList->nTotal++;
   return TRUE;
}

int AFExtractEx(
   pList,qFileNames,ppppString2d,pNrl,pNrh,pNcl,pNch,pSynchronizer
   )
   AFLIST *pList;
   const char *qFileNames;
   char ****ppppString2d;
   int *pNrl,*pNrh,*pNcl,*pNch;
   int ((*pSynchronizer)(char*));
{
   char qLastCommand[]="<<",qSpaceChars[]="\t\r\n";
   char *pLines,*pFile,*pError;
   char ***newMatrix;
   int newNrl,newNrh,newNcl,newNch;
   char ***tmpMatrix;
   int tmpNrl,tmpNrh,tmpNcl,tmpNch;
   int bResult,bBottomAttachment;

   newMatrix=0;
   tmpMatrix=0;
   tmpNrl=tmpNrh=tmpNcl=tmpNch=0;

   bResult=TRUE;
   bBottomAttachment=TRUE;
   pLines=strvcat((char*)qFileNames,AF_COMMAND_LINE_END,qLastCommand,0);
   strtrim(pLines);
   if (strlen(pLines)==strlen(qLastCommand)) {
      pError=strvcat(
         "Error @AFExtractEx(),\nCould not look for any SPLIT files.",
         0);
      AFSetErrorMessage(0,0);
      AFSetErrorMessage(pError,1);
      bResult=FALSE;
      goto E;
   }
   bResult=-36; /* 36 is my runar age when coding this first. */
   pFile=strtok(pLines,qSpaceChars);
   while (pFile) {
      strtrim(pFile);
      if (pSynchronizer) (*pSynchronizer)(pFile);
      if (bResult==-36 /* means the nFirst loop */
         && pFile[0]==AF_SPLIT_INDICATOR) {
         pFile=strtok(NULL,qSpaceChars);
         if (!pFile) {
            pError=strvcat(
               "Error @AFExtractEx(),\n"
               "Could not find any SPLIT files.\n"
               "Full of alias.",
               0);
            AFSetErrorMessage(0,0);
            AFSetErrorMessage(pError,1);
            bResult=FALSE;
            goto E;
         }
         continue;
      }
      switch (pList->nDataUnitType) {
      case AF_FILE :
         if (pFile[0]==AF_SPLIT_INDICATOR) {
            bBottomAttachment=FALSE; /* 2K.0516 */
         } else {
            bResult=AFExtract(pList,pFile,
               &newMatrix,&newNrl,&newNrh,&newNcl,&newNch);
            if (!bResult) break;
            if (!pList->bComposite) { /* 2001.0410 */
               AFPostNumericProcessOnEachColumn(
                  pList->nNumPostProcessType,
                  ((AFNODEONETOONE*)((AFNODEONETOONE*)pList->head))->pFormat,
                  newMatrix,newNrl,&newNrh,newNcl,newNch);
            }
            bResult=AFAddAnotherStringMatrix(
               newMatrix,newNrl,newNrh,newNcl,newNch,
               ppppString2d,pNrl,pNrh,pNcl,pNch,
               bBottomAttachment,
               AF_NULL_STRING);
            if (*ppppString2d!=newMatrix)
               freeString2d(newMatrix,newNrl,newNrh,newNcl,newNch);
            newMatrix=0;
            bBottomAttachment=TRUE; /* 2K.0516 */
         }
         break;
      case AF_FILES :
         if (pFile[0]==AF_SPLIT_INDICATOR) {
            if (!pList->bComposite) { /* 2001.0410 */
               AFPostNumericProcessOnEachColumn(
                  pList->nNumPostProcessType,
                  ((AFNODEONETOONE*)((AFNODEONETOONE*)pList->head))->pFormat,
                  tmpMatrix,tmpNrl,&tmpNrh,tmpNcl,tmpNch);
            }
            bResult=AFAddAnotherStringMatrix(
               tmpMatrix,tmpNrl,tmpNrh,tmpNcl,tmpNch,
               ppppString2d,pNrl,pNrh,pNcl,pNch,
               bBottomAttachment=FALSE, /* 2K.0516 */
               AF_NULL_STRING);
            if (*ppppString2d!=tmpMatrix && tmpMatrix)
               freeString2d(tmpMatrix,tmpNrl,tmpNrh,tmpNcl,tmpNch);
            tmpMatrix=0;
         } else {
            bResult=AFExtract(pList,pFile,
               &newMatrix,&newNrl,&newNrh,&newNcl,&newNch);
            if (!bResult) break;
            bResult=AFAddAnotherStringMatrix(
               newMatrix,newNrl,newNrh,newNcl,newNch,
               &tmpMatrix,&tmpNrl,&tmpNrh,&tmpNcl,&tmpNch,
               bBottomAttachment, /* 2K.0516 */
               AF_NULL_STRING);
            if (tmpMatrix!=newMatrix)
               freeString2d(newMatrix,newNrl,newNrh,newNcl,newNch);
            newMatrix=0;
            bBottomAttachment=TRUE; /* 2K.0516 */
         }
         break;
      }
      if (!bResult) break;
      pFile=strtok(NULL,qSpaceChars);
   }
   freeEx(pLines);

   if (pList->bComposite) { /* 2001.0410 */
      AFPostCompositeProcessOnEachColumn(
         pList->nNumPostProcessType,AFGetMaxFileCountPerSplit(qFileNames),
         ((AFNODEONETOONE*)pList->head)->pFormat,
         ppppString2d,*pNrl,pNrh,*pNcl,*pNch);
   }

E: if (!bResult) {
      freeEx(pLines);
      freeEx(pError);
   }
   return bResult;
}

int AFExtract( pList,qFileName,ppppString2d,pNrl,pNrh,pNcl,pNch ) /* once for each file */
   AFLIST *pList;
   const char *qFileName;
   char ****ppppString2d;
   int *pNrl,*pNrh,*pNcl,*pNch;
{
   AFNODEONETOONE *node;
   char *pStream;
   int bResult;

   AFSetErrorMessage(0,0);

   if (!myFileToStream(qFileName,&pStream)) {
      char *pTemp;
      pTemp=strvcat(
         "Error @AFExtract(),\n"
         "Could not open a file you enrolled :\n\n",
         qFileName,
         0);
      AFSetErrorMessage(pTemp,0);
      free(pTemp);
      return FALSE;
   }
   if (pList->bCaseSensitive) {
      for (node=((AFNODEONETOONE*)pList->head);node;node=node->next)
         strtolower(node->pPattern);
      strtolower(pStream);
   }
   /**/
   bResult=TRUE;
   *ppppString2d=0;
   *pNrl=*pNrh=*pNcl=*pNch=0;
   switch (pList->nSearchType) {
   case AF_ABSOLUTE :
      bResult=AFGetString2dAbsolutely(
         pList,pStream,ppppString2d,pNrl,pNrh,pNcl,pNch);
      break;
   case AF_SEQUENTIAL :
      bResult=AFGetString2dSequentially(
         pList,pStream,ppppString2d,pNrl,pNrh,pNcl,pNch);
      break;
   case AF_WILD :
      bResult=AFExtractWildly(
         pList,pStream,ppppString2d,pNrl,pNrh,pNcl,pNch);
      break;
   case AF_BLOCK :
      bResult=AFGetString2dByBlock(
         pList,pStream,ppppString2d,pNrl,pNrh,pNcl,pNch);
      break;
   default:
      return FALSE;
   }
   free(pStream);
   if (bResult) {
      AFSetNullStrToMatrix(*ppppString2d,*pNrl,*pNrh,*pNcl,*pNch,AF_NULL_STRING);
   } else {
      char *pTemp=strvcat(
         "Error @AFExtract(),\n"
         "Could not look for any PATTERNs in a file :\n\n",
         qFileName,
         0);
      AFSetErrorMessage(pTemp,1);
      free(pTemp);
   }
   return bResult;
}

/*
 >>> Exchange Row-Col Block From Originally Extracted Matrix
   ! s1       s2       s3       s4        <- split <----- grouped by each file
     p1 p2 p3 p1 p2 p3 p1 p2 p3 p1 p2 p3  <- pattern
     11 12 13 14 15 16 17 18 19 1a 1b 1c  <- data
     21 22 23 24 25 26 27 28 29 2a 2b 2c  <- data
     31 32 33 34 35 36 37 38 39 3a 3b 3c  <- data

 >>> Irreversible Rotation From Original Matrix Under bColumnarMatrix==TRUE

  >> nRCExchangeType == AF_ROWCOL_EXCHANGE_BYPATTERN -> 1st Column is pattern.
      ! s1 s1 s1 s2 s2 s2 s3 s3 s3 s4 s4 s4
     p1 11 21 31 14 24 34 17 27 37 1a 2a 3a
     p2 12 22 32 15 25 35 18 28 38 1b 2b 3b
     p3 13 23 33 16 26 36 19 29 39 1c 2c 3c
  >> nRCExchangeType == AF_ROWCOL_EXCHANGE_BYPATTERN2 -> 1st Column is pattern.
      ! s1 s2 s3 s4
     p1 11 14 17 1a
     p2 12 15 18 1b
     p3 13 16 19 1c
     p1 21 24 27 2a
     p2 22 25 28 2b
     p3 23 26 29 2c
     p1 31 34 37 3a
     p2 32 35 38 3b
     p3 33 36 39 3c
  >> nRCExchangeType == AF_ROWCOL_EXCHANGE_BYSPLIT -> 1st Column is split.
      ! p1 p1 p1 p2 p2 p2 p3 p3 p3
     s1 11 21 31 12 22 32 13 23 33
     s2 14 24 34 15 25 35 16 26 36
     s3 17 27 37 18 28 38 19 29 39
     s4 1a 2a 3a 1b 2b 3b 1c 2c 3c
*/
int AFExchangeRowColPerBlock( ppppString2d,pNrl,pNrh,pNcl,pNch,nColPerBlock,nRCExchangeType )
/* It works well under the assumption of No numeric header. 2K.0517+0703 */
   char ****ppppString2d;
   int *pNrl,*pNrh,*pNcl,*pNch;
   int nColPerBlock,nRCExchangeType;
{
   char ***pppMatrix;
   int nSplitCount,nPatternCount,nrlNew,nrhNew,nclNew,nchNew,nRowCount,
       i,j,i0,j0,r,c,jl,jh,k;

   if ((*pNch-*pNcl+1)%nColPerBlock) return 0;
   nRowCount=*pNrh-*pNrl+1;
   nSplitCount=(*pNch-*pNcl+1)/nColPerBlock;
   nPatternCount=nColPerBlock;

   switch (nRCExchangeType) {
   case AF_ROWCOL_EXCHANGE_BYPATTERN : /* First column is pattern */
      nrlNew=1;
      nrhNew=nPatternCount;
      nclNew=1;
      nchNew=nSplitCount*nRowCount;
      pppMatrix=alloString2d(nrlNew,nrhNew,nclNew,nchNew);
      if (!pppMatrix) return 0;
      for (i=nrlNew;i<=nrhNew;i++) {
         for (k=0;k<nSplitCount;k++) {
            if (!k) jl=nclNew;
            jh=jl+nRowCount-1;
            for (j=jl;j<=jh;j++) {
               r=j-jl+*pNcl;
               c=i-nrlNew+*pNcl+k*nPatternCount;
               pppMatrix[i][j]=strdpl((*ppppString2d)[r][c]);
            }
            jl=jh+1;
         }
      }
      break;
   case AF_ROWCOL_EXCHANGE_BYPATTERN2 : /* First column is pattern */
      nrlNew=1;
      nrhNew=nPatternCount*nRowCount;
      nclNew=1;
      nchNew=nSplitCount;
      pppMatrix=alloString2d(nrlNew,nrhNew,nclNew,nchNew);
      if (!pppMatrix) return 0;
      for (i=nrlNew;i<=nrhNew;i++) {
         for (j=nclNew;j<=nchNew;j++) {
            k=j-nclNew;
            r=*pNrl+(int)((i-nrlNew)/nPatternCount);
            c=*pNcl+(i-nrlNew)%nPatternCount+k*nPatternCount;
            pppMatrix[i][j]=strdpl((*ppppString2d)[r][c]);
         }
      }
      break;
   case AF_ROWCOL_EXCHANGE_BYSPLIT:  /* First column is split */
      nrlNew=1;
      nrhNew=nSplitCount;
      nclNew=1;
      nchNew=nPatternCount*nRowCount;
      pppMatrix=alloString2d(nrlNew,nrhNew,nclNew,nchNew);
      if (!pppMatrix) return 0;
      for (i=nrlNew;i<=nrhNew;i++) {
         i0=i-nrlNew;
         for (j=nclNew;j<=nchNew;j++) {
            j0=j-nclNew;
            r=j0%nRowCount+1;
            c=(int)(j0/nRowCount)+1+i0*nColPerBlock;
            pppMatrix[i][j]=strdpl((*ppppString2d)[r][c]);
         }
      }
      break;
   }
   
   freeString2d(*ppppString2d,*pNrl,*pNrh,*pNcl,*pNch);
   *ppppString2d=pppMatrix;
   *pNrl=nrlNew;
   *pNrh=nrhNew;
   *pNcl=nclNew;
   *pNch=nchNew;
   return (*pNrh-*pNrl+1)*(*pNch-*pNcl+1);
}

int AFGetColumnCountPerBlock( pList )
   AFLIST *pList;
{
   AFNODEONETOONE *node;
   int nCount=0;
   for (node=((AFNODEONETOONE*)pList->head);node;node=node->next) {
      nCount+=AFChkColNumberOfNode(node);
   }
   return nCount;
}

int AFPutItToStream( pList,pppString2d,nrl,nrh,ncl,nch,ppStream,bLeftHeaderAttachment,
                     nExHeader,sExHeader )
   AFLIST *pList;
   char ***pppString2d;
   int nrl,nrh,ncl,nch; /* should be (nch-ncl+1) = pList->nTotal */
   char **ppStream; /* returning object */
   int bLeftHeaderAttachment;
   int nExHeader;
   char **sExHeader; /* [1..nExHeader] */
{
   AFNODEONETOONE *node;
   char ***matrix;
   int nrlNew,i;
   
   *ppStream=0;
   if (bLeftHeaderAttachment) {
      int nclNew=ncl-1;
      matrix=salloc(char**,nrh-nrl+1);
      matrix-=nrl;
      node=((AFNODEONETOONE*)pList->head);
      for (i=nrl;i<=nrh;i++) {
         matrix[i]=salloc(char*,nch-nclNew+1);
         matrix[i]-=nclNew;
         memcpy(matrix[i]+ncl,pppString2d[i]+ncl,sizeof(char*)*(nch-ncl+1));
         if (!nExHeader) {
            matrix[i][nclNew]=node->pAlias ? node->pAlias:"NA";
            node=node->next ? node->next:((AFNODEONETOONE*)pList->head);
         } else {
            matrix[i][nclNew]=sExHeader[(i-nrl)%nExHeader+1];
         }
      }
      *ppStream=string2dtostream(matrix,nrl,nrh,nclNew,nch," ","\r\n");
      for (i=nrl;i<=nrh;i++) free(matrix[i]+nclNew);
      free(matrix+nrl);
   } else {
      nrlNew=nrl-1;
      matrix=(char***)malloc(sizeof(char**)*(nrh-nrlNew+1));
      matrix-=nrlNew;
      matrix[nrlNew]=(char**)malloc(sizeof(char*)*(nch-ncl+1));
      matrix[nrlNew]-=ncl;
      memcpy((char*)&(matrix[nrl]),(char*)&(pppString2d[nrl]),sizeof(char**)*(nrh-nrl+1));
      for (i=ncl,node=((AFNODEONETOONE*)pList->head);i<=nch;i++) {
         if (!nExHeader) {
            matrix[nrlNew][i]=node->pAlias ? node->pAlias:"NA";
            node=node->next ? node->next:((AFNODEONETOONE*)pList->head);
         } else {
            matrix[nrlNew][i]=sExHeader[(i-ncl)%nExHeader+1];
         }
      }
      *ppStream=string2dtostream(matrix,nrlNew,nrh,ncl,nch," ","\r\n");
      free(matrix[nrlNew]+ncl);
      free(matrix+nrlNew);
   }
   return TRUE;
}

int AFGetPatternAliasArrayB1( pList,bNumericHeader,rArray,nCount )
   AFLIST *pList;
   int bNumericHeader;
   char ***rArray;
   int *nCount;
{
   char **sHeader,*ptr;
   int nHeader,nIndex,nTotal,nPos;
   AFNODEONETOONE *node;

   nHeader=AFChkColNumber(pList);
   sHeader=alloString1d(1,nHeader);
   memset(&(sHeader[1]),0,sizeof(char*)*nHeader);

   nIndex=1;
   for (node=((AFNODEONETOONE*)pList->head);node;node=node->next) {
      nTotal=node->nLast-node->nFirst+1;
      ptr=node->pAlias;
      while (nTotal--) {
         if (bNumericHeader) {
            if (!isnumstr(ptr)) {
               if (ptr[0]=='\'') {
                  ptr[0]=' ';
                  nPos=strlen(ptr)-1;
                  if (ptr[nPos]=='\'') ptr[nPos]=' ';
                  strtrim(ptr);
               } else {
                  ptr=strvcat(
                     "Warning, No numerical value in pattern pAlias \" ",
                     ptr,
                     " \" \nunder bNumericalAlias=TRUE ! \n",
                     0);
                  AFSetErrorMessage(ptr,0);
                  free(ptr);
                  goto F;
               }
            }
         } else {
            if (isnumstr(ptr)) {
               ptr=strvcat("\'",node->pAlias,"\'",0);
               free(node->pAlias);
               node->pAlias=ptr;
            }
         }
         sHeader[nIndex++]=strdpl(node->pAlias);
      }
   }
   
   *rArray=sHeader;
   *nCount=nHeader;
   return TRUE;
F: freeString1d(sHeader,1,nHeader);
   *rArray=0;
   *nCount=0;
   return FALSE;
}

int AFPrintList( pList )
   AFLIST *pList;
{
   AFNODEONETOONE *node;
   int i;

   fprintf(stdout,"\nAF...\ntotal=%d,caseSensitive=%d\n",
          pList->nTotal,pList->bCaseSensitive);
   for (node=((AFNODEONETOONE*)pList->head),i=1;node;node=node->next) {
      fprintf(stdout,"[%d],head=<%s>,searchStr=<%s>,nDividerType=<%d>,"
                     "nFirst=<%d>,nLast=<%d>\n",
              i++,node->pAlias,node->pPattern,node->nDividerType,
              node->nFirst,node->nLast);
   }
   fprintf(stdout,"\n");
   return (1);
}

int AFGetErrorMessagePointer( char **pMessage ) /* do not use free() */
{
   *pMessage=AFErrorMessage;
   return AFErrorMessage ? strlen(AFErrorMessage):0;
}

static
void AFSetErrorMessage ( char *sMessage,int bAttach ) {
   if (bAttach) {
      AFErrorMessage=AFErrorMessage ?
         strvcat(AFErrorMessage,sMessage,0):strdpl(sMessage);
   } else {
      freeEx(AFErrorMessage);
      AFErrorMessage=sMessage ? strdpl(sMessage):0;
   }
}

static
int AFGetString2dAbsolutely( pList,pStream,ppppString2d,nrl,nrh,ncl,nch )
   AFLIST *pList;
   char *pStream;
   char * ***ppppString2d;
   int *nrl,*nrh,*ncl,*nch;
{
   int i,j,k,nLength,nCount,bError;
   AFNODEONETOONE *node;
   char *pAddr,**str1d0; /* str1d0 = string 1 dim of which base is zero */

   if (!(i=AFChkRowNumber(pList,pStream))) return FALSE;
   if (!(j=AFChkColNumber(pList))) return FALSE;

   *nrl=1;
   *nrh=i;
   *ncl=1;
   *nch=j;
   *ppppString2d=alloString2d(*nrl,*nrh,*ncl,*nch);

   for (i=*nrl;i<=*nrh;i++)
      memset((char*)&((*ppppString2d)[i][1]),0,(*nch-*ncl+1)*sizeof(char*));

   nCount=0;
   for (node=((AFNODEONETOONE*)pList->head);node;node=node->next) {
      nCount=MAX(nCount,AFChkColNumberOfNode(node));
   }
   str1d0=alloString1d(0,nCount-1);

   for (j=*ncl,node=((AFNODEONETOONE*)pList->head);
        j<=*nch && node;
        node=node->next) {
      if (IS_TRACKING_NODE(node)) continue;
      nCount=AFChkColNumberOfNode(node);
      nLength=strlen(node->pPattern);
      pAddr=pStream;
      for (i=*nrl;i<=*nrh;i++) {
         pAddr=AFFindString(pAddr,node->pPattern,nLength);
         if (!pAddr) break;
         AFGetFirstToLastStrings(node,pAddr,str1d0,nCount);
         for (k=0;k<nCount;k++)
            (*ppppString2d)[i][j+k]=str1d0[k];
      }
      j+=nCount;
      bError=ABS(*nrh-i+1); /* just check for row Error */
   }
      bError=ABS(*nch-j+1); /* just check for col Error */

   free((char*)(str1d0));
   
   return TRUE;
}

static
int AFGetString2dSequentially( pList,pStream,ppppString2d,nrl,nrh,ncl,nch )
   AFLIST *pList;
   char *pStream;
   char * ***ppppString2d;
   int *nrl,*nrh,*ncl,*nch;
{
   int i,j,k,nCount,nLength;
   AFNODEONETOONE *node;
   char *pAddr,**str1d0; /* str1d0 = string 1 dim of which base is zero */

   if (!(i=AFChkRowNumber(pList,pStream))) return FALSE;
   if (!(j=AFChkColNumber(pList))) return FALSE;

   *nrl=1;
   *nrh=i;
   *ncl=1;
   *nch=j;
   *ppppString2d=alloString2d(*nrl,*nrh,*ncl,*nch);
   
   for (k=*nrl;k<=*nrh;k++)
      memset((char*)&((*ppppString2d)[k][1]),0,(*nch-*ncl+1)*sizeof(char*));

   nCount=0;
   for (node=((AFNODEONETOONE*)pList->head);node;node=node->next) {
      nCount=MAX(nCount,AFChkColNumberOfNode(node));
   }
   str1d0=alloString1d(0,nCount-1);

   pAddr=pStream;
   for (i=*nrl;i<=*nrh;i++) {
      j=*ncl;
      for (node=((AFNODEONETOONE*)pList->head);node;node=node->next) {
         if (IS_EQUATION_NODE(node)) {
            AFGetFirstToLastStrings(node,pAddr,str1d0,1);
            (*ppppString2d)[i][j]=str1d0[0];
            j++;
            continue;
         }
         nLength=strlen(node->pPattern);
         pAddr=AFFindString(pAddr,node->pPattern,nLength);
         if (!pAddr) break;
         if (IS_TRACKING_NODE(node)) continue;
         nCount=AFChkColNumberOfNode(node);
         AFGetFirstToLastStrings(node,pAddr,str1d0,nCount);
         for (k=0;k<nCount;k++) {
            (*ppppString2d)[i][j]=str1d0[k];
            j++;
         }
      }
      if (--j>*nch) {
         free((char*)str1d0);
         return FALSE;
      }
   }

   free((char*)str1d0);

   return TRUE;
}

static
int AFExtractWildly( pList,pStream,ppppString2d,nrl,nrh,ncl,nch )
   AFLIST *pList; /* must have two nodes of children with some wild card */
   char *pStream,****ppppString2d;
   int *nrl,*nrh,*ncl,*nch;
{
   char **xHead,**yHead;
   int xHeadLength,yHeadLength,xHeadTotal,yHeadTotal;
   char *address,*ptr,*pointer,xBuf32[32],yBuf32[32],zBuf32[32];
   int xSearchStrLength,ySearchStrLength,i,j;

   /**/
   if (!strchrs(((AFNODEONETOONE*)pList->head)->pPattern,"?*[]")  /* x */
   ||  !strchrs(((AFNODEONETOONE*)pList->tail)->pPattern,"?*[]")) /* y */
      return FALSE;
   /**/
   xSearchStrLength=strlen(((AFNODEONETOONE*)pList->head)->pPattern);
   ySearchStrLength=strlen(((AFNODEONETOONE*)pList->tail)->pPattern);
   /**/
   xHead=yHead=0;
   xHeadLength=yHeadLength=xHeadTotal=yHeadTotal=0;
   address=pStream;
   skipwhite(&address);
   while (*address) {      
      if (strnweq(address,((AFNODEONETOONE*)pList->head)->pPattern,xSearchStrLength)) {
         /**/
         strncpy(xBuf32,address,xSearchStrLength);
         xBuf32[xSearchStrLength]=0;
         /**/
         SkipBlackWhite(&address);
         while (*address) {
            if (strnweq(address,((AFNODEONETOONE*)pList->tail)->pPattern,ySearchStrLength)) {
               /**/
               strncpy(yBuf32,address,ySearchStrLength);
               yBuf32[ySearchStrLength]=0;
               AFAddStrToStrArray(&xHead,&xHeadLength,&xHeadTotal,strdpl(xBuf32));
               AFAddStrToStrArray(&yHead,&yHeadLength,&yHeadTotal,strdpl(yBuf32));
               /**/
               break;
            }
            SkipBlackWhite(&address);
         }
      }
      SkipBlackWhite(&address);
   }
   /**/
   *nrl=0;
   *nrh=xHeadTotal;
   *ncl=0;
   *nch=yHeadTotal;
   *ppppString2d=alloString2d(*nrl,*nrh,*ncl,*nch);
   for (i=*nrl;i<=*nrh;i++)
      memset((*ppppString2d)[i]+*ncl,0,sizeof(char*)*(*nch-*ncl+1));
   (*ppppString2d)[0][0]=strdpl("xyz");
   if (!*ppppString2d) {
      free(pStream);
      for (i=0;i<*nrh;i++) free(xHead[i]);
      for (i=0;i<*nch;i++) free(yHead[i]);
      return FALSE;
   }
   for (i=1;i<=*nrh;i++) (*ppppString2d)[i][0]=xHead[i-1];
   for (i=1;i<=*nch;i++) (*ppppString2d)[0][i]=yHead[i-1];
   free(xHead);
   free(yHead);
   /**/
   address=pStream;
   skipwhite(&address);
   while (*address) {      
      if (strnweq(address,((AFNODEONETOONE*)pList->head)->pPattern,xSearchStrLength)) {
         /**/
         strncpy(xBuf32,address,xSearchStrLength);
         xBuf32[xSearchStrLength]=0;
         /**/
         SkipBlackWhite(&address);
         while (*address) {
            if (strnweq(address,((AFNODEONETOONE*)pList->tail)->pPattern,ySearchStrLength)) {
               /**/
               strncpy(yBuf32,address,ySearchStrLength);
               yBuf32[ySearchStrLength]=0;
               SkipBlackWhite(&address);
               ptr=address;
               for (i=ABS(((AFNODEONETOONE*)pList->tail)->nFirst);
                    i<=ABS(((AFNODEONETOONE*)pList->tail)->nLast);
                    i++) {
                  SkipBlackWhite(&ptr);
               }
               pointer=ptr;
               skipblack(&pointer);
               i=pointer-ptr-1+1;
               strncpy(zBuf32,ptr,i);
               zBuf32[i]=0;
               AFGetXYNoOfMatrix(*ppppString2d,*nrl,*nrh,*ncl,*nch,
                                 xBuf32,yBuf32,&i,&j);
               (*ppppString2d)[i][j]=
                  AFDuplicateString(zBuf32,
                  ((AFNODEONETOONE*)pList->tail)->pFormat,((AFNODEONETOONE*)pList->tail)->pEquation,0.0,0.0);
               break;
            }
            SkipBlackWhite(&address);
         }
      }
      SkipBlackWhite(&address);
   }
   free(pStream);
   AFSetNullStrToMatrix(*ppppString2d,*nrl,*nrh,*ncl,*nch,AF_NULL_STRING);

   return TRUE;
}

/* Y.Kim,20030209 */
static
int AFGetString2dByBlock( pList,pStream,ppppString2d,nrl,nrh,ncl,nch )
   AFLIST *pList;
   char *pStream;
   char * ***ppppString2d;
   int *nrl,*nrh,*ncl,*nch;
{
   AFNODEONETOMANY *pNode=(AFNODEONETOMANY *)pList->head;
   int bResult=FALSE;
   /*
   char qBuffer[_MAX_PATH*4]; * _MAX_PATH = 256 in <stdlib.h> *
   int nBufferLength=sizeof(qBuffer);
   char *pTemporaryPath,*pTemporaryFile,*pArgument;

   pTemporaryPath=myGetCurrentDirName();
   pTemporaryFile=strvcat(pTemporaryPath,"\\ANY",0);
   sprintf(qBuffer,"-x%d -y%d -b%d test.htm",1,2,3);
   pArgument=strdpl(qBuffer);

   pNode->script.pExtractor="excob.exe";


   freeEx(pTemporaryPath);
   freeEx(pTemporaryFile);
   freeEx(pArgument);
   */

   return bResult;
}

static
char *AFFindString( qString,qSearchString,nSearchStringLength )
   const char *qString;
   const char *qSearchString;
   int nSearchStringLength;
{
   char *pAddr;
   pAddr=strstr(qString,qSearchString);
   if (!pAddr) return NULL;
   pAddr+=nSearchStringLength;
   if (isspace(*pAddr)||*pAddr==0)
      return pAddr;
   return AFFindString(pAddr,qSearchString,nSearchStringLength);
}

static
char *AFDuplicateString( qString,pFormat,pEquation,dLc,dUc )
   const char *qString,*pFormat,*pEquation;
   double dLc,dUc;
{
   if (strchrs(pFormat,"deEfgG")) {
      char buf256[256],*ptr;
      double dResult;
      /**/
      if (!isnumstr(qString)) {
         strcpy(buf256,AF_NULL_STRING);
         return strdpl(buf256);
      }
      /**/
      dResult=atof(qString);
      //dResult=atofEx(qString);
      /**/
      if (pEquation && *pEquation) {
         int nCount=chrcount((const char*)pEquation,'=');
         if (nCount>=1) {
            if (!setjmp(jb_parser)) {
               char qBuffer[256];
               sprintf(qBuffer,"z=%1.9e",dResult);
               mathparser(qBuffer,&dResult);
               /* mathparser(pEquation,&dResult); */
               mathparserEx(pEquation,&dResult); /* 2001.0213 */
               dResult=mathparserSlotValue('z');
            } else {
               sprintf(buf256,"Something wrong with eqution ...\n%s\n"
                  "in AFDuplicateString()\n",pEquation);
               errWarning(buf256);
               return strdpl(AF_NULL_STRING);
            }
         }
      }
      /**/
      if (dLc<dUc) {
         if (dResult<dLc || dResult>dUc) {
            return strdpl(AF_NULL_STRING);
         }
      }
      /**/
      if ((ptr=strchrs(pFormat,"eEfgGzZ"))) {
         strcpy2buf(buf256,dtos(dResult,pFormat),noof(buf256));
      } else if ((ptr=strchrs(pFormat,"d"))) {
         char *pResult;
         if ((double)INT_MAX<dResult || (double)INT_MIN>dResult) /* 2001.0319 */
            pResult=dtostr(dResult,"%.0e");
         else
            pResult=itostr((int)dResult,pFormat);
         strcpy2buf(buf256,pResult,noof(buf256));
         freeEx(pResult);
      }
      return strdpl(buf256);
   }   
   return strdpl(qString); /* %s */
}

static
void AFGetFirstToLastStrings( node,ptr,str1d0,nTotal )
   AFNODEONETOONE *node;
   char *ptr,**str1d0;
   int nTotal;
{
   char *nFirst,*nLast,chr;
   int nIndex,nCount;

   skipblack(&ptr);
   skipwhite(&ptr);
   switch (node->nDividerType) {
   case AF_WHITESPACE : 
      for (nIndex=1;nIndex<node->nFirst;nIndex++) {
         skipwhite(&ptr);
         skipblack(&ptr);
      }
      nFirst=ptr;
      for (nIndex=0;nIndex<nTotal;nIndex++) {
         nLast=skipwhite(&nFirst);
         skipblack(&nLast);
         chr=*nLast;
         *nLast=0;
         str1d0[nIndex]=AFDuplicateString(nFirst,
            node->pFormat,node->pEquation,node->dLc,node->dUc);
         *nLast=chr;
         nFirst=nLast;
      }
      break;
   case AF_CHAR :
   case AF_ADDRESS :
      errWarning("AF_CHAR,AF_ADDRESS : Not yet in AFGetFirstToLastStrings()\n");
      break;
   case AF_EQUATION :
      if (!node->pEquation || !strlen(node->pEquation)) break;
      nCount=chrcount((const char*)node->pEquation,'=');
      if (!setjmp(jb_parser)) {
         double dResult=0.0;
         mathparserEx(node->pEquation,&dResult);
         str1d0[0]=AFDuplicateString(dtos(dResult,"%e"),
            node->pFormat,NULL,node->dLc,node->dUc);
      }
   }
}

static
int AFChkRowNumber( pList,pStream )
   AFLIST *pList;
   char *pStream;
{
   int nLength,nCount,j;
   AFNODEONETOONE *node;
   char *pMessage;

   switch (pList->nSearchType) {
   case AF_ABSOLUTE :
      node=((AFNODEONETOONE*)pList->head);
      nLength=strlen(node->pPattern);
      for (nCount=0;pStream;nCount++) {
         pStream=AFFindString(pStream,node->pPattern,nLength);
         if (!pStream) break;
      }
      if (!nCount) {
         pMessage=strvcat(
            "Could not find search-string absolutely that is :\n\n",
            node->pPattern,
            "\n\n",
            0);
         AFSetErrorMessage(pMessage,1);
         free(pMessage);
      }
      break;
   case AF_SEQUENTIAL :
      for (nCount=0;pStream;) {
         for (node=((AFNODEONETOONE*)pList->head),j=-1;node;node=node->next) {
            if (IS_EQUATION_NODE(node)) {
               j--;
               continue;
            }
            nLength=strlen(node->pPattern);
            pStream=AFFindString(pStream,node->pPattern,nLength);
            if (!pStream) {
               if (!nCount) {
                  pMessage=strvcat(
                     "Could not find search-string sequentially that is :\n\n",
                     node->pPattern,
                     "\n\n",
                     0);
                  AFSetErrorMessage(pMessage,1);
                  free(pMessage);
               }
               return nCount;
            }
            j--;
         }
         j++;
         if (abs(j)!=pList->nTotal) break;
         nCount++;
      }
      break;
   case AF_WILD :
   case AF_BLOCK :
   default :
      nCount=0;
      break;
   }
   return nCount;
}

static
int AFChkColNumber( pList )
   AFLIST *pList;
{
   AFNODEONETOONE *node;
   int nTotal;

   nTotal=0;
   for (node=((AFNODEONETOONE*)pList->head);node;node=node->next) {
      nTotal+=AFChkColNumberOfNode(node);
   }
   return nTotal;
}

static
int AFChkColNumberOfNode( node )
   AFNODEONETOONE *node;
{
   if (IS_TRACKING_NODE(node)) /* find only, not add the target */
      return 0;
   else if (IS_EQUATION_NODE(node))
      return 1;
   else
      return (node->nLast-node->nFirst+1);
}

static
int AFChkSearchString( string,sPattern,sAlias,s1stNo,sLastNo,pFormat,pEquation,sLC,sUC )
   char *string;
   char **sPattern,**sAlias,**s1stNo,**sLastNo,**pFormat,**pEquation,**sLC,**sUC;
{
   char *pAddress,*qAddress;
   int nIndex;
   
   *sPattern=*sAlias=*s1stNo=*sLastNo=*pFormat=*pEquation=*sLC=*sUC=0;

   pAddress=strrchr(string,'\"');
   *sPattern=strmid(string,0,pAddress-string);
   pAddress++;

   strtrim(pAddress);
   strreverse(pAddress);

   qAddress=pAddress;
   for (nIndex=AF_INDEXOF_ALIAS+1;nIndex<AF_INDEXOF_TOTAL;nIndex++) {
      skipblack(&qAddress);
      skipwhite(&qAddress);
   }
   *sAlias=   strdpl(qAddress);
   *s1stNo=   strtokbyindex(pAddress,whitechars,AF_INDEXOF_TOTAL-AF_INDEXOF_FIRSTNO-1);
   *sLastNo=  strtokbyindex(pAddress,whitechars,AF_INDEXOF_TOTAL-AF_INDEXOF_LASTNO-1);
   *pFormat=  strtokbyindex(pAddress,whitechars,AF_INDEXOF_TOTAL-AF_INDEXOF_FORMAT-1);
   *pEquation=strtokbyindex(pAddress,whitechars,AF_INDEXOF_TOTAL-AF_INDEXOF_EQUATION-1);
   *sLC=      strtokbyindex(pAddress,whitechars,AF_INDEXOF_TOTAL-AF_INDEXOF_LOWERCUT-1);
   *sUC=      strtokbyindex(pAddress,whitechars,AF_INDEXOF_TOTAL-AF_INDEXOF_UPPERCUT-1);

   strreverse(*sAlias);
   strreverse(*s1stNo);
   strreverse(*sLastNo);
   strreverse(*pFormat);
   strreverse(*pEquation);
   strreverse(*sLC);
   strreverse(*sUC);

   if ((*sPattern)[0]=='\"') {
      int l=strlen(*sPattern);
      if ((*sPattern)[l-1]=='\"') {
         (*sPattern)[0]=' ';
         (*sPattern)[l-1]=' ';
         strtrim(*sPattern);
      }
   }

   return TRUE;
}

static
int AFSetNullStrToMatrix( pppString2d,nrl,nrh,ncl,nch,nullStr )
   char ***pppString2d;
   int nrl,nrh,ncl,nch;
   char *nullStr;
{
   int i,j;

   if (!nullStr) nullStr=AF_NULL_STRING;
   for (i=nrl;i<=nrh;i++)
      for (j=ncl;j<=nch;j++)
         if (!(pppString2d)[i][j])
            (pppString2d)[i][j]=strdpl(nullStr);
   return TRUE;
}

static
int AFAddAnotherStringMatrix( mtxS,nrlS,nrhS,nclS,nchS,
                              mtxD,nrlD,nrhD,nclD,nchD,
                              bBottomAttachment,
                              nullStr )
   char ***mtxS;
   int nrlS,nrhS,nclS,nchS;
   char ****mtxD;
   int *nrlD,*nrhD,*nclD,*nchD;
   int bBottomAttachment;
   char *nullStr;
{
   int rowS,colS,nrhNew,nchNew,i,j,kr,kc,k;

   if (!mtxS)
      return FALSE;
   if (!*mtxD) {
      *mtxD=mtxS;
      *nrlD=nrlS;
      *nrhD=nrhS;
      *nclD=nclS;
      *nchD=nchS;
      return TRUE;
   }

   rowS=nrhS-nrlS+1;
   colS=nchS-nclS+1;
   i=(*nrhD-*nrlD+1)%rowS;
   j=(*nchD-*nclD+1)%colS;
   /*if (i||j) return FALSE; */ /* Both row. and col. should be matched before */
   if (j) return FALSE;  /* Only col. should be matched with what's got before */
   if (bBottomAttachment) { /* on the most-right bottom side */
      kc=nclS-(*nchD-colS+1);      
         for (i=nrlS;i<=nrhS;i++)
            mtxS[i]+=kc;
         nclS-=kc;
         nchS-=kc;
      /**/
      k=0;
      for (i=*nrhD;i>=*nrlD;i--) {
         for (j=*nchD-colS+1;j<=*nchD;j++) {
            if (strcmp((*mtxD)[i][j],nullStr)) {
               k=1;
               break;
            }            
         }
         if (k) break;
      }
      k=i; /* If nullStrBlock is not at the lower-right, k is *nrhD */
      for (i=k+1;i<*nrhD && i<rowS;i++) {
         for (j=*nchD-colS+1;j<=*nchD;j++) {
            free((*mtxD)[i][j]);
         }
      }
      /**/
      kr=nrlS-(  k  +1);
         mtxS+=kr;
         nrlS-=kr;
         nrhS-=kr;
   } else { /* rightAttachment */
      kc=nclS-(*nchD+1);
         for (i=nrlS;i<=nrhS;i++)
            mtxS[i]+=kc;
         nclS-=kc;
         nchS-=kc;
      kr=nrlS-(*nrlD);
         mtxS+=kr;
         nrlS-=kr;
         nrhS-=kr;
   }
   nrhNew=MAX(*nrhD,nrhS);
   nchNew=MAX(*nchD,nchS);
   AFReallocStringMatrix (mtxD,*nrlD,*nrhD,*nclD,*nchD,nrhNew,nchNew);
   for (i=nrlS;i<=nrhS;i++) {
      for (j=nclS;j<=nchS;j++) {
         (*mtxD)[i][j]=strdpl(mtxS[i][j]);
      }
   }
   AFSetNullStrToMatrix(*mtxD,*nrlD,nrhNew,*nclD,nchNew,nullStr);
   for (i=nrlS;i<=nrhS;i++) mtxS[i]-=kc;
   *nrhD=nrhNew;
   *nchD=nchNew;
   return TRUE;
}

static
int AFReallocStringMatrix ( mtx,nrl,nrh,ncl,nch,nrhNew,nchNew )
   char ****mtx;
   int nrl,nrh,ncl,nch,nrhNew,nchNew;
{
   char ***m,**v;
   int i;

   if (nch<nchNew) {
      for (i=nrl;i<=nrh;i++) {
         v=alloString1d(ncl,nchNew);
         memset((char*)&(v[nch+1]),0,sizeof(char*)*(nchNew-nch));
         memcpy(v+ncl,(*mtx)[i]+ncl,(nch-ncl+1)*sizeof(char*));
         free((*mtx)[i]+ncl);
         (*mtx)[i]=v;
      }
   }
   if (nrh<nrhNew) {
      m=salloc(char**,nrhNew-nrl+1);
      memcpy(m,*mtx+nrl,(nrh-nrl+1)*sizeof(char**));
      m-=nrl;
      for (i=nrh+1;i<=nrhNew;i++) {
         m[i]=alloString1d(ncl,nchNew);
         memset((char*)&(m[i][ncl]),0,sizeof(char*)*(nchNew-ncl+1));
      }
      free(*mtx+nrl);
      *mtx=m;
   }
   return TRUE;
}

static
int AFAddStrToStrArray( array,arrayLength,nTotal,str )
   char ***array;
   int *arrayLength,*nTotal;
   char *str;
{
   char **ptr;
   int i;

   if (!*array) {
      *arrayLength=100;
      *array=alloString1d(0,*arrayLength);
      *nTotal=0;
   }
   if (*arrayLength==*nTotal) {
      *arrayLength+=100;
      ptr=alloString1d(0,*arrayLength);
      memcpy(ptr,*array,*nTotal*sizeof(char*));
      *array=ptr;
   }
   for (i=0;i<*nTotal;i++) {
      if (!strcmp((*array)[i],str))
         return FALSE;
   }
   (*array)[*nTotal]=str;
   return ++(*nTotal);
}

static
int AFGetXYNoOfMatrix( matrix,nrl,nrh,ncl,nch,x,y,nr,nc )
   char ***matrix;
   int nrl,nrh,ncl,nch;
   char *x,*y;
   int *nr,*nc;
{
   int i,j;

   for (i=nrl;i<=nrh;i++) {
      if (strequ(matrix[i][0],x)) break;
   }
   for (j=ncl;j<=nch;j++) {
      if (strequ(matrix[0][j],y)) break;
   }
   if (i>nrh||j>nch) return FALSE;
   *nr=i;
   *nc=j;
   return TRUE;
}

static
int pDeleteFuncForOneToOneNode( node )
   AFNODEONETOONE *node;
{
   freeEx(node->pAlias);
   freeEx(node->pPattern);
   freeEx(node->pFormat);
   freeEx(node->pEquation);
   return (1);
}

static
int pDeleteFuncForOneToManyNode( node )
   AFNODEONETOMANY *node;
{
   freeEx(node->pBeginning);
   freeEx(node->pEnding);
   freeEx(node->pBlockSelections);
   freeEx(node->pOtherColumns);
   freeEx(node->pFormat);
   freeEx(node->pEquation);
   freeEx(node->script.pWorkFolder);
   freeEx(node->script.pExtractor);
   freeEx(node->script.pJoiner);
   return (1);
}

static
int AFPostNumericProcessOnEachColumn( nType,pFormat,pppString2d,nrl,pNrh,ncl,nch )
   int nType;
   char *pFormat,***pppString2d;
   int nrl,*pNrh,ncl,nch;
{
   int nRow,nCol,nCount;
   double *pVec,dValue;

   if (nType==AF_NONE) return FALSE;
   if (!pppString2d) return FALSE;

   pVec=dvector(1,*pNrh-nrl+1);
   for (nCol=ncl;nCol<=nch;nCol++) {
      nCount=1;
      for (nRow=nrl;nRow<=*pNrh;nRow++) {
         if (!pppString2d[nRow][nCol] ||
            strequ(pppString2d[nRow][nCol],AF_NULL_STRING)) continue;
         pVec[nCount]=atof(pppString2d[nRow][nCol]);
         nCount++;
      }
      nCount--;
      nRow=nrl; /* 2001.0414 */
      freeEx(pppString2d[nRow][nCol]);
      if (nCount>0) {
         dValue=AFGetVectorValueByType(pVec,nCount,nType);
         pppString2d[nRow][nCol]=
            AFDuplicateString(dtos(dValue,"%g"),pFormat,(char*)0,0.0,0.0);
      } else {
         pppString2d[nRow][nCol]=strdpl(AF_NULL_STRING);
      }
   }
   free_dvector(pVec,1,*pNrh-nrl+1);
   for (nRow=nrl+1;nRow<=*pNrh;nRow++) {
      for (nCol=ncl;nCol<=nch;nCol++) freeEx(pppString2d[nRow][nCol]);
      free((char*)(pppString2d[nRow]+ncl));
   }
   *pNrh=nrl;
   return TRUE;
}

static
int AFPostCompositeProcessOnEachColumn( nType,nBlock,pFormat,ppppString2d,nrl,pNrh,ncl,nch )
   int nType,nBlock;
   char *pFormat,****ppppString2d;
   int nrl,*pNrh,ncl,nch;
{
   char ***Matrix;
   double *pVec,dValue;
   int nRowOfBlock,nRowNew,nRow,nCol,nIndex,nCount,nRowTemp;

   Matrix=*ppppString2d;
   if (nType==AF_NONE) return FALSE;
   if (nBlock==1) return FALSE;
   if ((*pNrh-nrl+1)%nBlock) return FALSE;
   nRowOfBlock=(int)((*pNrh-nrl+1)/nBlock);
   nRowNew=nRowOfBlock+nrl-1;

   pVec=dvector(1,nBlock);
   for (nCol=ncl;nCol<=nch;nCol++) {
      for (nRow=nrl;nRow<=nRowNew;nRow++) {
         nCount=1;
         for (nIndex=0;nIndex<nBlock;nIndex++) {
            nRowTemp=nRow+nIndex*nRowOfBlock;
            if (!Matrix[nRowTemp][nCol] ||
               strequ(Matrix[nRowTemp][nCol],AF_NULL_STRING)) continue;
            pVec[nCount]=atof(Matrix[nRowTemp][nCol]);
            nCount++;
         }
         nCount--;
         freeEx(Matrix[nRow][nCol]);
         if (nCount>0) {
            dValue=AFGetVectorValueByType(pVec,nCount,nType);
            Matrix[nRow][nCol]=
               AFDuplicateString(dtos(dValue,"%g"),pFormat,(char*)0,0.0,0.0);
         } else {
            Matrix[nRow][nCol]=strdpl(AF_NULL_STRING);
         }
      }
   }
   free_dvector(pVec,1,nBlock);
   for (nRow=nRowNew+1;nRow<=*pNrh;nRow++) {
      for (nCol=ncl;nCol<=nch;nCol++) freeEx(Matrix[nRow][nCol]);
      free((char*)(Matrix[nRow]+ncl));
   }
   nCount=nRowNew-nrl+1;
   Matrix=salloc(char**,nCount);
   memcpy(Matrix,*ppppString2d+nrl,sizeof(char**)*nCount);
   Matrix-=nrl;
   free((char*)(*ppppString2d+nrl));
   *ppppString2d=Matrix;
   *pNrh=nRowNew;
   return TRUE;
}

static
int AFGetMaxFileCountPerSplit( qFileNames )
   const char *qFileNames;
{
   int nCount,nMax;
   char *pFiles,*pFile,qSpaceChars[]="\t\r\n";

   if (!qFileNames || !*qFileNames || !strlen(qFileNames)) return 0;
   pFiles=strvcat((char*)qFileNames,AF_COMMAND_LINE_END,0);
   pFile=strtok(pFiles,qSpaceChars);
   nCount=nMax=0;
   while (pFile) {
      strtrim(pFile);
      if (pFile[0]==AF_SPLIT_INDICATOR) {
         nMax=max(nCount,nMax);
         nCount=0;
      } else
         nCount++;
      pFile=strtok(NULL,qSpaceChars);
   }
   free(pFiles);
   return nMax;
}

static
double AFGetVectorValueByType( pVecB1,nCount,nType )
   double *pVecB1;
   int nCount,nType;
{
   double dValue=0.0;
   int i,j;

   switch(nType) {
   case AF_AVERAGE:
      dValue=0;
      for (i=1;i<=nCount;i++) dValue+=pVecB1[i];
      dValue/=(double)nCount;
      break;
   case AF_MEDIAN:
      mdian2(pVecB1,nCount,&dValue);
      break;
   case AF_MIN:
      dValue=pVecB1[1];
      for (i=2;i<=nCount;i++) dValue=min(dValue,pVecB1[i]);
      break;
   case AF_MAX:
      dValue=pVecB1[1];
      for (i=2;i<=nCount;i++) dValue=max(dValue,pVecB1[i]);
      break;
   case AF_RANGE: {
      double dMin,dMax;
      dMin=dMax=pVecB1[1];
      for (i=2;i<=nCount;i++) {
         dMin=min(dMin,pVecB1[i]);
         dMax=max(dMax,pVecB1[i]);
      }
      dValue=dMax-dMin;
                  }
      break;
   case AF_STDDEV: {
      double s,ave,svar;
      s=0.0;
      for (j=1;j<=nCount;j++) s+=pVecB1[j];
      ave=s/nCount;
      svar=0.0;
      for (j=1;j<=nCount;j++) {
         s=pVecB1[j]-ave;
         svar+=(s*s);
      }
      svar/=(nCount-1);
      dValue=sqrt(svar);
   }  break;
   case AF_SUM:
      dValue=0;
      for (i=1;i<=nCount;i++) dValue+=pVecB1[i];
      break;
   case AF_COUNT:
      dValue=(double)nCount;
      break;
   }

   return dValue;
}

/******************************************************************************/
/* anyfind.c */
