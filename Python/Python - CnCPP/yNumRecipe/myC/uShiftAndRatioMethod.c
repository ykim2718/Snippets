/*******************************************************************************
 Y.Kim)2001.0418
 Y.Taur and T.H.Ning,"Fundamentals of Modern VLSI Devices"
 1998,Page 206-211
 
! Input-Matrix
! argument="bias=0.1,1.8,0.1 length=.15,.16,.17,.18,.19,.20,.22,.3,.5,1,10"
! For NMOSFET,
! Vds=0.1V, Vbs=0.0V
! Input-Matrix                    | ! Output-Matrix(NOPTION=1)
! Vgs  s1 s2 s3 <- split          | ! s1            s2            s3
  0.0  *  *  *  <- for 10/0.15    |   0.0 0.1...1.8 0.0 0.1...1.8 0.0 0.1...1.8
  0.1  *  *  *                    |   Leff ........ Leff ........ Leff ........
  0.2  *  *  *                    |
  ...  *  *  *                    | ! Output-Matrix(NOPTION=2)
  1.8  *  *  *                    | ! s1            s2            s3
  0.0  *  *  *  <- for 10/0.16    |   0.0 0.1...1.8
.8 0.1 0.2...1.8 0.1 0.2...1.8
  0.1  *  *  *                    |   Rsd ......... Rsd ......... Rsd .........
  0.2  *  *  *                    |
  ...  *  *  *                    |
  1.8  *  *  *                    |
  ............  <- for 10/...
  0.0  *  *  *  <- for 10/10
  0.1  *  *  *
  0.2  *  *  *
  ...  *  *  *
  1.8  *  *  *
*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "nr.h"
#include "str.h"
#include "tools.h"
#include "usrfunc.h"

#define ABS(x) ((x)<0 ? (-(x)):(x))

static int nShiftAndRatioMethod_VectorCount;
static double *pShiftAndRatioMethod_VectorBias; /* [1..nShiftAndRatioMethod_VectorCount] */
static double *pShiftAndRatioMethod_VectorRef;  /* [1..nShiftAndRatioMethod_VectorCount] */
static double *pShiftAndRatioMethod_VectorVar;  /* [1..nShiftAndRatioMethod_VectorCount] */
static double *pShiftAndRatioMethod_VectorShift;/* [1..nShiftAndRatioMethod_VectorCount] */
static double *pShiftAndRatioMethod_VectorRatio;/* [1..nShiftAndRatioMethod_VectorCount] */
static
double ShiftAndRatioMethod_DeltaFunction( double dDelta )
{
   int nIndex,nStart;
   double y,dy,dAverage,dVariance;

   /* dDelta>=0 */

   for (nIndex=1;nIndex<=nShiftAndRatioMethod_VectorCount;nIndex++) {
      pShiftAndRatioMethod_VectorRatio[nIndex]=
         pShiftAndRatioMethod_VectorBias[nIndex]-dDelta;
   }
   for (nIndex=1;nIndex<=nShiftAndRatioMethod_VectorCount;nIndex++) {
      if (pShiftAndRatioMethod_VectorBias[1]>=0) {
         if (pShiftAndRatioMethod_VectorRatio[1]<=
             pShiftAndRatioMethod_VectorBias[nIndex]) {
            nStart=nIndex;
            break;
         }
      } else {
         if (pShiftAndRatioMethod_VectorRatio[1]>=
             pShiftAndRatioMethod_VectorBias[nIndex]) {
            nStart=nIndex;
            break;
         }
      }
   }
   for (nIndex=nStart;nIndex<=nShiftAndRatioMethod_VectorCount;nIndex++) {
      polint(
         pShiftAndRatioMethod_VectorRatio, /* shifted bias vector temporarily */
         pShiftAndRatioMethod_VectorVar,
         nShiftAndRatioMethod_VectorCount,
         pShiftAndRatioMethod_VectorBias[nIndex],
         &y,
         &dy /* error */
         );
      pShiftAndRatioMethod_VectorShift[nIndex]=y;
   }
   for (nIndex=nStart;nIndex<=nShiftAndRatioMethod_VectorCount;nIndex++) {
      pShiftAndRatioMethod_VectorRatio[nIndex]=
         pShiftAndRatioMethod_VectorRef[nIndex]/
         pShiftAndRatioMethod_VectorShift[nIndex];
   }

   dAverage=0.0;
   for (nIndex=nStart;nIndex<=nShiftAndRatioMethod_VectorCount;nIndex++) {
      dAverage+=pShiftAndRatioMethod_VectorRatio[nIndex];
   }
   dAverage/=(nShiftAndRatioMethod_VectorCount-nStart+1);
   dVariance=0.0;
   for (nIndex=nStart;nIndex<=nShiftAndRatioMethod_VectorCount;nIndex++) {
      y=pShiftAndRatioMethod_VectorRatio[nIndex]-dAverage;
      dVariance+=y*y;
   }
   dVariance/=(nShiftAndRatioMethod_VectorCount-nStart);

   return dVariance;
}

