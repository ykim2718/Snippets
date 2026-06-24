/******************************************************************************/
/*                           file name : plotcv.c                             */
/*                         description : plot 2 blob                          */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43230913-43240627                    */
/* 4324 0627,0724-0730,____,____,____,____,____,____,____,____,____,____,____ */
/* 4325 0810-1118,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4326 0318,0601-1111,____,____,____,____,____,____,____,____,____,____,____ */
/* 4328 0722,1017,1021,____,____,____,____,____,____,____,____,____,____,____ */
/* 4329 0118,0122,0411,0521,0612,0911,____,____,____,____,____,____,____,____ */
/* 4330 0307,0809-0831,____,____,____,____,____,____,____,____,____,____,____ */
/* 4331 0604,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0301-0431,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0222-0327,0511,0605-0616,0626,0821-1004,1208,____,____,____,____,____ */
/* 4334 0103,0220,0302-0307,0318,0410,0515,____,____,____,____,____,____,____ */
/* 4336 0215-0320,0403,0501,0822,1102,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <setjmp.h>
#include "myCore.h"
#include "blob.h"
#include "number.h"
#include "nrecipe.h"
#include "tools.h"
#include "gecore.h"
#include "geprint.h"
#include "parser.h"
#include "plotsymb.h"
#include "plot.h"

/******************************************************************************/

#define SYMBOL_SCALE_FACTOR    0.01*0.2   /* 1/100 nScale & empirical 0.2 */
#define TICK_MAX_FREQUENCY     256
#define TICK_MINOR_SIZE_FACTOR 0.01
#define TICK_MAJOR_SIZE_FACTOR 0.025

static PLTXFRM *CPX; /* Current Plot Transformation */
static WLDWINSIZE PLTClipWindow;

/*---p-l-o-t-2-B-L-O-B--------------------------------------------------------*/

static int GetPlotNameAddress(PLTNODE *pPlot,const char **ppName);

static int DoGlob(PLTLIST *pList);
static int DoCanvas();

static int DoAxis();
static int DoAxisProcess();
static int DoAxisProcessLinear();
static int DoAxisProcessLog10();
static int DoAxisProcessNormal();
static int DoAxisProcessSeries();
static int AxisXLine(
           int bAxisOn,
           double xStart,double yStart,double xEnd,double yEnd,
           BLOBGC GC,int nAxisAttr,double *pReturn
           );
static int AxisYLine(
           int bAxisOn,
           double xStart,double yStart,double xEnd,double yEnd,
           BLOBGC GC,int nAxisAttr,double *pReturn
           );
static int AxisXTick(
           int bMajorTickOn,int bMinorTickOn,
           double xStart,double xEnd,double yy,double y1,double y2,
           BLOBGC GC,int nMajorAttr,int nMinorAttr,
           double dMajorStep,double dMinorStep,
           int nScale
           );
static int OnAxisXTick();
static int AxisXLabel(
           int bLabelOn,
           double xStart,double xEnd,double yy,double y1,double y2,
           double dMajorStep,double dMinorStep,
           FONTATTR TC,int nScale,char *pFormat,char *pEquation,
           char **ppHeader,int nHeader,
           PAXIS *pAxis,/* pAxis must be reconstructed efficienty later, shik990329 */
           PLTNODE *pPlot /* totally awesome 2003.11.1 */
           );
static int OnAxisXLabel();
static int OnAxisXLabelSeries();
static int AxisXGrid(
           int bMajorGridOn,int bMinorGridOn,
           double xStart,double xEnd,double dRef1,double dRef2,
           BLOBGC MajorGC,BLOBGC MinorGC,
           double dMajorStep,double dMinorStep,
           int nScale
           );
static int OnAxisXGrid();
static int AxisYTick(
           int bMajorTickOn,int bMinorTickOn,
           double yStart,double yEnd,double xx,double x1,double x2,
           BLOBGC GC,int nMajorAttr,int nMinorAttr,
           double dMajorStep,double dMinorStep,
           int nScale
           );
static int OnAxisYTick();
static int AxisYLabel(
           int bLabelOn,
           double yStart,double yEnd,double xx,double x1,double x2,
           double dMajorStep,double dMinorStep,
           FONTATTR TC,int nScale,char *pFormat,char *pEquation,
           PAXIS *pAxis, /* pAxis must be reconstructed efficienty later, shik990329 */
           PLTNODE *pPlot
           );
static int OnAxisYLabel();
static int AxisYGrid(
           int bMajorGridOn,int bMinorGridOn,
           double yStart,double yEnd,double dRef1,double dRef2,
           BLOBGC MajorGC,BLOBGC MinorGC,
           double dMajorStep,double dMinorStep,
           int nScale
           );
static int OnAxisYGrid();
static double GetLabelValueFromEquation();

static int DoLegend();
static long GetColorValueFromZValue();
static int DoLegendFlat3D();

static int DoData();
static int DoDataPlus();
static int DrawDataSymbolLine();
static int DrawDataSymbolLineEx(); /* 20030303 */
static int DrawDataSymbolPoly();
static int DrawDataSymbolCircle();
static int DrawDataSymbolMoment();
static int DoDataMoment();
static int DoDataFlat3D(); 
static int DrawPLTBarSymbol(); /* 2000.2.22, ?? */
static int DoDataBar();   /* 2000.2.22, ?? */

static int DoText();
static int DoUserFunction();

static int EchoPlotPoints();

/*---p-l-o-t-2-B-L-O-B--CORE--------------------------------------------------*/

static BLOBLIST *DBList=NULL;
static int DBSetList();
static int DBHeader();
static int DBPlotPoints();
static int DBXmtx2DData();
static int DBGC();
static int DBData();
static int DBPoint();
static int DBLine();
static int DBLines();
static int DBPolyline();
static int DBArc();
static int DBTextAttr(FONTATTR *font,XFRMATTR *xfrm);
static int DBText();
static int DBClipWin();
static int DBPrint();

/*---typedef------------------------------------------------------------------*/
typedef struct { /* 2003.11.1- */
   SCALEATTR scale;
   BLOBLINE line; /* (x1,y1)=start,(x2,y2)=end, in real scale */
   BLOBPOINT step; /* x=x-step,y=y-step, in real scale */
   IPTRFN pProc; /* with argument of AXISPROCMODE */
   enum { DATA,TEXT } label_source;
   enum { CLOCKWISE,ANTICLOCKWISE } label_direction;
   enum { INSIDE,OUTSIDE,CROSS } major_tick_loc,minor_tick_loc;
   FONTATTR fa_title,fa_label;
   char *pTitle,*pFormat,*pEquation,**ppLabel;
   int nLabel;
} AXIS2DTAG;

static
int DoAxisProcessLog10Ex( pTag )
   AXIS2DTAG *pTag;
{
   /*
   double dStart=pData->dAxisStart,dEnd=pData->dAxisEnd;
   double dMinorStep=pData->dMinorStep,dMajorStep=pData->dMajorStep,
          dMinorStep4;
   double dValue,dStep;
   int nCount=0;
 
   dStart=exp10(dStart);
   dEnd=exp10(dEnd);
   dMinorStep=exp10(dMinorStep);
   dMajorStep=exp10(dMajorStep);
   dMinorStep4=dMinorStep/4.0;
   dValue=dStart;
   (*pData->pProc)(AXISPROC_START,pData,dValue);
   do {
      if (nCount++>=TICK_MAX_FREQUENCY) return TRUE;
      dStep=stepRound(dValue,dMinorStep);
      if (ABS(ABS(dMajorStep)-ABS(dStep))<dMinorStep4) {
         dMinorStep*=10.0;
         dMajorStep*=10.0;
         dMinorStep4*=10.0;
         (*pData->pProc)(AXISPROC_LARGETICK,pData,log10(dStep));
      } else {
         (*pData->pProc)(AXISPROC_SMALLTICK,pData,log10(dStep));
      }
      dValue+=dMinorStep;
   } while (dValue<dEnd+dMinorStep4);
   (*pData->pProc)(AXISPROC_END,pData,dValue);
   */
   return TRUE;
}

/*----------------------------------------------------------------------------*/

typedef struct { /* linear nScale */
   double dAxisStart,dAxisEnd;
   double dMajorStep,dMinorStep;
   IPTRFN pProc;
} AXISANYDATA;

typedef struct { /* linear nScale */
   double dAxisStart,dAxisEnd;
   double dMajorStep,dMinorStep;
   IPTRFN pProc;
   /**/
   double dAxisRef;
   BLOBGC GC;
   double dSmallTickStart,dSmallTickEnd,
          dLargeTickStart,dLargeTickEnd;
   int bMajorTickOn,bMinorTickOn;
} AXISTICKDATA;

typedef struct { /* linear nScale */
   double dAxisStart,dAxisEnd;
   double dMajorStep,dMinorStep;
   IPTRFN pProc;
   /**/
   double dAxisRef;
   FONTATTR TC;
   double dLargeTickSize;
   char *pFormat,*pEquation,**ppHeader;
   int nHeader;
} AXISLABELDATA;

typedef struct { /* linear nScale */
   double dAxisStart,dAxisEnd;
   double dMajorStep,dMinorStep;
   IPTRFN pProc;
   /**/
   double dAxisRef1,dAxisRef2;
   BLOBGC GC;
   int nAttr;
} AXISGRIDDATA;

typedef union { /* linear scale */ /* 2001.0307 */
   int nType;
   struct {
      int nType;
      double dAxisStart,dAxisEnd,dMajorStep,dMinorStep;
      IPTRFN pProc;
   } Any;
   struct {
      int nType;
      double dAxisStart,dAxisEnd,dMajorStep,dMinorStep;
      IPTRFN pProc;
      double dAxisRef;
      BLOBGC GC;
      double dSmallTickStart,dSmallTickEnd,dLargeTickStart,dLargeTickEnd;
      int bMajorOn,bMinorOn;
   } Tick;
   struct {
      int nType;
      double dAxisStart,dAxisEnd,dMajorStep,dMinorStep;
      IPTRFN pProc;
      double dAxisRef;
      FONTATTR TC;
      double dLargeTickSize;
      char *pFormat,*pEquation,**ppHeader;
      int nHeader;
   } Label;
   struct {
      int nType;
      double dAxisStart,dAxisEnd,dMajorStep,dMinorStep;
      IPTRFN pProc;
      double dAxisRef1,dAxisRef2;
      BLOBGC GC;
      int nAttr;
   } Grid;
} AXISPROCDATA;

typedef enum {
    AXISDATA_TICK,AXISDATA_LABEL,AXISDATA_GRID
} AXISPROCDATATYPE;

typedef enum {
    AXISPROC_START=1,AXISPROC_LARGETICK=2,AXISPROC_SMALLTICK=3,AXISPROC_END=0
} AXISPROCMODE;

typedef struct { /* plot moment */
   double dMed,dLow5,dUpp5,dMinv,dMaxv;
   double dSigma;
} BOXSYMBOLDATA;

int CreatePlotBlobList();

/******************************************************************************/
/******************************************************************************/

int CreatePlotBlobList( pList,ppBlobList )
   PLTLIST *pList;
   BLOBLIST **ppBlobList;
{
   PLTNODE *pPlot=pList->pHead;
   int nPlotCount;
   const char *pName;
   extern int gtvy6uh55();

   BLOpenList(ppBlobList);
   DBSetList(*ppBlobList);
   DBHeader(
      "gr",(int)0,(long)0,pList->Glob.xfrm,TRUE,
      pPlot->pXfrm->norwin.x1,pPlot->pXfrm->norwin.y1,
      pPlot->pXfrm->norwin.x2,pPlot->pXfrm->norwin.y2);
   DBXmtx2DData(pPlot->pXfrm->attr);
   DBPrint(1);
   CPX=pPlot->pXfrm;
   DoGlob(pList);
   nPlotCount=1;
   do { 
      GetPlotNameAddress(pPlot,&pName);
      if (pName)
         Echo("-C-O-N-V-E-R-T-I-N-G-TO-BLOB- +%d \"%s\"\n",nPlotCount,pName);
      else
         Echo("+%d \"\"\n",nPlotCount);
      nPlotCount++;
      DBHeader(
         "gr",(int)0,(long)0,pList->Glob.xfrm,FALSE,
         pPlot->pXfrm->norwin.x1,pPlot->pXfrm->norwin.y1,
         pPlot->pXfrm->norwin.x2,pPlot->pXfrm->norwin.y2);
      DBXmtx2DData(pPlot->pXfrm->attr);
      DBPrint(1);
      CPX=pPlot->pXfrm;
      if (pList->Glob.bEchoPlotPoints) EchoPlotPoints(pPlot);
      /* DBPlotPoints(pPlot); */
      DoCanvas(pPlot);
      DoAxis(pPlot);
      switch (pPlot->pAttr->type) {
      case PLT2D_GENETIC :
      case PLT2D_GENETICPLUS :
      case PLT2D_MOMENT :
      case PLT2D_BAR :     DoLegend(pPlot);break;
      case PLT2D_FLAT3D :  DoLegendFlat3D(pPlot);break;
      }
      switch (pPlot->pAttr->type) {
      case PLT2D_GENETIC : DoData(pPlot);break;
      case PLT2D_GENETICPLUS : DoDataPlus(pPlot);break;
      case PLT2D_MOMENT :  DoDataMoment(pPlot);break;
      case PLT2D_BAR :     DoDataBar(pPlot);break;
      case PLT2D_FLAT3D :  DoDataFlat3D(pPlot);break;
      }
      DBPrint(1);
      DoUserFunction(pPlot);
      DoText(pPlot);
   } while (pPlot=pPlot->next);

   Echo("\n(c)Y.Kim");
   if (!gtvy6uh55()) {
      fprintf(stderr,"bus error (core dumped)_\n");
      exit(1);
   }
   return TRUE;
}

static
int GetPlotNameAddress( pPlot,ppName )
   PLTNODE *pPlot;
   const char **ppName;
{
   PTEXT *tx;
   int i,j;

   *ppName=0;

   if (!*ppName) { /* 20030818 */
      for (i=0;i<pPlot->pAxis->zTotal;i++) {
         *ppName=pPlot->pAxis->zAxis[i]->pTitle;
         if (*ppName) break;
      }
      if (!*ppName) {
         for (i=0;i<pPlot->pAxis->yTotal;i++) {
            *ppName=pPlot->pAxis->yAxis[i]->pTitle;
            if (*ppName) break;
         }
         if (!*ppName) {
            for (i=0;i<pPlot->pAxis->xTotal;i++) {
               *ppName=pPlot->pAxis->xAxis[i]->pTitle;
               if (*ppName) break;
            }
         }
      }
   }
   if (!*ppName) {
      for (i=0,j=0;i<pPlot->pText->nTotal;i++) {
         tx=pPlot->pText->qText[i];
         if (!tx->pString) continue;
         if (*ppName=tx->pString) break;
      }
   }
   if (!*ppName) {
      for (i=0;i<pPlot->pSlct->nLegendTotal;i++) {
         if (!pPlot->pSlct->pLegend[i].bLegendOn) continue; /* 20030320 */
         if (*ppName=pPlot->pSlct->pLegend[i].pText) break;
      }
   }
   return *ppName ? TRUE : FALSE;
}

