/******************************************************************************/
/*                           file name : plot.c                               */
/*                         description : plot                                 */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43230913-43240627                    */
/* 4324 0724-0730,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4325 0810-1118,1202,____,____,____,____,____,____,____,____,____,____,____ */
/* 4326 0318,0920,0124,0622,____,____,____,____,____,____,____,____,____,____ */
/* 4328 1021,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4329 0122,0223,0411,0423,0612,0911,____,____,____,____,____,____,____,____ */
/* 4330 0717-0811,0826,0831,0930,____,____,____,____,____,____,____,____,____ */
/* 4331 0604,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0301-0331,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0317,0403-0412,0502-0626,0821-0913,1008,1012,1211,____,____,____,____ */
/* 4334 0109-0110,0222,0302-0318,0328,0410,0514,0607,0814,0815,____,____,____ */
/* 4335 1015,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4336 0211-0311,0320,0522,0824,0902,0905,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <setjmp.h>

#include "myCore.h"
#include "blob.h"
#include "nrecipe.h"
#include "any.h"
#include "tools.h"
#include "number.h"
#include "gecore.h"
#include "geplot.h"
#include "plotsymb.h"
#include "plotse.h"
#include "plot.h"

#include "../Grapher/AnyfindClient.h" /* 2001.0411 */

/******************************************************************************/

/*---m-a-i-n------------------------------------------------------------------*/

static int DoPreProcessor();                      /* 1st */
static int DoPage();                              /* 8th */
static int DoAttribute();                         /* 2nd */
static int CreateMatrixFromFile();              /* 3rd */
static int ModifyMatrix();                      /* 5th */
static int AdjustColumnSelection();            /* 4th */
static int CalculateColumnBoundaries();         /* 7th */
static int DoSymbol2D();
static int DoAxis2D();
static int DoText2D();
static int ModifyMatrixByUserFunction();        /* 6th */
static int DoXfrm2D();

/*---s-u-b-s------------------------------------------------------------------*/

       int GetBoxSymbolData _((
           double*,int,double,double*,double*,double*,double*,double*,double*));
static void EchoMatrixAndColSelection _((PLTNODE*,const char *pComment));
static int GetIndexOfDataFileInformation _((char*,const int,const GARGAMELINFO*));
static int FillupPlotColNumbers _((int,int,int,int*,int,int*,int**));
static int IsValidColumnNumber _((int,int,int,int,int,double**));
static int AttachPreviousMatrix();
static int GetColSelectionBlockCount _((int *iVec,int nStart,int nEnd));
static int GetColSelectionBlockFirstLast _((
           int *iVec,int nStart,int nEnd,int nBlock,int *nFirst,int *nLast));
static int GetDefaultSymbolLegend _((int nIndex,LEGEND *pLegend));
static int DoPreProcessorFilesExist _((
           const char *qHomePath,const char *qFile ));
static int GetTemporaryDataFileName _(( const char *qName,int nIndex,char **ppReturn ));
static int AddTemporaryFileName _((PLTLIST *pList,const char *pTemporaryFile ));

static int dupPltMtrx();
static int cmpPltMtrxRange();

static int GetMatrixMinMaxOfCols();
static int GetScaleBoundary();
static int GetAxisTickSpace();

       double GetTextXPitchOfNorWin();
       double GetTextYPitchOfNorWin();

       double GetXPosOfNorWin();
       double GetYPosOfNorWin();
       double GetXPosOfWldWin();
       double GetYPosOfWldWin();

/*---d-a-t-a-c-o-n-v-e-r-t-f-u-n-c--------------------------------------------*/

static double dummy();
static double iicnorm();

/******************************************************************************/
/******************************************************************************/

int GROpen( ppList,pFile,pScript )
   PLTLIST **ppList;
   const char *pFile,*pScript;
{
   extern int DoScriptCommandNull _(( ));
   extern int DoScriptCommandPBEG _(( ));
   extern int DoScriptCommandGXFM _(( ));
   extern int DoScriptCommandGTXT _(( ));
   extern int DoScriptCommandGOUT _(( ));
   extern int DoScriptCommandEXEC _(( ));
   extern int DoScriptCommandPLOT _(( ));
   extern int DoScriptCommandATTR _(( ));
   extern int DoScriptCommandDATA _(( ));
   extern int DoScriptCommandXYZB _(( ));
   extern int DoScriptCommandSYMB _(( ));
   extern int DoScriptCommandAXIS _(( ));
   extern int DoScriptCommandTEXT _(( ));
   extern int DoScriptCommandUFUN _(( ));
   extern int DoScriptCommandVIEW _(( ));
   extern int DoScriptCommandError _(( ));
   DLL *pDll=0;
   DLN *pDln=0,*pNext;
   int bResult;
   extern char *gpGRLog; /* in plotio.c */
   extern char *gpGRErrorLog; /* in plotio.c */

   gpGRLog=NULL;
   gpGRErrorLog=NULL;

   if (!pFile) {
      Echo(0,"Error @GROpen(), a missing file name...");
      return FALSE;
   }

   AnyOpenLinkedObject(ppList,sizeof(PLTLIST));
   memset(&((*ppList)->Glob),0,sizeof(PLTGLOB));
   (*ppList)->Glob.pName=strdplEx(pFile);
   (*ppList)->nTotal=0;
   (*ppList)->pTemporaryFiles=0;
 
   //mySetHeapDebugger(TRUE);///

   if (pScript) {
      if (!SEOpen(pScript,&pDll)) {
         Echo(0,"Error @GROpen(), something wrong in script.");
         goto F;
      }
   } else {
      char *pStream=0;
      if (!myFileToStream((*ppList)->Glob.pName,&pStream)) {
         Echo(0,"Error @GROpen(), ...",(*ppList)->Glob.pName);
         freeEx(pStream);
         goto F;
      }
      if (!SEOpen(pStream,&pDll)) {
         Echo(0,"Error @GROpen(), something wrong in script file.");
         freeEx(pStream);
         goto F;
      }
      free(pStream);
   }
      
   //myChkHeapDebugger();///   

   Echo("***** %s,(c)Kim,YongShik ***** \n",GRCoreVersion,NULL);

   SEMacroOpen();
   for (pDln=pDll->head,pNext=pDln->next;pDln;
        pDln=pNext,pNext=pDln?pDln->next:NULL) {
      if ((strequ(pDln->tok,PLOTSCRIPT_DEFINE))) {
         if (pDln->next && pDln->next->next) {
            SEMacroDefine(pDln->next->tok,pDln->next->next->tok);
            pDln=pDln->next->next;
         } else {
            Echo("Error @GROpen(),  something wrong with %s syntax in SCRIPT.",
               PLOTSCRIPT_DEFINE);
            SEClose(pDll);
            goto F;
         }
         continue;
      }
      bResult=SEMacroRun(&(pDln->tok));
      if (bResult) {
         DLL *pDllTemp;
         DLN *pDlnTemp;
         int nLine=(*(int*)((pDln->tok)+strlen(pDln->tok)+1));
         DLLGetItFrStream(pDln->tok,PLOTSCRIPT_COMMENT_CHAR," \t\f\n",&pDllTemp);
         for (pDlnTemp=pDllTemp->head;pDlnTemp;pDlnTemp=pDlnTemp->next) {
            DLLInsToken(pDll,pDln,strdplwid(pDlnTemp->tok,nLine));
         }
         DLLCloseWMA(pDllTemp);
         DLLDelNodeWMA(pDll,pDln);
      }
   }
   SEMacroClose();

   SEReorderLevel2nd(pDll); /* 2K.0830 */
   SEDeleteLevel4thAmbiguity(pDll); /* 2K.1114 */

   SECmdOpen(32);
   SECmdSetProcedure(
      GR_COMMAND_PBEG,PLOTSCRIPT_BEGINNING,DoScriptCommandPBEG,
      GR_COMMAND_PEND,PLOTSCRIPT_END,DoScriptCommandNull,
      GR_COMMAND_DEFN,PLOTSCRIPT_DEFINE,DoScriptCommandNull,
      GR_COMMAND_GLOB,PLOTSCRIPT_GLOB,DoScriptCommandNull,
      GR_COMMAND_GXFM,PLOTSCRIPT_GXFM,DoScriptCommandGXFM,
      GR_COMMAND_GOUT,PLOTSCRIPT_GOUT,DoScriptCommandGOUT,
      GR_COMMAND_GTXT,PLOTSCRIPT_GTXT,DoScriptCommandGTXT,
      GR_COMMAND_EXEC,PLOTSCRIPT_EXEC,DoScriptCommandEXEC,
      GR_COMMAND_PLOT,PLOTSCRIPT_PLOT,DoScriptCommandPLOT,
      GR_COMMAND_ATTR,PLOTSCRIPT_ATTR,DoScriptCommandATTR,
      GR_COMMAND_DATA,PLOTSCRIPT_DATA,DoScriptCommandDATA,
      GR_COMMAND_XYZB,PLOTSCRIPT_XYZB,DoScriptCommandXYZB,
      GR_COMMAND_SLCT,PLOTSCRIPT_SYMB,DoScriptCommandSYMB,
      GR_COMMAND_SLCT,PLOTSCRIPT_SLCT,DoScriptCommandSYMB,
      GR_COMMAND_AXIS,PLOTSCRIPT_AXIS,DoScriptCommandAXIS,
      GR_COMMAND_TEXT,PLOTSCRIPT_TEXT,DoScriptCommandTEXT,
      GR_COMMAND_UFUN,PLOTSCRIPT_UFUN,DoScriptCommandUFUN,
      GR_COMMAND_VIEW,PLOTSCRIPT_VIEW,DoScriptCommandVIEW,
      -1);
   if (!SECmdRun(pDll,(char*)(*ppList),DoScriptCommandError)) goto F;
   SECmdClose();

   //myChkHeapDebugger();///
   //mySetHeapDebugger(FALSE);///

   SEClose(pDll);

   return TRUE;
/* F: GRClose(*ppList); 20030223 */
F:   *ppList=NULL;
   return FALSE;
}

int GRClose( pList )
   PLTLIST *pList;
{
   int nIndex;
   extern char *gpGRLog; /* in plotio.c */
   extern char *gpGRErrorLog; /* in plotio.c */

   freeEx(gpGRLog);
   freeEx(gpGRErrorLog);
   if (!pList) return TRUE; /* 20030222 */
   freeEx(pList->Glob.pName);
   freeEx(pList->Glob.pTitle);
   freeEx(pList->Glob.pHomePath);
   for (nIndex=0;nIndex<noof(pList->Glob.qFile);nIndex++) {
      if (!pList->Glob.qFile[nIndex].pInput) break;
      freeEx(pList->Glob.qFile[nIndex].pInput);
      freeEx(pList->Glob.qFile[nIndex].pOption);
      freeEx(pList->Glob.qFile[nIndex].pOutput);
   }
   freeEx(pList->pTemporaryFiles);
   AnyCloseLinkedObject(pList,FreePlot);

   return TRUE;
}

int GRExecute( pList,ppBlobList )
   PLTLIST *pList;
   BLOBLIST **ppBlobList;
{
   extern int CreatePlotBlobList _(( ));
   PLTNODE *pNode;
   int i;

   Echo(".Pre-Processing ... <Gargamel>\n");
   if (!DoPreProcessor(pList)) return FALSE;

   Echo(".Total %d plot(s).\n",pList->nTotal);
   Echo("\n");

   pNode=pList->pHead;
   i=1;
   do { 
      Echo("-C-A-L-C-U-L-A-T-I-N-G- +%d\n",i++);
      Echo("-DoAttribute()-\n");
      if (!DoAttribute(pNode)) return FALSE;
      Echo("-CreateMatrixFromFile()-\n"); /* Create matrix */
      if (!CreateMatrixFromFile(pNode,noof(pList->Glob.qFile),&(pList->Glob.qFile)))
         return FALSE;
      Echo("-AdjustColumnSelection()-\n"); /* Check and Create XnY selection */
      if (!AdjustColumnSelection(pNode,noof(pList->Glob.qFile),&(pList->Glob.qFile)))
         return FALSE;
      Echo("-ModifyMatrix()-\n"); /* Massage matrix after fixing XnY */
      if (!ModifyMatrix(pNode)) return FALSE;
      Echo("-ModifyMatrixByUserFunction()-\n");  /* Calculate matrix */
      if (!ModifyMatrixByUserFunction(pNode)) return FALSE;
      Echo("-CalculateColumnBoundaries()-\n"); /* Verify XnY against matrix */
      if (!CalculateColumnBoundaries(pNode)) return FALSE;
      Echo("-DoXfrm2D()-\n");  /* Calculate scale of each XnY and matrix */
      if (!DoXfrm2D(pNode)) return FALSE;
   } while (pNode=pNode->next);
      Echo("\n");

   pNode=pList->pHead;
   i=1;
   do {      
      Echo("-F-O-R-M-A-T-I-N-G- +%d\n",i++);
      Echo("-DoSymbol2D()-\n"); /* Form the symbol/legend of XnY */
      if (!DoSymbol2D(pNode)) return FALSE;
      Echo("-DoAxis2D()-\n");
      if (!DoAxis2D(pNode)) return FALSE;
      Echo("-DoText2D()-\n");
      if (!DoText2D(pNode)) return FALSE;
   } while (pNode=pNode->next);
      Echo("\n");
      
   if (!DoPage(pList)) return FALSE;

   /* 20030215 */
   return CreatePlotBlobList(pList,ppBlobList);
}

