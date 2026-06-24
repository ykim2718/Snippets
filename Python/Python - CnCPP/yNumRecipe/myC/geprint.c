/******************************************************************************/
/*                           file name : GEPrint.c                            */
/*                    descriptive name : Graphic Engine (BLOB) PRINT Module   */
/*                            compiler : cc                                   */
/*                            producer : Kim,YongShik                         */
/*                                                                            */
/*                       creating date : 43241116-43250722                    */
/*                         update date : 43251201-43260809                    */
/*                         update date : 43260826-43260826                    */
/*                         update date : 43270104,1007-1009                   */
/*                         update date : 43280425,0712,1017-20,1031,1113      */
/*                         update date : 43290223,0521,0605                   */
/*                         update date : 43300307,0829-0830,0906,0909         */
/*                         update date : 43320301-0331                        */
/*                         update date : ********                             */
/*    GEPrintER1.10.000222                                                    */
#define                GEPrinterVersion "GEPrinter2.00.000313"
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "myCore.h"
#include "blob.h"
#include "str.h"
#include "number.h"
#include "tools.h"
#include "gecore.h"
#include "geprint.h"

/******************************************************************************/

static FILE       *F=NULL;
static char       *PrintName=NULL;
static GEPRINTTYPE PrintType;
static GEPRINTDIRECTION PrintDirection;
static int         PrintPageIndex;
static XMTX2D      DeviceXmtx2D;

/*----------------------------------------------------------------------------*/

       int GEPrintOpen();
       int GEPrintClose();
       int GEPrintSetProcedure();
       int GEPrintProcess();

static int PSHeader();
static int PSXmtx2DData();
static int PSXmtx3DData();
static int PSGc();
static int PSPoint();
static int PSLine();
static int PSPolyline();
static int PSArc();
static int PSText();
static int PSClipWin();

static int EPSHeader();
static int EPSXmtx2DData();
static int EPSXmtx3DData();
static int EPSGc();
static int EPSPoint();
static int EPSLine();
static int EPSPolyline();
static int EPSArc();
static int EPSText();
static int EPSClipWin();

       int GEPSFDumpWindow();

static int HPGL_LineForeground;
static int HPGL_PolyArcAttr;
static int HPGLHeader();
static int HPGLXmtx2DData();
static int HPGLXmtx3DData();
static int HPGLGc();
static int HPGLPoint();
static int HPGLLine();
static int HPGLPolyline();
static int HPGLArc();
static int HPGLText();
static int HPGLPrint();
 
       int GEPrintBlobAsText();
static int _PrintBLOBNode();
static int _PrintCommand();
static int _PrintHeader();
static int _PrintXmtx2DData();
static int _PrintXmtx3DData();
static int _PrintGC();
static int _PrintPoint();
static int _PrintLine();
static int _PrintArc();
static int _PrintText();
static int _PrintClipWin();

/******************************************************************************/
/***********************************k*i*m**************************************/
/*****************************y*o*n*g*-*s*h*i*k********************************/
/******************************************************************************/
/******************************************************************************/
/*****************************-*g*r*a*p*h*i*c*-********************************/
/*********************************p*r*i*n*t************************************/
/********************************e*n*g*i*n*e***********************************/
/******************************************************************************/
/******************************4*3*2*4*1*1*1*6*********************************/
/******************************************************************************/

/* PS *************************************************************************/

#define PS_Adobe_ID(ID_)         fprintf(F,"%%!PS-Adobe-%d.0\n",ID_);

#define PS_Comments(file_)       fprintf(F,"%%%%version: %s(c)Kim,YongShik\n"  \
                                          ,GEPrinterVersion);                  \
                                 fprintf(F,"%%%%file: %s\n",file_);            \
                                 fprintf(F,"/file (%s) def\n",file_);          \
                                 fprintf(F,"%%%%endcomments\n");

#define PS_LineFeed              fprintf(F,"\n");
#define PS_Page(d_)              fprintf(F,"%%%%pages: %d\n",d_);

#define PS_Save                  fprintf(F,"save\n");
#define PS_Restore               fprintf(F,"restore\n");
#define PS_Gsave                 fprintf(F,"gsave\n");
#define PS_Grestore              fprintf(F,"grestore\n");
#define PS_ShowPage              fprintf(F,"showpage\n");
#define PS_Header(d_)            fprintf(F,"%%%%Page: %d %d\n",d_,d_)
#define PS_Trailer               fprintf(F,"%%%%trailer\n");

/*----------------------------------------------------------------------------*/
#define PS_Debug2                                                              \
    fprintf(F,"/Debug2 {\n");                                                  \
    fprintf(F,"gsave\n");                                                      \
    fprintf(F,"initmatrix\n");                                                 \
    fprintf(F,"/str 50 string def\n");                                         \
    fprintf(F,"2 2 scale\n");                                                  \
    fprintf(F,"newpath\n");                                                    \
    fprintf(F,"100 10 moveto str cvs show\n");                                 \
    fprintf(F,"50 10 moveto str cvs show\n");                                  \
    fprintf(F,"grestore\n");                                                   \
    fprintf(F,"} bdef\n");
/*----------------------------------------------------------------------------*/
#define PS_BindKeys                                                            \
    fprintf(F,"/bdef {bind def} bind def\n");                                  \
    fprintf(F,"/ldef {load def} bdef\n");                                      \
    fprintf(F,"/xdef {exch def} bdef\n");                                      \
    fprintf(F,"%%/gs {gsave def} bdef\n");                                       \
    fprintf(F,"%%/gr {grestore def} bdef\n");                                    \
/*----------------------------------------------------------------------------*/
#define PS_InitiGraphics                                                       \
    fprintf(F,"\ninitgraphics\n");                                             \
    fprintf(F,"72 254 div 72 254 div scale\n");
 /* %% Default Portrait : 1/72 inch -> 0.1mm unit
  * %% 210mm x 297 mm Vertical A4 Boundary with each margin of 5mm.
  * fprintf(F,"50 50 2050 2920 R\n");
  */
/*----------------------------------------------------------------------------*/
#define PS_ProcTitle                                                           \
    fprintf(F,"/strcat {\n");                                                  \
    fprintf(F,"/src xdef\n");                                                  \
    fprintf(F,"/dst xdef\n");                                                  \
    fprintf(F,"src length /sl xdef\n");                                        \
    fprintf(F,"dst length /dl xdef\n");                                        \
    fprintf(F,"/buf sl dl add string def\n");                                  \
    fprintf(F,"buf 0 dst putinterval\n");                                      \
    fprintf(F,"buf dl src putinterval\n");                                     \
    fprintf(F,"buf\n");                                                        \
    fprintf(F,"} bdef \n");                                                    \
    fprintf(F,"/Title {\n");                                                   \
    fprintf(F,"/str xdef\n");                                                  \
    fprintf(F,"gsave\n");                                                      \
    fprintf(F,"0.7 setgray\n");                                                \
    fprintf(F,"2 setlinewidth\n");                                             \
    fprintf(F,"50 2870 2050 2870 L\n");                                        \
    fprintf(F,"/Helvetica-Bold findfont 30 scalefont setfont\n");              \
    fprintf(F,"50 2888 moveto str ( + ) strcat file strcat\n");                \
    fprintf(F,"0 setgray show\n");                                             \
    fprintf(F,"grestore\n");                                                   \
    fprintf(F,"} bdef\n");
/*----------------------------------------------------------------------------*/
#define PS_ProcPortrait                                                        \
    fprintf(F,"/Portrait {\n");                                                \
    fprintf(F,"50 50 translate\n");                                            \
    fprintf(F,"0 0 2000 2820 Clip\n");                                         \
    fprintf(F,"} bdef\n");
#define PS_ProcLandscape                                                       \
    fprintf(F,"/Landscape {\n");                                               \
    fprintf(F,"-90 rotate -2870 50 translate\n");                              \
    fprintf(F,"0 0 2820 2000 Clip\n");                                         \
    fprintf(F,"} bdef\n");
#define PS_Portrait                                                            \
    fprintf(F,"Portrait\n");
#define PS_Landscape                                                           \
    fprintf(F,"Landscape\n");
/*----------------------------------------------------------------------------*/
#define PS_Defaults(printType)                                                 \
    fprintf(F,"\n");                                                           \
    fprintf(F,"/myArcMode 0 def\n");                                           \
    fprintf(F,"/myFillRule 0 def\n");                                          \
    fprintf(F,"/myPolyarcAttr 0 def\n");                                       \
    fprintf(F,"/myTextFormat 11 def\n");                                            \
    fprintf(F,"/Helvetica-Bold findfont 1 scalefont setfont\n");               \
    switch (PrintType) {                                                       \
    case GE_PSGray :                                                           \
    case GE_PSEncapsulated :                                                   \
    fprintf(F,"/myFontColor 0 def\n");                                         \
         break;                                                                \
    case GE_PSColor :                                                          \
    fprintf(F,"/myFontColor {1 1 1} def\n");                                   \
         break;                                                                \
    }                                                                          \
    fprintf(F,"0 setgray \n"); 