static
int DoGlob( PLTLIST *pList )
{
   extern double GetTextYPitchOfNorWin();
   extern double GetXPosOfWldWin();
   extern double GetYPosOfWldWin();
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
   x=x1+(x2-x1)/2.0;
   y=GetTextYPitchOfNorWin(&(pList->Glob.TextAttr));
   y=y2+y*pList->Glob.dTitleSpaceFactor;
   x=GetXPosOfWldWin(pList->pHead,x);
   y=GetYPosOfWldWin(pList->pHead,y);

   pPlot=pList->pHead;
   DBTextAttr(&pList->Glob.TextAttr,&CPX->attr);
   DBText((*pPlot->pXfrm->xCnvFn)(x),(*pPlot->pXfrm->yCnvFn)(y),
          pList->Glob.pTitle);

   return TRUE;
}

static
int DoCanvas( pPlot )
   PLTNODE *pPlot;
{
   double x1,y1,x2,y2;
   char qBuffer[256];
   
   x1=(*pPlot->pXfrm->xCnvFn)(pPlot->pXfrm->wldwin.x1);
   y1=(*pPlot->pXfrm->yCnvFn)(pPlot->pXfrm->wldwin.y1);
   x2=(*pPlot->pXfrm->xCnvFn)(pPlot->pXfrm->wldwin.x2);
   y2=(*pPlot->pXfrm->yCnvFn)(pPlot->pXfrm->wldwin.y2);
   sprintf(qBuffer,"Canvas %1.2f %1.2f %1.2f %1.2f",x1,y1,x2,y2);
   BLAddCommand(DBList,qBuffer,strlen(qBuffer));
   //DBClipWin(x1,y1,x2,y2);

   return TRUE;

   if (pPlot->pAttr->back
   && pPlot->prev)
      return TRUE;

   {
   BLOBGC gc;
   gc.gc_type=GE_GCPolygon;
   gc.gc_mask=GE_GCMaskFillDefault;
   gc.foreground=RGB(225,225,225);
   gc.polyarc_attr=GE_PolyArcFill;
   DBGC(gc);
   }
   {
   BLOBPOINT points[5];
   points[0].x=x1;points[0].y=y1;
   points[1].x=x2;points[1].y=y1;
   points[2].x=x2;points[2].y=y2;
   points[3].x=x1;points[3].y=y2;
   points[4].x=x1;points[4].y=y1;
   DBPolyline(points,5);
   }
   return TRUE;
}

static
int DoAxis( pPlot )
   PLTNODE *pPlot;
{
   int nIndex;
   PAXIS *pAx;
   double dRef;

   for (nIndex=0;nIndex<pPlot->pAxis->xTotal;nIndex++) {
      pAx=pPlot->pAxis->xAxis[nIndex];
      AxisXGrid(
         pAx->bGridMajorOn,pAx->bGridMinorOn,
         pAx->dAxisX1,pAx->dAxisX2,pPlot->pSlct->ylowb,pPlot->pSlct->yuppb,
         pAx->GridGCMajorAttr,pAx->GridGCMinorAttr,
         pAx->dTickMajorStep,pAx->dTickMinorStep,pPlot->pAttr->xScale);
      AxisXLine(
         pAx->bAxisOn,
         pAx->dAxisX1,pAx->dAxisY1,pAx->dAxisX2,pAx->dAxisY2,
         pAx->AxisGCAttr,pAx->AxisAttr,&dRef);
      AxisXTick(
         pAx->bTickMajorOn,pAx->bTickMinorOn,
         pAx->dAxisX1,pAx->dAxisX2,dRef,
         pPlot->pSlct->ylowb,pPlot->pSlct->yuppb,
         pAx->AxisGCAttr,pAx->TickMajorAttr,pAx->TickMinorAttr,
         pAx->dTickMajorStep,pAx->dTickMinorStep,pPlot->pAttr->xScale);
      AxisXLabel(
         pAx->bLabelOn,
         pAx->dAxisX1,pAx->dAxisX2,dRef,pPlot->pSlct->ylowb,pPlot->pSlct->yuppb,
         pAx->dTickMajorStep,pAx->dTickMinorStep,
         pAx->FontAttr,pPlot->pAttr->xScale,pAx->pLabelFormat,pAx->pLabelEquation,
         pPlot->pData->ppHeader,pPlot->pData->nHeader,
         pAx,pPlot);
   }

   for (nIndex=0;nIndex<pPlot->pAxis->yTotal;nIndex++) {
      pAx=pPlot->pAxis->yAxis[nIndex];
      AxisYGrid(
         pAx->bGridMajorOn,pAx->bGridMinorOn,
         pAx->dAxisY1,pAx->dAxisY2,pPlot->pSlct->xlowb,pPlot->pSlct->xuppb,
         pAx->GridGCMajorAttr,pAx->GridGCMinorAttr,
         pAx->dTickMajorStep,pAx->dTickMinorStep,pPlot->pAttr->yScale);
      AxisYLine(
         pAx->bAxisOn,
         pAx->dAxisX1,pAx->dAxisY1,pAx->dAxisX2,pAx->dAxisY2,
         pAx->AxisGCAttr,pAx->AxisAttr,&dRef);
      AxisYTick(
         pAx->bTickMajorOn,pAx->bTickMinorOn,
         pAx->dAxisY1,pAx->dAxisY2,dRef,
         pPlot->pSlct->xlowb,pPlot->pSlct->xuppb,
         pAx->AxisGCAttr,pAx->TickMajorAttr,pAx->TickMinorAttr,
         pAx->dTickMajorStep,pAx->dTickMinorStep,pPlot->pAttr->yScale);
      AxisYLabel(
         pAx->bLabelOn,
         pAx->dAxisY1,pAx->dAxisY2,dRef,pPlot->pSlct->xlowb,pPlot->pSlct->xuppb,
         pAx->dTickMajorStep,pAx->dTickMinorStep,
         pAx->FontAttr,pPlot->pAttr->yScale,pAx->pLabelFormat,pAx->pLabelEquation,
         pAx,pPlot);
   }

   return TRUE;
}

static
int DoAxisProcess( nScale,pData )
   int nScale;
   AXISANYDATA *pData;
{
   switch (nScale) {
   case SCALE_LIN :    DoAxisProcessLinear(pData);break;
   case SCALE_LOG10 :  DoAxisProcessLog10(pData); break;
   case SCALE_NORM :   DoAxisProcessNormal(pData);break;
   case SCALE_SERIES : DoAxisProcessSeries(pData);break;
   }
   return TRUE;
}

static 
int DoAxisProcessLinear( pData )
   AXISANYDATA *pData;
{      
   double dStart=pData->dAxisStart,dEnd=pData->dAxisEnd;
   double dMinorStep=pData->dMinorStep,dMajorStep=pData->dMajorStep,
          dMinorStep4;
   double dValue,dStep,dTolerance;
   int nCount=0;
  
   dMinorStep4=dMinorStep/4.0;
   dValue=dStart;
   (*pData->pProc)(AXISPROC_START,pData,dValue);
   do {
      if (nCount++>=TICK_MAX_FREQUENCY) return TRUE;
      dStep=stepRound(dValue,dMinorStep);
      if (dStep<dStart) goto S;
      dTolerance=stepRound(dValue,dMajorStep);
      if (ABS(ABS(dTolerance)-ABS(dStep))<dMinorStep4) {
         dValue=dStep;
         (*pData->pProc)(AXISPROC_LARGETICK,pData,dStep);
      } else {
         (*pData->pProc)(AXISPROC_SMALLTICK,pData,dStep);
      }  
S:    dValue+=dMinorStep;
   } while (dValue<dEnd+dMinorStep4);
   (*pData->pProc)(AXISPROC_END,pData,dValue);
   return TRUE;
}

static
int DoAxisProcessLog10( pData )
   AXISANYDATA *pData;
{
   double dStart=pData->dAxisStart,dEnd=pData->dAxisEnd;
   double dMinorStep=pData->dMinorStep,dMajorStep=pData->dMajorStep,
          dMinorStep4;
   double dValue;
   int nCount=0;
 
   dStart=exp10(dStart);
   dEnd=exp10(dEnd);
   dMajorStep=exp10(dMajorStep);
   (*pData->pProc)(AXISPROC_START,pData,0);
   if (dMajorStep==10) {
      dValue=dvalue(order(dStart));
      dMinorStep=dValue;
      while (dValue<dStart) dValue+=dMinorStep;
      dStart=dValue;
      dMinorStep4=dMinorStep/4;
      do {
         double d1,d2;
         if (nCount++>=TICK_MAX_FREQUENCY) goto E;
         dValue=stepRound(dValue,dMinorStep);
         d1=log10(dValue);
         d2=(int)round(d1);
         if (ABS(d1-d2)<0.0457) {
            (*pData->pProc)(AXISPROC_LARGETICK,pData,log10(dValue));
            dStart=dValue;
            dMinorStep=dValue;
            dMinorStep4=dMinorStep/4;
         } else {
            (*pData->pProc)(AXISPROC_SMALLTICK,pData,log10(dValue));
         }
         dValue+=dMinorStep;
      } while (dValue<dEnd+dMinorStep4);
   } else if (dMajorStep>10) {
      dValue=dvalue(order(dStart));
      while (dValue<dStart) dValue*=dMajorStep;
      dMinorStep=dValue;
      do {
         if (nCount++>=TICK_MAX_FREQUENCY) goto E;
         dValue=stepRound(dValue,dMinorStep);
         (*pData->pProc)(AXISPROC_LARGETICK,pData,log10(dValue));
         dStart=dValue;
         dMinorStep=dValue*dMajorStep/10;
         dValue*=dMajorStep;
      } while (dValue<dEnd+dMinorStep);
   }
E: (*pData->pProc)(AXISPROC_END,pData,0);
   return TRUE;
}

static
int DoAxisProcessNormal( pData )
   AXISANYDATA *pData;
{
   static double pLoTable[]={0.00001,0.0001,0.001,0.01,0.1};
   static double pHiTable[]={0.9,0.99,0.999,0.9999,0.99999};
   int nTable;
   double dStart,dEnd,dPoint,dMinorStep,dMajorStep,dTolerance;
   double smallPt,largePt,tmp;
   int nCount=0,nIndex,j;
 
   nTable=sizeof(pLoTable)/sizeof(double);
   dStart=cnorm(pData->dAxisStart,0.0,1.0);
   dEnd=cnorm(pData->dAxisEnd,0.0,1.0);
   dMinorStep=cnorm(pData->dMinorStep,0.0,1.0);
   dMajorStep=cnorm(pData->dMajorStep,0.0,1.0);
   dStart=stepRound(dStart,dvalue(nIndex=(order(dStart)-0)));
   dEnd=stepRound(dEnd,dvalue(nIndex));
   dMajorStep=stepRound(dMajorStep,dvalue(order(dMajorStep)));
   dMinorStep=stepRound(dMinorStep,dvalue(order(dMinorStep)));
   dTolerance=dMinorStep*0.02;
   (*pData->pProc)(AXISPROC_START,pData,dStart);
   for (nIndex=0;nIndex<nTable-1;nIndex++) {
      if (pLoTable[nIndex]<=dStart && dStart<pLoTable[nIndex+1]) {
         for (j=nIndex;j<nTable;j++) {
            dPoint=pLoTable[j];
            if (dPoint>dEnd) goto R;
            tmp=icnorm(dPoint);
            (*pData->pProc)(AXISPROC_LARGETICK,pData,tmp);
            dPoint*=5.0;
            if (dPoint>dEnd) goto R;
            tmp=icnorm(dPoint);
            (*pData->pProc)(AXISPROC_SMALLTICK,pData,tmp);
         }
         break;
      }
   }
   dPoint=0.1;
   while ((0.1-dTolerance)<=dPoint && dPoint<=(0.9+dTolerance)) {
      if (nCount++>=TICK_MAX_FREQUENCY) return FALSE;
      smallPt=stepRound(dPoint,dMinorStep);
      largePt=stepRound(dPoint,dMajorStep);
      if (ABS(ABS(largePt)-ABS(smallPt))<dTolerance) {
         tmp=icnorm(dPoint=largePt);
         (*pData->pProc)(AXISPROC_LARGETICK,pData,tmp);
      } else {
         tmp=icnorm(dPoint=smallPt);
         (*pData->pProc)(AXISPROC_SMALLTICK,pData,tmp);
      }
      dPoint+=dMinorStep;
   }
   dPoint=0.99;
   for (nIndex=0;nIndex<nTable-1;nIndex++) {
      if (pHiTable[nIndex]<=dPoint && dPoint<pHiTable[nIndex+1]) {
         for (j=nIndex;j<nTable;j++) {
            dPoint=pHiTable[j];
            if (dPoint>dEnd) goto R;
            tmp=icnorm(dPoint);
            (*pData->pProc)(AXISPROC_LARGETICK,pData,tmp);
            dPoint+=(1-dPoint)*0.5;
            if (dPoint>dEnd) goto R;
            tmp=icnorm(dPoint);
            (*pData->pProc)(AXISPROC_SMALLTICK,pData,tmp);
         }
         break;
      }
   }
R: (*pData->pProc)(AXISPROC_END,pData,dEnd);
   return TRUE;
}

static
int DoAxisProcessSeries( pData )
   AXISANYDATA *pData;
{
   double dStart,dEnd,dPos,dMajorStep,dTolerance;
   int nCount=0;
  
   dMajorStep=pData->dMajorStep;
   dTolerance=dMajorStep*0.1;
   dStart=pData->dAxisStart; /* +dMajorStep; */
   dEnd=pData->dAxisEnd; /* -dMajorStep; */
   (*pData->pProc)(AXISPROC_START,pData,dPos=dStart);
   do {
      if (nCount++>=TICK_MAX_FREQUENCY) return FALSE;
      dPos=stepRound(dPos,dMajorStep);
      (*pData->pProc)(AXISPROC_LARGETICK,pData,dPos);
      dPos+=dMajorStep;
   } while (dPos<dEnd+dTolerance);
   (*pData->pProc)(AXISPROC_END,pData,dPos);
   return TRUE;
}

