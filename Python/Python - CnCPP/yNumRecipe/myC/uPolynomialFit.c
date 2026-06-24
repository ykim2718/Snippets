/******************************************************************************/

const char *PolynomialFit_Help=
"[Y.Kim]                                                                     \n"
"Creation: Too long time ago to remember. Maybe 1995.                        \n"
"Modification: 2003.6.22.                                                    \n"
"                                                                            \n"
"[Input]                                                                     \n"
"option=<i>                                                                  \n"
"! option: Polynomial degree beginning with 1.                               \n"
"xy=(x,y)(x,y)...(x,y)                                                       \n"
"! The first of each parentheses is x, column index.                         \n"
"! The second numbers are y column indexes.                                  \n"
"range=[<d>,<d>|(<d>,<d>)]                                                   \n"
"! The first is lower limit of x for fitting. If *, data minimum.            \n"
"! The second is upper limit of x for fitting. If *, data maximum.           \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! See Log window   ";

const char *PolynomialFit_Sample=
"type=PolynomialFit                                                         \n"
"option=2 xy=(1,2)(1,3)(1,4) ";

/******************************************************************************/

#include <math.h>
#include <string.h>
#include "usrfunc.h"
#include "nrecipe.h"
#include "number.h"
#include "tools.h"
#include "str.h"
#include "semiconductor.h"

extern int Echo();
extern int GetFittingRange(
   VECTOR vX,int nRl,int nRh,int nFitTotal,double dL,double dH,
   int *nL,int *nH
   );

#if !defined(SIGN)
#define SIGN(x)   ((x)>=0 ? 1:-1)
#endif

/******************************************************************************/

int PolynomialFit( ARGUMENTS )
   ARGULIST
{
   int nXyTotal,nXyIndex,nX,nY,nL,nH,j;
   char *pXy,*qDelimiter=",()",*pTok,*pL,*pH;
   double dL,dH,dGoodnessOfFit;
   VECTOR vX,vY,vCoeff;
   int nDataTotal,nFitTotal;

   //Check "OPTION"
   nFitTotal=!NOPTION ? 1:ABS(NOPTION);
   nFitTotal++;

   //Check "XY"
   pXy=strvcat("(",ARGUMENT2,")",0);
   if (chrcount(pXy,'(')!=chrcount(pXy,')')) {
      Echo(0,"Not paired parentheses at the expression of \"Xy=\"\n");
      free(pXy);
      return FALSE;
   }
   strreplace(&pXy,"((","(");
   strreplace(&pXy,"))",")");
   strreplace(&pXy,")(",",");
   strreplace(&pXy,")",",");
   nXyTotal=chrcount(pXy,',');
   if (nXyTotal%2) {
      Echo(0,"Total number is not a muliple of 2 at the expression of \"xy=\"\n");
      free(pXy);
      return FALSE;
   }
   
   //
   nXyTotal>>=1;
   for (nXyIndex=0;nXyIndex<nXyTotal;nXyIndex++) {

      pTok=strtokbyindex(pXy,qDelimiter,nXyIndex++);
      nX=atoi(pTok);freeEx(pTok);
      pTok=strtokbyindex(pXy,qDelimiter,nXyIndex++);
      nY=atoi(pTok);freeEx(pTok);
      MGetVector(*MTX,TRUE,nX,NRL,NRH,&vX);vX+=NRL-1;
      MGetVector(*MTX,TRUE,nY,NRL,NRH,&vY);vY+=NRL-1;
      nDataTotal=NRH-NRL+1;

      VGetMinMaxValue(vX,1,nDataTotal,&dL,&dH);
      if (SWEEP&&*SWEEP) {
         pTok=strtokbyindex(SWEEP,qDelimiter,0);
         if (pTok[0]!='*') dL=atof(pTok);
         freeEx(pTok);
         pTok=strtokbyindex(SWEEP,qDelimiter,1);
         if (pTok[0]!='*') dH=atof(pTok);
         freeEx(pTok);
      }

      Echo(" xy=%d,%d ",nX,nY);
      if (!GetFittingRange(vX,NRL,NRH,nFitTotal,dL,dH,&nL,&nH)) goto N;
      if ((nH-nL+1)<nFitTotal) nFitTotal=nH-nL+1;
      pL=dtostr(dL,"%.1z");
      pH=dtostr(dH,"%.1z");
      Echo("range=%s,%s=[%d..%d] polynomial-order=%d\n",pL,pH,nL,nH,nFitTotal-1);
      freeEx(pL);
      freeEx(pH);
      vCoeff=VCreate(1,nFitTotal);
      dGoodnessOfFit=xsvdfit(vX,vY,nDataTotal,vCoeff,nFitTotal,fpoly);
      for (j=1;j<=nFitTotal;j++) Echo(" a[%d]=%.4g",j-1,vCoeff[j]);
      Echo("\n r2=%.3f\n",dGoodnessOfFit);
      VDestroy(vCoeff,1,nFitTotal);

N:    VDestroy(vX,1,nDataTotal);
      VDestroy(vY,1,nDataTotal);
   }

   free(pXy);
   return TRUE;
}

/******************************************************************************/
/* PolynomialFit.c */