int AlloPlot( ppPlot )
   PLTNODE **ppPlot;
{
   PLTNODE *pPlot;
 
   pPlot      =salloc(PLTNODE,1);
   pPlot->pAttr=salloc(PLTATTR,1);
   pPlot->pData=salloc(PLTDATA,1);
   pPlot->pSlct=salloc(PLTSLCT,1);
   pPlot->pSlct->Etc.LineMoment.dRange=100.0;
   pPlot->pAxis=salloc(PLTAXIS,1);
   pPlot->pText=salloc(PLTTEXT,1);
   pPlot->pUfun=salloc(PLTUFUN,1);
   pPlot->pXfrm=salloc(PLTXFRM,1);
   *ppPlot     =pPlot;
   return TRUE;
}

int FreePlot( pPlot )
   PLTNODE *pPlot;
{
   int i;
   PUFUN *pUf;
 
   freeEx(pPlot->pAttr);
   if (pPlot->pData) {
      freeEx(pPlot->pData->pName);
      if (pPlot->pData->type!=MATRIX_PREVIOUS) {
         if (pPlot->pData->mtx)
            free_dmatrix(pPlot->pData->mtx,
                         pPlot->pData->nrl,pPlot->pData->nrh,
                         pPlot->pData->ncl,pPlot->pData->nch);
      }
      freeEx(pPlot->pData->vBlockIndex);
      if (pPlot->pData->ppHeader) {
         for (i=0;i<pPlot->pData->nHeader;i++)
            free(pPlot->pData->ppHeader[i]);
         free(pPlot->pData->ppHeader);
      }
      free(pPlot->pData);
   }
   if (pPlot->pSlct) {
      if (pPlot->pSlct->xNo)
         free(pPlot->pSlct->xNo);
      if (pPlot->pSlct->yNo)
         free(pPlot->pSlct->yNo);
      if (pPlot->pSlct->zNo)
         free(pPlot->pSlct->zNo);
      if (i=pPlot->pSlct->nLegendTotal) {
         while (i--) freeEx((pPlot->pSlct->pLegend)[i].pText);
         free(pPlot->pSlct->pLegend);
      }
      free(pPlot->pSlct);
   }
   if (pPlot->pAxis) {
      for (i=0;i<noof(pPlot->pAxis->xAxis);i++) {
         if (!pPlot->pAxis->xAxis[i]) break;
         freeEx(pPlot->pAxis->xAxis[i]->pLabelFormat);
         freeEx(pPlot->pAxis->xAxis[i]->pLabelEquation);
         freeEx(pPlot->pAxis->xAxis[i]->pTitle);
      }
      for (i=0;i<noof(pPlot->pAxis->yAxis);i++) {
         if (!pPlot->pAxis->yAxis[i]) break;
         freeEx(pPlot->pAxis->yAxis[i]->pLabelFormat);
         freeEx(pPlot->pAxis->yAxis[i]->pLabelEquation);
         freeEx(pPlot->pAxis->yAxis[i]->pTitle);
      }
      for (i=0;i<noof(pPlot->pAxis->zAxis);i++) {
         if (!pPlot->pAxis->zAxis[i]) break;
         freeEx(pPlot->pAxis->zAxis[i]->pLabelFormat);
         freeEx(pPlot->pAxis->zAxis[i]->pLabelEquation);
         freeEx(pPlot->pAxis->zAxis[i]->pTitle);
      }
      free(pPlot->pAxis);
   }
   if (pPlot->pText) {
      for (i=0;i<pPlot->pText->nTotal;i++) {
         freeEx(pPlot->pText->qText[i]->pString);
      }   
      free(pPlot->pText);
   }      
   if (pPlot->pUfun) {
      pUf=pPlot->pUfun->pHead;
      while (pUf) {
         freeEx(pUf->pType);
         if (pUf->out.vResult)
            free(pUf->out.vResult);         
         freeEx(pUf->out.pResult);
         freeEx(pUf->pArgument);
         freeEx(pUf->pArgument2);
         freeEx(pUf->pArgument3); /* 20030906 */
         freeEx(pUf->pArgument4); /* 20030906 */
         freeEx(pUf->pSweep);
         pUf=pUf->next;
      }   
      free(pPlot->pUfun);
   }      
   if (pPlot->pXfrm)
      free(pPlot->pXfrm);
   return TRUE;
}

static
int DoPreProcessor( pList )
   PLTLIST *pList;
{
   char *pAnyfind,*spMessage;
   GargamelInfo *pInfo;
   int nResult,nIndex,nTotal,
      nSearchType,nColumnarMatrixType,nPostProcessType,bNumericAlias,bComposite;
   char *pTemporaryFile,*pFirst,*pSecond;

   if (!pList->Glob.qFile[0].pInput)
      return TRUE;

   nResult=GargamelOpen(&pAnyfind,&spMessage);
   if (!nResult) {
      Echo(0,"\nCould not create COM :< \n %s",spMessage);
      return FALSE;
   }

   nIndex=0;
   nTotal=noof(pList->Glob.qFile);
   while (nIndex<nTotal
      && pList->Glob.qFile[nIndex].pInput
      && pList->Glob.qFile[nIndex].pOption) {

      if (pList->Glob.pHomePath && *pList->Glob.pHomePath) { /* 2001.0109 */
         pFirst=strtokbyindex(pList->Glob.qFile[nIndex].pInput,PLTOSCRIPT_PATH_DELIMITER,0);
         pSecond=strtokbyindex(pList->Glob.qFile[nIndex].pInput,PLTOSCRIPT_PATH_DELIMITER,1);
         strtrim(pFirst);
         strtrim(pSecond);
         if (pFirst[0]==PLTOSCRIPT_HOMEPATH_CHAR) {
            strdelete(pFirst,0,1);
            strinsert(&pFirst,0,pList->Glob.pHomePath);
         }
         if (pSecond[0]==PLTOSCRIPT_HOMEPATH_CHAR) {
            strdelete(pSecond,0,1);
            strinsert(&pSecond,0,pList->Glob.pHomePath);
         }
         pList->Glob.qFile[nIndex].pInput=strvcat(
            pFirst,PLTOSCRIPT_PATH_DELIMITER,pSecond,0);
         nResult=DoPreProcessorFilesExist(pList->Glob.pHomePath,pFirst);
         if (nResult) nResult=DoPreProcessorFilesExist(pList->Glob.pHomePath,pSecond);
         freeEx(pFirst);
         freeEx(pSecond);
         if (!nResult) return FALSE;
      }

      GetTemporaryDataFileName(pList->Glob.pName,nIndex+1,&pTemporaryFile);
      pList->Glob.qFile[nIndex].pOutput=pTemporaryFile;

      Echo(".%d>%s|%s|%s",
         nIndex,
         pList->Glob.qFile[nIndex].pInput,
         pList->Glob.qFile[nIndex].pOption, /* includes options */
         pList->Glob.qFile[nIndex].pOutput);
      nSearchType=nColumnarMatrixType=nPostProcessType=bNumericAlias=bComposite=0;
      pSecond=0;
      {
         DLL *l;
         DLN *n;
         DLLGetItFrStream(pList->Glob.qFile[nIndex].pOption,0," \t\f\n",&l);
         for (n=l->head;n;n=n->next) {
            if (!strncmp(n->tok,"-nST=",5))
               nSearchType=atoi(n->tok+5);
            else if (!strncmp(n->tok,"-nCMT=",6))
               nColumnarMatrixType=atoi(n->tok+6);
            else if (!strncmp(n->tok,"-nPPT=",6))
               nPostProcessType=atoi(n->tok+6);
            else if (!strncmp(n->tok,"-bNA=",5))
               bNumericAlias=atoi(n->tok+5);
            else if (!strncmp(n->tok,"-bC=",4))
               bComposite=atoi(n->tok+4);
         }
         DLLCloseWMA(l);
      }
      if (pList->Glob.bReuseGargamelOutputIfExist &&
         myDoesFileExist(pList->Glob.qFile[nIndex].pOutput)) {
         double **ppMtrx;
         int nRow,nCol;
         nResult=GetMtrxFrFile(pList->Glob.qFile[nIndex].pOutput,&ppMtrx,&nRow,&nCol);
         if (!nResult) {
            Echo(0,"\n");
            Echo(0,
               "Error, Woe is me. The data file is changed which is made before.\n%s",
               pList->Glob.qFile[nIndex].pOutput);
            GargamelClose(pAnyfind,NULL);
            return FALSE;
         }
         free_dmatrix(ppMtrx,1,nRow,1,nCol);
         pInfo=NULL;
      } else {
         remove(pList->Glob.qFile[nIndex].pOutput);
         pFirst=strtokbyindex(pList->Glob.qFile[nIndex].pInput,PLTOSCRIPT_PATH_DELIMITER,0);
         pSecond=strtokbyindex(pList->Glob.qFile[nIndex].pInput,PLTOSCRIPT_PATH_DELIMITER,1);
         nResult=GargamelDoit (
            pAnyfind,
            pFirst,pSecond,pList->Glob.qFile[nIndex].pOutput,
            nSearchType,nColumnarMatrixType,nPostProcessType,
            bNumericAlias,bComposite,
            &pInfo
            );
         freeEx(pFirst);
         freeEx(pSecond);
         if (!nResult) {
            Echo(0,"\n");
            Echo(0," %s",pInfo->dpMessage);
            GargamelClose(pAnyfind,pInfo);
            return FALSE;
         }
         Echo(" -> nCCPB=%d\n",pInfo->nColCountPerBlock);
      }
      AddTemporaryFileName(pList,pList->Glob.qFile[nIndex].pOutput); /* 2001.0328 */
      
      nIndex++;
   }

   GargamelClose(pAnyfind,pInfo);

   return TRUE;
}

static 
int DoPage( pList )
   PLTLIST *pList;
{
   /* 20030217
   PLTNODE *pPlot;
   double x1,y1,x2,y2,x,y;

   if (!(pPlot=pList->pHead)) return TRUE;
   if (!(pList->Glob.pTitle)) return TRUE;

   x1=pPlot->pXfrm->norwin.x1;
   y1=pPlot->pXfrm->norwin.y1;
   x2=pPlot->pXfrm->norwin.x2;
   y2=pPlot->pXfrm->norwin.y2;
   while (pPlot=pPlot->next) {
      x1=MIN(x1,pPlot->pXfrm->norwin.x1);
      x2=MAX(x2,pPlot->pXfrm->norwin.x2);
      y1=MAX(y1,pPlot->pXfrm->norwin.y1);
      y2=MAX(y2,pPlot->pXfrm->norwin.y2);
   }
   */
   pList->Glob.TextAttr.alignment=GE_AlignHCenter|GE_AlignBottom;
   /* 20030217
   x=x1+(x2-x1)/2.0;
   y=GetTextYPitchOfNorWin(&(pList->Glob.TextAttr));
   y=y2+y*pList->Glob.dTitleSpaceFactor;
   pList->Glob.x=GetXPosOfWldWin(pList->pHead,x);
   pList->Glob.y=GetYPosOfWldWin(pList->pHead,y);
   */
   return TRUE;
}

static
int DoAttribute( pPlot )
   PLTNODE *pPlot;
{
   if (pPlot->pAttr->type==PLT2D_FLAT3D) {
      if (pPlot->pAttr->zScale!=SCALE_LIN &&
         pPlot->pAttr->zScale!=SCALE_LOG10) {
         Echo(0,
            "Warning @DoAttribute(), Shoule Be zScale==Linear/Log10 Under PLT2D_FLAT3D !\n");
         return FALSE;
      }
   }

   if (pPlot->pAttr->back
   && pPlot->prev) {
      pPlot->pAttr->xScale=pPlot->prev->pAttr->xScale;
      pPlot->pAttr->yScale=pPlot->prev->pAttr->yScale;
      pPlot->pAttr->zScale=pPlot->prev->pAttr->zScale;
      pPlot->pSlct->xlowb=pPlot->prev->pSlct->xlowb;
      pPlot->pSlct->xuppb=pPlot->prev->pSlct->xuppb;
      pPlot->pSlct->ylowb=pPlot->prev->pSlct->ylowb;
      pPlot->pSlct->yuppb=pPlot->prev->pSlct->yuppb;
      pPlot->pSlct->zlowb=pPlot->prev->pSlct->zlowb;
      pPlot->pSlct->zuppb=pPlot->prev->pSlct->zuppb;
      pPlot->pXfrm->norwin.x1=pPlot->prev->pXfrm->norwin.x1;
      pPlot->pXfrm->norwin.y1=pPlot->prev->pXfrm->norwin.y1;
      pPlot->pXfrm->norwin.x2=pPlot->prev->pXfrm->norwin.x2;
      pPlot->pXfrm->norwin.y2=pPlot->prev->pXfrm->norwin.y2;
   }
   GESetGCDefault(pPlot->pAttr->CanvasAttr);
   pPlot->pAttr->CanvasAttr.gc_type=GE_GCPolygon;
   pPlot->pAttr->CanvasAttr.gc_mask=GE_GCMaskFillDefault;
   pPlot->pAttr->CanvasAttr.polyarc_attr=GE_PolyArcFill;
   pPlot->pAttr->CanvasAttr.fill_style=GE_FillStippled;
   pPlot->pAttr->CanvasAttr.stipple=2;
   pPlot->pAttr->CanvasAttr.stipple_width=8;
   pPlot->pAttr->CanvasAttr.stipple_height=8;
   return TRUE;
}

