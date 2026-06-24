/******************************************************************************/
/*                           file name : gecore.c                             */
/*                    descriptive name : Graphic Engine Core                  */
/*                            compiler : cc                                   */
/*                            producer : Kim,YongShik                         */
/*                       creating date : 43260811                             */
/* 1993 0811,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 1995 0722,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4329 0612,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4332 0301-0331-0505-0715,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0119,0222,0626,0718,____,____,____,____,____,____,____,____,____,____ */
/* 4335 0913-0914,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/


#include <stdio.h>
#include <math.h>

#include "myCore.h"
#include "blob.h"
#include "number.h"
#include "nr.h"
#include "nrecipe.h"
#include "any.h"
#include "tools.h"
#include "geprint.h"
#include "gecore.h"
#include "str.h"

/******************************************************************************/

XMTX2D myGEXMatrix2D; /* used in gecore.c and geprint.c*/
DLL *GEMESSAGE; /* Output Message of DoubleLinkedList */

/******************************************************************************/

static MYDISPLAY *myDisplay;
static XMTX2D     myDeviceXmtx2D;
static GEPOINT   *myBufPoint;
static GELINE    *myBufLine;
static GEARC     *myBufArc;
static IPTRFN     myGEDrawText=0;
static char      *myPSFileNameForPrintting=0;

       int GEDraw();
       int GEDrawEx();
       int GEPrint();
static void ScreenRectXY2Norm();
static int GEDrawOpen();
static int GEDrawClose();
static int GEDrawSetProcedure();
static int GEDrawProcess();
static int GECheckCount();

static int doHeader();
static int doXmtx2DData();
static int doXmtx3DData();
static int doGC();
static int doPoint();
static int doLine();
static int doPolyline();
static int doArc();
static int doText();
static int doClipWin();

static int doPointRect();
static int doLineRect();
static int doPolylineRect();
static int doArcRect();
static int doTextRect();

static int doHeaderForMarker();

int clipper_line();
int GEMarkerXY();

/******************************************************************************/

int gtvy6uh55();

/******************************************************************************/
/******************************************************************************/
/************************************k*i*m*************************************/
/******************************y*o*n*g*-*s*h*i*k*******************************/
/******************************************************************************/
/******************************************************************************/

int isPointInWldWindow( win,x,y )
   WLDWINSIZE *win;
   double x,y;
{
   if (!(win->x1||win->y1||
         win->x2||win->y2)) return TRUE;
   /*
   If the specified point lies within the rectangle, the return value is nonzero.
   If the specified point does not lie within the rectangle, the return value is zero. 
   */
   return (win->x1<=(x)&&(x)<=win->x2&&
           win->y1<=(y)&&(y)<=win->y2);
}
int isPointInDevWindow( win,x,y )
   DEVWINSIZE *win;
   int x,y;
{
   if (!(win->x1||win->y1||
         win->x2||win->y2)) return TRUE;
   /*
   If the specified point lies within the rectangle, the return value is nonzero.
   If the specified point does not lie within the rectangle, the return value is zero. 
   */
   return (win->x1<=(x)&&(x)<=win->x2&&
           win->y1<=(y)&&(y)<=win->y2);
}

/*----------------------------------------------------------------------------*/
/*---BLOB2DMDATA--------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

int SetXMatrixData2D( array,m11,m12,m21,m22,m31,m32 )
   BLOB2DMDATA *array;
   double m11,m12,m21,m22,m31,m32;
{
   array->m11=m11;
   array->m12=m12;
   array->m21=m21;
   array->m22=m22;
   array->m31=m31;
   array->m32=m32;
   return TRUE;
}

/*----------------------------------------------------------------------------*/
/*---XMTX2D---------------------------------------------------------------*/
/*---XMTX3DATTR---------------------------------------------------------------*/
/*----------------------------------------------------------------------------*/

int AlloXMatrix2D( mtx )
   XMTX2D *mtx;
{
   (*mtx)=dmatrix(1,3,1,3);
   return SetXMatrix2DDefault(*mtx);
}

int FreeXMatrix2D( mtx )
   XMTX2D mtx;
{
   free_dmatrix(mtx,1,3,1,3);
   return TRUE;
}

int SetXMatrix2D( mtx,a,b,c,d,e,f )
   XMTX2D mtx;
   double a,b,c,d,e,f;
{
   mtx[1][1]=a; mtx[1][2]=b; mtx[1][3]=0.0;
   mtx[2][1]=c; mtx[2][2]=d; mtx[2][3]=0.0;
   mtx[3][1]=e; mtx[3][2]=f; mtx[3][3]=1.0;
   return TRUE;
}

int SetXMatrix2DDefault( mtx )
   XMTX2D mtx;
{
   mtx[1][1]=1.0; mtx[1][2]=0.0; mtx[1][3]=0.0;
   mtx[2][1]=0.0; mtx[2][2]=1.0; mtx[2][3]=0.0;
   mtx[3][1]=0.0; mtx[3][2]=0.0; mtx[3][3]=1.0;
   return TRUE;
}

/* Scaling Relative to a Fixed Point */
int XMatrix2DScale( xmtx,x,y,Sx,Sy,Combine )
   XMTX2D xmtx;
   double x,y,Sx,Sy;
   IPTRFN Combine;
{
   double **mtx;

   mtx=dmatrix(1,3,1,3);   
   SetXMatrix2DDefault(mtx);
   mtx[1][1]=Sx;
   mtx[2][2]=Sy;
   mtx[3][1]=(1.0-Sx)*x;
   mtx[3][2]=(1.0-Sy)*y;
   (*Combine)(xmtx,mtx);
   free_dmatrix(mtx,1,3,1,3);
   return TRUE;
}

int XMatrix2DTranslate( xmtx,Tx,Ty,Combine )
   XMTX2D xmtx;
   double Tx,Ty;
   IPTRFN Combine;
{
   double **mtx;

   mtx=dmatrix(1,3,1,3);  
   SetXMatrix2DDefault(mtx);
   mtx[3][1]=Tx;
   mtx[3][2]=Ty;
   (*Combine)(xmtx,mtx);
   free_dmatrix(mtx,1,3,1,3);
   return TRUE;
}  

/* Rotation About a Pivot Point */
int XMatrix2DRotate( xmtx,x,y,Angle,Combine )
   XMTX2D xmtx;
   double x,y,Angle;
   IPTRFN Combine;
{
   double cosine,sine;
   double **mtx;

   mtx=dmatrix(1,3,1,3);  
   SetXMatrix2DDefault(mtx);
   cosine=cos(Angle);
   sine  =sin(Angle);
   mtx[1][1]=cosine;
   mtx[1][2]=sine;
   mtx[2][1]=-sine;
   mtx[2][2]=cosine;
   mtx[3][1]=(1.0-cosine)*x+y*sine;
   mtx[3][2]=(1.0-cosine)*y-x*sine;
   (*Combine)(xmtx,mtx);
   free_dmatrix(mtx,1,3,1,3);
   return TRUE;
}  

