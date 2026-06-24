/******************************************************************************/
/*                                                                            */
/*                                                                            */
/*   grapher,(c)shik,mospdt,43250325                                          */
/*   941002                                                                   */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include "myCore.h"
#include "gecore.h"
#include "geplot.h"
#include "plot.h"

/******************************************************************************/

main(argc,argv) 
   int argc;
   char *argv[];
{ 
   char version[40];
   GEDISPLIST *DispList;
   GERECT data;
   int i;

   char command[32];

   sprintf(version,"%s,%s",GRCoreName,__VERSION__);
   echo(" **** %s,mospdt(c)shik **** \n",version); 
   setSigHandle();
   grapherPlotOpen(&PlotList,argv[1],0);
   grapherPlotProcess(PlotList);
   grapherPlot2BLOB(PlotList);
   grapherPlot2File(PlotList);

/*-g.c------------------------------------------------------------------------*/
/*-gS.c-----------------------------------------------------------------------*/
   i=SetPlotCommand(command,GE_PlotOpen,0);
   BLAddCommand(PlotList->glob.blob,command,i);
   AnyMovDLObject(PlotList->glob.blob,
                  PlotList->glob.blob->tail,
                  PlotList->glob.blob->head);

   i=SetPlotCommand(command,GE_PlotClose,0);
   BLAddCommand(PlotList->glob.blob,command,i);

   i=SetPlotCommand(command,GE_PlotPrint,'p');
   BLAddCommand(PlotList->glob.blob,command,i);
   AnyMovDLObject(PlotList->glob.blob,
                  PlotList->glob.blob->tail,
                  PlotList->glob.blob->head);

   GEPlotCommander("",PlotList->glob.blob);
   echo("\n");
/*----------------------------------------------------------------------------*/
   grapherPlotClose(PlotList);
}

/******************************************************************************/