static
int CreateMatrixFromFile( pPlot,nInformation,qInformation )
   PLTNODE *pPlot;
   const int nInformation;
   const GARGAMELINFO *qInformation;
{
   PLTNODE *prevPlt;
   int bResult,nIndex;

   switch (pPlot->pData->type) {
   case MATRIX_FILE         : Echo(".MATRIX_FILE\n");        break;
   case MATRIX_PREVIOUS     : Echo(".MATRIX_PREVIOUS\n");    break;
   case MATRIX_CLONE        : Echo(".MATRIX_CLONE\n");       break;
   case MATRIX_USERFUNCTION : Echo(".MATRIX_USERFUNCTION\n");break;
   case MATRIX_SCRIPT       : Echo(".MATRIX_SCRIPT\n");      break;
   }
   Echo(".File=\"%s\"\n",pPlot->pData->pName);
   switch (pPlot->pData->type) {
   case MATRIX_FILE :
      pPlot->pData->nrl=pPlot->pData->ncl=1;
      if (pPlot->pAttr->xScale==SCALE_SERIES) {
         bResult=GetMtrxFrFileEx(
            pPlot->pData->pName,
            &pPlot->pData->mtx,&pPlot->pData->nrh,&pPlot->pData->nch,
            &pPlot->pData->ppHeader,&pPlot->pData->nHeader);
      } else if (pPlot->pData->nBlockIndex) {
         bResult=GetMtrxFrFileWithBlockIndex(
            pPlot->pData->pName,
            &pPlot->pData->mtx,&pPlot->pData->nrh,&pPlot->pData->nch,
            pPlot->pData->nBlockIndex,pPlot->pData->vBlockIndex);
      } else {
         bResult=GetMtrxFrFile(
            pPlot->pData->pName,
            &pPlot->pData->mtx,&pPlot->pData->nrh,&pPlot->pData->nch);
      }
      if (!bResult) {
         char qPath[1024];
         _getcwd(qPath,1024);
         Echo(0,
            "Error at CreateMatrixFromFile(),\n"
            "MATRIX_FILE : \n"
            "Matrix could not created from a file, <%s>. \n"
            "Current directory is <%s>. \n",
            pPlot->pData->pName,qPath);
         return FALSE;
      }
      break;
   case MATRIX_PREVIOUS :
      bResult=AttachPreviousMatrix(pPlot);
      if (!bResult) {
         Echo(0,
            "Error at CreateMatrixFromFile(),\n"
            "MATRIX_PREVIOUS : \n"
            "Cannot find \"%s\" in the previous plot(s). \n"
            "Aborted.",
            pPlot->pData->pName);
         return FALSE;
      }
      break;
   case MATRIX_CLONE :
      /*
      if (AttachPreviousMatrix(pPlot,&prevPlt)
         &&  cmpPltMtrxRange(pPlot,prevPlt))
         dupPltMtrx(pPlot,prevPlt);
      else 
      */
      {
         Echo(0,"Error at CreateMatrixFromFile(),\n"
            "MATRIX_CLONE : Under Construction. \n");
         return FALSE;
      }
      break;
   case MATRIX_USERFUNCTION :
      pPlot->pData->mtx=NULL;
      pPlot->pData->nrl=0;
      pPlot->pData->nrh=0;
      pPlot->pData->ncl=0;
      pPlot->pData->nch=0;
      break;
   case MATRIX_SCRIPT :
      nIndex=GetIndexOfDataFileInformation(pPlot->pData->pName,nInformation,qInformation);
      if (nIndex<0) {
         Echo(0,
            "Error at CreateMatrixFromFile(),\n"
            "MATRIX_SCRIPT : No enrolled script file, identified by %s ",
            pPlot->pData->pName);
         return FALSE;
      }
      /**/
      pPlot->pData->nrl=pPlot->pData->ncl=1;
      bResult=pPlot->pAttr->xScale==SCALE_SERIES ?
         GetMtrxFrFileEx(
            qInformation[nIndex].pOutput,
            &pPlot->pData->mtx,&pPlot->pData->nrh,&pPlot->pData->nch,
            &pPlot->pData->ppHeader,&pPlot->pData->nHeader) :
         GetMtrxFrFile(
            qInformation[nIndex].pOutput,
            &pPlot->pData->mtx,&pPlot->pData->nrh,&pPlot->pData->nch);
      if (!bResult) {
         Echo(0,
            "Error at CreateMatrixFromFile(),\n"
            "MATRIX_SCRIPT : Matrix did not generated. \n "
            "From a file named <%s>.\n",
            qInformation[nIndex].pOutput);
         return FALSE;
      }
      break;
   }
   
   EchoMatrixAndColSelection(pPlot,"");

   if (pPlot->pData->bRowColumnExchange) {
      double **mStuff;
      int l,h;
      Echo(
         ".Matrix Row-Column is Exchanged : [%d..%d][%d..%d]->[%d..%d][%d..%d]\n",
         pPlot->pData->nrl,pPlot->pData->nrh,
         pPlot->pData->ncl,pPlot->pData->nch,
         pPlot->pData->ncl,pPlot->pData->nch,
         pPlot->pData->nrl,pPlot->pData->nrh);
      mStuff=MRotate(
         pPlot->pData->mtx,
         pPlot->pData->nrl,pPlot->pData->nrh,
         pPlot->pData->ncl,pPlot->pData->nch);
      free_dmatrix(
         pPlot->pData->mtx,
         pPlot->pData->nrl,pPlot->pData->nrh,
         pPlot->pData->ncl,pPlot->pData->nch);
      for (prevPlt=pPlot->prev;prevPlt;prevPlt=prevPlt->prev)
         if (prevPlt->pData->mtx==pPlot->pData->mtx) prevPlt->pData->mtx=mStuff;
      pPlot->pData->mtx=mStuff;
      l=pPlot->pData->nrl;
      h=pPlot->pData->nrh;
      pPlot->pData->nrl=pPlot->pData->ncl;
      pPlot->pData->nrh=pPlot->pData->nch;
      pPlot->pData->ncl=l;
      pPlot->pData->nch=h;
   }

   return TRUE;
}

static
int ModifyMatrix( pPlot )
   PLTNODE *pPlot;
{
   double dNaN,**pMtx,*dVec,x1,y1;
   double dMin,low5,med,upp5,dMax,sigma;
   int i,j,nOldNch,nX,bSign,*iVec;
   int nBlockCount,ndVecCount,niVecCount;
   int nIndex,nIndex2,nBlockIndex,xIndex,yIndex;

   MkNaNDouble(dNaN);

   if (pPlot->pAttr->type==PLT2D_MOMENT) {
      if (pPlot->pSlct->yNoTotal==1) {
         Echo(0,
            "Warning @DoPlotDATA2(), Too Few Col.Selection To Draw Box Plot. \n");
         return FALSE;
      }
      nBlockCount=GetColSelectionBlockCount(pPlot->pSlct->yNo,0,pPlot->pSlct->yNoTotal-1);
      nOldNch=pPlot->pData->nch;
      pPlot->pData->nch+=nBlockCount*MTX_OFFSET_TOTAL;
      MInflate(
         &pPlot->pData->mtx,
         pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pData->ncl,nOldNch,
         pPlot->pData->nrh,pPlot->pData->nch);
      pMtx=pPlot->pData->mtx;
      iVec=salloc(int,pPlot->pSlct->yNoTotal);
      dVec=dvector(1,pPlot->pSlct->yNoTotal);
      for (nIndex=nBlockIndex=0;nIndex<pPlot->pSlct->yNoTotal;nIndex++) {
         xIndex=pPlot->pSlct->xNo[nIndex];
         yIndex=pPlot->pSlct->yNo[nIndex];
         if (IsMinOrMaxInt(xIndex) || IsMinOrMaxInt(yIndex)) continue;
         pPlot->pSlct->xNo[nBlockIndex]=xIndex;
         xIndex=ABS(xIndex);

         bSign=yIndex>=0 ? 1:-1;
         niVecCount=0;
         while (1) {
            if (nIndex>=pPlot->pSlct->yNoTotal) {
               nIndex--;
               break;
            }
            if (bSign*yIndex<0) {
               nIndex-=2;
               niVecCount--;
               break;
            }
            yIndex=pPlot->pSlct->yNo[nIndex++];
            if (!IsMinOrMaxInt(yIndex))
               iVec[niVecCount++]=ABS(yIndex);
         }
         for (i=pPlot->pData->nrl;i<=pPlot->pData->nrh;i++) {
            x1=pMtx[i][xIndex];
            if (IsNaNDouble(x1)) continue;
            ndVecCount=1;
            for (j=0;j<niVecCount;j++) {
               y1=pMtx[i][iVec[j]];
               if (IsNaNDouble(y1)) continue;
               dVec[ndVecCount++]=y1;
            }
            GetBoxSymbolData(
               dVec,ndVecCount-1,pPlot->pSlct->Etc.LineMoment.dRange,
               &dMin,&low5,&med,&upp5,&dMax,&sigma);
            j=1+MTX_OFFSET_TOTAL*nBlockIndex;
            pMtx[i][nOldNch+j+MTX_OFFSET_TO_MINV]=dMin;
            pMtx[i][nOldNch+j+MTX_OFFSET_TO_LOW5]=low5;
            pMtx[i][nOldNch+j+MTX_OFFSET_TO_MEDIAN]=med;
            pMtx[i][nOldNch+j+MTX_OFFSET_TO_UPP5]=upp5;
            pMtx[i][nOldNch+j+MTX_OFFSET_TO_MAXV]=dMax;
            pMtx[i][nOldNch+j+MTX_OFFSET_TO_SIGMA]=sigma;
         }
         nBlockIndex++;
      }
      free(iVec);
      free_dvector(dVec,1,pPlot->pSlct->yNoTotal);
      pPlot->pSlct->xNoTotal=
      pPlot->pSlct->yNoTotal=nBlockCount;
      if (pPlot->pSlct->nLegendTotal!=nBlockCount) {
         Echo(0,
            "Warning @DoPlotDATA2(), nLegendTotal != nBlockCount \n");
         return FALSE;
      }
      for (i=0;i<pPlot->pSlct->yNoTotal;i++) {
         /* pPlot->pSlct->xNo[i]=pPlot->pSlct->xNo[i]; see above ! */
         pPlot->pSlct->yNo[i]=nOldNch+1+MTX_OFFSET_TOTAL*i;
         pPlot->pSlct->pLegend[i].nCopy=0;
      }
      EchoMatrixAndColSelection(pPlot,": PLTLINE_MOMENT");
   }

   if (pPlot->pAttr->type==PLT2D_FLAT3D) {
      if (pPlot->pData->pOption && /* pPlot->pData->pOption => xy file */
         (pPlot->pData->type==MATRIX_FILE || pPlot->pData->type==MATRIX_SCRIPT))  {
         double **mtx;
         int bResult,nrh,nch,i,j;
         Echo(".Option=\"%s\"\n",pPlot->pData->pOption);
         bResult=GetMtrxFrFile(pPlot->pData->pOption,&mtx,&nrh,&nch);
         if (!bResult) {
            Echo(0,
               "Error @CreateMatrixFromFile() MATRIX_FILE, \n"
               "Optional matrix could not created from %s. \n",
               pPlot->pData->pOption);
            return FALSE;
         }
         if (nrh!=(pPlot->pData->nrh-pPlot->pData->nrl+1)) {
            Echo(0,
               "Error @CreateMatrixFromFile() MATRIX_FILE, \n"
               "Optional matrix differ from original matrix in number of rows. \n"
               "Row nTotal of optional (xy) matrix is %d and that of original matrix is %d. \n",
               nrh,pPlot->pData->nrh-pPlot->pData->nrl+1);
            return FALSE;
         } else if (nch!=2) {
            Echo(0,
               "Error @CreateMatrixFromFile() MATRIX_FILE, \n"
               "Optional matrix have a invalid column nTotal (%d) which should be 2. \n",
               nch);
            return FALSE;
         }
         MInflate(
            &pPlot->pData->mtx,pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pData->ncl,pPlot->pData->nch,
            pPlot->pData->nrh,pPlot->pData->nch+nch);
         pPlot->pData->nch+=nch;
         for (i=pPlot->pData->nrl;i<=pPlot->pData->nrh;i++) {
            for (j=1;j<=2;j++) {
               pPlot->pData->mtx[i][pPlot->pData->nch-2+j]=mtx[i][j];
            }
         }
         free_dmatrix(mtx,1,nrh,1,nch);
      }
      if (pPlot->pSlct->xNo[0]==ABS(pPlot->pSlct->yNo[0]) ||
         pPlot->pSlct->xNo[0]==ABS(pPlot->pSlct->zNo[0])) {
         Echo(0,
            "Warning @DoPlotDATA2(), \n"
            "All of xNo[0], yNo[0] and zNo[0] must differ each other. \n"
            "xNo[0]=%d, yNo[0]=%d, zNo[0]=%d. \n",
            pPlot->pSlct->xNo[0],pPlot->pSlct->yNo[0],pPlot->pSlct->zNo[0]);
         return FALSE;
      }
      if (pPlot->pData->pOption) { /* re-create matrix */
         pPlot->pSlct->xNoTotal=1;
         pPlot->pSlct->xNo[0]=pPlot->pData->nch-1;
         pPlot->pSlct->yNoTotal=1;
         pPlot->pSlct->yNo[0]=pPlot->pData->nch;
      }
   }

   if (pPlot->pAttr->xScale==SCALE_SERIES) {
      for (i=0;i<pPlot->pSlct->xNoTotal;i++) {
         if (pPlot->pSlct->xNo[i]!=0) {
            Echo(0,
               "Warning @DoPlotDATA2(), X Column Must Be Zero Under X-SERIES. \n");
            return FALSE;
         }
      }
      iVec=pPlot->pSlct->xNo;
      nX=pPlot->pData->ncl-1;
      for (i=0;i<pPlot->pSlct->xNoTotal;i++)
         pPlot->pSlct->xNo[i]=nX;
      for (i=pPlot->pData->nrl;i<=pPlot->pData->nrh;i++) {
         double *pVec;
         pVec=dvector(pPlot->pData->ncl-1,pPlot->pData->nch);
         memcpy(
            pVec+pPlot->pData->ncl,
            &(pPlot->pData->mtx[i][pPlot->pData->ncl]),
            (pPlot->pData->nch-pPlot->pData->ncl+1)*sizeof(double));
         free_dvector(pPlot->pData->mtx[i],pPlot->pData->ncl,pPlot->pData->nch);
         pPlot->pData->mtx[i]=pVec;
      }
      pPlot->pData->ncl--;
      for (i=pPlot->pData->nrl,j=1;i<=pPlot->pData->nrh;i++) {
         pPlot->pData->mtx[i][pPlot->pData->ncl]=(double)j++;
      }
      pPlot->pSlct->xlowb=0.0;
      pPlot->pSlct->xuppb=(double)j;
      Echo(".Series x (=%d) column is inserted.\n",pPlot->pData->ncl);
      Echo(".MATRIX=[%d..%d][%d..%d]\n",
         pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pData->ncl,pPlot->pData->nch);
      Echo(".X-Boundary : LB=%d,UB=%d\n",
         (int)pPlot->pSlct->xlowb,(int)pPlot->pSlct->xuppb);
   }

   if (pPlot->pAttr->xScale==SCALE_NORM || pPlot->pAttr->yScale==SCALE_NORM) {
      int nDenominator;
      nOldNch=pPlot->pData->nch;
      if (pPlot->pAttr->xScale==SCALE_NORM) {
         if (pPlot->pSlct->yNo) free(pPlot->pSlct->yNo);
         pPlot->pSlct->yNoTotal=pPlot->pSlct->xNoTotal;
         pPlot->pSlct->yNo=salloc(int,pPlot->pSlct->yNoTotal);
         for (i=0;i<pPlot->pSlct->yNoTotal;i++) {
            pPlot->pSlct->yNo[i]=nOldNch+i+1;
         }
      } else if (pPlot->pAttr->yScale==SCALE_NORM) {
         if (pPlot->pSlct->xNo) free(pPlot->pSlct->xNo);
         pPlot->pSlct->xNoTotal=pPlot->pSlct->yNoTotal;
         pPlot->pSlct->xNo=salloc(int,pPlot->pSlct->xNoTotal);
         for (i=0;i<pPlot->pSlct->xNoTotal;i++) {
            pPlot->pSlct->xNo[i]=nOldNch+i+1;
         }
      }
      pPlot->pData->nch+=pPlot->pSlct->xNoTotal; /* pPlot->pSlct->xNoTotal==pPlot->pSlct->yNoTotal */
      MInflate(
         &pPlot->pData->mtx,
         pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pData->ncl,nOldNch,
         pPlot->pData->nrh,pPlot->pData->nch);
      pMtx=pPlot->pData->mtx;
      dVec=dvector(pPlot->pData->nrl,pPlot->pData->nrh);
      for (j=0;j<pPlot->pSlct->xNoTotal;j++) {
         if (pPlot->pAttr->xScale==SCALE_NORM) {
            nIndex=pPlot->pSlct->xNo[j];
            nIndex2=ABS(pPlot->pSlct->yNo[j]);
         } else { /* (pPlot->pAttr->yScale==SCALE_NORM) */
            nIndex=ABS(pPlot->pSlct->yNo[j]);
            nIndex2=pPlot->pSlct->xNo[j];
         }
         ndVecCount=pPlot->pData->nrl;
         for (i=pPlot->pData->nrl;i<=pPlot->pData->nrh;i++) {
            /* if (!IsNaNDouble(pMtx[i][nIndex]) && pMtx[i][nIndex]>0.0) 2000.1124 */
            if (!IsNaNDouble(pMtx[i][nIndex])) /* 2000.1124 */
               dVec[ndVecCount++]=pMtx[i][nIndex];
         }
         ndVecCount-=pPlot->pData->nrl;
         dVec+=pPlot->pData->nrl-1;
         qcksrt(ndVecCount,dVec); /* pVec[1..nCount] */
         dVec-=pPlot->pData->nrl-1;
         nDenominator=
            pPlot->pData->nDenominatorForCDF>0 ? pPlot->pData->nDenominatorForCDF:ndVecCount;
         for (i=pPlot->pData->nrl;i<=pPlot->pData->nrl+ndVecCount-1;i++) {
            pMtx[i][nIndex2]=dVec[i]; 
            pMtx[i][nIndex]=(double)(i-pPlot->pData->nrl+0.5)/nDenominator;
            /* =(i-.5)/n <--- i=1..n */
            /* =(i-NRL+0.7)/(n-0.4); */
            /* =(i-.3)/(n-.4) Tobias91 */
         }
         for (i=ndVecCount+pPlot->pData->nrl;i<=pPlot->pData->nrh;i++) {
            pMtx[i][nIndex2]=dNaN;
            pMtx[i][nIndex2]=dNaN;
         }
         if (pPlot->pAttr->xScale==SCALE_NORM) {
            Echo(" (x*=%d,y=%d,nTotal=%d) \n",nIndex2,nIndex,nDenominator);
         } else { /* (pPlot->pAttr->yScale==SCALE_NORM) */
            Echo(" (x=%d,y*=%d,nTotal=%d) \n",nIndex,nIndex2,nDenominator);
         }
      }
      free_dvector(dVec,pPlot->pData->nrl,pPlot->pData->nrh);
      EchoMatrixAndColSelection(pPlot,": SCALE_NORM");
   }

   if (pPlot->pData->bColumnSortingByX) {
   }

   return TRUE;
}

