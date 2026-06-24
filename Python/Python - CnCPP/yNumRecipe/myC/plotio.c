/******************************************************************************/
/*                           file name : plotio.c                             */
/*                         description : plot input/output                    */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43230913-43240627                    */
/* 4324 0724-0730,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4325 0810-1118,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4326 0318,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4327 1002-1004,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4328 0509,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4329 0122,0411,0515,0822,0911,____,____,____,____,____,____,____,____,____ */
/* 4330 0307,0717-0830,____,____,____,____,____,____,____,____,____,____,____ */
/* 4331 0604,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0331,0706,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0315-0530,0606-0707,0822-0926,1009,1208,1214,____,____,____,____,____ */
/* 4334 0109,0220-0221,0307-0316,0515,0815,____,____,____,____,____,____,____ */
/* 4336 0212-0311,0417,0429,0522,0822,0902,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#if defined(_MSC_)
#include <stdarg.h>
#endif
#include "myCore.h"
#include "tools.h"
#include "number.h"
#include "nrecipe.h"
#include "any.h"
#include "geprint.h"
#include "plotsymb.h"
#include "gecore.h"
#include "str.h"
#include "plot.h"

/******************************************************************************/

/*---i-n----------------------------------------------------------------------*/

static char *qPltTokenOption=" \n\t\b\r\f";
static int TokenSplitter();
static int DoFontAttr();
static int DoGCAttr();

/* All parameters shall be zero or default. */
int DoScriptCommandPBEG _(( ));
int DoScriptCommandGXFM _(( ));
int DoScriptCommandGTXT _(( ));
int DoScriptCommandGOUT _(( ));
int DoScriptCommandEXEC _(( ));
int DoScriptCommandPLOT _(( ));
int DoScriptCommandATTR _(( ));
int DoScriptCommandDATA _(( ));
int DoScriptCommandXYZB _(( ));
int DoScriptCommandSYMB _(( ));
int DoScriptCommandAXIS _(( ));
int DoScriptCommandTEXT _(( ));
int DoScriptCommandUFUN _(( ));
int DoScriptCommandVIEW _(( ));
int DoScriptCommandError _(( ));

/*---o-u-t--------------------------------------------------------------------*/

char *gpGRLog=NULL;
char *gpGRErrorLog=NULL;

static FILE *pFILEGRLog=NULL;
#if defined(_MSC_)
int    Echo        _((char*,...));
#elif defined(_UNIXC_) || defined(_HP715C_)
int    Echo        _(( ));
#endif

/*---I-n-t-e-f-a-c-e-T-o-C-p-p-C-o-d-e------------------------------------*/

int (*pEchoAbroad)(const char*)=0; /* is set by a MFC code 2K.0512 */
 
/******************************************************************************/
/************************************K*I*M*************************************/
/******************************Y*O*N*G*-*S*H*I*K*******************************/
/***********************************P*L*O*T************************************/
/********************************G*R*A*P*H*E*R*********************************/
/******************************************************************************/
/*******************************4*3*2*4*1*0*1*7********************************/
/******************************************************************************/

static
int GetColIndexArray( qString,nArray,vArray )
   const char *qString;
   int *nArray,**vArray;
/*
 * in  : "1,a3,4-9:10:11:12-13,r1,"
 * out : vArray[0-based]={1,(a)3,4,5,6,7,8,9,-10,11,-12,-13,(r)-1}
 * [20030901-0902]
 * (a): PLOT_ATTACHEDINDEX_MASK
 * (r): PLOT_REVERSEINDEX_MASK
 * (-): PLOT_BLOCKINDEX_MASK
 */
{
   int iParity2=BIT(sizeof(int)*8-2);
   int nCol,*vCol,nIndex,bSign,nEnd,nCurrent;
   char *pAddr;

   *vArray=0;
   *vArray=0;

   nCol=chrcount(qString,',')+chrcount(qString,':')+1;
   vCol=salloc(int,nCol+1);
   bSign=1;
   for (nIndex=0,pAddr=(char*)qString;*pAddr;pAddr++) {
      switch (tolower(*pAddr)) {
      case '0' : case '1' : case '2' : case '3' : case '4' :
      case '5' : case '6' : case '7' : case '8' : case '9' :
         vCol[nIndex++]=bSign*(int)atof(pAddr);
         skipdigit(&pAddr);
         pAddr--;
         break;
      case '-' :
         pAddr++;
         if (!*pAddr) goto R;
         nEnd=(int)atof(pAddr);
         nCurrent=ABS(vCol[nIndex-1]);
         if (nEnd<nCurrent) {
            free(vCol);
            *nArray=0;
            *vArray=0;
            return FALSE;
         } else if (nEnd>nCurrent) {
            nCol+=nEnd-nCurrent;
            vCol=realloc(vCol,nCol*sizeof(int));
            for (nCurrent++;nCurrent<=nEnd;nCurrent++) {
               vCol[nIndex++]=bSign*nCurrent;
            }
         } // else {}
         skipdigit(&pAddr);
         pAddr--;
         break;
      case ':' :
         bSign*=-1;
         break;
      case ',' :
         if (pAddr[1]=='-') goto R; /* 20030901 */
         break;
      case 'a' : /* 20030901 */
         pAddr++;
         if (!*pAddr) goto R;
         vCol[nIndex]=bSign*(int)atof(pAddr);
         vCol[nIndex]|=PLOT_ATTACHEDINDEX_MASK;
         nIndex++;
         break;
      case 'r' : /* 20030902 */
         pAddr++;
         if (!*pAddr) goto R;
         vCol[nIndex]=bSign*(int)atof(pAddr);
         vCol[nIndex]|=PLOT_REVERSEINDEX_MASK;
         skipdigit(&pAddr);pAddr--; /* 20030912 */
         nIndex++;
         break;
      }
   }

R: *vArray=vCol;
   return (*nArray=nCol);
}

static 
int TokenSplitter( pTok,ppS1,ppS2 )
   char *pTok,**ppS1,**ppS2;
{
   char *pAddr;

   *ppS1=pTok;
   *ppS2=0;
   pAddr=strchr(pTok,'='); /* dividing character -> = */
   if (!pAddr) return 1; 
   *pAddr='\0';
   *ppS2=pAddr+1;
   if (**ppS2) {
      pAddr=strchr(*ppS2,'\"');
      if (pAddr) {
         *ppS2=pAddr+1;
         pAddr=strrchr(*ppS2,'\"');
         if (pAddr)
            *pAddr='\0';
      }
      return 2;    
   } else 
      return 1;    
}

static
int DoFontAttr( attr,cmnd,para )
   FONTATTR *attr;
   char *cmnd,*para;
/*
 * font=[<d>]
 * size=[<d>] width=[<d>] height=[<d>]
 * align=[l|r|c]
 * angle=[<d>] ! degree
 * def
 */
{
   if (strequ(cmnd,"font"))
      strncpy(attr->font,para,32);
   else if (strequ(cmnd,"size"))
   {
      attr->height=(int)atof(para);
      attr->width=(int)(attr->height/2);
   }
   else if (strequ(cmnd,"width"))
      attr->width=atoi(para);
   else if (strequ(cmnd,"height"))
      attr->height=atoi(para);
   else if (strequ(cmnd,"align"))
   {
      attr->alignment=0;      
      switch (para[0]) { /* horizontal flag */
      case '1' : case 'l' : case 'L' : attr->alignment|=GE_AlignLeft;   break;
      case '2' : case 'c' : case 'C' : attr->alignment|=GE_AlignHCenter;break;
      case '3' : case 'r' : case 'R' : attr->alignment|=GE_AlignRight;  break;
      }
      switch (para[1]) { /* vertical flag */
      case '1' : case 'b' : case 'B' : attr->alignment|=GE_AlignBottom;break;
      case '2' : case 'c' : case 'C' : attr->alignment|=GE_AlignVCenter;break;
      case '3' : case 't' : case 'T' : attr->alignment|=GE_AlignTop;break;
      }
   }
   else if (strequ(cmnd,"angle"))
      attr->angle=atoi(para);
   else if (strequ(cmnd,"color")) {
      attr->color=isdigit(*para) ? atoi(para):GEColorByName(NULL,para);
      if (attr->color<0) return FALSE;
   }
   else if (strequ(cmnd,"def")) {
      SetGRFontDefault(*attr);
      }
   else 
      return FALSE;
   return TRUE;
}

