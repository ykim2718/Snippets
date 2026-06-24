/******************************************************************************/
/*                           file name : geWindowMS.c                         */
/*                    descriptive name : Microsoft Window Tools               */
/*                         environment : MS-Window95                          */
/*                            compiler : Visual C++ 6.0                       */
/*                            producer : Kim,YongShik                         */
/*                             version : 1.0                                  */
/*                       creating date : 43310222-43290222                    */
/* 4332 0225-0431,0706,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0119-0127,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4334 0220,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4336 0305-0306,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#if defined(_MSWINDOW_)
/******************************************************************************/

#include <conio.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include "myCore.h"
#include "any.h"
#include "blob.h"
#include "str.h"
#include "gecore.h"
#include "tools.h"
#include "number.h"
#include "geWindow.h"

static IPTRFN myArc;

/*----------------------------------------------------------------------------*/

#define DEFAULT_GR_FONT_NAME "Arial Narrow"
static int myDashLine();

/******************************************************************************/

int GEOpen( MYDISPLAY **myDisplay,char *GC,float metricScale,char* window )
{
   MYDISPLAY *my;

   my=(MYDISPLAY*)malloc(sizeof(MYDISPLAY));
   my->metricScale=metricScale;
   my->window=(HWND)window;
   myAlloGC(my,GC);
   *myDisplay=my;
   return TRUE;
}

int GEClose( MYDISPLAY *myDisplay )
{
   myFreeGC(myDisplay);
   free(myDisplay); /* 2001.0220 */
   return (int)TRUE;
}

int myAlloGC( MYDISPLAY *myDisplay,char *globalGC )
{
/*   BLOBGC gc; 20030310 */
   HDC hDC;
   HFONT hFont;
   
   myDisplay->gc[GE_GCPoint]=
   myDisplay->gc[GE_GCLine]=
   myDisplay->gc[GE_GCPolygonL]=
   myDisplay->gc[GE_GCPolygon]=
   myDisplay->gc[GE_GCTextL]=
   myDisplay->gc[GE_GCText]=(HDC)globalGC;
   /*
   if (globalGC) {  
   } else {
      for (i=0;i<GE_GCTotal;i++) {   
         myDisplay->gc[i]=GetDC(myDisplay->window);
         // CreateCompatibleDC() ?????
         // SaveDC()
      }
   }
   */

   /* 20030310
   GESetGCDefault(gc);
   gc.gc_type=GE_GCPoint;
   gc.gc_mask=GE_GCMaskLineDefault;
   myChangeGC(myDisplay,&gc);
   gc.gc_type=GE_GCLine;
   gc.gc_mask=GE_GCMaskLineDefault;
   myChangeGC(myDisplay,&gc);
   gc.gc_type=GE_GCPolygonL;
   gc.gc_mask=GE_GCMaskLineDefault;
   myChangeGC(myDisplay,&gc);
   gc.gc_type=GE_GCPolygon;
   gc.gc_mask=GE_GCMaskFillDefault;
   myChangeGC(myDisplay,&gc);
   gc.gc_type=GE_GCTextL;
   gc.gc_mask=GE_GCMaskLineDefault;
   myChangeGC(myDisplay,&gc);
   gc.gc_type=GE_GCText;
   gc.gc_mask=GE_GCMaskFillDefault;
   myChangeGC(myDisplay,&gc);
   */

   hDC=myDisplay->gc[GE_GCText];
   hFont=CreateFont(12,0,0,0,
         FW_NORMAL,FALSE,FALSE,
         //FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
         FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,0x40,
         DEFAULT_QUALITY, VARIABLE_PITCH | FF_DONTCARE,DEFAULT_GR_FONT_NAME);
   DeleteObject(SelectObject(hDC,hFont));
   SetBkMode(hDC,TRANSPARENT);
   return TRUE;
}

int myFreeGC( MYDISPLAY* myDisplay )
{
   DeleteObject(SelectObject(myDisplay->gc[GE_GCPoint],GetStockObject(NULL_PEN)));
   DeleteObject(SelectObject(myDisplay->gc[GE_GCLine],GetStockObject(NULL_PEN)));
   DeleteObject(SelectObject(myDisplay->gc[GE_GCPolygonL],GetStockObject(NULL_PEN)));
   DeleteObject(SelectObject(myDisplay->gc[GE_GCPolygon],GetStockObject(NULL_BRUSH)));
   DeleteObject(SelectObject(myDisplay->gc[GE_GCTextL],GetStockObject(NULL_PEN)));
   DeleteObject(SelectObject(myDisplay->gc[GE_GCText],GetStockObject(NULL_BRUSH)));
   DeleteObject(SelectObject(myDisplay->gc[GE_GCText],GetStockObject(SYSTEM_FONT)));
   ReleaseDC(myDisplay->window,myDisplay->gc[GE_GCPoint]);
   ReleaseDC(myDisplay->window,myDisplay->gc[GE_GCLine]);
   ReleaseDC(myDisplay->window,myDisplay->gc[GE_GCPolygonL]);
   ReleaseDC(myDisplay->window,myDisplay->gc[GE_GCPolygon]);
   ReleaseDC(myDisplay->window,myDisplay->gc[GE_GCTextL]);
   ReleaseDC(myDisplay->window,myDisplay->gc[GE_GCText]);
   return TRUE;
}

