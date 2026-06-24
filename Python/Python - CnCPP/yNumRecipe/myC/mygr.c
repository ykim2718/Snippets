/******************************************************************************/
/*                           file name : myGR.c                               */
/*                         description : Gr Interface to MSWindow & XnMotif   */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43320222                             */
/* 4332 0222-0431,0720-____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0222-0328,0409,0512,0522,0612,1005,____,____,____,____,____,____,____ */
/* 4334 0104-0110,0215-0221,____,____,____,____,____,____,____,____,____,____ */
/* 4335 0913-0914,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4336 0215,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>

/******************************************************************************/

#include "myCore.h"
#include "blob.h"
#include "geWindow.h"
#include "gecore.h"
#include "plot.h"
#include "str.h"
#include "myGR.h"
#include "any.h"

static char *pGrVersion=0;
static char *pGrLog=0;
static char *pGrErrorLog=0;
static char *pGrTemporaryFiles=0;
static int myGRBlobNoOfHeader(const BLOBLIST *pBlobList);

/******************************************************************************/

void myGROpen()
{
   freeEx(pGrVersion);
   pGrVersion=strvcat("myGR,",GECoreVersion,"+",GRCoreVersion,NULL);
   freeEx(pGrLog);
   freeEx(pGrErrorLog);
   freeEx(pGrTemporaryFiles);
   pGrLog=pGrErrorLog=0;
   pGrTemporaryFiles=0;
}

void myGRClose()
{
   freeEx(pGrVersion);
   freeEx(pGrLog);
   freeEx(pGrErrorLog);
   freeEx(pGrTemporaryFiles);
   pGrVersion=0;
   pGrLog=pGrErrorLog=0;
   pGrTemporaryFiles=0;
   myGRSetEchoFunction(NULL);
}

void myGRGEClose(
   char *pGEClose
   )
{
   GEClose((MYDISPLAY*)pGEClose);
}

const char *myGRVersionPointer()
{
   return pGrVersion;
}

const char *myGRLogPointer()
{
   return pGrLog;
}

const char *myGRErrorLogPointer()
{
   return pGrErrorLog;
}

const char *myGRTemporaryFilesPointer()
{
   return pGrTemporaryFiles;
}

void myGRSetEchoFunction( int(*pointer)(const char*) ) /* cpp to c */
{
   extern int (*pEchoAbroad)(const char*);
   pEchoAbroad=pointer;
}

void myGRExecute(
     const char *pWindow,const char *pGC,const GERECT *pRect,double DPIFactor,
     const char *pFile,
     BLOBLIST **ppBlobList
     )
{
   PLTLIST *PlotList;
   extern void myGRFreeBlob();
   extern char *gpGRLog,*gpGRErrorLog; // in plotio.c
   int bResult;

   *ppBlobList=0;
   
   //mySetHeapDebugger(TRUE);
   bResult=GROpen(&PlotList,pFile,0);
   if (bResult) {
      bResult=GRExecute(PlotList,ppBlobList);
      pGrLog=strdpl(gpGRLog); //20030902
   }
   if (bResult) {
      pGrTemporaryFiles=
         PlotList->pTemporaryFiles ? strdpl(PlotList->pTemporaryFiles):0;
   } else {
      pGrErrorLog=strdpl(gpGRErrorLog);
   }
   GRClose(PlotList);
   if (!bResult) return;
   //myChkHeapDebugger();
   //mySetHeapDebugger(FALSE);

   //mySetHeapDebugger(TRUE);
   {
   MYDISPLAY *myDisplay;
   
   GEOpen(&myDisplay,(char*)pGC,(float)DPIFactor,(char*)pWindow);
   //MYDISPLIST **list,char *pGC,double metricScale,char* pWindow
   GEDraw((char*)myDisplay,*ppBlobList,(GERECT*)pRect);
   GEClose(myDisplay);
   }
   //myChkHeapDebugger();
   //mySetHeapDebugger(FALSE);
}

