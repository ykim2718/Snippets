/******************************************************************************/
/*                           file name : gecore.h                             */
/*                    descriptive name : Graphic Engine Core                  */
/*                                       Graphic Extreme Core (2000.2.24)     */
/*                            compiler : cc                                   */
/*                            producer : Kim,YongShik                         */
/*                                                                            */
/*                       creating date : 43260525-43260525                    */
/*                         update date : 06/14/93,43290118                    */
/*                                       ....                                 */
/*                         update date :                                      */
/*    GE1.00(43290118),GE1.01(43290418),GE1.02(43290521),GE1.03(43300831),    */
/*    GE1.04(43300909),GE1.05(43310117)                                       */
/*    GE2.00.43320431,GE2.10.43330121,GE2.12.43330309,GE2.20.43340914         */
/*    GE2.21.43360305                                                         */
#define                   GECoreVersion "GE2.21.43360318"
/*                                                                            */
/******************************************************************************/

#ifndef gecore_header_INSTALLED
#define gecore_header_INSTALLED 1
/******************************************************************************/

#include "myCore.h"
#include "blob.h"
#include "geresource.h"
#include "gefont.h"
#include "any.h"
/* #include "myWindow.h" ------------------> look up the bottom of this file */

/******************************************************************************/
/******************************************************************************/

/*----------------------------------------------------------------------------* 
 * GC Type & Mask
 *----------------------------------------------------------------------------*/
#define GE_GCPoint    0
#define GE_GCLine     1
#define GE_GCPolygonL 2 /* outline property */
#define GE_GCPolygon  3
#define GE_GCTextL    4 /* outline property */
#define GE_GCText     5
#define GE_GCTotal    6

#define GE_GCMaskNull              (0L)
#define GE_GCMaskFunction          (1L<<0)
#define GE_GCMaskPlaneMask         (1L<<1)
#define GE_GCMaskForeground        (1L<<2)
#define GE_GCMaskBackground        (1L<<3)
#define GE_GCMaskLineWidth         (1L<<4)
#define GE_GCMaskLineStyle         (1L<<5)
#define GE_GCMaskCapStyle          (1L<<6)
#define GE_GCMaskJoinStyle         (1L<<7)
#define GE_GCMaskFillStyle         (1L<<8)
#define GE_GCMaskFillRule          (1L<<9)
#define GE_GCMaskArcMode           (1L<<10)
#define GE_GCMaskTile              (1L<<11)
#define GE_GCMaskStipple           (1L<<12)
#define GE_GCMaskTileStipXOrigin   (1L<<13)
#define GE_GCMaskTileStipYOrigin   (1L<<14)
#define GE_GCMaskFont              (1L<<15)
#define GE_GCMaskSubwindowMode     (1L<<16)
#define GE_GCMaskGraphicsExposures (1L<<17)
#define GE_GCMaskClipXOrigin       (1L<<18)
#define GE_GCMaskClipYOrigin       (1L<<19)
#define GE_GCMaskClipMask          (1L<<20)
#define GE_GCMaskDashOffset        (1L<<21)
#define GE_GCMaskDashList          (1L<<22)
#define GE_GCMaskPolyShape         (1L<<23) /* myGC */
#define GE_GCMaskPolyArcAttr       (1L<<24) /* myGC */
/*efine GE_GCMaskText              (1L<<25) */

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

/*----------------------------------------------------------------------------* 
 * gc_mask
 *----------------------------------------------------------------------------*/

#define GE_GCMaskLineDefault      (GE_GCMaskFunction                         | \
                                   GE_GCMaskForeground                       | \
                                   GE_GCMaskBackground                       | \
                                   GE_GCMaskLineWidth                        | \
                                   GE_GCMaskLineStyle                        | \
                                   GE_GCMaskCapStyle                         | \
                                   GE_GCMaskJoinStyle                        | \
                                   GE_GCMaskDashList                         )
 