int myChangeGC(MYDISPLAY *myDisplay,
               BLOBGC *gc)
{
   HDC hDC=myDisplay->gc[gc->gc_type];
   HPEN hPen;
   LOGPEN logPen;
   EXTLOGPEN *pExtLogPen; /* 20030310 ^^Y */
   HBRUSH hBrush;
   LOGBRUSH logBrush;
   HFONT hFont;
   int nCount,aDashSizes[4],nDashSizes,bUserStyle;

   if (!gc->gc_mask)
      return TRUE;

   /* GE_GCMaskFunction */
   if (gc->gc_mask&GE_GCMaskFunction) {
      switch (gc->function) {
      case GE_FnClear        :                             break;
      case GE_FnAnd          :                             break;
      case GE_FnAndReverse   :                             break;
      case GE_FnCopy         : SetROP2(hDC,R2_COPYPEN);    break;
      case GE_FnAndInverted  :                             break;
      case GE_FnNoOp         : SetROP2(hDC,R2_NOP);        break;
      case GE_FnXor          : SetROP2(hDC,R2_XORPEN);     break;
      case GE_FnOr           :                             break;
      case GE_FnNor          :                             break;
      case GE_FnEquiv        :                             break;
      case GE_FnInvert       : SetROP2(hDC,R2_NOT);        break;
      case GE_FnOrReverse    :                             break;
      case GE_FnCopyInverted : SetROP2(hDC,R2_NOTCOPYPEN); break;
      case GE_FnOrInverted   :                             break;
      case GE_FnNand         :                             break;
      case GE_FnSet          :                             break;
      }
   }
   /* GE_GCMaskPlaneMask */
   if (gc->gc_mask&GE_GCMaskPlaneMask) {
      ;
   }
   /* GE_GCMaskForeground */
   if (gc->gc_mask&GE_GCMaskForeground) {
      if (gc->gc_type==GE_GCLine
      ||  gc->gc_type==GE_GCPolygonL
      ||  gc->gc_type==GE_GCTextL) {
         hPen=SelectObject(hDC,GetStockObject(NULL_PEN));
         GetObject(hPen,sizeof(LOGPEN),(LPVOID)&logPen);
         DeleteObject(hPen);
         logPen.lopnColor=gc->foreground;
         DeleteObject(SelectObject(hDC,CreatePenIndirect(&logPen)));
      } else
      if (gc->gc_type==GE_GCPolygon
      ||  gc->gc_type==GE_GCText) {
         hBrush=SelectObject(hDC,GetStockObject(WHITE_BRUSH));
         GetObject(hBrush,sizeof(LOGBRUSH),(LPVOID)&logBrush);
         DeleteObject(hBrush);
         logBrush.lbColor=gc->foreground;
         DeleteObject(SelectObject(hDC,CreateBrushIndirect(&logBrush)));
         if (gc->gc_type==GE_GCText) SetTextColor(hDC,gc->foreground);
      }
   }
   /* GE_GCMaskBackground */
   if (gc->gc_mask&GE_GCMaskBackground) {
      SetBkColor(hDC,gc->background);
   }
   /* GE_GCMaskLineWidth,E_GCMaskLineStyle,GE_GCMaskDashList,
      GE_GCMaskCapStyle,GE_GCMaskJoinStyle */
   if (gc->gc_mask&GE_GCMaskLineWidth ||
       gc->gc_mask&GE_GCMaskLineStyle ||
       gc->gc_mask&GE_GCMaskDashList ||
       gc->gc_mask&GE_GCMaskCapStyle ||
       gc->gc_mask&GE_GCMaskJoinStyle) {
      hPen=SelectObject(hDC,GetStockObject(NULL_PEN));
      nCount=GetObject(hPen,0,0); /* 20030310 */
      pExtLogPen=(EXTLOGPEN*)salloc(char,nCount); /* 20030310 */
      GetObject(hPen,nCount,(LPVOID)pExtLogPen); /* 20030310 */
      DeleteObject(hPen);
      pExtLogPen->elpPenStyle&=~PS_TYPE_MASK;
      pExtLogPen->elpPenStyle|=PS_GEOMETRIC;
      nDashSizes=0;
      if (gc->gc_mask&GE_GCMaskLineWidth) {
         pExtLogPen->elpWidth=gc->line_width-1; /* 20030306 */
      }
      if (gc->gc_mask&GE_GCMaskLineStyle) {
         if (gc->line_style==GE_LineSolid) {
            pExtLogPen->elpPenStyle&=~PS_STYLE_MASK;
            pExtLogPen->elpPenStyle|=PS_SOLID;
         } else if (gc->gc_mask&GE_GCMaskDashList) {
            /* GE_LineOnOffDash,GE_LineDoubleDash,GE_LineUser */
            pExtLogPen->elpPenStyle&=~PS_STYLE_MASK;
            pExtLogPen->elpPenStyle|=PS_USERSTYLE;
            nDashSizes=4;
            for (nCount=0;nCount<nDashSizes;nCount++)
               aDashSizes[nCount]=(gc->dash_list)[nCount];
         }
      }
      if (gc->gc_mask&GE_GCMaskCapStyle) {
         pExtLogPen->elpPenStyle&=~PS_ENDCAP_MASK;
         switch (gc->cap_style) {
         case GE_CapNotLast    : pExtLogPen->elpPenStyle|=PS_ENDCAP_FLAT;  break;
         case GE_CapButt       : pExtLogPen->elpPenStyle|=PS_ENDCAP_FLAT;  break;
         case GE_CapRound      : pExtLogPen->elpPenStyle|=PS_ENDCAP_ROUND; break;
         case GE_CapProjecting : pExtLogPen->elpPenStyle|=PS_ENDCAP_SQUARE;break;
         }
      }
      if (gc->gc_mask&GE_GCMaskJoinStyle) {
         pExtLogPen->elpPenStyle&=~PS_JOIN_MASK;
         switch (gc->join_style) {
         case GE_JoinMiter : pExtLogPen->elpPenStyle|=PS_JOIN_MITER;break;
         case GE_JoinRound : pExtLogPen->elpPenStyle|=PS_JOIN_ROUND;break;
         case GE_JoinBevel : pExtLogPen->elpPenStyle|=PS_JOIN_BEVEL;break;
         }
      }
      logBrush.lbColor=pExtLogPen->elpColor;
      logBrush.lbStyle=BS_SOLID;
      logBrush.lbHatch=0;
      bUserStyle=(pExtLogPen->elpPenStyle&PS_STYLE_MASK)==PS_USERSTYLE;
      hPen=ExtCreatePen(
         pExtLogPen->elpPenStyle,
         pExtLogPen->elpWidth,
         &logBrush,
         bUserStyle?nDashSizes?nDashSizes:pExtLogPen->elpNumEntries:0, /* 20030310 */
         bUserStyle?nDashSizes?aDashSizes:pExtLogPen->elpStyleEntry:NULL /* 20030310 */
      );
      assert(hPen); /* 20030310 */
      DeleteObject(SelectObject(hDC,hPen));
      free(pExtLogPen); /* 20030310 */
   }
   /* GE_GCMaskFillStyle */
   if (gc->gc_mask&GE_GCMaskFillStyle) {
      switch (gc->fill_style) {
      case GE_FillSolid         :
      case GE_FillOpaqueStippled: SetBkMode(hDC,OPAQUE); break;
      case GE_FillStippled      :
      case GE_FillTiled         : SetBkMode(hDC,TRANSPARENT); break;
      }
   }
   /* GE_GCMaskFillRule */
   if (gc->gc_mask&GE_GCMaskFillRule) {
      switch (gc->fill_rule) {
      case GE_FillEvenOdd : SetPolyFillMode(hDC,ALTERNATE);break;
      case GE_FillWinding : SetPolyFillMode(hDC,WINDING);break;
      }
   }
   /* GE_GCMaskArcMode */
   if (gc->gc_mask&GE_GCMaskArcMode) {
      switch (gc->arc_mode) {
      case GE_ArcPieSlice : myArc=(IPTRFN)Arc;break;
      case GE_ArcChord    : myArc=(IPTRFN)Chord;break;
      }
   }
   /* GE_GCMaskPolyShape */
   if (gc->gc_mask&GE_GCMaskPolyShape) {
      ;
   }
   /* GE_GCMaskPolyArcAttr */
   if (gc->gc_mask&GE_GCMaskPolyArcAttr) {
      if (gc->gc_type==GE_GCPolygonL)
         myDisplay->etc[GE_GCPolygon].polyarc_attr=gc->polyarc_attr;
      else
         myDisplay->etc[gc->gc_type].polyarc_attr=gc->polyarc_attr;
   }
   /* GE_GCMaskTile */
   if (gc->gc_mask&GE_GCMaskTile) {
      ;
   }
   /* GE_GCMaskStipple */
   if (gc->gc_mask&GE_GCMaskStipple) {
      if (gc->stipple) myDisplay->etc[gc->gc_type].polyarc_attr=gc->polyarc_attr;
      else             myDisplay->etc[gc->gc_type].polyarc_attr=GE_PolyArcLine;
      if (myDisplay->etc[gc->gc_type].polyarc_attr==GE_PolyArcFill
      ||  myDisplay->etc[gc->gc_type].polyarc_attr==GE_PolyArcBoth) { 
         logBrush.lbStyle=BS_HATCHED;
         logBrush.lbHatch=HS_BDIAGONAL;
      } else {
         logBrush.lbStyle=BS_HOLLOW;
      }
   }
   /* GE_GCMaskTileStipXOrigin */
   if (gc->gc_mask&GE_GCMaskTileStipXOrigin) {
      ;
   }
   /* GE_GCMaskTileStipYOrigin */
   if (gc->gc_mask&GE_GCMaskTileStipYOrigin) {
      ;
   }
   /* GE_GCMaskFont */
   if (gc->gc_mask&GE_GCMaskFont) {
      if (gc->font_type==GE_FontRaster)
         ;
      else if (gc->font_type==GE_FontVector)
         ;
      else if (gc->font_type==GE_FontTrueType) {
         /* char font[256]="fontName,Height,Width,Angle,Alignment" */
         char *name;
         int height,width,angle,alignment;
         //
         name=gc->font[0]=='*' ? DEFAULT_GR_FONT_NAME:gc->font;
         width=(int)(gc->font_width*myDisplay->metricScale);
         height=(int)(gc->font_height*myDisplay->metricScale);
         angle=gc->font_angle;
         alignment=gc->text_format;
         //
         width*=2;height*=2; // how stupid ? 2000.218
         //
         hFont=CreateFont(height,width,angle,angle,
            FW_NORMAL,FALSE,FALSE,
            //FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,
            FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,0x40,
            DEFAULT_QUALITY,VARIABLE_PITCH|FF_DONTCARE,name);
         DeleteObject(SelectObject(hDC,hFont));
         SetBkMode(hDC,TRANSPARENT);
         /* text alignment */
         {
         unsigned int textAlignmentFlag=0;
         switch (alignment&15) {
         case GE_AlignBottom   : textAlignmentFlag=TA_BOTTOM;   break;
         case GE_AlignBaseline : textAlignmentFlag=TA_BASELINE; break;
         case GE_AlignVCenter  : textAlignmentFlag=TA_BASELINE; break;
         case GE_AlignTop      : textAlignmentFlag=TA_TOP;      break;
         }         
         switch (alignment&240) {
         case GE_AlignLeft     : textAlignmentFlag|=TA_LEFT;    break;
         case GE_AlignHCenter  : textAlignmentFlag|=TA_CENTER;  break;
         case GE_AlignRight    : textAlignmentFlag|=TA_RIGHT;   break;
         }
         SetTextAlign(hDC,textAlignmentFlag);
         }
      }
   }
   /* GE_GCMaskSubwindowMode */
   if (gc->gc_mask&GE_GCMaskSubwindowMode) {
      ;
   }
   /* GE_GCMaskGraphicsExposures */
   if (gc->gc_mask&GE_GCMaskGraphicsExposures) {
      ;
   }
   /* GE_GCMaskClipXOrigin */
   if (gc->gc_mask&GE_GCMaskClipXOrigin) {
      ;
   }
   /* GE_GCMaskClipYOrigin */
   if (gc->gc_mask&GE_GCMaskClipYOrigin) {
      ;
   }
   /* GE_GCMaskClipMask */
   if (gc->gc_mask&GE_GCMaskClipMask) {
      ;
   }
   /* GE_GCMaskDashOffset */
   if (gc->gc_mask&GE_GCMaskDashOffset) {
      ;
   }
   return TRUE;
}
 
