/******************************************************************************/
/*                           file name : blob.h                               */
/*                    descriptive name : Binary Large OBject                  */
/*                         environment : SUN UNIX 4.0.3                       */
/*                            compiler : cc                                   */
/*                            producer : Kim,YongShik                         */
/*                             version : 1.0                                  */
/*                       creating date : 43260410-43260425                    */
/*                         update date : 43280328-43280401                    */
/*                         update date : 43280605-43280612                    */
/*                         update date : 43320302-43320431                    */
/*                         update date : 43330127+0224+0309+1006              */
/*                                                                            */
/******************************************************************************/

#ifndef blob_header_INSTALLED
#define blob_header_INSTALLED 1
#include "myCore.h"

/******************************************************************************/

typedef char *Pointer;

typedef struct {
   char dummy;
} BLOBNULL;

typedef struct {
   char name[16];
   char version[16];
   char date[16];
   char c;
   double m11,m12,m21,m22,m31,m32;
   char reset;
} BLOBHEADER;

typedef struct {
   double m11,m12,m21,m22,m31,m32;
} BLOB2DMDATA;

typedef struct {
   double m11,m12,m13,m21,m22,m23,m31,m32,m33,m41,m42,m43;
} BLOB3DMDATA;

/*
typedef struct {
   int gc_type;
   int gc_mask;
   int function;
   unsigned long foreground;
   unsigned long background;
   union {
      int width;
      int style;
      int join;
   } line;
} BLOBGCEX;
*/

typedef struct {             /* Based on the X-WINDOW GC */
   int  gc_type;             /* myGC */
   long gc_mask;             /* myGC */
   int  function;            /* GE_GCMaskFunction   : Raster Output */
/* unsigned long plane_mask;    GE_GCMaskPlaneMask  : Raster Output */
   unsigned long foreground; /* GE_GCMaskForeground : Patterning */
   unsigned long background; /* GE_GCMaskBackground : Patterning */
   int  line_width;          /* GE_GCMaskLineWidth  : Pixel Selection,Lines/Arcs */
   int  line_style;          /* GE_GCMaskLineStyle  : Pixel Selection,Lines/Arcs */
   int  cap_style;           /* GE_GCMaskCapStyle   : Pixel Selection,Lines/Arcs */
   int  join_style;          /* GE_GCMaskJoinStyle  : Pixel Selection,Lines/Arcs */
   int  fill_style;          /* GE_GCMaskFillStyle  : Patterning */
   int  fill_rule;           /* GE_GCMaskFillRule   : Pixel Selection,Polygons */
   int  arc_mode;            /* GE_GCMaskArcMode    : Pixel Selection,Filled Arcs */
   int  poly_shape;          /* GE_GCMaskPolyShape  : myGC */
   int  polyarc_attr;        /* GE_GCMaskPolyArcAttr : myGC */
/* Pixmap tile;                 GE_GCMaskTile       : Patterning */
   int  stipple;             /* GE_GCMaskStipple    : Patterning (Pixmap) */
   int  stipple_width;       /* GE_GCMaskStipple    : myGC */
   int  stipple_height;      /* GE_GCMaskStipple    : myGC */
/* int  ts_x_origin;            GE_GCMaskTileStipXOrigin : Patterning */
/* int  ts_y_origin;            GE_GCMaskTileStipYOrigin : Patterning */
   char font[256];           /* GE_GCMaskFont       : Text (Font) */   
   int  font_type;           /* GE_GCMaskFont       : myGC */
   int  font_height;         /* GE_GCMaskFont       : myGC */
   int  font_width;          /* GE_GCMaskFont       : myGC */
   int  font_angle;          /* GE_GCMaskFont       : myGC -> 0..3600 degree */
   BLOB2DMDATA font_matrix;  /* GE_GCMaskFont       : myGC */
   int  text_format;         /* GE_GCMaskFont       : myGC (alignment) */
/* int  subwindw_mode;          GE_GCMaskSubwindowMode : Window Clipping */
/* Bool graphics_exposures;     GE_GCMaskGraphicsExposures : Window Clipping */
/* int  clip_x_origin;          GE_GCMaskClipXOrigin : GC Clipping */
/* int  clip_y_origin;          GE_GCMaskClipYOrigin : GC Clipping */
/* Pixmap clip_mask;            GE_GCMaskClipMask   : GC Clipping */
   int  dash_offset;         /* GE_GCMaskDashOffset : Pixel Selection,Lines/Arcs */
   char dashes;              /* GE_GCMaskDashList   : Pixel Selection,Lines/Arcs */
   char dash_list[16];       /* GE_GCMaskDashList   : myGC */
} BLOBGC;

typedef struct {
   double x,y;
} BLOBPOINT;

typedef BLOBPOINT BLOBDATA;