static
int AxisXLine(
   int bAxisOn,
   double xStart,double yStart,double xEnd,double yEnd,
   BLOBGC GC,int AxisAttr,double *pReturn
)
{
   xStart=(*CPX->xCnvFn)(xStart);
   yStart=(*CPX->yCnvFn)(yStart);
   xEnd=(*CPX->xCnvFn)(xEnd);
   yEnd=(*CPX->yCnvFn)(yEnd);
   if (bAxisOn) {
      DBGC(GC);
      switch (AxisAttr) {
      case AXIS_ATLOWERBOUND :
      case AXIS_ATANYPOSITION :
         DBLine(xStart,yStart,xEnd,yStart);
         break;
      case AXIS_ATMIDDLE :
         DBLine(xStart,*pReturn,xEnd,*pReturn);
         break;
      case AXIS_ATUPPERBOUND :
         DBLine(xStart,yEnd,xEnd,yEnd);
         break;
      }
   }
   switch (AxisAttr) {
   case AXIS_ATLOWERBOUND :
   case AXIS_ATANYPOSITION : *pReturn=yStart;break;
   case AXIS_ATMIDDLE :      *pReturn=(yStart+yEnd)/2.0;break;
   case AXIS_ATUPPERBOUND :  *pReturn=yEnd;break;
   }
   *pReturn=(*CPX->yInvFn)(*pReturn);
   return TRUE;
}

static
int AxisYLine(
   int bAxisOn,
   double xStart,double yStart,double xEnd,double yEnd,
   BLOBGC GC,int nAxisAttr,double *pReturn
)
{
   xStart=(*CPX->xCnvFn)(xStart);
   yStart=(*CPX->yCnvFn)(yStart);
   xEnd=(*CPX->xCnvFn)(xEnd);
   yEnd=(*CPX->yCnvFn)(yEnd);
   if (bAxisOn) {
      DBGC(GC);
      switch (nAxisAttr) {
      case AXIS_ATLOWERBOUND :
      case AXIS_ATANYPOSITION :
         DBLine(xStart,yStart,xStart,yEnd);
         break;
      case AXIS_ATMIDDLE :
         DBLine(*pReturn,yStart,*pReturn,yEnd);
         break;
      case AXIS_ATUPPERBOUND :
         DBLine(xEnd,yStart,xEnd,yEnd);
         break;
      }
   }
   switch (nAxisAttr) {
   case AXIS_ATLOWERBOUND :
   case AXIS_ATANYPOSITION : *pReturn=xStart;break;
   case AXIS_ATMIDDLE :      *pReturn=(xStart+xEnd)/2.0;break;
   case AXIS_ATUPPERBOUND :  *pReturn=xEnd;break;
   }
   *pReturn=(*CPX->xInvFn)(*pReturn);
   return TRUE;
}

static
int AxisXTick(
   int bMajorTickOn,int bMinorTickOn,
   double xStart,double xEnd,double yy,double y1,double y2,
   BLOBGC GC,int nMajorAttr,int nMinorAttr,
   double dMajorStep,double dMinorStep,
   int nScale
)
{
   AXISTICKDATA *pData;
   double small_sz,large_sz,
          smallTick_sy,smallTick_dy,
          largeTick_sy,largeTick_dy;

   pData=salloc(AXISTICKDATA,1);
   pData->dAxisStart=(*CPX->xCnvFn)(xStart);
   pData->dAxisEnd=  (*CPX->xCnvFn)(xEnd);
   pData->dMinorStep= (*CPX->xCnvFn)(dMinorStep);
   pData->dMajorStep= (*CPX->xCnvFn)(dMajorStep);
   pData->dAxisRef=  (*CPX->yCnvFn)(yy);
   memcpy((char*)&pData->GC,(char*)&GC,sizeof(BLOBGC));
   y1=(*CPX->yCnvFn)(y1);
   y2=(*CPX->yCnvFn)(y2);
   small_sz=TICK_MINOR_SIZE_FACTOR*(y2-y1);
   large_sz=TICK_MAJOR_SIZE_FACTOR*(y2-y1);
   smallTick_sy=0.0;
   largeTick_sy=0.0;
   smallTick_dy=small_sz;
   largeTick_dy=large_sz;
   switch (nMajorAttr) {
   case TICK_INSIDE : if (pData->dAxisRef>(y1+y2)/2.0) largeTick_dy*=-1.0; break;
   case TICK_OUTSIDE : if (pData->dAxisRef<(y1+y2)/2.0) largeTick_dy*=-1.0; break;
   case TICK_CROSS : largeTick_sy=-large_sz; break;
   }
   switch (nMinorAttr) {
   case TICK_INSIDE : if (pData->dAxisRef>(y1+y2)/2.0) smallTick_dy*=-1.0; break;
   case TICK_OUTSIDE : if (pData->dAxisRef<(y1+y2)/2.0) smallTick_dy*=-1.0; break;
   case TICK_CROSS : smallTick_sy=-small_sz; break;
   }
   pData->dSmallTickStart=smallTick_sy;
   pData->dSmallTickEnd=smallTick_dy;
   pData->dLargeTickStart=largeTick_sy;
   pData->dLargeTickEnd=largeTick_dy;
   pData->pProc=OnAxisXTick;
   pData->bMajorTickOn=bMajorTickOn;
   pData->bMinorTickOn=bMinorTickOn;
   DoAxisProcess(nScale,pData);
   free(pData);
   return TRUE;
}

static
int OnAxisXTick( nProcMode,pData,x )
   AXISPROCMODE nProcMode;
   AXISTICKDATA *pData;
   double x;
{
   switch (nProcMode) {
   case AXISPROC_START :
      DBGC(pData->GC);
      break;
   case AXISPROC_LARGETICK :
      if (!pData->bMajorTickOn) break;
      DBLine(x,pData->dAxisRef+pData->dLargeTickStart,
         x,pData->dAxisRef+pData->dLargeTickEnd);
      break;
   case AXISPROC_SMALLTICK :
      if (!pData->bMinorTickOn) break;
      DBLine(x,pData->dAxisRef+pData->dSmallTickStart,
         x,pData->dAxisRef+pData->dSmallTickEnd);
      break;
   case AXISPROC_END :
      return TRUE;
   }
   return TRUE;
}

static
int AxisXLabel(
   int bLabelOn,
   double xStart,double xEnd,double yy,double y1,double y2,
   double dMajorStep,double dMinorStep,
   FONTATTR TC,int nScale,char *pFormat,char *pEquation,
   char **ppHeader,int nHeader,
   PAXIS *pAxis,PLTNODE *pPlot ) /* These must be reconstructed efficienty later, shik990329 */
{
   AXISLABELDATA *pData;
   double dLargeTickSize;

   pData=salloc(AXISLABELDATA,1);
   pData->dAxisStart=(*CPX->xCnvFn)(xStart);
   pData->dAxisEnd=  (*CPX->xCnvFn)(xEnd);
   pData->dMinorStep=(*CPX->xCnvFn)(dMinorStep);
   pData->dMajorStep=(*CPX->xCnvFn)(dMajorStep);
   pData->dAxisRef=  (*CPX->yCnvFn)(yy);


   y1=(*CPX->yCnvFn)(y1);
   y2=(*CPX->yCnvFn)(y2);
   dLargeTickSize=(TICK_MAJOR_SIZE_FACTOR)*(y2-y1);

   if (bLabelOn) {
      if (pData->dAxisRef<(y1+y2)/2.0)
         dLargeTickSize*=-1.0;
      if (TC.angle==0) {
         //TC.align=0;
         TC.alignment&=~(GE_AlignTop|GE_AlignVCenter|GE_AlignBottom);
         if (pData->dAxisRef<(y1+y2)/2.0) TC.alignment|=GE_AlignTop;
         else                           TC.alignment|=GE_AlignBottom;
      }
      memcpy((char*)&pData->TC,(char*)&TC,sizeof(FONTATTR));
      pData->dLargeTickSize=dLargeTickSize;
      pData->pFormat=pFormat;
      pData->pEquation=pEquation;
      pData->pProc=ppHeader&&nHeader>0 ? OnAxisXLabelSeries:OnAxisXLabel;
      pData->ppHeader=ppHeader;
      pData->nHeader=nHeader;
      DoAxisProcess(nScale,pData);
   }
   
   if (pAxis->pTitle&&pAxis->bTitleShow) {
      /* 2003.11.1 */
      double x1,y1,x2,y2,x,y;
      x1=CPX->norwin.x1;
      y1=CPX->norwin.y1;
      x2=CPX->norwin.x2;
      y2=CPX->norwin.y2;
      x=x1+(x2-x1)/2.0;
      y=GetTextYPitchOfNorWin(&(pAxis->TitleFontAttr));
      y=y1-y*pAxis->dTitleSpaceFactor;
      x=GetXPosOfWldWin(pPlot,x);
      y=GetYPosOfWldWin(pPlot,y);
      pAxis->TitleFontAttr.alignment=GE_AlignHCenter|GE_AlignTop;
      DBTextAttr(&pAxis->TitleFontAttr,&CPX->attr);
      DBText((*pPlot->pXfrm->xCnvFn)(x),(*pPlot->pXfrm->yCnvFn)(y),
         pAxis->pTitle);
      /*
      double x1,x2,w,x,y;
      pAxis->TitleFontAttr.alignment=GE_AlignHCenter|GE_AlignTop;
      DBTextAttr(&pAxis->TitleFontAttr,&CPX->attr);
      x1=pData->dAxisStart;
      x2=pData->dAxisEnd;
      w=ABS(x2-x1);
      x=(x2>x1) ? x1+w/2.0 : x2+w/2.0;
      y=pData->dAxisRef+dLargeTickSize*pAxis->dTitleSpaceFactor;
      DBText(x,y,pAxis->pTitle);
      */
   }

   free(pData);
   return TRUE;
}

static
int OnAxisXLabel( nProcMode,pData,x )
   AXISPROCMODE nProcMode;
   AXISLABELDATA *pData;
   double x;
{
   const char *qAddr;
   double dResult;

   switch (nProcMode) {
   case AXISPROC_START :
      DBTextAttr(&pData->TC,&CPX->attr);
      break;
   case AXISPROC_LARGETICK :
      dResult=(*CPX->xInvFn)(x);
      dResult=GetLabelValueFromEquation(pData->pEquation,dResult);
      qAddr=dtos(dResult,pData->pFormat);
      DBText(x,pData->dAxisRef+pData->dLargeTickSize,qAddr);
      break;
   case AXISPROC_SMALLTICK :
      return TRUE;
   case AXISPROC_END : 
      return TRUE;
   }
   return TRUE;
}

static
int OnAxisXLabelSeries( nProcMode,pData,x )
   AXISPROCMODE nProcMode;
   AXISLABELDATA *pData;
   double x;
{
   int nIndex;
   const char *qAddr;
   double dResult;

   switch (nProcMode) {
   case AXISPROC_START :
      DBTextAttr(&pData->TC,&CPX->attr);
      break;
   case AXISPROC_LARGETICK :
      dResult=(x-pData->dAxisStart)/pData->dMajorStep;
      nIndex=(int)dResult-1;
      if (nIndex<0 || nIndex>=pData->nHeader) break;
      qAddr=pData->ppHeader[nIndex];
      DBText(x,pData->dAxisRef+pData->dLargeTickSize,qAddr);
      break;
   case AXISPROC_SMALLTICK :
      return TRUE;
   case AXISPROC_END : 
      return TRUE;
   }
   return TRUE;
}

static
int AxisXGrid(
   int bMajorGridOn,int bMinorGridOn,
   double xStart,double xEnd,double dRef1,double dRef2,
   BLOBGC MajorGC,BLOBGC MinorGC,
   double dMajorStep,double dMinorStep,
   int nScale
)
{
   AXISGRIDDATA *pData;

   if (bMinorGridOn) {
      pData=salloc(AXISGRIDDATA,1);
      pData->dAxisStart=(*CPX->xCnvFn)(xStart);
      pData->dAxisEnd=  (*CPX->xCnvFn)(xEnd);
      pData->dMinorStep= (*CPX->xCnvFn)(dMinorStep);
      pData->dMajorStep= (*CPX->xCnvFn)(dMajorStep);
      pData->dAxisRef1= (*CPX->yCnvFn)(dRef1);
      pData->dAxisRef2= (*CPX->yCnvFn)(dRef2);
      memcpy((char*)&pData->GC,(char*)&MinorGC,sizeof(BLOBGC));
      pData->GC.dash_list[0]=1;
      pData->GC.dash_list[1]=4;
      pData->GC.dash_offset=0;
      pData->GC.dashes=2;
      pData->nAttr=AXISPROC_SMALLTICK;
      pData->pProc=OnAxisXGrid;
      DoAxisProcess(nScale,pData);
      free(pData);
   }
   if (bMajorGridOn) {
      pData=salloc(AXISGRIDDATA,1);
      pData->dAxisStart=(*CPX->xCnvFn)(xStart);
      pData->dAxisEnd=  (*CPX->xCnvFn)(xEnd);
      pData->dMinorStep= (*CPX->xCnvFn)(dMinorStep);
      pData->dMajorStep= (*CPX->xCnvFn)(dMajorStep);
      pData->dAxisRef1= (*CPX->yCnvFn)(dRef1);
      pData->dAxisRef2= (*CPX->yCnvFn)(dRef2);
      memcpy((char*)&pData->GC,(char*)&MajorGC,sizeof(BLOBGC));
      pData->GC.dash_list[0]=1;
      pData->GC.dash_list[1]=4;
      pData->GC.dash_offset=0;
      pData->GC.dashes=2;
      pData->nAttr=AXISPROC_LARGETICK;
      pData->pProc=OnAxisXGrid;
      DoAxisProcess(nScale,pData);
      free(pData);
   }
   return TRUE;
}