/*----------------------------------------------------------------------------*/
#define PS_ProcPoint                                                           \
    fprintf(F,"/D {\n");                                                       \
    fprintf(F,"/y xdef\n");                                                    \
    fprintf(F,"/x xdef\n");                                                    \
    fprintf(F,"x y 1 1 0 360 A\n");                                            \
    fprintf(F,"} bdef\n")
#define PS_Point(x1,y1)                                                        \
    fprintf(F,"%d %d D\n",(int)(x1),(int)(y1))
/*----------------------------------------------------------------------------*/
#define PS_ProcLine                                                            \
    fprintf(F,"/L {\n");                                                       \
    fprintf(F,"/y2 xdef\n");                                                   \
    fprintf(F,"/x2 xdef\n");                                                   \
    fprintf(F,"/y1 xdef\n");                                                   \
    fprintf(F,"/x1 xdef\n");                                                   \
    fprintf(F,"newpath\n");                                                    \
    fprintf(F,"x1 y1 moveto\n");                                               \
    fprintf(F,"x2 y2 lineto\n");                                               \
    fprintf(F,"stroke\n");                                                     \
    fprintf(F,"} bdef\n")
#define PS_Line(x1,y1,x2,y2)                                                   \
    fprintf(F,"%d %d %d %d L\n",(int)(x1),(int)(y1),(int)(x2),(int)(y2))
/*----------------------------------------------------------------------------*/
#define PS_ProcRect                                                            \
    fprintf(F,"/R {\n");                                                       \
    fprintf(F,"/y2 xdef\n");                                                   \
    fprintf(F,"/x2 xdef\n");                                                   \
    fprintf(F,"/y1 xdef\n");                                                   \
    fprintf(F,"/x1 xdef\n");                                                   \
    fprintf(F,"newpath\n");                                                    \
    fprintf(F,"x1 y1 moveto\n");                                               \
    fprintf(F,"x2 y1 lineto\n");                                               \
    fprintf(F,"x2 y2 lineto\n");                                               \
    fprintf(F,"x1 y2 lineto\n");                                               \
    fprintf(F,"x1 y1 lineto\n");                                               \
    fprintf(F,"closepath stroke\n");                                           \
    fprintf(F,"} bdef\n");
#define PS_Rect(x1,y1,x2,y2)                                                   \
    fprintf(F,"%d %d %d %d R\n",(int)(x1),(int)(y1),(int)(x2),(int)(y2))
/*----------------------------------------------------------------------------*/
#define PS_ProcPolyline                                                        \
    fprintf(F,"/Po {\n");                                                      \
    fprintf(F,"[\n");                                                          \
    fprintf(F,"} bdef\n");                                                     \
    fprintf(F,"/Pc {\n");                                                      \
    fprintf(F,"] /PolyPath xdef\n");                                           \
    fprintf(F,"PolyPath length 1 gt {\n");                                     \
    fprintf(F,"gsave\n");                                                      \
    fprintf(F,"myPolyarcAttr 1 eq myPolyarcAttr 2 eq or {\n");                 \
    fprintf(F,"newpath\n");                                                    \
    fprintf(F,"PolyPath aload pop moveto\n");                                  \
    fprintf(F,"PolyPath length 2 sub 2 idiv {lineto} repeat\n");               \
    fprintf(F,"closepath\n");                                                  \
    fprintf(F,"fill } if\n");                                                  \
/*  fprintf(F,"0 setgray\n"); */                                               \
    fprintf(F,"myPolyarcAttr 0 eq myPolyarcAttr 2 eq or {\n");                 \
    fprintf(F,"newpath\n");                                                    \
    fprintf(F,"PolyPath aload pop moveto\n");                                  \
    fprintf(F,"PolyPath length 2 sub 2 idiv {lineto} repeat\n");               \
    fprintf(F,"stroke } if\n");                                                \
    fprintf(F,"grestore\n");                                                   \
    fprintf(F,"} if\n");                                                       \
    fprintf(F,"} bdef\n");
#define PS_Polyline_Open                                                       \
    fprintf(F,"Po\n");                         
#define PS_Polyline_Point(x,y)                                                 \
    fprintf(F,"%d %d\n",(int)(x),(int)(y));
#define PS_Polyline_Close                                                      \
    fprintf(F,"Pc\n");
/*----------------------------------------------------------------------------*/
#define PS_ProcArc                                                             \
    fprintf(F,"/A {\n");                                                       \
    fprintf(F,"/degree2 xdef\n");                                              \
    fprintf(F,"/degree1 xdef\n");                                              \
    fprintf(F,"/radius2 xdef\n");                                              \
    fprintf(F,"/radius1 xdef\n");                                              \
    fprintf(F,"/y xdef\n");                                                    \
    fprintf(F,"/x xdef\n");                                                    \
    fprintf(F,"gsave\n");                                                      \
    fprintf(F,"x y translate\n");                                              \
    fprintf(F,"1 radius2 radius1 div scale\n");                                \
    fprintf(F,"myPolyarcAttr 1 eq myPolyarcAttr 2 eq or {\n");                 \
    fprintf(F,"newpath\n");                                                    \
    fprintf(F,"myArcMode 0 eq {0 0 moveto} if\n");                             \
    fprintf(F,"0 0 radius1 degree1 degree2 arc\n");                            \
    fprintf(F,"closepath\n");                                                  \
    fprintf(F,"fill } if\n");                                                  \
/*  fprintf(F,"0 setgray\n"); */                                               \
    fprintf(F,"myPolyarcAttr 0 eq myPolyarcAttr 2 eq or {\n");                 \
    fprintf(F,"newpath\n");                                                    \
    fprintf(F,"myArcMode 0 eq {0 0 moveto} if\n");                             \
    fprintf(F,"0 0 radius1 degree1 degree2 arc\n");                            \
/*  fprintf(F,"closepath\n"); */                                               \
    fprintf(F,"stroke } if\n");                                                \
    fprintf(F,"grestore\n");                                                   \
    fprintf(F,"} bdef\n")
#define PS_Arc(x,y,radius1,radius2,degree1,degree2)                            \
    fprintf(F,"%d %d %d %d %1.2f %1.2f A\n",                       \
              (int)(x),(int)(y),(int)(radius1),(int)(radius2),degree1,degree2);