static
int DoGCAttr( attr,cmnd,para )
   BLOBGC *attr;
   char *cmnd,*para;
{
   DLL *pList;
   DLN *node;
   int nIndex;

   if (strequ(cmnd,"color")) {
      attr->foreground=isdigit(*para) ? atoi(para):GEColorByName(NULL,para);
      if (attr->foreground<0) return FALSE;
   } else if (strequ(cmnd,"background")) {
      attr->background=GEColorByName(NULL,para);
      if (attr->background<0) return FALSE;
   } else if (strequ(cmnd,"width")) {
      attr->line_width=(int)atof(para);
      if (attr->line_width<=0) return FALSE;
   } else if (strequ(cmnd,"style")) {
      attr->line_style=(int)atof(para);
      if (attr->line_style>GE_LineDoubleDash) return FALSE;
   } else if (strequ(cmnd,"cap")) {
      attr->cap_style=(int)atof(para);
      if (attr->cap_style>GE_CapProjecting) return FALSE;
   } else if (strequ(cmnd,"join")) {
      attr->join_style=(int)atof(para);
      if (attr->join_style>GE_JoinBevel) return FALSE;
   } else if (strequ(cmnd,"stipple")) {
      attr->stipple=(int)atof(para);
      if (attr->stipple<0) return FALSE;
   } else if (strequ(cmnd,"dash_list")) {
      strtolower(para);
      if (isalpha(*para)) { /* 2001.0422 */
         if (strnequ(para,"solid",2)) {
            attr->line_style=GE_LineSolid;
         } else {
            attr->line_style=GE_LineOnOffDash;
            attr->dash_offset=0;
            nIndex=0;            
            if (strnequ(para,"longdashed",2)) {
               attr->dash_list[nIndex++]=10;
               attr->dash_list[nIndex++]=3;
               attr->dash_list[nIndex++]=10;
               attr->dash_list[nIndex++]=3;
            } else if (strnequ(para,"shortdashed",2)) {
               attr->dash_list[nIndex++]=6;
               attr->dash_list[nIndex++]=3;
               attr->dash_list[nIndex++]=6;
               attr->dash_list[nIndex++]=3;
            } else if (strnequ(para,"dashdotted",2)) {
               attr->dash_list[nIndex++]=6;
               attr->dash_list[nIndex++]=3;
               attr->dash_list[nIndex++]=3;
               attr->dash_list[nIndex++]=3;
            } else if (strnequ(para,"dotted",2)) {
               attr->dash_list[nIndex++]=3;
               attr->dash_list[nIndex++]=3;
            }
            attr->dashes=nIndex;
         }
      } else {
         DLLOpen(&pList);
         DLLAddTokens(pList,para,"(),");
         if (pList->total<2) {
            DLLClose(pList);
            return TRUE;
         }
         attr->line_style=GE_LineOnOffDash;
         attr->dash_offset=0;
         nIndex=0;
         for (node=pList->head;nIndex<pList->total;node=node->next)
            attr->dash_list[nIndex++]=atoi(node->tok);
         attr->dashes=nIndex;
         DLLClose(pList);
      }
   } else if (strequ(cmnd,"polyarc")) {
      attr->polyarc_attr=(int)atof(para);
      if (attr->polyarc_attr>GE_PolyArcBoth) return FALSE;
   } else if (strequ(cmnd,"def")) {
      GESetGCDefault(*attr)
   } else 
      return FALSE;
   return TRUE;
}

int GRGetColNumberCount(
   const char *qString
   )
{
   int nColumn,*vColumn;
   
   nColumn=chrcount(qString,':');
   if (nColumn) return nColumn+1;
   GetColIndexArray(qString,&nColumn,&vColumn);
   freeEx(vColumn);
   return nColumn;
}

int DoScriptCommandNull( pList,pDummy )
   PLTLIST *pList;
   char *pDummy;
{
   return TRUE;
}

int DoScriptCommandPBEG( pList,pDummy )
   PLTLIST *pList;
   char *pDummy;
{
   int nIndex;

   pList->Glob.xfrm.angle =0.0;
   pList->Glob.xfrm.xScale=1.0;
   pList->Glob.xfrm.yScale=1.0;
   pList->Glob.xfrm.xTranslate=0.0;
   pList->Glob.xfrm.yTranslate=0.0;
   SetGRFontDefault(pList->Glob.TextAttr);
   /* 20030217
   pList->Glob.x=0.0;
   pList->Glob.y=0.0;
   */
   pList->Glob.pTitle=NULL;
   pList->Glob.pHomePath=NULL;
   pList->Glob.dTitleSpaceFactor=1;
   pList->Glob.OutputType.whole.attr=~(~0);
   pList->Glob.nPageDirection=PD_LANDSCAPE;
   pList->Glob.bReuseGargamelOutputIfExist=FALSE;
   pList->Glob.bEchoPlotPoints=TRUE;
   nIndex=noof(pList->Glob.qFile);
   while (nIndex--)  {
      pList->Glob.qFile[nIndex].pInput=NULL;
      pList->Glob.qFile[nIndex].pOption=NULL;
      pList->Glob.qFile[nIndex].pOutput=NULL;
   }
   return TRUE;
}

int DoScriptCommandGXFM( pList,pAddr )
   PLTLIST *pList;
   const char *pAddr;
/*
 gxfm [angle=<f>] 
      [xscale=<f>] [yscale=<f>] [scale=<f>]
      [xtrans=<f>] [ytrans=<f>]
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   if (strequ(pS1,"angle"))
      pList->Glob.xfrm.angle=RADIAN(atof(pS2));
   else if (strequ(pS1,"xscale"))
      pList->Glob.xfrm.xScale=atof(pS2);
   else if (strequ(pS1,"yscale"))
      pList->Glob.xfrm.yScale=atof(pS2);
   else if (strequ(pS1,"scale"))
      pList->Glob.xfrm.xScale=
      pList->Glob.xfrm.yScale=atof(pS2);
   else if (strequ(pS1,"xtrans"))
      pList->Glob.xfrm.xTranslate=atof(pS2);
   else if (strequ(pS1,"ytrans"))
      pList->Glob.xfrm.yTranslate=atof(pS2);
   else
      bResult=FALSE;

   free(pString);
   return bResult;
}

int DoScriptCommandGTXT( pList,pAddr )
   PLTLIST *pList;
   const char *pAddr;
/*
 gtxt [txt=<c>]
      [txt.spaceFactor=<f>] <--- with respect to font height.20030217
      [t.def]
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);
       
   if (strequ(pS1,"txt"))
      {
      freeEx(pList->Glob.pTitle);
/*
      pList->Glob.pTitle=strdplEx(pS2);
*/
      if (pS2&&*pS2)
         pList->Glob.pTitle=strdpl(pS2);
      }
   else if (strequ(pS1,"txt.spaceFactor"))
      pList->Glob.dTitleSpaceFactor=atof(pS2);
   else if (pS1[0]=='t'&&pS1[1]=='.') {
      if (!DoFontAttr(&(pList->Glob.TextAttr),&(pS1[2]),pS2)) {
         bResult=FALSE;
      }
   } else
      bResult=FALSE;

   free(pString);
   return bResult;
}

int DoScriptCommandGOUT( pList,pAddr )
   PLTLIST *pList;
   const char *pAddr;