static
int OnAxisXGrid( nProcMode,pData,xRef )
   AXISPROCMODE nProcMode;
   AXISGRIDDATA *pData;
   double xRef;
{
   if ((nProcMode!=AXISPROC_START)
   &&  (pData->dAxisStart==xRef || pData->dAxisEnd==xRef)) return TRUE;
   switch (nProcMode) {
   case AXISPROC_START :
      DBGC(pData->GC);
      break;
   case AXISPROC_LARGETICK :
      if (pData->nAttr==AXISPROC_SMALLTICK) break;
      DBLine(xRef,pData->dAxisRef1,xRef,pData->dAxisRef2);
      break;
   case AXISPROC_SMALLTICK :
      if (pData->nAttr==AXISPROC_LARGETICK) break;
      DBLine(xRef,pData->dAxisRef1,xRef,pData->dAxisRef2);
      break;
   case AXISPROC_END :
      return TRUE;
   }
   return TRUE;
}

static
int AxisYTick(
   int bMajorTickOn,int bMinorTickOn,
   double yStart,double yEnd,double xx,double x1,double x2,
   BLOBGC GC,int nMajorAttr,int nMinorAttr,
   double dMajorStep,double dMinorStep,
   int nScale
)
{
   AXISTICKDATA *pData;
   double small_sz,large_sz,
          smallTick_sx,smallTick_dx,
          largeTick_sx,largeTick_dx;

   pData=salloc(AXISTICKDATA,1);
   pData->dAxisStart= (*CPX->yCnvFn)(yStart);
   pData->dAxisEnd=   (*CPX->yCnvFn)(yEnd);
   pData->dMinorStep=(*CPX->yCnvFn)(dMinorStep);
   pData->dMajorStep=(*CPX->yCnvFn)(dMajorStep);
   pData->dAxisRef=   (*CPX->xCnvFn)(xx);
   memcpy((char*)&pData->GC,(char*)&GC,sizeof(BLOBGC));
   x1=(*CPX->xCnvFn)(x1);
   x2=(*CPX->xCnvFn)(x2);
   small_sz=TICK_MINOR_SIZE_FACTOR*(x2-x1);
   large_sz=TICK_MAJOR_SIZE_FACTOR*(x2-x1);
   smallTick_sx=0.0;
   largeTick_sx=0.0;
   smallTick_dx=small_sz;
   largeTick_dx=large_sz;
   switch (nMajorAttr) {
   case TICK_INSIDE : if (pData->dAxisRef>(x1+x2)/2.0) largeTick_dx*=-1.0; break;
   case TICK_OUTSIDE : if (pData->dAxisRef<(x1+x2)/2.0) largeTick_dx*=-1.0; break;
   case TICK_CROSS : largeTick_sx=-large_sz; break;
   }
   switch (nMinorAttr) {
   case TICK_INSIDE : if (pData->dAxisRef>(x1+x2)/2.0) smallTick_dx*=-1.0; break;
   case TICK_OUTSIDE : if (pData->dAxisRef<(x1+x2)/2.0) smallTick_dx*=-1.0; break;
   case TICK_CROSS : smallTick_sx=-small_sz; break;
   }
   pData->dSmallTickStart=smallTick_sx;
   pData->dSmallTickEnd=smallTick_dx;
   pData->dLargeTickStart=largeTick_sx;
   pData->dLargeTickEnd=largeTick_dx;
   pData->pProc=OnAxisYTick;
   pData->bMajorTickOn=bMajorTickOn;
   pData->bMinorTickOn=bMinorTickOn;
   DoAxisProcess(nScale,pData);
   free(pData);
   return TRUE;
}

static
int OnAxisYTick( nProcMode,pData,y )
   AXISPROCMODE nProcMode;
   AXISTICKDATA *pData; /* linear nScale */
   double y; /* linear nScale */
{
   switch (nProcMode) {
   case AXISPROC_START :
      DBGC(pData->GC);
      break;
   case AXISPROC_LARGETICK :
      if (!pData->bMajorTickOn) break;
      DBLine(pData->dAxisRef+pData->dLargeTickStart,y,
         pData->dAxisRef+pData->dLargeTickEnd,y);
      break;
   case AXISPROC_SMALLTICK :
      if (!pData->bMinorTickOn) break;
      DBLine(pData->dAxisRef+pData->dSmallTickStart,y,
         pData->dAxisRef+pData->dSmallTickEnd,y);
      break;
   case AXISPROC_END :
      return TRUE;
   }
   return TRUE;
}

static
int AxisYLabel(
   int bLabelOn,
   double yStart,double yEnd,double xx,double x1,double x2,
   double dMajorStep,double dMinorStep,
   FONTATTR TC,int nScale,char *pFormat,char *pEquation,
   PAXIS *pAxis, /* pAxis must be reconstructed efficienty later, shik990329 */
   PLTNODE *pPlot
)
{
   AXISLABELDATA *pData;
   double dLargeTickSize;
   
   pData=salloc(AXISLABELDATA,1);
   pData->dAxisStart=(*CPX->yCnvFn)(yStart);
   pData->dAxisEnd=  (*CPX->yCnvFn)(yEnd);
   pData->dMinorStep= (*CPX->yCnvFn)(dMinorStep);
   pData->dMajorStep= (*CPX->yCnvFn)(dMajorStep);
   pData->dAxisRef=  (*CPX->xCnvFn)(xx);
   
   x1=(*CPX->xCnvFn)(x1);
   x2=(*CPX->xCnvFn)(x2);
   dLargeTickSize=(TICK_MAJOR_SIZE_FACTOR)*(x2-x1);

   if (bLabelOn) {
      if (pData->dAxisRef<(x1+x2)/2.0)
         dLargeTickSize*=-1.0;
      if (TC.angle==0) {
         //TC.align=0;
         TC.alignment&=~(GE_AlignLeft|GE_AlignHCenter|GE_AlignRight);
         if (pData->dAxisRef<(x1+x2)/2.0) TC.alignment|=GE_AlignRight;
         else                           TC.alignment|=GE_AlignLeft;
      }
      memcpy((char*)&pData->TC,(char*)&TC,sizeof(FONTATTR));
      pData->dLargeTickSize=dLargeTickSize;
      pData->pFormat=pFormat;
      pData->pEquation=pEquation;
      pData->pProc=OnAxisYLabel;
      DoAxisProcess(nScale,pData);
   }
   
   if (pAxis->pTitle && pAxis->bTitleShow) {
      /* 2003.11.1 */
      double x1,y1,x2,y2,x,y;
      x1=CPX->norwin.x1;
      y1=CPX->norwin.y1;
      x2=CPX->norwin.x2;
      y2=CPX->norwin.y2;
      x=GetTextYPitchOfNorWin(&(pAxis->TitleFontAttr));
      x=x1-x*pAxis->dTitleSpaceFactor;
      y=y1+(y2-y1)/2.0;
      x=GetXPosOfWldWin(pPlot,x);
      y=GetYPosOfWldWin(pPlot,y);
      pAxis->TitleFontAttr.alignment=GE_AlignHCenter|GE_AlignTop;
      pAxis->TitleFontAttr.angle=90;
      DBTextAttr(&pAxis->TitleFontAttr,&CPX->attr);
      DBText((*pPlot->pXfrm->xCnvFn)(x),(*pPlot->pXfrm->yCnvFn)(y),
         pAxis->pTitle);
      /*
      double y1,y2,w,x,y;
      pAxis->TitleFontAttr.alignment=GE_AlignHCenter|GE_AlignTop;
      pAxis->TitleFontAttr.angle=90;
      DBTextAttr(&pAxis->TitleFontAttr,&CPX->attr);
      y1=pData->dAxisStart;
      y2=pData->dAxisEnd;
      w=ABS(y2-y1);
      y=(y2>y1) ? y1+w/2.0 : y2+w/2.0;
      x=pData->dAxisRef+dLargeTickSize*pAxis->dTitleSpaceFactor;
      DBText(x,y,pAxis->pTitle);
      */
   }

   free(pData);
   return TRUE;
}

static
int OnAxisYLabel( nProcMode,pData,y )
   AXISPROCMODE nProcMode;
   AXISLABELDATA *pData;
   double y;
{
   const char *qAddr;
   double dResult;

   switch (nProcMode) {
   case AXISPROC_START :
      DBTextAttr(&pData->TC,&CPX->attr);
      break;
   case AXISPROC_LARGETICK :
      dResult=(*CPX->yInvFn)(y);
      dResult=GetLabelValueFromEquation(pData->pEquation,dResult);
      qAddr=dtos(dResult,pData->pFormat);
      DBText(pData->dAxisRef+pData->dLargeTickSize,y,qAddr);
      break;
   case AXISPROC_SMALLTICK :
      return TRUE;
   case AXISPROC_END :
      return TRUE;
   }
   return TRUE;
}

static
int AxisYGrid(
   int bMajorGridOn,int bMinorGridOn,
   double yStart,double yEnd,double dRef1,double dRef2,
   BLOBGC MajorGC,BLOBGC MinorGC,
   double dMajorStep,double dMinorStep,
   int nScale
)
{
   AXISGRIDDATA *pData;

   if (bMinorGridOn) {
      pData=salloc(AXISGRIDDATA,1);
      pData->dAxisStart=(*CPX->yCnvFn)(yStart);
      pData->dAxisEnd=  (*CPX->yCnvFn)(yEnd);
      pData->dMinorStep= (*CPX->yCnvFn)(dMinorStep);
      pData->dMajorStep= (*CPX->yCnvFn)(dMajorStep);
      pData->dAxisRef1= (*CPX->xCnvFn)(dRef1);
      pData->dAxisRef2= (*CPX->xCnvFn)(dRef2);
      memcpy((char*)&pData->GC,(char*)&MinorGC,sizeof(BLOBGC));
      pData->GC.dash_list[0]=1;
      pData->GC.dash_list[1]=4;
      pData->GC.dash_offset=0;
      pData->GC.dashes=2;
      pData->nAttr=AXISPROC_SMALLTICK;
      pData->pProc=OnAxisYGrid;
      DoAxisProcess(nScale,pData);
      free(pData);
   }
   if (bMajorGridOn) {
      pData=salloc(AXISGRIDDATA,1);
      pData->dAxisStart=(*CPX->yCnvFn)(yStart);
      pData->dAxisEnd=  (*CPX->yCnvFn)(yEnd);
      pData->dMinorStep= (*CPX->yCnvFn)(dMinorStep);
      pData->dMajorStep= (*CPX->yCnvFn)(dMajorStep);
      pData->dAxisRef1= (*CPX->xCnvFn)(dRef1);
      pData->dAxisRef2= (*CPX->xCnvFn)(dRef2);
      memcpy((char*)&pData->GC,(char*)&MajorGC,sizeof(BLOBGC));
      pData->GC.dash_list[0]=1;
      pData->GC.dash_list[1]=4;
      pData->GC.dash_offset=0;
      pData->GC.dashes=2;
      pData->nAttr=AXISPROC_LARGETICK;
      pData->pProc=OnAxisYGrid;
      DoAxisProcess(nScale,pData);
      free(pData);
   }
   return TRUE;
}

static
int OnAxisYGrid( nProcMode,pData,yRef )
   AXISPROCMODE nProcMode;
   AXISGRIDDATA *pData;
   double yRef;
{
   if ((nProcMode!=AXISPROC_START)
   &&  (pData->dAxisStart==yRef || pData->dAxisEnd==yRef)) return TRUE;
   switch (nProcMode) {
   case AXISPROC_START :
      DBGC(pData->GC);
      break;
   case AXISPROC_LARGETICK :
      if (pData->nAttr==AXISPROC_SMALLTICK) break;
      DBLine(pData->dAxisRef1,yRef,pData->dAxisRef2,yRef);
      break;
   case AXISPROC_SMALLTICK :
      if (pData->nAttr==AXISPROC_LARGETICK) break;
      DBLine(pData->dAxisRef1,yRef,pData->dAxisRef2,yRef);
      break;
   case AXISPROC_END :
      return TRUE;
   }
   return TRUE;
}

static
double GetLabelValueFromEquation( qProgram,dResult )
   const char *qProgram;
   double dResult;
{
   char qExpr[80],*pToken;

   if (!qProgram) return dResult;

   sprintf(qExpr,"z=%e",dResult);
   mathparser(qExpr,&dResult);
   sprintf(qExpr,"%s",qProgram);
   pToken=strtok(qExpr,"\";");
   do {
      setjmp(jb_parser);
      mathparser(pToken,&dResult);
      pToken=strtok(NULL,";");
   } while (pToken);
   return dResult;
}

static
int DoLegend( pPlot )
   PLTNODE *pPlot;
{
   int nTotal,nIndex;
   double x,y,dFactor;

   PLTClipWindow.x1=
   PLTClipWindow.y1=
   PLTClipWindow.x2=
   PLTClipWindow.y2=(double)(0.0);

   nTotal=min(pPlot->pSlct->nLegendTotal,pPlot->pSlct->yNoTotal);
   for (nIndex=0;nIndex<nTotal;nIndex++) { 

      if (!pPlot->pSlct->pLegend[nIndex].bLegendOn) continue;
      if (!pPlot->pSlct->pLegend[nIndex].pText) continue;

      DBPrint(pPlot->pSlct->pLegend[nIndex].nPen);

      y=(*CPX->yCnvFn)(pPlot->pSlct->pLegend[nIndex].y);
      x=(*CPX->xCnvFn)(pPlot->pSlct->pLegend[nIndex].x);
      dFactor=pPlot->pSlct->pLegend[nIndex].dLegendSize/CPX->attr.xScale
         *SYMBOL_SCALE_FACTOR;
      if (pPlot->pSlct->pLegend[nIndex].bLineOn) {
         LgndGCLineAttr(nIndex).gc_type=GE_GCLine;
         LgndGCLineAttr(nIndex).gc_mask=GE_GCMaskLineDefault;
         DBGC(LgndGCLineAttr(nIndex));
         DBLine(x-dFactor,y,x+dFactor,y);
      }

      if (pPlot->pSlct->pLegend[nIndex].bSymbolOn) { /* 20030227 */
         switch (pPlot->pSlct->pLegend[nIndex].nType) {
         case MOMENT_BOX_SYMBOL_TYPE : //
            LgndGCSymbAttr(nIndex).gc_type=GE_GCPolygonL;
            LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskLineDefault;
            DBGC(LgndGCSymbAttr(nIndex));
            LgndGCSymbAttr(nIndex).gc_type=GE_GCPolygon;
            LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskFillDefault;
            DBGC(LgndGCSymbAttr(nIndex));
            DrawDataSymbolPoly(pPlot->pSlct->pLegend[nIndex].x,
               pPlot->pSlct->pLegend[nIndex].y,
               pPlot->pSlct->pLegend[nIndex].dLegendSize,
               STROKESYMB_INDEX_OF_SQUARE);
            break;
         /*
         case 1 :
            LgndGCSymbAttr(nIndex).gc_type=GE_GCArcLine;
            LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskLineDefault;
            DBGC(LgndGCSymbAttr(nIndex));
            LgndGCSymbAttr(nIndex).gc_type=GE_GCArcFill;
            LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskFillDefault;
            DBGC(LgndGCSymbAttr(nIndex));
            DrawDataSymbolCircle(pPlot->pSlct->pLegend[nIndex].x,
            pPlot->pSlct->pLegend[nIndex].y,
            pPlot->pSlct->pLegend[nIndex].dLegendSize);
            break;
         */
         default:
            LgndGCSymbAttr(nIndex).gc_type=GE_GCPolygonL;
            LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskLineDefault;
            DBGC(LgndGCSymbAttr(nIndex));
            LgndGCSymbAttr(nIndex).gc_type=GE_GCPolygon;
            LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskFillDefault;
            DBGC(LgndGCSymbAttr(nIndex));
            DrawDataSymbolPoly(pPlot->pSlct->pLegend[nIndex].x,
               pPlot->pSlct->pLegend[nIndex].y,
               pPlot->pSlct->pLegend[nIndex].dLegendSize,
               pPlot->pSlct->pLegend[nIndex].nType);
            break;
         }
      }

      DBTextAttr(&LgndFontAttr(nIndex),&CPX->attr);
      x+=dFactor*1.4;
      DBText(x,y,pPlot->pSlct->pLegend[nIndex].pText);
   }
   return TRUE;
}


