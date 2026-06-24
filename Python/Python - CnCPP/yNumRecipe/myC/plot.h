/******************************************************************************/
/*                           file name : plot.h                               */
/*                         description : plot                                 */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43230913-43240627                    */
/* 4324 0724-0730,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4325 0810-1118,1202,____,____,____,____,____,____,____,____,____,____,____ */
/* 4327 1002-1007,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4328 0509,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4329 0223,0411,____,____,____,____,____,____,____,____,____,____,____,____ */
/*                                       ....                                 */
/*  Gr1.000(43251130),Gr2.700(43280125),                                      */
/*  Gr3.003(43281020),Gr3.013(43290118),Gr3.015(43290000),Gr3.016(43290130)   */
/*  Gr3.017(43290223),Gr3.018(4329022?),Gr3.019(43290307),Gr3.022(43290411)   */
/*  Gr3.030(43290418),Gr3.031(43290419),Gr3.032(43290426),Gr3.033(43290503)   */
/*  Gr3.034(43290515),Gr3.036(43290521),Gr3.037(43290612),Gr3.038(43290619)   */
/*  Gr3.039(43290821),Gr3.040(43290911),Gr3.041(43300307),Gr4.000(43300811)   */
/*  Gr4.001(43300826),Gr4.002(43300828),                                      */
/*  Gr4.03(43300831),Gr4.04(43300909),Gr4.10(43300920),Gr4.11(43310604)       */
/*  Gr5.00.43320331,Gr5.00.43320707,Gr5.00.990812,Gr5.01.000222,Gr5.04.000314 */
/*  Gr5.05.43330331,Gr5.50.000501,Gr5.51.000521,Gr5.60.000901,Gr6.01.001212   */
/*  Gr6.02.20010109,Gr6.10.20010307                                           */
/*  Gr7.00.20010308,Gr7.01.20010330,Gr7.02.20010330,Gr7.03.20010418           */
/*  Gr7.04.20021014,Gr7.11.20030429,Gr7.20.20030822                           */
/*                                                                            */
#define                   GRCoreVersion "Gr7.30.20030905"
/*                                                                            */
/******************************************************************************/

#ifndef plot_tools_header_INSTALLED
#define plot_tools_header_INSTALLED 1
/******************************************************************************/

#include "myCore.h"
#include "str.h"
#include "gecore.h"
#include "nrecipe.h"

#define GR_COMMAND_PBEG 0
#define GR_COMMAND_DEFN GR_COMMAND_PBEG + 1
#define GR_COMMAND_GLOB GR_COMMAND_PBEG + 2
#define GR_COMMAND_GXFM GR_COMMAND_PBEG + 3
#define GR_COMMAND_GTXT GR_COMMAND_PBEG + 4
#define GR_COMMAND_GOUT GR_COMMAND_PBEG + 5
#define GR_COMMAND_EXEC GR_COMMAND_PBEG + 6
#define GR_COMMAND_PLOT GR_COMMAND_PBEG + 7
#define GR_COMMAND_ATTR GR_COMMAND_PBEG + 8
#define GR_COMMAND_DATA GR_COMMAND_PBEG + 9
#define GR_COMMAND_XYZB GR_COMMAND_PBEG + 10
#define GR_COMMAND_SLCT GR_COMMAND_PBEG + 11
#define GR_COMMAND_AXIS GR_COMMAND_PBEG + 12
#define GR_COMMAND_TEXT GR_COMMAND_PBEG + 13
#define GR_COMMAND_UFUN GR_COMMAND_PBEG + 14
#define GR_COMMAND_VIEW GR_COMMAND_PBEG + 15
#define GR_COMMAND_PEND GR_COMMAND_PBEG + 16
#define GR_COMMAND_CMNT GR_COMMAND_PBEG + 17
#define GR_COMMAND_CONT GR_COMMAND_PBEG + 18