/*----------------------------------------------------------------------------*/
#define PS_ProcTextStroke                                                      \
    fprintf(F,"/Distance {\n");                                                \
    fprintf(F,"/y2 xdef\n");                                                   \
    fprintf(F,"/x2 xdef\n");                                                   \
    fprintf(F,"/y1 xdef\n");                                                   \
    fprintf(F,"/x1 xdef\n");                                                   \
    fprintf(F,"x2 x1 sub dup mul\n");                                          \
    fprintf(F,"y2 y1 sub dup mul\n");                                          \
    fprintf(F,"add sqrt\n");                                                   \
    fprintf(F,"} bdef\n");                                                     \
    fprintf(F,"/GetWYSIWYGFactor {\n");                                        \
    fprintf(F,"/str xdef\n");                                                  \
    fprintf(F,"/Y1 xdef\n");                                                   \
    fprintf(F,"/X1 xdef\n");                                                   \
    fprintf(F,"gsave\n");                                                      \
    fprintf(F,"[1 0 0 1 0 0] setmatrix\n");                                    \
    fprintf(F,"str stringwidth pop /Tx1 xdef 1 /Ty1 xdef\n");                  \
    fprintf(F,"X1 str length mul Tx1 div /Fx xdef\n");                         \
    fprintf(F,"Y1 Ty1 div /Fy xdef\n");                                        \
    fprintf(F,"grestore\n");                                                   \
    fprintf(F,"Fx Fy\n");                                                      \
    fprintf(F,"} bdef\n");                                                     \
    fprintf(F,"/T {\n");                                                       \
    fprintf(F,"/yPitch xdef %% for WYSIWYG\n");                                \
    fprintf(F,"/xPitch xdef %% for WYSIWYG\n");                                \
    fprintf(F,"/str xdef\n");                                                  \
    fprintf(F,"/y xdef\n");                                                    \
    fprintf(F,"/x xdef\n");                                                    \
    fprintf(F,"gsave\n");                                                      \
    fprintf(F,"x y moveto\n");                                                 \
    fprintf(F,"%%TextMatrix concat\n");                                          \
    fprintf(F,"%%xPitch yPitch str GetWYSIWYGFactor scale\n");                   \
    fprintf(F,"gsave\n");                                                      \
    fprintf(F,"newpath 0 0 moveto\n");                                         \
    fprintf(F,"str true charpath flattenpath pathbbox\n");                     \
    fprintf(F,"neg /H_22 xdef neg /W_22 xdef pop pop\n");                      \
    fprintf(F,"grestore\n");                                                   \
    switch (PrintType) {                                                       \
    case GE_PSGray :                                                           \
    case GE_PSEncapsulated :                                                   \
    fprintf(F,"myFontColor setgray\n");                                        \
         break;                                                                \
    case GE_PSColor :                                                          \
    fprintf(F,"myFontColor setrgbcolor\n");                                    \
         break;                                                                \
    }                                                                          \
    fprintf(F,"/W12 W22 2 div def\n");                                         \
    fprintf(F,"/H12 H22 2 div def\n");                                         \
    fprintf(F,"myTextFormat 11 eq {0 0 rmoveto} {\n");                         \
    fprintf(F,"myTextFormat 12 eq {W12 0 rmoveto} {\n");                       \
    fprintf(F,"myTextFormat 13 eq {W22 0 rmoveto} {\n");                       \
    fprintf(F,"myTextFormat 21 eq {0 H12 rmoveto} {\n");                       \
    fprintf(F,"myTextFormat 22 eq {W12 H12 rmoveto} {\n");                     \
    fprintf(F,"myTextFormat 23 eq {W22 H12 rmoveto} {\n");                     \
    fprintf(F,"myTextFormat 31 eq {0 H22 rmoveto} {\n");                       \
    fprintf(F,"myTextFormat 32 eq {W12 H22 rmoveto} {\n");                     \
    fprintf(F,"myTextFormat 33 eq {W22 H22 rmoveto} {\n");                     \
    fprintf(F,"} ifelse } ifelse } ifelse\n");                                 \
    fprintf(F,"} ifelse } ifelse } ifelse\n");                                 \
    fprintf(F,"} ifelse } ifelse } ifelse\n");                                 \
    fprintf(F,"currentpoint /Y xdef /X xdef\n");                               \
    fprintf(F,"H22 1 yPitch sub add /H22 xdef\n");                             \
    fprintf(F,"str (\n");                                                      \
    fprintf(F,") search pop show\n");                                          \
    fprintf(F,"{count 1 eq {exit} if\n");                                      \
    fprintf(F,"pop X Y H22 add /Y xdef Y moveto (\n");                         \
    fprintf(F,") search pop show}\n");                                         \
    fprintf(F,"loop\n");                                                       \
    fprintf(F,"grestore\n");                                                   \
    fprintf(F,"} bdef\n");
#define PS_TextStroke(x,y,str,xPitch,yPitch)                                   \
    fprintf(F,"%d %d (%s) %1.2f %1.2f T\n",(int)(x),(int)(y),str,xPitch,yPitch);
#define PS_ProcText                                                            \
    fprintf(F,"/T1 {\n");                                                      \
    fprintf(F,"/str xdef\n");                                                  \
    fprintf(F,"/y xdef\n");                                                    \
    fprintf(F,"/x xdef\n");                                                    \
    fprintf(F,"gsave\n");                                                      \
    fprintf(F,"gsave\n");                                                      \
    fprintf(F,"newpath 0 0 moveto\n");                                         \
    fprintf(F,"str true charpath flattenpath pathbbox\n");                     \
    fprintf(F,"neg /H22 xdef neg /W22 xdef pop pop\n");                        \
    fprintf(F,"grestore\n");                                                   \
    fprintf(F,"x y translate\n");                                              \
    fprintf(F,"0 0 moveto myFontAngle 10 div rotate\n");                       \
    switch (PrintType) {                                                       \
    case GE_PSGray :                                                           \
    case GE_PSEncapsulated :                                                   \
    fprintf(F,"myFontColor setgray\n");                                        \
         break;                                                                \
    case GE_PSColor :                                                          \
    fprintf(F,"myFontColor setrgbcolor\n");                                    \
         break;                                                                \
    }                                                                          \
    fprintf(F,"/W12 W22 2 div def\n");                                         \
    fprintf(F,"/H12 H22 2 div def\n");                                         \
    fprintf(F,"myTextFormat 11 eq {0 0 rmoveto} {\n");                         \
    fprintf(F,"myTextFormat 12 eq {W12 0 rmoveto} {\n");                       \
    fprintf(F,"myTextFormat 13 eq {W22 0 rmoveto} {\n");                       \
    fprintf(F,"myTextFormat 21 eq {0 H12 rmoveto} {\n");                       \
    fprintf(F,"myTextFormat 22 eq {W12 H12 rmoveto} {\n");                     \
    fprintf(F,"myTextFormat 23 eq {W22 H12 rmoveto} {\n");                     \
    fprintf(F,"myTextFormat 31 eq {0 H22 rmoveto} {\n");                       \
    fprintf(F,"myTextFormat 32 eq {W12 H22 rmoveto} {\n");                     \
    fprintf(F,"myTextFormat 33 eq {W22 H22 rmoveto} {\n");                     \
    fprintf(F,"} ifelse } ifelse } ifelse\n");                                 \
    fprintf(F,"} ifelse } ifelse } ifelse\n");                                 \
    fprintf(F,"} ifelse } ifelse } ifelse\n");                                 \
    fprintf(F,"str show\n");                                                   \
    fprintf(F,"grestore\n");                                                   \
    fprintf(F,"} bdef\n");
#define PS_Text1(x,y,str)                                                      \
    fprintf(F,"%d %d (%s) T1\n",(int)(x),(int)(y),str);
/*----------------------------------------------------------------------------*/
#define PS_ProcClip                                                            \
    fprintf(F,"/Clip {\n");                                                    \
    fprintf(F,"/y2 xdef\n");                                                   \
    fprintf(F,"/x2 xdef\n");                                                   \
    fprintf(F,"/y1 xdef\n");                                                   \
    fprintf(F,"/x1 xdef\n");                                                   \
    fprintf(F,"newpath\n");                                                    \
    fprintf(F,"x1 y1 moveto\n");                                               \
    fprintf(F,"x2 y1 lineto\n");                                               \
    fprintf(F,"x2 y2 lineto\n");                                               \
    fprintf(F,"x1 y2 lineto\n");                                               \
    fprintf(F,"x1 y1 lineto\n");                                               \
    fprintf(F,"closepath clip\n");                                             \
    fprintf(F,"} bdef\n")
#define PS_Clip(x1,y1,x2,y2);                                                  \
    fprintf(F,"%d %d %d %d Clip\n",(x1),(y1),(x2),(y2));
/*----------------------------------------------------------------------------*/

/*
/printZip
{ 0 0 moveto (Zip) show} def
0.95 -0.05 0
{setgray printZip -1 0.5 translate} for
1 setgray printZip
*/

/* EPS ************************************************************************/
/*
http://www.cs.wisc.edu/~ghost/gsview/winhelp.html#1011
To convert a PostScript file to EPS, the original file must be a single page
document.
EPS documents must not use any of the following operators:
     banddevice   clear         cleardictstack  copypage
     erasepage    exitserver    framedevice     grestoreall
     initclip    *initgraphics *initmatrix      quit
     renderbands  setglobal     setpagedevice   setpageparams
     setshared    startjob      letter          note
     legal        a3            a4              a5
The following operators should be used with care:
     nulldevice   setgstate     sethalftone   *setmatrix
     setscreen    settransfer   setcolortransfer

http://www.gkss.de/W3/PS/eps.html
The first line must be %!PS-Adobe EPSF-3.0
The file must make use of the BoundingBox comment
The file should be a single page image (in DSC terms, the %%Pages
comment must have a value of 0 or 1).
The file should not use any operators which affect the global state.
Finally, the EPS file should not use showpage.
*/

#define EPS_Adobe_ID(ID_)        fprintf(F,"%%!PS-Adobe-%d.0 EPSF-%d.0\n",     \
                                           ID_,ID_);                           \
                                 fprintf(F,"%%%%BoundingBox: 0 0 800 570\n");
                                 /* see int GEPrintOpen() */

/* HPGL ***********************************************************************/