static
int AdjustColumnSelection( pPlot,nInformation,qInformation )
   PLTNODE *pPlot;
   const int nInformation;
   const GARGAMELINFO *qInformation;
{
   int j;

   if (!pPlot->pSlct->xNoTotal) {
      Echo(0,"Warning from AdjustColumnSelection(): no X column selection. \n");
      return FALSE;
   }
   if (!pPlot->pSlct->yNoTotal) {
      Echo(0,"Warning from AdjustColumnSelection(): no Y column selection. \n");
      return FALSE;
   }
   if (!pPlot->pSlct->zNoTotal && pPlot->pAttr->type==PLT2D_FLAT3D) {
      Echo(0,
         "Warning from AdjustColumnSelection(): no Z column selection. \n"
         "Under PLT2D_FLAT3D, only the First of X,Y,Z column will be used.");
      return FALSE;
   }

   if (IsMinOrMaxInt(pPlot->pSlct->xNoTotal)) {
      if (pPlot->pSlct->xNo) free(pPlot->pSlct->xNo);
      pPlot->pSlct->xNoTotal=0;
      FillupPlotColNumbers(pPlot->pData->ncl,pPlot->pData->nch,
         0,0,TRUE,
         &pPlot->pSlct->xNoTotal,&pPlot->pSlct->xNo);
      if (IsMinOrMaxInt(pPlot->pSlct->yNoTotal)) {
         Echo("Warning from AdjustColumnSelection(): All of X and Y column are selected.\n");
         if (pPlot->pSlct->yNo) free(pPlot->pSlct->yNo);
         pPlot->pSlct->yNoTotal=0;
         FillupPlotColNumbers(pPlot->pData->ncl,pPlot->pData->nch,
            0,0,TRUE,
            &pPlot->pSlct->yNoTotal,&pPlot->pSlct->yNo);
      }
   } else { /* 20030901 */
      for (j=0;j<pPlot->pSlct->xNoTotal;j++) {
         if (pPlot->pSlct->xNo[j]&PLOT_ATTACHEDINDEX_MASK) {
            pPlot->pSlct->xNo[j]&=~PLOT_ATTACHEDINDEX_MASK;
            pPlot->pSlct->xNo[j]+=pPlot->pData->nch;
         }
         if (pPlot->pSlct->xNo[j]&PLOT_REVERSEINDEX_MASK) {
            pPlot->pSlct->xNo[j]&=~PLOT_REVERSEINDEX_MASK;
            pPlot->pSlct->xNo[j]=pPlot->pData->nch-pPlot->pSlct->xNo[j]+1;
         }
      }
   }

   if (IsMinOrMaxInt(pPlot->pSlct->yNoTotal)) {
      if (pPlot->pSlct->yNo) free(pPlot->pSlct->yNo);
      pPlot->pSlct->yNoTotal=0;
      FillupPlotColNumbers(pPlot->pData->ncl,pPlot->pData->nch,
         pPlot->pSlct->xNoTotal,pPlot->pSlct->xNo,TRUE,
         &pPlot->pSlct->yNoTotal,&pPlot->pSlct->yNo);
      /*
      if (pPlot->pSlct->yNo) free(pPlot->pSlct->yNo);
      pPlot->pSlct->yNoTotal=0;
      FillupPlotColNumbers(pPlot->pData->ncl,pPlot->pData->nch,
         0,0,TRUE,
         &pPlot->pSlct->yNoTotal,&pPlot->pSlct->yNo);
      */
   } else { /* 20030901 */
      for (j=0;j<pPlot->pSlct->yNoTotal;j++) {
         if (pPlot->pSlct->yNo[j]&PLOT_ATTACHEDINDEX_MASK) {
            pPlot->pSlct->yNo[j]&=~PLOT_ATTACHEDINDEX_MASK;
            pPlot->pSlct->yNo[j]+=pPlot->pData->nch;
         }
         if (pPlot->pSlct->yNo[j]&PLOT_REVERSEINDEX_MASK) {
            pPlot->pSlct->yNo[j]&=~PLOT_REVERSEINDEX_MASK;
            pPlot->pSlct->yNo[j]=pPlot->pData->nch-pPlot->pSlct->yNo[j]+1;
         }
      }
   }

   if (IsMinOrMaxInt(pPlot->pSlct->zNoTotal) && pPlot->pAttr->type==PLT2D_FLAT3D) {
      Echo(0,
         "Warning from AdjustColumnSelection(): \n "
         "Invalid Z column selection. "
         "Under PLT2D_FLAT3D, only the first of X,Y,Z column will be used.");
      return FALSE;
   }

   /*
    * This makes pPlot->pSlct->xNoTotal equal to pPlot->pSlct->yNoTotal
    */
   if (pPlot->pSlct->xNoTotal>0
      && pPlot->pSlct->yNoTotal>0
      && pPlot->pSlct->xNoTotal<pPlot->pSlct->yNoTotal) {
      int *iVec,i;
      iVec=salloc(int,pPlot->pSlct->yNoTotal);
      for (i=0;i<pPlot->pSlct->xNoTotal;i++)
         iVec[i]=pPlot->pSlct->xNo[i];
      for (i=pPlot->pSlct->xNoTotal;i<pPlot->pSlct->yNoTotal;i++)
         iVec[i]=pPlot->pSlct->xNo[pPlot->pSlct->xNoTotal-1];
      free(pPlot->pSlct->xNo);
      pPlot->pSlct->xNo=iVec;
      pPlot->pSlct->xNoTotal=pPlot->pSlct->yNoTotal;
   }

   return TRUE;
}

