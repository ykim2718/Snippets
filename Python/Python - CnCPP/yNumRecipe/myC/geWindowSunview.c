/********************************************************************/
/*                   module name : geWindowSunview.c                */
/*              descriptive name : sunview grahpic tools            */
/*                   environment : SUN UNIX 4.0.3                   */
/*                      compiler : cc                               */
/*                      producer : kim, yong shik                   */
/*                       version : 1.0                              */
/*                                                                  */
/*                       43240110-43240514                          */
/*                                                                  */
/********************************************************************/
/*****************************k*i*m**********************************/
/************************y*o*n*g*-*s*h*i*k***************************/
/********************************************************************/
/********************************************************************/

#if defined(_SUNVIEW_)
/********************************************************************/
#include <suntool/sunview.h>
#include <suntool/canvas.h>
#include <stdio.h>
#include "myCore.h"
#include "color.h"
#include "geWindowSunview.h"

/********************************************************************/

int SVGrSystemOpen();
int SVGrSystemClose();

int SVDrawPoint(); 
int SVDrawPoints(); 
int SVDrawLine(); 
int SVDrawLines();
int SVDrawArc(); 
int SVDrawArcs(); 
int SVDrawText();
  
int SVGetGeometry(); 
  
int SVSetMouseXY(); 
int SVGetMouseXY(); 
 
int SVGeKeyEvent();

/*==================================================================*/

static int SVPixColor=0,SVPixRasterOp=0;
static int SVScreenX=0,SVScreenY=0,SVScreenW=0,SVScreenH=0;
static int SVWindowX=0,SVWindowY=0,SVWindowW=0,SVWindowH=0;

#define SUNVIEW_SCREEN_WIDTH  1150 /* 1140 */
#define SUNVIEW_SCREEN_HEIGHT 900  /* 875 */

/*--------------------------------------------------------------------
   color,
      0 : black   (rgb=0,0,0)
      1 : red     (rgb=255,0,0)
      2 : green   (rgb=0,255,0)
      3 : blue    (rgb=0,0,255)
      4 : aqua    (rgb=0,255,255)
      5 : magneta (rgb=255,255,0)
      6 : yellow  (rgb=255,0,255)
      7 : white   (rgb=255,255,255)
--------------------------------------------------------------------*/

static short my_icon_image[256]={
#include "shik.icn"
};
mpr_static(sIcIcon,64,64,1,my_icon_image);
static short my_cursor_image[]={
#include "shik.cur"
};
mpr_static(my_cursor,16,16,1,my_cursor_image);

int SVGrSystemOpen()
{
#define MYFRAME    0
#define MYCANVAS   1
#define MYCMS_SIZE 8
static Pixwin *pixwins[2];
static mycms_sizes[2]={2,MYCMS_SIZE};
static char red[MYCMS_SIZE] = {0,255,  0,  0,  0,255,255,255};
static char green[MYCMS_SIZE]={0,  0,255,  0,255,  0,255,255};
static char blue[MYCMS_SIZE] ={0,  0,  0,255,255,255,  0,255};

   Inputmask SVim;

   SVpixfont=
   pf_open("/usr/lib/fonts/fixedwidthfonts/screen.b.16");
   if (SVpixfont==NULL) {
      printf("sunview font error !\n");
      exit(1);
   }
   SVicon=icon_create(ICON_IMAGE,&sIcIcon,0);

   SVframe=window_create(
           NULL,FRAME,
           FRAME_LABEL,SYSVERTXT,
           FRAME_ICON,SVicon,
           WIN_WIDTH,SUNVIEW_SCREEN_WIDTH,
           WIN_HEIGHT,SUNVIEW_SCREEN_HEIGHT,
           WIN_X,0,WIN_Y,0,
           WIN_ERROR_MSG,"\nMOSPDT,7988]\n",
           0 );

   SVcanvas=window_create(
            SVframe,CANVAS,
            WIN_CURSOR,cursor_create(CURSOR_IMAGE,&my_cursor,0),
            0 );

   SVScreenX=0;
   SVScreenY=0;
   SVScreenW=(int)window_get(SVcanvas,CANVAS_WIDTH);
   SVScreenH=(int)window_get(SVcanvas,CANVAS_HEIGHT);
   pixwins[MYFRAME]=(Pixwin*)window_get(SVframe,WIN_PIXWIN);
   SVpixwin=pixwins[MYCANVAS]=
	      (Pixwin*)canvas_pixwin(SVcanvas);
   pw_setcmsname(SVpixwin,"COLOR");
   pw_putcolormap(SVpixwin,0,mycms_sizes[MYCANVAS],red,green,blue);

   SVwinfd=(int)window_get(SVcanvas,WIN_FD);

   input_imnull(&SVim);
   SVim.im_flags|=IM_ASCII;
   win_set_kbd_mask(SVwinfd,SVim);

/*
   window_main_loop(SVframe);
   SVGrSystemClose();
*/
}

int SVGrSystemClose()
{
   /* window_done(SVframe); */
   exit(0);
}

int SVDrawPoint( x,y )
   int x,y;
{
   pw_vector(SVpixwin,x,y,x,y,SVPixRasterOp,SVPixColor);
}

int SVDrawPoints()
{
}

int SVDrawLine( x1,y1,x2,y2 )
   int x1,y1,x2,y2;
{
/*---c-l-i-p-p-i-n-g---*/
/*---c-l-i-p-p-i-n-g---*/

   pw_vector(SVpixwin,x1,y1,x2,y2,SVPixRasterOp,SVPixColor);
}

int SVDrawLines()
{
}

int SVDrawArc()
{
}

int SVDrawArcs()
{
}

int SVDrawText( x,y,str )
   int x,y;
   char *str;
{
/*---c-l-i-p-p-i-n-g---*/
/*---c-l-i-p-p-i-n-g---*/

   pw_ttext(SVpixwin,
   x,y,SVPixRasterOp|PIX_COLOR(SVPixColor),SVpixfont,(str));
}

int SVGetGeometry( x,y,w,h )
   int *x,*y,*w,*h;
{
   *x=SVWindowX;
   *y=SVWindowY;
   if (!SVWindowW & !SVWindowH) {
      SVWindowW=1140;
      SVWindowH=875;
   }
   *w=SVWindowW;
   *h=SVWindowH;
}

int SVSetMouseXY( x,y )
   int x,y;
{
   window_set(SVframe,WIN_MOUSE_XY,(x)+5,(y)+5,0);
}

int SVGetMouseXY()
{
}

int SVGetKeyEvent()
{
   Event SVevent;

R: input_readevent(SVwinfd,&SVevent);
   if (!event_is_ascii(&SVevent)) goto R;
   return (int)SVevent.ie_code;
}

/********************************************************************/
#endif /* geWindowSunview.c */