/*
 gout [ps|psf] [gps] [eps] [hpgl] [dot] [fmt]
      [name=<s>]
      [landscape|portrait]
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   if (strequ(pS1,"bEchoPlotPoints"))
      pList->Glob.bEchoPlotPoints=atoi(pS2);
   else if (strequ(pS1,"ps")||strequ(pS1,"psf"))
      pList->Glob.OutputType.parts.COLORPS=1;
   else if (strequ(pS1,"gps"))
      pList->Glob.OutputType.parts.GRAYPS=1;
   else if (strequ(pS1,"eps"))
      pList->Glob.OutputType.parts.EPS=1;
   else if (strequ(pS1,"hpgl"))
      pList->Glob.OutputType.parts.HPGL2=1;
   else if (strequ(pS1,"dot"))
      pList->Glob.OutputType.parts.DOT=1;
   else if (strequ(pS1,"fmt"))
      pList->Glob.OutputType.parts.SCRIPT=1;
   else if (strequ(pS1,"name"))
   {
      freeEx(pList->Glob.pName);
      pList->Glob.pName=strdplEx(pS2);
   }
   else if (strequ(pS1,"landscape"))
      pList->Glob.nPageDirection=PD_LANDSCAPE;
   else if (strequ(pS1,"portrait"))
      pList->Glob.nPageDirection=PD_PORTRAIT;
   else
      bResult=FALSE;

   free(pString);
   return bResult;
}

int DoScriptCommandEXEC( pList,pAddr )
   PLTLIST *pList;
   const char *pAddr;
/*
 exec [type=gargamel]   <---- just one
      [home="<s>"]
      [bReuseIfExist=TRUE|FALSE]
      [file="<s>|<s>|<s>"] <- 1st<s>=pattern,2nd<s>=split,3rd<s>=option
      Cautions: Inhibited characters in a file path
                * ? " < > |
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;
   int nIndex;
   const char *qDelimiters="*?\"<>|";

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   for (nIndex=0;pList->Glob.qFile[nIndex].pInput;nIndex++);

   /*
   if (strequ(pS1,"file")) {
      pS1=pS2;
      if (pS1[0]=='<') {
         pS2=strchr(pS1,'>');
         if (!pS2) return FALSE;
         memcpy(pS1,pS1+1,(int)(pS2-pS1-1));
         pS2[-1]=0;
         pS2++;
      } else {
         pS2=strchr(pS1,' ');
         if (!pS2) return FALSE;
         pS2[0]=0;
         pS2++;
      }
      skipwhite(&pS2);
      if (pS2[0]=='<') {
         char *pAddr=strchr(pS2,'>');
         if (!pAddr) return FALSE;
         pAddr[0]='\"';
         pS2[0]='\"';
      }
      pList->Glob.qFile[nIndex].input=strdplEx(pS1);
      pList->Glob.qFile[nIndex].option=strdplEx(pS2);
      strtrim(pList->Glob.qFile[nIndex].input);
      strtrim(pList->Glob.qFile[nIndex].option);
   }
   */
   if (strequ(pS1,"type")) {
      /* gargamel */;
   } else if (strequ(pS1,"file")) {
      char *p1,*p2,*p3;
      p1=strtokbyindex(pS2,qDelimiters,0);
      p2=strtokbyindex(pS2,qDelimiters,1);
      p3=strtokbyindex(pS2,qDelimiters,2);
      if (p1 && p2 && p3) {
         strtrim(p1);
         strtrim(p2);
         strtrim(p3);
         pList->Glob.qFile[nIndex].pInput=strvcat(p1,PLTOSCRIPT_PATH_DELIMITER,p2,0);
         pList->Glob.qFile[nIndex].pOption=strdpl(p3);
      } else {
         bResult=FALSE;
      }
      freeEx(p1);
      freeEx(p2);
      freeEx(p3);
   }
   else if (strequ(pS1,"home"))
      pList->Glob.pHomePath=strdplEx(pS2);
   else if (strequ(pS1,"bReuseIfExist"))
      pList->Glob.bReuseGargamelOutputIfExist=(int)atof(pS2);
   else
      bResult=FALSE;

   free(pString);
   return bResult;
}

int DoScriptCommandPLOT( pList,pDummy ) 
   PLTLIST *pList;
   const char *pDummy;
/*
 .plot
 */
{
   PLTNODE *pPlot;

   if (pList->pTail &&
      (!pList->pTail->pSlct->xNo&&!pList->pTail->pSlct->yNo))
      return FALSE;

   AlloPlot(&pPlot);
   AnyAddDLObject(pList,pPlot);
   pList->nTotal++;

   memset(pPlot->pAttr,0,sizeof(PLTATTR));
      pPlot->pAttr->type=PLT2D_GENETIC;
      pPlot->pAttr->xScale=SCALE_LIN;
      pPlot->pAttr->yScale=SCALE_LIN;
      pPlot->pAttr->zScale=SCALE_LIN;
      GESetGCDefault(pPlot->pAttr->CanvasAttr);
   memset(pPlot->pData,0,sizeof(PLTDATA));
      pPlot->pData->type=MATRIX_FILE;
      pPlot->pData->pName=strdplEx(pList->Glob.pName);
   memset(pPlot->pSlct,0,sizeof(PLTSLCT));
      MkNaNDouble(pPlot->pSlct->xlowb);
      MkNaNDouble(pPlot->pSlct->xuppb);
      MkNaNDouble(pPlot->pSlct->ylowb);
      MkNaNDouble(pPlot->pSlct->yuppb);
      MkNaNDouble(pPlot->pSlct->zlowb);
      MkNaNDouble(pPlot->pSlct->zuppb);
   memset(pPlot->pAxis,0,sizeof(PLTAXIS));
   memset(pPlot->pText,0,sizeof(PLTTEXT));
   memset(pPlot->pUfun,0,sizeof(PLTUFUN));
   memset(pPlot->pXfrm,0,sizeof(PLTXFRM));
      pPlot->pXfrm->norwin.x1=0.2;
      pPlot->pXfrm->norwin.y1=0.2;
      pPlot->pXfrm->norwin.x2=0.8;
      pPlot->pXfrm->norwin.y2=0.8;

   return TRUE;
}

int DoScriptCommandATTR( pList,pAddr ) 
   PLTLIST *pList;
   const char *pAddr;