/*
#define HPGL_Header              fprintf(F,"\x1B.(BPINPS7100,9600RO90IP;\n");
#define HPGL_Header              fprintf(F,"\x1B.(BPINSP9600,7100RO90IP;\n");
*/
#define HPGL_Header              fprintf(F,"\x1B%%-1BBPINRO0IP;WU0PW0.25;\n");
#define HPGL_Trailer             fprintf(F,"PUSP0;\n");
#define HPGL_InitiGraphics       fprintf(F,"VS10SP1PU;\n"); /* NP16 */
#define HPGL_PenSelect(i)        fprintf(F,"SP%dPU;\n",(i));

#define HPGL_Point(x1,y1)                                                      \
    fprintf(F,"PU%d,%dPD;\n",(int)(x1),(int)(y1));
#define HPGL_Line(x1,y1,x2,y2)                                                 \
    fprintf(F,"PU%d,%dPD%d,%d;\n",(int)(x1),(int)(y1),(int)(x2),(int)(y2));
#define HPGL_Polyline_Open(x1,y1)                                              \
    fprintf(F,"PM0PU%d,%dPD",(int)(x1),(int)(y1));
#define HPGL_Polyline_Point(x1,y1)                                             \
    fprintf(F,",%d,%d",(int)(x1),(int)(y1));
#define HPGL_Polyline_Close(i)                                                 \
    fprintf(F,"PM2%s;\n",(i) ? "FP":"EP");
#define HPGL_Arc(x,y,radius1,radius2,degree1,degree2)                          \
    {                                                                          \
    int xs,ys;                                                                 \
    xs=(int)(x+radius1*cos(RADIAN(degree1)));                                  \
    ys=(int)(y+radius2*sin(RADIAN(degree1)));                                  \
    fprintf(F,"PU%d,%dAA%d,%d,%dPU;\n",                                        \
            xs,ys,(int)(x),(int)(y),(int)(degree2-degree1));                   \
    }

/******************************************************************************/
/**********************************k*i*m***************************************/
/****************************y*o*n*g*-*s*h*i*k*********************************/
/******************************************************************************/
/****************************-*g*r*a*p*h*i*c*-*********************************/
/********************************p*r*i*n*t*************************************/
/*******************************e*n*g*i*n*e************************************/
/******************************************************************************/
/*****************************4*3*2*5*1*2*0*3**********************************/
/******************************************************************************/

int GEPrintOpen( name,printType,printDirection,xmtx )
   char *name;
   GEPRINTTYPE printType;
   GEPRINTDIRECTION printDirection;
   XMTX2D xmtx;
{
   GERECT paper;
   double Angle,XScale,YScale,XTranslate,YTranslate;

   F=fopen(name,"w");
   if (!F) errWarning("GEPrintOpen : file open error");
   PrintName=strdpl(name);
   PrintType=printType;
   PrintDirection=printDirection;
   PrintPageIndex=0;

   AlloXMatrix2D(&myGEXMatrix2D);
   switch (PrintType) {
   case GE_PSGray :
   case GE_PSColor :
   case GE_PSEncapsulated :
      paper.x=0;
      paper.y=0;
      paper.width=2000;  /* 2050-50 => 20.0mm */
      paper.height=2820; /* 2920-50-50 => 28.2mm */
      break;
   case GE_HPGL2 :
      paper.x=0;
      paper.y=0;
      paper.width=7100; /* 7600 ?? */
      paper.height=9600; /* 10850 ?? */
      switch (PrintDirection) { /* I was not willing to do this way ! */
      case GE_Landscape :
         PrintDirection=GE_Portrait;
         break;
      case GE_Portrait  :
         PrintDirection=GE_Landscape;
         break;
      }
      break;
   }
   /* Default (Adobe) Portrait Direction */
   XScale=(double)MIN(paper.width,paper.height);
   /* GE_WinScaleByObject */
   YScale=XScale;
   switch (PrintDirection) { /* based on the (Adobe) Portrait Page */
   case GE_Portrait  :
      Angle=0.0;
      XTranslate=0.0;
      YTranslate=(double)(paper.height-paper.width)/2.0;
      break;
   case GE_Landscape :
      Angle=PI/2.0;
      XTranslate=(double)(paper.height-paper.width)/2.0;
      YTranslate=0.0;
      break;
   }
   XMatrix2DScale(myGEXMatrix2D,0.0,0.0,XScale,YScale,ComXMatrix2DAdobe);
   XMatrix2DRotate(myGEXMatrix2D,0.0,0.0,Angle,ComXMatrix2DAdobe);
   XMatrix2DTranslate(myGEXMatrix2D,XTranslate,YTranslate,ComXMatrix2D);

   if (xmtx) ComXMatrix2DAdobe(myGEXMatrix2D,xmtx);

   AlloXMatrix2D(&DeviceXmtx2D);
   SetXMatrix2D(DeviceXmtx2D,myGEXMatrix2D[1][1],myGEXMatrix2D[1][2],
                             myGEXMatrix2D[2][1],myGEXMatrix2D[2][2],
                             myGEXMatrix2D[3][1],myGEXMatrix2D[3][2]);
   return TRUE;
}

int GEPrintClose()
{
   fclose(F);

   free(PrintName);
   PrintName=NULL;
   PrintType=0;
   PrintDirection=0;
   FreeXMatrix2D(myGEXMatrix2D);
   FreeXMatrix2D(DeviceXmtx2D);
   myGEXMatrix2D=NULL;
   DeviceXmtx2D=NULL;
   return TRUE;
}

int GEPrintSetProcedure()
{
   switch (PrintType) {
   case GE_PSGray :
   case GE_PSColor :
      BLSetProcedure(BL_COMMAND, NULL,        _PrintCommand);
      BLSetProcedure(BL_HEADER,  PSHeader,    _PrintHeader);
      BLSetProcedure(BL_2DMDATA, PSXmtx2DData,_PrintXmtx2DData);
      BLSetProcedure(BL_3DMDATA, PSXmtx3DData,_PrintXmtx3DData); 
      BLSetProcedure(BL_GC,      PSGc,        NULL);
      BLSetProcedure(BL_POINT,   PSPoint,     _PrintPoint);
      BLSetProcedure(BL_LINE,    PSLine,      _PrintLine);
      BLSetProcedure(BL_POLY,    PSPolyline,  _PrintPoint);
      BLSetProcedure(BL_ARC,     PSArc,       _PrintArc);
      BLSetProcedure(BL_TEXT,    PSText,      _PrintText);
      BLSetProcedure(BL_CLIPWIN, PSClipWin,   NULL);
      BLSetProcedure(BL_PRINT,   NULL,        NULL);
      break;
   case GE_PSEncapsulated :
      BLSetProcedure(BL_COMMAND, NULL,        _PrintCommand);
      BLSetProcedure(BL_HEADER,  PSHeader,    _PrintHeader);
      BLSetProcedure(BL_2DMDATA, PSXmtx2DData,_PrintXmtx2DData);
      BLSetProcedure(BL_3DMDATA, PSXmtx3DData,_PrintXmtx3DData); 
      BLSetProcedure(BL_GC,      PSGc,        NULL);
      BLSetProcedure(BL_POINT,   PSPoint,     _PrintPoint);
      BLSetProcedure(BL_LINE,    PSLine,      _PrintLine);
      BLSetProcedure(BL_POLY,    PSPolyline,  _PrintPoint);
      BLSetProcedure(BL_ARC,     PSArc,       _PrintArc);
      BLSetProcedure(BL_TEXT,    PSText,      _PrintText);
      BLSetProcedure(BL_CLIPWIN, PSClipWin,   NULL);
      BLSetProcedure(BL_PRINT,   NULL,        NULL);
      break;
   case GE_HPGL2 :
      BLSetProcedure(BL_COMMAND, NULL,          _PrintCommand);
      BLSetProcedure(BL_HEADER,  HPGLHeader,    _PrintHeader);
      BLSetProcedure(BL_2DMDATA, HPGLXmtx2DData,_PrintXmtx2DData);
      BLSetProcedure(BL_3DMDATA, HPGLXmtx3DData,_PrintXmtx3DData); 
      BLSetProcedure(BL_GC,      HPGLGc,        NULL);
      BLSetProcedure(BL_POINT,   HPGLPoint,     _PrintPoint);
      BLSetProcedure(BL_LINE,    HPGLLine,      _PrintLine);
      BLSetProcedure(BL_POLY,    HPGLPolyline,  _PrintPoint);
      BLSetProcedure(BL_ARC,     HPGLArc,       _PrintArc);
      BLSetProcedure(BL_TEXT,    HPGLText,      _PrintText);
      BLSetProcedure(BL_CLIPWIN, NULL,              NULL);
      BLSetProcedure(BL_PRINT,   HPGLPrint,     NULL);
      break;
   default : 
      errExit("NOT YET in GEPrintSetProc()");
   }
   return TRUE;
}