int myDrawPoint(MYDISPLAY *myDisplay,
                GEPOINT *ptr,
                int nTotal)
{
   register int i,j=GE_GCPoint;

   MoveToEx(myDisplay->gc[j],ptr->x,ptr->y,NULL);
   LineTo(myDisplay->gc[j],ptr->x,ptr->y);
   ptr-=2;
   for (i=2;i<=nTotal;i++) {
      MoveToEx(myDisplay->gc[j],ptr[i].x,ptr[i].y,NULL);
      LineTo(myDisplay->gc[j],ptr[i].x,ptr[i].y);
   }
   return TRUE;
}

int myDrawLine( MYDISPLAY *myDisplay,GELINE *pLine,int nTotal )
{
   int i,j=GE_GCLine;

   BeginPath(myDisplay->gc[j]);
   for (i=0;i<nTotal;i++) { /* 20030306 */
      MoveToEx(myDisplay->gc[j],pLine[i].x1,pLine[i].y1,NULL);
      LineTo(myDisplay->gc[j],pLine[i].x2,pLine[i].y2);
   }
   EndPath(myDisplay->gc[j]);
   StrokePath(myDisplay->gc[j]);
   return TRUE;
}

int myDrawPoly(
   MYDISPLAY *myDisplay,
   GEPOINT *_ptr,
   int nTotal,
   GERECT *Rect
   )
{
   POINT *ptr;
   int i;
   HDC hDC;

   ptr=salloc(POINT,nTotal);
   for (i=0;i<nTotal;i++) {
      ptr[i].x=(long)_ptr[i].x;
      ptr[i].y=(long)_ptr[i].y;
   }
   if (Rect) {
      HRGN hRgn;
      RECT RgnRect;
      POINT Point;
      hDC=myDisplay->gc[GE_GCPolygon];
      memset(Rect,0,sizeof(GERECT));
      BeginPath(hDC);
      MoveToEx(hDC,ptr[0].x,ptr[0].y,NULL);
      for (i=1;i<nTotal;i++) LineTo(hDC,ptr[i].x,ptr[i].y);
      EndPath(hDC);
      hRgn=PathToRegion(hDC);
      GetRgnBox(hRgn,&RgnRect);
      DeleteObject(hRgn);
      Point.x=RgnRect.left;
      Point.y=RgnRect.top;
      DPtoLP(hDC,&Point,1);
      Rect->x=Point.x;
      Rect->y=Point.y;
      Point.x=RgnRect.right;
      Point.y=RgnRect.bottom;
      DPtoLP(hDC,&Point,1);
      Rect->width=Point.x-Rect->x;
      Rect->height=Point.y-Rect->y;
   } else {
      switch (myDisplay->etc[GE_GCPolygon].polyarc_attr) {
      case GE_PolyArcLine :
         hDC=myDisplay->gc[GE_GCPolygonL];
         BeginPath(hDC);
         MoveToEx(hDC,ptr[0].x,ptr[0].y,NULL);
         for (i=1;i<nTotal;i++) LineTo(hDC,ptr[i].x,ptr[i].y);
         EndPath(hDC);
         StrokePath(hDC);
         break;
      case GE_PolyArcFill :
         hDC=myDisplay->gc[GE_GCPolygon];
         BeginPath(hDC);
         MoveToEx(hDC,ptr[0].x,ptr[0].y,NULL);
         for (i=1;i<nTotal;i++) LineTo(hDC,ptr[i].x,ptr[i].y);
         EndPath(hDC);
         FillPath(hDC);
      case GE_PolyArcBoth :
         hDC=myDisplay->gc[GE_GCPolygon];
         BeginPath(hDC);
         MoveToEx(hDC,ptr[0].x,ptr[0].y,NULL);
         for (i=1;i<nTotal;i++) LineTo(hDC,ptr[i].x,ptr[i].y);
         EndPath(hDC);
         FillPath(hDC);
         hDC=myDisplay->gc[GE_GCPolygonL];
         BeginPath(hDC);
         MoveToEx(hDC,ptr[0].x,ptr[0].y,NULL);
         for (i=1;i<nTotal;i++) LineTo(hDC,ptr[i].x,ptr[i].y);
         EndPath(hDC);
         StrokePath(hDC);
      }
   }
   free(ptr);
   return TRUE;
}