typedef struct {
   double x1,y1,x2,y2;
} BLOBLINE;

typedef struct {
   double x,y; /* center */
   double width,height;
   double angle1,angle2; /* radian */
} BLOBARC;

/*
typedef struct tagLOGFONT { // Microsoft Windows
   LONG lfHeight;
   LONG lfWidth; 
   LONG lfEscapement;
   LONG lfOrientation;
   LONG lfWeight; 
   BYTE lfItalic;
   BYTE lfUnderline;
   BYTE lfStrikeOut;
   BYTE lfCharSet; 
   BYTE lfOutPrecision;
   BYTE lfClipPrecision;
   BYTE lfQuality; 
   BYTE lfPitchAndFamily;
   TCHAR lfFaceName[LF_FACESIZE];
} LOGFONT; 
*/

typedef char
  BLOBTEXT;

typedef struct {
   double x1,y1,x2,y2;
} BLOBCLIPWIN;

typedef struct {
   struct {
      char pen_select;
   } xyp;
} BLOBPRINT;

/*------------------------------------------------------------------*/

typedef enum { /* this order must match that of "struct _BLOBTABLE" */
   BL_NULL=0,                   /* invalid type */
   BL_COMMAND,                  /* command */
   BL_HEADER,                   /* header */
   BL_2DMDATA,                  /* 2d matrix */
   BL_3DMDATA,                  /* 3d matrix */
   BL_GC,                       /* graphic context */
   BL_DATA,                     /* to access each point of scientific plot */
   BL_POINT,                    /* point */
   BL_LINE,                     /* line */
   BL_POLY,                     /* polygon */
   BL_ARC,                      /* arc */
   BL_BEZIER,                   /* Bezier curve */
   BL_XPOLY,                    /* Mixed polygon */
   BL_TEXT,                     /* text */
   BL_CLIPWIN,                  /* clip window */
   BL_DATABASE,                 /* BLOBTEXT : variable length data base */
   BL_PRINT,                    /* print */
   BL_TOTAL
} BLOBTYPE;

typedef struct {
   BLOBTYPE type;
   short size;
   char *name;
   IPTRFN proc,print;
} BLOBATTR;

typedef struct {
   BLOBTYPE type;
   int total;
} BLOBANY;

typedef struct _BLOBNODE {
   struct _BLOBNODE *next,*prev;
   BLOBANY any;
} BLOBNODE;

typedef struct _BLOBLIST {
   BLOBNODE *head,*tail;
} BLOBLIST;

/******************************************************************************/

/*
 ** Naming Conventions **
 *
 *  BLSet ...             : Function
 *  BLGet ...             : Function
 *  BLCre ...             : Function
 *  BLAllo ...            : Function
 *  BLFree ...            : Function
 *  BL_ ...               : ID/MASK
 *
 */

extern BLOBATTR BLOBTABLE[];

#define SizeOfBLOBTABLE (sizeof(BLOBATTR)*BL_TOTAL)

/*----------------------------------------------------------------------------*/

#define BLNodeType(node)                                                       \
        ((int)((node)->any.type))
#define BLNodeTotal(node)                                                      \
        ((int)((node)->any.total))
#define BLNodeSelfSize(node)                                                   \
        (sizeof(BLOBNODE))
#define BLNodeDataSize(node)                                                   \
        (BLOBTABLE[(int)(node)->any.type].size*(int)(node)->any.total)
#define BLNodeTotalSize(node)                                                  \
        (BLNodeSelfSize(node)+BLNodeDataSize(node))

#define BLNodeObjAddr(node)                                                    \
        ((char*)(node)+sizeof(BLOBNODE))

/*----------------------------------------------------------------------------*/

int BLOpenList();
int BLCloseList();
int BLDuplicateList();

int BLAlloObject();
int BLFreeObject();
int BLAddrObject(); /* !!? */
int BLHintObject(); /* !!? */

int BLSetProcedure();
int BLExecute();

int BLAddCommand();
int BLAddHeader();
int BLAdd2DMatrix();
int BLAdd3DMatrix();
int BLAddGC();
int BLAddData();
int BLAddPoint();
int BLAddLine();
int BLAddPoly();
int BLAddArc();
int BLAddFontAttr();
int BLAddText();
int BLAddClipWin();
int BLAddDataBase();
int BLAddPrint();

int BLGetStatus();
int BLFindObject();

int BLFreadList();
int BLFwriteList();

int BLDBOpen();
int BLDBClose();
int BLDBGetNode();
int BLDBPutNode();
int BLDBRead();
int BLDBWrite();
int BLDBtoPrevAddress();
int BLDBtoNextAddress();
int BLDBtoAbsPrevAddress();
int BLDBtoAbsNextAddress();
int BLDBPrint();

/******************************************************************************/
#endif  /* blob.h */
