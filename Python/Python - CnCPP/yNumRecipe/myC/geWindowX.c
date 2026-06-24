/******************************************************************************/
/*                                                                            */
/*                           file name : geWindowX.c                          */
/*                    descriptive name : xwindow grahpic tools                */
/*                         environment : OpenWindow3.0/Motif1.1               */
/*                            compiler : cc                                   */
/*                            producer : Kim,YongShik                         */
/*                       creating date : 43260107-43260120,0507               */
/*                         update date : 19941027                             */
/*                         update date : 43290417                             */
/*                         update date : 43300831                             */
/*                         update date : 43310117,0125                        */
/*                         update date : 43320224                             */
/*                                                                            */
/******************************************************************************/

#if defined(_XnMOTIF_)
/******************************************************************************/

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <varargs.h>
#include "myCore.h"
#include "any.h"
#include "blob.h"
#include "str.h"
#include "gecore.h"
#include "gewindow.h"

static MYDISPLIST *myGrDisplayList=0;

static unsigned long myColor();
static unsigned long myRGB();
static int myCmpHostName();
static int myDelDispNode();

/******************************************************************************/

#ifndef NonConvex
#define NonConvex Nonconvex
#endif

/******************************************************************************/


int myGetRGBbyName( name,switchBW,red,green,blue )
   int switchBW; /* boolean */
   float *red,*green,*blue; /* 0 ... 1 : intensity */
{
   MYDISPNODE *node;
   XColor px,exact;
   int maxColor=65535;

   if (!myGrDisplayList
   ||  !myGrDisplayList->head) {
      errExit("DISPLAYLIST is not ready .. in RGBbyName()");
   }
   node=myGrDisplayList->head;
   if (!XAllocNamedColor(node->display,node->colormap,name,&px,&exact)) {
      fprintf(stderr,"Error, ... \"%s\" ... in RGBbyName()\n",name);
      exit(1);
   }
   if (px.red>=maxColor&&px.green>=maxColor&&px.blue>=maxColor)
      px.red=px.green=px.blue=0;
   else if (!px.red&&!px.green&&!px.blue)
      px.red=px.green=px.blue=maxColor;
   *red=(float)px.red/(float)maxColor;
   *green=(float)px.green/(float)maxColor;
   *blue=(float)px.blue/(float)maxColor;
   return 1;
}

static
unsigned long myColor( node,name )
   MYDISPNODE *node;
   char *name;
{
   XColor px,exact;

   if (!XAllocNamedColor(node->display,node->colormap,name,&px,&exact)) {
      fprintf(stderr,"Error, ... \"%s\" ... in myColor()\n",name);
      exit(1);
   }
   return px.pixel;
/*
   XColor px,exact;

   if (!XLookupColor(node->display,node->colormap,name,&px,&exact)) {
      fprintf(stderr,"Error, ... \"%s\" ... in myColor()\n",name);
      exit(1);
   }
   return px.pixel;
*/
/*
   XColor exact;

   if (!XParseColor(node->display,node->colormap,name,&exact)) {
      fprintf(stderr,"Error, ... \"%s\" ... in myColor()\n",name);
      exit(1);
   }
   return exact.pixel;
*/
}

static
unsigned long myRGB( node,red,green,blue )
   MYDISPNODE *node;
   unsigned short red,green,blue;
{
   XColor px;

   px.red=red<<8;
   px.green=green<<8;
   px.blue=blue<<8;
   XAllocColor(node->display,node->colormap,&px);
   return px.pixel;
}

static
char *target=NULL;

static
int myCmpHostName( node )
   MYDISPNODE *node;
{
   if (target) {
      if (strequ(node->hostname,target))
         return TRUE;
      else
         return FALSE;
   } else
      return FALSE;
}

static
int myDelDispNode( node )
   MYDISPNODE *node;
{
   free(node->hostname);
   XDestroyWindow(node->display,node->window);
}

/*
   {
   XSetWindowAttributes a;
   a.override_redirect=1;
   XChangeWindowAttributes(MYDisplay,MYParent,CWOverrideRedirect,&a);
   }
*/
 