int GEPrintProcess( list )
   BLOBLIST *list;
{
   char fileName[256];

   strcpy2buf(fileName,PrintName,noof(fileName));
#if defined(_MSC_)   
   strrep(fileName,"\\","\\\\");
#endif
   switch (PrintType) {
   case GE_PSGray :
   case GE_PSColor :
      PS_Adobe_ID(1);
      PS_Comments(fileName);
      PS_BindKeys;
      PS_ProcTitle;
      PS_ProcPortrait;
      PS_ProcLandscape;
      PS_ProcPoint;
      PS_ProcLine;
      PS_ProcRect;
      PS_ProcPolyline;
      PS_ProcArc;
      PS_ProcText;
      PS_ProcClip;
      PS_InitiGraphics;
      PS_Defaults(PrintType);
      BLExecute(list);
      PS_ShowPage;
      PS_Restore;
      PS_Trailer;
      break;
   case GE_PSEncapsulated :
      EPS_Adobe_ID(3);
      PS_Comments(fileName);
      PS_BindKeys;
      PS_ProcTitle;
      PS_ProcPortrait;
      PS_ProcLandscape;
      PS_ProcPoint;
      PS_ProcLine;
      PS_ProcRect;
      PS_ProcPolyline;
      PS_ProcArc;
      PS_ProcText;
      PS_ProcClip;
      PS_Defaults(PrintType);
      BLExecute(list);
      PS_Trailer;
      break;
   case GE_HPGL2 :
      HPGL_Header;
      HPGL_InitiGraphics;
      BLExecute(list);
      HPGL_Trailer;
      break;
   default : 
      errExit("NOT YET in GEPrintProcess()");
   }
   return TRUE;
}

static 
int PSHeader( ptr,tot )
   BLOBHEADER *ptr;
   int tot;
{
   XMTX2D xmtx;

   PrintPageIndex++;
   if (PrintPageIndex==1) {
      PS_LineFeed;
      if (ptr->reset) {
         PS_Header(PrintPageIndex);
      }
      PS_Save;
   } else {
      PS_Restore;
      PS_LineFeed;
      if (ptr->reset) {
         PS_ShowPage;
         PS_Header(PrintPageIndex);
      }
      PS_Save;
   }

   if (ptr->reset) {
      fprintf(F,"(%s(c)shik",GECoreVersion);
      fprintf(F," + %s) Title\n",CurrentDateAndTime());
   }

   PS_Portrait; /* must */

   SetXMatrix2D(myGEXMatrix2D,DeviceXmtx2D[1][1],DeviceXmtx2D[1][2],
                             DeviceXmtx2D[2][1],DeviceXmtx2D[2][2],
                             DeviceXmtx2D[3][1],DeviceXmtx2D[3][2]);
   AlloXMatrix2D(&xmtx);

   SetXMatrix2D(xmtx,ptr->m11,ptr->m12,
                     ptr->m21,ptr->m22,
                     ptr->m31,ptr->m32);
   ComXMatrix2DAdobe(myGEXMatrix2D,xmtx);
   FreeXMatrix2D(xmtx);
   return TRUE;
}

static 
int PSXmtx2DData( ptr,tot )
   BLOB2DMDATA *ptr;
   int tot;
{
   XMTX2D xmtx;

   AlloXMatrix2D(&xmtx);
   SetXMatrix2D(xmtx,ptr->m11,ptr->m12,
                     ptr->m21,ptr->m22,
                     ptr->m31,ptr->m32);
   ComXMatrix2DAdobe(myGEXMatrix2D,xmtx);
   FreeXMatrix2D(xmtx);
   return TRUE;
}

static
int PSXmtx3DData( ptr,tot )
   BLOB3DMDATA *ptr;
   int tot;
{
   errExit("Not Yet .. in PSXmtx3DData()");
   return TRUE;
}

static
int PSGc( gc,tot )
   BLOBGC *gc;
   int tot;
{
   int colorMax;
   unsigned short r,g,b;
   float grey,red,green,blue;
   int i,dash_offset=0;

   if (!gc->gc_mask) return FALSE;
/*
   if (gc->gc_mask&GE_GCMaskFunction) {
   }   
*/
   if (gc->gc_mask&GE_GCMaskForeground) {
      GEColor2RGB(NULL,gc->foreground,&r,&g,&b,1);
      colorMax=(int)GEColorTotal(NULL);
      red=(float)r/colorMax;
      green=(float)g/colorMax;
      blue=(float)b/colorMax;
      switch (PrintType) {
      case GE_PSGray :
      case GE_PSEncapsulated :
         grey=(float)(0.30*red+0.59*green+0.11*blue); /* Steve Rimmer 386 */
         fprintf(F,"%1.4f setgray\n",grey);
         if (gc->gc_type==GE_GCTextL || gc->gc_type==GE_GCText)
            fprintf(F,"/myFontColor %1.2f def\n",grey);
         break;
      case GE_PSColor :
         fprintf(F,"%1.2f %1.2f %1.2f setrgbcolor\n",red,green,blue);
         if (gc->gc_type==GE_GCTextL || gc->gc_type==GE_GCText)
            fprintf(F,"/myFontColor {%1.2f %1.2f %1.2f} def\n",red,green,blue);
         break;
      }
   }
/*
   if (gc->gc_mask&GE_GCMaskBackground) {
   }
*/
   if (gc->gc_mask&GE_GCMaskLineWidth) {
      fprintf(F,"%1.2f setlinewidth\n",(float)gc->line_width*0.5);
   }
   if (gc->gc_mask&GE_GCMaskLineStyle) {
      switch (gc->line_style) {
      case GE_LineSolid      : GE_LineSolid;     break;
      case GE_LineOnOffDash  : GE_LineOnOffDash; break;
      case GE_LineDoubleDash : GE_LineDoubleDash;break;
      }
   }
   if (gc->gc_mask&GE_GCMaskCapStyle) {
      switch (gc->cap_style) {
      case GE_CapNotLast    : fprintf(F,"0 setlinecap\n");break;
      case GE_CapButt       : fprintf(F,"0 setlinecap\n");break;
      case GE_CapRound      : fprintf(F,"1 setlinecap\n");break;
      case GE_CapProjecting : fprintf(F,"2 setlinecap\n");break;
      }
   }
   if (gc->gc_mask&GE_GCMaskJoinStyle) {
      switch (gc->join_style) {
      case GE_JoinMiter : fprintf(F,"0 setlinejoin\n");break;
      case GE_JoinRound : fprintf(F,"1 setlinejoin\n");break;
      case GE_JoinBevel : fprintf(F,"2 setlinejoin\n");break;
      }
   }
/*
   if (gc->gc_mask&GE_GCMaskFillStyle) {
   }
*/
   if (gc->gc_mask&GE_GCMaskFillRule) {
      switch (gc->fill_rule) {
      case GE_FillEvenOdd : fprintf(F,"/myFillRule 0 def\n");break;
      case GE_FillWinding : fprintf(F,"/myFillRule 1 def\n");break;
      }
   }
   if (gc->gc_mask&GE_GCMaskArcMode) {
      switch (gc->arc_mode) {
      case GE_ArcPieSlice : fprintf(F,"/myArcMode 0 def\n");break;
      case GE_ArcChord    : fprintf(F,"/myArcMode 1 def\n");break;
      }
   }
/*
   if (gc->gc_mask&GE_GCMaskTile) {
      if (gc->stipple) {
      }
   }
   if (gc->gc_mask&GE_GCMaskStipple) {
      if (gc->stipple) {
      }
   }
   if (gc->gc_mask&GE_GCMaskTileStipXOrigin) {
   }
   if (gc->gc_mask&GE_GCMaskTileStipYOrigin) {
   }
*/
   if (gc->gc_mask&GE_GCMaskFont) {
      fprintf(F,"/myFontName (%s) def\n",*(gc->font)=='*' ? "Helvetica-Bold":gc->font);
       fprintf(F,"myFontName findfont %d scalefont setfont\n",
          (int)(gc->font_height*10*0.4)); /* [0.1 mm] */ /* stupid 0.4 ! */
      fprintf(F,"/myFontAngle %d def\n",gc->font_angle);      /* [0.1 degree] */
      fprintf(F,"/myFontMatrix [%1.2f %1.2f %1.2f %1.2f %1.2f %1.2f] bdef\n",
         gc->font_matrix.m11,gc->font_matrix.m12,
         gc->font_matrix.m21,gc->font_matrix.m22,
         gc->font_matrix.m31,gc->font_matrix.m32);
      {
      char v,h;
      switch (gc->text_format&15) {
      case GE_AlignBottom   : v='1'; break;
      case GE_AlignBaseline : v='2'; break;
      case GE_AlignVCenter  : v='2'; break;
      case GE_AlignTop      : v='3'; break;
      }
      switch (gc->text_format&240) {
      case GE_AlignLeft     : h='1'; break;
      case GE_AlignHCenter  : h='2'; break;
      case GE_AlignRight    : h='3'; break;
      }
      fprintf(F,"/myTextFormat %c%c def\n",v,h);
      }
   }
/*
   if (gc->gc_mask&GE_GCMaskSubwindowMode) {
   }
   if (gc->gc_mask&GE_GCMaskGraphicsExposures) {
   }
   if (gc->gc_mask&GE_GCMaskClipXOrigin) {
   }
   if (gc->gc_mask&GE_GCMaskClipYOrigin) {
   }
   if (gc->gc_mask&GE_GCMaskClipMask) {
   }
*/
   if (gc->gc_mask&GE_GCMaskDashOffset) {
      dash_offset=gc->dash_offset;
   }
   if (gc->gc_mask&GE_GCMaskDashList) {
      if (gc->dashes
      &&  gc->line_style!=GE_LineSolid) {
         fprintf(F,"[");
         for (i=0;i<gc->dashes;i++)
         fprintf(F,"%d ",gc->dash_list[i]);
         fprintf(F,"] %d setdash\n",dash_offset);
      } else {
         fprintf(F,"[ ] %d setdash\n",dash_offset);
      }
   }
   if (gc->gc_mask&GE_GCMaskStipple) {
      if (gc->stipple) {
         switch (gc->polyarc_attr) {
         case GE_PolyArcLine : fprintf(F,"/myPolyarcAttr 0 def\n");break;
         case GE_PolyArcFill : fprintf(F,"/myPolyarcAttr 1 def\n");break;
         case GE_PolyArcBoth : fprintf(F,"/myPolyarcAttr 2 def\n");break;
         default :             fprintf(F,"/myPolyarcAttr 0 def\n");break;
         }
      } else
                               fprintf(F,"/myPolyarcAttr 0 def\n");
   }
/*
   switch (gc->poly_shape) {
   case GE_PolyConvex    : break;
   case GE_PolyNonConvex : break;
   case GE_PolyComplex   : break;
   }
*/
   return TRUE;
}

