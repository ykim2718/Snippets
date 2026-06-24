/******************************************************************************/
/*                          file name : geplot.h                              */
/*                   descriptive name : Graphic Engine (BLOB) PLOT Module     */
/*                        environment : X-Window                              */
/*                           compiler : cc                                    */
/*                           producer : Kim,YongShik                          */
/*                            version : 1.0                                   */
/*                                                                            */
/*                            43260812-43260812                               */
/*                                 08/12/93                                   */
/*                                                                            */
/******************************************************************************/

#ifndef geplot_header_INSTALLED
#define geplot_header_INSTALLED 1
/******************************************************************************/
#include "myCore.h"

typedef enum {
   GE_PlotOpen,GE_PlotClose,GE_PlotContinue,GE_PlotClear,
   GE_PlotPrint,GE_PlotExit
} GEPLOTCOMMANDTYPE;

/*----------------------------------------------------------------------------*/

int GEPlotProcesser();      /* for Selection Requestor */
int GEPlotCommander();      /* for Selection Owner */

int SetPlotCommand();
int ChkPlotCommand();

int GEPlotWindowViewer();

/******************************************************************************/
#endif /* geplot.h */
