/******************************************************************************/
/*                          file name : geWindowMy.c                          */
/*                   descriptive name : Graphic Engine WINDOW Module          */
/*                           compiler : cc                                    */
/*                           producer : Kim,YongShik                          */
/*                            version : 1.0                                   */
/*                                                                            */
/*                            43240327-43250218                               */
/*                            43251210-43251215                               */
/*                            43271028-43280222                               */
/*                            under construction                              */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include "myCore.h"
#include "tools.h"
#include "any.h"
#include "gecore.h"
#include "geWindowMy.h"

/******************************************************************************/

static char *AlloBuffer();
static int FreeBuffer();

static int x_buf2buf();
static int x_buf2can();
static int x_can2buf();

static int allo_rectlist();
static int free_rectlist();
static int add_rectnode();
static int del_rectnode();
static int ger_rectnode();
static int new_rectnode();
static int mul_rectnode();
static int xid_rectnode();

static int fnd_crossrect();
static int get_crossrect();

static int make_crossrect_list();
static int dele_crossrect_list();
static int show_crossrect_list();
static int swap_crossrect_list();

       int GEOpenDynWinSys();
       int GECloseDynWinSys();

static int show_DynWindow();
static int swap_DynWindow();
static int allo_DynWindow();
static int free_DynWindow();

       int mm_box();
       int GEMoveDynWin();
       int GEZoomDynWin();

       int GEAlloDynWinTop();
       int GEFreeDynWinTop();
       int GESetDynWinAttrs();

static int win_on();
static int win_off();

       int GEOpenSimpleWin();
       int GECloseSimpleWin();

       GEWINDOW *GEFindDynWinFrXY();

       int GEWriteDynWin();
       int GEWriteDynWinColor();
       int GEWriteDynWinBorder();
       int GEWriteDynWinText();

       int GEMyWinDemo();

/******************************************************************************/

typedef enum {on,mm,off} mmboxattr;

/*----------------------------------------------------------------------------*/

#define size_x1(s) ((s).x)
#define size_y1(s) ((s).y)
#define size_x2(s) (size_x1(s)+(s).w-1)
#define size_y2(s) (size_y1(s)+(s).h-1)

#define rect_data(r) ((r)->data)
#define rect_size(r) ((r)->size)
 
/*----------------------------------------------------------------------------*/
 
#define rn_xrss(rn) ((rn)->xrss)
#define rn_size(rn) ((rn)->size)
#define rn_x(rn)    ((rn)->size.x)
#define rn_y(rn)    ((rn)->size.y)
#define rn_w(rn)    ((rn)->size.w)
#define rn_h(rn)    ((rn)->size.h)

/*----------------------------------------------------------------------------*/

#define GEWinAttr(win)     ((win)->attr)
#define GEWinRect(win)     ((win)->rect)
#define GEWinData(win)     ((win)->rect->data)
#define GEWinSize(win)     ((win)->rect->size)

#define GEWinId(win)       (GEWinAttr(win)->id)
#define GEWinName(win)     (GEWinAttr(win)->name)
#define GEWinFgColor(win)  (GEWinAttr(win)->fgcolor)
#define GEWinBgColor(win)  (GEWinAttr(win)->bgcolor)
#define GEWinBdColor(win)  (GEWinAttr(win)->bdcolor)

#define GEWinSizeX(win)    (GEWinSize(win).x)
#define GEWinSizeY(win)    (GEWinSize(win).y)
#define GEWinSizeW(win)    (GEWinSize(win).w)
#define GEWinSizeH(win)    (GEWinSize(win).h)
#define GEWinSizeX1(win)   (size_x1(GEWinSize(win)))
#define GEWinSizeY1(win)   (size_y1(GEWinSize(win)))
#define GEWinSizeX2(win)   (size_x2(GEWinSize(win)))
#define GEWinSizeY2(win)   (size_y2(GEWinSize(win)))

/*----------------------------------------------------------------------------*/

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
#define is_c1in(under,over) ((size_x1(under)<=size_x1(over)) ? \
                             (size_x1(over)<=size_x2(under)) ? \
                             (size_y1(under)<=size_y1(over)) ? \
                             (size_y1(over)<=size_y2(under)) ? \
                             1:0:0:0:0)
#define is_c2in(under,over) ((size_x1(under)<=size_x2(over)) ? \
                             (size_x2(over)<=size_x2(under)) ? \
                             (size_y1(under)<=size_y1(over)) ? \
                             (size_y1(over)<=size_y2(under)) ? \
                             1:0:0:0:0)