static
int CalculateColumnBoundaries( pPlot )
   PLTNODE *pPlot;
{
   int nResult,nIndex,nCount,bSign;

   /*
   if (!pPlot->pSlct->xNoTotal
      || pPlot->pSlct->xNoTotal!=pPlot->pSlct->yNoTotal) {
      Echo(0,
         "Error @CalculateColumnBoundaries(), Invalid xNo or yNo : xTotal=%d,yTotal=%d !\n",
         pPlot->pSlct->xNoTotal,pPlot->pSlct->yNoTotal);
      return FALSE;
   }
   if (!pPlot->pSlct->zNoTotal)
      Echo(
         "Warning @CalculateColumnBoundaries(), Invalid zNo : zTotal=%d.\n",
         pPlot->pSlct->zNoTotal);
   */

   nCount=0;
   for (nIndex=0;nIndex<pPlot->pSlct->xNoTotal;nIndex++) {
      nResult=IsValidColumnNumber(
         pPlot->pSlct->xNo[nIndex],
         pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pData->ncl,pPlot->pData->nch,
         pPlot->pData->mtx);
      if (nResult==0) {
         Echo(" X column (%d) has been ruled out due to its invalidity.\n",pPlot->pSlct->xNo[nIndex]);
         MkMaxInteger(pPlot->pSlct->xNo[nIndex]);
         nCount++;
      }
   }
   if (nCount==pPlot->pSlct->xNoTotal) {
      Echo(0,"CalculateColumnBoundaries():Error, all x columns are invalid.\n");
      return FALSE;
   }
   nCount=0;
   for (nIndex=0;nIndex<pPlot->pSlct->yNoTotal;nIndex++) {
      nResult=IsValidColumnNumber(
         ABS(pPlot->pSlct->yNo[nIndex]),
         pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pData->ncl,pPlot->pData->nch,
         pPlot->pData->mtx);
      if (nResult==0) {
         Echo(" Y column (%d) has been ruled out due to its invalidity.\n",pPlot->pSlct->yNo[nIndex]);
         bSign=pPlot->pSlct->yNo[nIndex];
         bSign>0 ? MkMaxInteger(pPlot->pSlct->yNo[nIndex]):
                   MkMinInteger(pPlot->pSlct->yNo[nIndex]);
         nCount++;
      }
   }
   if (nCount==pPlot->pSlct->yNoTotal) {
      Echo(0,"CalculateColumnBoundaries():Error, all y columns are invalid.\n");
      return FALSE;
   }
   nCount=0;
   for (nIndex=0;nIndex<pPlot->pSlct->zNoTotal;nIndex++) {
      nResult=IsValidColumnNumber(
         pPlot->pSlct->zNo[nIndex],
         pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pData->ncl,pPlot->pData->nch,
         pPlot->pData->mtx);
      if (nResult==0) {
         bSign=pPlot->pSlct->zNo[nIndex];
         bSign>0 ? MkMaxInteger(pPlot->pSlct->zNo[nIndex]):
                   MkMinInteger(pPlot->pSlct->zNo[nIndex]);
         nCount++;
      }
   }
   if (nCount &&
      nCount==pPlot->pSlct->zNoTotal) {
      Echo(0,
         "Error @CalculateColumnBoundaries(), \n"
         "Every Z column of %d column(s) in the matrix is invalid. \n",
         nCount);
      return FALSE;
   }

   nResult=GetMatrixMinMaxOfCols(
      pPlot->pData->mtx,pPlot->pSlct->xNo,pPlot->pSlct->xNoTotal,
      pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pAttr->xScale==SCALE_LOG10,
      &pPlot->pSlct->xminv,&pPlot->pSlct->xmaxv);
   if (!nResult) return FALSE;
   nResult=GetMatrixMinMaxOfCols(
      pPlot->pData->mtx,pPlot->pSlct->yNo,pPlot->pSlct->yNoTotal,
      pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pAttr->yScale==SCALE_LOG10,
      &pPlot->pSlct->yminv,&pPlot->pSlct->ymaxv);
   if (!nResult) return FALSE;
   nResult=GetMatrixMinMaxOfCols(
      pPlot->pData->mtx,pPlot->pSlct->zNo,pPlot->pSlct->zNoTotal,
      pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pAttr->zScale==SCALE_LOG10,
      &pPlot->pSlct->zminv,&pPlot->pSlct->zmaxv);
   if (!nResult) return FALSE;

   nResult=GetScaleBoundary(pPlot->pAttr->xScale,
      pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pSlct->xminv,pPlot->pSlct->xmaxv,
      &pPlot->pSlct->xlowb,&pPlot->pSlct->xuppb);
   if (!nResult) return FALSE;
   nResult=GetScaleBoundary(pPlot->pAttr->yScale,
      pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pSlct->yminv,pPlot->pSlct->ymaxv,
      &pPlot->pSlct->ylowb,&pPlot->pSlct->yuppb);
   if (!nResult) return FALSE;
   nResult=GetScaleBoundary(pPlot->pAttr->zScale,
      pPlot->pData->nrl,pPlot->pData->nrh,pPlot->pSlct->zminv,pPlot->pSlct->zmaxv,
      &pPlot->pSlct->zlowb,&pPlot->pSlct->zuppb);
   if (!nResult) return FALSE;

   if (pPlot->pAttr->type==PLT2D_FLAT3D) {
      pPlot->pSlct->xlowb=pPlot->pSlct->xminv-0.5;
      pPlot->pSlct->xuppb=pPlot->pSlct->xmaxv+0.5;
      pPlot->pSlct->ylowb=pPlot->pSlct->yminv-0.5;
      pPlot->pSlct->yuppb=pPlot->pSlct->ymaxv+0.5;
   }

   EchoMatrixAndColSelection(pPlot,"");
   Echo(".xlb=%1.2e xub=%1.2e xmin=%1.2e xmax=%1.2e\n",
      pPlot->pSlct->xlowb,pPlot->pSlct->xuppb,
      pPlot->pSlct->xminv,pPlot->pSlct->xmaxv);
   Echo(".ylb=%1.2e yub=%1.2e ymin=%1.2e ymax=%1.2e\n",
      pPlot->pSlct->ylowb,pPlot->pSlct->yuppb,
      pPlot->pSlct->yminv,pPlot->pSlct->ymaxv);
   Echo(".zlb=%1.2e zub=%1.2e zmin=%1.2e zmax=%1.2e\n",
      pPlot->pSlct->zlowb,pPlot->pSlct->zuppb,
      pPlot->pSlct->zminv,pPlot->pSlct->zmaxv);

   switch (pPlot->pSlct->Etc.nType) {
   case PLT2D_FLAT3D :
      if (pPlot->pSlct->Etc.Flat3D.nColorMin==
         pPlot->pSlct->Etc.Flat3D.nColorMax) {
         pPlot->pSlct->Etc.Flat3D.nColorMin=GEColorByName(NULL,"gray50");
         pPlot->pSlct->Etc.Flat3D.nColorMax=GEColorByName(NULL,"gray99");
      }
      break;
   case PLT2D_MOMENT : /* 20030818 */
      if (pPlot->pSlct->Etc.LineMoment.dRange<=50.0 ||
         pPlot->pSlct->Etc.LineMoment.dRange>100.0) {
         Echo(
            "Warning @CalculateColumnBoundaries(), momentRange(%2.1f%%) <=50%% or >=100%%\n",
            pPlot->pSlct->Etc.LineMoment.dRange);
         pPlot->pSlct->Etc.LineMoment.dRange=100.0;
      } else {
         Echo(".momentRange=%g%%\n",pPlot->pSlct->Etc.LineMoment.dRange);
      }
   }

   return TRUE;
}

static
int DoSymbol2D( pPlot )
   PLTNODE *pPlot;
{
   char *sLegendTextCommand="legend.txt=";
   char *sDefaultSymbol={
      "type=54 legend.txt=\"%s\" line=on solid color=blue\n"
      "type=55 legend.txt=\"%s\" line=on solid color=magenta\n"
      "type=56 legend.txt=\"%s\" line=on solid color=SkyBlue\n"
      "type=57 legend.txt=\"%s\" line=on solid color=aquamarine\n"
      "type=58 legend.txt=\"%s\" line=on solid color=GreenYellow\n"
      "type=59 legend.txt=\"%s\" line=on solid color=khaki\n"
      "type=60 legend.txt=\"%s\" line=on solid color=salmon\n"
      "type=61 legend.txt=\"%s\" line=on solid color=pink\n"
      "type=62 legend.txt=\"%s\" line=on solid color=violet\n"
      "type=63 legend.txt=\"%s\" line=on solid color=purple\n"
      "type=64 legend.txt=\"%s\" line=on solid color=red"
   };
   int nIndex,nBlockCount,nCount,bResult,j,k;
   PLTNODE *pCurrent=pPlot;
   double x1,x2,y1,y2,x,y=0.0;

   nBlockCount=GetColSelectionBlockCount(pPlot->pSlct->yNo,0,pPlot->pSlct->yNoTotal-1);
   if (nBlockCount>1) { /* nBlockCount>1  on 2000.1211 */
      int nStart,nEnd;
      LEGEND *pVec,Legend;
      pVec=salloc(LEGEND,pPlot->pSlct->yNoTotal);
      memset((char*)pVec,0,sizeof(LEGEND)*pPlot->pSlct->yNoTotal);
      nCount=0;
      for (nIndex=0;nIndex<MIN(nBlockCount,pPlot->pSlct->nLegendTotal);nIndex++) {
         bResult=GetColSelectionBlockFirstLast(
            pPlot->pSlct->yNo,0,pPlot->pSlct->yNoTotal-1,nIndex,&nStart,&nEnd);
         if (!bResult) {
            free(pVec);
            return FALSE;
         }
         memcpy((char*)&(pVec[nStart++]),
            (char*)&(pPlot->pSlct->pLegend[nIndex]),sizeof(LEGEND));
         nCount++;
         for (j=nStart;j<=nEnd;j++) {
            memcpy((char*)&(pVec[j]),
               (char*)&(pPlot->pSlct->pLegend[nIndex]),sizeof(LEGEND));
            pVec[j].nCopy=0;
            pVec[j].pText=0;
            nCount++;
         }
      }
      for (;nIndex<nBlockCount;nIndex++) { /* for remnant */
         bResult=GetColSelectionBlockFirstLast(
            pPlot->pSlct->yNo,0,pPlot->pSlct->yNoTotal-1,nIndex,&nStart,&nEnd);
         if (!bResult) {
            free(pVec);
            return FALSE;
         }
         GetDefaultSymbolLegend(nIndex,&Legend);
         freeEx(Legend.pText); /* 20030219 */
         memcpy((char*)&(pVec[nStart++]),(char*)&Legend,sizeof(LEGEND));
         nCount++;
         for (j=nStart;j<=nEnd;j++) {
            memcpy((char*)&(pVec[j]),(char*)&Legend,sizeof(LEGEND));
            pVec[j].nCopy=0;
            pVec[j].pText=0;
            nCount++;
         }
      }
      freeEx(pPlot->pSlct->pLegend);
      pPlot->pSlct->pLegend=pVec;
      pPlot->pSlct->nLegendTotal=nCount; /* nCount==pPlot->pSlct->yNoTotal */
   } else { /* to support a old-fashioned manner */
      nIndex=pPlot->pSlct->nLegendTotal;
      nCount=0;
      while (nIndex--) nCount+=pPlot->pSlct->pLegend[nIndex].nCopy;
      if (nCount) {
         LEGEND *pVec;
         nCount+=pPlot->pSlct->nLegendTotal;
         pVec=salloc(LEGEND,nCount);
         for (nIndex=j=0;nIndex<pPlot->pSlct->nLegendTotal;nIndex++) {
            memcpy(
               (char*)&(pVec[j++]),
               (char*)&(pPlot->pSlct->pLegend[nIndex]),
               sizeof(LEGEND));
            for (k=1;k<=pPlot->pSlct->pLegend[nIndex].nCopy;k++) {
               memcpy(
                  (char*)&(pVec[j]),
                  (char*)&(pPlot->pSlct->pLegend[nIndex]),
                  sizeof(LEGEND));
               pVec[j].nCopy=0;
               pVec[j].pText=0;
               j++;
            }
         }
         free(pPlot->pSlct->pLegend);
         pPlot->pSlct->pLegend=pVec;
         pPlot->pSlct->nLegendTotal=nCount; /* j==nCount if works well */
      }
      /* This makes pPlot->pSlct->nLegendTotal equal to pPlot->pSlct->yNoTotal */
      if (pPlot->pSlct->nLegendTotal<pPlot->pSlct->yNoTotal) {
         DLL *pDll;
         DLN *pDln;
         char delimiter='\n',*base,*ptr,*pNumber,buffer[256];
         int nLength,nBeginning,nEnd;
         PLTLIST list;
         list.pTail=pPlot;
         base=strdpl(sDefaultSymbol);
         strtrim(base);
         nLength=strlen(base);
         nBeginning=0;
         for (nIndex=pPlot->pSlct->nLegendTotal;nIndex<pPlot->pSlct->yNoTotal;nIndex++) {
            ptr=base+nBeginning;
            nEnd=(int)(strchr(ptr,delimiter)-base);
            if (nEnd>0) {
               base[nEnd]=0;
               nBeginning=nEnd+1;
            } else {
               for (j=0;j<nLength;j++)
                  if (base[j]==0) base[j]='\n';
               nBeginning=0;
            }
            k=ABS(pPlot->pSlct->yNo[nIndex]); /* Y.Kim,20030211 */
            pNumber=IsMinOrMaxInt(k) ? strdpl("#NA"):itostr(k,"#%02d");
            sprintf(buffer,ptr,pNumber);
            freeEx(pNumber);
            if (!pPlot->pSlct->bAutoLegend) {
               ptr=strstr(buffer,sLegendTextCommand);
               if (ptr) {
                  char *pEnd;
                  pEnd=ptr;
                  skipblack(&pEnd);
                  strcpy(ptr,pEnd);
               }
            }
            DLLGetItFrStream(buffer,PLOTSCRIPT_COMMENT_CHAR," \t\f\n",&pDll);
            for (pDln=pDll->head;pDln;pDln=pDln->next)
               DoScriptCommandSYMB(&list,pDln->tok);
            DLLCloseWMA(pDll);
         }
         free(base);
         pPlot->pSlct->nLegendTotal=pPlot->pSlct->yNoTotal;
      }
   }

   for (nIndex=0;nIndex<pPlot->pSlct->nLegendTotal;nIndex++) {
      if (pPlot->pSlct->pLegend[nIndex].nType<0) {
         if (pPlot->pAttr->type==PLT2D_MOMENT)
            pPlot->pSlct->pLegend[nIndex].nType=MOMENT_BOX_SYMBOL_TYPE;
         else
            pPlot->pSlct->pLegend[nIndex].nType=ABS(pPlot->pSlct->pLegend[nIndex].nType);
      }
      if (pPlot->pSlct->pLegend[nIndex].nType>=STROKESYMB_TOTAL)
         pPlot->pSlct->pLegend[nIndex].nType=STROKESYMB_TOTAL-1;
      LgndGCLineAttr(nIndex).gc_type=GE_GCLine; 
      LgndGCLineAttr(nIndex).gc_mask=GE_GCMaskLineDefault;
      LgndGCSymbAttr(nIndex).gc_type=GE_GCPolygonL; 
      LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskFillDefault;
      LgndGCSymbAttr(nIndex).fill_style=GE_FillStippled;
      LgndGCSymbAttr(nIndex).stipple_width=8;
      LgndGCSymbAttr(nIndex).stipple_height=8;
     // pPlot->pSlct->lgnd[nIndex].legendSize
     // LgndFontAttr(nIndex).height=LgndGCSymbAttr(nIndex).stipple_height;

      LgndFontAttr(nIndex).alignment=GE_AlignLeft|GE_AlignVCenter;
   }

   x1=pPlot->pXfrm->norwin.x1;
   x2=pPlot->pXfrm->norwin.x2;
   y1=pPlot->pXfrm->norwin.y1;
   y2=pPlot->pXfrm->norwin.y2;
   x=GetXPosOfWldWin(pPlot,x1+ABS(x2-x1)*0.1);
   y=y2-ABS(y2-y1)*0.05;
   while (pPlot=pPlot->prev) {
      if (pCurrent->pXfrm->norwin.x1!=pPlot->pXfrm->norwin.x1
      ||  pCurrent->pXfrm->norwin.x2!=pPlot->pXfrm->norwin.x2
      ||  pCurrent->pXfrm->norwin.y1!=pPlot->pXfrm->norwin.y1
      ||  pCurrent->pXfrm->norwin.y2!=pPlot->pXfrm->norwin.y2)
         continue;
      for (nIndex=0;nIndex<pPlot->pSlct->nLegendTotal;nIndex++) {
         if (!(pPlot->pSlct->pLegend)[nIndex].bLegendOn) continue;
         if (!(pPlot->pSlct->pLegend)[nIndex].pText) continue;
         x=pPlot->pSlct->pLegend[nIndex].x;
         y=MIN(y,(double)GetYPosOfNorWin(pCurrent,pPlot->pSlct->pLegend[nIndex].y));
      }
   }

   pPlot=pCurrent; /* 2001.0815 */
   if (!IsNaNDouble(pPlot->pSlct->pLegend[0].x)
      &&pPlot->pAttr->xScale==SCALE_LOG10
      &&pPlot->pSlct->pLegend[0].x<=0.0)
      MkNaNDouble(pPlot->pSlct->pLegend[0].x);
   if (!IsNaNDouble(pPlot->pSlct->pLegend[0].y)
      &&pPlot->pAttr->yScale==SCALE_LOG10
      &&pPlot->pSlct->pLegend[0].y<=0.0)
      MkNaNDouble(pPlot->pSlct->pLegend[0].y);
   for (nIndex=0;nIndex<pPlot->pSlct->nLegendTotal;nIndex++) {
      if (!(pPlot->pSlct->pLegend)[nIndex].bLegendOn) continue;
      if (!(pPlot->pSlct->pLegend)[nIndex].pText) continue;
      if (IsNaNDouble(pPlot->pSlct->pLegend[nIndex].x)) {
         pPlot->pSlct->pLegend[nIndex].x=x;
      } else {
         x=pPlot->pSlct->pLegend[nIndex].x;
      }
      if (IsNaNDouble(pPlot->pSlct->pLegend[nIndex].y)) {
         y-=GetTextYPitchOfNorWin(&LgndFontAttr(nIndex))*1.2;
         pPlot->pSlct->pLegend[nIndex].y=GetYPosOfWldWin(pPlot,y);
      } else {
         y=GetYPosOfNorWin(pPlot,pPlot->pSlct->pLegend[nIndex].y);
      }
   }
   return TRUE;
}