#define GE_GCMaskFillDefault      (GE_GCMaskFunction                         | \
                                   GE_GCMaskForeground                       | \
                                   GE_GCMaskBackground                       | \
                                   GE_GCMaskFillStyle                        | \
                                   GE_GCMaskFillRule                         | \
                                   GE_GCMaskArcMode                          | \
                                   GE_GCMaskStipple                          | \
                                   GE_GCMaskTileStipXOrigin                  | \
                                   GE_GCMaskTileStipXOrigin                  )
 
#define GE_GCMaskTextDefalut      (GE_GCMaskFunction                         | \
                                   GE_GCMaskForeground                       | \
                                   GE_GCMaskBackground                       | \
                                   GE_GCMaskFont                             )

/*----------------------------------------------------------------------------* 
 * typedef
 *----------------------------------------------------------------------------*/

typedef enum {
   GE_FnClear, GE_FnAnd,      GE_FnAndReverse,  GE_FnCopy,     GE_FnAndInverted,
   GE_FnNoOp,  GE_FnXor,      GE_FnOr,          GE_FnNor,       GE_FnEquiv,
   GE_FnInvert,GE_FnOrReverse,GE_FnCopyInverted,GE_FnOrInverted,GE_FnNand,
   GE_FnSet
} GEFUNCTYPE;

typedef enum {
   GE_LineSolid,GE_LineOnOffDash,GE_LineDoubleDash,GE_LineUser
} GELINETYPE;

typedef enum {
   GE_CapNotLast,GE_CapButt,GE_CapRound,GE_CapProjecting
} GECAPTYPE;

typedef enum {
   GE_JoinMiter,GE_JoinRound,GE_JoinBevel
} GEJOINTYPE;

typedef enum {
   GE_FillSolid,GE_FillOpaqueStippled,GE_FillStippled,GE_FillTiled
} GEFILLTYPE;

typedef enum {
   GE_FillEvenOdd,GE_FillWinding
} GEFILLRULETYPE;

typedef enum {
   GE_PolyConvex,GE_PolyNonConvex,GE_PolyComplex
} GEPOLYSHAPETYPE;

typedef enum {
  GE_ArcPieSlice,GE_ArcChord
} GEARCMODETYPE;

typedef enum {
   GE_ClipByChildren,GE_IncludeInferiors
} GESUBWINMODETYPE;

typedef enum {
  GE_PolyArcLine,GE_PolyArcFill,GE_PolyArcBoth
} GEPOLYARCTYPE;

typedef enum {
   GE_FontRaster=-1,GE_FontVector=0,GE_FontTrueType=1 /* Microsoft Style */
   /*     bitmap           line            line+curve    <- Glyph        */
} GEFONTTYPE;

typedef enum {
   GE_AlignBottom=1,GE_AlignBaseline=2,GE_AlignVCenter=4,GE_AlignTop=8, /* vertical */
   GE_AlignLeft=16, GE_AlignHCenter=32,GE_AlignRight=64              /* horizontal */
} GEALIGNTYPE; /* for bit operation */

typedef struct { /* identical to XPoint in X */
   short x,y;
} GEPOINT;

typedef struct { /* same with XSegment in X */
   short x1,y1,x2,y2;
} GELINE;

typedef struct { /* equivalent to XArc in X */
   short x,y;
   unsigned short width,height;
   short angle1,angle2;
} GEARC;

/*    x,y
 * 0,0 +--------+ width
 *     | window |
 *     +--------+
 *     height
 */
typedef struct {
   int x,y;
   unsigned int width,height,borderWidth;
} GERECT;

typedef struct {
   unsigned short red,green,blue;
   char *name;
} GECOLOR;

typedef enum {
   GE_EventNull=0,
   GE_EventZoomIn,GE_EventZoomOut,
   GE_EventTranslate,GE_EventMoveUp,GE_EventMoveDown,
   GE_EventMoveLeft,GE_EventMoveRight,
   GE_EventRedraw,GE_EventScaleByObject,GE_EventScaleByWindow,
   GE_EventDumpToHPS,GE_EventDumpToVPS
} GEDRAWEVENT;