void myGRExecuteSilently(
     const char *pFile,const char *pScript,
     BLOBLIST **ppBlobList
     )
{
   PLTLIST *PlotList;
   extern void myGRFreeBlob();
   extern char *gpGRLog,*gpGRErrorLog; // in plotio.c
   int bResult;

   *ppBlobList=0;
   
   //mySetHeapDebugger(TRUE);
   bResult=GROpen(&PlotList,pFile,pScript);
   if (bResult) {
      bResult=GRExecute(PlotList,ppBlobList);
      pGrLog=strdpl(gpGRLog); //20030902
   }
   if (bResult) {
      pGrTemporaryFiles=
         PlotList->pTemporaryFiles ? strdpl(PlotList->pTemporaryFiles):0;
   } else {
      pGrErrorLog=strdpl(gpGRErrorLog);
   }
   GRClose(PlotList);
   if (!bResult) return;
   ////0529//////////////////////myGRFreeBlob(*ppBlobList);
   ////////0529//////////////////freeEx(pGrLog);
   ////////////0529//////////////freeEx(pGrErrorLog);
   ////////////////0529//////////freeEx(pGrTemporaryFiles);
   //myChkHeapDebugger(); /* See "extern char qErrorMessage[]" in gecore.c */
   //mySetHeapDebugger(FALSE);
}

void myGRRefresh(
     const BLOBLIST *pBlobList,
     const char *pWindow,const char *pGC,const GERECT *pRect,double DPIFactor,
     int nEvent,int x,int y,double dFactor,
     int bGEClose,char **ppGEClose
     )
{
   MYDISPLAY *myDisplay;

   if (!pBlobList) return;
   if (!nEvent) nEvent='f';

   GEOpen(&myDisplay,(char*)pGC,(float)DPIFactor,(char*)pWindow);
   //GEDraw((char*)myDisplay,pBlobList,pRect);
   GEDrawEx((char*)myDisplay,(BLOBLIST*)pBlobList,(GERECT*)pRect,
      nEvent,x,y,(float)dFactor);
   if (bGEClose) {
      GEClose(myDisplay);
      if (ppGEClose) ppGEClose=NULL;
   } else {
      *ppGEClose=(char*)myDisplay;
   }
}

void myGRRefreshPlotViewport(
     const BLOBLIST *pBlobList,
     const char *pWindow,const char *pGC,const GERECT *pRect,double DPIFactor,
     int nEvent,int x,int y,double dFactor,
     int nPlotIndex, /* 1..* */
     int bGEClose,char **ppGEClose
     )
{
   BLOBLIST *pList;
   BLOBNODE *pNode,*pNodeGC,*pNodeRect;
   BLOBGC gc;
   BLOBPOINT points[5];
   int nHeaderCount,nLength;
   char sBuffer[256],*pAddress;
   BLOBCLIPWIN clip;
   double x1,y1,x2,y2;

   if (!pBlobList) return;
   if (nPlotIndex<=0) return;

   BLDuplicateList(pBlobList,&pList);

   pNode=pList->head;
   nHeaderCount=0;

   while (pNode) {
      if ((int)pNode->any.type==BL_COMMAND)
         nHeaderCount++;
      if (nHeaderCount==nPlotIndex) {
         nLength=BLNodeTotal(pNode);
         strncpy(sBuffer,BLNodeObjAddr(pNode),nLength);
         sBuffer[nLength]=0;
         if (strncmp(sBuffer,"Canvas",6)) break;
         pAddress=sBuffer;
         skipblack(&pAddress);skipwhite(&pAddress);
         x1=atof(pAddress);
         skipblack(&pAddress);skipwhite(&pAddress);
         y1=atof(pAddress);
         skipblack(&pAddress);skipwhite(&pAddress);
         x2=atof(pAddress);
         skipblack(&pAddress);skipwhite(&pAddress);
         y2=atof(pAddress);
         clip.x1=(double)x1;clip.x2=(double)x2;
         clip.y1=(double)y1;clip.y2=(double)y2;
         BLAddClipWin(pList,&clip,1);
         gc.gc_type=GE_GCPolygon;
         gc.gc_mask=GE_GCMaskFillDefault;
         gc.foreground=RGB(255,255,0);
         gc.polyarc_attr=GE_PolyArcFill;
         BLAddGC(pList,&gc,1);
         pNodeGC=pList->tail;
         points[0].x=(double)x1;points[0].y=(double)y1;
         points[1].x=(double)x2;points[1].y=(double)y1;
         points[2].x=(double)x2;points[2].y=(double)y2;
         points[3].x=(double)x1;points[3].y=(double)y2;
         points[4].x=(double)x1;points[4].y=(double)y1;
         BLAddPoly(pList,points,5);
         pNodeRect=pList->tail;
         AnyMovDLObject(pList,pList->tail,pNode->next);
         AnyMovDLObject(pList,pList->tail,pNode->next);
         AnyMovDLObject(pList,pList->tail,pNode->next);
         break;
      }
      pNode=pNode->next;
   }

   myGRRefresh(pList,pWindow,pGC,pRect,DPIFactor,nEvent,x,y,dFactor,
      bGEClose,ppGEClose);

   /* BLFreeObject(pList,pNodeGC); */
   /* BLFreeObject(pList,pNodeRect); */
   BLCloseList(pList);
}