#define is_c3in(under,over) ((size_x1(under)<=size_x2(over)) ? \
                             (size_x2(over)<=size_x2(under)) ? \
                             (size_y1(under)<=size_y2(over)) ? \
                             (size_y2(over)<=size_y2(under)) ? \
                             1:0:0:0:0)
#define is_c4in(under,over) ((size_x1(under)<=size_x1(over)) ? \
                             (size_x1(over)<=size_x2(under)) ? \
                             (size_y1(under)<=size_y2(over)) ? \
                             (size_y2(over)<=size_y2(under)) ? \
                             1:0:0:0:0)
#define is_c5in(under,over) ((size_x1(over)<size_x1(under)) ? \
                             (size_y1(over)<size_y1(under)) ? \
                             (size_x2(under)<size_x2(over)) ? \
                             (size_y2(under)<size_y2(over)) ? \
                             1:0:0:0:0)
#define is_e1in(under,over) ((size_x1(under)<=size_x1(over)) ? \
                             (size_x1(over)<=size_x2(under)) ? \
                             (size_y1(over)<=size_y1(under)) ? \
                             (size_y2(under)<=size_y2(over)) ? \
                             1:0:0:0:0)
#define is_e2in(under,over) ((size_y1(under)<=size_y1(over)) ? \
                             (size_y1(over)<=size_y2(under)) ? \
                             (size_x1(over)<=size_x1(under)) ? \
                             (size_x2(under)<=size_x2(over)) ? \
                             1:0:0:0:0)
#define is_e3in(under,over) ((size_x1(under)<=size_x2(over)) ? \
                             (size_x2(over)<=size_x2(under)) ? \
                             (size_y1(over)<=size_y1(under)) ? \
                             (size_y2(under)<=size_y2(over)) ? \
                             1:0:0:0:0)
#define is_e4in(under,over) ((size_y1(under)<=size_y2(over)) ? \
                             (size_y2(over)<=size_y2(under)) ? \
                             (size_x1(over)<=size_x1(under)) ? \
                             (size_x2(under)<=size_x2(over)) ? \
                             1:0:0:0:0)

/*----------------------------------------------------------------------------*/

static MYDISPNODE *NODE=NULL;
static char *BUFFER=NULL; 

/******************************************************************************/
/**********************************k*i*m***************************************/
/*****************************y*o*n*g*-*s*i*c**********************************/
/******************************************************************************/

static
char *AlloBuffer( width,height )
   int width,height;
{
   char *image;

   GEAlloImage(NODE,width,height,&image);
   return image;
}

static
int FreeBuffer( image )
   char *image;
{
   GEFreeImage(image);
   return TRUE;
}

static
int x_buf2buf( ssize,sbuffer,dsize,dbuffer,xsize )
   char *sbuffer,*dbuffer;
   RECTSIZE ssize,dsize,xsize;
{
   int sx,sy,dx,dy; /* offset */

   sx=xsize.x-ssize.x;
   sy=xsize.y-ssize.y;
   dx=xsize.x-dsize.x;
   dy=xsize.y-dsize.y;
   GECpyImage(sbuffer,dbuffer,sx,sy,dx,dy,xsize.w,xsize.h);
   return TRUE;
}

static
int x_buf2can( bsize,buffer,xsize )
   char *buffer;
   RECTSIZE bsize,xsize;
{
   int bx,by; /* offset */

   bx=xsize.x-bsize.x;
   by=xsize.y-bsize.y;
   GEPutImage(NODE,buffer,bx,by,xsize.x,xsize.y,xsize.w,xsize.h);
   return TRUE;
}

static
int x_can2buf( bsize,buffer,xsize )
   char *buffer;
   RECTSIZE bsize,xsize;
{
   int bx,by; /* offset */

   bx=xsize.x-bsize.x;
   by=xsize.y-bsize.y;
   GEGetImage(NODE,buffer,xsize.x,xsize.y,bx,by,xsize.w,xsize.h);
   return TRUE;
}

static
int allo_rectlist( list )
   RECTLIST **list;
{
   AnyOpenLinkedObject(list,sizeof(RECTLIST));
   return TRUE;
}

static
int delete_rectnode( node )
   RECTNODE *node;
{
   free(node);
   return TRUE;
}

static
int free_rectlist( list )
   RECTLIST *list;
{
   AnyCloseLinkedObject(list,delete_rectnode);
   return TRUE;
}

static
int add_rectnode( list,rn )
   RECTLIST *list;
   RECTNODE *rn;
{
   if (list->head) {
      list->tail->next = rn;
      while (rn->next)
         rn = rn->next;
      list->tail = rn;
      list->tail->next = NULL;
   } else {
      list->head = rn;
      while (rn->next)
         rn = rn->next;
      list->tail = rn;
   }
   return TRUE;
}