static 
int PSPoint( ptr,tot ) /* D */
   BLOBPOINT *ptr;
   int tot;
{
   int i;
   double x,y;

   for (i=0;i<tot;i++) {
      x=ptr[i].x;
      y=ptr[i].y;
      xform(&x,&y);
      PS_Point(x,y);
   }
   return TRUE;
}

static
int PSLine( ptr,tot ) /* L */
   BLOBLINE *ptr;
   int tot;
{
   int i;
   double x1,y1,x2,y2;

   for (i=0;i<tot;i++) {
      x1=ptr[i].x1;
      y1=ptr[i].y1;
      x2=ptr[i].x2;
      y2=ptr[i].y2;
      xform_it(&x1,&y1,&x2,&y2);
      PS_Line(x1,y1,x2,y2);
   }
   return TRUE;
}

static 
int PSPolyline( ptr,tot ) /* P */
   BLOBPOINT *ptr;
   int tot;
{
   int i;
   double x,y;

   if (!tot)
      return FALSE;
   PS_Polyline_Open;
   for (i=0;i<tot;i++) {
      x=ptr[i].x;
      y=ptr[i].y;
      xform(&x,&y);
      PS_Polyline_Point(x,y);
   }
   PS_Polyline_Close;
   return TRUE;
}

static 
int PSArc( ptr,tot ) /* A */
   BLOBARC *ptr;
   int tot;
{
   int i;
   double x,y,width,height,degree1,degree2;

   for (i=0;i<tot;i++) {
      x=ptr[i].x;
      y=ptr[i].y;
      xform(&x,&y);
      width=ptr[i].width;
      height=ptr[i].height;
      dxform(&width,&height);
      width/=2.0;
      height/=2.0;
      degree1=(ptr[i].angle1*180/PI);
      degree2=(ptr[i].angle2*180/PI);
      switch (PrintDirection) {
      case GE_Landscape :
         PS_Arc(x+width,y-height,width,height,degree1,degree2);break;
      case GE_Portrait  :
         PS_Arc(x+width,y+height,width,height,degree1,degree2);break;
      }
   }
   return TRUE;
}

static 
int PSText( ptr,tot ) /* T */
   BLOBTEXT *ptr;
   int tot;
{
   double x,y;
   char *p,buf256[256];

   SaveXMatrix2D();
   x=((BLOBPOINT*)ptr)->x;
   y=((BLOBPOINT*)ptr)->y;
   xform(&x,&y);
   myGEXMatrix2D[3][1]=x;
   myGEXMatrix2D[3][2]=y;
   p=(char*)ptr;
   p+=sizeof(BLOBPOINT);
   strcpy2buf(buf256,p,256);
   strrep(buf256,"(","\\(");
   strrep(buf256,")","\\)");
   /*
   PS_TextStroke(x,y,buf256,
       1.0+(float)(myGEFONTATTR.ch_space)/myGEFONTATTR.width,
       1.0+(float)(myGEFONTATTR.ln_space)/myGEFONTATTR.height);
                      */
   PS_Text1(x,y,buf256);
   RestoreXMatrix2D();
   return TRUE;
}

static
int PSClipWin( ptr,tot )
   BLOBCLIPWIN *ptr;
   int tot;
{
   printf("Not yet ... in PSClipWin()\n");
   return TRUE;
}

int GEPSFDumpWindow( node )
   MYDISPLAY *node;
{
   GERECT data;
   char *image;
   unsigned short red,green,blue,grey;
   register unsigned int i,j,k;
   FILE *out;
   char *name="GEwinDump";

   GEGetGeometry(node,&data);
   GEAlloImage(node,data.width,data.height,&image);
   GEGetImage(node,image,0,0,0,0,data.width,data.height); 
   out=fopen(name,"w");
   fprintf(out,"%%!ps-adobe-1.0\n");
   PS_Comments(name);
   fprintf(out,"%%%%pages: 1\n");
   fprintf(out,"%%%%reference: Steve Rimmer 344\n");
   fprintf(out,"%%%%boundingbox: (atend)\n");
   fprintf(out,"%%%%endcomments\n");
   fprintf(out,"initgraphics\n");
   fprintf(out,"/width %d def\n",data.width);
   fprintf(out,"/height %d def\n",data.height);
   fprintf(out,"/picstr 32 string def\n");
   fprintf(out,"/hardcopy {\n");
   fprintf(out,"gsave\n");
   fprintf(out,"width height 8 [width 0 0 height neg 0 height]\n");
   fprintf(out,"{currentfile picstr readhexstring pop} image\n");
   fprintf(out,"grestore\n");
   fprintf(out,"} def\n");
   fprintf(out,"25 40 translate\n");
   fprintf(out,"width height scale\n");
   fprintf(out,"hardcopy\n");
   for (j=0,k=1;j<data.height;j++) {
      for (i=0;i<data.width;i++) {
         GEGetPixel(node,image,i,j,&red,&green,&blue);
         red>>=8;
         green>>=8;
         blue>>=8;
         grey=(char)(0.30*red+0.59*green+0.11*blue); /* Steve Rimmer 386 */
         grey=0xff-grey;
         if (grey>255) grey=255;
         fprintf(out,"%s",c2ha((char)grey));
         if (!(k++&0x1f)) fprintf(out,"\n");
      }
   }
   fprintf(out,"showpage\n");
   fclose(out);
   printf("GEPSFDumpWindow() : written \"%s\" ...\n",name);
   GEFreeImage(image);
   return TRUE;
}

/*----------------------------------------------------------------------------*/

static
int HPGLHeader( ptr,tot )
   BLOBHEADER *ptr;
   int tot;
{
   XMTX2D xmtx;

   SetXMatrix2D(myGEXMatrix2D,DeviceXmtx2D[1][1],DeviceXmtx2D[1][2],
                               DeviceXmtx2D[2][1],DeviceXmtx2D[2][2],
                               DeviceXmtx2D[3][1],DeviceXmtx2D[3][2]);
   AlloXMatrix2D(&xmtx);
   SetXMatrix2D(xmtx,ptr->m11,ptr->m12,
                     ptr->m21,ptr->m22,
                     ptr->m31,ptr->m32);
   ComXMatrix2DAdobe(myGEXMatrix2D,xmtx);
   FreeXMatrix2D(xmtx);
   return TRUE;
}