/*
 attr [genetic|genetic+|moment|area|bar|pie|flat3d]
      [back|nbck]
      [xlin|xlog|xnormal|xseries]
      [ylin|ylog|ynormal]
      [zlin|zlog]
 
      [g.def]
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;
   PLTNODE *pPlot=pList->pTail;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   if (strequ(pS1,"genetic")) 
      pPlot->pAttr->type=PLT2D_GENETIC;
   else if (strequ(pS1,"genetic+")) 
      pPlot->pAttr->type=PLT2D_GENETICPLUS;
   else if (strequ(pS1,"moment")) 
      pPlot->pAttr->type=PLT2D_MOMENT;
   else if (strequ(pS1,"area")) 
      pPlot->pAttr->type=PLT2D_AREA;
   else if (strequ(pS1,"bar")) 
      pPlot->pAttr->type=PLT2D_BAR;
   else if (strequ(pS1,"pie")) 
      pPlot->pAttr->type=PLT2D_PIE;
   else if (strequ(pS1,"flat3d")) 
      pPlot->pAttr->type=PLT2D_FLAT3D;
   else if (strequ(pS1,"back"))
      pPlot->pAttr->back=BACK_TRUE;
   else if (strequ(pS1,"nbck"))
      pPlot->pAttr->back=BACK_FALSE;
   else if (strequ(pS1,"xlin"))
      pPlot->pAttr->xScale=SCALE_LIN;
   else if (strequ(pS1,"ylin"))
      pPlot->pAttr->yScale=SCALE_LIN;
   else if (strequ(pS1,"zlin"))
      pPlot->pAttr->zScale=SCALE_LIN;
   else if (strequ(pS1,"xlog"))
      pPlot->pAttr->xScale=SCALE_LOG10;
   else if (strequ(pS1,"ylog"))
      pPlot->pAttr->yScale=SCALE_LOG10;
   else if (strequ(pS1,"zlog"))
      pPlot->pAttr->zScale=SCALE_LOG10;
   else if (strequ(pS1,"xnormal"))
      pPlot->pAttr->xScale=SCALE_NORM;
   else if (strequ(pS1,"ynormal"))
      pPlot->pAttr->yScale=SCALE_NORM;
   else if (strequ(pS1,"xseries"))
      pPlot->pAttr->xScale=SCALE_SERIES;
   else if (pS1[0]=='g'&&pS1[1]=='.') {
      if (!DoGCAttr(&pPlot->pAttr->CanvasAttr,&(pS1[2]),pS2)) {
         bResult=FALSE;
      }
   } else
      bResult=FALSE;

   free(pString);
   return bResult;
}

int DoScriptCommandDATA( pList,pAddr )  
   PLTLIST *pList;
   const char *pAddr;
/*
 data *[type=file|prev|clone|user|script]
       [file=<d>|"<s>"]
       [xyFile="<s>"]
       [block=*|<d>|<d>,..,<d>] 20030311
       [sortingByX] [rcx]
       [nDenominatorForCDF=<d>]
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;
   PLTNODE *pPlot=pList->pTail;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   if (strequ(pS1,"type")) {
      switch (tolower(*pS2)) {
      case 'f' : pPlot->pData->type=MATRIX_FILE;break;
      case 'p' : pPlot->pData->type=MATRIX_PREVIOUS;break;
      case 'c' : pPlot->pData->type=MATRIX_CLONE;break;
      case 'u' : pPlot->pData->type=MATRIX_USERFUNCTION;break;
      case 's' : pPlot->pData->type=MATRIX_SCRIPT;break;
      }
      goto R;
   }
   
   if (strequ(pS1,"file")) {
      freeEx(pPlot->pData->pName); /* 20030529 */
      if (pPlot->pData->type==MATRIX_SCRIPT &&
         isnumchr(pS2[0])) {
         pPlot->pData->pName=strdplEx(pS2);
      } else {
         pPlot->pData->pName=strdplEx(pS2);
      }
   }
   else if (strequ(pS1,"xyfile"))
      pPlot->pData->pOption=strdplEx(pS2);
   else if (strequ(pS1,"block")) { /* 20030311 */
      int nCol,*vCol;
      if (*pS2=='*') {
         nCol=0;
         vCol=NULL;
      } else {
         GetColIndexArray((const char*)pS2,&nCol,&vCol);
      }
      freeEx(pPlot->pData->vBlockIndex);
      pPlot->pData->nBlockIndex=nCol;
      pPlot->pData->vBlockIndex=vCol;
   }
   else if (strnequ(pS1,"sorting",4))
      pPlot->pData->bColumnSortingByX=TRUE;
   else if (strequ(pS1,"rcx"))
      pPlot->pData->bRowColumnExchange=TRUE;
   else if (strequ(pS1,"nDenominatorForCDF"))
      pPlot->pData->nDenominatorForCDF=atoi(pS2);
   else
      bResult=FALSE;

R: free(pString);
   return bResult;
}

int DoScriptCommandXYZB( pList,pAddr )
  
   PLTLIST *pList;
   const char *pAddr;
