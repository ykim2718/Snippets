/*
 * AnyfindClient.c
 * shik96@samsung.co.kr, 2K.0810
 */

#include "str.h"
#include "../Anyfind/Iface.h"

const GUID IID_IANYFIND = 
{0x756c7981, 0x6d0e, 0x11d4, {0x96, 0x22, 0x0, 0x0, 0xe8, 0xc3, 0x6, 0x4a}};
// {756C7982-6D0E-11d4-9622-0000E8C3064A}
const GUID IID_ANYFINDCLASS = 
{0x756c7982, 0x6d0e, 0x11d4, {0x96, 0x22, 0x0, 0x0, 0xe8, 0xc3, 0x6, 0x4a}};

#include "myCore.h"
#include "tools.h"
#include "AnyFindClient.h" /* 2001.0411 */

int GargamelOpen( char **pAnyfind, char **spMessage /* static */ )
{
   IAnyfind *pInterface; /* interface virtual table pointer */
   long hResult;

   CoInitialize(NULL);
   *pAnyfind=*spMessage=0;
   hResult=CoCreateInstance(
      &IID_ANYFINDCLASS,
      NULL,
      CLSCTX_INPROC_SERVER,
      &IID_IANYFIND,
      (void**)&pInterface);
   if (FAILED(hResult)) {
      switch (hResult) {
      case REGDB_E_CLASSNOTREG :
         *spMessage=
            "shik96@samsung.co.kr \n\n"
            "Watch out ! (hResult=REGDB_E_CLASSNOTREG) \n\n"
            "A specified class is not registered in the registration \n"
            "database. Also can indicate that the type of server you \n"
            "requested in the CLSCTX enumeration is not registered or \n"
            "the values for the server types in the registry are corrupt.";
         break;
      case CLASS_E_NOAGGREGATION :
         *spMessage=
            "shik96@samsung.co.kr \n\n"
            "Watch out ! (hResult=CLASS_E_NOAGGREGATION) \n\n"
            "This class cannot be created as part of an aggregate. ";
         break;
      }
      CoUninitialize();
      return FALSE;
   }
   *pAnyfind=(char*)pInterface;
   return TRUE;
}

int GargamelClose( char *pAnyfind, GargamelInfo *pInfo )
{
   IAnyfind *pI;
   if (!pInfo) {
      CoUninitialize();
      return TRUE;
   }
   pI=(IAnyfind*)pAnyfind;
   if (pInfo->vb1PatternAlias)
      ((IAnyfindVtbl*)(pI->lpVtbl))->_AFReleaseString1D(
      pI,pInfo->vb1PatternAlias,1,pInfo->nPattern);
   if (pInfo->vb1SplitAlias)
      ((IAnyfindVtbl*)(pI->lpVtbl))->_AFReleaseString1D(
      pI,pInfo->vb1SplitAlias,1,pInfo->nSplit);
   if (pInfo->dpMessage)
      ((IAnyfindVtbl*)(pI->lpVtbl))->_AFReleaseString(
      pI,pInfo->dpMessage);
   free(pInfo);
   CoUninitialize();
   return TRUE;
}