typedef struct _GERECTNODE {
   struct _GERECTNODE *next;
   GERECT rect;
} GERECTNODE;

typedef struct _GERECTLIST {
   GERECTNODE *head,*tail;
   int total;
} GERECTLIST;

/*----------------------------------------------------------------------------* 
 * macro
 *----------------------------------------------------------------------------*/

#define GESetGCDefault(a) {                                                    \
               /* myGC */ (a).gc_type           = GE_GCPoint;                  \
               /* myGC */ (a).gc_mask           = GE_GCMaskNull;               \
                          (a).function          = GE_FnCopy;                   \
                          (a).foreground        = GEColorByName(NULL,"black"); \
                          (a).background        = GEColorByName(NULL,"white"); \
                          (a).line_width        = 1;                           \
                          (a).line_style        = GE_LineSolid;                \
                          (a).cap_style         = GE_CapButt;                  \
                          (a).join_style        = GE_JoinBevel;                \
                          (a).fill_style        = GE_FillSolid;                \
                          (a).fill_rule         = GE_FillEvenOdd;              \
               /* myGC */ (a).poly_shape        = GE_PolyComplex;              \
                          (a).arc_mode          = GE_ArcPieSlice;              \
               /* myGC */ (a).polyarc_attr      = GE_PolyArcLine;              \
                          (a).stipple           = 0;                           \
               /* myGC */ (a).stipple_width     = 0;                           \
               /* myGC */ (a).stipple_height    = 0;                           \
                          (a).font[0]           = (char)0;                     \
               /* myGC */ (a).font_type         = GE_FontVector;               \
               /* myGC */ (a).font_height       = 10;                          \
               /* myGC */ (a).font_width        = 0;                           \
               /* myGC */ (a).font_angle        = 0;                           \
               /* myGC */ (a).text_format       = GE_AlignBottom|GE_AlignLeft; \
                          (a).dash_offset       = 0;                           \
                          (a).dashes            = 0;                           \
               /* myGC */ memset((a).dash_list,0,16);                          \
                          }

/*----------------------------------------------------------------------------* 
 * message box
 *----------------------------------------------------------------------------*/

#define GE_MB_NULL        0
#define GE_MB_WARNING     1
#define GE_MB_ERROR       2
#define GE_MB_INFORMATION 3
#define GE_MB_QUESTION    4
#define GE_MB_WORKING     5

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

typedef double     **XMTX2D;
typedef double     **XMTX3D;

extern XMTX2D myGEXMatrix2D; // shik,990303+2000.3.8

extern DLL *GEMESSAGE;

/*----------------------------------------------------------------------------* 
 * transformation
 *----------------------------------------------------------------------------*/

/*
 *           x2,y2
 *    +--------+
 *    | window |
 *    +--------+
 *  x1,y1
 */

typedef struct { double x1,y1,x2,y2; } WLDWINSIZE;
typedef struct { double x1,y1,x2,y2; } NORWINSIZE; // to be removed later :990303
typedef struct { int    x1,y1,x2,y2; } DEVWINSIZE;

int isPointInWldWindow _(( WLDWINSIZE *win, double x,double y ));
int isPointInDevWindow _(( DEVWINSIZE *win, int x,int y ));

int SetXMatrixData2D _(( BLOB2DMDATA *array,
                         double m11,double m12,double m21,
                         double m22,double m31,double m32 ));

int AlloXMatrix2D _(( XMTX2D *mtx ));
int FreeXMatrix2D _(( XMTX2D mtx ));
int SetXMatrix2D _(( XMTX2D attr,
                     double a,double b,double c,
                     double d,double e,double f ));
int SetXMatrix2DDefault _(( XMTX2D attr ));
int XMatrix2DScale _(( XMTX2D xmtx,
                       double x,double y,double Sx,double Sy,
                       IPTRFN Combine ));