static
int DoAxis2D( pPlot )
   PLTNODE *pPlot;
{
   int i;

   /* Axis Size */
   for (i=0;i<pPlot->pAxis->xTotal;i++) {
      if (pPlot->pAxis->xAxis[i]->dAxisX1==pPlot->pAxis->xAxis[i]->dAxisY1) {
         pPlot->pAxis->xAxis[i]->dAxisX1=pPlot->pXfrm->wldwin.x1;
         pPlot->pAxis->xAxis[i]->dAxisX2=pPlot->pXfrm->wldwin.x2;
         pPlot->pAxis->xAxis[i]->dAxisY1=pPlot->pXfrm->wldwin.y1;
         pPlot->pAxis->xAxis[i]->dAxisY2=pPlot->pXfrm->wldwin.y2;
      } else {
         if (pPlot->pAxis->xAxis[i]->dAxisX1==pPlot->pAxis->xAxis[i]->dAxisX2) {
         pPlot->pAxis->xAxis[i]->dAxisX1=pPlot->pXfrm->wldwin.x1;
         pPlot->pAxis->xAxis[i]->dAxisX2=pPlot->pXfrm->wldwin.x2;
         }
      }
   }
   for (i=0;i<pPlot->pAxis->yTotal;i++) {
      if (pPlot->pAxis->yAxis[i]->dAxisX1==pPlot->pAxis->yAxis[i]->dAxisY1) {
         pPlot->pAxis->yAxis[i]->dAxisX1=pPlot->pXfrm->wldwin.x1;
         pPlot->pAxis->yAxis[i]->dAxisX2=pPlot->pXfrm->wldwin.x2;
         pPlot->pAxis->yAxis[i]->dAxisY1=pPlot->pXfrm->wldwin.y1;
         pPlot->pAxis->yAxis[i]->dAxisY2=pPlot->pXfrm->wldwin.y2;
      } else {
         if (pPlot->pAxis->yAxis[i]->dAxisY1==pPlot->pAxis->yAxis[i]->dAxisY2) {
         pPlot->pAxis->yAxis[i]->dAxisY1=pPlot->pXfrm->wldwin.y1;
         pPlot->pAxis->yAxis[i]->dAxisY2=pPlot->pXfrm->wldwin.y2;
         }
      }
   }
   /* Tick space */
   for (i=0;i<pPlot->pAxis->xTotal;i++)
      GetAxisTickSpace(pPlot->pAttr->xScale,
         pPlot->pAxis->xAxis[i]->dAxisX1,pPlot->pAxis->xAxis[i]->dAxisX2,
         &pPlot->pAxis->xAxis[i]->dTickMinorStep,&pPlot->pAxis->xAxis[i]->dTickMajorStep);
   for (i=0;i<pPlot->pAxis->yTotal;i++)
      GetAxisTickSpace(pPlot->pAttr->yScale,
         pPlot->pAxis->yAxis[i]->dAxisY1,pPlot->pAxis->yAxis[i]->dAxisY2,
         &pPlot->pAxis->yAxis[i]->dTickMinorStep,&pPlot->pAxis->yAxis[i]->dTickMajorStep);
   /* Label Attr 
   if (pPlot->pAttr->xScale==SCALE_SERIES) {
      for (i=0;i<pPlot->pAxis->xTotal;i++)
         pPlot->pAxis->xAxis[i]->LabelAttr=LABEL_NONE;
   }
   */

   return TRUE;
}

static
int DoText2D( pPlot )
   PLTNODE *pPlot;
{
   int i;
   PTEXT *tx;
   double x1,y1,x2,y2,w,h,x,y;

   for (i=0;i<pPlot->pText->nTotal;i++) {
      tx=pPlot->pText->qText[i];
      if (tx->nType==TEXT_FREE
      || !tx->pString) 
         continue;
      x1=pPlot->pXfrm->norwin.x1;
      x2=pPlot->pXfrm->norwin.x2;
      y1=pPlot->pXfrm->norwin.y1;
      y2=pPlot->pXfrm->norwin.y2;
      w=ABS(x2-x1);
      h=ABS(y2-y1);
      switch (tx->nType) {
      case TEXT_MAIN : 
         tx->FontAttr.alignment=GE_AlignHCenter|GE_AlignBottom;
         x=x1+w/2.0;
         y=y2+GetTextYPitchOfNorWin(&(tx->FontAttr))*2;/* 20030306 */
         tx->x=GetXPosOfWldWin(pPlot,x);
         tx->y=GetYPosOfWldWin(pPlot,y);
         break;
      case TEXT_LEFTSHOULDER :
      case TEXT_RIGHTSHOULDER :
         switch (tx->nType) {
         case TEXT_LEFTSHOULDER :
            x=x1;
            tx->FontAttr.alignment=GE_AlignLeft|GE_AlignBottom;
            break;
         case TEXT_RIGHTSHOULDER :
            x=x2;
            tx->FontAttr.alignment=GE_AlignRight|GE_AlignBottom;
            break;
         }
         y=y2+GetTextYPitchOfNorWin(&(tx->FontAttr))*0.25;/* 20030306 */
         tx->x=GetXPosOfWldWin(pPlot,x);
         tx->y=GetYPosOfWldWin(pPlot,y);
         break;
      case TEXT_BOTTOM : 
         SetGRFontDefault(tx->FontAttr);
         tx->FontAttr.alignment=GE_AlignLeft|GE_AlignTop;
         x=x1;
         y=y1-0.10;
         tx->x=GetXPosOfWldWin(pPlot,x);
         tx->y=GetYPosOfWldWin(pPlot,y);
         strescape(tx->pString);
         break;
      }
   }
   return TRUE;
}

static
int ModifyMatrixByUserFunction( pPlot )
   PLTNODE *pPlot;
{
   extern IPTRFN UfunLookUp(); /* usrfunc.h */
   PUFUN *pUf;
   PTEXT *tx;
   int i=0,j,bFound;
   PLTNODE *ptr;

   if (!pPlot->pUfun->pHead)
      return TRUE;

   pUf=pPlot->pUfun->pHead;
   do {
      pUf->out.nResult=0;
      pUf->out.vResult=0;
      pUf->out.pResult=0;
      if (pUf->nrl<=0 && pUf->nrl==pUf->nrh) {
         pUf->nrl=pPlot->pData->nrl;
         pUf->nrh=pPlot->pData->nrh;
      }
      if (pUf->ncl<=0 && pUf->ncl==pUf->nch) {
         pUf->ncl=pPlot->pData->ncl;
         pUf->nch=pPlot->pData->nch;
      }
      j=(*UfunLookUp(i,pUf->pType))(
         &pPlot->pData->mtx,
         &pPlot->pData->nrl,&pPlot->pData->nrh,
         &pPlot->pData->ncl,&pPlot->pData->nch,
         &pPlot->pSlct->xNoTotal,&pPlot->pSlct->xNo,
         &pPlot->pSlct->yNoTotal,&pPlot->pSlct->yNo,
         &pPlot->pSlct->zNoTotal,&pPlot->pSlct->zNo,
         pUf->nrl,pUf->nrh,pUf->ncl,pUf->nch,
         pUf->nOption,pUf->nSubOption,
         pPlot->pAttr->xScale,pPlot->pAttr->yScale,pPlot->pAttr->zScale,
         pUf->pArgument,pUf->pArgument2,pUf->pArgument3,pUf->pArgument4,pUf->pSweep,
         &pUf->out.nResult,&pUf->out.vResult,&pUf->out.pResult);
      if (j==FALSE) return j;
      i++;
      if (pUf->out.pResult
      &&  pUf->bTableOn) {
         bFound=FALSE;
         for (ptr=pPlot;ptr;ptr=ptr->prev) {
            if (pPlot->pXfrm->norwin.x1!=ptr->pXfrm->norwin.x1
            ||  pPlot->pXfrm->norwin.x2!=ptr->pXfrm->norwin.x2
            ||  pPlot->pXfrm->norwin.y1!=ptr->pXfrm->norwin.y1
            ||  pPlot->pXfrm->norwin.y2!=ptr->pXfrm->norwin.y2)
                continue;
            for (j=ptr->pText->nTotal;j;j--) {
               tx=ptr->pText->qText[j-1];
               if (tx->nType==TEXT_BOTTOM) {
                  char *pText;
                  bFound=TRUE;
                  pText=tx->pString;
                  tx->pString=(char*)malloc(strlen(tx->pString)
                                          +strlen(pUf->out.pResult)+2);
                  strcpy(tx->pString,pText);
                  free(pText);
                  pText=tx->pString+strlen(tx->pString);
                  *pText='\n';
                  strcpy(++pText,pUf->out.pResult);
                  break;
               }
            }
         }
         if (!bFound) {
            j=pPlot->pText->nTotal;
            pPlot->pText->nTotal++;
            pPlot->pText->qText[j]=salloc(PTEXT,1); 
            memcpy((char*)&(pPlot->pText->qText[j]->FontAttr),
                   (char*)&(pUf->FontAttr),
                   sizeof(FONTATTR));
            pPlot->pText->qText[j]->nType=TEXT_BOTTOM;
            pPlot->pText->qText[j]->pString=strdpl(pUf->out.pResult);
         }
      }
   } while (pUf=pUf->next);
   return TRUE;
}