int myDrawArc(
   MYDISPLAY *myDisplay,
   GEARC *ptr,
   int nTotal
   )
{
   int xStart,yStart,xEnd,yEnd;
   int r;
   r=(ptr->width+ptr->height)/2;
   xStart=(int)(r*cos((double)RADIAN(ptr->angle1)));
   yStart=(int)(r*sin((double)RADIAN(ptr->angle1)));
   xEnd=(int)(r*cos((double)RADIAN(ptr->angle2)));
   yEnd=(int)(r*sin((double)RADIAN(ptr->angle2)));
   (*myArc)(myDisplay->gc[GE_GCPolygonL],ptr->x,ptr->y,
      ptr->x+ptr->width,ptr->y+ptr->height,
      ptr->x+xStart,ptr->y+yStart,ptr->x+xEnd,ptr->y+yEnd);
   return TRUE;
}

int myDrawText(
   MYDISPLAY *myDisplay,
   int x, int y, char *text,
   GERECT *Rect
   )
{
   HDC hDC=myDisplay->gc[GE_GCText];
   int bSpecialAlign; /* 2K.0717 */
   SIZE size;
   UINT Alignment;
   char *ptr;
   if (Rect) {
      int nBkModeBackUp;
      HRGN hRgn;
      RECT RgnRect;
      POINT Point;
      memset(Rect,0,sizeof(GERECT));
      nBkModeBackUp=GetBkMode(hDC);
      if (nBkModeBackUp!=TRANSPARENT) SetBkMode(hDC,TRANSPARENT);
      BeginPath(hDC);
      myDrawText(myDisplay,x,y,text,(GERECT*)0);
      EndPath(hDC);
      hRgn=PathToRegion(hDC);
      GetRgnBox(hRgn,&RgnRect);
      DeleteObject(hRgn);
      Point.x=RgnRect.left;
      Point.y=RgnRect.top;
      DPtoLP(hDC,&Point,1);
      Rect->x=Point.x;
      Rect->y=Point.y;
      Point.x=RgnRect.right;
      Point.y=RgnRect.bottom;
      DPtoLP(hDC,&Point,1);
      Rect->width=Point.x-Rect->x;
      Rect->height=Point.y-Rect->y;
      if (nBkModeBackUp!=TRANSPARENT) SetBkMode(hDC,nBkModeBackUp);
      return TRUE;
   }
   Alignment=GetTextAlign(hDC);
   GetTextExtentPoint32(hDC,text,strlen(text),&size);
   bSpecialAlign=TA_BASELINE==(TA_BASELINE&Alignment) ? TRUE:FALSE;
   if (bSpecialAlign) { /* 2000.3.17+3.18 */
      y+=(size.cy>>1);
      SetTextAlign(hDC,(Alignment&~TA_BASELINE)|TA_BOTTOM);
   }
   while (ptr=strchr(text,'\n')) {
      TextOut(hDC,x,y,text,ptr-text);
      y+=size.cy;
      text=ptr+1;
   }
   TextOut(hDC,x,y,text,strlen(text));
   if (bSpecialAlign) { /* 2000.3.17+3.18 */
      SetTextAlign(hDC,Alignment);
   }
   return TRUE;
}

int myDrawTextLine( MYDISPLAY *myDisplay, /* only used in gefont.c */
                    GELINE *ptr,
                    int nTotal )
{
   int i,j=GE_GCTextL;

   for (i=0;i<nTotal;i++) {
      MoveToEx(myDisplay->gc[j],ptr[i].x1,ptr[i].y1,NULL);
      LineTo(myDisplay->gc[j],ptr[i].x2,ptr[i].y2);
   }
   return TRUE;
}

int myClipWin( MYDISPLAY *myDisplay,
               RECT *rect )
{
   return TRUE;
}
 
int myGetGeometry( MYDISPLAY *myDisplay,GERECT *data )
{
   RECT rect;

   GetClientRect(myDisplay->window,&rect);
   data->x=rect.left;
   data->y=rect.top;
   data->width=rect.right-rect.left+1;
   data->height=rect.bottom-rect.top+1;
   data->borderWidth=0; // to be reinforced
   return TRUE;
}

int myFlush()
{
   return TRUE;
}

int myWindowShow(MYDISPLAY *myDisplay,
                 char *name,
                 int x, int y, int width, int height )
{
   int i,j;

   i=j=0;
   i=SetWindowText(myDisplay->window,name);
   j=SetWindowPos(myDisplay->window,HWND_TOP,x,y,width,height,
      SWP_SHOWWINDOW);
   return (i&j);
}

int myWindowHide( MYDISPLAY *myDisplay )
{
   ShowWindow(myDisplay->window,SW_HIDE);
   return TRUE;
}

int myWindowKill()
{
   return TRUE;
}

int myWindowClear( MYDISPLAY *myDisplay )
{
   if (myDisplay->window)
      SendMessage(myDisplay->window,WM_ERASEBKGND,0,0);
   return TRUE;
}

int myCopyToBackingStore()
{
   return TRUE;
}

int myCopyFromBackingStore()
{
   return TRUE;
}

int myGetKeyEvent()
{
   return TRUE;
}

int myGetMouseEvent()
{
   return TRUE;
}

int myGetMouseXY( myDisplay,x,y ) /* in window coordinates */
   MYDISPLAY *myDisplay;
   int *x,*y;
{
   RECT rect;
   POINT point;

   GetWindowRect((HWND)myDisplay->window,&rect);
   GetCursorPos(&point);
   *x=point.x-rect.left;
   *y=point.y-rect.top;
   return TRUE;
}