int XMatrix2DStretch()
{
   return TRUE;
}  

int ComXMatrix2D( dst,src )
   XMTX2D dst,src;
/*
 * dst = dst x src
 */
{
   int i,j;
   double mtx[4][4];

   for (i=1;i<=3;i++) 
      for (j=1;j<=3;j++) 
         mtx[i][j]=dst[i][1]*src[1][j]+dst[i][2]*src[2][j]
                  +dst[i][3]*src[3][j];
   for (i=1;i<=3;i++) 
      for (j=1;j<=3;j++) 
         dst[i][j]=mtx[i][j];
   return TRUE;
}

int ComXMatrix2DAdobe( dst,src )
   XMTX2D dst,src;
/*
 * dst = src x dst : Adobe Postscript Language Style
 */
{
   int i,j;
   double mtx[4][4];
 
   for (i=1;i<=3;i++)
      for (j=1;j<=3;j++)
         mtx[i][j]=src[i][1]*dst[1][j]+src[i][2]*dst[2][j]
                  +src[i][3]*dst[3][j];
   for (i=1;i<=3;i++)
      for (j=1;j<=3;j++)
         dst[i][j]=mtx[i][j];
   return TRUE;
}

static XMTX2D XMatrix2DBackUp=(XMTX2D)0; /* for CopyXMatrix2D(),SaveXMatrix2D(),
                                            RestoreXMatrix2D() */
int CopyXMatrix2D( dst,src )
   XMTX2D dst,src;
{
   int i,j;

   for (i=1;i<=3;i++)
      for (j=1;j<=3;j++)
         dst[i][j]=src[i][j];
   return TRUE;
}

int SaveXMatrix2D()
{
   if (!XMatrix2DBackUp) XMatrix2DBackUp=dmatrix(1,3,1,3);
   return CopyXMatrix2D(XMatrix2DBackUp,myGEXMatrix2D);
}

int RestoreXMatrix2D()
{
   if (!XMatrix2DBackUp) return FALSE;
   CopyXMatrix2D(myGEXMatrix2D,XMatrix2DBackUp);
   free_dmatrix(XMatrix2DBackUp,1,3,1,3);
   XMatrix2DBackUp=(XMTX2D)0;
   return TRUE;
}

int xform( x,y )
   double *x,*y;
/*
 *  S(xscale,yscale) x R(angle) x T(xtrans,ytrans)
 *
 *                     +-       -+
 *                     | A  B  0 |
 *  [x' y' 1] = [x y 1]| C  D  0 |
 *                     | E  F  1 |
 *                     +-       -+
 */
{
   register double tmpX,tmpY;

   tmpX=*x;
   tmpY=*y;
   *x=myGEXMatrix2D[1][1]*tmpX+myGEXMatrix2D[2][1]*tmpY+myGEXMatrix2D[3][1];
   *y=myGEXMatrix2D[1][2]*tmpX+myGEXMatrix2D[2][2]*tmpY+myGEXMatrix2D[3][2];
   return TRUE;
}

int dxform( x,y )
   double *x,*y;
/*
 *  S(xscale,yscale) x R(angle)
 *
 *                     +-       -+
 *                     | A  B  0 |
 *  [x' y' 1] = [x y 1]| C  D  0 |
 *                     | 0  0  1 |
 *                     +-       -+
 */
{
   register double tmpX,tmpY;
 
   tmpX=*x;
   tmpY=*y;
   *x=myGEXMatrix2D[1][1]*tmpX+myGEXMatrix2D[2][1]*tmpY;
   *y=myGEXMatrix2D[1][2]*tmpX+myGEXMatrix2D[2][2]*tmpY;
   *x=ABS(*x);
   *y=ABS(*y);
   return TRUE;
}

int ixform( x,y )
   double *x,*y;
{
   double **mtx;
   register double tmpX,tmpY;

   mtx=matrix(1,3,1,3);
   MCopy(myGEXMatrix2D,mtx,1,3,1,3);
   invmatrix(mtx,3);
   tmpX=*x;
   tmpY=*y;
   *x=mtx[1][1]*tmpX+mtx[2][1]*tmpY+mtx[3][1];
   *y=mtx[1][2]*tmpX+mtx[2][2]*tmpY+mtx[3][2];
   free_matrix(mtx,1,3,1,3);
   return TRUE;
}

int idxform()
{
   return TRUE;
}