static
long GetColorValueFromZValue( nColorMin,nColorMax,nTotal,zLowB,zUppB,zValue )
   long nColorMin,nColorMax;
   int nTotal;
   double zLowB,zUppB,zValue;
{
   unsigned short nRedMin,nGreenMin,nBlueMin,
                  nRedMax,nGreenMax,nBlueMax,
                  nRed,nGreen,nBlue;
   double zPitch;
   int nIndex; // 0..nTotal

   //GEColorName(0,nColorMin);
   //GEColorName(0,nColorMax);
   if (zValue<=zLowB) {
      nIndex=0;
   } else if (zValue>=zUppB) {
      nIndex=nTotal;
   } else {
      zPitch=(zUppB-zLowB)/nTotal;
      nIndex=(int)((zValue-zLowB)/zPitch);
   }

   GEColor2RGB(NULL,
      (unsigned long)nColorMin,
      &nRedMin,&nGreenMin,&nBlueMin,0);
   GEColor2RGB(NULL,
      (unsigned long)nColorMax,
      &nRedMax,&nGreenMax,&nBlueMax,0);
   nRed=nIndex*(nRedMax-nRedMin)/nTotal+nRedMin;
   nGreen=nIndex*(nGreenMax-nGreenMin)/nTotal+nGreenMin;
   nBlue=nIndex*(nBlueMax-nBlueMin)/nTotal+nBlueMin;

   return GEColorByRGB(NULL,nRed,nGreen,nBlue);
}

static
int DoLegendFlat3D( pPlot )
   PLTNODE *pPlot;
{
   double dSize,dW,dH,x1,y1,x2,y2,z1,z2,zValue;
   int nIndex;
   BLOBPOINT p[5];
   BLOBGC gc;
   const char *qAddr;

   if (!pPlot->pSlct->Etc.Flat3D.nColorTotal) return FALSE;

   DBPrint(pPlot->pSlct->pLegend[0].nPen);
      
   LgndGCSymbAttr(0).gc_type=GE_GCPolygonL;
   LgndGCSymbAttr(0).gc_mask=GE_GCMaskLineDefault;
   DBGC(LgndGCSymbAttr(0));
   LgndGCSymbAttr(0).gc_type=GE_GCPolygon;
   LgndGCSymbAttr(0).gc_mask=GE_GCMaskFillDefault;
   DBGC(LgndGCSymbAttr(0));
   memcpy((char*)&gc,(char*)&LgndGCSymbAttr(0),sizeof(BLOBGC));

   dSize=pPlot->pSlct->pLegend[0].dLegendSize;
   dW=dSize/CPX->attr.xScale*SYMBOL_SCALE_FACTOR;
   dH=dSize/CPX->attr.yScale*SYMBOL_SCALE_FACTOR*0.5;
   x1=(*CPX->xCnvFn)(pPlot->pSlct->xlowb)-dW*0.5;
   x2=(*CPX->xCnvFn)(pPlot->pSlct->xuppb);
   y1=(*CPX->yCnvFn)(pPlot->pSlct->ylowb);
   y2=(*CPX->yCnvFn)(pPlot->pSlct->yuppb);
   z1=(*CPX->zCnvFn)(pPlot->pSlct->zlowb);
   z2=(*CPX->zCnvFn)(pPlot->pSlct->zuppb);
   if ((y2-y1)<dH*pPlot->pSlct->Etc.Flat3D.nColorTotal) {
      dH=(y2-y1)/pPlot->pSlct->Etc.Flat3D.nColorTotal;
   }

   LgndGCLineAttr(0).gc_type=GE_GCPolygonL;
   LgndGCLineAttr(0).gc_mask=GE_GCMaskLineDefault;
   DBGC(LgndGCLineAttr(0));
   for (nIndex=0;nIndex<pPlot->pSlct->Etc.Flat3D.nColorTotal;nIndex++) {
      p[0].x=x1-dW; p[0].y=y1+dH*nIndex;
      p[1].x=x1;    p[1].y=p[0].y;
      p[2].x=p[1].x;p[2].y=p[0].y+dH;
      p[3].x=p[0].x;p[3].y=p[2].y;
      p[4].x=p[0].x;p[4].y=p[0].y;
      DBPolyline(p,5);
   }

   LgndGCSymbAttr(0).gc_type=GE_GCPolygon;
   LgndGCSymbAttr(0).gc_mask=GE_GCMaskFillDefault;
   memcpy((char*)&gc,(char*)&LgndGCSymbAttr(0),sizeof(BLOBGC));
   for (nIndex=0;nIndex<pPlot->pSlct->Etc.Flat3D.nColorTotal;nIndex++) {
      zValue=(z2-z1)/pPlot->pSlct->Etc.Flat3D.nColorTotal*nIndex+z1;
      gc.foreground=GetColorValueFromZValue(
         pPlot->pSlct->Etc.Flat3D.nColorMin,
         pPlot->pSlct->Etc.Flat3D.nColorMax,
         pPlot->pSlct->Etc.Flat3D.nColorTotal,
         z1,z2,zValue
         );
      DBGC(gc);
      p[0].x=x1-dW; p[0].y=y1+dH*nIndex;
      p[1].x=x1;    p[1].y=p[0].y;
      p[2].x=p[1].x;p[2].y=p[0].y+dH;
      p[3].x=p[0].x;p[3].y=p[2].y;
      p[4].x=p[0].x;p[4].y=p[0].y;
      DBPolyline(p,5);
   }
   LgndFontAttr(0).alignment=GE_AlignVCenter|GE_AlignHCenter;
   DBTextAttr(&LgndFontAttr(0),&CPX->attr);
   qAddr=dtos(pPlot->pSlct->zlowb,pPlot->pSlct->Etc.Flat3D.qFormat);
   DBText(x1-dW/2,y1-dH,qAddr);
   qAddr=dtos(pPlot->pSlct->zuppb,pPlot->pSlct->Etc.Flat3D.qFormat);
   DBText(x1-dW/2,y1+dH*(pPlot->pSlct->Etc.Flat3D.nColorTotal+1),qAddr);
   return TRUE;
}

static
int DoData( pPlot )
   PLTNODE *pPlot;
{
   int i,j,xIndex,yIndex;
   double x1,y1,x2,y2;

   PLTClipWindow.x1=(double)(pPlot->pSlct->xlowb);
   PLTClipWindow.y1=(double)(pPlot->pSlct->ylowb);
   PLTClipWindow.x2=(double)(pPlot->pSlct->xuppb);
   PLTClipWindow.y2=(double)(pPlot->pSlct->yuppb);

   for (i=0;i<pPlot->pSlct->yNoTotal;i++) {
      xIndex=pPlot->pSlct->xNo[i];
      yIndex=pPlot->pSlct->yNo[i];
      if (IsMinOrMaxInt(xIndex) || IsMinOrMaxInt(yIndex)) continue;
      xIndex=ABS(xIndex);
      yIndex=ABS(yIndex);
      DBPrint(pPlot->pSlct->pLegend[i].nPen);

      if (pPlot->pSlct->pLegend[i].bLineOn) {
         BLOBGC GC; //20030310
         memcpy((char*)&GC,(char*)&LgndGCLineAttr(i),sizeof(BLOBGC));
         GC.gc_type=GE_GCLine;
         GC.gc_mask=GE_GCMaskLineDefault;
         DBGC(GC);
         /* LgndGCSymbAttr(i).gc_type=GE_GCLine;
         LgndGCSymbAttr(i).gc_mask=GE_GCMaskLineDefault;
         DBGC(LgndGCLineAttr(i));
         DBGC(LgndGCLineAttr(i));*/
         if (pPlot->pSlct->pLegend[i].bSymbolOn) { /* <- 20030304 */
            for (MkNaNDouble(x1),MkNaNDouble(y1),j=pPlot->pData->nrl;
            j<=pPlot->pData->nrh;
            j++) {
               if (IsNaNDouble(x1)||IsNaNDouble(y1)) {
                  x1=pPlot->pData->mtx[j][xIndex];
                  y1=pPlot->pData->mtx[j][yIndex];
                  continue;
               }
               x2=pPlot->pData->mtx[j][xIndex];
               y2=pPlot->pData->mtx[j][yIndex];
               if (IsNaNDouble(x2)||IsNaNDouble(y2)) continue;
               DrawDataSymbolLine(x1,y1,x2,y2);
               x1=x2;
               y1=y2;
            }
         } else { /* 20030303 */
            BLOBPOINT *vPoint;
            int nCount;
            nCount=pPlot->pData->nrh-pPlot->pData->nrl+1;
            vPoint=salloc(BLOBPOINT,nCount);
            for (j=pPlot->pData->nrl,nCount=0;j<=pPlot->pData->nrh;j++) {
               x1=pPlot->pData->mtx[j][xIndex];
               y1=pPlot->pData->mtx[j][yIndex];
               if (IsNaNDouble(x1)||IsNaNDouble(y1)) continue;
               vPoint[nCount].x=x1;
               vPoint[nCount].y=y1;
               nCount++;
            }
            DrawDataSymbolLineEx(vPoint,nCount);
            free(vPoint);
         }
      }

      if (!pPlot->pSlct->pLegend[i].bSymbolOn) continue; /* 20030225 */
/*
      if (pPlot->pSlct->pLegend[i].nType==1) {
         LgndGCSymbAttr(i).gc_type=GE_GCPolygonL;
         LgndGCSymbAttr(i).gc_mask=GE_GCMaskLineDefault;
         DBGC(LgndGCSymbAttr(i));
         LgndGCSymbAttr(i).gc_type=GE_GCPolygon;
         LgndGCSymbAttr(i).gc_mask=GE_GCMaskFillDefault;
         DBGC(LgndGCSymbAttr(i));
         for (j=pPlot->pSlct->nrl;j<=pPlot->pSlct->nrh;j++) {
            x1=pPlot->pData->mtx[j][xIndex];
            y1=pPlot->pData->mtx[j][yIndex];
            if (IsNaNDouble(x1)
            ||  IsNaNDouble(y1))
               continue;
            DrawDataSymbolCircle(x1,y1,pPlot->pSlct->lgnd[i].dSymbSize);
         }
      }
      else if (pPlot->pSlct->pLegend[i].nType) {
*/
         LgndGCSymbAttr(i).gc_type=GE_GCPolygonL;
         LgndGCSymbAttr(i).gc_mask=GE_GCMaskLineDefault;
         DBGC(LgndGCSymbAttr(i));
         LgndGCSymbAttr(i).gc_type=GE_GCPolygon;
         LgndGCSymbAttr(i).gc_mask=GE_GCMaskFillDefault;
         DBGC(LgndGCSymbAttr(i));
         for (j=pPlot->pData->nrl;j<=pPlot->pData->nrh;j++) {
            x1=pPlot->pData->mtx[j][xIndex];
            y1=pPlot->pData->mtx[j][yIndex];
            if (IsNaNDouble(x1)||IsNaNDouble(y1)) continue;
            DrawDataSymbolPoly(x1,y1,
               pPlot->pSlct->pLegend[i].dSymbSize,
               pPlot->pSlct->pLegend[i].nType);
         }
/*
      }
*/
   }
   return TRUE;
}