int myGrSystemOpen( va_alist )
   va_dcl
{
   int argc;
   char **argv;
   MYDISPLIST *list,**addr;
   MYDISPNODE *node;
   va_list ap;
   char *p,i;
   XGCValues values;
   BLOBGC gc;
   int screen,depth;
   unsigned long valuemask;
   XSetWindowAttributes xswa;
   XVisualInfo vinfo_ret;
   MYGEOMETRY data;

   openAnyDLObject(&list,sizeof(MYDISPLIST));

   va_start(ap);
   addr=va_arg(ap,MYDISPLIST **);
   *addr=list;
   while (p=va_arg(ap,char *)) {
      node=(MYDISPNODE*)malloc(sizeof(MYDISPNODE));
      node->hostname=(*p) ? strdpl(p):strdpl("");
      AddAnyDLObject(list,node);
   }
   va_end(ap);

   GESetGCDefault(gc);
   xswa.backing_store=1;
   valuemask=CWBackingStore;

   node=(MYDISPNODE*)list->head;
   while (node) {
      node->display=XOpenDisplay(node->hostname);
      if (!node->display)
         errExit("Display Environment ... in MY_GrSystemOpen()");
      screen=DefaultScreen(node->display);
      depth=DefaultDepth(node->display,screen);
      node->window=XCreateWindow(node->display,RootWindow(node->display,0),
                                 0,0,1,1,0,depth,
                                 InputOutput,CopyFromParent,
                                 valuemask,&xswa);
      if (!XMatchVisualInfo(node->display,screen,depth,PseudoColor,
                            &vinfo_ret))
         errExit("Error, ... in MY_GrSystemOpen()");
      node->colormap=XDefaultColormap(node->display,0);
      MY_AlloGC(node);
      XSetWindowBackground(node->display,node->window,myColor(node,"black"));
      MY_GetGeometry(node,&data); 
      node->backing_store=XCreatePixmap(node->display,node->window,
                                        data.width,data.height,data.depth);
      node=node->next;
   }
   myGrDisplayList=list;
}

int myGrSystemClose( list )
   MYDISPLIST *list;
{
   MYDISPNODE *node;

   for (node=list->head;
        node;
        node=node->next) {
      myDelDispNode(node);
      delAnyDLObject(list,node);
   }
   myGrDisplayList=0;
   exit(0);
}

int myAlloGC( node )
   MYDISPNODE *node;
{
   BLOBGC gc;
   Font font;

   node->gc[GE_GCPoint ]=XCreateGC(node->display,node->window,0,0);
   node->gc[GE_GCSoleLine]=XCreateGC(node->display,node->window,0,0);
   node->gc[GE_GCPolyLine]=XCreateGC(node->display,node->window,0,0);
   node->gc[GE_GCPolyFill]=XCreateGC(node->display,node->window,0,0);
   node->gc[GE_GCTextLine]=XCreateGC(node->display,node->window,0,0);
   node->gc[GE_GCTextFill]=XCreateGC(node->display,node->window,0,0);

   GESetGCDefault(gc);

   gc.gc_type=GE_GCPoint;
   gc.gc_mask=GE_GCMaskLineDefault;
   myChangeGC(node,&gc);
   font=XLoadFont(node->display,"-*-courier-bold-r-*--*-120-*-*-*-*-iso8859-1");
   XSetFont(node->display,node->gc[GE_GCPoint ],font);

   gc.gc_type=GE_GCPoint;
   gc.gc_mask=GE_GCMaskLineDefault;
   myChangeGC(node,&gc);
   gc.gc_type=GE_GCSoleLine;
   gc.gc_mask=GE_GCMaskLineDefault;
   myChangeGC(node,&gc);
   gc.gc_type=GE_GCPolyLine;
   gc.gc_mask=GE_GCMaskLineDefault;
   myChangeGC(node,&gc);
   gc.gc_type=GE_GCPolyFill;
   gc.gc_mask=GE_GCMaskFillDefault;
   myChangeGC(node,&gc);
   gc.gc_type=GE_GCTextLine;
   gc.gc_mask=GE_GCMaskLineDefault;
   myChangeGC(node,&gc);
   gc.gc_type=GE_GCTextFill;
   gc.gc_mask=GE_GCMaskFillDefault;
   myChangeGC(node,&gc);
}