static
int del_rectnode( list,rn )
   RECTLIST *list;
   RECTNODE *rn;
{
   RECTNODE *prern=list->head;

   if (rn==prern) {
      free(rn);
      if (rn->next) {
         list->head = rn->next;
         return TRUE;
      } else {
         list->head = list->tail = NULL;
         return TRUE;
      }  
   }   
   while (rn!=prern->next)
      prern = prern->next;
   prern->next = rn->next;
   if (!prern->next) list->tail = prern;
   free(rn);
   return TRUE;
}

static
int ger_rectnode ( list,win,nextwin )
   RECTLIST *list;
   GEWINDOW *win,*nextwin;
{
   int xid,poss=FALSE;
   RECTNODE *rn,*mrn;

   rn=list->head;
   do {
      if (rn_xrss(rn)) continue; 
      else             poss=TRUE;
      xid=xid_rectnode(rn,nextwin);
      if (xid) {
         mul_rectnode(rn_size(rn),nextwin,xid,&mrn);
         add_rectnode(list,mrn);
         del_rectnode(list,rn);
      } 
   } while (rn=rn->next); 
   return poss;
}

static 
int xid_rectnode( rn,cross )
   RECTNODE *rn;
   GEWINDOW  *cross;
{
   register int xid=~(~0);

   if (is_c1in(rn_size(rn),GEWinSize(cross)))
      xid |= 0x0001; 
   if (is_c2in(rn_size(rn),GEWinSize(cross)))
      xid |= 0x0010; 
   if (is_c3in(rn_size(rn),GEWinSize(cross)))
      xid |= 0x0100; 
   if (is_c4in(rn_size(rn),GEWinSize(cross)))
      xid |= 0x1000; 
   if (xid) {
      switch (xid) {
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
      if (is_e1in(rn_size(rn),GEWinSize(cross)))
         xid |= 0x0001; 
      if (is_e2in(rn_size(rn),GEWinSize(cross)))
         xid |= 0x0010; 
      if (is_e3in(rn_size(rn),GEWinSize(cross)))
         xid |= 0x0100; 
      if (is_e4in(rn_size(rn),GEWinSize(cross)))
         xid |= 0x1000; 
      if (is_c5in(rn_size(rn),GEWinSize(cross)))
         return XID66;
      switch (xid) {
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
int new_rectnode( n,headrn )
  int n;
  RECTNODE **headrn;
{
  register int i;
  RECTNODE *rn,*prern;

  *headrn=prern=salloc(RECTNODE,1);
  for (i=2;i<=n;i++) {
     rn=salloc(RECTNODE,1);
     prern=prern->next=rn;
  }
  prern->next=NULL;
  return TRUE;
}

static
int mul_rectnode( object,cross,xid,mrn )
   RECTSIZE object;
   GEWINDOW  *cross;
   int xid;
   RECTNODE **mrn;
{
   register int ax1,ay1,ax2,ay2,
                bx1,by1,bx2,by2;
   RECTNODE *n;

  /*
   *  ax1,ay1 |       bx1,by1
   *     +----+----+     +------+
   *     | 23 | 12 |     |      | 
   *   --+----+----+--   |      | 
   *     | 34 | 41 |     +------+
   *     +----+----+         bx2,by2
   *          | ax2,ay2
   */
   ax1 = size_x1(object);
   ay1 = size_y1(object);
   ax2 = size_x2(object);
   ay2 = size_y2(object);
   bx1 = GEWinSizeX1(cross);
   by1 = GEWinSizeY1(cross);
   bx2 = GEWinSizeX2(cross);
   by2 = GEWinSizeY2(cross);
 
   switch (xid) {
      case XID11 : new_rectnode( 4,mrn );
                   n = *mrn;
                   rn_x(n)= bx1;
                   rn_y(n)= by1;
                   rn_w(n)= ax2-bx1+1;
                   rn_h(n)= GEWinSizeH(cross);
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by2+1;
                   rn_w(n)= object.w;
                   rn_h(n)= ay2-by2;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by1;
                   rn_w(n)= bx1-ax1;
                   rn_h(n)= GEWinSizeH(cross);
                   rn_xrss(n)= NULL;  
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= object.w;
                   rn_h(n)= by1-ay1;
                   rn_xrss(n)= NULL;
                   return XID11;
      case XID22 : new_rectnode( 4,mrn );
                   n = *mrn;
                   rn_x(n)= bx1;
                   rn_y(n)= by1;
                   rn_w(n)= GEWinSizeW(cross);
                   rn_h(n)= ay2-by1+1;
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by1;
                   rn_w(n)= bx1-ax1;
                   rn_h(n)= ay2-by1+1;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= bx2+1;
                   rn_y(n)= by1;
                   rn_w(n)= ax2-bx2;
                   rn_h(n)= ay2-by1+1;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= object.w;
                   rn_h(n)= by1-ay1;
                   rn_xrss(n)= NULL;
                   return XID22;
      case XID33 : new_rectnode( 4,mrn );
                   n = *mrn;
                   rn_x(n)= ax1;
                   rn_y(n)= by1;
                   rn_w(n)= bx2-ax1+1;
                   rn_h(n)= GEWinSizeH(cross);
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by2+1;
                   rn_w(n)= object.w;
                   rn_h(n)= ay2-by2;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= bx2+1;
                   rn_y(n)= by1;
                   rn_w(n)= ax2-bx2;
                   rn_h(n)= GEWinSizeH(cross);
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= object.w;
                   rn_h(n)= by1-ay1;
                   rn_xrss(n)= NULL;
                   return XID33;
      case XID44 : new_rectnode( 4,mrn );
                   n = *mrn;
                   rn_x(n)= bx1;
                   rn_y(n)= ay1;
                   rn_w(n)= GEWinSizeW(cross);
                   rn_h(n)= by2-ay1+1;
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by2+1;
                   rn_w(n)= object.w;
                   rn_h(n)= ay2-by2;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= bx1-ax1;
                   rn_h(n)= by2-ay1+1;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= bx2+1;
                   rn_y(n)= ay1;
                   rn_w(n)= ax2-bx2;
                   rn_h(n)= by2-ay1+1;
                   rn_xrss(n)= NULL;
                   return XID44;
      case XID10 : new_rectnode( 2,mrn );
                   n = *mrn;
                   rn_x(n)= bx1;
                   rn_y(n)= ay1;
                   rn_w(n)= ax2-bx1+1;
                   rn_h(n)= object.h;
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= bx1-ax1;
                   rn_h(n)= object.h;
                   rn_xrss(n)= NULL;
                   return XID10;
      case XID20 : new_rectnode( 2,mrn );
                   n = *mrn; 
                   rn_x(n)= ax1; 
                   rn_y(n)= by1; 
                   rn_w(n)= object.w; 
                   rn_h(n)= ay2-by1+1; 
                   rn_xrss(n)= GEWinRect(cross); 
                   n = n->next; 
                   rn_x(n)= ax1; 
                   rn_y(n)= ay1; 
                   rn_w(n)= object.w; 
                   rn_h(n)= by1-ay1; 
                   rn_xrss(n)= NULL;
                   return XID20;
      case XID30 : new_rectnode( 2,mrn );
                   n = *mrn;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= bx2-ax1+1;
                   rn_h(n)= object.h;
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next; 
                   rn_x(n)= bx2+1;
                   rn_y(n)= ay1;
                   rn_w(n)= ax2-bx2;
                   rn_h(n)= object.h;
                   rn_xrss(n)= NULL;
                   return XID30;
      case XID40 : new_rectnode( 2,mrn );
                   n = *mrn; 
                   rn_x(n)= ax1; 
                   rn_y(n)= ay1; 
                   rn_w(n)= object.w; 
                   rn_h(n)= by2-ay1+1; 
                   rn_xrss(n)= GEWinRect(cross); 
                   n = n->next; 
                   rn_x(n)= ax1; 
                   rn_y(n)= by2+1; 
                   rn_w(n)= object.w; 
                   rn_h(n)= ay2-by2; 
                   rn_xrss(n)= NULL;
                   return XID40;
      case XID55 : new_rectnode( 5,mrn );
                   n = *mrn;
                   rn_x(n)= bx1;
                   rn_y(n)= by1;
                   rn_w(n)= GEWinSizeW(cross);
                   rn_h(n)= GEWinSizeH(cross);
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by2+1;
                   rn_w(n)= object.w;
                   rn_h(n)= ay2-by2;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)=ax1;
                   rn_y(n)= by1;
                   rn_w(n)= bx1-ax1;
                   rn_h(n)= GEWinSizeH(cross);
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= bx2+1;
                   rn_y(n)= by1;
                   rn_w(n)= ax2-bx2;
                   rn_h(n)= GEWinSizeH(cross);
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= object.w;
                   rn_h(n)= by1-ay1;
                   rn_xrss(n)= NULL;
                   return XID55;
      case XID66 : new_rectnode( 1,mrn );
                   n = *mrn;
                   rn_x(n)= object.x;
                   rn_y(n)= object.y;
                   rn_w(n)= object.w;
                   rn_h(n)= object.h;
                   rn_xrss(n)= GEWinRect(cross);
                   return XID66;
      case XID12 : new_rectnode( 3,mrn );
                   n = *mrn;
                   rn_x(n)= bx1;
                   rn_y(n)= by1;
                   rn_w(n)= ax2-bx1+1;
                   rn_h(n)= ay2-by1+1;
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by1;
                   rn_w(n)= bx1-ax1;
                   rn_h(n)= ay2-by1+1;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= object.w;
                   rn_h(n)= by1-ay1;
                   rn_xrss(n)= NULL;
                   return XID12;
      case XID23 : new_rectnode( 3,mrn );
                   n = *mrn;
                   rn_x(n)= ax1;
                   rn_y(n)= by1;
                   rn_w(n)= bx2-ax1+1;
                   rn_h(n)= ay2-by1+1;
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= bx2+1;
                   rn_y(n)= by1;
                   rn_w(n)= ax2-bx2;
                   rn_h(n)= ay2-by1+1;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= object.w;
                   rn_h(n)= by1-ay1;
                   rn_xrss(n)= NULL;
                   return XID23;
      case XID34 : new_rectnode( 3,mrn );
                   n = *mrn;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= bx2-ax1+1;
                   rn_h(n)= by2-ay1+1;
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by2+1;
                   rn_w(n)= object.w;
                   rn_h(n)= ay2-by2;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= bx2+1;
                   rn_y(n)= ay1;
                   rn_w(n)= ax2-bx2;
                   rn_h(n)= by2-ay1+1;
                   rn_xrss(n)= NULL;
                   return XID34;
      case XID41 : new_rectnode( 3,mrn );
                   n = *mrn;
                   rn_x(n)= bx1;
                   rn_y(n)= ay1;
                   rn_w(n)= ax2-bx1+1;
                   rn_h(n)= by2-ay1+1;
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by2+1;
                   rn_w(n)= object.w;
                   rn_h(n)= ay2-by2;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= bx1-ax1;
                   rn_h(n)= by2-ay1+1;
                   rn_xrss(n)= NULL;
                   return XID41;
      case XID77 : new_rectnode( 3,mrn );
                   n = *mrn;
                   rn_x(n)= bx1;
                   rn_y(n)= ay1;
                   rn_w(n)= GEWinSizeW(cross);
                   rn_h(n)= object.h;
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= bx1-ax1;
                   rn_h(n)= object.h;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= bx2+1;
                   rn_y(n)= ay1;
                   rn_w(n)= ax2-bx2;
                   rn_h(n)= object.h;
                   rn_xrss(n)= NULL;
                   return XID77;
      case XID88 : new_rectnode( 3,mrn );
                   n = *mrn;
                   rn_x(n)= ax1;
                   rn_y(n)= by1;
                   rn_w(n)= object.w;
                   rn_h(n)= GEWinSizeH(cross);
                   rn_xrss(n)= GEWinRect(cross);
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= by2+1;
                   rn_w(n)= object.w;
                   rn_h(n)= ay2-by2;
                   rn_xrss(n)= NULL;
                   n = n->next;
                   rn_x(n)= ax1;
                   rn_y(n)= ay1;
                   rn_w(n)= object.w;
                   rn_h(n)= by1-ay1;
                   rn_xrss(n)= NULL;
                   return XID88;
      default    : return XID00;
   }                
   return TRUE;
}

static 
int make_crossrect_list( win,list )
   GEWINDOW *win;
   RECTLIST *list;
{
   GEWINDOW *nextwin=win->next;
   RECTNODE *rn;
   register int poss;

   new_rectnode(1,&rn);
   rn_xrss(rn)=NULL;
   rn_size(rn)=GEWinSize(win); 
   add_rectnode(list,rn);
   
   while (nextwin) {
      poss=ger_rectnode(list,win,nextwin);
      if (!poss) return;
      nextwin=nextwin->next;
   }
   return TRUE;
}

static 
int show_crossrect_list( win,list )
   GEWINDOW *win;
   RECTLIST *list;
{
   RECTNODE *rn=list->head;
   PIXRECT   *cross;
   char  *buf;

   while (rn) {
      if (cross=rn_xrss(rn)) {
         buf=AlloBuffer(rn_w(rn),rn_h(rn));
         x_can2buf(rn_size(rn),buf,rn_size(rn));
         x_buf2can(rect_size(cross),rect_data(cross),
                   rn_size(rn));
         x_buf2buf(GEWinSize(win),GEWinData(win),
                   rect_size(cross),rect_data(cross),
                   rn_size(rn));
         x_buf2buf(rn_size(rn),buf,
                   GEWinSize(win),GEWinData(win),
                   rn_size(rn));
         FreeBuffer(buf);
      }
      rn=rn->next;
   }
   return TRUE;
}

static 
int swap_crossrect_list( win,list )
   GEWINDOW *win;  
   RECTLIST *list;
{
   RECTNODE *rn=list->head;
   PIXRECT   *cross;
   char  *buf;

   while (rn) {
      buf=AlloBuffer(rn_w(rn),rn_h(rn));
      if (cross=rn_xrss(rn)) {
         x_buf2buf(rect_size(cross),rect_data(cross),
                   rn_size(rn),buf,
                   rn_size(rn));
         x_buf2buf(GEWinSize(win),GEWinData(win),
                   rect_size(cross),rect_data(cross),
                   rn_size(rn));
      } else {
         x_can2buf(rn_size(rn),buf,rn_size(rn));
         x_buf2can(GEWinSize(win),GEWinData(win),
                   rn_size(rn));
      }
      x_buf2buf(rn_size(rn),buf,
                GEWinSize(win),GEWinData(win),
                rn_size(rn));
      FreeBuffer(buf);
      rn=rn->next;
   }
   return TRUE;
}

int GEOpenDynWinSys( list )
   GEWINLIST **list;
{
   AnyOpenLinkedObject(list,sizeof(GEWINLIST));
   return TRUE;
}

static GEWINLIST *list_for_delete;
static
int delete_winnode( node )
   GEWINDOW *node;
{
   GEMoveDynWin(list_for_delete,node,0,0,GE_WINKill);
   return TRUE;
}

int GECloseDynWinSys( list )
   GEWINLIST *list;
{
   list_for_delete=list;
   AnyCloseLinkedObject(list,delete_winnode);
   list_for_delete=0;
   return TRUE;
}

static
int show_DynWindow( win )
   GEWINDOW *win;
{
   RECTLIST *list;

   allo_rectlist( &list );
   make_crossrect_list( win,list );
   show_crossrect_list( win,list );
   free_rectlist( list );
   return TRUE;
}

static
int swap_DynWindow( win )
   GEWINDOW *win;
{
   RECTLIST *list;

   allo_rectlist( &list );
   make_crossrect_list( win,list );
   swap_crossrect_list( win,list );
   free_rectlist( list );
   return TRUE;
}

static
int allo_DynWindow( win )
   GEWINDOW **win;
{
   (*win)=salloc(GEWINDOW,1);
   (*win)->attr=salloc(GEWINATTR,1);
   (*win)->rect=salloc(PIXRECT,1);
   (*win)->rect->data=salloc(char,1);
   return TRUE;
}

static
int free_DynWindow( win )
   GEWINDOW *win;
{
   FreeBuffer(GEWinData(win));
   free(GEWinRect(win));
   if (GEWinName(win)) free(GEWinName(win));
   free(GEWinAttr(win));
   free(win);
   return TRUE;
}

int mm_box( rect,attr )
   RECTSIZE  rect;
   mmboxattr attr;
{
   static RECTSIZE oldr;

/*
   GESetPixRastOp(CPY_PIXOP);
   GESetPixColor(BLACK);
*/
   switch (attr) {
      case on  : printf("x1=%d y1=%d x2=%d y2=%d\n",
                          size_x1(rect),size_y1(rect),
                          size_x2(rect),size_y2(rect));
                 oldr=rect;
                 break;
      case mm  : printf("x1=%d y1=%d x2=%d y2=%d\n",
                          size_x1(oldr),size_y1(oldr),
                          size_x2(oldr),size_y2(oldr));
/*
                 put_pixrect(size_x1(rect),size_y1(rect),
                           size_x2(rect),size_y2(rect));
*/
                 oldr=rect;
                 break;
      case off : printf("x1=%d y1=%d x2=%d y2=%d\n",
                          size_x1(oldr),size_y1(oldr),
                          size_x2(oldr),size_y2(oldr));
                 oldr.x=oldr.y=oldr.w=oldr.h=0;
   }
   return TRUE;
}

int GEMoveDynWin( list,win,x,y,type ) 
   GEWINLIST *list;
   GEWINDOW *win;
   int x,y;
   GEWINACTIONTYPE type;
{
   if (!win) {
      fprintf(stderr,"Error, no more window in GEMoveDynWin()\n");
      exit(1);
   }
   switch (type) {
      case GE_WINMove : 
            swap_DynWindow(win);
            GEWinSizeX(win)=(x);
            GEWinSizeY(win)=(y);
            swap_DynWindow(win);
            break;
      case GE_WINBack : 
            swap_DynWindow(win);
            AnyMovDLObject(list,win,list->head);
            swap_DynWindow(win);
            break;
      case GE_WINFrnt : 
            show_DynWindow(win);
            AnyMovDLObject(list,win,NULL);
            break;
      case GE_WINHide : 
      case GE_WINShow : 
            swap_DynWindow(win);
            break;
      case GE_WINKill :
            swap_DynWindow(win);
            delAnyDLObject(list,win); 
            free_DynWindow(win);
   }
   return TRUE;
}

int GEZoomDynWin( list,win,x,y,w,h )
   GEWINLIST *list;
   GEWINDOW *win;
   int x,y,w,h;
{
   RECTLIST *rlist;

/*
   GEMoveDynWin(list,win,0,0,GE_WINFrnt);

   GEAlloDynWinTop(list,x,y,w,h);
   allo_rectlist(&rlist);
   make_crossrect_list(win,rlist);
   swap_crossrect_list(win,rlist);

   GESetDynWinAttrs(list->tail,GEWinId(win),GEWinName(win),
                  GEWinFgColor(win),GEWinBgColor(win),GEWinBdColor(win));
   mm_box(GE_WINZOOM,GEWinSize(win),GEWinSize(list->tail));
   GEWriteDynWin(list->tail);

   free_rectlist(rlist);
   delAnyDLObject(list,win);
   free_DynWindow(win);
*/
   return TRUE;
}

int GEAlloDynWinTop( list,x,y,w,h )
   GEWINLIST *list;
   int x,y,w,h;
{
   GERECT data;
   GEWINDOW *win;

   GEGetGeometry(NODE,&data);
   if (data.width<(x+w-1))
      w=data.width-x+1;
   if (data.height<(y+h-1))
      h=data.height-y+1;
   allo_DynWindow(&win);
   GEWinSizeX(win)=x;
   GEWinSizeY(win)=y;
   GEWinSizeW(win)=w;
   GEWinSizeH(win)=h;
   win_on(x,y,w,h);
   GEWinData(win)=BUFFER;
   AddAnyDLObject(list,win);
   GESetDynWinAttrs(win,0,NULL,"magenta","black","white");
   return TRUE;
}

int GEFreeDynWinTop( list,win )
   GEWINLIST *list;
   GEWINDOW *win;
{
   if (!win) {
      printf("no more win in FREE_TOP_GEWINDOW !\n");
      exit(1);
   }
   GEPutImage(NODE,GEWinData(win),0,0,GEWinSizeX(win),GEWinSizeY(win),
              GEWinSizeW(win),GEWinSizeH(win));
   delAnyDLObject(list,win); 
   free_DynWindow(win);
   return TRUE;
}

int GESetDynWinAttrs( win,id,name,foreground,background,border )
   GEWINDOW *win;
   int id;
   char *name,*foreground,*background,*border;
{
   GEWinId(win)=id;
   GEWinName(win)=(name)?strdpl(name):NULL;
   win->attr->foreground=GEgetColorValue(foreground);
   win->attr->background=GEgetColorValue(background);
   win->attr->border=GEgetColorValue(border);
   return TRUE;
}

static
int win_on( x,y,w,h )
   int x,y,w,h;
{
   BUFFER=AlloBuffer(w,h);
   GEGetImage(NODE,BUFFER,x,y,0,0,w,h);
   return TRUE;
}

static
int win_off( x,y,w,h )
   int x,y,w,h;
{
   if (!BUFFER) {
      printf("no more win in WIN_OFF !\n");
      exit(1);
   }
   GEPutImage(NODE,BUFFER,0,0,x,y,w,h);
   FreeBuffer(BUFFER);
   BUFFER=NULL;
   return TRUE;
}

static char *SimpleWinBUFFER;

int GEOpenSimpleWin( x,y,w,h )
   int x,y,w,h;
{
   SimpleWinBUFFER=AlloBuffer(w,h);
   /* write_pixrect_color(x,y,w,h,2); */
   GEGetImage(NODE,SimpleWinBUFFER,x,y,0,0,w,h);
   return TRUE;
}

int GECloseSimpleWin( x,y,w,h )
   int x,y,w,h;
{
   if (!SimpleWinBUFFER) {
      printf("Error, no more window in GECloseSimpleWin()\n");
      exit(1);
   }
   GEPutImage(NODE,SimpleWinBUFFER,0,0,x,y,w,h);
   FreeBuffer(SimpleWinBUFFER);
   SimpleWinBUFFER=NULL;
   return TRUE;
}

GEWINDOW *GEFindDynWinFrXY( list,x,y )
   GEWINLIST *list;
   int x,y;
{
   GEWINDOW *win=list->tail;

   while (win) {
      if (GEWinSizeX(win)<=x
      &&  x<GEWinSizeX(win)+GEWinSizeW(win)
      &&  GEWinSizeY(win)<=y
      &&  y<GEWinSizeY(win)+GEWinSizeH(win)) {
         return win;
      }
      win=win->prev;
   }
   return (GEWINDOW*)NULL;
}

int GEWriteDynWin( win )
   GEWINDOW *win;
{
   GEWriteDynWinColor(win);
   GEWriteDynWinBorder(win);
   return TRUE;
}

int GEWriteDynWinColor( win )
   GEWINDOW *win;
{
   register int x,y,w,h;
   BLOBGC gc;

   x=GEWinSizeX(win); x++;
   y=GEWinSizeY(win); y++;
   w=GEWinSizeW(win); w--;w--;
   h=GEWinSizeH(win); h--;h--;
   gc.gc_type=GE_GCPolyFill;
   gc.gc_mask=GE_GCMaskForeground;
   gc.foreground=win->attr->background;
   GEChangeGC(NODE,&gc);
   XFillRectangle(NODE->display,NODE->window,NODE->gc[MX_GCPolyFill],x,y,w,h);
   XFlush(NODE->display);
   return TRUE;
}

int GEWriteDynWinBorder( win )
   GEWINDOW *win;
{
   register int x,y,w,h;
   BLOBGC gc;

   x=GEWinSizeX(win); x++;
   y=GEWinSizeY(win); y++;
   w=GEWinSizeW(win); w--;w--;
   h=GEWinSizeH(win); h--;h--;
   gc.gc_type=GE_GCPolyLine;
   gc.gc_mask=GE_GCMaskForeground;
   gc.foreground=win->attr->border;
   GEChangeGC(NODE,&gc);
   XDrawRectangle(NODE->display,NODE->window,NODE->gc[MX_GCPolyLine],x,y,w,h);
   XFlush(NODE->display);
   return TRUE;
}

int GEWriteDynWinText( win,text,color )
   GEWINDOW *win;
   char *text;
   int color;
{
   return TRUE;
}

int GEMyWinDemo( display_node )
   MYDISPNODE *display_node;
{
   char *c;
   int flag;
   char str[80];
   GEWINLIST *list;

printf("Now in GEMyWinDemo() ...\n");
   NODE=display_node;
   GEOpenDynWinSys(&list);

#define SLEEP sleep(0)
 
   GEAlloDynWinTop(list,50,100,300,300);
   GESetDynWinAttrs(list->tail,0,"shik","white","black","red");
   GEWriteDynWin(list->tail);
   SLEEP;
   GEAlloDynWinTop(list,100,200,300,300);
   GESetDynWinAttrs(list->tail,0,NULL,"red","blue","yellow");
   GEWriteDynWin(list->tail);
   SLEEP;
   GEAlloDynWinTop(list,150,300,300,300);
   GESetDynWinAttrs(list->tail,0,NULL,"green","red","yellow");
   GEWriteDynWin(list->tail);
   SLEEP;
   GEAlloDynWinTop(list,120,350,800,100);
   GESetDynWinAttrs(list->tail,0,NULL,"red","magenta","yellow");
   GEWriteDynWin(list->tail);
   SLEEP;
   GEAlloDynWinTop(list,200,250,400,300);
   GESetDynWinAttrs(list->tail,0,NULL,"magenta","yellow","red");
   GEWriteDynWin(list->tail);
   SLEEP;
   GEDynWinZoom(list,list->tail,200,250,100,100);  
   SLEEP;
   GEDynWinHide(list,list->tail->prev->prev);
   SLEEP;
   GEDynWinShow(list,list->tail->prev->prev);
   SLEEP;
   GEDynWinKill(list,list->head);
   SLEEP;
   GEDynWinKill(list,list->head);
   SLEEP;
   GEDynWinKill(list,list->head);
   SLEEP;
   GEDynWinKill(list,list->head);
   SLEEP;
   GEDynWinKill(list,list->head);

   GECloseDynWinSys(list);
   return TRUE;
}

/******************************************************************************/
/* geWindowMy.c */