int mySetMouseXY( myDisplay,x,y ) /* in window coordinates */
   MYDISPLAY *myDisplay;
   int x,y;
{
   RECT rect;

   GetWindowRect((HWND)myDisplay->window,&rect);
   SetCursorPos(rect.left+x,rect.top+y);
   return TRUE;
}

int myAlloImage()
{
   return TRUE;
}

int myFreeImage()
{
   return TRUE;
}

int myGetImage()
{
   return TRUE;
}

int myPutImage()
{
   return TRUE;
}

int myGetPixel()
{
   return TRUE;
}

int myPutPixel()
{
   return TRUE;
}

int myCopyBuffer2Buffer()
{
   return TRUE;
}

int myCopyBuffer2Screen()
{
   return TRUE;
}

int myCopyScreen2Buffer()
{
   return TRUE;
}

static
GECOLOR myColorTable[] = {
{255,250,250,"snow"},
{248,248,255,"GhostWhite"},
{245,245,245,"WhiteSmoke"},
{220,220,220,"gainsboro"},
{255,250,240,"FloralWhite"},
{253,245,230,"OldLace"},
{250,240,230,"linen"},
{250,235,215,"AntiqueWhite"},
{255,239,213,"PapayaWhip"},
{255,235,205,"BlanchedAlmond"},
{255,228,196,"bisque"},
{255,218,185,"PeachPuff"},
{255,222,173,"NavajoWhite"},
{255,228,181,"moccasin"},
{255,248,220,"cornsilk"},
{255,255,240,"ivory"},
{255,250,205,"LemonChiffon"},
{255,245,238,"seashell"},
{240,255,240,"honeydew"},
{245,255,250,"MintCream"},
{240,255,255,"azure"},
{240,248,255,"AliceBlue"},
{230,230,250,"lavender"},
{255,240,245,"LavenderBlush"},
{255,228,225,"MistyRose"},
{255,255,255,"white"},
{  0,  0,  0,"black"},
{ 47, 79, 79,"DarkSlateGray"},
{105,105,105,"DimGray"},
{112,128,144,"SlateGray"},
{119,136,153,"LightSlateGray"},
{192,192,192,"gray"},
{211,211,211,"LightGray"},
{ 25, 25,112,"MidnightBlue"},
{  0,  0,128,"navy"},
{  0,  0,128,"NavyBlue"},
{100,149,237,"CornflowerBlue"},
{ 72, 61,139,"DarkSlateBlue"},
{106, 90,205,"SlateBlue"},
{123,104,238,"MediumSlateBlue"},
{132,112,255,"LightSlateBlue"},
{  0,  0,205,"MediumBlue"},
{ 65,105,225,"RoyalBlue"},
{  0,  0,255,"blue"},
{ 30,144,255,"DodgerBlue"},
{  0,191,255,"DeepSkyBlue"},
{135,206,235,"SkyBlue"},
{135,206,250,"LightSkyBlue"},
{ 70,130,180,"SteelBlue"},
{176,196,222,"LightSteelBlue"},
{173,216,230,"LightBlue"},
{176,224,230,"PowderBlue"},
{175,238,238,"PaleTurquoise"},
{  0,206,209,"DarkTurquoise"},
{ 72,209,204,"MediumTurquoise"},
{ 64,224,208,"turquoise"},
{  0,255,255,"cyan"},
{224,255,255,"LightCyan"},
{ 95,158,160,"CadetBlue"},
{102,205,170,"MediumAquamarine"},
{127,255,212,"aquamarine"},
{  0,100,  0,"DarkGreen"},
{ 85,107, 47,"DarkOliveGreen"},
{143,188,143,"DarkSeaGreen"},
{ 46,139, 87,"SeaGreen"},
{ 60,179,113,"MediumSeaGreen"},
{ 32,178,170,"LightSeaGreen"},
{152,251,152,"PaleGreen"},
{  0,255,127,"SpringGreen"},
{124,252,0,"LawnGreen"},
{0,255,0,"green"},
{127,255,0,"chartreuse"},
{0,250,154,"MediumSpringGreen"},
{173,255,47,"GreenYellow"},
{50,205,50,"LimeGreen"},
{154,205,50,"YellowGreen"},
{34,139,34,"ForestGreen"},
{107,142,35,"OliveDrab"},
{189,183,107,"DarkKhaki"},
{240,230,140,"khaki"},
{238,232,170,"PaleGoldenrod"},
{250,250,210,"LightGoldenrodYellow"},
{255,255,224,"LightYellow"},
{255,255,0,"yellow"},
{255,215,0,"gold"},
{238,221,130,"LightGoldenrod"},
{218,165,32,"goldenrod"},
{184,134,11,"DarkGoldenrod"},
{188,143,143,"RosyBrown"},
{205,92,92,"IndianRed"},
{139,69,19,"SaddleBrown"},
{160,82,45,"sienna"},
{205,133,63,"peru"},
{222,184,135,"burlywood"},
{245,245,220,"beige"},
{245,222,179,"wheat"},
{244,164,96,"SandyBrown"},
{210,180,140,"tan"},
{210,105,30,"chocolate"},
{178,34,34,"firebrick"},
{165,42,42,"brown"},
{233,150,122,"DarkSalmon"},
{250,128,114,"salmon"},
{255,160,122,"LightSalmon"},
{255,165,0,"orange"},
{255,140,0,"DarkOrange"},
{255,127,80,"coral"},
{240,128,128,"LightCoral"},
{255,99,71,"tomato"},
{255,69,0,"OrangeRed"},
{255,0,0,"red"},
{255,105,180,"HotPink"},
{255,20,147,"DeepPink"},
{255,192,203,"pink"},
{255,182,193,"LightPink"},
{219,112,147,"PaleVioletRed"},
{176,48,96,"maroon"},
{199,21,133,"MediumVioletRed"},
{208,32,144,"VioletRed"},
{255,0,255,"magenta"},
{238,130,238,"violet"},
{221,160,221,"plum"},
{218,112,214,"orchid"},
{186,85,211,"MediumOrchid"},
{153,50,204,"DarkOrchid"},
{148,0,211,"DarkViolet"},
{138,43,226,"BlueViolet"},
{160,32,240,"purple"},
{147,112,219,"MediumPurple"},
{216,191,216,"thistle"},
{255,250,250,"snow1"},
{238,233,233,"snow2"},
{205,201,201,"snow3"},
{139,137,137,"snow4"},
{255,245,238,"seashell1"},
{238,229,222,"seashell2"},
{205,197,191,"seashell3"},
{139,134,130,"seashell4"},
{255,239,219,"AntiqueWhite1"},
{238,223,204,"AntiqueWhite2"},
{205,192,176,"AntiqueWhite3"},
{139,131,120,"AntiqueWhite4"},
{255,228,196,"bisque1"},
{238,213,183,"bisque2"},
{205,183,158,"bisque3"},
{139,125,107,"bisque4"},
{255,218,185,"PeachPuff1"},
{238,203,173,"PeachPuff2"},
{205,175,149,"PeachPuff3"},
{139,119,101,"PeachPuff4"},
{255,222,173,"NavajoWhite1"},
{238,207,161,"NavajoWhite2"},
{205,179,139,"NavajoWhite3"},
{139,121,94,"NavajoWhite4"},
{255,250,205,"LemonChiffon1"},
{238,233,191,"LemonChiffon2"},
{205,201,165,"LemonChiffon3"},
{139,137,112,"LemonChiffon4"},
{255,248,220,"cornsilk1"},
{238,232,205,"cornsilk2"},
{205,200,177,"cornsilk3"},
{139,136,120,"cornsilk4"},
{255,255,240,"ivory1"},
{238,238,224,"ivory2"},
{205,205,193,"ivory3"},
{139,139,131,"ivory4"},
{240,255,240,"honeydew1"},
{224,238,224,"honeydew2"},
{193,205,193,"honeydew3"},
{131,139,131,"honeydew4"},
{255,240,245,"LavenderBlush1"},
{238,224,229,"LavenderBlush2"},
{205,193,197,"LavenderBlush3"},
{139,131,134,"LavenderBlush4"},
{255,228,225,"MistyRose1"},
{238,213,210,"MistyRose2"},
{205,183,181,"MistyRose3"},
{139,125,123,"MistyRose4"},
{240,255,255,"azure1"},
{224,238,238,"azure2"},
{193,205,205,"azure3"},
{131,139,139,"azure4"},
{131,111,255,"SlateBlue1"},
{122,103,238,"SlateBlue2"},
{105,89,205,"SlateBlue3"},
{71,60,139,"SlateBlue4"},
{72,118,255,"RoyalBlue1"},
{67,110,238,"RoyalBlue2"},
{58,95,205,"RoyalBlue3"},
{39,64,139,"RoyalBlue4"},
{  0,  0,255,"blue1"},
{  0,  0,238,"blue2"},
{  0,  0,205,"blue3"},
{  0,  0,139,"blue4"},
{ 30,144,255,"DodgerBlue1"},
{ 28,134,238,"DodgerBlue2"},
{ 24,116,205,"DodgerBlue3"},
{ 16, 78,139,"DodgerBlue4"},
{ 99,184,255,"SteelBlue1"},
{ 92,172,238,"SteelBlue2"},
{ 79,148,205,"SteelBlue3"},
{ 54,100,139,"SteelBlue4"},
{  0,191,255,"DeepSkyBlue1"},
{  0,178,238,"DeepSkyBlue2"},
{  0,154,205,"DeepSkyBlue3"},
{  0,104,139,"DeepSkyBlue4"},
{135,206,255,"SkyBlue1"},
{126,192,238,"SkyBlue2"},
{108,166,205,"SkyBlue3"},
{ 74,112,139,"SkyBlue4"},
{176,226,255,"LightSkyBlue1"},
{164,211,238,"LightSkyBlue2"},
{141,182,205,"LightSkyBlue3"},
{ 96,123,139,"LightSkyBlue4"},
{198,226,255,"SlateGray1"},
{185,211,238,"SlateGray2"},
{159,182,205,"SlateGray3"},
{108,123,139,"SlateGray4"},
{202,225,255,"LightSteelBlue1"},
{188,210,238,"LightSteelBlue2"},
{162,181,205,"LightSteelBlue3"},
{110,123,139,"LightSteelBlue4"},
{191,239,255,"LightBlue1"},
{178,223,238,"LightBlue2"},
{154,192,205,"LightBlue3"},
{104,131,139,"LightBlue4"},
{224,255,255,"LightCyan1"},
{209,238,238,"LightCyan2"},
{180,205,205,"LightCyan3"},
{122,139,139,"LightCyan4"},
{187,255,255,"PaleTurquoise1"},
{174,238,238,"PaleTurquoise2"},
{150,205,205,"PaleTurquoise3"},
{102,139,139,"PaleTurquoise4"},
{152,245,255,"CadetBlue1"},
{142,229,238,"CadetBlue2"},
{122,197,205,"CadetBlue3"},
{83,134,139,"CadetBlue4"},
{  0,245,255,"turquoise1"},
{  0,229,238,"turquoise2"},
{  0,197,205,"turquoise3"},
{  0,134,139,"turquoise4"},
{  0,255,255,"cyan1"},
{  0,238,238,"cyan2"},
{  0,205,205,"cyan3"},
{  0,139,139,"cyan4"},
{151,255,255,"DarkSlateGray1"},
{141,238,238,"DarkSlateGray2"},
{121,205,205,"DarkSlateGray3"},
{ 82,139,139,"DarkSlateGray4"},
{127,255,212,"aquamarine1"},
{118,238,198,"aquamarine2"},
{102,205,170,"aquamarine3"},
{ 69,139,116,"aquamarine4"},
{193,255,193,"DarkSeaGreen1"},
{180,238,180,"DarkSeaGreen2"},
{155,205,155,"DarkSeaGreen3"},
{105,139,105,"DarkSeaGreen4"},
{ 84,255,159,"SeaGreen1"},
{ 78,238,148,"SeaGreen2"},
{ 67,205,128,"SeaGreen3"},
{ 46,139, 87,"SeaGreen4"},
{154,255,154,"PaleGreen1"},
{144,238,144,"PaleGreen2"},
{124,205,124,"PaleGreen3"},
{ 84,139, 84,"PaleGreen4"},
{  0,255,127,"SpringGreen1"},
{  0,238,118,"SpringGreen2"},
{  0,205,102,"SpringGreen3"},
{  0,139, 69,"SpringGreen4"},
{  0,255,  0,"green1"},
{  0,238,  0,"green2"},
{  0,205,  0,"green3"},
{  0,139,  0,"green4"},
{127,255,  0,"chartreuse1"},
{118,238,  0,"chartreuse2"},
{102,205,  0,"chartreuse3"},
{ 69,139,  0,"chartreuse4"},
{192,255, 62,"OliveDrab1"},
{179,238, 58,"OliveDrab2"},
{154,205, 50,"OliveDrab3"},
{105,139, 34,"OliveDrab4"},
{202,255,112,"DarkOliveGreen1"},
{188,238,104,"DarkOliveGreen2"},
{162,205, 90,"DarkOliveGreen3"},
{110,139, 61,"DarkOliveGreen4"},
{255,246,143,"khaki1"},
{238,230,133,"khaki2"},
{205,198,115,"khaki3"},
{139,134, 78,"khaki4"},
{255,236,139,"LightGoldenrod1"},
{238,220,130,"LightGoldenrod2"},
{205,190,112,"LightGoldenrod3"},
{139,129, 76,"LightGoldenrod4"},
{255,255,224,"LightYellow1"},
{238,238,209,"LightYellow2"},
{205,205,180,"LightYellow3"},
{139,139,122,"LightYellow4"},
{255,255,  0,"yellow1"},
{238,238,  0,"yellow2"},
{205,205,  0,"yellow3"},
{139,139,  0,"yellow4"},
{255,215,  0,"gold1"},
{238,201,  0,"gold2"},
{205,173,  0,"gold3"},
{139,117,  0,"gold4"},
{255,193, 37,"goldenrod1"},
{238,180, 34,"goldenrod2"},
{205,155, 29,"goldenrod3"},
{139,105, 20,"goldenrod4"},
{255,185, 15,"DarkGoldenrod1"},
{238,173, 14,"DarkGoldenrod2"},
{205,149, 12,"DarkGoldenrod3"},
{139,101,  8,"DarkGoldenrod4"},
{255,193,193,"RosyBrown1"},
{238,180,180,"RosyBrown2"},
{205,155,155,"RosyBrown3"},
{139,105,105,"RosyBrown4"},
{255,106,106,"IndianRed1"},
{238, 99, 99,"IndianRed2"},
{205, 85, 85,"IndianRed3"},
{139, 58, 58,"IndianRed4"},
{255,130, 71,"sienna1"},
{238,121, 66,"sienna2"},
{205,104, 57,"sienna3"},
{139, 71, 38,"sienna4"},
{255,211,155,"burlywood1"},
{238,197,145,"burlywood2"},
{205,170,125,"burlywood3"},
{139,115, 85,"burlywood4"},
{255,231,186,"wheat1"},
{238,216,174,"wheat2"},
{205,186,150,"wheat3"},
{139,126,102,"wheat4"},
{255,165, 79,"tan1"},
{238,154, 73,"tan2"},
{205,133, 63,"tan3"},
{139, 90, 43,"tan4"},
{255,127,36,"chocolate1"},
{238,118,33,"chocolate2"},
{205,102,29,"chocolate3"},
{139, 69, 19,"chocolate4"},
{255, 48, 48,"firebrick1"},
{238, 44, 44,"firebrick2"},
{205, 38, 38,"firebrick3"},
{139, 26, 26,"firebrick4"},
{255, 64, 64,"brown1"},
{238, 59, 59,"brown2"},
{205, 51, 51,"brown3"},
{139, 35, 35,"brown4"},
{255,140,105,"salmon1"},
{238,130, 98,"salmon2"},
{205,112, 84,"salmon3"},
{139, 76, 57,"salmon4"},
{255,160,122,"LightSalmon1"},
{238,149,114,"LightSalmon2"},
{205,129, 98,"LightSalmon3"},
{139, 87, 66,"LightSalmon4"},
{255,165,  0,"orange1"},
{238,154,  0,"orange2"},
{205,133,  0,"orange3"},
{139, 90,  0,"orange4"},
{255,127,  0,"DarkOrange1"},
{238,118,  0,"DarkOrange2"},
{205,102,  0,"DarkOrange3"},
{139, 69,  0,"DarkOrange4"},
{255,114, 86,"coral1"},
{238,106, 80,"coral2"},
{205, 91, 69,"coral3"},
{139, 62, 47,"coral4"},
{255, 99, 71,"tomato1"},
{238, 92, 66,"tomato2"},
{205, 79, 57,"tomato3"},
{139, 54, 38,"tomato4"},
{255, 69,  0,"OrangeRed1"},
{238, 64,  0,"OrangeRed2"},
{205, 55,  0,"OrangeRed3"},
{139, 37,  0,"OrangeRed4"},
{255,  0,  0,"red1"},
{238,  0,  0,"red2"},
{205,  0,  0,"red3"},
{139,  0,  0,"red4"},
{255, 20,147,"DeepPink1"},
{238, 18,137,"DeepPink2"},
{205, 16,118,"DeepPink3"},
{139, 10, 80,"DeepPink4"},
{255,110,180,"HotPink1"},
{238,106,167,"HotPink2"},
{205, 96,144,"HotPink3"},
{139, 58, 98,"HotPink4"},
{255,181,197,"pink1"},
{238,169,184,"pink2"},
{205,145,158,"pink3"},
{139, 99,108,"pink4"},
{255,174,185,"LightPink1"},
{238,162,173,"LightPink2"},
{205,140,149,"LightPink3"},
{139, 95,101,"LightPink4"},
{255,130,171,"PaleVioletRed1"},
{238,121,159,"PaleVioletRed2"},
{205,104,137,"PaleVioletRed3"},
{139, 71, 93,"PaleVioletRed4"},
{255, 52,179,"maroon1"},
{238, 48,167,"maroon2"},
{205, 41,144,"maroon3"},
{139, 28, 98,"maroon4"},
{255, 62,150,"VioletRed1"},
{238, 58,140,"VioletRed2"},
{205, 50,120,"VioletRed3"},
{139, 34, 82,"VioletRed4"},
{255,  0,255,"magenta1"},
{238,  0,238,"magenta2"},
{205,  0,205,"magenta3"},
{139,  0,139,"magenta4"},
{255,131,250,"orchid1"},
{238,122,233,"orchid2"},
{205,105,201,"orchid3"},
{139, 71,137,"orchid4"},
{255,187,255,"plum1"},
{238,174,238,"plum2"},
{205,150,205,"plum3"},
{139,102,139,"plum4"},
{224,102,255,"MediumOrchid1"},
{209, 95,238,"MediumOrchid2"},
{180, 82,205,"MediumOrchid3"},
{122, 55,139,"MediumOrchid4"},
{191, 62,255,"DarkOrchid1"},
{178, 58,238,"DarkOrchid2"},
{154, 50,205,"DarkOrchid3"},
{104, 34,139,"DarkOrchid4"},
{155, 48,255,"purple1"},
{145, 44,238,"purple2"},
{125, 38,205,"purple3"},
{ 85, 26,139,"purple4"},
{171,130,255,"MediumPurple1"},
{159,121,238,"MediumPurple2"},
{137,104,205,"MediumPurple3"},
{ 93, 71,139,"MediumPurple4"},
{255,225,255,"thistle1"},
{238,210,238,"thistle2"},
{205,181,205,"thistle3"},
{139,123,139,"thistle4"},
{  0,  0,  0,"gray00"},{  3,  3,  3,"gray01"},
{  5,  5,  5,"gray02"},{  8,  8,  8,"gray03"},
{ 10, 10, 10,"gray04"},{ 13, 13, 13,"gray05"},
{ 15, 15, 15,"gray06"},{ 18, 18, 18,"gray07"},
{ 20, 20, 20,"gray08"},{ 23, 23, 23,"gray09"},
{ 26, 26, 26,"gray10"},{ 28, 28, 28,"gray11"},
{ 31, 31, 31,"gray12"},{ 33, 33, 33,"gray13"},
{ 36, 36, 36,"gray14"},{ 38, 38, 38,"gray15"},
{ 41, 41, 41,"gray16"},{ 43, 43, 43,"gray17"},
{ 46, 46, 46,"gray18"},{ 48, 48, 48,"gray19"},
{ 51, 51, 51,"gray20"},{ 54, 54, 54,"gray21"},
{ 56, 56, 56,"gray22"},{ 59, 59, 59,"gray23"},
{ 61, 61, 61,"gray24"},{ 64, 64, 64,"gray25"},
{ 66, 66, 66,"gray26"},{ 69, 69, 69,"gray27"},
{ 71, 71, 71,"gray28"},{ 74, 74, 74,"gray29"},
{ 77, 77, 77,"gray30"},{ 79, 79, 79,"gray31"},
{ 82, 82, 82,"gray32"},{ 84, 84, 84,"gray33"},
{ 87, 87, 87,"gray34"},{ 89, 89, 89,"gray35"},
{ 92, 92, 92,"gray36"},{ 94, 94, 94,"gray37"},
{ 97, 97, 97,"gray38"},{ 99, 99, 99,"gray39"},
{102,102,102,"gray40"},{105,105,105,"gray41"},
{107,107,107,"gray42"},{110,110,110,"gray43"},
{112,112,112,"gray44"},{115,115,115,"gray45"},
{117,117,117,"gray46"},{120,120,120,"gray47"},
{122,122,122,"gray48"},{125,125,125,"gray49"},
{127,127,127,"gray50"},{130,130,130,"gray51"},
{133,133,133,"gray52"},{135,135,135,"gray53"},
{138,138,138,"gray54"},{140,140,140,"gray55"},
{143,143,143,"gray56"},{145,145,145,"gray57"},
{148,148,148,"gray58"},{150,150,150,"gray59"},
{153,153,153,"gray60"},{156,156,156,"gray61"},
{158,158,158,"gray62"},{161,161,161,"gray63"},
{163,163,163,"gray64"},{166,166,166,"gray65"},
{168,168,168,"gray66"},{168,168,168,"gray66"},
{171,171,171,"gray67"},{173,173,173,"gray68"},
{176,176,176,"gray69"},{179,179,179,"gray70"},
{181,181,181,"gray71"},{184,184,184,"gray72"},
{186,186,186,"gray73"},{189,189,189,"gray74"},
{191,191,191,"gray75"},{194,194,194,"gray76"},
{196,196,196,"gray77"},{199,199,199,"gray78"},
{201,201,201,"gray79"},{204,204,204,"gray80"},
{207,207,207,"gray81"},{209,209,209,"gray82"},
{212,212,212,"gray83"},{214,214,214,"gray84"},
{217,217,217,"gray85"},{219,219,219,"gray86"},
{222,222,222,"gray87"},{224,224,224,"gray88"},
{227,227,227,"gray89"},{229,229,229,"gray90"},
{232,232,232,"gray91"},{235,235,235,"gray92"},
{237,237,237,"gray93"},{240,240,240,"gray94"},
{242,242,242,"gray95"},{245,245,245,"gray96"},
{247,247,247,"gray97"},{250,250,250,"gray98"},
{252,252,252,"gray99"},{255,255,255,"gray100"}
};