#define PLOTSCRIPT_LINEEND    "\r\n"
#define PLOTSCRIPT_COMMENT_CHAR '!'
#define PLTOSCRIPT_HOMEPATH_CHAR '~'
#define PLTOSCRIPT_PATH_DELIMITER "|"
#define PLOTSCRIPT_BEGINNING    "%grBeginning"
#define PLOTSCRIPT_END          "%grEnd"
#define PLOTSCRIPT_DEFINE       "_defn"
#define PLOTSCRIPT_UNDEF        "_undf"
#define PLOTSCRIPT_GLOB         ".glob"
#define PLOTSCRIPT_GXFM         "gxfm"
#define PLOTSCRIPT_GTXT         "gtxt"
#define PLOTSCRIPT_GOUT         "gout"
#define PLOTSCRIPT_EXEC         "exec"
#define PLOTSCRIPT_PLOT         ".plot"
#define PLOTSCRIPT_ATTR         "attr"
#define PLOTSCRIPT_DATA         "data"
#define PLOTSCRIPT_XYZB         "xyzb" /* 20030211 */
#define PLOTSCRIPT_SYMB         "symb" /* 20030211 */
#define PLOTSCRIPT_SLCT         "slct" /* <- to be deleted. 20030211 */
#define PLOTSCRIPT_AXIS         "axis"
#define PLOTSCRIPT_TEXT         "text"
#define PLOTSCRIPT_UFUN         "ufun"
#define PLOTSCRIPT_VIEW         "view"
#define PLOTSCRIPT_4UNDERSCORES "____"
#define PLOTSCRIPT_TYPE         "type"

#define DEFAULT_PLOT_LEGEND_SIZE 5
#define DEFAULT_PLOT_SYMBOL_SIZE 5

/******************************************************************************/

typedef struct {
   double angle;
   double xScale;
   double xTranslate;
   double yScale;
   double yTranslate;
} XFRMATTR;

typedef struct {
   char  font[32];
   int   height;
   int   width;
   unsigned long color;
   int   angle;
   short alignment;
} FONTATTR;

#define SetGRFontDefault(a)   {                                                \
                              (a).font[0]  = '*';                              \
                              (a).font[1]  = 0;                                \
                              (a).height   = 10;                               \
                              (a).width    = 5;                                \
                              (a).color    = 0; /* black */                    \
                              (a).angle    = 0;                                \
                              (a).alignment= GE_AlignBottom|GE_AlignLeft;      }

/*---PLTATTR------------------------------------------------------------------*/
typedef enum { /* 2003.11.1 */
   SCALE_LIN=0,SCALE_LOG10=1,SCALE_SERIES=2,SCALE_NORM=3,SCALE_WEIBULL=4
} SCALEATTR;

typedef struct {
   enum {
      PLT2D_GENETIC=0,PLT2D_GENETICPLUS,PLT2D_MOMENT,PLT2D_FLAT3D,
      PLT2D_BAR,PLT2D_AREA,PLT2D_PIE,
   } type;
   enum { /* prev-plot attr used */
      BACK_FALSE=0,BACK_TRUE
   } back;
   SCALEATTR xScale,yScale,zScale;
   BLOBGC CanvasAttr;
} PLTATTR;

/*---PLTDATA------------------------------------------------------------------*/

#define MTX_OFFSET_TO_MINV   0
#define MTX_OFFSET_TO_LOW5   1
#define MTX_OFFSET_TO_MEDIAN 2
#define MTX_OFFSET_TO_UPP5   3
#define MTX_OFFSET_TO_MAXV   4
#define MTX_OFFSET_TO_SIGMA  5
#define MTX_OFFSET_TOTAL     6

typedef struct {
   enum {
      MATRIX_FILE=0,MATRIX_PREVIOUS,MATRIX_CLONE,MATRIX_USERFUNCTION,
      MATRIX_SCRIPT
   } type;
   char *pName;   /* 1) data file or 2) script file for MATRIX_SCRIPT */
   char *pOption; /* 1) xy file when PLTATTR->type==PLT2D_FLAT3D */
   int nBlockIndex,*vBlockIndex; /* data block index in a file 20030311 */
   double **mtx;
   int nrl,nrh,ncl,nch;
   int nDenominatorForCDF;
   char **ppHeader;
   int nHeader;  /* (nrh-nrl+1) 2001.0514 */
   int bColumnSortingByX,bRowColumnExchange;
} PLTDATA; 

/*---PLTXYZB------------------------------------------------------------------*/