int myFreeGC( node )
   MYDISPNODE *node;
{
   XFreeGC(node->display,node->gc[GE_GCPoint ]);
   XFreeGC(node->display,node->gc[GE_GCSoleLine]);
   XFreeGC(node->display,node->gc[GE_GCPolyLine]);
   XFreeGC(node->display,node->gc[GE_GCPolyFill]);
   XFreeGC(node->display,node->gc[GE_GCTextLine]);
   XFreeGC(node->display,node->gc[GE_GCTextFill]);
}

int myChangeGC( node,gc )
   MYDISPNODE *node;
   BLOBGC *gc;
{
   unsigned long valuemask;
   XGCValues values;

   if (!gc->gc_mask) return;
   valuemask=0L;

   if (gc->gc_mask&GE_GCMaskFunction) {
      valuemask|=GCFunction;
      switch (gc->function) {
         case GE_FnClear        : values.function=GXclear;       break;
         case GE_FnAnd          : values.function=GXand;         break;
         case GE_FnAndReverse   : values.function=GXandReverse;  break;
         case GE_FnCopy         : values.function=GXcopy;        break;
         case GE_FnAndInverted  : values.function=GXandInverted; break;
         case GE_FnNoOp         : values.function=GXnoop;        break;
         case GE_FnXor          : values.function=GXxor;         break;
         case GE_FnOr           : values.function=GXor;          break;
         case GE_FnNor          : values.function=GXnor;         break;
         case GE_FnEquiv        : values.function=GXequiv;       break;
         case GE_FnInvert       : values.function=GXinvert;      break;
         case GE_FnOrReverse    : values.function=GXorReverse;   break;
         case GE_FnCopyInverted : values.function=GXcopyInverted;break;
         case GE_FnOrInverted   : values.function=GXorInverted;  break;
         case GE_FnNand         : values.function=GXnand;        break;
         case GE_FnSet          : values.function=GXset;         break;
      }
   }
   if (gc->gc_mask&GE_GCMaskPlaneMask) {
      ;
   }
   if (gc->gc_mask&GE_GCMaskForeground) {
      valuemask|=GCForeground;
      values.foreground=myColor(node,GEgetColorName(gc->foreground));
   }
   if (gc->gc_mask&GE_GCMaskBackground) {
      valuemask|=GCBackground;
      values.background=myColor(node,GEgetColorName(gc->background));
   }
   if (gc->gc_mask&GE_GCMaskLineWidth) {
      valuemask|=GCLineWidth;
      values.line_width=gc->line_width;
   }
   if (gc->gc_mask&GE_GCMaskLineStyle) {
      valuemask|=GCLineStyle;
      switch (gc->line_style) {
         case GE_LineSolid      : values.line_style=LineSolid;     break;
         case GE_LineOnOffDash  : values.line_style=LineOnOffDash; break;
         case GE_LineDoubleDash : values.line_style=LineDoubleDash;break;
      }
   }
   if (gc->gc_mask&GE_GCMaskCapStyle) {
      valuemask|=GCCapStyle;
      switch (gc->cap_style) {
         case GE_CapNotLast    : values.cap_style=CapNotLast;   break;
         case GE_CapButt       : values.cap_style=CapButt;      break;
         case GE_CapRound      : values.cap_style=CapRound;     break;
         case GE_CapProjecting : values.cap_style=CapProjecting;break;
      }
   }
   if (gc->gc_mask&GE_GCMaskJoinStyle) {
      valuemask|=GCJoinStyle;
      switch (gc->join_style) {
         case GE_JoinMiter : values.join_style=JoinMiter;break;
         case GE_JoinRound : values.join_style=JoinRound;break;
         case GE_JoinBevel : values.join_style=JoinBevel;break;
      }
   }
   if (gc->gc_mask&GE_GCMaskFillStyle) {
      valuemask|=GCFillStyle;
      switch (gc->fill_style) {
         case GE_FillSolid         : values.fill_style=FillSolid;         break;
         case GE_FillOpaqueStippled: values.fill_style=FillOpaqueStippled;break;
         case GE_FillStippled      : values.fill_style=FillStippled;      break;
         case GE_FillTiled         : values.fill_style=FillTiled;         break;
      }
   }
   if (gc->gc_mask&GE_GCMaskFillRule) {
      valuemask|=GCFillRule;
      switch (gc->fill_rule) {
         case GE_FillEvenOdd : values.fill_rule=EvenOddRule;break;
         case GE_FillWinding : values.fill_rule=WindingRule;break;
      }
   }
   if (gc->gc_mask&GE_GCMaskArcMode) {
      valuemask|=GCArcMode;
      switch (gc->arc_mode) {
         case GE_ArcPieSlice : values.arc_mode=ArcPieSlice;break;
         case GE_ArcChord    : values.arc_mode=ArcChord;   break;
      }
   }
   if (gc->gc_mask&GE_GCMaskTile) {
      if (gc->stipple) {
         /* valuemask|=GCTile; */
         errExit("\"GE_GCMaskTile\" in myChangeGC()");
      }
   }
   if (gc->gc_mask&GE_GCMaskStipple) {
      if (gc->stipple) {
         valuemask|=GCStipple;
         values.stipple=XCreateBitmapFromData(
                        node->display,node->window,
                        GEgetMyStipple8x8(gc->stipple),
                        gc->stipple_width,gc->stipple_height);
         node->etc.stipple_width=gc->stipple_width;
         node->etc.stipple_height=gc->stipple_height;
      }
   }
   if (gc->gc_mask&GE_GCMaskTileStipXOrigin) {
      valuemask|=GCTileStipXOrigin;
      values.ts_x_origin=gc->ts_x_origin;
   }
   if (gc->gc_mask&GE_GCMaskTileStipYOrigin) {
      valuemask|=GCTileStipYOrigin;
      values.ts_y_origin=gc->ts_y_origin;
   }
   if (gc->gc_mask&GE_GCMaskFont) {
      /* valuemask|=GCFont; */
   }
   if (gc->gc_mask&GE_GCMaskSubwindowMode) {
      /* valuemask|=GCSubwindowMode; */
   }
   if (gc->gc_mask&GE_GCMaskGraphicsExposures) {
      /* valuemask|=GCGraphicsExposures; */
   }
   if (gc->gc_mask&GE_GCMaskClipXOrigin) {
      /* valuemask|=GCClipXOrigin; */
      errExit("\"GE_GCMaskClipXOrigin\" in myChangeGC()");
   }
   if (gc->gc_mask&GE_GCMaskClipYOrigin) {
      /* valuemask|=GCClipYOrigin; */
      errExit("\"GE_GCMaskClipYOrigin\" in myChangeGC()");
   }
   if (gc->gc_mask&GE_GCMaskClipMask) {
      /* valuemask|=GCClipMask; */
      errExit("\"GE_GCMaskClipMask\" in myChangeGC()");
   }
   if (gc->gc_mask&GE_GCMaskDashOffset) {
      valuemask|=GCDashOffset;
      values.dash_offset=gc->dash_offset;
   }
   if (gc->gc_mask&GE_GCMaskDashes) {
      /* valuemask|=GCDashes; */
      if (gc->dashes)
         XSetDashes(node->display,node->gc[gc->gc_type],
                    gc->dash_offset,gc->dash_list,gc->dashes);

   }
   XChangeGC(node->display,node->gc[gc->gc_type],valuemask,&values); 

   if (gc->gc_mask&GE_GCMaskStipple) {
      if (gc->stipple)
         node->etc.polyarc_attr=gc->polyarc_attr;
      else
         node->etc.polyarc_attr=GE_PolyArcLine;
   }
   switch (gc->poly_shape) {
      case GE_PolyConvex    : node->etc.poly_shape=Convex;   break;
      case GE_PolyNonConvex : node->etc.poly_shape=NonConvex;break;
      case GE_PolyComplex   : node->etc.poly_shape=Complex;  break;
   }
}