static
int HPGLXmtx2DData( ptr,tot )
   BLOB2DMDATA *ptr;
   int tot;
{
   PSXmtx2DData(ptr,tot);
   return TRUE;
}

static
int HPGLXmtx3DData( ptr,tot )
   BLOB2DMDATA *ptr;
   int tot;
{
   PSXmtx3DData(ptr,tot);
   return TRUE;
}

static
int HPGLGc( gc,tot )
   BLOBGC *gc;
   int tot;
{
   int i;

   if (gc->gc_mask&GE_GCMaskForeground) {
      HPGL_LineForeground=gc->foreground;
   }
   if (gc->gc_mask&GE_GCMaskCapStyle) {
      switch (gc->cap_style) {
      case GE_CapNotLast    : fprintf(F,"LA1,1;\n");break;
      case GE_CapButt       : fprintf(F,"LA1,1;\n");break;
      case GE_CapRound      : fprintf(F,"LA1,4;\n");break;
      case GE_CapProjecting : fprintf(F,"LA1,2;\n");break;
      }
   }
   if (gc->gc_mask&GE_GCMaskJoinStyle) {
      switch (gc->join_style) {
      case GE_JoinMiter : fprintf(F,"LA2,1;\n");break;
      case GE_JoinRound : fprintf(F,"LA2,4;\n");break;
      case GE_JoinBevel : fprintf(F,"LA2,5;\n");break;
      }
   }
   if (gc->gc_mask&GE_GCMaskDashList) {
      if (gc->dashes
      &&  gc->line_style!=GE_LineSolid) {
         fprintf(F,"UL8");
/*
         for (i=j=0;i<gc->dashes;i++)
            j+=gc->dash_list[i];
         for (i=0;i<gc->dashes;i++)
            fprintf(F,",%d",(int)(100*gc->dash_list[i]/j));
*/
         for (i=0;i<gc->dashes;i++) fprintf(F,",%d",(int)gc->dash_list[i]);
         fprintf(F,"LT8,4,1;\n");
      } else {
         fprintf(F,"LT;\n");
      }
   }
   if (gc->gc_mask&GE_GCMaskStipple
   &&  gc->stipple) {
      HPGL_PolyArcAttr=gc->polyarc_attr;
   } else
      HPGL_PolyArcAttr=GE_PolyArcLine;
   return TRUE;
}

static
int HPGLPoint( ptr,tot )
   BLOBPOINT *ptr;
   int tot;
{
   int i;
   double x,y;
      
   for (i=0;i<tot;i++) {
      x=ptr[i].x;
      y=ptr[i].y;
      xform(&x,&y);
      HPGL_Point(x,y);
   }
   return TRUE;
}

static
int HPGLLine( ptr,tot )
   BLOBLINE *ptr;
   int tot;
{
   int i;
   double x1,y1,x2,y2;

   for (i=0;i<tot;i++) {
      x1=ptr[i].x1;
      y1=ptr[i].y1;
      x2=ptr[i].x2;
      y2=ptr[i].y2;
      xform_it(&x1,&y1,&x2,&y2);
      HPGL_Line(x1,y1,x2,y2);
   }
   return TRUE;
}

static
int HPGLPolyline( ptr,tot )
   BLOBPOINT *ptr;
   int tot;
{
   int i;
   double x,y;
 
   x=ptr[0].x;
   y=ptr[0].y;
   xform(&x,&y);
   HPGL_Polyline_Open(x,y);
   for (i=1;i<tot;i++) {
      x=ptr[i].x;
      y=ptr[i].y;
      xform(&x,&y);
      HPGL_Polyline_Point(x,y);
   }
   HPGL_Polyline_Close(HPGL_PolyArcAttr==GE_PolyArcLine ? 0:1);
   return TRUE;
}

static
int HPGLArc( ptr,tot )
   BLOBARC *ptr;
   int tot;
{
   int i;
   double x,y,width,height,degree1,degree2;

   for (i=0;i<tot;i++) {
      x=ptr[i].x;
      y=ptr[i].y;
      xform(&x,&y);
      width=ptr[i].width;
      height=ptr[i].height;
      dxform(&width,&height);
      width/=2.0;
      height/=2.0;
      degree1=(ptr[i].angle1*180/PI);
      degree2=(ptr[i].angle2*180/PI);
      switch (PrintDirection) {
      case GE_Landscape :
         HPGL_Arc(x+width,y-height,width,height,degree1,degree2);break;
      case GE_Portrait  :
         HPGL_Arc(x+width,y+height,width,height,degree1,degree2);break;
      }
   }
   return TRUE;
}

static
int myDrawCharStroke( x,y,chr )
   double x,y;
   char chr;
{
   GESTROKEFONT font;
   unsigned int i=0;
   double x1,y1,x2,y2;
   static GELINE obj[36];
 
   while ((font.whole.word=STROKEFONT[(unsigned int)chr][i++])
         !=0xffff) {
      x1=x+(double)(font.part.col1)/7.0;
      y1=y+(double)(7-font.part.row1)/7.0;
      x2=x+(double)(font.part.col2)/7.0;
      y2=y+(double)(7-font.part.row2)/7.0;
      xform_it(&x1,&y1,&x2,&y2);
      HPGL_Line(x1,y1,x2,y2);
   }
   return TRUE;
}
 
int XYPDrawTextStroke( x,y,str )
   double x,y;
   char *str;
{
   /*
   double xplace,xpitch,ypitch,xwidth;
 
   xpitch=1.0+(double)(myGEFONTATTR.ch_space)/myGEFONTATTR.width;
   ypitch=1.0+(double)(myGEFONTATTR.ln_space)/myGEFONTATTR.height;
   xwidth=(double)strlen(str)*xpitch
         -(double)(myGEFONTATTR.ch_space)/myGEFONTATTR.width;
 
   if (myGEFONTATTR.align&GE_AlignLeft)         x;
   else if (myGEFONTATTR.align&GE_AlignHCenter) x-=xwidth/2.0;
   else if (myGEFONTATTR.align&GE_AlignRight)   x-=xwidth;
   if (myGEFONTATTR.align&GE_AlignBottom)       y;
   else if (myGEFONTATTR.align&GE_AlignVCenter) y-=ypitch/2.0;
   else if (myGEFONTATTR.align&GE_AlignTop)     y-=ypitch;
   fprintf(F,"LT;\n");
   for (xplace=x;*str;str++) {
      if (*str=='\n') {
         x=xplace;
         y-=ypitch;
         continue;
      }
      myDrawCharStroke(x,y,*str);
      x+=xpitch;
   }
   fprintf(F,"LT99;\n");
   */
   return TRUE;
}

/* 2000.2.24
static
int HPGLFontAttr( ptr,tot )
   BLOBFONTATTR *ptr;
   int tot;
{
   myGEFONTATTR.height   =ptr->height;
   myGEFONTATTR.width    =ptr->width;
   myGEFONTATTR.angle    =ptr->angle;
   myGEFONTATTR.alignment=ptr->alignment;
   return TRUE;
}
*/

static
int HPGLText( ptr,tot )
   BLOBTEXT *ptr;
   int tot;
{
   double x,y;
   char *p;
 
   SaveXMatrix2D();
   x=((BLOBPOINT*)ptr)->x;
   y=((BLOBPOINT*)ptr)->y;
   xform(&x,&y);
   //ComXMatrix2DAdobe(myGEXMatrix2D,myGETEXT2DATT R);
   myGEXMatrix2D[3][1]=x;
   myGEXMatrix2D[3][2]=y;
   p=(char*)ptr;
   p+=sizeof(BLOBPOINT);
   XYPDrawTextStroke(0.0,0.0,p);
   RestoreXMatrix2D();
   return TRUE;
}

static
int HPGLPrint( ptr,tot )
   BLOBPRINT *ptr;
{
   HPGL_PenSelect(ptr->xyp.pen_select);
   return TRUE;
}

int GEPrintBlobAsText( list )
   BLOBLIST *list;
{
   BLOBNODE *node;
   int i=0;

   printf("\n");
   node=list->head;
   while (node) {
      _PrintBLOBNode(i++,node);
      node=node->next;
   }
   return TRUE;
}