/* 
 xyzb  [xlb=*|<f>] [ylb=*|<f>] [zlb=*|<f>]
       [xub=*|<f>] [yub=*|<f>] [zub=*|<f>]
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;
   const char cWild='*';

   PLTNODE *pPlot=pList->pTail;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   if (strequ(pS1,"xlb")) {
      if (*pS2!=cWild) pPlot->pSlct->xlowb=atof(pS2);
   } else if (strequ(pS1,"xub")) {
      if (*pS2!=cWild) pPlot->pSlct->xuppb=atof(pS2);
   } else if (strequ(pS1,"ylb")) {
      if (*pS2!=cWild) pPlot->pSlct->ylowb=atof(pS2);
   } else if (strequ(pS1,"yub")) {
      if (*pS2!=cWild) pPlot->pSlct->yuppb=atof(pS2);
   } else if (strequ(pS1,"zlb")) {
      if (*pS2!=cWild) pPlot->pSlct->zlowb=atof(pS2);
   } else if (strequ(pS1,"zub")) {
      if (*pS2!=cWild) pPlot->pSlct->zuppb=atof(pS2);
   } 
   
   
   free(pString);
   return bResult;
}

int DoScriptCommandSYMB( pList,pAddr )  
   PLTLIST *pList;
   const char *pAddr;
/* 
 slct *[___]                   <--- pDummy against [type=<d|a>]
       [xno=*|<d>|<d>,..,<d>]  <--- "x=1"
       [yno=*|<d>|<d>,..,<d>|<d>,<d>:<d>-<d>]  <--- "y=2"  means 2nd col.
       [zno=*|r<d>|a<d>|<d>,..,<d>] <--- "a":attached, "r":reverse

       [xlb=*|<f>] [ylb=*|<f>] [zlb=*|<f>]
       [xub=*|<f>] [yub=*|<f>] [zub=*|<f>]
       [autoLegend=on|off] <--- Auto Legend Text Generation. 2K.0523

       If nEtc==PLT2D_GENETIC,
          [etc.Range=<f>]
       If nEtc==PLT2D_FLAT3D,
          [etc.ColorMin=<d>|color] [etc.ColorMax=<d>|color]
          [etc.ColorTotal=<d>]
          [etc.Format=<s>][8]
 
      *[type=<d|a>]    <----------- symbol (>0 except -6 for Moment Box)
       [nCopy=<d>]
       [legend=on|off]   <--------- legend
       [symbol=on|off]   <--------- symbol
       [line=on|off]   <----------- line
       [symbol.size=<f>] [pen=<d>]
       [symbol.def] [line.def] <----- gc attr
       [color=<s|d>]     <----------- symb.color & line.color
       [solid|hollow]  <---- solid: symb.stipple=10 & symb.polyarc=2. 2K.0522
                       <--- hollow: symb.stipple=0 & symb.polyarc=0.  2K.0522
       [legend.symbolsize=<f>] 
       [x=*|<f>] [y=*|<f>]
       [legend.txt=<s>] 
       [legend.def]    <----------- text attr
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;
   const char cWild='*';

   PLTNODE *pPlot=pList->pTail;

   int nCol,*vCol,nIndex;
   LEGEND *pLegend;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   pPlot->pSlct->Etc.nType=pPlot->pAttr->type;

   if (strequ(pS1,"____")) {
      goto R;
   } else if (strequ(pS1,"xno")
      ||  strequ(pS1,"yno")
      ||  strequ(pS1,"zno")) {
      if (strchr(pS2,'*')) {
         MkMaxInteger(nCol);
         vCol=NULL;
      } else {
         GetColIndexArray((const char*)pS2,&nCol,&vCol);
      }
      switch (*pS1) {
      case 'x' :
         pPlot->pSlct->xNoTotal=nCol;
         freeEx(pPlot->pSlct->xNo);
         pPlot->pSlct->xNo=vCol;
         break;
      case 'y' :
         pPlot->pSlct->yNoTotal=nCol;
         freeEx(pPlot->pSlct->yNo);
         pPlot->pSlct->yNo=vCol;
         break;
      case 'z' :
         pPlot->pSlct->zNoTotal=nCol;
         freeEx(pPlot->pSlct->zNo);
         pPlot->pSlct->zNo=vCol;
         break;
      }
      goto R;
   } else if (strequ(pS1,"xlb")) {
      if (*pS2!=cWild) pPlot->pSlct->xlowb=atof(pS2);
      goto R;
   } else if (strequ(pS1,"xub")) {
      if (*pS2!=cWild) pPlot->pSlct->xuppb=atof(pS2);
      goto R;
   } else if (strequ(pS1,"ylb")) {
      if (*pS2!=cWild) pPlot->pSlct->ylowb=atof(pS2);
      goto R;
   } else if (strequ(pS1,"yub")) {
      if (*pS2!=cWild) pPlot->pSlct->yuppb=atof(pS2);
      goto R;
   } else if (strequ(pS1,"zlb")) {
      if (*pS2!=cWild) pPlot->pSlct->zlowb=atof(pS2);
      goto R;
   } else if (strequ(pS1,"zub")) {
      if (*pS2!=cWild) pPlot->pSlct->zuppb=atof(pS2);
      goto R;
   } else if (strequ(pS1,"autoLegend")) {
      switch (pS2[1]) {
      case 'n' : case 'N' : pPlot->pSlct->bAutoLegend=TRUE;break;
      case 'f' : case 'F' : pPlot->pSlct->bAutoLegend=FALSE;break;
      default  : bResult=FALSE;break;
      }
      goto R;
   /* } else if (strequ(pS1,"nEtc")) {
      pPlot->pSlct->Etc.nType=(int)atof(pS2);
      goto R; */
   } else if (strequ(pS1,"etc.Range")) {
      if (pPlot->pSlct->Etc.nType!=PLT2D_MOMENT) goto R;
      pPlot->pSlct->Etc.LineMoment.dRange=atof(pS2);
      goto R;
   } else if (strequ(pS1,"etc.ColorMin")) {
      if (pPlot->pSlct->Etc.nType!=PLT2D_FLAT3D) goto R;
      pPlot->pSlct->Etc.Flat3D.nColorMin=isdigit(*pS2) ? atoi(pS2):GEColorByName(NULL,pS2);
      if (pPlot->pSlct->Etc.Flat3D.nColorMin<0) return FALSE;
      goto R;
   } else if (strequ(pS1,"etc.ColorMax")) {
      if (pPlot->pSlct->Etc.nType!=PLT2D_FLAT3D) goto R;
      pPlot->pSlct->Etc.Flat3D.nColorMax=isdigit(*pS2) ? atoi(pS2):GEColorByName(NULL,pS2);
      if (pPlot->pSlct->Etc.Flat3D.nColorMax<0) return FALSE;
      goto R;
   } else if (strequ(pS1,"etc.ColorTotal")) {
      if (pPlot->pSlct->Etc.nType!=PLT2D_FLAT3D) goto R;
      pPlot->pSlct->Etc.Flat3D.nColorTotal=atoi(pS2);
      goto R;
   } else if (strequ(pS1,"etc.Format")) {
      if (pPlot->pSlct->Etc.nType!=PLT2D_FLAT3D) goto R;
      strncpy(
         pPlot->pSlct->Etc.Flat3D.qFormat,
         pS2,
         noof(pPlot->pSlct->Etc.Flat3D.qFormat));
      goto R;
   }
   
   if (strequ(pS1,"type")) {
      nIndex=pPlot->pSlct->nLegendTotal++; /* At first pPlot->pSlct->nLegendTotal=0 */
      pS1=(char*)salloc(LEGEND,pPlot->pSlct->nLegendTotal);
      if (pPlot->pSlct->nLegendTotal>1) {
         memcpy(pS1,(char*)pPlot->pSlct->pLegend,sizeof(LEGEND)*nIndex);
         free(pPlot->pSlct->pLegend);
      }
      pPlot->pSlct->pLegend=(LEGEND*)pS1;
      memset((char*)&(pPlot->pSlct->pLegend[nIndex]),0,sizeof(LEGEND));
      pPlot->pSlct->pLegend[nIndex].dLegendSize=DEFAULT_PLOT_LEGEND_SIZE;
      pPlot->pSlct->pLegend[nIndex].dSymbSize=DEFAULT_PLOT_SYMBOL_SIZE;
      pPlot->pSlct->pLegend[nIndex].bLegendOn=1;
      pPlot->pSlct->pLegend[nIndex].bSymbolOn=1;
      pPlot->pSlct->pLegend[nIndex].bLineOn=1;
      pPlot->pSlct->pLegend[nIndex].nPen=1;
      MkNaNDouble(pPlot->pSlct->pLegend[nIndex].x); /* 2001.0815 */
      MkNaNDouble(pPlot->pSlct->pLegend[nIndex].y);
      GESetGCDefault(LgndGCLineAttr(nIndex));
      GESetGCDefault(LgndGCSymbAttr(nIndex));
      SetGRFontDefault(LgndFontAttr(nIndex));
      if (isalpha(*pS2))
         pPlot->pSlct->pLegend[nIndex].nType=
         toupper(*pS2)-'A'+STROKESYMB_INDEX_OF_ALPHA;
      else
         pPlot->pSlct->pLegend[nIndex].nType=(int)atof(pS2);
      goto R;
   } else {
      nIndex=pPlot->pSlct->nLegendTotal-1;
      if (nIndex<0) {
         bResult=FALSE;
         goto R;
      }
   }

   pLegend=&(pPlot->pSlct->pLegend[nIndex]);

   if (strequ(pS1,"nCopy"))
      pLegend->nCopy=(int)atof(pS2);
   else if (strequ(pS1,"legend")) {
      switch (pS2[1]) {
      case 'n' : case 'N' : pLegend->bLegendOn=1;break;
      case 'f' : case 'F' : pLegend->bLegendOn=0;break;
      default  : bResult=FALSE;break;
      }
   }
   else if (strequ(pS1,"symbol")) {
      switch (pS2[1]) {
      case 'n' : case 'N' : pLegend->bSymbolOn=1;break;
      case 'f' : case 'F' : pLegend->bSymbolOn=0;break;
      default  : bResult=FALSE;break;
      }
   }
   else if (strequ(pS1,"line")) {
      switch (pS2[1]) {
      case 'n' : case 'N' : pLegend->bLineOn=1;break;
      case 'f' : case 'F' : pLegend->bLineOn=0;break;
      default  : bResult=FALSE;break;
      }
   }
   else if (strequ(pS1,"symbol.size"))
      pLegend->dSymbSize=atof(pS2);
   else if (strequ(pS1,"pen"))
      pLegend->nPen=(int)atof(pS2);
   else if (!strncmp(pS1,"symbol.",7))
      bResult=DoGCAttr(&LgndGCSymbAttr(nIndex),&(pS1[7]),pS2) ? TRUE:FALSE;
   else if (!strncmp(pS1,"line.",5))
      bResult=DoGCAttr(&LgndGCLineAttr(nIndex),&(pS1[5]),pS2) ? TRUE:FALSE;
   else if (strequ(pS1,"color")) {
      bResult=DoGCAttr(&LgndGCSymbAttr(nIndex),pS1,pS2) ? TRUE:FALSE;
      if (bResult)
      bResult=DoGCAttr(&LgndGCLineAttr(nIndex),pS1,pS2) ? TRUE:FALSE;
   }
   else if (strequ(pS1,"solid")) { /* 2K.0522 */
      DoGCAttr(&LgndGCSymbAttr(nIndex),"stipple","10");
      DoGCAttr(&LgndGCSymbAttr(nIndex),"polyarc","2");
   }
   else if (strequ(pS1,"hollow")) { /* 2K.0522 */
      DoGCAttr(&LgndGCSymbAttr(nIndex),"stipple","0");
      DoGCAttr(&LgndGCSymbAttr(nIndex),"polyarc","0");
   }
   else if (strequ(pS1,"legend.symbolsize"))
      pLegend->dLegendSize=atof(pS2);
   else if (strequ(pS1,"x")) {
      if (isnumstr(pS2)) pLegend->x=atof(pS2);
      else MkNaNDouble(pLegend->x); /* 2001.0815 */
   }
   else if (strequ(pS1,"y")) {
      if (isnumstr(pS2)) pLegend->y=atof(pS2);
      else MkNaNDouble(pLegend->y); /* 2001.0815 */
   }
   else if (strequ(pS1,"legend.txt"))
      pLegend->pText=strdplEx(pS2);
   else if (strnequ(pS1,"legend.",7))
      bResult=DoFontAttr(&LgndFontAttr(nIndex),&(pS1[7]),pS2) ? TRUE:FALSE;
   else
      bResult=FALSE;