int myDrawPoint( node,ptr,tot )
   MYDISPNODE *node;
   XPoint *ptr;
   int tot;
{
   if (tot==1)
      XDrawPoint(node->display,node->window,node->gc[GE_GCPoint],
                 ptr->x,ptr->y);
   else 
      XDrawPoints(node->display,node->window,node->gc[GE_GCPoint],
                  ptr,tot,CoordModeOrigin);
   XFlush(node->display);
}

int myDrawLine( node,ptr,tot )
   MYDISPNODE *node;
   XSegment *ptr;
   int tot;
{
   if (tot==1)
      XDrawLine(node->display,node->window,node->gc[GE_GCSoleLine],
                ptr->x1,ptr->y1,ptr->x2,ptr->y2);
   else
      XDrawSegments(node->display,node->window,node->gc[GE_GCSoleLine],
                    ptr,tot);
   XFlush(node->display);
}

int myDrawPoly( node,ptr,tot )
   MYDISPNODE *node;
   XPoint *ptr;
   int tot;
{
   if (node->etc.polyarc_attr==GE_PolyArcFill
   ||  node->etc.polyarc_attr==GE_PolyArcBoth)
      XFillPolygon(node->display,node->window,node->gc[GE_GCPolyFill],
                   ptr,tot,node->etc.poly_shape,CoordModeOrigin);
   if (node->etc.polyarc_attr==GE_PolyArcLine
   ||  node->etc.polyarc_attr==GE_PolyArcBoth)
      XDrawLines(node->display,node->window,node->gc[GE_GCPolyLine],
                 ptr,tot,CoordModeOrigin);
   XFlush(node->display);
}