int xform_it( x1,y1,x2,y2 )
   double *x1,*y1,*x2,*y2;
{
   xform( x1,y1 );
   return xform( x2,y2 );
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

int GEDraw( pDisplay,pBlobList,pViewport )
   char *pDisplay; /* MYDISPLAY* */
   BLOBLIST *pBlobList;
   GERECT *pViewport; /* viewport */
{
   return GEDrawEx(pDisplay,pBlobList,pViewport,GE_EventScaleByObject,0,0,1.0);
}

int GEDrawEx(
    char *pDisplay, /* MYDISPLAY* */
    BLOBLIST *pBlobList,
    GERECT *pViewport,
    int nEvent,int nEventX,int nEventY, /* ref.UL=0,0 */
    float fEventFactor /* default=1.0 */
)
{
   static XMTX2D mtx;   
   static int objScale=GE_EventScaleByObject;
   GERECT Rect;
   double dx,dy;

   myDisplay=(MYDISPLAY*)pDisplay;

   if (!mtx) AlloXMatrix2D(&mtx);
   if (!pViewport) GEGetGeometry(myDisplay,&Rect);
   else memcpy(&Rect,pViewport,sizeof(GERECT));
   switch (nEvent) {
   case 'z' : nEvent=GE_EventZoomIn       ;break;
   case 'Z' : nEvent=GE_EventZoomOut      ;break;
   case 't' : nEvent=GE_EventTranslate    ;break;
   case 'k' : nEvent=GE_EventMoveUp       ;break;
   case 'j' : nEvent=GE_EventMoveDown     ;break;
   case 'h' : nEvent=GE_EventMoveLeft     ;break;
   case 'l' : nEvent=GE_EventMoveRight    ;break;
   case 'r' : nEvent=GE_EventRedraw       ;break;
   case 'f' : nEvent=GE_EventScaleByObject;break;
   case 'F' : nEvent=GE_EventScaleByWindow;break;
   case 'p' : nEvent=GE_EventDumpToHPS    ;break;
   case 'P' : nEvent=GE_EventDumpToVPS    ;break;
   }
   switch (nEvent) {
   case GE_EventZoomIn :
   case GE_EventZoomOut :
      if (fEventFactor<=0.1) fEventFactor=(float)0.1;
      if (fEventFactor>=10.0) fEventFactor=(float)10.0;
      ScreenRectXY2Norm(objScale,&Rect,nEventX,nEventY,&dx,&dy);
      /* Not bad, but I dont make up my mind at this time on its usage.
      XMatrix2DScale(mtx,dx,dy,fEventFactor,fEventFactor,ComXMatrix2DAdobe);
      */
      dx=0.5-dx;
      dy=0.5-dy;
      XMatrix2DTranslate(mtx,dx,dy,ComXMatrix2D);
      XMatrix2DScale(mtx,0.5,0.5,fEventFactor,fEventFactor,ComXMatrix2D);
      goto DRAW;
   case GE_EventTranslate :
      ScreenRectXY2Norm(objScale,&Rect,nEventX,nEventY,&dx,&dy);
      mtx[3][1]=dx-0.5;
      mtx[3][2]=dy-0.5;
      goto DRAW;
   case GE_EventMoveLeft :
      XMatrix2DTranslate(mtx,(double)fEventFactor,0.0,ComXMatrix2DAdobe);
      goto DRAW;
   case GE_EventMoveDown :
      XMatrix2DTranslate(mtx,0.0,(double)fEventFactor,ComXMatrix2DAdobe);
      goto DRAW;
   case GE_EventMoveUp :
      XMatrix2DTranslate(mtx,0.0,-(double)fEventFactor,ComXMatrix2DAdobe);
      goto DRAW;
   case GE_EventMoveRight :
      XMatrix2DTranslate(mtx,-(double)fEventFactor,0.0,ComXMatrix2DAdobe);
      goto DRAW;
   case GE_EventRedraw :
      goto DRAW;
   case GE_EventScaleByObject :
      objScale=GE_EventScaleByObject;
      SetXMatrix2DDefault(mtx);
      goto DRAW;
   case GE_EventScaleByWindow :
      objScale=GE_EventScaleByWindow;
      SetXMatrix2DDefault(mtx);
      goto DRAW;
   case GE_EventDumpToHPS : /* Postscript BLOB Dump on a horizontal page */
   case GE_EventDumpToVPS : /* Postscript BLOB Dump on a vertical page */
      if (!myPSFileNameForPrintting||!*myPSFileNameForPrintting) return FALSE;
      GEPrintOpen(
         myPSFileNameForPrintting,
         GE_PSColor,
         nEvent==GE_EventDumpToHPS?GE_Landscape:GE_Portrait,
         mtx);
      GEPrintSetProcedure();
      GEPrintProcess(pBlobList);
      GEPrintClose();
      return TRUE;
   }
   return FALSE;
DRAW:
   GEDrawOpen(&Rect,objScale,mtx);
   GEDrawSetProcedure();
   GEDrawProcess(pBlobList);
   GEDrawClose();
   return TRUE;
}

int GEPrint( /* functions like Export or Save-as, 20020914 */
   char *pDisplay, /* MYDISPLAY* */
   BLOBLIST *pBlobList,
   GERECT *pViewport,
   int nEvent,int nEventX,int nEventY,
   float fEventFactor, /* default=1.0 */
   char *pFileName,
   int bLandscape
)
{
   int nResult;

   if (!pFileName||!*pFileName) return FALSE;
   myPSFileNameForPrintting=strdpl(pFileName);
   nEvent=bLandscape?GE_EventDumpToHPS:GE_EventDumpToVPS;
   nResult=GEDrawEx(pDisplay,pBlobList,pViewport,nEvent,nEventX,nEventY,fEventFactor);
   freeEx(myPSFileNameForPrintting);
   return nResult;
}

static
void ScreenRectXY2Norm( objScale,rect,rx,ry,nx,ny )
   int objScale;
   GERECT *rect;
   int rx,ry;
   double *nx,*ny; /* return x,y */
{
   double dx,dy;

   switch (objScale) {
   case GE_EventScaleByWindow : 
      dx=(double)rx/rect->width;
      dy=1.0-(double)ry/rect->height;
      break;
   case GE_EventScaleByObject :
   default :
      if (rect->width>=rect->height) {
         rx-=(rect->width-rect->height)>>1;
         dx=(double)rx/rect->height;
         dy=1.0-(double)ry/rect->height;
      } else {
         dx=(double)rx/rect->width;
         ry-=(rect->height-rect->width)>>1;
         dy=1.0-(double)ry/rect->width;
      }
      break;
   }
   *nx=dx;
   *ny=dy;
}

static
int GEDrawOpen( rect,nEvent,xmtx )
   GERECT *rect;
   GEDRAWEVENT nEvent;
   XMTX2D xmtx;
{
   double XScale,YScale,XTranslate,YTranslate;

   AlloXMatrix2D(&myGEXMatrix2D);
   switch (nEvent) {
   case GE_EventScaleByObject :
   default :   
      if (rect->width>=rect->height) {
         XScale=(double)rect->height;
         YScale=-XScale;
         XTranslate=(double)(rect->width-rect->height)/2.0+rect->x;
         YTranslate=(double)rect->height+rect->y;
      } else {
         XScale=(double)rect->width;
         YScale=-XScale;
         XTranslate=(double)rect->x;
         YTranslate=(double)(rect->height-(rect->height-rect->width)/2.0)+rect->y;
      }
      break;
   case GE_EventScaleByWindow :
      XScale=(double)rect->width;
      YScale=(double)rect->height*-1.0;
      XTranslate=(double)rect->x;
      YTranslate=(double)(rect->height+rect->y);
      break;   
   }
   XMatrix2DScale(myGEXMatrix2D,0.0,0.0,XScale,YScale,ComXMatrix2DAdobe);
   XMatrix2DTranslate(myGEXMatrix2D,XTranslate,YTranslate,ComXMatrix2D);

   if (xmtx) ComXMatrix2DAdobe(myGEXMatrix2D,xmtx);

   AlloXMatrix2D(&myDeviceXmtx2D);
   SetXMatrix2D(myDeviceXmtx2D,myGEXMatrix2D[1][1],myGEXMatrix2D[1][2],
                               myGEXMatrix2D[2][1],myGEXMatrix2D[2][2],
                               myGEXMatrix2D[3][1],myGEXMatrix2D[3][2]);
   myBufPoint=(GEPOINT*)malloc(sizeof(GEPOINT)*GE_BUFSIZE);
   myBufLine =(GELINE *)malloc(sizeof(GELINE )*GE_BUFSIZE);
   myBufArc  =(GEARC  *)malloc(sizeof(GEARC  )*GE_BUFSIZE);
   return TRUE;
}

static
int GEDrawClose()
{
   myDisplay=NULL;
   FreeXMatrix2D(myGEXMatrix2D);
   FreeXMatrix2D(myDeviceXmtx2D);
   myGEXMatrix2D=NULL;
   myDeviceXmtx2D=NULL;
   free(myBufPoint);
   free(myBufLine);
   free(myBufArc);
   return TRUE;
}

static
int GEDrawSetProcedure()
{
   BLSetProcedure(BL_COMMAND, NULL        );
   BLSetProcedure(BL_HEADER,  doHeader    );
   BLSetProcedure(BL_2DMDATA, doXmtx2DData);
   BLSetProcedure(BL_3DMDATA, doXmtx3DData); 
   BLSetProcedure(BL_GC,      doGC        );
   BLSetProcedure(BL_DATA,    NULL        );
   BLSetProcedure(BL_POINT,   doPoint     );
   BLSetProcedure(BL_LINE,    doLine      );
   BLSetProcedure(BL_POLY,    doPolyline  );
   BLSetProcedure(BL_ARC,     doArc       ); 
   BLSetProcedure(BL_TEXT,    doText      );
   BLSetProcedure(BL_CLIPWIN, doClipWin   );
   BLSetProcedure(BL_PRINT,   NULL        );
   return TRUE;
}

static
int GEDrawProcess( list )
   BLOBLIST *list; 
{ 
   return BLExecute(list);
}

static
int GECheckCount( tot,func_name )
   int *tot;
   char *func_name;
{
   if (*tot>GE_BUFSIZE) {
      fprintf(stderr,"Warning, ge_tot(=%d)>GE_BUFSIZE(=%d) in %s()\n",
              *tot,GE_BUFSIZE,func_name);
      *tot=GE_BUFSIZE;
      return FALSE;
   }
   return TRUE;
}

static 
int doHeader( ptr,tot )
   BLOBHEADER *ptr;
   int tot;
{
   XMTX2D xmtx;

   SetXMatrix2D(
      myGEXMatrix2D,
      myDeviceXmtx2D[1][1],myDeviceXmtx2D[1][2],
      myDeviceXmtx2D[2][1],myDeviceXmtx2D[2][2],
      myDeviceXmtx2D[3][1],myDeviceXmtx2D[3][2]);
   AlloXMatrix2D(&xmtx);
   SetXMatrix2D(xmtx,ptr->m11,ptr->m12,ptr->m21,ptr->m22,ptr->m31,ptr->m32);
   ComXMatrix2DAdobe(myGEXMatrix2D,xmtx);
   FreeXMatrix2D(xmtx);

   GESetFontMatrixDefault();

   if (ptr->reset) {  // ????? 꼭필요한가??? window 평션은 window에서..
      GEWindowClear(myDisplay);
/*
      printf(" .. display refresh ... in gegraph.c\n");
*/
   }
   return TRUE;
}

static 
int doXmtx2DData( ptr,tot )
   BLOB2DMDATA *ptr;
   int tot;
{
   XMTX2D xmtx;

   AlloXMatrix2D(&xmtx);
   SetXMatrix2D(xmtx,ptr->m11,ptr->m12,ptr->m21,ptr->m22,ptr->m31,ptr->m32);
   ComXMatrix2DAdobe(myGEXMatrix2D,xmtx);
   FreeXMatrix2D(xmtx);
   return TRUE;
}

static 
int doXmtx3DData( ptr,tot )
   BLOB3DMDATA *ptr;
   int tot;
{
   printf("Not, ... yet in doXmtx3DData()\n");
   exit(1);
   return FALSE;
}

static
int doGC( ptr,tot )
   BLOBGC *ptr;
   int tot; 
{   
   if (ptr->gc_mask&GE_GCMaskFont) {
      myGEDrawText=ptr->font_type==GE_FontVector ? GEDrawTextStroke:GEDrawText;
      if (!*ptr->font) {
         strcpy(ptr->font,"*");
         ptr->font_type=GE_FontVector;
      }
      if (ptr->font_type==GE_FontVector) {
         GESetStrokeTextFormat(ptr->text_format);
         {
         XMTX2D mtxFont,mtx;
         BLOB2DMDATA m2d;
         AlloXMatrix2D(&mtxFont);
         AlloXMatrix2D(&mtx);
         GESetFontMatrixDefault();
         GEGetFontMatrix(&m2d);
         SetXMatrix2D(mtxFont,m2d.m11,m2d.m12,m2d.m21,m2d.m22,m2d.m31,m2d.m32);
         memcpy((char*)&m2d,(char*)&(ptr->font_matrix),sizeof(BLOB2DMDATA));
         SetXMatrix2D(mtx,m2d.m11,m2d.m12,m2d.m21,m2d.m22,m2d.m31,m2d.m32);
         ComXMatrix2DAdobe(mtxFont,mtx);
         //XMatrix2DRotate(mtxFont,0,0,RADIAN(ptr->font_angle/10),ComXMatrix2D);
         m2d.m11=mtxFont[1][1];m2d.m12=mtxFont[1][2];
         m2d.m21=mtxFont[2][1];m2d.m22=mtxFont[2][2];
         m2d.m31=mtxFont[3][1];m2d.m32=mtxFont[3][2];
         GESetFontMatrix(&m2d);
         FreeXMatrix2D(mtx);
         FreeXMatrix2D(mtxFont);
         }
      }
   }
   GEChangeGC(myDisplay,ptr);
   return TRUE;
}

static
int doPoint( ptr,tot )
   BLOBPOINT *ptr;
   int tot; 
{
   register int i;
   double x,y;

   GECheckCount(&tot,"doPoint");
   for (i=0;i<tot;i++) {
      x=ptr[i].x;
      y=ptr[i].y;
      xform(&x,&y);
      myBufPoint[i].x=(short)x;
      myBufPoint[i].y=(short)y;
   }
   GEDrawPoint(myDisplay,myBufPoint,tot);
   return TRUE;
}

static
int doLine( ptr,tot )
   BLOBLINE *ptr;
   int tot; 
{
   register int i;
   double x1,y1,x2,y2;
 
   GECheckCount(&tot,"doLine");
   for (i=0;i<tot;i++) {
      x1=ptr[i].x1;
      y1=ptr[i].y1; 
      x2=ptr[i].x2;
      y2=ptr[i].y2; 
      xform_it(&x1,&y1,&x2,&y2);
      myBufLine[i].x1=(short)x1;
      myBufLine[i].y1=(short)y1;
      myBufLine[i].x2=(short)x2;
      myBufLine[i].y2=(short)y2;
   }
   GEDrawLine(myDisplay,myBufLine,tot);
   return TRUE;
}

static
int doPolyline( ptr,tot )
   BLOBPOINT *ptr;
   int tot; 
{
   register int i;
   double x,y;

   GECheckCount(&tot,"doPolyline");
   for (i=0;i<tot;i++) {
      x=ptr[i].x;
      y=ptr[i].y;
      xform(&x,&y);
      myBufPoint[i].x=(short)x;
      myBufPoint[i].y=(short)y;
   }
   GEDrawPoly(myDisplay,myBufPoint,tot,NULL);
   return TRUE;
}

static
int doArc( ptr,tot )
   BLOBARC *ptr;
   int tot; 
{
   register int i;
   double x,y,width,height;
 
   GECheckCount(&tot,"doArc");
   for (i=0;i<tot;i++) { 
      x=ptr[i].x; 
      y=ptr[i].y;  
      xform(&x,&y);
      width=ptr[i].width;
      height=ptr[i].height;
      dxform(&width,&height);
      myBufArc[i].x=(short)x; 
      myBufArc[i].y=(short)y;
      myBufArc[i].width= (unsigned int)width;
      myBufArc[i].height=(unsigned int)height;
      myBufArc[i].angle1=(short)(ptr[i].angle1*11520/PI);
      myBufArc[i].angle2=(short)(ptr[i].angle2*11520/PI);
   } 
   GEDrawArc(myDisplay,myBufArc,tot);
   return FALSE;
}

static
int doText( ptr,tot ) 
   BLOBTEXT *ptr;
   int tot; 
{
   double x,y;
   char *p;

   SaveXMatrix2D();
   x=((BLOBPOINT*)ptr)->x;
   y=((BLOBPOINT*)ptr)->y;
   xform(&x,&y);
   p=(char*)ptr;
   p+=sizeof(BLOBPOINT);
   myGEDrawText==GEDrawTextStroke ?
      GEDrawTextStroke(myDisplay,(int)x,(int)y,p):
      GEDrawText(myDisplay,(int)x,(int)y,p,NULL);
   RestoreXMatrix2D();
   return TRUE;
}

static 
int doClipWin( ptr,tot )
   BLOBCLIPWIN *ptr;
   int tot;
{
   double x1,y1,x2,y2;

   x1=ptr->x1;
   y1=ptr->y1;
   xform(&x1,&y1);
   x2=ptr->x2;
   y2=ptr->y2;
   xform(&x2,&y2);
   myBufPoint[0].x=(short)x1;
   myBufPoint[0].y=(short)y1;
   myBufPoint[1].x=(short)x2;
   myBufPoint[1].y=(short)y2;
   GEClipWin(myDisplay,myBufPoint,2);
   return TRUE;
}

static
int doPointRect( ptr,tot,pRect )
   BLOBPOINT *ptr;
   int tot;
   GERECT *pRect;
{
   int i;
   double x,y,xMin,xMax,yMin,yMax;

   x=ptr[0].x;
   y=ptr[0].y;
   xform(&x,&y);
   xMin=xMax=x;
   yMin=yMax=y;
   for (i=1;i<tot;i++) {
      x=ptr[i].x;
      y=ptr[i].y;
      xform(&x,&y);
      xMin=MIN(xMin,x);
      xMax=MAX(xMax,x);
      yMin=MIN(yMin,y);
      yMax=MAX(yMax,y);
   }
   pRect->x=(int)xMin;
   pRect->y=(int)yMin;
   pRect->width=(int)(xMax-xMin);
   pRect->height=(int)(yMax-yMin);
   return TRUE;
}

static
int doLineRect( ptr,tot,pRect )
   BLOBLINE *ptr;
   int tot;
   GERECT *pRect;
{
   int i;
   double x1,y1,x2,y2,xMin,xMax,yMin,yMax;

   xMin=xMax=ptr[0].x1;
   yMin=yMax=ptr[0].y1;
   for (i=0;i<tot;i++) {
      x1=ptr[i].x1;
      y1=ptr[i].y1; 
      x2=ptr[i].x2;
      y2=ptr[i].y2; 
      xform_it(&x1,&y1,&x2,&y2);
      xMin=MIN(xMin,MIN(x1,x2));
      xMax=MAX(xMax,MAX(x1,x2));
      yMin=MIN(yMin,MIN(y1,y2));
      yMax=MAX(yMax,MAX(y1,y2));
   }
   pRect->x=(int)xMin;
   pRect->y=(int)yMin;
   pRect->width=(int)(xMax-xMin);
   pRect->height=(int)(yMax-yMin);
   return TRUE;
}

static
int doPolylineRect( ptr,tot,pRect )
   BLOBPOINT *ptr;
   int tot; 
   GERECT *pRect;
{
   return doPointRect(ptr,tot,pRect);
}

static
int doArcRect( ptr,tot,pRect )
   BLOBARC *ptr;
   int tot;
   GERECT *pRect;
{
   int i;
   double x1,y1,x2,y2,width,height;
   double xMin,xMax,yMin,yMax;

   x1=ptr[0].x;
   y1=ptr[0].y;
   xform(&x1,&y1);
   xMin=xMax=x1;
   yMin=yMax=y1;
   for (i=0;i<tot;i++) { 
      x1=ptr[i].x;
      y1=ptr[i].y;  
      xform(&x1,&y1);
      width=ptr[i].width;
      height=ptr[i].height;
      dxform(&width,&height);
      x2=x1+width;
      y2=y1+height;
      xMin=MIN(xMin,x1);
      xMax=MAX(xMax,x2);
      yMin=MIN(yMin,y1);
      yMax=MAX(yMax,y2);
   }
   pRect->x=(int)xMin;
   pRect->y=(int)yMin;
   pRect->width=(int)(xMax-xMin);
   pRect->height=(int)(yMax-yMin);
   return FALSE;
}

static
int doTextRect( ptr,tot,pRect )
   BLOBTEXT *ptr;
   int tot; 
   GERECT *pRect;
{
   double x,y;
   char *p;
   GERECT Rect;

   SaveXMatrix2D();
   x=((BLOBPOINT*)ptr)->x;
   y=((BLOBPOINT*)ptr)->y;
   xform(&x,&y);
   p=(char*)ptr;
   p+=sizeof(BLOBPOINT);
   GEDrawText(myDisplay,(int)x,(int)y,p,&Rect);
   RestoreXMatrix2D();
   return TRUE;
}

static
int doHeaderForMarker( ptr,tot )
   BLOBHEADER *ptr;
   int tot;
{
   XMTX2D xmtx;

   SetXMatrix2D(myGEXMatrix2D,myDeviceXmtx2D[1][1],myDeviceXmtx2D[1][2],
                              myDeviceXmtx2D[2][1],myDeviceXmtx2D[2][2],
                              myDeviceXmtx2D[3][1],myDeviceXmtx2D[3][2]);
   AlloXMatrix2D(&xmtx);
   SetXMatrix2D(xmtx,ptr->m11,ptr->m12,
                     ptr->m21,ptr->m22,
                     ptr->m31,ptr->m32);
   ComXMatrix2DAdobe(myGEXMatrix2D,xmtx);
   FreeXMatrix2D(xmtx);
   return TRUE;
}

int clipper_line( xmin,xmax,ymin,ymax,x1,y1,x2,y2 )
   double xmin,xmax,ymin,ymax;
   double *x1,*y1,*x2,*y2;
/*
 * Cohen-Sutherland Algorithm + (c)Y.S.Kim
 */
{
   double a,b;

#define is_point_win_in(x,y) \
          (xmin<=(x) && (x)<=xmax && \
           ymin<=(y) && (y)<=ymax)
#define is_point_win_out(x,y) \
         (!is_point_win_in(x,y))

   if (is_point_win_out(*x1,*y1)
   &&  is_point_win_out(*x2,*y2)
   && ((*x1<xmin&&*x2<xmin) || (xmax<*x1&&xmax<*x2)
     ||(*y1<ymin&&*y2<ymin) || (ymax<*y1&&ymax<*y2)))
      return FALSE;

   if (is_point_win_in(*x1,*y1)
   &&  is_point_win_in(*x2,*y2))
      return TRUE;

   if (*x2!=*x1) {
      a=(*y2-*y1)/(*x2-*x1);
      b=*y1-a**x1;
      if (*x1<xmin) {
         *y1=a*xmin+b;
         *x1=xmin;
      } else if (xmax<*x1) {
         *y1=a*xmax+b;
         *x1=xmax;
      }
      if (*y1<ymin) {
         *x1=(ymin-b)/a;
         *y1=ymin;
      } else if (ymax<*y1) {
         *x1=(ymax-b)/a;
         *y1=ymax;
      }
      if (*x2<xmin) {
         *y2=a*xmin+b;
         *x2=xmin;
      } else if (xmax<*x2) {
         *y2=a*xmax+b;
         *x2=xmax;
      }
      if (*y2<ymin) {
         *x2=(ymin-b)/a;
         *y2=ymin;
      } else if (ymax<*y2) {
         *x2=(ymax-b)/a;
         *y2=ymax;
      }
   } else {
      *y1=(*y1<ymin) ? ymin: (*y1>ymax) ? ymax:*y1; /* 2K.0626 */
      *y2=(*y2<ymin) ? ymin: (*y2>ymax) ? ymax:*y2; /* 2K.0626 */
   }
   return TRUE+1; /* clipped */

#undef  is_point_win_out
#undef  is_point_win_in
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

int GEMarkerXY( disp_node,blob_list,tracer,WinScale,mtx,x,y )
   MYDISPLAY *disp_node;
   BLOBLIST *blob_list;
   BLOBNODE *tracer;
   int WinScale;
   XMTX2D mtx;
   double *x,*y;
{
   BLOBNODE *blob_node;

   GEDrawOpen(disp_node,WinScale,mtx);
   blob_node=blob_list->head;
   while (blob_node!=tracer) {
      switch ((int)blob_node->any.type) {
      case BL_HEADER  :
         doHeaderForMarker(BLNodeObjAddr(blob_node),blob_node->any.total);
         break;
      case BL_2DMDATA :
         doXmtx2DData(BLNodeObjAddr(blob_node),blob_node->any.total);
         break;
      }
      blob_node=blob_node->next;
   }
   *x=((BLOBDATA*)BLNodeObjAddr(tracer))->x;
   *y=((BLOBDATA*)BLNodeObjAddr(tracer))->y;
   xform(x,y);
   GEDrawClose();
   return TRUE;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

#define RECTX1(s) (int)((s).x)
#define RECTY1(s) (int)((s).y)
#define RECTX2(s) (int)(RECTX1(s)+(s).width-1)
#define RECTY2(s) (int)(RECTY1(s)+(s).height-1)

/*
   23|12
   --+--
   34|41
*/
#define XID00  0 /* exclusion */
#define XID12  1 /* cross at right-upper corner */
#define XID23  2 /* cross at left-upper  corner */
#define XID34  3 /* cross at left-lower  corner */
#define XID41  4 /* cross at right-lower corner */
#define XID11  5 /* bar-in cross  at right edge */
#define XID22  6 /* bar-in cross  at upper edge */
#define XID33  7 /* bar-in cross  at left  edge */
#define XID44  8 /* bar-in cross  at lower edge */
#define XID10  9 /* bar-out cross at right edge */
#define XID20 10 /* bar-out cross at upper edge */
#define XID30 11 /* bar-out cross at left  edge */
#define XID40 12 /* bar-out cross at lower edge */
#define XID55 13 /* box-in  cross  */
#define XID66 14 /* box-out cross */
#define XID77 15 /* bar cross at upper & lower edge */
#define XID88 16 /* bar cross at left & right  edge */

/*
   1---2
   |   |
   4---3
*/
#define ISCORNER1XROSSED(under,over) \
   ((RECTX1(under)<=RECTX1(over)) ? (RECTX1(over)<=RECTX2(under)) ? \
    (RECTY1(under)<=RECTY1(over)) ? (RECTY1(over)<=RECTY2(under)) ? \
    1:0:0:0:0)
#define ISCORNER2XROSSED(under,over) \
   ((RECTX1(under)<=RECTX2(over)) ? (RECTX2(over)<=RECTX2(under)) ? \
    (RECTY1(under)<=RECTY1(over)) ? (RECTY1(over)<=RECTY2(under)) ? \
    1:0:0:0:0)
#define ISCORNER3XROSSED(under,over) \
   ((RECTX1(under)<=RECTX2(over)) ? (RECTX2(over)<=RECTX2(under)) ? \
    (RECTY1(under)<=RECTY2(over)) ? (RECTY2(over)<=RECTY2(under)) ? \
    1:0:0:0:0)
#define ISCORNER4XROSSED(under,over) \
   ((RECTX1(under)<=RECTX1(over)) ? (RECTX1(over)<=RECTX2(under)) ? \
    (RECTY1(under)<=RECTY2(over)) ? (RECTY2(over)<=RECTY2(under)) ? \
    1:0:0:0:0)
#define ISALLCORNERXROSSED(under,over) \
   ((RECTX1(over)<RECTX1(under)) ? (RECTY1(over)<RECTY1(under)) ? \
    (RECTX2(under)<RECTX2(over)) ? (RECTY2(under)<RECTY2(over)) ? \
    1:0:0:0:0)
#define ISEDGE1XROSSED(under,over) \
   ((RECTX1(under)<=RECTX1(over)) ? (RECTX1(over)<=RECTX2(under)) ? \
    (RECTY1(over)<=RECTY1(under)) ? (RECTY2(under)<=RECTY2(over)) ? \
    1:0:0:0:0)
#define ISEDGE2XROSSED(under,over) \
   ((RECTY1(under)<=RECTY1(over)) ? (RECTY1(over)<=RECTY2(under)) ? \
    (RECTX1(over)<=RECTX1(under)) ? (RECTX2(under)<=RECTX2(over)) ? \
    1:0:0:0:0)
#define ISEDGE3XROSSED(under,over) \
   ((RECTX1(under)<=RECTX2(over)) ? (RECTX2(over)<=RECTX2(under)) ? \
    (RECTY1(over)<=RECTY1(under)) ? (RECTY2(under)<=RECTY2(over)) ? \
    1:0:0:0:0)
#define ISEDGE4XROSSED(under,over) \
   ((RECTY1(under)<=RECTY2(over)) ? (RECTY2(over)<=RECTY2(under)) ? \
    (RECTX1(over)<=RECTX1(under)) ? (RECTX2(under)<=RECTX2(over)) ? \
    1:0:0:0:0)

static 
int GetXRectID( pR1,pR2 )
   const GERECT *pR1,*pR2;
{
   int nXID=~(~0);

   if (ISCORNER1XROSSED(*pR1,*pR2))
      nXID |= 0x0001; 
   if (ISCORNER2XROSSED(*pR1,*pR2))
      nXID |= 0x0010; 
   if (ISCORNER3XROSSED(*pR1,*pR2))
      nXID |= 0x0100; 
   if (ISCORNER4XROSSED(*pR1,*pR2))
      nXID |= 0x1000; 
   if (nXID) {
      switch (nXID) {
      case 0x0001 : return XID12;
      case 0x0010 : return XID23;
      case 0x0100 : return XID34;
      case 0x1000 : return XID41;
      case 0x1001 : return XID11;
      case 0x0011 : return XID22;
      case 0x0110 : return XID33;
      case 0x1100 : return XID44;
      case 0x1111 : return XID55;
      }
   } else {
      if (ISEDGE1XROSSED(*pR1,*pR2))
         nXID |= 0x0001; 
      if (ISEDGE2XROSSED(*pR1,*pR2))
         nXID |= 0x0010; 
      if (ISEDGE3XROSSED(*pR1,*pR2))
         nXID |= 0x0100; 
      if (ISEDGE4XROSSED(*pR1,*pR2))
         nXID |= 0x1000; 
      if (ISALLCORNERXROSSED(*pR1,*pR2))
         return XID66;
      switch (nXID) {
      case 0x0001 : return XID10;
      case 0x0010 : return XID20;
      case 0x0100 : return XID30;
      case 0x1000 : return XID40;
      case 0x0101 : return XID77;
      case 0x1010 : return XID88;
      }
   }
   return XID00;
}

static
int NewRectNodes( nTotal,pHeader )
  int nTotal;
  GERECTNODE **pHeader;
{
  int i;
  GERECTNODE *pRN,*preRN;

  *pHeader=preRN=salloc(GERECTNODE,1);
  memset((char*)preRN,0,sizeof(GERECTNODE));
  for (i=2;i<=nTotal;i++) {
     pRN=salloc(GERECTNODE,1);
     memset((char*)pRN,0,sizeof(GERECTNODE));
     preRN=preRN->next=pRN;
  }
  preRN->next=NULL;
  return TRUE;
}

static
int BreakdownRectIntoPieces( pRect1,pRect2,nXID,ppRNs )
   const GERECT *pRect1,*pRect2;
   int nXID;
   GERECTNODE **ppRNs;
{
   int nCount;
   int ax1,ay1,ax2,ay2,bx1,by1,bx2,by2;
   GERECTNODE *n;
  /*
   *  ax1,ay1 |       bx1,by1
   *     +----+----+     +------+
   *     | 23 | 12 |     |      | 
   *   --+----+----+--   |      | 
   *     | 34 | 41 |     +------+
   *     +----+----+         bx2,by2
   *          | ax2,ay2
   */
   ax1 = RECTX1(*pRect1);
   ay1 = RECTY1(*pRect1);
   ax2 = RECTX2(*pRect1);
   ay2 = RECTY2(*pRect1);
   bx1 = RECTX1(*pRect2);
   by1 = RECTY1(*pRect2);
   bx2 = RECTX2(*pRect2);
   by2 = RECTY2(*pRect2);
 
   switch (nXID) {
   case XID11 :
      NewRectNodes(nCount=4,ppRNs);
      n = *ppRNs;
      n->rect.x= bx1;
      n->rect.y= by1;
      n->rect.width= ax2-bx1+1;
      n->rect.height= pRect2->height;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by2+1;
      n->rect.width= pRect1->width;
      n->rect.height= ay2-by2;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by1;
      n->rect.width= bx1-ax1;
      n->rect.height= pRect2->height;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= pRect1->width;
      n->rect.height= by1-ay1;
      return nCount;
   case XID22 :
      NewRectNodes( nCount=4,ppRNs );
      n = *ppRNs;
      n->rect.x= bx1;
      n->rect.y= by1;
      n->rect.width= pRect2->width;
      n->rect.height= ay2-by1+1;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by1;
      n->rect.width= bx1-ax1;
      n->rect.height= ay2-by1+1;
      n = n->next;
      n->rect.x= bx2+1;
      n->rect.y= by1;
      n->rect.width= ax2-bx2;
      n->rect.height= ay2-by1+1;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= pRect1->width;
      n->rect.height= by1-ay1;
      return nCount;
   case XID33 :
      NewRectNodes( nCount=4,ppRNs );
      n = *ppRNs;
      n->rect.x= ax1;
      n->rect.y= by1;
      n->rect.width= bx2-ax1+1;
      n->rect.height= pRect2->height;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by2+1;
      n->rect.width= pRect1->width;
      n->rect.height= ay2-by2;
      n = n->next;
      n->rect.x= bx2+1;
      n->rect.y= by1;
      n->rect.width= ax2-bx2;
      n->rect.height= pRect2->height;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= pRect1->width;
      n->rect.height= by1-ay1;
      return nCount;
   case XID44 :
      NewRectNodes( nCount=4,ppRNs );
      n = *ppRNs;
      n->rect.x= bx1;
      n->rect.y= ay1;
      n->rect.width= pRect2->width;
      n->rect.height= by2-ay1+1;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by2+1;
      n->rect.width= pRect1->width;
      n->rect.height= ay2-by2;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= bx1-ax1;
      n->rect.height= by2-ay1+1;
      n = n->next;
      n->rect.x= bx2+1;
      n->rect.y= ay1;
      n->rect.width= ax2-bx2;
      n->rect.height= by2-ay1+1;
      return nCount;
   case XID10 :
      NewRectNodes( nCount=2,ppRNs );
      n = *ppRNs;
      n->rect.x= bx1;
      n->rect.y= ay1;
      n->rect.width= ax2-bx1+1;
      n->rect.height= pRect1->height;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= bx1-ax1;
      n->rect.height= pRect1->height;
      return nCount;
   case XID20 :
      NewRectNodes( nCount=2,ppRNs );
      n = *ppRNs; 
      n->rect.x= ax1; 
      n->rect.y= by1; 
      n->rect.width= pRect1->width; 
      n->rect.height= ay2-by1+1; 
      n = n->next; 
      n->rect.x= ax1; 
      n->rect.y= ay1; 
      n->rect.width= pRect1->width; 
      n->rect.height= by1-ay1; 
      return nCount;
   case XID30 :
      NewRectNodes( nCount=2,ppRNs );
      n = *ppRNs;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= bx2-ax1+1;
      n->rect.height= pRect1->height;
      n = n->next; 
      n->rect.x= bx2+1;
      n->rect.y= ay1;
      n->rect.width= ax2-bx2;
      n->rect.height= pRect1->height;
      return nCount;
   case XID40 :
      NewRectNodes( nCount=2,ppRNs );
      n = *ppRNs; 
      n->rect.x= ax1; 
      n->rect.y= ay1; 
      n->rect.width= pRect1->width; 
      n->rect.height= by2-ay1+1; 
      n = n->next; 
      n->rect.x= ax1; 
      n->rect.y= by2+1; 
      n->rect.width= pRect1->width; 
      n->rect.height= ay2-by2; 
      return nCount;
   case XID55 :
      NewRectNodes( nCount=5,ppRNs );
      n = *ppRNs;
      n->rect.x= bx1;
      n->rect.y= by1;
      n->rect.width= pRect2->width;
      n->rect.height= pRect2->height;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by2+1;
      n->rect.width= pRect1->width;
      n->rect.height= ay2-by2;
      n = n->next;
      n->rect.x=ax1;
      n->rect.y= by1;
      n->rect.width= bx1-ax1;
      n->rect.height= pRect2->height;
      n = n->next;
      n->rect.x= bx2+1;
      n->rect.y= by1;
      n->rect.width= ax2-bx2;
      n->rect.height= pRect2->height;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= pRect1->width;
      n->rect.height= by1-ay1;
      return nCount;
   case XID66 :
      NewRectNodes( nCount=1,ppRNs );
      n = *ppRNs;
      n->rect.x= pRect1->x;
      n->rect.y= pRect1->y;
      n->rect.width= pRect1->width;
      n->rect.height= pRect1->height;
      return nCount;
   case XID12 :
      NewRectNodes( nCount=3,ppRNs );
      n = *ppRNs;
      n->rect.x= bx1;
      n->rect.y= by1;
      n->rect.width= ax2-bx1+1;
      n->rect.height= ay2-by1+1;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by1;
      n->rect.width= bx1-ax1;
      n->rect.height= ay2-by1+1;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= pRect1->width;
      n->rect.height= by1-ay1;
      return nCount;
   case XID23 :
      NewRectNodes( nCount=3,ppRNs );
      n = *ppRNs;
      n->rect.x= ax1;
      n->rect.y= by1;
      n->rect.width= bx2-ax1+1;
      n->rect.height= ay2-by1+1;
      n = n->next;
      n->rect.x= bx2+1;
      n->rect.y= by1;
      n->rect.width= ax2-bx2;
      n->rect.height= ay2-by1+1;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= pRect1->width;
      n->rect.height= by1-ay1;
      return nCount;
   case XID34 :
      NewRectNodes( nCount=3,ppRNs );
      n = *ppRNs;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= bx2-ax1+1;
      n->rect.height= by2-ay1+1;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by2+1;
      n->rect.width= pRect1->width;
      n->rect.height= ay2-by2;
      n = n->next;
      n->rect.x= bx2+1;
      n->rect.y= ay1;
      n->rect.width= ax2-bx2;
      n->rect.height= by2-ay1+1;
      return nCount;
   case XID41 :
      NewRectNodes( nCount=3,ppRNs );
      n = *ppRNs;
      n->rect.x= bx1;
      n->rect.y= ay1;
      n->rect.width= ax2-bx1+1;
      n->rect.height= by2-ay1+1;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by2+1;
      n->rect.width= pRect1->width;
      n->rect.height= ay2-by2;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= bx1-ax1;
      n->rect.height= by2-ay1+1;
      return nCount;
   case XID77 :
      NewRectNodes( nCount=3,ppRNs );
      n = *ppRNs;
      n->rect.x= bx1;
      n->rect.y= ay1;
      n->rect.width= pRect2->width;
      n->rect.height= pRect1->height;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= bx1-ax1;
      n->rect.height= pRect1->height;
      n = n->next;
      n->rect.x= bx2+1;
      n->rect.y= ay1;
      n->rect.width= ax2-bx2;
      n->rect.height= pRect1->height;
      return nCount;
   case XID88 :
      NewRectNodes( nCount=3,ppRNs );
      n = *ppRNs;
      n->rect.x= ax1;
      n->rect.y= by1;
      n->rect.width= pRect1->width;
      n->rect.height= pRect2->height;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= by2+1;
      n->rect.width= pRect1->width;
      n->rect.height= ay2-by2;
      n = n->next;
      n->rect.x= ax1;
      n->rect.y= ay1;
      n->rect.width= pRect1->width;
      n->rect.height= by1-ay1;
      return nCount;
   default    :
      return 0;
   }                
   return TRUE;
}

int GECreateXRectList( ppList,pRect1,pRect2 )
   GERECTLIST **ppList;
   const GERECT *pRect1,*pRect2;
{
   int nXID;
   GERECTNODE *pHeader,*node,*nodeNext;

   AnyOpenLinkedObject(ppList,sizeof(GERECTLIST));

   nXID=GetXRectID(pRect1,pRect2);
   if (nXID) {
      (*ppList)->total=BreakdownRectIntoPieces(pRect1,pRect2,nXID,&pHeader);
      (*ppList)->head=pHeader;
      for (node=pHeader;node->next;node=node->next);
      (*ppList)->tail=node;
      for (node=(*ppList)->head;node;) {
         if (node->rect.width<=0 || node->rect.height<=0) {
            nodeNext=node->next;
            AnyDelSLObject(*ppList,node);
            free(node);
            (*ppList)->total--;
            node=nodeNext;
            continue;
         }
         node=node->next;
      }
   }
   return (*ppList)->total;
}

int GEDestroyXRectList( pList )
   GERECTLIST *pList;
{
   AnyCloseLinkedObject(pList,NULL);
   return TRUE;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

static
char qErrorMessage[1024]={0}; /* 20030317 */

void errWarning( qMessage )
   const char *qMessage;
{
/* 20030317
#if defined(_XnMOTIF_)
   fprintf(stderr,"Warning, %s\n",qMessage);
#elif defined(_MSWINDOW_)
   GEMessageBox(NULL,(char*)qMessage,GE_MB_WARNING);
#endif
*/
   strncpy(qErrorMessage,qMessage,sizeof(qErrorMessage)); /* 20030317 */
}

void errExit( qMessage )
   const char *qMessage;
{
#if defined(_XnMOTIF_)
   fprintf(stderr,"Error, %s\n",qMessage);
#elif defined(_MSWINDOW_)
   GEMessageBox(NULL,(char*)qMessage,GE_MB_ERROR);
#endif
   strncpy(qErrorMessage,qMessage,sizeof(qErrorMessage)); /* 20030317 */
   exit(1);
}

const char *errMessage()
{
   return qErrorMessage;
}

int gtvy6uh55()
{
#if defined(_UNIXC_)
   static char *userName[]={"mospdt","csp7et",
                            "casper","rosebud","zeppelin",
                            "bicmos","shmos5"};
   char path[256];
   register int i;

   getcwd(path,256);
   for (i=0;i<noof(userName);i++)
      if (strstr(path,userName[i])) return 1;
   return 0;
#elif defined(_MSC_)
   /*
   char *lpSystemName,*lpAccountName,*ReferencedDomainName,*Sid;
   int cbSid,cbReferencedDomainName,peUse;
   */

   /*
   char lpBuffer[256];
   int nSize=256;
   */

   /*
   LookupAccountName(
      lpSystemName,  // LPCTSTR : address of string for system name
      lpAccountName, // LPCTSTR : address of string for account name
      Sid,           // PSID : address of security identifier
      &cbSid,         // LPDWORD : address of size of security identifier
      ReferencedDomainName,    // LPTSTR : address of string for referenced domain 
      &cbReferencedDomainName, // LPDWORD : address of size of domain string
      &peUse          // PSID_NAME_USE : address of SID-type indicator
   ); */
   /*
   GetUserName(
      lpBuffer,	// address of name buffer 
      nSize 	// address of size of name buffer 
   );
   */
   return 1;
#else
#error Compiler type should be defined at the preprocessor.
#endif
}

/******************************************************************************/
/* gecore.c */
