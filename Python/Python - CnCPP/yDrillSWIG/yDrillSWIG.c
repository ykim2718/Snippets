#include <stdio.h>

int check_array1d( int *arrayb0, int narray, int *result )
{
   printf("(yC) check_array_1d()\n");
   printf("narray=%d\n",narray);
   if (narray>1000) return 0; /* just to avoid infinite loop */
   for (int i=0;i<=narray;i++)
      printf("arrayb0[%d]=%d\n",i,arrayb0[i]);
   printf("*result=%d -->329\n",*result);
   *result=329; /* Python sees changed number. Y, 2016.3.30 */
   return 1;
}

int check_array2d_w_numpy( int *array2d, int nRow, int nCol )
{
   printf("(yC) check_array2d_w_numpy()\n");
   printf("nRow=%d nCol=%d\n",nRow,nCol);
   if (nRow*nCol>1000) return 0;
   for (int i=0;i<nRow;i++)
      for (int j=0;j<nCol;j++) {
         int nIndex=i*nCol+j;
         printf("array2d[%d][%d]=[%d]=%d\n",i,j,nIndex,array2d[nIndex]);
      }
   return nRow*nCol;
}