int ShiftAndRatioMethod( ARGUMENTS )
   ARGULIST
{
   char *pBias,*pLength,*pAddr;
   double dStart,dEnd,dStep,**ppMatrix;
   int nBiasCount,nLengthCount,nRowBlockCount;
   int nIndex,nSubIndex,nRow,nCol,nRowStart,nRowEnd,nMaxLengthIndex;
   double dSlope,dDelta,dRatio,dValue;

   if (!ARGUMENT||!*ARGUMENT||!strlen(ARGUMENT)) return FALSE;
   if (!(pBias=strstr(ARGUMENT,"bias="))) return FALSE; 
   if (!(pLength=strstr(ARGUMENT,"length="))) return FALSE;
   pBias=strmiddle(pBias,0,pLength-pBias);
   pLength=strdpl(pLength);
   dStart=atof(pAddr=strtokbyindex(pBias,"=, ",1));freeEx(pAddr);
   dEnd=atof(pAddr=strtokbyindex(pBias,"=, ",2));freeEx(pAddr);
   dStep=atof(pAddr=strtokbyindex(pBias,"=, ",3));freeEx(pAddr);
   if (ABS(dStart)<1e-6) return FALSE;

   nBiasCount=(int)((dEnd-dStart)/dStep)+1;
   nLengthCount=chrcount(pLength,',')+1;
   if ((*MRH-*MRL+1)%nLengthCount) {
      freeEx(pBias);
      freeEx(pLength);
      return FALSE;
   }

   if ((*MRH-*MRL+1)%(nBiasCount*nLengthCount)) return FALSE;
   nRowBlockCount=(int)((*MRH-*MRL+1)/nBiasCount/nLengthCount);

   ppMatrix=*MTX;

   /* R */
   for (nRow=*MRL;nRow<=*MRH;nRow++) {
      for (nCol=*MCL+1;nCol<=*MCH;nCol++) {
         dValue=ppMatrix[nRow][*MCL]/ppMatrix[nRow][nCol];
         ppMatrix[nRow][nCol]=dValue;
      }
   }
   MWriteToFile("Rtotal.txt","%g",ppMatrix,*MRL,*MRH,*MCL,*MCH);

   /* Slope */
   for (nIndex=0;nIndex<nRowBlockCount*nLengthCount;nIndex++) {
      nRowStart=*MRL+nBiasCount*nIndex;
      nRowEnd=nRowStart+nBiasCount;
      for (nCol=*MCL+1;nCol<=*MCH;nCol++) {
         for (nRow=nRowStart;nRow<(nRowEnd-1);nRow++) {
            dSlope=ppMatrix[nRow][nCol]-ppMatrix[nRow+1][nCol];
            dSlope/=dStep;
            ppMatrix[nRow][nCol]=dSlope;
         }
         ppMatrix[nRow][nCol]=
            ppMatrix[nRow-1][nCol]-ppMatrix[nRow-2][nCol]+ppMatrix[nRow-1][nCol];
      }
   }
   MWriteToFile("Slope.txt","%g",ppMatrix,*MRL,*MRH,*MCL,*MCH);
   if (NOPTION==0) goto R;

   /* Ratio */
   nMaxLengthIndex=0;
   dValue=0.0;
   for (nIndex=0;nIndex<nLengthCount;nIndex++) {
      pAddr=strtokbyindex(pLength,"=, ",nIndex+1);
      if (dValue<atof(pAddr)) {
         nMaxLengthIndex=nIndex;
         dValue=atof(pAddr);
      }
      myFree(pAddr);
   }
   nShiftAndRatioMethod_VectorCount=nBiasCount>>0;
   pShiftAndRatioMethod_VectorBias=dvector(1,nShiftAndRatioMethod_VectorCount);
   pShiftAndRatioMethod_VectorRef=dvector(1,nShiftAndRatioMethod_VectorCount);
   pShiftAndRatioMethod_VectorVar=dvector(1,nShiftAndRatioMethod_VectorCount);
   pShiftAndRatioMethod_VectorShift=dvector(1,nShiftAndRatioMethod_VectorCount);
   pShiftAndRatioMethod_VectorRatio=dvector(1,nShiftAndRatioMethod_VectorCount);
   dValue=dStart;
   for (nIndex=1;nIndex<=nShiftAndRatioMethod_VectorCount;nIndex++) {
      pShiftAndRatioMethod_VectorBias[nIndex]=dValue;
      dValue+=dStep;
   }
   for (nCol=*MCL+1;nCol<=*MCH;nCol++) {
      for (nIndex=0;nIndex<nRowBlockCount;nIndex++) {
         nRowStart=*MRL+nBiasCount*(nIndex+nMaxLengthIndex);
         nRowEnd=nRowStart+nShiftAndRatioMethod_VectorCount;
         for (nRow=nRowStart;nRow<nRowEnd;nRow++) {
            pShiftAndRatioMethod_VectorRef[nRow-nRowStart+1]=ppMatrix[nRow][nCol];
         }
         for (nSubIndex=0;nSubIndex<nLengthCount;nSubIndex++) {
            nRowStart=*MRL+nBiasCount*(nIndex+nSubIndex);
            nRowEnd=nRowStart+nShiftAndRatioMethod_VectorCount;
            for (nRow=nRowStart;nRow<nRowEnd;nRow++) {
               pShiftAndRatioMethod_VectorVar[nRow-nRowStart+1]=ppMatrix[nRow][nCol];
            }
            /* dValue=ShiftAndRatioMethod_DeltaFunction(0.0);
            dValue=ShiftAndRatioMethod_DeltaFunction(0.025);
            dValue=ShiftAndRatioMethod_DeltaFunction(0.050);
            dValue=ShiftAndRatioMethod_DeltaFunction(0.075);
            dValue=ShiftAndRatioMethod_DeltaFunction(0.1);
            dValue=ShiftAndRatioMethod_DeltaFunction(0.125);
            dValue=ShiftAndRatioMethod_DeltaFunction(0.15);
            dValue=ShiftAndRatioMethod_DeltaFunction(0.175);
            dValue=ShiftAndRatioMethod_DeltaFunction(0.2); */
            dValue=brent(
               0.0,0.05,0.2,
               ShiftAndRatioMethod_DeltaFunction,
               1e-6,
               &dDelta);
            dRatio=dValue;
         }
      }
   }
   free_dvector(pShiftAndRatioMethod_VectorBias,1,nShiftAndRatioMethod_VectorCount);
   free_dvector(pShiftAndRatioMethod_VectorRef,1,nShiftAndRatioMethod_VectorCount);
   free_dvector(pShiftAndRatioMethod_VectorVar,1,nShiftAndRatioMethod_VectorCount);
   free_dvector(pShiftAndRatioMethod_VectorShift,1,nShiftAndRatioMethod_VectorCount);
   free_dvector(pShiftAndRatioMethod_VectorRatio,1,nShiftAndRatioMethod_VectorCount);
   MWriteToFile("Ratio.txt","%g",ppMatrix,*MRL,*MRH,*MCL,*MCH);
   
   if (NOPTION==1) goto R;

R: freeEx(pBias);
   freeEx(pLength);
   return TRUE;
}