R: free(pString);
   return bResult;
}

int DoScriptCommandAXIS( pList,pAddr )  
   PLTLIST *pList;
   const char *pAddr;
/*
 axis *[type=<x|y|z>]
  
       [loc=Lower-bound|Middle|Upper-bound|Any]
       [loc.x=<f>|(<f>,<f>)] [loc.y=<f>|(<f>,<f>)]

       [axle=on|off]
       [axle.def]                        <--- line (axis & tick) gc attr

       [tickmajor=on|off] 
       [tickminor=on|off] 
       [tickmajor.loc=Inside|Outside|Cross]
       [tickminor.loc=Inside|Outside|Cross]
       [tickmajor.step=<f>]
       [tickminor.step=<f>]
       
       [gridmajor=on|off]
       [gridminor=on|off]
       [gridmajor.def]                  <--- major grid gc attr
       [gridminor.def]                  <--- minor grid gc attr
 
       [label=on|off]
       [label.org=Tick|Space|byUser]
       [label.format=<c>] [label.eq=<c>]
       [label.def]                      <--- label text attr
   
       [title=<s>]
       [title.show=t|f|true|false]  20030304
       [title.spaceFactor=<f>]  <----------- distance from the axis by the
                                number which is multiplied by largeTickSize.
       [title.def]                   <------ title text attr
 */
{
   DLL *l;
   DLN *n;
   PLTNODE *pPlot=pList->pTail;
   char *pS1,*pS2,bDone=TRUE;
   static PAXIS **ppAx=NULL;
   int nIndex=0;

   DLLOpen(&l);
   if (!DLLGetTokensV1(l,pAddr,qPltTokenOption)) goto T;
   DLLDelCommentNode(l,PLOTSCRIPT_COMMENT_CHAR);
   n=l->head;
   if (!n) goto T;
   do {
      TokenSplitter(n->tok,&pS1,&pS2);

      if (strequ(pS1,"type")) { /* SHOULD BE FIRST */
         switch(tolower((int)*pS2)) {
         case 'x' :
            if (pPlot->pAxis->xTotal>=noof(pPlot->pAxis->xAxis)) goto T;            
            nIndex=pPlot->pAxis->xTotal++;
            ppAx=pPlot->pAxis->xAxis;
            break;
         case 'y' :
            if (pPlot->pAxis->yTotal>=noof(pPlot->pAxis->yAxis)) goto T;
            nIndex=pPlot->pAxis->yTotal++;
            ppAx=pPlot->pAxis->yAxis;
            break;
         case 'z' :
            if (pPlot->pAxis->zTotal>=noof(pPlot->pAxis->zAxis)) goto T;
            nIndex=pPlot->pAxis->zTotal++;
            ppAx=pPlot->pAxis->zAxis;
            break;
         default  : goto F;
         }
         if (!ppAx[nIndex]) {
            ppAx[nIndex]=salloc(PAXIS,1);
            memset(ppAx[nIndex],0,sizeof(PAXIS));
            ppAx[nIndex]->bAxisOn=TRUE;
            ppAx[nIndex]->bTickMajorOn=TRUE;
            ppAx[nIndex]->bTickMinorOn=TRUE;
            ppAx[nIndex]->bLabelOn=TRUE;
            ppAx[nIndex]->bGridMajorOn=FALSE;
            ppAx[nIndex]->bGridMinorOn=FALSE;
            ppAx[nIndex]->AxisAttr=AXIS_ATLOWERBOUND;
            ppAx[nIndex]->TickMajorAttr=TICK_INSIDE;
            ppAx[nIndex]->TickMinorAttr=TICK_INSIDE;
            ppAx[nIndex]->LabelAttr=LABEL_BYTICKNUMBER;
            ppAx[nIndex]->pLabelFormat=strdplEx("%1.3g");
            ppAx[nIndex]->pLabelEquation=0;
            ppAx[nIndex]->pTitle=0;
            ppAx[nIndex]->bTitleShow=TRUE;
            ppAx[nIndex]->dTitleSpaceFactor=4.0;
            SetGRFontDefault(ppAx[nIndex]->TitleFontAttr);
            GESetGCDefault(ppAx[nIndex]->AxisGCAttr);
            ppAx[nIndex]->AxisGCAttr.gc_type=GE_GCLine; 
            ppAx[nIndex]->AxisGCAttr.gc_mask=GE_GCMaskLineDefault; 
            GESetGCDefault(ppAx[nIndex]->GridGCMajorAttr);
            ppAx[nIndex]->GridGCMajorAttr.gc_type=GE_GCLine; 
            ppAx[nIndex]->GridGCMajorAttr.gc_mask=GE_GCMaskLineDefault; 
            ppAx[nIndex]->GridGCMajorAttr.foreground=GEColorByName(NULL,"gray25"); 
            GESetGCDefault(ppAx[nIndex]->GridGCMinorAttr);
            ppAx[nIndex]->GridGCMinorAttr.gc_type=GE_GCLine; 
            ppAx[nIndex]->GridGCMinorAttr.gc_mask=GE_GCMaskLineDefault; 
            ppAx[nIndex]->GridGCMinorAttr.foreground=GEColorByName(NULL,"gray100"); 
            SetGRFontDefault(ppAx[nIndex]->FontAttr);
            SetGRFontDefault(ppAx[nIndex]->TitleFontAttr);
         }
         continue;
      }

      if (!ppAx) goto F;
      if (ppAx==pPlot->pAxis->xAxis) nIndex=pPlot->pAxis->xTotal-1;
      else if (ppAx==pPlot->pAxis->yAxis) nIndex=pPlot->pAxis->yTotal-1;
      else if (ppAx==pPlot->pAxis->zAxis) nIndex=pPlot->pAxis->zTotal-1;
      if (nIndex<0) goto F;

      if (strequ(pS1,"loc")) 
         switch (tolower(pS2[0])) {
         case 'l' : ppAx[nIndex]->AxisAttr=AXIS_ATLOWERBOUND;break;
         case 'm' : ppAx[nIndex]->AxisAttr=AXIS_ATMIDDLE;break;
         case 'u' : ppAx[nIndex]->AxisAttr=AXIS_ATUPPERBOUND;break;
         case 'a' : ppAx[nIndex]->AxisAttr=AXIS_ATANYPOSITION;break;
         default  : bDone=FALSE;break;
         }
      else if (strequ(pS1,"loc.x")) {
         if (*pS2=='(') {
            pS2++;
            if (!(pS2=strtok(pS2,",)")))
               goto F;
            ppAx[nIndex]->dAxisX1=atof(pS2);
            if (!(pS2=strtok(NULL,",)")))
               goto F;
            ppAx[nIndex]->dAxisX2=atof(pS2);
         } else {
            ppAx[nIndex]->dAxisX1=atof(pS2);
            ppAx[nIndex]->dAxisX2=atof(pS2);
         }
      } else if (strequ(pS1,"loc.y")) {
         if (*pS2=='(') {
            pS2++;
            if (!(pS2=strtok(pS2,",)")))
               goto F;
            ppAx[nIndex]->dAxisY1=atof(pS2);
            if (!(pS2=strtok(NULL,",)")))
               goto F;
            ppAx[nIndex]->dAxisY2=atof(pS2);
         } else {
            ppAx[nIndex]->dAxisY1=atof(pS2);
            ppAx[nIndex]->dAxisY2=atof(pS2);
         }
      }
      else if (strequ(pS1,"axle"))
         switch (tolower(pS2[1])) {
         case 'n' : ppAx[nIndex]->bAxisOn=TRUE;break;
         case 'f' : ppAx[nIndex]->bAxisOn=FALSE;break;
         default  : bDone=FALSE;break;
         }
      else if (strnequ(pS1,"axle.",5))
         bDone=DoGCAttr(&(ppAx[nIndex]->AxisGCAttr),&(pS1[5]),pS2);
      else if (strequ(pS1,"tickmajor"))
         switch (tolower(pS2[1])) {
         case 'n' : ppAx[nIndex]->bTickMajorOn=TRUE;break;
         case 'f' : ppAx[nIndex]->bTickMajorOn=FALSE;break;
         default  : bDone=FALSE;break;
         }
      else if (strequ(pS1,"tickminor"))
         switch (tolower(pS2[1])) {
         case 'n' : ppAx[nIndex]->bTickMinorOn=TRUE;break;
         case 'f' : ppAx[nIndex]->bTickMinorOn=FALSE;break;
         default  : bDone=FALSE;break;
         }
      else if (strequ(pS1,"tickmajor.loc")) 
         switch (tolower(pS2[0])) {
         case 'i' : ppAx[nIndex]->TickMajorAttr=TICK_INSIDE;break;
         case 'o' : ppAx[nIndex]->TickMajorAttr=TICK_OUTSIDE;break;
         case 'c' : ppAx[nIndex]->TickMajorAttr=TICK_CROSS;break;
         default  : bDone=FALSE;break;
         }
      else if (strequ(pS1,"tickminor.loc")) 
         switch (tolower(pS2[0])) {
         case 'i' : ppAx[nIndex]->TickMinorAttr=TICK_INSIDE;break;
         case 'o' : ppAx[nIndex]->TickMinorAttr=TICK_OUTSIDE;break;
         case 'c' : ppAx[nIndex]->TickMinorAttr=TICK_CROSS;break;
         default  : bDone=FALSE;break;
         }
      else if (strequ(pS1,"tickmajor.step"))
         ppAx[nIndex]->dTickMajorStep=atof(pS2);
      else if (strequ(pS1,"tickminor.step"))
         ppAx[nIndex]->dTickMinorStep=atof(pS2);
      else if (strequ(pS1,"gridmajor"))
         switch (tolower(pS2[1])) {
         case 'n' : ppAx[nIndex]->bGridMajorOn=TRUE;break;
         case 'f' : ppAx[nIndex]->bGridMajorOn=FALSE;break;
         default  : bDone=FALSE;break;
         }
      else if (strequ(pS1,"gridminor"))
         switch (tolower(pS2[1])) {
         case 'n' : ppAx[nIndex]->bGridMinorOn=TRUE;break;
         case 'f' : ppAx[nIndex]->bGridMinorOn=FALSE;break;
         default  : bDone=FALSE;break;
         }
      else if (strnequ(pS1,"gridmajor.",10))
         bDone=DoGCAttr(&(ppAx[nIndex]->GridGCMajorAttr),&(pS1[10]),pS2);
      else if (strnequ(pS1,"gridminor.",10))
         bDone=DoGCAttr(&(ppAx[nIndex]->GridGCMinorAttr),&(pS1[10]),pS2);
      else if (strequ(pS1,"label"))
         switch (tolower(pS2[1])) {
         case 'n' : ppAx[nIndex]->bLabelOn=TRUE;break;
         case 'f' : ppAx[nIndex]->bLabelOn=FALSE;break;
         default  : bDone=FALSE;break;
         }
      else if (strequ(pS1,"label.org"))
         switch (tolower(pS2[0])) {
         case 't' : ppAx[nIndex]->LabelAttr=LABEL_BYTICKNUMBER;break;
         case 's' : ppAx[nIndex]->LabelAttr=LABEL_BYTICKSPACE;break;
         case 'u' : ppAx[nIndex]->LabelAttr=LABEL_BYUSER;break;
         default  : bDone=FALSE;break;
         }
      else if (strequ(pS1,"label.format"))
         ppAx[nIndex]->pLabelFormat=strdplEx(pS2);
      else if (strequ(pS1,"label.eq"))
         ppAx[nIndex]->pLabelEquation=strdplEx(pS2);
      else if (strnequ(pS1,"label.",6))
         bDone=DoFontAttr(&(ppAx[nIndex]->FontAttr),&(pS1[6]),pS2);
      else if (strequ(pS1,"title"))
         ppAx[nIndex]->pTitle=strdplEx(pS2);
      else if (strequ(pS1,"title.show"))
         switch (tolower(pS2[0])) {
         case 't' : ppAx[nIndex]->bTitleShow=TRUE;break;
         case 'f' : ppAx[nIndex]->bTitleShow=FALSE;break;
         }
      else if (strequ(pS1,"title.spaceFactor"))
         ppAx[nIndex]->dTitleSpaceFactor=atof(pS2);
      else if (strnequ(pS1,"title.",6))
         bDone=DoFontAttr(&(ppAx[nIndex]->TitleFontAttr),&(pS1[6]),pS2);
      else
         goto F;
      if (!bDone)
         goto F;
   } while (n=n->next);
T: DLLClose(l);
   return TRUE;
F: DLLClose(l);
   return FALSE;
}