static
int DoXfrm2D( pPlot )
   PLTNODE *pPlot;
{
   double wx1,wy1,wx2,wy2;
   double nx1,ny1,nx2,ny2;

   switch (pPlot->pAttr->xScale) {
   case SCALE_LIN   : pPlot->pXfrm->xCnvFn=dummy; pPlot->pXfrm->xInvFn=dummy;   break;
   case SCALE_LOG10 : pPlot->pXfrm->xCnvFn=log10; pPlot->pXfrm->xInvFn=pow10;   break;
   case SCALE_NORM  : pPlot->pXfrm->xCnvFn=icnorm;pPlot->pXfrm->xInvFn=iicnorm;break;
   case SCALE_SERIES: pPlot->pXfrm->xCnvFn=dummy; pPlot->pXfrm->xInvFn=dummy;   break;
   }
   switch (pPlot->pAttr->yScale) {
   case SCALE_LIN   : pPlot->pXfrm->yCnvFn=dummy; pPlot->pXfrm->yInvFn=dummy;   break;
   case SCALE_LOG10 : pPlot->pXfrm->yCnvFn=log10; pPlot->pXfrm->yInvFn=pow10;   break;
   case SCALE_NORM  : pPlot->pXfrm->yCnvFn=icnorm;pPlot->pXfrm->yInvFn=iicnorm;break;
   case SCALE_SERIES: pPlot->pXfrm->yCnvFn=dummy; pPlot->pXfrm->yInvFn=dummy;   break;
   }
   switch (pPlot->pAttr->zScale) {
   case SCALE_LIN   : pPlot->pXfrm->zCnvFn=dummy; pPlot->pXfrm->zInvFn=dummy;   break;
   case SCALE_LOG10 : pPlot->pXfrm->zCnvFn=log10; pPlot->pXfrm->zInvFn=pow10;   break;
   case SCALE_NORM  : pPlot->pXfrm->zCnvFn=icnorm;pPlot->pXfrm->zInvFn=iicnorm;break;
   case SCALE_SERIES: pPlot->pXfrm->zCnvFn=dummy; pPlot->pXfrm->zInvFn=dummy;   break;
   }

   pPlot->pXfrm->wldwin.x1=pPlot->pSlct->xlowb;
   pPlot->pXfrm->wldwin.x2=pPlot->pSlct->xuppb;
   pPlot->pXfrm->wldwin.y1=pPlot->pSlct->ylowb;
   pPlot->pXfrm->wldwin.y2=pPlot->pSlct->yuppb;
   wx1=(*pPlot->pXfrm->xCnvFn)(pPlot->pXfrm->wldwin.x1);
   wx2=(*pPlot->pXfrm->xCnvFn)(pPlot->pXfrm->wldwin.x2);
   wy1=(*pPlot->pXfrm->yCnvFn)(pPlot->pXfrm->wldwin.y1);
   wy2=(*pPlot->pXfrm->yCnvFn)(pPlot->pXfrm->wldwin.y2);

   nx1=MIN(pPlot->pXfrm->norwin.x1,pPlot->pXfrm->norwin.x2); 
   nx2=MAX(pPlot->pXfrm->norwin.x1,pPlot->pXfrm->norwin.x2); 
   ny1=MIN(pPlot->pXfrm->norwin.y1,pPlot->pXfrm->norwin.y2); 
   ny2=MAX(pPlot->pXfrm->norwin.y1,pPlot->pXfrm->norwin.y2);
   if ((nx2-nx1)<0.1) {
      nx1=0.3;
      nx2=0.7;
   }
   if ((ny2-ny1)<0.1) {
      ny1=0.3;
      ny2=0.7;
   }
   if (pPlot->pXfrm->norwin.x1!=nx1 ||
       pPlot->pXfrm->norwin.x2!=nx2 ||
       pPlot->pXfrm->norwin.y1!=ny1 ||
       pPlot->pXfrm->norwin.y2!=ny2)
       Echo("<view> changed (x1,y1,x2,y2) : (%.2f,%.2f,%.2f,%.2f)"
            "->(%.2f,%.2f,%.2f,%.2f)\n",
            pPlot->pXfrm->norwin.x1,pPlot->pXfrm->norwin.y1,
            pPlot->pXfrm->norwin.x2,pPlot->pXfrm->norwin.y2,
            nx1,ny1,nx2,ny2);
   pPlot->pXfrm->norwin.x1=nx1;
   pPlot->pXfrm->norwin.x2=nx2;
   pPlot->pXfrm->norwin.y1=ny1;
   pPlot->pXfrm->norwin.y2=ny2;

   pPlot->pXfrm->attr.angle=0.0;
   /* scaling to the normalzied window of 1.0 */
   pPlot->pXfrm->attr.xScale=(nx2-nx1)/(wx2-wx1); 
   pPlot->pXfrm->attr.yScale=(ny2-ny1)/(wy2-wy1);
   /**/
   pPlot->pXfrm->attr.xTranslate=nx1-wx1*pPlot->pXfrm->attr.xScale;
   pPlot->pXfrm->attr.yTranslate=ny1-wy1*pPlot->pXfrm->attr.yScale;
   return TRUE;
}
 
/*----------------------------------------------------------------------------*/
/*                               sub-functions                                */
/*----------------------------------------------------------------------------*/

int GetBoxSymbolData( pData,nTotal,dRange,minv,low5,med,upp5,maxv,sigma )
   /* in */
   double *pData; /* base = 1 */
   int nTotal;
   double dRange; /* 50.0 ... 100.0 */
   /* out */
   double *minv,*low5,*med,*upp5,*maxv,*sigma;
/*
 * ref : nr.c,13.1
 */
{
   int i;
   int i_n,i_p;
   double s,sv_n,sv_p,sd_n,sd_p;
   int j;
   double low_range,upp_range;

   *minv=*low5=*med=*upp5=*maxv=*sigma=0.0;

   if (nTotal<=1) {
      *med=pData[1];
      return TRUE;
   }
   mdian2(pData,nTotal,med);
   VGetMinMaxValue(pData,1,nTotal,minv,maxv);
   i_n=i_p=0;
   sv_n=sv_p=0.0;
   for (i=1;i<=nTotal;i++) {
      s=pData[i]-*med;
      if (s>=0.0) {
         i_p++;
         sv_p+=(s*s);
      } else {
         i_n++;
         sv_n+=(s*s);
      }
   }
   if (i_n) {
      sd_n=sqrt(sv_n/i_n);
      *low5=*med-0.675*sd_n;
   } else
      *low5=*med;
   if (i_p) {
      sd_p=sqrt(sv_p/i_p);
      *upp5=*med+0.675*sd_p;
   } else
      *upp5=*med;
   *sigma=sqrt((sv_n+sv_p)/(nTotal-1));

   if (dRange<50.0
   ||  dRange>=100.0)
      return TRUE;
   else {
      dRange=icnorm(0.5+dRange/200.0);
      s=MAX(sd_n,sd_p);
      low_range=*med-dRange*s;
      upp_range=*med+dRange*s;
      for (i=j=1;i<=nTotal;i++) {
         if (pData[i]<low_range
         ||  pData[i]>upp_range)
            continue;
         pData[j++]=pData[i];
      }
      GetBoxSymbolData(pData,--j,0.0,minv,low5,med,upp5,maxv,sigma);
   }
   return TRUE;
}

static
void EchoMatrixAndColSelection( pPlot,pComment )
   PLTNODE *pPlot;
   const char *pComment;
{
   int i,j;
   Echo(".MATRIX=[*..*][%d..%d] %s \n",
      pPlot->pData->ncl,pPlot->pData->nch,pComment);
   Echo(".x");
   if (pPlot->pSlct->xNo) {
      for (i=0;i<pPlot->pSlct->xNoTotal;i++) {
         j=pPlot->pSlct->xNo[i];
         IsMinOrMaxInt(j) ? Echo(",##"):
         Echo("%s%02d",
            j&PLOT_ATTACHEDINDEX_MASK ? ",a":
            j&PLOT_REVERSEINDEX_MASK ? ",r":
            j&PLOT_BLOCKINDEX_MASK ? ",-": ",",
            j&PLOT_COLUMNINDEX_MASK);
      }
   } else {
      Echo("=NULL");
   }
   Echo("\n");
   Echo(".y");
   if (pPlot->pSlct->yNo) {
      for (i=0;i<pPlot->pSlct->yNoTotal;i++) {
         j=pPlot->pSlct->yNo[i];
         IsMinOrMaxInt(j) ? Echo(",##") :
         Echo("%s%02d",
            j&PLOT_ATTACHEDINDEX_MASK ? ",a":
            j&PLOT_REVERSEINDEX_MASK ? ",r":
            j&PLOT_BLOCKINDEX_MASK ? ",-": ",",
            j&PLOT_COLUMNINDEX_MASK);
      }
   } else {
      Echo("=NULL");
   }
   Echo("\n");
   if (pPlot->pSlct->zNoTotal<=0) return;
   Echo(".z");
   if (pPlot->pSlct->zNo) {
      for (i=0;i<pPlot->pSlct->zNoTotal;i++) {
         j=pPlot->pSlct->zNo[i];
         IsMinOrMaxInt(j) ? Echo(",##"):
         Echo("%s%02d",
            j&PLOT_ATTACHEDINDEX_MASK ? ",a":
            j&PLOT_REVERSEINDEX_MASK ? ",r":
            j&PLOT_BLOCKINDEX_MASK ? ",-": ",",
            j&PLOT_COLUMNINDEX_MASK);
      }
   } else {
      Echo("=NULL");
   }
   Echo("\n");
}

static
int GetIndexOfDataFileInformation( name,nInformation,infoVec )
   char *name;
   const int nInformation;
   const GARGAMELINFO *infoVec;
{
   int nIndex;
   nIndex=abs(atoi(name));
   if (nIndex<nInformation && !infoVec[nIndex].pInput) nIndex=-1;

   /* old style, not used currently. 2001.0221
   int nIndex,nPos;

   for (nIndex=0;nIndex<=nInformation;nIndex++) {
      if (nIndex==nInformation) {
         if (isdigit(*name)) {
            nIndex=atoi(name);
            if (infoVec[abs(nIndex)].pInput) break;
         }
         return -1;
      }
      if (infoVec[nIndex].pInput) {
            if (name[0]==PLTOSCRIPT_HOMEPATH_CHAR) {
            nPos=strlen(infoVec[nIndex].pInput)-strlen(name)+1;
            if (strequ(infoVec[nIndex].pInput+nPos,name+1)) break;
         } else {
            if (strequ(infoVec[nIndex].pInput,name)) break;
         }
      }
   }
   */
   return nIndex;
}

static
int FillupPlotColNumbers( ncl,nch,iTotal,iNo,bExclusive,oTotal,oNo )
   int ncl,nch;
   int iTotal,*iNo,bExclusive; /* input */
   int *oTotal,**oNo; /* output */
{
   int i,j,k;

   if (*oTotal>0)
      return FALSE;
   if (iTotal==0) {
      *oTotal=nch-ncl+1;
      *oNo=salloc(int,*oTotal);
      for (i=0,j=ncl;i<*oTotal;i++,j++)
         (*oNo)[i]=j;
   } else { /* *yTotal<=0 */
      *oTotal=nch-ncl+1;
      *oNo=salloc(int,*oTotal);
      for (i=0,j=ncl;i<*oTotal;i++,j++) {
         (*oNo)[i]=j;
         if (bExclusive) {
            for (k=0;k<iTotal;k++)
               if (j==iNo[k]) {
                  i--;
                  (*oTotal)--;
                  break;
               }
         }
      }
      if (!*oTotal) {
         free(*oNo);
         *oNo=0;
      }
   }
   return TRUE;
}

static
int IsValidColumnNumber( column,nrl,nrh,ncl,nch,mtrx )
   int column,nrl,nrh,ncl,nch;
   double **mtrx; 
{
   int i,count;
   
   column=ABS(column);
   if (column<ncl
      || column>nch)
      return FALSE;
   count=0;
   for (i=nrl;i<=nrh;i++) {
      if (!IsNaNDouble(mtrx[i][column]))
         count++;
   }
   return count;
}

static 
int AttachPreviousMatrix( pPlot )
   PLTNODE *pPlot;
{
   PLTNODE *pNode;
   int bFound=0;

   pNode=pPlot->prev;
   if (!pNode) return FALSE;
   if (!pPlot->pData->pName||!*(pPlot->pData->pName)) return FALSE; /* 20030625 */
   do {
      if (!pNode->pData->pName||!*(pNode->pData->pName)) continue; /* 20030625 */
      if (strequ(pNode->pData->pName,pPlot->pData->pName)) bFound=1;
      if (bFound) {
         pPlot->pData->mtx=pNode->pData->mtx;
         pPlot->pData->nrl=pNode->pData->nrl;
         pPlot->pData->nrh=pNode->pData->nrh;
         pPlot->pData->ncl=pNode->pData->ncl;
         pPlot->pData->nch=pNode->pData->nch;
         return TRUE;
      }
   } while (pNode=pNode->prev);
   return FALSE;
}

static
int GetColSelectionBlockCount( int *iVec,int nStart,int nEnd )
{
   int nIndex,bSign1,bSign2,nCount;

   nCount=1;
   for (nIndex=++nStart;nIndex<=nEnd;nIndex++) {
      bSign1=iVec[nIndex-1]>=0 ? 1:-1;
      bSign2=iVec[nIndex]>=0 ? 1:-1;
      if (bSign1!=bSign2) nCount++;
   }
   return nCount;
}

static
int GetColSelectionBlockFirstLast(
   int *iVec,int nStart,int nEnd,int nBlock,int *nBlockFirst,int *nBlockLast)
   /* nBlock -> based on 0 */
{
   int nIndex,bSign,bSignTemp;

   *nBlockFirst=nStart;
   bSign=iVec[nStart]>=0 ? 1:-1;
   for (nIndex=nStart;nIndex<=nEnd;nIndex++) {
      bSignTemp=iVec[nIndex]>=0 ? 1:-1;
      if (bSignTemp!=bSign) {
         bSign=bSignTemp;
         *nBlockFirst=nIndex;
         nBlock--;
      }
      if (!nBlock) break;
   }
   if (nBlock) goto F;
   for (;nIndex<=nEnd;nIndex++) {
      bSignTemp=iVec[nIndex]>=0 ? 1:-1;
      if (bSignTemp!=bSign) {
         *nBlockLast=nIndex-1;
         return TRUE;
      }
      if (nIndex==nEnd) {
         *nBlockLast=nIndex;
         return TRUE;
      }
   }
F: *nBlockFirst=*nBlockLast=0;
   return FALSE;
}

