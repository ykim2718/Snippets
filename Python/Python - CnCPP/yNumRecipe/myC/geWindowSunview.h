/******************************************************************************/
/*                          file name : sunview.h                             */
/*                   descriptive name : sunview grahpic tools                 */
/*                        environment : SUN UNIX 4.0.3                        */
/*                           compiler : cc                                    */
/*                           producer : kim, yong shik                        */
/*                            version : 1.0                                   */
/*                                                                            */
/*                            43230913-43250218                               */
/*                                 05/31/93                                   */
/*                                                                            */
/******************************************************************************/


#if defined(_SUNVIEW_)
#ifndef sunview_header_INSTALLED
#define sunview_header_INSTALLED 1

#include <suntool/sunview.h>
#include <suntool/canvas.h>
#include <stdio.h>
#include "myCore.h"

/******************************************************************************/

Frame    SVframe;
Pixwin  *SVpixwin;
Canvas   SVcanvas;
Icon     SVicon;
Pixfont *SVpixfont;
int     SVwinfd;

/*----------------------------------------------------------------------------*/

extern int SVGrSystemOpen();
extern int SVGrSystemClose();

extern int SVDrawPoint();
extern int SVDrawPoints();
extern int SVDrawLine();
extern int SVDrawLines();
extern int SVDrawArc();
extern int SVDrawArcs();
extern int SVDrawText();
 
extern int SVGetGeometry();
 
extern int SVSetMouseXY();
extern int SVGetMouseXY();
 
extern int SVGeKeyEvent();
 
/******************************************************************************/
#endif /* sunview.h */
#endif