static
int _PrintBLOBNode( i,node )
   int i;
   BLOBNODE *node;
{
   static Pointer ptr=NULL;

   if (!ptr) {
      BLOBTABLE[(int)BL_COMMAND ].print=_PrintCommand;
      BLOBTABLE[(int)BL_HEADER  ].print=_PrintHeader;
      BLOBTABLE[(int)BL_2DMDATA ].print=_PrintXmtx2DData;
      BLOBTABLE[(int)BL_3DMDATA ].print=_PrintXmtx3DData;
      BLOBTABLE[(int)BL_GC      ].print=_PrintGC;
      BLOBTABLE[(int)BL_DATA    ].print=_PrintPoint;
      BLOBTABLE[(int)BL_POINT   ].print=_PrintPoint;
      BLOBTABLE[(int)BL_LINE    ].print=_PrintLine;
      BLOBTABLE[(int)BL_POLY    ].print=_PrintPoint;
      BLOBTABLE[(int)BL_ARC     ].print=_PrintArc;
      BLOBTABLE[(int)BL_TEXT    ].print=_PrintText;
//      BLOBTABLE[(int)BL_TEXTDATA].print=_PrintTextData;
      BLOBTABLE[(int)BL_CLIPWIN ].print=_PrintClipWin;
   }

   printf("[%4d][%-12s][type=%2d][total=%3d] <<<\n",
          i,BLOBTABLE[(int)node->any.type].name, 
          node->any.type,node->any.total); 
   if (BLOBTABLE[(int)node->any.type].print) { 
      ptr=(Pointer)node+sizeof(BLOBNODE); 
      (*BLOBTABLE[(int)node->any.type].print)(ptr,node->any.total); 
   }
   return TRUE;
}

static
int _PrintCommand( ptr,tot )
   BLOBTEXT *ptr;
   int tot;
{
   printf("(%2d) <%s>\n",tot,ptr);
   return TRUE;
}

static
int _PrintHeader( ptr,tot )
   BLOBHEADER *ptr;
   int tot;
{
   int i;
   for (i=1;i<=tot;i++) {
      printf("(%2d/%2d) name=<%s>\n",i,tot,ptr->name);
      printf("        version=<%s>\n",ptr->version);
      printf("        date=<%s>\n",ptr->date);
      printf("        m11=%1.2E m12=%1.2E\n",ptr->m11,ptr->m12);
      printf("        m21=%1.2E m22=%1.2E\n",ptr->m21,ptr->m22);
      printf("        m31=%1.2E m32=%1.2E\n",ptr->m31,ptr->m32);
      printf("        reset=%d\n",ptr->reset);
      ptr++;
   }
   return TRUE;
}

static
int _PrintXmtx2DData( ptr,tot )
   BLOB2DMDATA *ptr;
   int tot;
{
   int i;
   for (i=1;i<=tot;i++) {
      printf("(2dmtrx) m11=%1.2E m12=%1.2E\n",ptr->m11,ptr->m12);
      printf("         m21=%1.2E m22=%1.2E\n",ptr->m21,ptr->m22);
      printf("         m31=%1.2E m32=%1.2E\n",ptr->m31,ptr->m32);
      ptr++;
   }
   return TRUE;
}

static
int _PrintXmtx3DData( ptr,tot )
   BLOB3DMDATA *ptr;    
   int tot;
{
   int i;
   for (i=1;i<=tot;i++) {
      printf("(3dmtrx) m11=%1.2E m12=%1.2E m13=%1.2E\n",
              ptr->m11,ptr->m12,ptr->m13);
      printf("         m21=%1.2E m22=%1.2E m23=%1.2E\n",
              ptr->m21,ptr->m22,ptr->m23);
      printf("         m31=%1.2E m32=%1.2E m33=%1.2E\n",
              ptr->m31,ptr->m32,ptr->m33);
      printf("         m41=%1.2E m42=%1.2E m43=%1.2E\n",
              ptr->m41,ptr->m42,ptr->m43);
      ptr++;
   }
   return TRUE;
}

static
int _PrintGC( ptr,tot )
   BLOBGC *ptr;
   int tot;
{
   int i;
   char *p;

   switch (ptr->gc_type) {
   case GE_GCPoint    : p="GE_GCPoint";break;
   case GE_GCLine     : p="GE_GCLine";break;
   case GE_GCPolygonL : p="GE_GCPolygonLine";break;
   case GE_GCPolygon  : p="GE_GCPolygon";break;
   case GE_GCTextL    : p="GE_GCTextLine";break;
   case GE_GCText     : p="GE_GCText";break;
   case GE_GCTotal    : p="GE_GCTotal";break;
   default            : p="GE_GC?";break;
   }
   printf("(gc) gc_type        = %s\n",p);
   printf("     gc_mask        = %d\n",ptr->gc_mask);
   printf("     function       = %d\n",ptr->function);
   printf("     foreground     = %d\n",ptr->foreground);
   printf("     background     = %d\n",ptr->background);
   printf("     line_width     = %d\n",ptr->line_width);
   printf("     line_style     = %d\n",ptr->line_style);
   printf("     cap_style      = %d\n",ptr->cap_style);
   printf("     join_style     = %d\n",ptr->join_style);
   printf("     fill_style     = %d\n",ptr->fill_style);
   printf("     fill_rule      = %d\n",ptr->fill_rule);
   printf("     polyarc_attr   = %d\n",ptr->polyarc_attr);
   printf("     arc_mode       = %d\n",ptr->arc_mode);
   printf("     stipple        = %d\n",ptr->stipple);
   printf("     stipple_width  = %d\n",ptr->stipple_width);
   printf("     stipple_height = %d\n",ptr->stipple_height);
   printf("     font           = %s\n",ptr->font);
   printf("     height         = %d\n",ptr->font_height);
   printf("     width          = %d\n",ptr->font_width);
   printf("     angle          = %d\n",ptr->font_angle);
   printf("     alignment      = %d\n",ptr->text_format);
/* printf("     ts_x_origin    = %d\n",ptr->ts_x_origin); */
/* printf("     ts_y_origin    = %d\n",ptr->ts_y_origin); */
/* printf("     subwindow_mode = %d\n",ptr->subwindow_mode); */
/* printf("     clip_x_origin  = %d\n",ptr->clip_x_origin); */
/* printf("     clip_y_origin  = %d\n",ptr->clip_y_origin); */
   printf("     dash_offset    = %d\n",ptr->dash_offset);
   printf("     dashes         = %d\n",ptr->dashes);
   printf("     dash_list      = (");
      for (i=0;i<ptr->dashes;i++) {
         printf("%d",ptr->dash_list[i]);
         if (i!=ptr->dashes-1) printf(",");
      }
      printf(")\n");
   return TRUE;
}

static
int _PrintPoint( ptr,tot )
   BLOBPOINT *ptr;
   int tot;
{
   int i;
   for (i=1;i<=tot;i++) {
      printf("(%2d/%2d) x=%1.5E y=%1.5E\n",i,tot,ptr->x,ptr->y);
      ptr++;
   }
   return TRUE;
}

static
int _PrintLine( ptr,tot )
   BLOBLINE *ptr;
   int tot;
{
   int i;
   for (i=1;i<=tot;i++) {
      printf("(%2d/%2d) x1=%1.2E y1=%1.2E x2=%1.2E y2=%1.2E\n",
             i,tot,ptr->x1,ptr->y1,ptr->x2,ptr->y2);
      ptr++;
   }
   return TRUE;
}

static
int _PrintArc( ptr,tot )
   BLOBARC *ptr;
   int tot;
{
   int i;
   for (i=1;i<=tot;i++) {
      printf("(%2d/%2d) x=%1.2E y=%1.2E\n",i,tot,ptr->x,ptr->y);
      printf("(%2d/%2d) width=%1.2E height=%1.2E\n",
             i,tot,ptr->width,ptr->height);
      printf("(%2d/%2d) angle1=%1.2E angle2=%1.2E\n",
             i,tot,ptr->angle1,ptr->angle2);
      ptr++;
   }
   return TRUE;
}

static
int _PrintText( ptr,tot )
   BLOBTEXT *ptr;
   int tot;
{
   char *p;
   printf("(x=%1.2e)(y=%1.2e)\n",((BLOBPOINT*)ptr)->x,((BLOBPOINT*)ptr)->y);
   p=(char*)ptr;
   p+=sizeof(BLOBPOINT);
   printf("(%2d) <%s>\n",tot,p);
   return TRUE;
}

static
int _PrintClipWin( ptr,tot )
   BLOBCLIPWIN *ptr;
   int tot;
{
   int i;
   for (i=1;i<=tot;i++) {
      printf("(clip) x1=%1.2E y1=%1.2E x2=%1.2E y2=%1.2E\n",
             ptr->x1,ptr->y1,ptr->x2,ptr->y2);
      ptr++;
   }
   return TRUE;
}

/******************************************************************************/
/* geprint.c */
