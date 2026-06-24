/******************************************************************************/
/*                           file name : geWindow.h                           */
/*                    descriptive name : ge Window                            */
/*                         environment : OpenWindow3.0/Motif1.1/MSWINDOW      */
/*                            producer : Kim,YongShik                         */
/*                             version : 1.0                                  */
/*                        created date : 43260509-43260509                    */
/*                        updated date : 05/09/93                             */
/*                        updated date : 43290417                             */
/*                        updated date : 43310125                             */
/*                  2ndly-created date : 43320222-43320728                    */
/*                        updated date : 43330127+0222                        */
/*                        updated date : 43360305                             */
/*                                                                            */
/******************************************************************************/

#ifndef geWindow_header_INSTALLED
#define geWindow_header_INSTALLED 1
/******************************************************************************/

#include "myCore.h"
#include "gecore.h"
#include "any.h"

/******************************************************************************/
#if defined(_XnMOTIF_)
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

/*
typedef struct {short x,y;} XPoint;
typedef struct {short x1,y1,x2,y2;} XSegment;
typedef struct {short x,y;unsigned short width,height;short angle1,angle2;} XArc
*/
typedef struct _MYDISPLAY {
   struct _MYDISPLAY *next,*prev;
   char *hostname;
   Display *display;
   Window window;
   Colormap colormap;
   Pixmap backing_store;
   GC gc[6]; /* GE_GCTotal=6 */
   struct {
      int polyarc_attr; /* GE_PolyArcLine,GE_PolyArcFill,GE_PolyArcBoth */
      int poly_shape; /* GE_PolyConvex,GE_PolyNonConvex,GE_PolyComplex */
      int stipple_width;
      int stipple_height;
   } etc;
} MYDISPLAY;

typedef struct _MYDISPLIST {
   struct _MYDISPLAY *head,*tail;
} MYDISPLIST;

/******************************************************************************/
#elif defined(_MSWINDOW_)
#include <time.h>
#include <windows.h>

/* Porting from X to MSWindow */
typedef HWND Window;
typedef HDC GC;
/* end of Porting */

typedef struct _MYDISPLAY {
   struct _MYDISPLAY *next,*prev;
   // char *hostname;       /* not used in MSWin */
   // Display *display;     /* not used in MSWin */
   Window window;
   // Colormap colormap;    /* not used in MSWin */
   // Pixmap backing_store; /* not used in MSWin */
   GC gc[6]; // GE_GCTotal=6
   struct {
      int polyarc_attr; /* GE_PolyArcLine,GE_PolyArcFill,GE_PolyArcBoth */
      int poly_shape; /* GE_PolyConvex,GE_PolyNonConvex,GE_PolyComplex */
      int stipple_width;
      int stipple_height;
   } etc[6];
   float metricScale; /* metricScale = (Phy.Length 1 mm / Logical Length 1.0) */
                      /* Log.Length 100 * metricScale = Phy.Length 100 mm */
} MYDISPLAY;

#else
#error Window type (_XnMOTIF_/_MSWINDOW_/..) must be defined.
#endif
/******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

int GEOpen _((MYDISPLAY **list,char *GC,float metricScale,char* window));
int GEClose _((MYDISPLAY *list));
 
int myAlloGC _((MYDISPLAY*,char*));
int myFreeGC _((MYDISPLAY*));
int myChangeGC _((MYDISPLAY*,BLOBGC*));
int myDrawPoint _((MYDISPLAY*,GEPOINT*,int));
int myDrawLine _((MYDISPLAY*,GELINE*,int));
int myDrawPoly _((MYDISPLAY*,GEPOINT*,int,GERECT*));
int myDrawArc _((MYDISPLAY*,GEARC*,int));
int myDrawText _((MYDISPLAY*,int,int,char*,GERECT*));
int myDrawTextLine _((MYDISPLAY*,GELINE*,int));
int myClipWin();
int myGetGeometry _((MYDISPLAY*,GERECT*));

int myFlush();

int myWindowShow _((MYDISPLAY*,char*,int,int,int,int));
int myWindowHide _((MYDISPLAY*));
int myWindowKill();
int myWindowClear _((MYDISPLAY*));

int myCopyToBackingStore();
int myCopyFromBackingStore();

int myGetKeyEvent();
int myGetMouseEvent();

int myGetMouseXY();
int mySetMouseXY();

int myAlloImage();
int myFreeImage();
int myGetImage();
int myPutImage();
int myGetPixel();
int myPutPixel();

int myCopyBuffer2Buffer();
int myCopyBuffer2Screen();
int myCopyScreen2Buffer();

/*----------------------------------------------------------------------------*/

int GEColorTotal _((
   MYDISPLAY*
   ));
const char* GEColorName _((
   MYDISPLAY*,unsigned long
   ));
const char *GEColorNameByIndex _((
   MYDISPLAY *,int nIndex
   ));
unsigned long GEColorByName _((
   MYDISPLAY*,const char*
   ));
unsigned long GEColorByRGB _((
   MYDISPLAY*,
   unsigned short,unsigned short,unsigned short
   ));
int GEColor2RGB _((
   MYDISPLAY*,unsigned long,
   unsigned short*,unsigned short*,unsigned short*,
   int
   ));

/*----------------------------------------------------------------------------*/

int GEMessageBox _((HWND,char*,unsigned int));

void mySleep _(( clock_t wait ));
void myBeep _(( int frequency, int duration ));

#if defined(__cplusplus)
}
#endif
/******************************************************************************/
#endif /* geWindow.h */

