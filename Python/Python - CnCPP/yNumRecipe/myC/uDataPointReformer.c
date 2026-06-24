/******************************************************************************/

const char *DataPointReformer_Help=
"[Y.Kim]                                                                     \n"
"2003.07.16-07.17                                                            \n"
"2004.02.04                                                                  \n"
"                                                                            \n"
"[Input]                                                                     \n"
"sweep=START,STOP,STEP                                                       \n"
"! X column data is refilled according to stepping valuses.                  \n"
"! Data of other columns are interpolated or extrapolated.                   \n"
"! If total count exceeds or row count of the original, matrix dimension     \n"
"! will be adapted.                                                          \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! Data value is changed by your options.                                    \n"
"! Moreover data row-column dimension can be changed to accommodate to your options. ";

const char *DataPointReformer_Sample=
"type=DataPointReformer                                                      \n"
"sweep=0,1,0.1                                                                ";

/******************************************************************************/

#include <string.h>
#include <math.h>
#include "usrfunc.h"
#include "nrecipe.h"
#include "number.h"
#include "tools.h"
#include "str.h"
#include "semiconductor.h"

extern int Echo();

/******************************************************************************/

int DataPointReformer( ARGUMENTS )
   ARGULIST
{
   char *pAddr,*qDelimiter=",";
   double dStart,dStop,dStep;
   double dX,dY,dError,aX[6],aY[6];
   int nXColIndex,nRHNew,iRow,iCol,nL,nH;
   int nFit,nFitL,nFitH,nPos,nIndex;
   VECTOR vX,vY;

   /* Version */
   Echo(" V.1.1\n");

   /* Check "SWEEP" */
   if (strtokcount(SWEEP,qDelimiter)!=3) {
      Echo(0,"Not enough parameters in <SWEEP=*,*,*>\n");
      return FALSE;
   }
   dStart=atof(pAddr=strtokbyindex(SWEEP,qDelimiter,0));freeEx(pAddr);
   dStop= atof(pAddr=strtokbyindex(SWEEP,qDelimiter,1));freeEx(pAddr);
   dStep= atof(pAddr=strtokbyindex(SWEEP,qDelimiter,2));freeEx(pAddr);
   if (dStart>dStop) { double d=dStop;dStop=dStart;dStart=d; }
   nRHNew=(int)floor((dStop-dStart)/dStep)+1; /* New one */
   Echo(" start,stop,step=%g,%g,%g\n",dStart,dStop,dStep);
   
   /* Check dStart and dStop with data Min and Max. */
   nXColIndex=(*XNO)[0];
   {
   double dMin,dMax;
   MGetMinMaxValue(*MTX,TRUE,nXColIndex,*MRL,*MRH,FALSE,&dMin,&dMax);
   if (dStart<dMin||dStart>dMax||dStop<dMin||dStop>dMax) {
      Echo(0,"START and STOP values are not inside data min. and max.\n"
             "START=%g STOP=%g MIN=%g MAX=%g\n",dStart,dStop,dMin,dMax);
      return FALSE;
   }
   }

   /* Inflate row dimension of matrix if needed */
   if (nRHNew>*MRH) {
      int r,c;
      MInflate(MTX,*MRL,*MRH,*MCL,*MCH,nRHNew,*MCH);
      for (r=*MRH+1;r<=nRHNew;r++) {
         for (c=*MCL;c<=*MCH;c++) {
            MkNaNDouble((*MTX)[r][c]);
         }
      }
      *MRH=nRHNew;
   }

   /* Reforming */
   nFit=noof(aX)-1;
   for (iCol=*MCL;iCol<=*MCH;iCol++) {
      if (iCol==nXColIndex) continue;
      MGetSafeVectorPair(*MTX,TRUE,*MRL,*MRH,nXColIndex,iCol,&vX,&vY,&nL,&nH);
      for (iRow=*MRL;iRow<=nRHNew;iRow++) {
         dX=dStart+(iRow-1)*dStep;
         VGetValueIndexOfMonotonicVector(vX,nL,nH,dX,&nPos);
         //if (nPos<nL||nPos>nH) goto N;
         nFitL=nFitH=nPos;
         while ((nFitH-nFitL+1)<nFit) {
            if (nFitL>nL) nFitL--;
            if (nFitH<nH) nFitH++;
         }
         for (nIndex=nFitL;nIndex<=nFitH;nIndex++) {
            aX[nIndex-nFitL+1]=vX[nIndex];
            aY[nIndex-nFitL+1]=vY[nIndex];
         }
         /* Press,Numerical Receipes in C,p.90 */
         polint(aX,aY,nFit,dX,&dY,&dError);
         (*MTX)[iRow][iCol]=dY;
      }
//N:
      VDestroy(vX,*MRL,*MRH);
      VDestroy(vY,*MRL,*MRH);
   }
   for (iRow=*MRL;iRow<=*MRH;iRow++) {
      (*MTX)[iRow][nXColIndex]=dStart+(iRow-1)*dStep;
   }
   for (iRow=nRHNew+1;iRow<=*MRH;iRow++) {
      MkNaNDouble((*MTX)[iRow][nXColIndex]);
      for (iCol=*MCL;iCol<=*MCH;iCol++) {
         MkNaNDouble((*MTX)[iRow][iCol]);
      }
   }

   return TRUE;
}

/******************************************************************************/
/* DataReformer.c */