static
int DoDataPlus( pPlot )
   PLTNODE *pPlot;
{
   extern int GetBoxSymbolData _((
           double*,int,double,double*,double*,double*,double*,double*,double*));
   double *dVec,dMinv,dLow5,dMed,dUpp5,dMaxv,dSigma;
   int i,j,k,xIndex,yIndex,bSign,yCount,nStart,nEnd,nLast;
   double x1,y1,x2,y2;

   PLTClipWindow.x1=(double)(pPlot->pSlct->xlowb);
   PLTClipWindow.y1=(double)(pPlot->pSlct->ylowb);
   PLTClipWindow.x2=(double)(pPlot->pSlct->xuppb);
   PLTClipWindow.y2=(double)(pPlot->pSlct->yuppb);

   for (i=0;i<pPlot->pSlct->yNoTotal;i++) {
      xIndex=pPlot->pSlct->xNo[i];
      yIndex=pPlot->pSlct->yNo[i];
      if (IsMinOrMaxInt(xIndex) || IsMinOrMaxInt(yIndex)) continue;
      xIndex=ABS(xIndex);
      yIndex=ABS(yIndex);
      DBPrint(pPlot->pSlct->pLegend[i].nPen);
      LgndGCSymbAttr(i).gc_type=GE_GCPolygonL;
      LgndGCSymbAttr(i).gc_mask=GE_GCMaskLineDefault;
      DBGC(LgndGCSymbAttr(i));
      LgndGCSymbAttr(i).gc_type=GE_GCPolygon;
      LgndGCSymbAttr(i).gc_mask=GE_GCMaskFillDefault;
      DBGC(LgndGCSymbAttr(i));
      for (j=pPlot->pData->nrl;j<=pPlot->pData->nrh;j++) {
           x1=pPlot->pData->mtx[j][xIndex];
           y1=pPlot->pData->mtx[j][yIndex];
         if (IsNaNDouble(x1) || IsNaNDouble(y1))
            continue;
         DrawDataSymbolPoly(x1,y1,
            pPlot->pSlct->pLegend[i].dSymbSize,
            pPlot->pSlct->pLegend[i].nType);
      }
   }

   dVec=dvector(1,pPlot->pSlct->yNoTotal);
   for (i=0;i<pPlot->pSlct->yNoTotal;i++) {
      nStart=nEnd=i;
      for (nStart=i;nStart<pPlot->pSlct->yNoTotal;nStart++) {
         xIndex=pPlot->pSlct->xNo[nStart];
         yIndex=pPlot->pSlct->yNo[nStart];
         if (!IsMinOrMaxInt(xIndex) && !IsMinOrMaxInt(yIndex)) break;
      }
      bSign=pPlot->pSlct->yNo[nStart]>0 ? 1:-1;
      for (nEnd=nStart;nEnd<pPlot->pSlct->yNoTotal;nEnd++) {
         if (IsMinOrMaxInt(xIndex) || IsMinOrMaxInt(yIndex)) continue;
         yIndex=pPlot->pSlct->yNo[nEnd]>0 ? 1:-1;
         if (bSign*yIndex<0) {
            nEnd--;
            break;
         }
      }
      if (nEnd>=pPlot->pSlct->yNoTotal) nEnd=pPlot->pSlct->yNoTotal-1;
      i=nEnd;
      if (nStart==nEnd) {
         xIndex=pPlot->pSlct->xNo[nStart];
         yIndex=pPlot->pSlct->yNo[nStart];
         if (IsMinOrMaxInt(xIndex) || IsMinOrMaxInt(yIndex)) continue;
      }
      DBPrint(pPlot->pSlct->pLegend[nStart].nPen);
      LgndGCSymbAttr(nStart).gc_type=GE_GCLine;
      LgndGCSymbAttr(nStart).gc_mask=GE_GCMaskLineDefault;
      DBGC(LgndGCLineAttr(nStart));
      for (j=pPlot->pData->nrl;j<=pPlot->pData->nrh;j++) {
         if (nStart<nEnd) {
            yCount=0;
            for (k=nStart;k<=nEnd;k++) {
               xIndex=pPlot->pSlct->xNo[k];
               yIndex=pPlot->pSlct->yNo[k];
               if (IsMinOrMaxInt(xIndex) || IsMinOrMaxInt(yIndex)) continue;
               yIndex=ABS(yIndex);
               if (IsNaNDouble(pPlot->pData->mtx[j][yIndex])) continue;
               nLast=k;
               dVec[yCount+1]=pPlot->pData->mtx[j][yIndex];
               yCount++;
            }
            if (!yCount) {
               continue;
            } else if (yCount==1) {
               dMed=pPlot->pData->mtx[j][nLast];
            } else {
               GetBoxSymbolData(
                  dVec,yCount,100.0,&dMinv,&dLow5,&dMed,&dUpp5,&dMaxv,&dSigma);
            }
            xIndex=pPlot->pSlct->xNo[nLast];
            yIndex=ABS(pPlot->pSlct->yNo[nStart]);
            if (IsMinOrMaxInt(xIndex) || IsMinOrMaxInt(yIndex)) continue;
            x2=pPlot->pData->mtx[j][xIndex];
            y2=dMed;
         } else { /* nStart==nEnd */
            xIndex=pPlot->pSlct->xNo[nStart];
            yIndex=ABS(pPlot->pSlct->yNo[nStart]);
            if (IsMinOrMaxInt(xIndex) || IsMinOrMaxInt(yIndex)) continue;
            x2=pPlot->pData->mtx[j][xIndex];
            y2=pPlot->pData->mtx[j][yIndex];
         }
         if (j==pPlot->pData->nrl) {
            x1=x2;
            y1=y2;
            continue;
         }
         if (IsNaNDouble(x1) || IsNaNDouble(y1) ||
             IsNaNDouble(x2) || IsNaNDouble(y2))
            continue;
         DrawDataSymbolLine(x1,y1,x2,y2);
         x1=x2;
         y1=y2;
      }
   }
   free_dvector(dVec,1,pPlot->pSlct->yNoTotal);
   return TRUE;
}

static
int DrawDataSymbolLine( x1,y1,x2,y2 )
   double x1,y1,x2,y2;
{
   if (!clipper_line(PLTClipWindow.x1,PLTClipWindow.x2,
                     PLTClipWindow.y1,PLTClipWindow.y2,
                     &x1,&y1,&x2,&y2)) return 0;
   x1=(*CPX->xCnvFn)(x1);
   y1=(*CPX->yCnvFn)(y1);
   x2=(*CPX->xCnvFn)(x2);
   y2=(*CPX->yCnvFn)(y2);
   DBLine(x1,y1,x2,y2);
   return 1;
}

/* 20030303 */
static
int DrawDataSymbolLineEx( pPoints,nTotal )
   BLOBPOINT *pPoints;
   int nTotal;
{
   BLOBLINE *pLines;
   int j,k,bResult,nCount;
   double x1,y1,x2,y2;

   pLines=salloc(BLOBLINE,nTotal);

   nCount=0;
   for (j=0;j<(nTotal-1);j++) {
      x1=pPoints[j].x;
      y1=pPoints[j].y;
      x2=pPoints[j+1].x;
      y2=pPoints[j+1].y;
      bResult=clipper_line(
         PLTClipWindow.x1,PLTClipWindow.x2,PLTClipWindow.y1,PLTClipWindow.y2,
         &x1,&y1,&x2,&y2);
      if (!bResult) { /* 20030307 */
         nCount=0;
         continue;
      }
      pPoints[nCount].x=(*CPX->xCnvFn)(x1);
      pPoints[nCount++].y=(*CPX->yCnvFn)(y1);
      if (bResult==(TRUE+1) /* clipped */ &&
         (x1==pPoints[j].x||y1==pPoints[j].y) && /* 20030307 */
         (x2!=pPoints[j+1].x||y2!=pPoints[j+1].y)) {
         pPoints[nCount].x=(*CPX->xCnvFn)(x2);
         pPoints[nCount].y=(*CPX->yCnvFn)(y2); /* 20030904 */
         for (k=0;k<(nCount-1);k++) {
            pLines[k].x1=pPoints[k].x;
            pLines[k].y1=pPoints[k].y;
            pLines[k].x2=pPoints[k+1].x;
            pLines[k].y2=pPoints[k+1].y;
         }
         DBLines(pLines,nCount);
         nCount=0;
      }
   }
   if (nCount) { /* 20030904 */
      pPoints[nCount].x=(*CPX->xCnvFn)(x2); /* 20030403 */
      pPoints[nCount].y=(*CPX->yCnvFn)(y2); /* 20030403+0410 */
      for (k=0;k<nCount;k++) {              /* 20030410 */
         pLines[k].x1=pPoints[k].x;
         pLines[k].y1=pPoints[k].y;
         pLines[k].x2=pPoints[k+1].x;
         pLines[k].y2=pPoints[k+1].y;
      }
      DBLines(pLines,nCount);
   }

   free(pLines);
   return 1;
}

static 
int DrawDataSymbolPoly( x,y,dSize,nCode )
   double x,y,dSize;
   int nCode;
{
   double x_factor,y_factor;
   int xPoints[STROKESYMB_DATA_UNIT],yPoints[STROKESYMB_DATA_UNIT];
   double xx,yy;
   unsigned int i,nTotal;
   BLOBPOINT p[STROKESYMB_DATA_UNIT];

   if (!isPointInWldWindow(&PLTClipWindow,x,y))
      return 0;
   x=(*CPX->xCnvFn)(x);
   y=(*CPX->yCnvFn)(y);
   dSize*=SYMBOL_SCALE_FACTOR;
   x_factor=dSize/CPX->attr.xScale;
   y_factor=dSize/CPX->attr.yScale;
   nTotal=GetStrokeSymbolPoints(nCode,xPoints,yPoints,STROKESYMB_DATA_UNIT);
   for (i=0;i<nTotal;i++) {
    //  xx=(double)(xPoints[i]-500)/1000; /* center-alignment */
    //  yy=(double)(yPoints[i]-500)/1000; /* center-alignment */
      xx=(double)(xPoints[i]-450)/1000; /* center-alignment */
      yy=(double)(yPoints[i]-450)/1000; /* center-alignment */
      // 450 ??? 20030223
      p[i].x=xx*x_factor+x;
      p[i].y=y-yy*y_factor;
   }
   DBPolyline(p,nTotal);
   return 1;
}

static
int DrawDataSymbolCircle( x,y,dSize )
   double x,y,dSize;
{
   double xSize,ySize;

   if (!isPointInWldWindow(&PLTClipWindow,x,y))
      return 0;
   x=(*CPX->xCnvFn)(x);
   y=(*CPX->yCnvFn)(y);
   dSize*=SYMBOL_SCALE_FACTOR;
   xSize=dSize/CPX->attr.xScale;
   ySize=dSize/CPX->attr.yScale;
   DBArc(x,y,xSize,ySize,0.0,RADIAN(360));
   return 1;
}

static
int DrawDataSymbolMoment( nCode,dSize,dX,dMinv,dLow5,dMedv,dUpp5,dMaxv )
   int nCode;
   double dSize,dX;
   double dMinv,dLow5,dMedv,dUpp5,dMaxv;
{
   double boxx,boxl,boxh,size04,size05,medv;
   BLOBLINE p[8];

   if (!isPointInWldWindow(&PLTClipWindow,dX,dMedv)) return FALSE;
   
   boxx=(*CPX->xCnvFn)(dX);
   boxl=(*CPX->yCnvFn)(dLow5);
   boxh=(*CPX->yCnvFn)(dUpp5);
   medv=(*CPX->yCnvFn)(dMedv);
   dMinv=(*CPX->yCnvFn)(dMinv);
   dMaxv=(*CPX->yCnvFn)(dMaxv);
   size05=dSize*SYMBOL_SCALE_FACTOR/CPX->attr.xScale*0.5;
   size04=size05*0.8;

   if (nCode!=MOMENT_BOX_SYMBOL_TYPE) {
      /* DrawDataSymbolCircle(dX,mom->dMed,dSize); */
      DrawDataSymbolPoly(dX,dMedv,dSize,nCode);
      p[0].x1=boxx-size04;p[0].x2=boxx+size04;
      p[0].y1=p[0].y2=dMaxv;                        
      p[1].x1=boxx-size04;p[1].x2=boxx+size04;
      p[1].y1=p[1].y2=dMinv;                        
      p[2].x1=p[2].x2=boxx;
      p[2].y1=dMaxv;p[2].y2=dMinv;                        
      DBLines(p,3);
   } else {
      p[0].x1=boxx-size04;p[0].x2=boxx+size04;
      p[0].y1=p[0].y2=dMaxv;                        
      p[1].x1=boxx-size04;p[1].x2=boxx+size04;
      p[1].y1=p[1].y2=dMinv;                        
      p[2].x1=p[2].x2=boxx;
      p[2].y1=dMaxv;p[2].y2=dMinv;                        
      p[3].x1=boxx-size05;p[3].x2=boxx+size05;
      p[3].y1=p[3].y2=medv;                        
      p[4].x1=p[4].x2=boxx-size04;
      p[4].y1=boxl;p[4].y2=boxh;                        
      p[5].x1=boxx-size04;p[5].x2=boxx+size04;
      p[5].y1=p[5].y2=boxh;                        
      p[6].x1=p[6].x2=boxx+size04;
      p[6].y1=boxh;p[6].y2=boxl;                        
      p[7].x1=boxx+size04;p[7].x2=boxx-size04;
      p[7].y1=p[7].y2=boxl;                        
      DBLines(p,8);
   }
   return 1;
}

static
int DoDataMoment( pPlot )
   PLTNODE *pPlot;
{
   double x1,y1,x2,y2,dMinv,dLow5,median,dUpp5,dMaxv,dNoiseRef,dNoise;
   int nIndex,xIndex,yIndex,j;

   PLTClipWindow.x1=(double)(pPlot->pSlct->xlowb);
   PLTClipWindow.y1=(double)(pPlot->pSlct->ylowb);
   PLTClipWindow.x2=(double)(pPlot->pSlct->xuppb);
   PLTClipWindow.y2=(double)(pPlot->pSlct->yuppb);

   dNoiseRef=(pPlot->pSlct->xuppb-pPlot->pSlct->xlowb)*MOMENT_X_NOISE_FACTOR;

   for (nIndex=0;nIndex<pPlot->pSlct->yNoTotal;nIndex++) {
      xIndex=pPlot->pSlct->xNo[nIndex];
      yIndex=pPlot->pSlct->yNo[nIndex];
      if (IsMinOrMaxInt(xIndex) || IsMinOrMaxInt(yIndex)) continue;
      xIndex=ABS(xIndex);
      yIndex=ABS(yIndex);
      DBPrint(pPlot->pSlct->pLegend[nIndex].nPen);

      dNoise=-nIndex*dNoiseRef;
      
      if (pPlot->pSlct->pLegend[nIndex].bLineOn) {
         LgndGCLineAttr(nIndex).gc_type=GE_GCLine;
         LgndGCLineAttr(nIndex).gc_mask=GE_GCMaskLineDefault;
         DBGC(LgndGCLineAttr(nIndex));
         MkNaNDouble(x1);
         MkNaNDouble(y1);
         for (j=pPlot->pData->nrl;j<=pPlot->pData->nrh;j++) {
            if (IsNaNDouble(x1)
            ||  IsNaNDouble(y1)) {
               x1=pPlot->pData->mtx[j][xIndex];
               y1=pPlot->pData->mtx[j][yIndex+MTX_OFFSET_TO_MEDIAN];
               continue;
            }
            x2=pPlot->pData->mtx[j][xIndex];
            y2=pPlot->pData->mtx[j][yIndex+MTX_OFFSET_TO_MEDIAN];
            if (IsNaNDouble(x2)
            ||  IsNaNDouble(y2))
               continue;
            DrawDataSymbolLine(x1+dNoise,y1,x2+dNoise,y2);
            x1=x2;
            y1=y2;
         }
      }

      if (!pPlot->pSlct->pLegend[nIndex].bSymbolOn) continue; /* 20030225 */

      LgndGCLineAttr(nIndex).gc_type=GE_GCLine;
      LgndGCLineAttr(nIndex).gc_mask=GE_GCMaskLineDefault;
      LgndGCLineAttr(nIndex).line_style=GE_LineSolid;
      DBGC(LgndGCLineAttr(nIndex));
      switch (pPlot->pSlct->pLegend[nIndex].nType) {
      case MOMENT_BOX_SYMBOL_TYPE :
         LgndGCSymbAttr(nIndex).gc_type=GE_GCPolygonL;
         LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskLineDefault;
         DBGC(LgndGCSymbAttr(nIndex));
         LgndGCSymbAttr(nIndex).gc_type=GE_GCPolygon;
         LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskFillDefault;
         DBGC(LgndGCSymbAttr(nIndex));
         break;
      default:
         LgndGCSymbAttr(nIndex).gc_type=GE_GCPolygonL;
         LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskLineDefault;
         DBGC(LgndGCSymbAttr(nIndex));
         LgndGCSymbAttr(nIndex).gc_type=GE_GCPolygon;
         LgndGCSymbAttr(nIndex).gc_mask=GE_GCMaskFillDefault;
         DBGC(LgndGCSymbAttr(nIndex));
         break;
      }
      for (j=pPlot->pData->nrl;j<=pPlot->pData->nrh;j++) {
         x1=pPlot->pData->mtx[j][xIndex];
         y1=pPlot->pData->mtx[j][yIndex+MTX_OFFSET_TO_MEDIAN];
         if (IsNaNDouble(x1)
         ||  IsNaNDouble(y1))
             continue;
         dMinv=pPlot->pData->mtx[j][yIndex+ MTX_OFFSET_TO_MINV];
         dLow5=pPlot->pData->mtx[j][yIndex+ MTX_OFFSET_TO_LOW5];
         median=pPlot->pData->mtx[j][yIndex+MTX_OFFSET_TO_MEDIAN];
         dUpp5=pPlot->pData->mtx[j][yIndex+ MTX_OFFSET_TO_UPP5];
         dMaxv=pPlot->pData->mtx[j][yIndex+ MTX_OFFSET_TO_MAXV];
         DrawDataSymbolMoment(
            pPlot->pSlct->pLegend[nIndex].nType,
            pPlot->pSlct->pLegend[nIndex].dSymbSize,
            x1+dNoise,dMinv,dLow5,median,dUpp5,dMaxv);
      }
   }
   return TRUE;
}