void myGRRefreshPlotByOne(
     const BLOBLIST *pBlobList,
     const char *pWindow,const char *pGC,const GERECT *pRect,double DPIFactor,
     int nEvent,int x,int y,double dFactor,
     int nPlotIndex, /* 1..* */
     int bGEClose,
     char **ppGEClose
     )
{
   BLOBLIST *pList;
   BLOBNODE *pNode,*pFirst,*pLast,*pNext;
   int nIndex,nResult;

   if (!pBlobList) return;
   if (nPlotIndex<=0) return;

   BLDuplicateList(pBlobList,&pList);

   pFirst=pList->head;
   for (nIndex=0;nIndex<=nPlotIndex;nIndex++) {
      if (nIndex) pFirst=pFirst->next;
      nResult=BLFindObject(pList,&pFirst,BL_HEADER,'l');
      if (nResult) {
         pNode=pList->head;
         while (pNode!=pFirst) {
            pNext=pNode->next;
            BLFreeObject(pList,pNode);
            pNode=pNext;
         }
      }
   }
   pLast=pFirst->next;
   nResult=BLFindObject(pList,&pLast,BL_HEADER,'l');
   if (nResult) {
      pNode=pLast;
      while (pNode) {
          pNext=pNode->next;
          BLFreeObject(pList,pNode);
          pNode=pNext;
      }
   }

   myGRRefresh(pList,pWindow,pGC,pRect,DPIFactor,nEvent,x,y,dFactor,
      bGEClose,ppGEClose);

   BLCloseList(pList);
}

void myGRPrint(
     const BLOBLIST *pBlobList,
     const char *pWindow,const char *pGC,const GERECT *pRect,double DPIFactor,
     int nEvent,int x,int y,double dFactor,
     const char *pFileName,int bLandscape
)
{
   MYDISPLAY *myDisplay;

   if (!pBlobList || !pRect || !pFileName) return;

   GEOpen(&myDisplay,(char*)pGC,(float)DPIFactor,(char*)pWindow);
   GEPrint((char*)myDisplay,(BLOBLIST*)pBlobList,(GERECT*)pRect,
      nEvent,x,y,(float)dFactor,(char*)pFileName,bLandscape);
   GEClose(myDisplay);
}

void myGRFreeBlob( BLOBLIST *pBlobList )
{
   if (!pBlobList) return;
   BLCloseList(pBlobList);
}

void myGRBlob2File(
   const BLOBLIST *pBlobList,const char *pFile,const char *pWindow
   )
{
   /* nothing */
}

void myGRBlobChangeFont(
   const BLOBLIST *pBlobList,
   const char *pFontName
   )
{
   BLOBNODE *pNode;
   BLOBGC *pGC;

   if (!pBlobList) return;

   pNode=pBlobList->head;
   while (BLFindObject(pBlobList,&pNode,BL_GC,'l')) {
      pGC=(BLOBGC*)BLNodeObjAddr(pNode);
      strcpy2buf(pGC->font,pFontName,noof(pGC->font));
      pGC->font_type=GE_FontTrueType;
      pNode=pNode->next;
   }
}

void
myDLLPrintToFile(
   const DLL *list,
   const char *pFile
   )
{
   DLLPrintToFile((DLL*)list,(char*)pFile);
}

static
int myGRBlobNoOfHeader(
   const BLOBLIST *pBlobList
   )
{
   if (!pBlobList)
      return 0;
   {
   BLOBNODE *pNode;
   int nHeaderCount=0;

   pNode=pBlobList->head;
   while (pNode) {
      if ((int)pNode->any.type==BL_HEADER)
         nHeaderCount++;
      pNode=pNode->next;
   }
   return nHeaderCount;
   }
}

/******************************************************************************/
/* myGR.c */