int GEColorTotal( myDisplay )
   MYDISPLAY *myDisplay;
{
   return noof(myColorTable);
}

const char *GEColorName( myDisplay,value )
   MYDISPLAY *myDisplay; // not used only for porting to X
   unsigned long value;
{
   int i;

   for (i=0;i<noof(myColorTable);i++) {
      if (value==RGB(myColorTable[i].red,
                     myColorTable[i].green,
                     myColorTable[i].blue))
         return myColorTable[i].name;
   }
   return NULL;
}

const char *GEColorNameByIndex( myDisplay,nIndex )
   MYDISPLAY *myDisplay; // not used only for porting to X
   int nIndex;
{
   if (nIndex<0 || nIndex>=noof(myColorTable)) return (char*)0;
   return myColorTable[nIndex].name;
}

unsigned long GEColorByName( myDisplay,name )
   MYDISPLAY *myDisplay; // not used only for porting to X
   const char *name;
{
   int i;

   for (i=0;i<noof(myColorTable);i++) {
      if (!strcmp(name,myColorTable[i].name))
         break;
   }
   return i<noof(myColorTable) ?
      RGB(myColorTable[i].red,myColorTable[i].green,myColorTable[i].blue):
      GEColorByName(myDisplay,"black");
}

unsigned long GEColorByRGB( myDisplay,red,green,blue )
   MYDISPLAY *myDisplay; // not used only for porting to X
   unsigned short red,green,blue;
{
   return RGB(red,green,blue);
}