int DoScriptCommandTEXT( pList,pAddr )  
   PLTLIST *pList;
   const char *pAddr;
/*
 text *[type=<d>] 
       [x=<f>] [y=<f>] [txt=<s>]
       [t.def] <-------------------- text attr
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;
   PLTNODE *pPlot=pList->pTail;
   int nIndex;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   if (strequ(pS1,"type")) /* SHOULD BE FIRST */
   {
      nIndex=pPlot->pText->nTotal++; /* First pPlot->pText->nTotal=0 */
      if (nIndex>=noof(pPlot->pText->qText)) {
         pPlot->pText->nTotal--;
         goto R;
      }
      if (!pPlot->pText->qText[nIndex]) {
         pPlot->pText->qText[nIndex]=salloc(PTEXT,1);
         memset(pPlot->pText->qText[nIndex],0,sizeof(PTEXT));
         SetGRFontDefault(pPlot->pText->qText[nIndex]->FontAttr);
      }
      pPlot->pText->qText[nIndex]->nType=(int)atof(pS2);
      goto R;
   }

   nIndex=pPlot->pText->nTotal-1; /* 2000.0409 */
   if (nIndex<0) goto R;

   if (strequ(pS1,"x"))
      pPlot->pText->qText[nIndex]->x=atof(pS2);
   else if (strequ(pS1,"y"))
      pPlot->pText->qText[nIndex]->y=atof(pS2);
   else if (strequ(pS1,"txt"))
      pPlot->pText->qText[nIndex]->pString=strdplEx(pS2);
   else if (pS1[0]=='t'&&pS1[1]=='.') 
      bResult=DoFontAttr(&(pPlot->pText->qText[nIndex]->FontAttr),&(pS1[2]),pS2);
   else
      bResult=FALSE;

R: free(pString);
   return bResult;
}

int DoScriptCommandUFUN( pList,pAddr )  
   PLTLIST *pList;
   const char *pAddr;