static
int DoDataFlat3D( pPlot )
   PLTNODE *pPlot;
{
   int xIndex,yIndex,zIndex,i;
   double x1,y1,x2,y2,z1,z2,zValue;
   BLOBGC gc;
   BLOBPOINT p[5];
   const char *pAddr;

   PLTClipWindow.x1=(double)(pPlot->pSlct->xlowb);
   PLTClipWindow.y1=(double)(pPlot->pSlct->ylowb);
   PLTClipWindow.x2=(double)(pPlot->pSlct->xuppb);
   PLTClipWindow.y2=(double)(pPlot->pSlct->yuppb);

   xIndex=pPlot->pSlct->xNo[0];
   yIndex=pPlot->pSlct->yNo[0];
   zIndex=pPlot->pSlct->zNo[0];

   DBPrint(pPlot->pSlct->pLegend[0].nPen);

   LgndGCLineAttr(0).gc_type=GE_GCPolygonL;
   LgndGCLineAttr(0).gc_mask=GE_GCMaskLineDefault;
   DBGC(LgndGCLineAttr(0));
   LgndGCSymbAttr(0).gc_type=GE_GCPolygon;
   LgndGCSymbAttr(0).gc_mask=GE_GCMaskFillDefault;
   DBGC(LgndGCSymbAttr(0));
   if (pPlot->pSlct->Etc.Flat3D.nColorTotal) {
      memcpy((char*)&gc,(char*)&LgndGCSymbAttr(0),sizeof(BLOBGC));
      z1=(*CPX->zCnvFn)(pPlot->pSlct->zlowb);
      z2=(*CPX->zCnvFn)(pPlot->pSlct->zuppb);
   }
   for (i=pPlot->pData->nrl;i<=pPlot->pData->nrh;i++) {
      x1=pPlot->pData->mtx[i][xIndex];
      y1=pPlot->pData->mtx[i][yIndex];
      zValue=pPlot->pData->mtx[i][zIndex];
      if (IsNaNDouble(x1) || IsNaNDouble(y1) || IsNaNDouble(zValue))
         continue;
      if (!isPointInWldWindow(&PLTClipWindow,x1,y1))
         continue;
      x1-=0.5;
      y1-=0.5;
      x2=x1+1.0;
      y2=y1+1.0;
      x1=(*CPX->xCnvFn)(x1);
      y1=(*CPX->yCnvFn)(y1);
      x2=(*CPX->xCnvFn)(x2);
      y2=(*CPX->yCnvFn)(y2);
      if (pPlot->pSlct->Etc.Flat3D.nColorTotal) {
         zValue=(*CPX->zCnvFn)(zValue);
         gc.foreground=GetColorValueFromZValue(
            pPlot->pSlct->Etc.Flat3D.nColorMin,
            pPlot->pSlct->Etc.Flat3D.nColorMax,
            pPlot->pSlct->Etc.Flat3D.nColorTotal,
            z1,z2,zValue
            );
         DBGC(gc);
      }
      p[0].x=x1;p[0].y=y1;
      p[1].x=x1;p[1].y=y2;
      p[2].x=x2;p[2].y=y2;
      p[3].x=x2;p[3].y=y1;
      p[4].x=x1;p[4].y=y1;
      DBPolyline(p,5);
   }
   LgndFontAttr(0).alignment=GE_AlignHCenter|GE_AlignVCenter;
   DBTextAttr(&LgndFontAttr(0),&CPX->attr);
   for (i=pPlot->pData->nrl;i<=pPlot->pData->nrh;i++) {
      x1=pPlot->pData->mtx[i][xIndex];
      y1=pPlot->pData->mtx[i][yIndex];
      zValue=pPlot->pData->mtx[i][zIndex];
      if (IsNaNDouble(x1) || IsNaNDouble(y1) || IsNaNDouble(zValue))
         continue;
      if (!isPointInWldWindow(&PLTClipWindow,x1,y1))
         continue;
      x1=(*CPX->xCnvFn)(x1);
      y1=(*CPX->yCnvFn)(y1);
      pAddr=dtos(zValue,pPlot->pSlct->Etc.Flat3D.qFormat);
      DBText(x1,y1,pAddr);
   }
   return TRUE;
}

static
int DrawPLTBarSymbol( x,y,dSize )
   double x,y,dSize;
{
   double xSize;
   double x1,y1,x2,y2;
   BLOBPOINT p[5];
 
   if (!isPointInWldWindow(&PLTClipWindow,x,y))
      return FALSE;
   x=(*CPX->xCnvFn)(x);
   y=(*CPX->yCnvFn)(y);
   xSize=dSize*SYMBOL_SCALE_FACTOR/CPX->attr.xScale/2.0;
   x1=x-xSize;
   x2=x+xSize;
   y1=CPX->wldwin.y1;
   y2=y;
   p[0].x=x1;p[0].y=y1;
   p[1].x=x1;p[1].y=y2;
   p[2].x=x2;p[2].y=y2;
   p[3].x=x2;p[3].y=y1;
   p[4].x=x1;p[4].y=y1;
   DBPolyline(p,5);
   return TRUE;
}

static
int DoDataBar( pPlot )
   PLTNODE *pPlot;
{
   register int i,j;
   double x1,y1,x2,y2;

   PLTClipWindow.x1=(double)(pPlot->pSlct->xlowb);
   PLTClipWindow.y1=(double)(pPlot->pSlct->ylowb);
   PLTClipWindow.x2=(double)(pPlot->pSlct->xuppb);
   PLTClipWindow.y2=(double)(pPlot->pSlct->yuppb);

   for (i=0;i<pPlot->pSlct->yNoTotal;i++) {
      if (pPlot->pSlct->pLegend[i].bLineOn) {
         DBGC(LgndGCLineAttr(i));
         for (MkNaNDouble(x1),
              MkNaNDouble(y1),
              j=pPlot->pData->nrl;
              j<=pPlot->pData->nrh;
              j++) {
            if (IsNaNDouble(x1)
            ||  IsNaNDouble(y1)) {
               x1=pPlot->pData->mtx[j][pPlot->pSlct->xNo[0]];
               y1=pPlot->pData->mtx[j][pPlot->pSlct->yNo[i]];
               continue;
            }
            x2=pPlot->pData->mtx[j][pPlot->pSlct->xNo[0]];
            y2=pPlot->pData->mtx[j][pPlot->pSlct->yNo[i]];
            if (IsNaNDouble(x2)
            ||  IsNaNDouble(y2))
               continue;
            DrawDataSymbolLine(x1,y1,x2,y2);
            x1=x2;
            y1=y2;
         }
      }

      LgndGCSymbAttr(i).gc_type=GE_GCPolygonL;
      LgndGCSymbAttr(i).gc_mask=GE_GCMaskLineDefault;
      DBGC(LgndGCSymbAttr(i));
      LgndGCSymbAttr(i).gc_type=GE_GCPolygon;
      LgndGCSymbAttr(i).gc_mask=GE_GCMaskFillDefault;
      DBGC(LgndGCSymbAttr(i));
      for (j=pPlot->pData->nrl;j<=pPlot->pData->nrh;j++) {
         x1=pPlot->pData->mtx[j][pPlot->pSlct->xNo[0]];
         y1=pPlot->pData->mtx[j][pPlot->pSlct->yNo[i]];
         if (IsNaNDouble(x1)
         ||  IsNaNDouble(y1))
            continue;
         DrawPLTBarSymbol(x1,y1,pPlot->pSlct->pLegend[i].dSymbSize);
      }
   }
   return TRUE;
}

static
int DoText( pPlot )
   PLTNODE *pPlot;
{
   int i;
   PTEXT *tx;

   for (i=0;i<pPlot->pText->nTotal;i++) {
      tx=pPlot->pText->qText[i];
      if (!tx->pString) continue;
      DBTextAttr(&tx->FontAttr,&CPX->attr);
      DBText((*CPX->xCnvFn)(tx->x),(*CPX->yCnvFn)(tx->y),tx->pString);
   }
   return TRUE;
}

static
int DoUserFunction( pPlot )
   PLTNODE *pPlot;
{
   PUFUN *pUf;
   double xlb,xub,ylb,yub,x1,y1,x2,y2;
   int point_tot,pt_tot,i,k;
   BLOBPOINT *point,*pt;
   extern PlotPolynomial();

   return TRUE; /* 20030901 */

   xlb=(*CPX->xCnvFn)(pPlot->pSlct->xlowb);
   xub=(*CPX->xCnvFn)(pPlot->pSlct->xuppb);
   ylb=(*CPX->yCnvFn)(pPlot->pSlct->ylowb);
   yub=(*CPX->yCnvFn)(pPlot->pSlct->yuppb);
   for (pUf=pPlot->pUfun->pHead;pUf;pUf=pUf->next) {
      if (!pUf->out.nResult) continue;
      if (!pUf->bLineOn) continue;
      if (pUf->nOption==1) {
         point_tot=2;
         point=salloc(BLOBPOINT,point_tot);
         point[0].x=xlb;
         point[0].y=(pUf->out.vResult)[1]*xlb+(pUf->out.vResult)[0];
         point[1].x=xub;
         point[1].y=(pUf->out.vResult)[1]*xub+(pUf->out.vResult)[0];
      } else
         PlotPolynomial(
            xlb,xub,ylb,yub,
            pUf->nOption,pUf->out.nResult,pUf->out.vResult,
            &point_tot,&point);
      pUf->GCAttr.gc_type=GE_GCPolygonL;
      pUf->GCAttr.gc_mask=GE_GCMaskLineDefault|GE_GCMaskStipple|GE_GCMaskPolyArcAttr;
      pUf->GCAttr.polyarc_attr=GE_PolyArcLine;
      DBGC(pUf->GCAttr);
      pt=salloc(BLOBPOINT,point_tot);
      for (i=pt_tot=0;i<point_tot-1;i++) {
         x1=point[i].x;
         y1=point[i].y;
         x2=point[i+1].x;
         y2=point[i+1].y;
         k=clipper_line(xlb,xub,ylb,yub,&x1,&y1,&x2,&y2);
         if (k!=FALSE) { /* k==TRUE or TRUE+1 */
            if (!pt_tot)
               pt_tot=1;
            pt[pt_tot-1].x=x1;
            pt[pt_tot-1].y=y1;
            pt[pt_tot].x=x2;
            pt[pt_tot].y=y2;
            pt_tot++;
         }
         if (k==TRUE+1
         && pt_tot>1) {
            DBPolyline(pt,pt_tot);
            pt_tot=1;
         }
      }
      if (pt_tot>1)
         DBPolyline(pt,pt_tot);
      free(point);
      free(pt);
   }
   return TRUE;
}

static
int DBSetList( pList )
   BLOBLIST *pList;
{
   DBList=pList;
   return TRUE;
}

static
int DBHeader( pName,version,date,xfrm,reset,x1,y1,x2,y2 )
   char *pName;
   int version;
   long date;
   XFRMATTR xfrm;
   char reset;
   double x1,y1,x2,y2;
{
   BLOBHEADER obj;
   char *pNumber;
   double x,y;
   XMTX2D mtx;
   BLOB2DMDATA array;

   strcpy(obj.name,pName);
   strcpy(obj.version,pNumber=itostr(version,"%d"));freeEx(pNumber);
   strcpy(obj.date,pNumber=itostr(date,"%d"));freeEx(pNumber);
   obj.c='\0';

   x=y=0.5;
   AlloXMatrix2D(&mtx);
   XMatrix2DScale(mtx,x,y,xfrm.xScale,xfrm.yScale,ComXMatrix2D);
   XMatrix2DRotate(mtx,x,y,xfrm.angle,ComXMatrix2D);
   XMatrix2DTranslate(mtx,xfrm.xTranslate,xfrm.yTranslate,ComXMatrix2D);
   SetXMatrixData2D(&array,mtx[1][1],mtx[1][2],mtx[2][1],mtx[2][2],mtx[3][1],mtx[3][2]);
   FreeXMatrix2D(mtx);

   obj.m11=array.m11; obj.m12=array.m12;
   obj.m21=array.m21; obj.m22=array.m22;
   obj.m31=array.m31; obj.m32=array.m32;
   obj.reset=reset;

   BLAddHeader(DBList,&obj,1);
   BLAdd2DMatrix(DBList,&array,1);

   return TRUE;
}

