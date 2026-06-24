/******************************************************************************/
/*                                                                            */
/*   grapher,(c)Kim,YongShik                                                  */
/*   43250325,                                                                */
/*   43290122,43290223,                                                       */
/*   43300826                                                                 */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include "myCore.h"
#include "str.h"
#include "tools.h"
#include "gecore.h"
#include "geplot.h"
#include "plot.h"
#include "myWindow.h"

extern int echoToStandardOut;
static int printMessage();

/******************************************************************************/

int main(argc,argv) 
   int argc;
   char *argv[];
{ 
   char *name,*geom;
   int i;

   setSigHandle();
   echoToStandardOut=1;
   geom=NULL;
   name=argv[0];
   for (i=1;i<argc;i++) {
      if (argv[i][0]=='-') {
         switch (argv[i][1]) {
            case 'g' : if (++i>=argc)
                          errExit("-geometry in main()");
                       geom=strdpl(argv[i]);
                       break;
            case 's' : echoToStandardOut=0;
                       break;
            case 'v' : fprintf(stdout,"\n... %s\n\n",GRCoreName);
                       exit(0);
            default  : break;
         }
      }      
   }

   if (!GrapherOpen(&PlotList,name,0)) return FALSE;
   if (!GrapherProcess(PlotList)) return FALSE;
   if (!GrapherPlot2BLOB(PlotList)) return FALSE;
/* GrapherPlot2File(PlotList); */

/*-g.c------------------------------------------------------------------------*/

   // GEPlotWindowViewer(DisplayList->head,PlotList->glob.blob);

   // GEGrSystemClose(DisplayList); 
/*-gS.c-----------------------------------------------------------------------*/
/*
   join_plot_BLOB(PlotList);

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
*/
/*----------------------------------------------------------------------------*/
   // GrapherClose(PlotList);
   return TRUE;
}

/******************************************************************************/