/*
 ufun *[type=<s>] [option=<i>|<c>] [suboption|unit=<i>]
       [nrl=<i>] [nrh=<i>] [ncl=<i>] [nch=<i>]
       [argument1|argument|model=<s>]
       [argument2|xy|xyz|xyv|xyt=(<f>,<f>)...(<f>,<f>)|(<f>,<f>,<f>)...(<f>,<f>,<f>)]
       [argument3=<s>]  <---- general purpose
       [argument4=<s>]  <---- another purpose -_- 20030906
       [sweep|range=<f>,..,<f>] <------- start,stop,step
       [rline=on|off]  <---------- line result
       [rtext=on|off] <----------- text result
  
       [rline.def] <-------------- line gc attr
       [rtext.def] <-------------- text attr
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;
   PLTNODE *pPlot=pList->pTail;
   PUFUN *pUfun=NULL;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   if (strequ(pS1,"type")) { /* SHOULD BE FIRST */
      pUfun=salloc(PUFUN,1);
      memset(pUfun,0,sizeof(PUFUN));
      pUfun->pType=strdpl(pS2);
      pUfun->bLineOn=TRUE;
      pUfun->bTableOn=TRUE;
      GESetGCDefault(pUfun->GCAttr);
      SetGRFontDefault(pUfun->FontAttr);
      AnyAddSLObject(pPlot->pUfun,pUfun);
      goto R;
   }

   pUfun=pPlot->pUfun->pTail;
   if (!pUfun) {
      bResult=FALSE;
      goto R;
   }

   if (strequ(pS1,"option")) /* 20030212 */
      pUfun->nOption=isnumber(pS2) ? (int)atof(pS2):(int)pS2[0];
   else if (strequ(pS1,"suboption")||strequ(pS1,"unit")) /* 20030212,040315 */
      pUfun->nSubOption=isnumber(pS2) ? (int)atof(pS2):(int)(*pS2);
   else if (strequ(pS1,"nrl"))
      pUfun->nrl=(int)atof(pS2);
   else if (strequ(pS1,"nrh"))
      pUfun->nrh=(int)atof(pS2);
   else if (strequ(pS1,"ncl"))
      pUfun->ncl=(int)atof(pS2);
   else if (strequ(pS1,"nch"))
      pUfun->nch=(int)atof(pS2);
   else if (strequ(pS1,"argument1")||strequ(pS1,"argument")||strequ(pS1,"model")) {
      freeEx(pUfun->pArgument);
      pUfun->pArgument=strdplEx(pS2);
   }
   else if (strequ(pS1,"argument2")|| /* 20030904 */
      strequ(pS1,"xy")||strequ(pS1,"xyz")||  /* 20030622 */
      strequ(pS1,"xyv")||strequ(pS1,"xyt")) { /* 20031230 */
      freeEx(pUfun->pArgument2);
      pUfun->pArgument2=strdplEx(pS2);
   }
   else if (strequ(pS1,"argument3")) {
      freeEx(pUfun->pArgument3);
      pUfun->pArgument3=strdplEx(pS2);
   }
   else if (strequ(pS1,"argument4")) {
      freeEx(pUfun->pArgument4);
      pUfun->pArgument4=strdplEx(pS2);
   }
   else if (strequ(pS1,"sweep")||strequ(pS1,"range")) {
      freeEx(pUfun->pSweep);
      pUfun->pSweep=strdplEx(pS2);
   }
   else if (strequ(pS1,"rline")) {
      switch (pS2[1]) {
      case 'n' : case 'N' :pUfun->bLineOn=TRUE;break;
      case 'f' : case 'F' :pUfun->bLineOn=FALSE;break;
      }
   }
   else if (strequ(pS1,"rtext")) {
      switch (pS2[1]) {
      case 'n' : case 'N' :pUfun->bTableOn=TRUE;break;
      case 'f' : case 'F' :pUfun->bTableOn=FALSE;break;
      }
   }
   else if (strnequ(pS1,"rline.",6))
      bResult=DoGCAttr(&pUfun->GCAttr,&(pS1[6]),pS2);
   else if (strnequ(pS1,"rtext.",6))
      bResult=DoFontAttr(&pUfun->FontAttr,&(pS1[6]),pS2);
   else
      bResult=FALSE;

R: free(pString);
   return bResult;
}

int DoScriptCommandVIEW( pList,pAddr )
   PLTLIST *pList;
   const char *pAddr;
/*
 view [x1=<d>] [y1=<d>] [x2=<d>] [y2=<d>] 
 */
{
   int bResult=TRUE;
   char *pString,*pS1,*pS2;
   PLTNODE *pPlot=pList->pTail;

   if (!*pAddr) return bResult;
   pString=strdpl(pAddr);
   TokenSplitter(pString,&pS1,&pS2);

   if (strequ(pS1,"x1")) 
      pPlot->pXfrm->norwin.x1=atof(pS2);
   else if (strequ(pS1,"y1")) 
      pPlot->pXfrm->norwin.y1=atof(pS2);
   else if (strequ(pS1,"x2")) 
      pPlot->pXfrm->norwin.x2=atof(pS2);
   else if (strequ(pS1,"y2")) 
      pPlot->pXfrm->norwin.y2=atof(pS2);
   else
      bResult=FALSE;

   free(pString);
   return bResult;
}

int DoScriptCommandError( nLineNo,qString )
   int nLineNo;
   const char *qString;
{
   Echo(0, /* 20030223 */
      "Error, invalid syntax \"%s\" found \n"
      "at line %d of the script file.",
      qString,nLineNo);
   return FALSE;
}

char *GRGetErrorMessage() /* Y.Kim,20030215 */
{
   return gpGRErrorLog;
}

#if defined(_MSC_)
int Echo( char *pFirst, ... ) /* char*,char*,...,NULL */
/* 20030429
 * Echo(0,2) -> turn on printing outside.
 * Echo(0,1) -> turn on printing inside.
 * Echo(0,-1) -> turn off messaging inside.
 * Echo(0,-2) -> turn off messaging outside.
 * Echo(0,char*) -> error message.
 * Echo(char*) -> general message.
 */
{
   static int bEcho=TRUE,bEchoOutside=TRUE;
   va_list ap;
   char qBuffer[1024];
   int nBuffer,bError;

   nBuffer=noof(qBuffer);
   va_start(ap,pFirst);
   if (!pFirst) {
      pFirst=va_arg(ap,char *);
      switch ((int)pFirst) {
      case  2 : bEchoOutside=TRUE;return TRUE;
      case  1 : bEcho=TRUE; return TRUE;
      case -1 : bEcho=FALSE;return TRUE;
      case -2 : bEchoOutside=FALSE;return TRUE;
      case  0 : return FALSE;
      }
      bError=TRUE;
   } else
      bError=FALSE; /* 20030615 */

   if (!bEcho) return TRUE; /* 20030429 */

   _vsnprintf(qBuffer,nBuffer-1,pFirst,ap);
   qBuffer[nBuffer-1]=0;
   /* 20030215 */
   if (bError) {
      char *pNew;
      if (gpGRErrorLog) {
         pNew=strvcat(gpGRErrorLog,qBuffer,0);
         freeEx(gpGRErrorLog);
      } else {
         pNew=strdpl(qBuffer);
      }
      gpGRErrorLog=pNew;
   }
   va_end(ap);

   if (!gpGRLog)
      gpGRLog=strdpl(qBuffer);
   else {
      char *pAddr=gpGRLog;
      gpGRLog=strvcat(
         pAddr,
         bError ? "\n-_- -_- -_- -_- -_- -_- -_- -_- -_- -_-\n":"", 
         qBuffer,
         0);
      free(pAddr);
   }
   if (bEchoOutside && pEchoAbroad) (*pEchoAbroad)((const char*)qBuffer);

   return strlen(gpGRLog);
}
#elif defined(_UNIXC_) || defined(_HP715C_)
int Echo( va_alist ) /* char*,char*,NULL */
   va_dcl
{
   va_list args;
   char *fmt,pBuffer[1024],*b;
   int nIndex;
 
   if (!pFILEGRLog) {
      sprintf(buf,"%s.log",fGRLogName);
      pFILEGRLog=fopen(buf,"w");
   }
   va_start(args,fmt);
   fmt=va_arg(args,char *);
   vsprintf(pBuffer,fmt,args);
   for (nIndex=0,b=pBuffer;nIndex<(int)strlen(pBuffer);nIndex++) {
      if (*b=='\n') {
         fprintf(pFILEGRLog,"\n ---> ");
      } else {
         fprintf(pFILEGRLog,"%c",*b);
      }
      b++;
   }
   va_end(args);
   return TRUE;
}
#else
#error Compiler type (_MSC_,_UNIXC_,...) should be defined.
#endif

/******************************************************************************/
/* plotio.c */