static
int EchoPlotPoints( pPlot )
   PLTNODE *pPlot;
{
   extern int GetBoxSymbolData _((
      /* in */
      double *pData /* base = 1 */,int nTotal,double dRange,
      /* out */
      double *dMinv,double*dLow5,double*dMed,double*dUpp5,double*dMaxv,
      double*dSigma ));

   char *qNumFormat=" %.3e",qNaNFormat[128];
   int bMultipleXColumn;
   int nIndex,xIndex,yIndex,zIndex,nCount,nRow,nCol;
   double *xVec,*yVec,x,y;

   Echo(0,-2); /* 20030501 */

   sprintf(qNaNFormat,qNumFormat,0.0);
   memset(qNaNFormat,' ',strlen(qNaNFormat));
   strncpy(qNaNFormat+1,"#NaN",4);

   bMultipleXColumn=FALSE;
   nCol=pPlot->pSlct->xNo[0];
   for (nIndex=1;nIndex<pPlot->pSlct->xNoTotal;nIndex++) {
      if (nCol!=pPlot->pSlct->xNo[nIndex]) {
         bMultipleXColumn=TRUE;
         break;
      }
   }

   switch (pPlot->pAttr->type) {
   case PLT2D_GENETIC :
   case PLT2D_GENETICPLUS :
      if (pPlot->pAttr->xScale==SCALE_NORM
         ||pPlot->pAttr->yScale==SCALE_NORM) {
         Echo(" (nCol), 5%%, 10%%, 20%%, median, 80%%, 90%%, 95%% \n");
         xVec=dvector(1,pPlot->pData->nrh-pPlot->pData->nrl+1);
         yVec=dvector(1,pPlot->pData->nrh-pPlot->pData->nrl+1);
         for (nIndex=0;nIndex<pPlot->pSlct->xNoTotal;nIndex++) {
            xIndex=(pPlot->pAttr->xScale!=SCALE_NORM ? pPlot->pSlct->xNo:pPlot->pSlct->yNo)[nIndex];
            yIndex=(pPlot->pAttr->xScale==SCALE_NORM ? pPlot->pSlct->xNo:pPlot->pSlct->yNo)[nIndex];
            if (IsMinOrMaxInt(xIndex)||IsMinOrMaxInt(yIndex)) continue;
            xIndex=ABS(xIndex);
            yIndex=ABS(yIndex);
            nCount=0;
            for (nRow=pPlot->pData->nrl;nRow<=pPlot->pData->nrh;nRow++) {
               x=pPlot->pData->mtx[nRow][xIndex];
               y=pPlot->pData->mtx[nRow][yIndex];
               if (IsNaNDouble(x)||IsNaNDouble(y)) break;
               nCount++;
               xVec[nCount]=x;
               yVec[nCount]=y;
            }
            for (zIndex=1;zIndex<=nCount;zIndex++) {
               yVec[zIndex]=icnorm(yVec[zIndex]);
            }
            Echo(
               " (%02d) %.2e %.2e %.2e %.2e %.2e %.2e %.2e\n",
               yIndex,
               twoptint(yVec,xVec,nCount,-1.645), /*  5% */
               twoptint(yVec,xVec,nCount,-1.28),  /* 10% */
               twoptint(yVec,xVec,nCount,-0.84),  /* 20% */
               twoptint(yVec,xVec,nCount,0.0),    /* 50% */
               twoptint(yVec,xVec,nCount,+0.84),  /* 80% */
               twoptint(yVec,xVec,nCount,+1.28),  /* 90% */
               twoptint(yVec,xVec,nCount,+1.645));/* 95% */
         }
         free_dvector(xVec,1,nCount);
         free_dvector(yVec,1,nCount);
      } else if (bMultipleXColumn) {
         Echo(".MultipPlot x-column. Too many data to print.\n");
      } else {
         Echo(" x(%d)",pPlot->pSlct->xNo[0]);
         for (nIndex=0;nIndex<pPlot->pSlct->yNoTotal;nIndex++) {
            Echo(" y(%d)",pPlot->pSlct->yNo[nIndex]);
         }
         Echo("\r\n");
         for (nRow=pPlot->pData->nrl;nRow<=pPlot->pData->nrh;nRow++) {
            xIndex=pPlot->pSlct->xNo[0];
            if (IsMinOrMaxInt(xIndex)) {
               Echo(" #xNo  ");
            } else {
               x=pPlot->pData->mtx[nRow][xIndex];
               IsNaNDouble(x)?Echo(qNaNFormat):Echo(qNumFormat,x);
            }
            for (nCol=0;nCol<pPlot->pSlct->yNoTotal;nCol++) {
               yIndex=ABS(pPlot->pSlct->yNo[nCol]);
               if (IsMinOrMaxInt(yIndex)) {
                  Echo(" #xNo  ");
               } else {
                  y=pPlot->pData->mtx[nRow][yIndex];
                  IsNaNDouble(y)?Echo(qNaNFormat):Echo(qNumFormat,y);
               }
            }
            Echo("\r\n");
         }
      }
      break;
   case PLT2D_MOMENT :
      for (nIndex=0;nIndex<pPlot->pSlct->yNoTotal;nIndex++) {
         Echo(
            " x-value, dMinv, dLow5, median, dUpp5, dMaxv, 3sigma @%1.0f%%\n",
            pPlot->pSlct->Etc.LineMoment.dRange);
         xIndex=ABS(pPlot->pSlct->xNo[nIndex]);
         yIndex=ABS(pPlot->pSlct->yNo[nIndex]);
         for (nRow=pPlot->pData->nrl;nRow<=pPlot->pData->nrh;nRow++) {
            Echo(
               " %.2e %.2e %.2e %.2e %.2e %.2e %.2e\n",
            pPlot->pData->mtx[nRow][xIndex],
            pPlot->pData->mtx[nRow][yIndex+MTX_OFFSET_TO_MINV],
            pPlot->pData->mtx[nRow][yIndex+MTX_OFFSET_TO_LOW5],
            pPlot->pData->mtx[nRow][yIndex+MTX_OFFSET_TO_MEDIAN],
            pPlot->pData->mtx[nRow][yIndex+MTX_OFFSET_TO_UPP5],
            pPlot->pData->mtx[nRow][yIndex+MTX_OFFSET_TO_MAXV],
            pPlot->pData->mtx[nRow][yIndex+MTX_OFFSET_TO_SIGMA]*3.0);
         }
      }
      break;
   case PLT2D_FLAT3D : { /* 2001.0410 */
      double **ppMatrix;
      int nrl,nrh,ncl,nch,xIndex,yIndex,i,j;
      nrl=(int)(pPlot->pSlct->yminv);
      nrh=(int)(pPlot->pSlct->ymaxv);
      ncl=(int)(pPlot->pSlct->xminv);
      nch=(int)(pPlot->pSlct->xmaxv);
      xIndex=ABS(pPlot->pSlct->xNo[0]);
      yIndex=ABS(pPlot->pSlct->yNo[0]);
      zIndex=ABS(pPlot->pSlct->zNo[0]);
      ppMatrix=dmatrix(nrl,nrh,ncl,nch);
      for (i=nrl;i<=nrh;i++) {
         for (j=ncl;j<=nch;j++) {
            MkNaNDouble(ppMatrix[i][j]);
         }
      }
      for (nIndex=pPlot->pData->nrl;nIndex<=pPlot->pData->nrh;nIndex++) {
         i=(int)(pPlot->pData->mtx[nIndex][yIndex]);
         j=(int)(pPlot->pData->mtx[nIndex][xIndex]);
         ppMatrix[i][j]=pPlot->pData->mtx[nIndex][zIndex];
      }
      for (i=nrh;i>=nrl;i--) {
         for (j=ncl;j<=nch;j++) {
            if (IsNaNDouble(ppMatrix[i][j])) {
               Echo(qNaNFormat);
            } else {
               Echo(qNumFormat,ppMatrix[i][j]);
            }
         }
         Echo("\n");
      }
      free_dmatrix(ppMatrix,nrl,nrh,ncl,nch);
      }
      break;
   }

   Echo(0,+2); /* 20030501 */

   return TRUE;
}

static
int DBPlotPoints( pPlot )
   PLTNODE *pPlot;
{
   int i,j,nIndex,xIndex,yIndex,nRow;
   double x,y;

   PLTClipWindow.x1=(double)(pPlot->pSlct->xlowb);
   PLTClipWindow.y1=(double)(pPlot->pSlct->ylowb);
   PLTClipWindow.x2=(double)(pPlot->pSlct->xuppb);
   PLTClipWindow.y2=(double)(pPlot->pSlct->yuppb);
   switch (pPlot->pAttr->type) {
   case PLT2D_GENETIC :
   case PLT2D_BAR :
      for (i=0;i<pPlot->pSlct->yNoTotal;i++) {
         j=(pPlot->pSlct->xNoTotal>i) ? i:pPlot->pSlct->xNoTotal-1;
         for (nRow=pPlot->pData->nrl;nRow<=pPlot->pData->nrh;nRow++) {
            x=pPlot->pData->mtx[nRow][pPlot->pSlct->xNo[j]];
            y=pPlot->pData->mtx[nRow][pPlot->pSlct->yNo[i]];
            if (!isPointInWldWindow(&PLTClipWindow,x,y))
               continue;
            DBData((*pPlot->pXfrm->xCnvFn)(x),(*pPlot->pXfrm->yCnvFn)(y));
         }
      }
      break;
   case PLT2D_MOMENT :
      for (nIndex=0;nIndex<=pPlot->pSlct->yNoTotal;nIndex++) {
         xIndex=pPlot->pSlct->xNo[nIndex];
         yIndex=pPlot->pSlct->yNo[nIndex];
         for (nRow=pPlot->pData->nrl;nRow<=pPlot->pData->nrh;nRow++) {
            x=pPlot->pData->mtx[nRow][xIndex];
            y=pPlot->pData->mtx[nRow][yIndex+MTX_OFFSET_TO_MEDIAN];
            if (!isPointInWldWindow(&PLTClipWindow,x,y))
               continue;
            DBData((*pPlot->pXfrm->xCnvFn)(x),(*pPlot->pXfrm->yCnvFn)(y));
         }
      }
      break;
   }
   return TRUE;
}

static
int DBXmtx2DData( xfrm )
   XFRMATTR xfrm;
{
   XMTX2D nAttr;
   double x,y;
   BLOB2DMDATA xmtx2d;

   x=y=0.0;
   AlloXMatrix2D(&nAttr);
   XMatrix2DScale(nAttr,x,y,xfrm.xScale,xfrm.yScale,ComXMatrix2D);
   XMatrix2DRotate(nAttr,x,y,xfrm.angle,ComXMatrix2D);
   XMatrix2DTranslate(nAttr,xfrm.xTranslate,xfrm.yTranslate,ComXMatrix2D);
   SetXMatrixData2D(&xmtx2d,nAttr[1][1],nAttr[1][2],nAttr[2][1],nAttr[2][2],
                            nAttr[3][1],nAttr[3][2]);
   FreeXMatrix2D(nAttr);
   BLAdd2DMatrix(DBList,&xmtx2d,1);
   return TRUE;
}

static
int DBGC( obj )
   BLOBGC obj;
{
   BLAddGC(DBList,&obj,1);
   return TRUE;
}

static
int DBData( x,y )
   double x,y;
{
   BLOBDATA obj;

   obj.x=x;
   obj.y=y;
   BLAddData(DBList,&obj,1);
   return TRUE;
}

static
int DBPoint( x,y )
   double x,y;
{
   BLOBPOINT obj;

   obj.x=x;
   obj.y=y;
   BLAddPoint(DBList,&obj,1);
   return TRUE;
}

static
int DBLine( x1,y1,x2,y2 )
   double x1,y1,x2,y2;
{
   BLOBLINE obj;

   obj.x1=x1;
   obj.y1=y1;
   obj.x2=x2;
   obj.y2=y2;
   BLAddLine(DBList,&obj,1);
   return TRUE;
}

static
int DBLines( lines,tot )
   BLOBLINE *lines;
   int tot;
{
   BLAddLine(DBList,lines,tot);
   return TRUE;
}
 
static
int DBPolyline( points,tot )
   BLOBPOINT *points;
   int tot;
{
   BLAddPoly(DBList,points,tot);
   return TRUE;
}

static
int DBArc( x,y,width,height,angle1,angle2 )
   double x,y,width,height,angle1,angle2;
{
   BLOBARC obj;

   obj.x=x;
   obj.y=y;
   obj.width=width;
   obj.height=height;
   obj.angle1=angle1;
   obj.angle2=angle2;
   BLAddArc(DBList,&obj,1);
   return TRUE;
}

static
int DBTextAttr( font,xfrm )
   FONTATTR *font;
   XFRMATTR *xfrm;
{
   BLOBGC gc;
   double w,h,sine,cosine;
   gc.gc_type=GE_GCText;
   gc.gc_mask=GE_GCMaskFont|GE_GCMaskForeground|GE_GCMaskLineWidth;
   strcpy(gc.font,"*");
   gc.font_type=GE_FontTrueType;
   gc.font_height=font->height;
   gc.font_width=0;
   gc.foreground=font->color;
   gc.font_angle=font->angle*10;
   gc.text_format=font->alignment;
   gc.line_width=1;
   /**/
   w=gc.font_width ? gc.font_width:gc.font_height/3.0;
   h=gc.font_height;
   sine=sin(RADIAN(gc.font_angle/10));
   cosine=cos(RADIAN(gc.font_angle/10));
   gc.font_matrix.m11=w*cosine/(xfrm->xScale*1e3);
   gc.font_matrix.m12=w*sine/(xfrm->yScale*1e3);
   gc.font_matrix.m21=h*-sine/(xfrm->xScale*1e3);
   gc.font_matrix.m22=h*cosine/(xfrm->yScale*1e3);
   gc.font_matrix.m31=0.0;
   gc.font_matrix.m32=0.0;
   BLAddGC(DBList,&gc,1);
   return TRUE;
}

static
int DBText( x,y,str )
   double x,y;
   char *str;
{
   BLAddText(DBList,str,strlen(str)+1,x,y);
   return TRUE;
}

static
int DBClipWin( x1,y1,x2,y2 )
   double x1,y1,x2,y2;
{
   BLOBCLIPWIN clip;

   clip.x1=x1; clip.x2=x2;
   clip.y1=y1; clip.y2=y2;
   BLAddClipWin(DBList,&clip,1);
   return TRUE;
}

static
int DBPrint( index )
   int index;
{
   BLOBPRINT print;

   print.xyp.pen_select=(char)index;
   BLAddPrint(DBList,&print,1);
   return TRUE;
}

/******************************************************************************/