int myDrawArc( node,ptr,tot )
   MYDISPNODE *node;
   XArc *ptr;
   int tot;
{
   if (tot==1) {
      if (node->etc.polyarc_attr==GE_PolyArcFill
      ||  node->etc.polyarc_attr==GE_PolyArcBoth) {
         XFillArc(node->display,node->window,node->gc[GE_GCPolyFill],
                  ptr->x,ptr->y,ptr->width,ptr->height,
                  ptr->angle1,ptr->angle2);
      }
      if (node->etc.polyarc_attr==GE_PolyArcLine
      ||  node->etc.polyarc_attr==GE_PolyArcBoth)
         XDrawArc(node->display,node->window,node->gc[GE_GCPolyLine],
                  ptr->x,ptr->y,ptr->width,ptr->height,
                  ptr->angle1,ptr->angle2);
   } else {
      if (node->etc.polyarc_attr==GE_PolyArcFill
      ||  node->etc.polyarc_attr==GE_PolyArcBoth)
         XFillArcs(node->display,node->window,node->gc[GE_GCPolyFill],ptr,tot);
      if (node->etc.polyarc_attr==GE_PolyArcLine
      ||  node->etc.polyarc_attr==GE_PolyArcBoth)
         XDrawArcs(node->display,node->window,node->gc[GE_GCPolyLine],ptr,tot);
   }
   XFlush(node->display);
}

int myDrawText( node,ptr,tot )
   MYDISPNODE *node;
   XPoint *ptr; 
   int tot;
{
   XFillPolygon(node->display,node->window,node->gc[GE_GCTextFill],
                ptr,tot,node->etc.poly_shape,CoordModeOrigin);
   XFlush(node->display);
}

int myDrawTextLine( node,ptr,tot )
   MYDISPNODE *node;
   GELINE *ptr;
   int tot;
{
   if (tot==1)
      XDrawLine(node->display,node->window,node->gc[GE_GCTextLine],
                ptr->x1,ptr->y1,ptr->x2,ptr->y2);
   else
      XDrawSegments(node->display,node->window,node->gc[GE_GCTextLine],
                    ptr,tot);
   XFlush(node->display);
}

int myClipWin( node,ptr,tot )
   MYDISPNODE *node;
   XPoint *ptr; 
   int tot;
{
   XRectangle rect; 

   rect.x=ptr[0].x;
   rect.y=ptr[0].y;
   rect.width=(unsigned short)(ptr[1].x-rect.x+1);
   rect.height=(unsigned short)(ptr[1].y-rect.y+1);
   XSetClipRectangles(node->display,node->gc[GE_GCPoint],
                      0,0,&rect,1,Unsorted);
   XCopyGC(node->display,node->gc[GE_GCPoint],
           (GCClipMask|GCClipXOrigin|GCClipYOrigin),node->gc[GE_GCSoleLine]);
   XCopyGC(node->display,node->gc[GE_GCPoint],
           (GCClipMask|GCClipXOrigin|GCClipYOrigin),node->gc[GE_GCPolyLine]);
   XCopyGC(node->display,node->gc[GE_GCPoint],
           (GCClipMask|GCClipXOrigin|GCClipYOrigin),node->gc[GE_GCPolyFill]);
   XCopyGC(node->display,node->gc[GE_GCPoint],
           (GCClipMask|GCClipXOrigin|GCClipYOrigin),node->gc[GE_GCTextLine]);
   XCopyGC(node->display,node->gc[GE_GCPoint],
           (GCClipMask|GCClipXOrigin|GCClipYOrigin),node->gc[GE_GCTextFill]);
}