int GEColor2RGB( myDisplay,value,red,green,blue,BWswitch )
   MYDISPLAY *myDisplay; // not used only for porting to X
   unsigned long value;
   unsigned short *red,*green,*blue;
   int BWswitch;
{
   *red=(short)(value&BITS(0,7));
   *green=(short)((value&BITS(8,15))>>8);
   *blue=(short)((value&BITS(16,31))>>16);
   if (BWswitch) {
      if (*red==255&&*green==255&&*blue==255)
         *red=*green=*blue=0;
   }
   return TRUE;
}

int GEMessageBox( window,string,type )
   HWND window;
   char *string;
   unsigned int type;
{
   switch (type) {
   case GE_MB_ERROR :
      return MessageBox(window,string,"Error ...",
         MB_OK|MB_ICONERROR|MB_SYSTEMMODAL);
   case GE_MB_WARNING :
      return MessageBox(window,string,"Warning ...",
         MB_OK|MB_ICONWARNING|MB_SYSTEMMODAL);
   case GE_MB_INFORMATION :
      return MessageBox(window,string,"Information ...",
         MB_OK|MB_ICONINFORMATION|MB_SYSTEMMODAL);
   case GE_MB_QUESTION :
      return MessageBox(window,string,"Question ...",
         MB_OKCANCEL|MB_ICONQUESTION|MB_SYSTEMMODAL);
   default :
      return GEMessageBox(window,string,GE_MB_INFORMATION);
   }
}