typedef struct {
   double xMinV,yMinV,zMinV,xMaxV,yMaxV,zMaxV,
          xLowB,yLowB,zLowB,xUppB,yUppB,zUppB;
} PLTXYZB;
 
/*---PLTSYMB------------------------------------------------------------------*/

#define MOMENT_BOX_SYMBOL_TYPE -6

   typedef struct {
      int bLegendOn,bSymbolOn,bLineOn,nType,nCopy,nPen;
      double x,y,dSymbSize,dLegendSize;
      char *pText;
      BLOBGC GCSymbAttr,GCLineAttr;
      FONTATTR FontAttr;
   } LEGEND;
typedef struct {
   int xNoTotal,*xNo,yNoTotal,*yNo,zNoTotal,*zNo;
   #define PLOT_COLUMNINDEX_MASK   BITS(0,7) /* 20030901-0902 */
   #define PLOT_ATTACHEDINDEX_MASK BIT(8)
   #define PLOT_REVERSEINDEX_MASK  BIT(9)
   #define PLOT_BLOCKINDEX_MASK    BIT(sizeof(int)*8-1)
   /* 20030901
    * BIT(0-7) reserves for column index,i.e., max. 256.
    * BIT(8) means virtual index for being attched later. relative to data.
    * BIT(9) means reverse index from max. column index.
    * BIT(sizeof(int)*8-1) means sign and block parity.
    */
   /* To be realized later like below. 20030901 ???
    * int **xyz;
    * xyz[0][0]=noof(selections).
    * xyz[0][1..*]=not used.
    * xyz[r][0]=noof(columns of rth selection) called nrth.
    * xyz[r][1..nrth]=column numbers of rth selection.
    */
   int nLegendTotal,bAutoLegend,nColPerBlock;
   LEGEND *pLegend;
   double xminv,yminv,zminv,xmaxv,ymaxv,zmaxv,
          xlowb,ylowb,zlowb,xuppb,yuppb,zuppb;
   union {
      int nType; /* must equal PLTATTR->type */
      struct {
         int nType;
         double dRange;
      } LineMoment;
      struct {
         int nType;
         long nColorMin,nColorMax;
         int nColorTotal;
         char qFormat[8];
      } Flat3D;
   } Etc;
} PLTSLCT;

/*---PLTAXIS------------------------------------------------------------------*/
   typedef struct _plot_axis {
      int bAxisOn,bTickMajorOn,bTickMinorOn,bGridMajorOn,bGridMinorOn;
      int bLabelOn,bTitleShow;
      enum {
         AXIS_ATLOWERBOUND,AXIS_ATMIDDLE,AXIS_ATUPPERBOUND,AXIS_ATANYPOSITION
      } AxisAttr;
      enum {
         TICK_INSIDE,TICK_OUTSIDE,TICK_CROSS
      } TickMajorAttr,TickMinorAttr;
      enum {
         LABEL_BYTICKNUMBER,LABEL_BYTICKSPACE,LABEL_BYUSER
      } LabelAttr;
      char
         *pLabelFormat,*pLabelEquation;
      double
         dAxisX1,dAxisY1,dAxisX2,dAxisY2;
      double 
         dTickMinorStep,dTickMajorStep,dTitleSpaceFactor;
      BLOBGC
         AxisGCAttr,GridGCMajorAttr,GridGCMinorAttr;
      FONTATTR 
         FontAttr,TitleFontAttr;
      char
         *pTitle;
   } PAXIS;
typedef struct {
   int
       xTotal,yTotal,zTotal;
   PAXIS 
      *xAxis[8],*yAxis[8],*zAxis[8];
} PLTAXIS;

/*---PLTTEXT------------------------------------------------------------------*/
   typedef struct _plot_text {
      enum {
         TEXT_FREE=0,TEXT_MAIN,TEXT_LEFTSHOULDER,TEXT_RIGHTSHOULDER,TEXT_BOTTOM
      } nType;
      double 
         x,y;
      FONTATTR 
         FontAttr;
      char 
         *pString;
   } PTEXT;
typedef struct {
   int
       nTotal;
   PTEXT 
      *qText[32];
} PLTTEXT;