int GargamelDoit (
   /* vftbl pointer */
   const char *pAnyfind,
   /* in */
   const char *sFilePattern,const char *sFileSplit,const char *sFileToWrite,
   int nSearchType,int nColMatrixType,int nPostProcessType,
   int bNumericAlias,int bComposite,
   /* out */
   GargamelInfo **pInformation
   )
{
#define ANYFINDVFPTR ((IAnyfindVtbl*)(pI->lpVtbl))
   IAnyfind *pI;
   GargamelInfo *pInfo;
   AFLIST *list;
   char ***string2d;int nrl;int nrh;int ncl;int nch;
   int nResult,nTmp,nAliasCount;
   char *sBuffer,*sTmp1,*sTmp2,*sPattern,*sSplit,**pAliasString1d;
   
   pI=(IAnyfind*)pAnyfind;
   pInfo=*pInformation=salloc(GargamelInfo,1);
   memset(pInfo,0,sizeof(GargamelInfo));
   sBuffer=(char*)0;
   string2d=(char***)0;
   /**/
   nResult=myFileToStream(sFilePattern,&sBuffer);
   if (!nResult) {
      pInfo->dpMessage=strvcat(
         "Error @GargamelDoit, File Not Found : ",
         sFilePattern,
         0
         );
      goto F;
   }
   nResult=ANYFINDVFPTR->_AFGetParametersFromScript(pI,
      sBuffer,
      &sTmp1,&nTmp,&nTmp,&nTmp,&nTmp,
      &sPattern,&sTmp2);
   freeEx(sBuffer);
   ANYFINDVFPTR->_AFReleaseString(pI,sTmp1);
   ANYFINDVFPTR->_AFReleaseString(pI,sTmp2);
   nResult=myFileToStream(sFileSplit,&sBuffer);
   if (!nResult) {
      pInfo->dpMessage=strvcat(
         "Error @GargamelDoit, File Not Found : ",
         sFileSplit,
         0
         );
      goto F;
   }
   nResult=ANYFINDVFPTR->_AFGetParametersFromScript(pI,
      sBuffer,
      &sTmp1,&nTmp,&nTmp,&nTmp,&nTmp,
      &sTmp2,&sSplit);
   freeEx(sBuffer);
   ANYFINDVFPTR->_AFReleaseString(pI,sTmp1);
   ANYFINDVFPTR->_AFReleaseString(pI,sTmp2);
   ANYFINDVFPTR->_AFOpen(pI,
      &list,
      nSearchType,
      1,
      nPostProcessType,
      0,
      bComposite
      );
   nResult=ANYFINDVFPTR->_AFAddNodes(pI,
      list,
      0, // AF_WhiteSpace=0
      sPattern);
   if (!nResult) {
      char *spMessage;
      ANYFINDVFPTR->_AFGetErrorMessagePointer(pI,&spMessage);
      pInfo->dpMessage=strvcat(
         "Error @GargamelDoit, ambiguous search patterns be there !",
         spMessage,
         0
         );
      goto F;
   }
   string2d=0;
   nrl=nrh=ncl=nch=0;
   nResult=ANYFINDVFPTR->_AFExtractEx(pI,
      list,
      sSplit,
      &string2d,&nrl,&nrh,&ncl,&nch,
      NULL);
   if (!nResult) {
      char *spMessage;
      ANYFINDVFPTR->_AFGetErrorMessagePointer(pI,&spMessage);
      pInfo->dpMessage=strdpl(spMessage);
      goto F;
   }
   if (nColMatrixType) {
      nTmp=nrh-nrl+1;
      pInfo->nColCountPerBlock=
         ANYFINDVFPTR->_AFGetColumnCountPerBlock(pI,list);
      ANYFINDVFPTR->_AFExchangeRowColPerBlock(pI,
         &string2d,&nrl,&nrh,&ncl,&nch,
         pInfo->nColCountPerBlock,
         nColMatrixType);
      pInfo->nColCountPerBlock=nTmp;
   } else {
      pInfo->nColCountPerBlock=1;
   }
   pInfo->nRow=(nrh-nrl+1);
   pInfo->nCol=(nch-ncl+1);
   switch (nColMatrixType) {
   case AF_ROWCOL_EXCHANGE_NONE : // 0
   case AF_ROWCOL_EXCHANGE_BYPATTERN : // 1
   case AF_ROWCOL_EXCHANGE_BYPATTERN2 : // 2
      nResult=ANYFINDVFPTR->_AFGetPatternAliasArrayB1(pI,
         list,bNumericAlias,
         &(pInfo->vb1PatternAlias),&(pInfo->nPattern));
      if (!nResult) {
         char *spMessage;
         ANYFINDVFPTR->_AFGetErrorMessagePointer(pI,&spMessage);
         pInfo->dpMessage=strdpl(spMessage);
         goto F;
      }
      pAliasString1d=pInfo->vb1PatternAlias;
      nAliasCount=pInfo->nPattern;
      nResult=ANYFINDVFPTR->_AFGetSplitAliasArrayB1(pI,
         sSplit,"\n",0,
         &(pInfo->vb1SplitAlias),&(pInfo->nSplit));
      break;
   case AF_ROWCOL_EXCHANGE_BYSPLIT : // 3
      nResult=ANYFINDVFPTR->_AFGetSplitAliasArrayB1(pI,
         sSplit,"\n",bNumericAlias,
         &(pInfo->vb1SplitAlias),&(pInfo->nSplit));
      if (!nResult) {
         char *spMessage;
         //ANYFINDVFPTR->_AFGetErrorMessagePointer(pI,&spMessage);
         spMessage="Warning, No Numeric Split Alias "
                   "Under bNumbericAlias=TRUE : Execution Canceled !";
         pInfo->dpMessage=strdpl(spMessage);
         goto F;
      }
      pAliasString1d=pInfo->vb1SplitAlias;
      nAliasCount=pInfo->nSplit;
      nResult=ANYFINDVFPTR->_AFGetPatternAliasArrayB1(pI,
         list,0,
         &(pInfo->vb1PatternAlias),&(pInfo->nPattern));
      break;
   default:
      pAliasString1d=0;
      nAliasCount=0;
      pInfo->dpMessage=strdpl("Error, Something wrong take placed !");
      goto F;
   }
   if (sFileToWrite) {
      nResult=ANYFINDVFPTR->_AFPutItToStream(pI,
         list,nColMatrixType,nAliasCount,pAliasString1d,
         string2d,nrl,nrh,ncl,nch,&sBuffer);
      nResult=myStreamToFile(sFileToWrite,sBuffer);
   }
   /**/
   ANYFINDVFPTR->_AFClose(pI,list);
   /**/
   nResult=TRUE;
   if (!nResult) { F:
      if (pInfo->vb1PatternAlias)
         ANYFINDVFPTR->_AFReleaseString1D(
         pI,pInfo->vb1PatternAlias,1,pInfo->nPattern);
      pInfo->nPattern=0;
      if (pInfo->vb1SplitAlias)
         ANYFINDVFPTR->_AFReleaseString1D(
         pI,pInfo->vb1SplitAlias,1,pInfo->nSplit);
      pInfo->nSplit=0;
      pInfo->nRow=pInfo->nCol=pInfo->nColCountPerBlock=0;
      nResult=FALSE;
   }
   if (sBuffer)
      ANYFINDVFPTR->_AFReleaseString(pI,sBuffer);
   if (string2d && *string2d)
      ANYFINDVFPTR->_AFReleaseString2D(pI,string2d,nrl,nrh,ncl,nch);
   /**/
   return nResult;
#undef ANYFINDVFPTR
}

int GargamelGetPostProcessType(
   char ***pppTable,
   int *nTable
   )
{
   *pppTable=(char**)qNumericPostProcessStrings;
   *nTable=sizeof(qNumericPostProcessStrings)/sizeof(qNumericPostProcessStrings[0]);
   return *nTable;
}