int myGetGeometry( node,data )
   MYDISPNODE *node;
   MYGEOMETRY *data;
{
   Window root;
   int x,y;
   unsigned int width,height;
   unsigned int border_width,depth;
   Status status;

   status=XGetGeometry(node->display,node->window,
                       &root,&x,&y,&width,&height,&border_width,&depth);
   if (!status)
      return 0;
   else {
      data->x=(int)x;
      data->y=(int)y;
      data->width=(unsigned int)width;
      data->height=(unsigned int)height;
      data->border_width=(unsigned int)border_width;
      data->depth=(unsigned int)depth;
      return 1;
   }
}

int myFlush()
{
}

int myWindowShow( node,name,x,y,width,height )
   MYDISPNODE *node;
   char *name;
   int x,y,width,height;
{
   XSizeHints myhint;

   XUnmapWindow(node->display,node->window);
   myhint.flags=PPosition|PSize;
   myhint.x=x;
   myhint.y=y;
   myhint.width=width;
   myhint.height=height;
   XSetStandardProperties(node->display,node->window,
                          name,name,0,0,0,&myhint);
   XMapWindow(node->display,node->window);
   XFlush(node->display);
}

int myWindowHide()
{
}

int myWindowKill()
{
}

int myWindowClear( node )
   MYDISPNODE *node;
{
   XClearWindow(node->display,node->window);
}

int myCopyToBackingStore( node )
   MYDISPNODE *node;
{
   Window root;
   int x,y;
   unsigned int width,height;
   unsigned int border_width,depth;
   Status status;

   MYGEOMETRY data;

   status=XGetGeometry(node->display,node->backing_store,
                       &root,&x,&y,&width,&height,&border_width,&depth);
   myGetGeometry(node,&data);
   if (!status 
   ||  width!=data.width
   ||  height!=data.height
   ||  depth!=data.depth) {
       XFreePixmap(node->display,node->backing_store);
       node->backing_store=XCreatePixmap(node->display,node->window,
                                         data.width,data.height,data.depth);
   }
/*
   fprintf(stdout,"myCopyToBackingStore .....\n");
*/
   XCopyArea(node->display,node->window,node->backing_store,
             node->gc[GE_GCPoint],0,0,data.width,data.height,0,0);
}

int myCopyFromBackingStore( node,event )
   MYDISPNODE *node;
   XEvent *event;
{
/*
   fprintf(stdout,"myCopyFromBackingStore .....\n");
*/
   XCopyArea(node->display,node->backing_store,node->window,
             node->gc[GE_GCPoint],
             event->xgraphicsexpose.x,event->xgraphicsexpose.y,
             event->xgraphicsexpose.width,event->xgraphicsexpose.height,
             event->xgraphicsexpose.x,event->xgraphicsexpose.y);
   while (event->xgraphicsexpose.count) {
      XNextEvent(node->display,event);
      if (event->type==Expose)
         XCopyArea(node->display,node->backing_store,node->window,
                   node->gc[GE_GCPoint],
                   event->xgraphicsexpose.x,event->xgraphicsexpose.y,
                   event->xgraphicsexpose.width,event->xgraphicsexpose.height,
                   event->xgraphicsexpose.x,event->xgraphicsexpose.y);
      else
         break;
   }
}

int MYGEOMETRY( node,data,position )
   MYDISPNODE *node;
   MYGEOMETRY *data;
   char *position;
{
   int flag_mask,x,y,width,height;

   flag_mask=XGeometry(node->display,0,position,"",0,1,1,0,0,
                       &x,&y,&width,&height);
   if (flag_mask&XValue)
      data->x=x;
   if (flag_mask&YValue)
      data->y=y;
   if (flag_mask&WidthValue)
      data->width=width;
   if (flag_mask&HeightValue)
      data->height=height;
}

