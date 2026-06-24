/******************************************************************************/
/*                          file name : gewindow.h                            */
/*                   descriptive name : Graphic Engine WINDOW Module          */
/*                           compiler : unix cc                               */
/*                           producer : Kim,YongShik                          */
/*                            version : 1.0                                   */
/*                                                                            */
/*                            43240327-43250218                               */
/*                            43251210-43251215                               */
/*                            43271028-43271028                               */
/*                            43271028-43280222                               */
/*                                uncomplete                                  */
/*                                                                            */
/******************************************************************************/
#ifndef gewindow_header_INSTALLED
#define gewindow_header_INSTALLED 1
/******************************************************************************/

#include "myCore.h"

/*     
 *  x,y           *    x1,y1
 *    +------+ w  *  0,0 +------+ >
 *    | rect |    *      | rect |
 *    +------+    *      +------+  
 *   h            *      v    x2,y2
 */
typedef struct {
   int x,y,w,h;
} RECTSIZE;

typedef struct _PIXRECT {
   char     *data; /* image buffer data */
   RECTSIZE  size;
} PIXRECT;

typedef struct _RECTNODE {
   struct _RECTNODE *next;
   PIXRECT  *xrss; /* HIDDEN,VISIBLE */
   RECTSIZE  size;
} RECTNODE;
typedef struct _RECTLIST {
   RECTNODE *head,*tail; /* should be kept ! */
} RECTLIST;

#define GEWINLIST struct _GEWINLIST

typedef struct _GEWINATTR {
   int id;
   char *name;
   int foreground,background,border;
} GEWINATTR;

typedef struct _GEWINDOW {
   struct _GEWINDOW  *next,*prev; /* should be kept ! */
   GEWINATTR *attr;
   PIXRECT   *rect;
   RECTLIST  *list;
/*
   IPTRFN     operation;
   struct _GEWINDOW  *parent;
   GEWINLIST *childs;
*/
} GEWINDOW; 

GEWINLIST {
   GEWINDOW *head,*tail;
};

/*----------------------------------------------------------------------------*/

typedef enum {
   GE_WINBack,GE_WINMove,GE_WINFrnt,GE_WINHide,GE_WINShow,GE_WINKill,GE_WINZoom
} GEWINACTIONTYPE;

#define GEDynWinMove(list,win,x,y)     GEMoveDynWin(list,win,(x),(y),GE_WINMove)
#define GEDynWinBack(list,win)         GEMoveDynWin(list,win,0,0,GE_WINBack)
#define GEDwinFrnt(list,win)           GEMoveDynWin(list,win,0,0,GE_WINFrnt)
#define GEDynWinHide(list,win)         GEMoveDynWin(list,win,0,0,GE_WINHide)
#define GEDynWinShow(list,win)         GEMoveDynWin(list,win,0,0,GE_WINShow)
#define GEDynWinKill(list,win)         GEMoveDynWin(list,win,0,0,GE_WINKill)
#define GEDynWinZoom(list,win,x,y,w,h) GEZoomDynWin(list,win,(x),(y),(w),(h))

/******************************************************************************/

int GEOpenDynWinSys    _(( ));
int GECloseDynWinSys   _(( ));

int GEMoveDynWin       _(( ));
int GEZoomDynWin       _(( ));

int GEAlloDynWinTop     _(( int x,int y,int w,int h ));
int GEFreeDynWinTop     _(( GEWINDOW *win ));
int GESetDynWinAttrs    _(( ));

int GEOpenSimpleWin   _(( int x,int y,int w,int h ));
int GECloseSimpleWin  _(( int x,int y,int w,int h ));

GEWINDOW *GEFindDynWinFrXY    _(( ));

int GEWriteDynWin    _(( ));
int GEWriteDynWinColor  _(( ));
int GEWriteDynWinBorder _(( ));
int GEWriteDynWinText   _(( ));

int GEMyWinDemo();

/******************************************************************************/
#endif /* gewindow.h */
