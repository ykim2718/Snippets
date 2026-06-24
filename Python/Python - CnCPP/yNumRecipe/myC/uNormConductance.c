/******************************************************************************/

#define MOUDLENAME "NormConductance()"

#include "usrfunc.h"
uFuncTableTag uNormConductanceTag={
"NormConductance:dln(J)/dln(V)",
"type=NormConductance                                                        \n"
"argument=smooth xy=(1,2)(1,3) unit=5                                        ",
"[Y.Kim]                                                                     \n"
"Normalized conductance = dln(J)/dln(V)                                      \n"
"2004.0315,0613                                                              \n"
"                                                                            \n"
"[Input]                                                                     \n"
"ARGUMENT=<MODEL>                                                            \n"
"! NONE: Slope will be extracted with its original data.                     \n"
"! SMOOTH+<f>: Obtained slope will be smoothed with low-pass noise filter: smooft(). \n"
"!    e.g.) smooth+10 -> smoothed with smooting parameter 10.                \n"
"! MONOTONIC: Make data monotonic before taking the slope.                   \n"
"! Orignal data is not changed at any case.       　　　　　　　　　　　　　 \n"
"XY=(X,Y,)(X,Y)...(X,Y)                                                      \n"
"! The first and the second in parentheses are X and Y vector indices.       \n"
"SUBOPTION|UNIT=<N>                                                          \n"
"! N [integer] : Defines minimum number of data point to fit.                \n"
"! Should be greater than 2 at least. Default is 5.                          \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! Add slope vector to the next of the last column for each set of X&Y indices."
};

/******************************************************************************/

#include <math.h>
#include <string.h>
#include "usrfunc.h"
#include "nrecipe.h"
#include "number.h"
#include "tools.h"
#include "str.h"

extern int Echo();

/******************************************************************************/

int NormConductance( ARGUMENTS )
   ARGULIST
{
   char *qDelimiter=",()",*pTok,*pAddr;
   int bSmooth,bMonotonic;
   int nCount,nSet,nUnit,nXCol,nYCol,nL,nH,nLB,nHB,i;
   double dSmootingFactor=1;
   VECTOR vX,vY,vS;

   /* Version */
   Echo(" V.1.1\n");

   /* Check "ARGUMENT" */
   bSmooth=bMonotonic=FALSE;
   nCount=strtokcount(ARGUMENT,qDelimiter);
   for (i=0;i<nCount;i++) {
      pTok=strtokbyindex(ARGUMENT,qDelimiter,i);
      switch (tolower(*pTok)) {
      case 's' : bSmooth=TRUE;
         pAddr=pTok;
         skipalpha(&pAddr);
         dSmootingFactor=atof(pAddr);
         break;
      case 'm' : bMonotonic=TRUE;
         break;
      }
      freeEx(pTok);
   }
   /* Check "XY" */
   if (chrcount(ARGUMENT2,'(')!=chrcount(ARGUMENT2,')')) {
      Echo(0,"%s\nNot paired parentheses at the expression of <XY=>\n",
         MOUDLENAME);
      return FALSE;
   }
   nSet=strtokcount(ARGUMENT2,qDelimiter);
   if (nSet%2) {
      Echo(0,"%s\nTotal number of argument per each set is not a muliple of 2 at <XY=>\n",
         MOUDLENAME);
      return FALSE;
   }
   nSet>>=1;
   /* Check "UNIT" */
   nUnit=(NSUBOPTION<2||NSUBOPTION>(NRH-NRL+1)) ? 2:NSUBOPTION;

   /* Echo */
   Echo(" Model=%s op.set=%d slope.unit=%d \n",ARGUMENT,nSet,nUnit);

   /* Compute */
   for (i=0;i<nSet;i++) {
      //nXCol,nYCol
      nXCol=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,i*2));freeEx(pTok);
      nYCol=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,i*2+1));freeEx(pTok);
      Echo(" [%d] xy=%d,%d\n",i+1,nXCol,nYCol);
      if (nXCol<NCL||nXCol>NCH||nYCol<NCL||nYCol>NCH) {
         Echo(0,
            "%s\nX(%d) or Y(%d) index is out of range "
            "compared to matrix columns [%d..%d] by the command of <XY=>.\n",
            MOUDLENAME,nXCol,nYCol,NCL,NCH);
         return FALSE;
      }
      /* Allocate vX,vY,vS */
      //MGetSafeVectorPair(*MTX,TRUE,NRL,NRH,nXCol,nYCol,&vX,&vY,&nL,&nH);
      MGetVector(*MTX,TRUE,nXCol,NRL,NRH,&vX);
      MGetVector(*MTX,TRUE,nYCol,NRL,NRH,&vY);
      nL=NRL;
      nH=NRH;
      vS=VCreate(nL,nH);
      /* Make x and y vectors natural logarithmic */
      for (i=nL;i<=nH;i++) {
         if (vX[i]<=0||vY[i]<=0) {
            MkNaNDouble(vX[i]);
            MkNaNDouble(vY[i]);
            continue;
         }
         vX[i]=log(vX[i]);
         vY[i]=log(vY[i]);
      }
      /* Check integrity and get new boundary */
      if (!VGetFirstIndexOfNumberBlock(vX,nL,nH,&nLB)||
          !VGetLastIndexOfNumberBlock(vX,nL,nH,&nHB)) {
         VDestroy(vX,nL,nH);
         VDestroy(vY,nL,nH);
         VDestroy(vS,nL,nH);
         return FALSE;
      }
      for (i=nL;i<nLB;i++) MkNaNDouble(vS[i]);
      for (i=nHB;i<nH;i++) MkNaNDouble(vS[i]);
      nL=nLB;
      nH=nHB;
      /* Make x and y vectors monotonic */
      if (bMonotonic) {
      }
      /* Compute slope */ {
      VECTOR vSlope;
      VGetSlopeVectorOverSpan(vX,vY,nL,nH,nUnit,&vSlope);
      for (i=nL;i<=nH;i++) vS[i]=vSlope[i];
      VDestroy(vSlope,nL,nH);
      }
      /* Make slope vector smooth */
      if (bSmooth) {
         VECTOR vSlope;
         int m=2;
         while (m<(nH+(int)(2.0*dSmootingFactor+0.5))) m*=2;
         vSlope=VCreate(1,m);
         for (i=nL;i<=nH;i++) vSlope[i-nL+1]=vS[i];
         smooft(vSlope,nH-nL+1,dSmootingFactor); /* Numerical Recipes in C, 1988, pp.514-16. */
         for (i=nL;i<=nH;i++) vS[i]=vSlope[i-nL+1];
         VDestroy(vSlope,1,m);
      }
      /* Attach slope vector to original matrix */
      MAddVector(MTX,NRL,NRH,NCL,NCH,vS,TRUE,MRH,MCH);
      /* Release */
      VDestroy(vX,NRL,NRH);
      VDestroy(vY,NRL,NRH);
      VDestroy(vS,NRL,NRH);
   }

   return TRUE;
}

/******************************************************************************/
/* NormConductance.c */
