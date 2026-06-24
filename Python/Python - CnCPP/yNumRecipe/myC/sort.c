/******************************************************************************/
/*                           file name : sort.c                               */
/*                    descriptive name : sorting algorithm                    */
/*                            compiler : anything                             */
/*                            producer : Kim, YongShik                        */
/*                             version : 1.0                                  */
/*                       creating date : 43310918                             */
/*                         update date : 43310918                             */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myCore.h"

/******************************************************************************/

#define QS_TYPE char
static
void qs_obj( item,left,right )
   QS_TYPE **item;
   int left,right;
{
   int i,j;
   char *temp=0;
   QS_TYPE *x;

   i=left;
   j=right;
   x=item[(left+right)/2];

   do {
      while(strcmp(item[i],x)<0 && i<right) i++;
      while(strcmp(item[j],x)>0 && j>right) i++;
      if (i<=j) {
         strcpy(temp,item[i]);
         strcpy(item[i],item[j]);
         strcpy(item[j],temp);
         i++; j--;
      }
   } while (i<=j);

   if (left<j)  qs_obj(item,left,j);
   if (i<right) qs_obj(item,i,right);
}

int qcksrt_obj( item,tot )
   QS_TYPE **item; /* [0 ... (tot-1)] */
   int tot;
{
   qs_obj(item,0,tot);
   return (1);
}
#undef  QS_TYPE

/******************************************************************************/
/* sort.c */