/******************************************************************************/

/* mySleep: Pauses for a specified number of microseconds.
*/
void mySleep( clock_t wait )
{
    clock_t goal;

    goal = wait + clock();
    while( goal >= clock() );
}

/* myBeep: Sounds the speaker for a time specified in microseconds by
   duration at a pitch specified in hertz by frequency.
*/
/*
void myBeep( int frequency, int duration )
{
    int control;

    // If frequency is 0, Beep doesn't try to make a sound. It
    // just sleeps for the duration.
    if( frequency )
    {
        // 75 is about the shortest reliable duration of a sound.
        if( duration < 75 )
            duration = 75;
        // Prepare timer by sending 10111100 to port 43.
        _outp( 0x43, 0xb6 );
        // Divide input frequency by timer ticks per second and
        // write (byte by byte) to timer.
        frequency = (unsigned)(1193180L / frequency);
        _outp( 0x42, (char)frequency );
        _outp( 0x42, (char)(frequency >> 8) );
        // Save speaker control byte.
        control = _inp( 0x61 );
        // Turn on the speaker (with bits 0 and 1).
        _outp( 0x61, control | 0x3 );
    }
    mySleep( (clock_t)duration );
    // Turn speaker back on if necessary.
    if( frequency )
        _outp( 0x61, control );
}
*/

/******************************************************************************/
#endif /* geWindowMS.c */