int myGetKeyEvent( node )
   MYDISPNODE *node;
{
   XEvent event;
   char buffer[32];
   int bufsize=32;
   KeySym key;
   XComposeStatus cs;
   int count;

   XSelectInput(node->display,node->window,KeyPressMask);
L: XNextEvent(node->display,&event);
   if (event.type==KeyPress) {
      count=XLookupString(&event,buffer,bufsize,&key,&cs);
      buffer[count]=0;
      return *buffer;
   } else
      goto L;
}

int myGetMouseEvent()
{
}

int mySetMouseXY( node,x,y )
   MYDISPNODE *node;
   int x,y;
{
   XWarpPointer(node->display,0,node->window,0,0,0,0,x,y);
}

int myAlloImage( node,width,height,image )
   MYDISPNODE *node;
   unsigned int width,height;
   XImage **image;
{
   unsigned int depth;
   int screen,format,bitmap_pad;

   screen=DefaultScreen(node->display);
   depth=DefaultDepth(node->display,screen);
   format=ZPixmap;
   bitmap_pad=(depth>8) ? 32:8;
   *image=XCreateImage(node->display,DefaultVisual(node->display,screen),
                       depth,format,0,0,width,height,bitmap_pad,0);
   if (!*image)
      errExit("XImage allocation failure in myAlloImage()");
   (*image)->data=(char*)malloc((*image)->bytes_per_line*height);
   if (!(*image)->data)
      errExit("XImage data allocation failure in myAlloImage()");
}

int myFreeImage( image )
   XImage *image;
{
   if (image->data) free(image->data);
   XFree(image);
} 

int myGetImage( node,image,src_x,src_y,dst_x,dst_y,width,height )
   MYDISPNODE *node;
   XImage *image;
   int src_x,src_y,dst_x,dst_y;
   unsigned int width,height; 
{
   image=XGetSubImage(node->display,node->window,
                      src_x,src_y,width,height,(unsigned long)-1,ZPixmap,
                      image,dst_x,dst_y);
}

int myPutImage( node,image,src_x,src_y,dst_x,dst_y,width,height )
   MYDISPNODE *node;
   XImage *image;
   int src_x,src_y,dst_x,dst_y;
   unsigned int width,height; 
{
   XPutImage(node->display,node->window,node->gc[GE_GCPoint],image,
             src_x,src_y,dst_x,dst_y,width,height);
}

int myCpyImage( src_image,dst_image,src_x,src_y,dst_x,dst_y,width,height )
   XImage *src_image,*dst_image;
   int src_x,src_y,dst_x,dst_y;
   unsigned int width,height; 
{
   register int i,j;
   unsigned long pixel;

   for (i=0;i<width;i++) {
      for (j=0;j<height;j++) {
         pixel=XGetPixel(src_image,i+src_x,j+src_y);
         if (!XPutPixel(dst_image,i+dst_x,j+dst_y,pixel))
            errExit(" ... in myCpyImage()");
      }
   }
}

int myGetPixel( node,image,x,y,red,green,blue )
/* from IMAGE */
   MYDISPNODE *node;
   XImage *image;
   int x,y;
   unsigned short *red,*green,*blue; 
{
   unsigned long pixel;
   XColor color;

   pixel=XGetPixel(image,x,y);
   color.pixel=pixel;
   XQueryColor(node->display,node->colormap,&color);
   *red=color.red;
   *green=color.green;
   *blue=color.blue;
}

int myPutPixel()
{
}

int myopenDefChildWin( node,win,backColor,x,y,width,height )
   MYDISPNODE *node;
   Window *win;
   char *backColor;
   int x,y;
   unsigned int width,height;
{
   int screen,depth;
   XSetWindowAttributes xswa;
   unsigned long valuemask;

   screen=DefaultScreen(node->display);
   depth=DefaultDepth(node->display,screen);
   xswa.backing_store=1;
   valuemask=CWBackingStore;
   *win=XCreateWindow(node->display,node->window,x,y,width,height,0,depth,
                      InputOutput,CopyFromParent,valuemask,&xswa);
   XSetWindowBackground(node->display,*win,myColor(node,backColor));
   XMapWindow(node->display,*win);
   XFlush(node->display);
}

int mycloseDefChildWin( node,win )
   MYDISPNODE *node;
   Window *win;
{
   XDestroyWindow(node->display,win);
}

/******************************************************************************/
#endif /* geWindowX.c */