int XMatrix2DTranslate _(( XMTX2D xmtx,
                           double Tx,double Ty,
                           IPTRFN Combine ));
int XMatrix2DRotate _(( XMTX2D xmtx,
                        double x,double y,double Angle,
                        IPTRFN Combine ));
int XMatrix2DStretch _(( void ));

int ComXMatrix2D _(( XMTX2D dst,XMTX2D src ));
int ComXMatrix2DAdobe _(( XMTX2D dst,XMTX2D src ));

int CopyXMatrix2D _(( XMTX2D dst,XMTX2D src ));
int SaveXMatrix2D _(( void ));
int RestoreXMatrix2D _(( void ));

int xform _(( double *x,double *y ));
int dxform _(( double *x,double *y ));
int ixform _(( double *x,double *y ));
int idxform _(( void ));
int xform_it _(( double *x1,double *y1,double *x2,double *y2 ));

/*----------------------------------------------------------------------------* 
 * BLOB drawing
 *----------------------------------------------------------------------------*/

#define GE_BUFSIZE 1024

int GEDraw _((
   char *pDisplay, /* MYDISPLAY* */
   BLOBLIST *pBlobList,
   GERECT *pViewport /* viewport */
   ));
int GEDrawEx _((
   char *pDisplay, /* MYDISPLAY* */
   BLOBLIST *pBlobList,
   GERECT *pViewport, /* viewport */
   int nEvent,int nEventX,int nEventY,
   float fEventFactor /* default=1.0 */
   ));
int GEPrint _(( /* functions like Export or Save-as, 20020914 */
   char *pDisplay, /* MYDISPLAY* */
   BLOBLIST *pBlobList,
   GERECT *pViewport, /* viewport */
   int nEvent,int nEventX,int nEventY,
   float fEventFactor, /* default=1.0 */
   char *pFileName,
   int bLandscape
   ));

//int GERetriveHitObject ?
int clipper_line();
int GEMarkerXY();

int GECreateXRectList _((
   GERECTLIST **ppList,
   const GERECT *pRect1, const GERECT *pRect2
   ));
int GEDestroyXRectList _((
   GERECTLIST *pList
   ));

/*----------------------------------------------------------------------------* 
 * Error&Warning
 *----------------------------------------------------------------------------*/

void  errWarning _((const char*));
void  errExit    _((const char*));
const char *errMessage _(( ));

/*----------------------------------------------------------------------------* 
 * function definition
 *----------------------------------------------------------------------------*/

#define GEChangeGC             myChangeGC
#define GEDrawPoint            myDrawPoint
#define GEDrawLine             myDrawLine
#define GEDrawPoly             myDrawPoly
#define GEDrawArc              myDrawArc
#define GEDrawText             myDrawText
#define GEDrawTextStroke       myDrawTextStroke
#define GEDrawTextLine         myDrawTextLine
#define GEClipWin              myClipWin

#define GEWindowShow           myWindowShow
#define GEWindowClear          myWindowClear
#define GEFlush                myFlush

#define GECopyToBackingStore   myCopyToBackingStore
#define GECopyFromBackingStore myCopyFromBackingStore
 
#define GEGetGeometry          myGetGeometry
 
#define GEGetKeyEvent          myGetKeyEvent
#define GEGetMouseEvent        myGetMouseEvent

#define GEGetMouseXY           myGetMouseXY
#define GESetMouseXY           mySetMouseXY

#define GEAlloImage            myAlloImage
#define GEFreeImage            myFreeImage
#define GEGetImage             myGetImage
#define GEPutImage             myPutImage
#define GECpyImage             myCpyImage
#define GEGetPixel             myGetPixel
#define GEPutPixel             myPutPixel

/******************************************************************************/
#include "geWindow.h" /* Keep this location or you'll meet compile error ******/
/******************************************************************************/
#endif /* gecore.h */