static
int GetDefaultSymbolLegend( int nIndex,LEGEND *pLegend )
{
   struct {
      int nType;
      char *sColor;
   } pTable[]= {
      {54,"blue"},{55,"magenta"},{56,"SkyBlue"},{57,"aquamarine"},
      {58,"GreenYellow"},{59,"khaki"},{60,"salmon"},{61,"pink"},
      {62,"violet"},{63,"purple"},{64,"red"},{65,"brown"},
      {66,"CadetBlue"},{67,"SandyBrown"}
   };
   int nTotal;

   nTotal=noof(pTable);
   nIndex%=nTotal;
   GESetGCDefault(pLegend->GCSymbAttr);
   GESetGCDefault(pLegend->GCLineAttr);
   SetGRFontDefault(pLegend->FontAttr);
   pLegend->nType=pTable[nIndex].nType;
   pLegend->pText=strdpl("\"%s\"");
   pLegend->dLegendSize=DEFAULT_PLOT_LEGEND_SIZE;
   pLegend->dSymbSize=DEFAULT_PLOT_SYMBOL_SIZE;
   pLegend->bLineOn=1;
   pLegend->nPen=1;
   pLegend->GCSymbAttr.stipple=10;
   pLegend->GCSymbAttr.polyarc_attr=2;
   pLegend->GCSymbAttr.foreground=GEColorByName(NULL,pTable[nIndex].sColor);
   pLegend->GCLineAttr.line_style=GE_LineSolid;
   pLegend->GCLineAttr.foreground=GEColorByName(NULL,pTable[nIndex].sColor);
   return TRUE;
}

static
int DoPreProcessorFilesExist( qHomePath,qFile )
   const char *qHomePath,*qFile;
{
   char *pAddr;
   pAddr=(char*)qFile;
   if (!myDoesFileExist(pAddr)) {
      pAddr=strvcat(
         "Error, The input file in which \"~\" was replaced by HOME-PATH "
         "was not opened and named : \r\n\r\n"
         "FILE= ",
         pAddr,
         "\r\n\r\n",
         "HOME-PATH(~)= ",
         qHomePath,
         0);
      Echo(1,pAddr);
      free(pAddr);
      return FALSE;
   }
   return TRUE;
}

static
int GetTemporaryDataFileName( qName,nIndex,ppReturn )
   const char *qName;
   int nIndex;
   char **ppReturn;
{
   char *pNew,*pAddr;
   char qBuffer[1024];
   int nBuffer=1024;

   *ppReturn=0;
   pNew=strdpl(qName);
   strreverse(pNew);
   pAddr=strchr(pNew,'\\');
   if (pAddr) *pAddr=0;
   pAddr=strchr(pNew,'.');
   if (pAddr) strcpy(pNew,pAddr+1);
   strreverse(pNew);
   GetTempPath(nBuffer,qBuffer);
   sprintf(qBuffer+strlen(qBuffer),"%s-%03d.dat",pNew,nIndex); /* This must
   coincide with CGrPlotWizard::GetGrTemporaryFileName() in GrPlotWizard.cpp. */
   freeEx(pNew);
   *ppReturn=strdpl(qBuffer);

   return strlen(*ppReturn);
}

static
int AddTemporaryFileName( pList,pTemporaryFile )
   PLTLIST *pList;
   const char *pTemporaryFile;
{
   char *pStrings;
   int nCount;

   if (!pTemporaryFile || !*pTemporaryFile) return FALSE;
   if (pList->pTemporaryFiles) {
      pStrings=strvcat(pList->pTemporaryFiles,"\n",pTemporaryFile,0);
      freeEx(pList->pTemporaryFiles);
      pList->pTemporaryFiles=pStrings;
   } else
      pList->pTemporaryFiles=strdpl(pTemporaryFile);

   nCount=chrcount(pList->pTemporaryFiles,'\n');
   return nCount;
}

static 
int dupPltMtrx( pPlot,fplt )
   PLTNODE *pPlot,*fplt;
{
   if (pPlot->pData->nrl==pPlot->pData->nrh
   &&  pPlot->pData->ncl==pPlot->pData->nch) {
      pPlot->pData->nrl=fplt->pData->nrl;
      pPlot->pData->nrh=fplt->pData->nrh;
      pPlot->pData->ncl=fplt->pData->ncl;
      pPlot->pData->nch=fplt->pData->nch;
   }
   pPlot->pData->mtx=dmatrix(pPlot->pData->nrl,pPlot->pData->nrh,
                          pPlot->pData->ncl,pPlot->pData->nch);
   MCopy(fplt->pData->mtx,pPlot->pData->mtx,
         pPlot->pData->nrl,pPlot->pData->nrh,
         pPlot->pData->ncl,pPlot->pData->nch);
   return TRUE;
}

static
int cmpPltMtrxRange( p1,p2 )
   PLTNODE *p1,*p2;
{
   if (p1->pData->nrl<=p2->pData->nrl
   &&  p1->pData->nrh<=p2->pData->nrh
   &&  p1->pData->ncl<=p2->pData->ncl
   &&  p1->pData->nch<=p2->pData->nch)
      return TRUE;
   else
      return FALSE;
}

static
int GetMatrixMinMaxOfCols( mStuff,vColumns,nColumns,nL,nH,bLog,pMin,pMax )
   double **mStuff,*pMin,*pMax;
   int *vColumns,nColumns,nL,nH,bLog;
{
   int nIndex,nValue;
   double tmin,tmax;

   *pMin=*pMax=0;
   if (!nColumns) return TRUE; /* FALSE->TRUE 20030318 */
   nIndex=0;
   while (IsMinOrMaxInt(vColumns[nIndex])) {
      nIndex++;
      if (nIndex>=nColumns) return FALSE;
   }
   if (!MGetMinMaxValue(mStuff,TRUE,vColumns[nIndex],nL,nH,bLog,pMin,pMax)) {
      char qMsg[1024];
      sprintf(qMsg,"%s\nIndex of the column is %d.\n%s",
         (char*)errMessage(),
         vColumns[nIndex],
         !bLog?"":"This may come from the negative or zero data with the Log scale.\n"
         );
      Echo(0,qMsg);
      return FALSE;
   }
   tmin=*pMin;
   tmax=*pMax;
   for (;nIndex<nColumns;nIndex++) {
      nValue=ABS(vColumns[nIndex]);
      if (IsMinOrMaxInt(nValue)) continue;
      MGetMinMaxValue(mStuff,TRUE,nValue,nL,nH,bLog,pMin,pMax);
      tmin=MIN(tmin,*pMin);
      tmax=MAX(tmax,*pMax);
   }   
   *pMin=tmin;
   *pMax=tmax;
   return TRUE;
}

static
int GetScaleBoundary( nScale,nL,nH,dMin,dMax,pLB,pUB )
   int nScale,nL,nH;
   double dMin,dMax,*pLB,*pUB;
{
   int nOrder,nGap;
   double dOrder,dLB,dUB;

   switch (nScale) {
   case SCALE_LIN :
      nOrder=order(MAX(ABS(dMax),ABS(dMin)));
      dUB=orderCeil(dMax,nOrder);
      dLB=orderFloor(dMin,nOrder);
      if (dLB==dUB) {
         dLB-=pow10((double)nOrder);
         dUB+=pow10((double)nOrder);
      }
      if (dUB*dLB!=0.0) { /* 20030320 */
         nGap=order(dUB)-order(dLB);
         if (nGap>0) {
            dLB=orderFloor(dMin,nOrder+nGap); /* 20030405 */
         } else if (nGap<0) {
            dUB=orderCeil(dMax,nOrder-nGap);
         }
      }
      if (IsNaNDouble(*pLB)) *pLB=dLB;
      if (IsNaNDouble(*pUB)) *pUB=dUB;
      break;
   case SCALE_LOG10 :
      if (!IsNaNDouble(*pLB) && *pLB<=0.0) MkNaNDouble(*pLB);
      if (!IsNaNDouble(*pUB) && *pUB<=0.0) MkNaNDouble(*pUB);
      if (IsNaNDouble(*pLB)) dLB=0.0;
      if (IsNaNDouble(*pUB)) dUB=0.0;
      if (dLB>=dUB || dLB<=0.0 || dUB<=0.0) {
         nOrder=order(dMax);
         dUB=orderCeil(dMax,++nOrder);
         if (dUB/dMax==10.0)
            dUB/=10;
         if (dMin<=0) {
            Echo(0,
               "Warning @GetScaleBoundary(), Zero or Negative Value In Log-Scale !");
            return FALSE;
         }
         nOrder=order(dMin);
         dLB=pow10((double)nOrder);
      } else if (dLB<dUB) {
         nOrder=order(dUB);
         dOrder=pow10((double)nOrder);
         if ((dUB/dOrder)!=1.0)
            dUB=orderCeil(dUB,++nOrder);
         nOrder=order(dLB);
         dOrder=pow10((double)nOrder);
         if ((dLB/dOrder)!=1.0)
            dLB=pow10((double)nOrder);
      }
      if (IsNaNDouble(*pLB)) *pLB=dLB;
      if (IsNaNDouble(*pUB)) *pUB=dUB;
      break;
   case SCALE_NORM :
      if (!IsNaNDouble(*pLB) && *pLB<0.001) MkNaNDouble(*pLB);
      if (!IsNaNDouble(*pUB) && *pUB>0.999) MkNaNDouble(*pUB);
      dLB=0.01;
      dUB=0.99;
      if (IsNaNDouble(*pLB)) *pLB=dLB;
      if (IsNaNDouble(*pUB)) *pUB=dUB;
      /*
      Echo("Warning @GetScaleBoundary(), No normal scale boundary. "
         "So, dLB=0.01,dUB=0.99\n");
      */
      break;
   case SCALE_SERIES :
      dLB=0.0;
      dUB=(double)(nH-nL+1+1);
      Echo(".X-Boundary : LB=%d,UB=%d\n",(int)dLB,(int)dUB);
      break;
   }
   if (*pLB>*pUB) {
      double dTemp=*pLB;
      *pLB=*pUB;
      *pUB=dTemp;
   }
   return TRUE;
}

static 
int GetAxisTickSpace( nScale,dLB,dUB,pdMinTc,pdMajTc )
   int nScale;
   double dLB,dUB,*pdMinTc,*pdMajTc;
{
   int nSmallTickMax=20;

   if (*pdMajTc&&*pdMinTc) { /* 2001.0318 */
      double dTemp;
      if (*pdMajTc<*pdMinTc) {
         dTemp=*pdMajTc;
         *pdMajTc=*pdMinTc;
         *pdMinTc=dTemp;
      }
      dTemp=*pdMajTc/(*pdMinTc);
      if (dTemp>(double)nSmallTickMax) *pdMinTc=*pdMajTc/4;
      dTemp-=floor(dTemp);
      if (dTemp>(1./nSmallTickMax)) *pdMinTc=*pdMajTc/4;
   } else {
      if (!*pdMajTc) {
         switch (nScale) {
         case SCALE_LIN :  *pdMajTc=dvalue(order(dUB-dLB));  break;
         case SCALE_LOG10 : *pdMajTc=10.;break;
         case SCALE_NORM :  *pdMajTc=dvalue(order(dUB-dLB)); break;
         case SCALE_SERIES :*pdMajTc=1.;                    break;
         }
         if (nScale==SCALE_LIN &&
            fabs(1-(dUB-dLB)/ *pdMajTc)<1e-3) { /* 20030824 */
            *pdMajTc/=2.;
         }
      } else {
         if (nScale==SCALE_LOG10&&*pdMajTc<1) *pdMajTc=10.;
      }
      if (!*pdMinTc) {
         switch (nScale) {
         case SCALE_LIN :   *pdMinTc=*pdMajTc/5.; break;
         case SCALE_LOG10 : *pdMinTc=*pdMajTc/10.;break;
         case SCALE_NORM :  *pdMinTc=*pdMajTc/2.; break;
         case SCALE_SERIES :*pdMinTc=1.0;          break;
         }
      }
   }
   return TRUE;
}

/* static 20030217 */
double GetTextXPitchOfNorWin( pAttr )
   FONTATTR *pAttr;
{
   /*return (double)(pAttr->width+pAttr->ch_space)/500;*/
   return (double)(pAttr->width)/500;
}

/* static 20030217 */
double GetTextYPitchOfNorWin( pAttr )
   FONTATTR *pAttr;
{
   /*return (double)(pAttr->height+pAttr->ln_space)/500;*/
   return (double)(pAttr->height)/500;
}

/* static 20030217 */
double GetXPosOfNorWin( pPlot,xValue )
   PLTNODE *pPlot;
   double xValue;
{
   xValue=(pPlot->pXfrm->xCnvFn)(xValue);
   xValue*=pPlot->pXfrm->attr.xScale;
   xValue+=pPlot->pXfrm->attr.xTranslate;
   return xValue;
}

/* static 20030217 */
double GetYPosOfNorWin( pPlot,yValue ) 
   PLTNODE *pPlot;    
   double yValue; 
{ 
   yValue=(pPlot->pXfrm->yCnvFn)(yValue);
   yValue*=pPlot->pXfrm->attr.yScale; 
   yValue+=pPlot->pXfrm->attr.yTranslate;
   return yValue; 
}

/* static 20030217 */
double GetXPosOfWldWin( pPlot,xValue )
   PLTNODE *pPlot;
   double xValue;
{
   xValue-=pPlot->pXfrm->attr.xTranslate;
   xValue/=pPlot->pXfrm->attr.xScale;
   xValue=(pPlot->pXfrm->xInvFn)(xValue);
   return xValue;
}

/* static 20030217 */
double GetYPosOfWldWin( pPlot,yValue )
   PLTNODE *pPlot;
   double yValue;
{
   yValue-=pPlot->pXfrm->attr.yTranslate;
   yValue/=pPlot->pXfrm->attr.yScale;
   yValue=(pPlot->pXfrm->yInvFn)(yValue);
   return yValue;
}

static 
double dummy( dValue )
   double dValue; 
{ 
   return dValue; 
}

static
double iicnorm( dValue )
   double dValue;
{
   return cnorm(dValue,0.0,1.0); 
} 

/******************************************************************************/
/* plot.c */
