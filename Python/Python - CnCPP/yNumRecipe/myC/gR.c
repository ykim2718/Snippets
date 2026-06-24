/******************************************************************************/

#include <stdio.h>

#include "gecore.h"
#include "geplot.h"

/******************************************************************************/

main()
{
   GEDISPLIST *list;

/*
   GEGrSystemOpen(&list,FALSE,"","mosprc4:0.0",(char*)0);
*/
   GEGrSystemOpen(&list,FALSE,"",(char*)0);
   GEPlotProcesser(list);
   GEGrSystemClose();
}

/******************************************************************************/
/* test.c */