/*---PLTUFUN------------------------------------------------------------------*/
   typedef struct _user_function_node {
      struct _user_function_node 
         *next;
      char
         *pType;
      char
         *pArgument,
         *pArgument2, /* Y.Kim,20030522,0904 */
         *pArgument3, /* Y.Kim,20030905 */
         *pArgument4, /* Y.Kim,20030906 */
         *pSweep; /* start,stop,step, Y.Kim,20021015,20030223 */
      int    
         nOption,nSubOption,nrl,nrh,ncl,nch,bLineOn,bTableOn;
      struct {
         int nResult;
         VECTOR vResult;
         char *pResult;
      } out;
      FONTATTR
         FontAttr;
      BLOBGC
         GCAttr;
   } PUFUN;
typedef struct {
   PUFUN
      *pHead,*pTail;
} PLTUFUN;

/*---PLTXFRM------------------------------------------------------------------*/
typedef struct {
   double (*xCnvFn)(),(*yCnvFn)(),(*zCnvFn)();
   double (*xInvFn)(),(*yInvFn)(),(*zInvFn)();
   WLDWINSIZE wldwin;
   NORWINSIZE norwin; /* Be aware of "norwin" size : 0..1,0..1 */
   XFRMATTR attr;
} PLTXFRM;

/*---PLOT---------------------------------------------------------------------*/
typedef struct _PLTNODE {
   struct _PLTNODE *next,*prev;
   PLTATTR *pAttr; /* must be */
   PLTDATA *pData; /* must be */
   PLTSLCT *pSlct; /* must be, but can be another type */
   PLTAXIS *pAxis;
   PLTTEXT *pText;
   PLTUFUN *pUfun;
   PLTXFRM *pXfrm; /* must be */
} PLTNODE; 

/*---PLTGLOB------------------------------------------------------------------*/
   typedef struct {
      char *pInput,*pOutput,*pOption;
   } GARGAMELINFO;
typedef struct {
   char *pName,*pHomePath,*pTitle;
   int bReuseGargamelOutputIfExist;
   int bEchoPlotPoints; /* 20030822 */
   /* double x,y; 20030217 */
   double dTitleSpaceFactor; /* with respect to font height. 20030217 */
   XFRMATTR xfrm;
   FONTATTR TextAttr;
   union {
     struct {
        int attr;
     } whole;
     struct {
       char COLORPS :1;
       char GRAYPS  :1;
       char EPS     :1;
       char PCL5    :1;
       char HPGL2   :1;
       char DOT     :1;
       char SCRIPT  :1;
     } parts;
   } OutputType;
   enum { PD_LANDSCAPE=0,PD_PORTRAIT=1 } nPageDirection;
   GARGAMELINFO qFile[32];
} PLTGLOB; /* global_plot_attributes */

/*---PLTLIST------------------------------------------------------------------*/
typedef struct {
   PLTNODE *pHead,*pTail;
   PLTGLOB  Glob;
   int nTotal;
   char *pTemporaryFiles; /* This split up into each file by \n */
} PLTLIST; /* plot_list_structure */

/******************************************************************************/

#define MOMENT_X_NOISE_FACTOR 0.0005

#define LgndGCSymbAttr(i) (pPlot->pSlct->pLegend[(i)].GCSymbAttr)
#define LgndGCLineAttr(i) (pPlot->pSlct->pLegend[(i)].GCLineAttr)
#define LgndFontAttr(i)   (pPlot->pSlct->pLegend[(i)].FontAttr)

/******************************************************************************/

int    GROpen      _((PLTLIST**,const char*,const char*));
int    GRClose     _((PLTLIST*));
int    GRExecute   _((PLTLIST*,BLOBLIST**));
char  *GRGetErrorMessage _(( )); /* in plotio.c */
#if defined(__cplusplus)
extern "C" {
int    GRGetColNumberCount _((const char *qString)); /* in plotio.c */
}
#endif

int    AlloPlot    _((PLTNODE **));
int    FreePlot    _((PLTNODE *));

double icnorm      _(( ));            /* in nrecipe.c */

#if defined(_MSC_)
int    Echo        _(( ));    /* in plotio.c */
#elif defined(_UNIXC_) || defined(_HP715C_)
int    Echo        _(( ));
#endif

/******************************************************************************/
#endif /* plot.h */

