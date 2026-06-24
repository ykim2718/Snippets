/******************************************************************************

       File: yNrecipe.c
Description: Numberical Recipes in C
    Creator: Kim, Yongshik (copyRight)
       Date: 43240103-43250115
   Revision: Kim, Yongshik
     Update: 4332 0303,
             4334 0604,
             4336 0210 - 0225, 0318,0503, 0611, 0806,0820,0901-0902,0929-0930,
                  1207 - 1209,
             4337 0101 - 0103, 0613
Last Update: 2016 0325 - 0331

*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "yCore.h"
#include "yAlloc.h"
#include "yNumber.h"
#include "yNrecipe.h"
#include "yAny.h"
#include "yString.h"
#include "yNr.h"

/******************************************************************************/

/******************************************************************************/

Vector *VCreateEx ( int nL,int nH )
{
   Vector *V;
   V=salloc(Vector,1);
   V->v=dvector(nL,nH);
   V->l=nL;
   V->h=nH;
   return V;
}

int VDestroyEx( Vector *V )
{
   free_dvector(V->v,V->l,V->h);
   free(V);
   return TRUE;
}

Matrix *MCreateEx( int nRL,int nRH,int nCL,int nCH )
{
   Matrix *M;
   M=salloc(Matrix,1);
   M->m=dmatrix(nRL,nRH,nCL,nCH);
   M->rl=nRL;
   M->rh=nRH;
   M->cl=nCL;
   M->ch=nCH;
   return M;
}

int MDestroyEx( Matrix *M )
{
   free_dmatrix(M->m,M->rl,M->rh,M->cl,M->ch);
   free(M);
   return TRUE;
}

VECTOR VCreate( int nL,int nH )
{
   return dvector(nL,nH);
}

int VDestroy( VECTOR vAny,int nL,int nH )
{
   free_dvector(vAny,nL,nH);
   return TRUE;
}

int VCopy( VECTOR vSource,VECTOR vDestination,int nL,int nH )
{
   int i;
   for (i=nL;i<=nH;i++)
      vDestination[i]=vSource[i];
   return TRUE;
}

VECTOR VDuplicate( VECTOR vAny,int nL,int nH )
{
   VECTOR vNew;
   vNew=VCreate(nL,nH);
   memcpy((char*)&(vNew[nL]),(char*)&(vAny[nL]),sizeof(double)*(nH-nL+1));
   return vNew;
}

VECTOR VDuplicateSafely( VECTOR vAny,int nL,int nH,int *nNewH )
{
   VECTOR vNew;
   int j,nCount;
   vNew=VCreate(0,nH-nL+1);
   for (j=nL,nCount=0;j<=nH;j++) {
      if (IsNaNDouble(vAny[j])) continue;
      vNew[nCount]=vAny[j];
      nCount++;
   }
   if (!nCount) {
      VDestroy(vNew,0,nH-nL+1);
      vNew=0;
      nNewH=0;
   } else {
      VChangeBase(&vNew,0,nL);
      *nNewH=nL+nCount-1;
   }
   return vNew;
}

int VChangeBase( pVec,nBaseOld,nBaseNew )
   VECTOR *pVec;
   int nBaseOld,nBaseNew;
{
   *pVec=(*pVec)-(nBaseNew-nBaseOld);
   return TRUE;
}

int VChangeBase2( VECTOR *pV1,VECTOR *pV2,int nBaseOld,int nBaseNew )
{
   return
      VChangeBase(pV1,nBaseOld,nBaseNew) &
      VChangeBase(pV2,nBaseOld,nBaseNew);
}

int VGetMinOrMaxValue( vAny,nL,nH,bMax,pdReturn )
   VECTOR vAny;
   int nL,nH,bMax;
   double *pdReturn;
{
   int i=nL,j;
   while (IsNaNDouble(vAny[i])) i++;
   if (i>nH) {
      *pdReturn=vAny[nL];
      return nL;
   }
   *pdReturn=vAny[j=i];
   for (i++;i<=nH;i++) {
      if (IsNaNDouble(vAny[i])) continue;
      if (bMax&&*pdReturn<vAny[i]) *pdReturn=vAny[j=i];
      else if (!bMax&&*pdReturn>vAny[i]) *pdReturn=vAny[j=i];
   }
   return j;
}

int VGetMinMaxValue( vAny,nL,nH,pMin,pMax )
   VECTOR vAny;
   int nL,nH;
   double *pMin,*pMax;
{
   int i=nL;
   while (IsNaNDouble(vAny[i])) i++;
   if (i>nH) return FALSE;
   if (pMin) *pMin=vAny[i];
   if (pMax) *pMax=vAny[i];
   for (i++;i<=nH;i++) {
      if (IsNaNDouble(vAny[i])) continue;
      if (pMin && *pMin>vAny[i]) *pMin=vAny[i];
      if (pMax && *pMax<vAny[i]) *pMax=vAny[i];
   }
   return TRUE;
}

double VGetOneSideStdev( vAny,nL,nH,dRef,bPositiveSide )
   VECTOR vAny;
   int nL,nH,bPositiveSide;
   double dRef;
{
   int nIndex,nCount;
   double dS,dSS;

   bPositiveSide=bPositiveSide ? 1:-1;
   nCount=0;
   dSS=0.0;
   for (nIndex=nL;nIndex<=nH;nIndex++) {
      dS=vAny[nIndex]-dRef;
      if (dS*bPositiveSide<0.0) continue;
      nCount++;
      dSS+=dS*dS;
   }
   if (!nCount) return 0.0;
   return sqrt(dSS/nCount);
}

int VGetValueIndexOfMonotonicVector( vAny,nL,nH,dValue,pResult )
   VECTOR vAny; /* monotonic */
   int nL,nH,*pResult;
   double dValue;
{
   /* 20031227.....Uncomplete
   int j;
   VChangeBase(&vAny,nL,1);
   locate(vAny,nH-nL+1,dValue,&j);
   *pResult=j+nL-1;
   return TRUE; */
   int j;
   *pResult=nL-1;
   for (j=nL;j<nH;j++) {
      if ((vAny[j]<vAny[j+1] && vAny[j]<=dValue && dValue<=vAny[j+1]) ||
         (vAny[j]>vAny[j+1] && vAny[j]>=dValue && dValue>=vAny[j+1])) {
         *pResult=ABS(vAny[j]-dValue)<ABS(vAny[j+1]-dValue) ? j:j+1;
         return TRUE;
      }
   }
   *pResult=(dValue<=vAny[nL])?nL:(dValue>=vAny[nH])?nH:nL-1; //20031218
   return FALSE;
}

int VGetValueIndexOfMonotonicVectorEx( vAny,nL,nH,dValue,pResult,dTolerance )
   VECTOR vAny; /* monotonic */
   int nL,nH,*pResult;
   double dValue,dTolerance;
{
   int j;
   double dVLow,dVHigh;
   dTolerance=fabs(dTolerance);
   dVLow=dValue-dTolerance;
   dVHigh=dValue+dTolerance;
   *pResult=nL-1;
   for (j=nL;j<nH;j++) {
      if ((vAny[j]<vAny[j+1] && vAny[j]<=dVHigh && dVLow<=vAny[j+1]) ||
         (vAny[j]>vAny[j+1] && vAny[j]>=dVHigh && dVLow>=vAny[j+1])) {
         *pResult=ABS(vAny[j]-dValue)<ABS(vAny[j+1]-dValue) ? j:j+1;
         return TRUE;
      }
   }
   *pResult=nL;
   return FALSE;
}

int VGetIndexedBoudaryWithSpan( int nL,int nH, int nSpan, int nIndex, int *pnLB, int *pnHB )
{
   *pnLB=*pnHB=nL;
   if (nIndex<nL||nH<nIndex) {
      return FALSE;
   } else if (nIndex<=(nL+nSpan)) {
      *pnLB=nL;
      *pnHB=nL+nSpan-1;
   } else if (nIndex>=(nH-nSpan)) {
      *pnLB=nH-nSpan+1;
      *pnHB=nH;
   } else {
      *pnLB=nIndex-(nSpan>>1);
      *pnHB=*pnLB+nSpan-1;
   }
   return (*pnHB-*pnLB+1);
}

int VGetFirstIndexOfNumberBlock( VECTOR V,int nL,int nH, int *pnFirst )
{
   *pnFirst=nL-1;
   while (nL<=nH) {
      if (!IsNaNDouble(V[nL])) {
         *pnFirst=nL;
         return TRUE;
      }
      nL++;
   }
   return FALSE;
}

int VGetLastIndexOfNumberBlock( VECTOR V,int nL,int nH, int *pnLast )
{
   *pnLast=nH+1;
   while (nL<=nH) {
      if (!IsNaNDouble(V[nH])) {
         *pnLast=nH;
         return TRUE;
      }
      nH--;
   }
   return FALSE;
}

int VCheckIntegrity( VECTOR vAny,int nL,int nH )
{
   for (;nL<=nH;nL++) {
      if (IsNaNDouble(vAny[nL])) return FALSE;
      if (!_finite(vAny[nL])) return FALSE;
   }
   return TRUE;
}

int VCheckMonotonity( VECTOR vAny,int nL,int nH )
{
   int j,bSign;

   bSign=vAny[nH]>vAny[nL] ? 1:-1;
   for (j=nL+1;j<=nH;j++) {
      if (IsNaNDouble(vAny[j])) return FALSE;
      if (!_finite(vAny[j])) return FALSE;
      if ((vAny[j]-vAny[j-1])*bSign<=0) return FALSE;
   }
   return TRUE;
}

int VCheckGreaterThanZero( VECTOR vAny,int nL,int nH )
{
   int j;

   for (j=nL;j<=nH;j++) {
      if (IsNaNDouble(vAny[j])) return FALSE;
      if (!_finite(vAny[j])) return FALSE;
      if (vAny[j]<=0) return FALSE;
   }
   return TRUE;
}

int VIsInIntVector(int iValue, int *pVec, int nl, int nh)
{
	for (int j = nl; j <= nh; j++) {
		if (iValue == pVec[j]) return TRUE;
	}
	return FALSE;
}

int VMakeYVectorMonotonicByXVector( VECTOR vX,VECTOR vY,int nL,int nH )
/*
 * Requirements: 1) vX must be monotonic in advance.
 *               2) No abnormal numbers in both vectors.
 */
{
   double vCoeff[5];
   int nCoeff=4,nCoeffi;
   int bSign,nFirst,nLast,nSpan,i,j,k;
   VECTOR vZ;

   /*
   MATRIX m;
   m=MCreate(nL,nH,1,3);
   for (j=nL;j<=nH;j++) m[j][1]=vX[j];
   for (j=nL;j<=nH;j++) m[j][2]=vY[j]; */

   if (!VCheckIntegrity(vX,nL,nH)) return FALSE;
   if (!VCheckIntegrity(vY,nL,nH)) return FALSE;
   //if (!VCheckMonotonity(vX,nL,nH)) return FALSE;
   if (vY[nL]==vY[nH]) return FALSE;
   bSign=(vY[nH]-vY[nL])>0 ? 1:-1;
   nFirst=nLast=0;
   for (i=nL+1;i<=nH;i++) {
      if (nFirst==nLast && (vY[i]-vY[i-1])*bSign<=0)
         nFirst=i-1;
      if (nFirst!=nLast && (vY[i]-vY[i-1])*bSign>0) {
         nLast=i;
         for (;i<=nH&&(vY[nFirst]-vY[i])*bSign>0;i++);
         if (nLast<i) nLast=i;
         else return FALSE;
         nSpan=nLast-nFirst+1;
         nFirst=MAX(nFirst-nSpan,nL);
         nLast=MIN(nLast+nSpan,nH);
         nSpan=nLast-nFirst+1;
         vZ=VCreate(nFirst,nLast);
         nCoeffi=nCoeff;
         while (nCoeffi>=1) {
            xsvdfit(vX+nFirst-1,vY+nFirst-1,nSpan,vCoeff,nCoeffi,fpoly);
            for (j=nFirst;j<=nLast;j++) {
               vZ[j]=vCoeff[1];
               for (k=2;k<=nCoeffi;k++) vZ[j]+=vCoeff[k]*pow(vX[j],k-1);
            }
            if (VCheckMonotonity(vZ,nFirst,nLast)) break;
            nCoeffi--;
         }
         for (j=nFirst;j<=nLast;j++) vY[j]=vZ[j];
         VDestroy(vZ,nFirst,nLast);
         if (!nCoeffi) {
            for (j=nFirst;j<=nLast;j++) MkNaNDouble(vY[j]);
            return FALSE;
         }
         i=nL;
         nFirst=nLast=0;
      }
   }

   /*
   for (j=nL;j<=nH;j++) m[j][3]=vY[j];
   MWriteToFile("qName","%g",m,nL,nH,1,3); */

   return nFirst==nLast;
}

int VGetMaxValueIndexOfMonotonicVector( vV,nV,pResult ) /* ????? */
   VECTOR vV;
   int nV,*pResult;
{
   double dMax;
   int j;

   *pResult=-1;

   for (j=1;IsNaNDouble(vV[j]);j++);
   dMax=vV[j];
   for (j++;j<=nV;j++) {
      if (IsNaNDouble(vV[j])) continue;
      if (dMax<vV[j]) {
         dMax=vV[j];
         *pResult=j;
      }
   }
   return TRUE;
}

int VGetMaxSlopeOfMonotonicVectorByHalfRangeMethod( vX,vY,nXY,pResult )
   VECTOR vX,vY;
   int nXY;
   double *pResult;
{
   int nRange,nL,nH,nIndex,nIndexAtMax;
   double dMaxSlope,dNumerator,dDenominator,dSlope;

   nL=1;
   nH=nXY;
   nRange=nXY>>1;
   dMaxSlope=(vY[nH]-vY[nL])/(vX[nH]-vX[nL]);
   while (nRange>1) {
      for (nIndex=nL;(nIndex+nRange-1)<=nH;nIndex++) {
         dDenominator=vX[nIndex+nRange-1]-vX[nIndex];
         dNumerator=vY[nIndex+nRange-1]-vY[nIndex];
         dSlope=(dNumerator/dDenominator);
         if (dMaxSlope<dSlope) {
            dMaxSlope=dSlope;
            nIndexAtMax=nIndex;
         }
      }
      nL=nIndexAtMax;
      nH=nL+nRange-1;
      nRange=nRange>>1;
   }
   *pResult=dMaxSlope;
   return nIndexAtMax+(nRange>>1);
}

int VGetSlopeVector( /* 20030902 */
   VECTOR vX,VECTOR vY,int nL,int nH,int bFit,VECTOR *pvSlope
)
{
   if ((nH-nL+1)<5) { /* Fixed */
      *pvSlope=0;
      return FALSE;
   }
   *pvSlope=VCreate(nL,nH);
   if (!bFit) {
      int j;
      double dS1,dS2,dS3,dS4;
      for (j=nL+2;j<=(nH-2);j++) {
         dS1=vX[j]-vX[j-2];
         dS2=vX[j]-vX[j-1];
         dS3=vX[j+1]-vX[j];
         dS4=vX[j+2]-vX[j];
         if (dS1*dS2*dS3*dS4==0) {
            VDestroy(*pvSlope,nL,nH);
            *pvSlope=0;
            return FALSE;
         }
         dS1=(vY[j]-vY[j-2])/dS1;
         dS2=(vY[j]-vY[j-1])/dS2;
         dS3=(vY[j+1]-vY[j])/dS3;
         dS4=(vY[j+2]-vY[j])/dS4;
         (*pvSlope)[j]=(dS1+dS2+dS3+dS4)/4;
         if (j==(nL+2)) {
            (*pvSlope)[nL]=dS1;
            (*pvSlope)[nL+1]=(dS1+dS2)/2;
         } else if (j==(nH-2)) {
            (*pvSlope)[nH-1]=(dS3+dS4)/2;
            (*pvSlope)[nH]=dS4;
         }
      }
   } else { // not yet
      VECTOR vXFit,vYFit,vCoeff,sig,w;
      MATRIX u,v;
      double dChi2;
      int nFit,nCoeff,nNan,i,j,k;
      nFit=5; /* Fixed */
      nCoeff=3; /* Fixed */
      vXFit=VCreate(1,nFit);
      vYFit=VCreate(1,nFit);
      vCoeff=VCreate(1,nCoeff);
      sig=VCreate(1,nFit);
      for (j=1;j<=nFit;j++) sig[j]=1;
      u=MCreate(1,nFit,1,nCoeff);
      v=MCreate(1,nCoeff,1,nCoeff);
      w=VCreate(1,nCoeff);
      for (i=j=nL;i<=nH;i++) {
         for (k=nNan=0;k<nFit&&(j+k)<=nH;) {
            if (IsNaNDouble(vX[j+k+nNan])||IsNaNDouble(vY[j+k+nNan])) {
               nNan++;
               continue;
            }
            vXFit[k+1]=vX[j+k+nNan];
            vYFit[k+1]=vY[j+k+nNan];
            k++;
         }
         if (k==nFit) svdfit(vXFit,vYFit,sig,nFit,vCoeff,nCoeff,u,v,w,&dChi2,fpoly);
         (*pvSlope)[i]=vCoeff[2]+2*vCoeff[3]*vX[i];
         if ((j+nFit+nNan)<nH&&(i-j)>(nFit>>1)) j++;
      }
      MDestroy(u,1,nFit,1,nCoeff);
      MDestroy(v,1,nCoeff,1,nCoeff);
      VDestroy(w,1,nCoeff);
      VDestroy(vXFit,1,nFit);
      VDestroy(vYFit,1,nFit);
   }

   return TRUE;
}

int VGetSlopeVectorOverSpan( /* 20040613 */
   VECTOR vX,VECTOR vY,int nL,int nH,int nSpan,VECTOR *pvSlope
)
{
   int nTotal=nH-nL+1,nHalf,i;
   double dSlope,dYi,dAbdev;

   if (nTotal<2) {
      *pvSlope=0;
      return FALSE;
   } else if (nTotal==2) {
      if (vX[nH]==vX[nL]) {
         *pvSlope=0;
         return FALSE;
      }
   }

   *pvSlope=VCreate(nL,nH);
   if (nTotal<nSpan) nSpan=nTotal;
   nHalf=nSpan>>1;

   if (nTotal==nSpan) {
      medfit(vX+nL-1,vY+nL-1,nSpan,&dYi,&dSlope,&dAbdev);
      for (i=nL;i<=nH;i++) (*pvSlope)[i]=dSlope;
   } else if (nSpan==2) {
      for (i=nL;i<nH;i++) {
         dSlope=(vY[i+1]-vY[i])/(vX[i+1]-vX[i]);
         (*pvSlope)[i]=dSlope;
      }
      (*pvSlope)[nH]=(*pvSlope)[nH-1];
   } else {
      for (i=nL;(i+nSpan)<=nH;i++) {
         medfit(vX+i-1,vY+i-1,nSpan,&dYi,&dSlope,&dAbdev);
         (*pvSlope)[i+nHalf]=dSlope;
      }
   }
   for (i=nL;i<(nL+nHalf);i++) (*pvSlope)[i]=(*pvSlope)[nL+nHalf];
   nHalf=nSpan-nHalf;
   for (i=nH;i>(nH-nHalf);i--) (*pvSlope)[i]=(*pvSlope)[nH-nHalf];

   return TRUE;
}

int VGetInterpolatedYValueWithXYVectors( /* 20030901 */
   double dXValue,VECTOR vX,VECTOR vY,int nL,int nH,int nSpan,
   double *pdReturn
)
{
   int nPosition,nFirst,nLast;
   double dError;

   MkNaNDouble(*pdReturn);
   if (!VGetValueIndexOfMonotonicVector(vX,nL,nH,dXValue,&nPosition))
      return FALSE;
   nFirst=nSpan>>1;
   nLast=nSpan-nFirst-1;
   nFirst=(nPosition-nFirst)>=nL ? nPosition-nFirst:nL;
   nLast=(nPosition+nLast)<=nH ? nPosition+nLast:nH;
   vX+=nFirst-nL;
   vY+=nFirst-nL;
   /* Press,Numerical Receipes in C,p.90 */
   polint(vX,vY,nLast-nFirst+1,dXValue,pdReturn,&dError);
   return TRUE;
}

int VGetCumAreaVector( /* 20031003,1208 */
   VECTOR vX,VECTOR vY,int nL,int nH,int bAbsolute,VECTOR *pvArea
)
{
   int i;
   VECTOR vArea;
   double dYc,dYn,dYAvg;
   *pvArea=(VECTOR)0;
   if ((nH-nL)<1) return FALSE;
   /* if (bLog && !bAbsolute) return FALSE;
   if (bLog && !VCheckGreaterThanZero(vY,nL,nH)) return FALSE; */
   vArea=VCreate(nL,nH);
   if (bAbsolute) {
      /* if (bLog) {
         dYc=log(fabs(vY[nL]));
         for (i=nL;i<nH;i++) {
            dYn=log(fabs(vY[i+1]));
            dYAvg=exp((dYc+dYn)/2);
            vArea[i]=fabs(dYAvg*(vX[i+1]-vX[i]));
            dYc=dYn;
         }
      } else { */
      dYc=fabs(vY[nL]);
      for (i=nL;i<nH;i++) {
         dYn=fabs(vY[i+1]);
         if (vY[i]*vY[i+1]<0) { /* 20031219 */
            int j,k;
            double dX0,dError;
            j=MAX(nL,i-1);
            k=MIN(nH,i+2);
            polint(vY+j-1,vX+j-1,k-j+1,0,&dX0,&dError);
            vArea[i]=fabs((vY[i]*(dX0-vX[i]))+fabs(vY[i+1]*(vX[i+1]-dX0)))*0.5;
            dYc=dYn;
            continue;
         }
         dYAvg=(dYc+dYn)/2;
         vArea[i]=dYAvg*fabs(vX[i+1]-vX[i]);
         dYc=dYn;
      }
      /* } */
      vArea[i]=(i==(nL+1)) ? vArea[i-1]:fabs(vArea[i-1]+(vArea[i-1]-vArea[i-2]));
   } else {
      for (i=nL;i<nH;i++) {
         dYc=vY[i];
         dYn=vY[i+1];
         if (dYc*dYn<0) { /* 20031219 */
            int j,k;
            double dX0,dError;
            j=MAX(nL,i-1);
            k=MIN(nH,i+2);
            polint(vY+j-1,vX+j-1,k-j+1,0,&dX0,&dError);
            vArea[i]=(vY[i]*fabs(dX0-vX[i])+vY[i+1]*fabs(vX[i+1]-dX0))*0.5;
            continue;
         }
         vArea[i]=(vY[i+1]+vY[i])/2*fabs(vX[i+1]-vX[i]);
      }
      vArea[i]=(i==(nL+1)) ? vArea[i-1]:vArea[i-1]+(vArea[i-1]-vArea[i-2]);
   }
   for (i=nL+1;i<=nH;i++) vArea[i]+=vArea[i-1];
   *pvArea=vArea;
   return TRUE;
}

int VGetEqualSpanVector(
   double dStart,double dStop,int nTotal,int bLog,VECTOR *pvSpan,int *nL,int *nH
   )
{
   int i;
   double dStep;
   *pvSpan=(VECTOR)(size_t)(*nL=*nH=0);
   if (dStop<dStart) {
      double d=dStop;
      dStop=dStart;
      dStop=d;
   }
   if (bLog) {
      if (dStart<=0||dStop<=0) return 0;
      dStart=log(dStart);
      dStop=log(dStop);
   }
   *pvSpan=VCreate(1,nTotal);
   *nL=1;
   *nH=nTotal;
   dStep=(dStop-dStart)/(nTotal-1);
   for (i=1;i<=nTotal;i++) (*pvSpan)[i]=(i-1)*dStep+dStart;
   if (bLog) for (i=1;i<=nTotal;i++) (*pvSpan)[i]=exp((*pvSpan)[i]);
   return nTotal;
}

int VChangeXStepsInARange(
   VECTOR vX,VECTOR vY,int nL,int nH, /* vX should be monotonic */
   VECTOR *pvXNew,VECTOR *pvYNew,int *pnLNew,int *pnHNew,
   double dXStart,double dXStop,double dXStep
)
{
   VECTOR vXNew,vYNew;
   int bReversed,i,j,nStart,nStop,nAdd,nHNew,nHCount,jL,jH;
   double dZ,dError;

   bReversed=0;
   if (vX[nL]>vX[nH]) { /* Make increasing monotonic vector */
      for (i=nL,j=nH;i<j;i++,j--) {
         dZ=vX[i];vX[i]=vX[j];vX[j]=dZ;
         dZ=vY[i];vY[i]=vY[j];vY[j]=dZ;
      }
      bReversed=1;
   }
   if (dXStart>dXStop) {
      dZ=dXStart;
      dXStart=dXStop;
      dXStop=dZ;
   }

   //locate(vX+nL-1,nH-nL+1,dXStop,&nTarget);
   VGetValueIndexOfMonotonicVector(vX,nL,nH,dXStart,&nStart);
   VGetValueIndexOfMonotonicVector(vX,nL,nH,dXStop,&nStop);
   if (vX[nStart]>dXStart) nStart=MAX(nL,nStart-1);
   if (vX[nStop]<dXStop) nStop=MIN(nH,nStop+1);
   if (nStart==nStop) {
      *pvXNew=*pvYNew=0;
      *pnLNew=*pnHNew=0;
      return *pnLNew**pnHNew;
   }

   nAdd=(int)fabs((dXStop-dXStart)/dXStep);
   nHNew=nH+nAdd;
   vXNew=VCreate(nL,nHNew);
   vYNew=VCreate(nL,nHNew);
   nHCount=nL;
   for (i=nL;i<nStart;i++) {
      vXNew[nHCount]=vX[i];
      vYNew[nHCount]=vY[i];
      nHCount++;
   }
   for (i=nL;i<nL+nAdd;i++) {
      vXNew[nHCount]=dXStart+dXStep*(i-nL);
      if (vXNew[nHCount]<vX[nStart]||vX[nStop]<vXNew[nHCount]) break;
      if (vXNew[nHCount]<dXStart||dXStop<vXNew[nHCount]) break;
      hunt(vX+nL-1,nH-nL+1,vXNew[nHCount],&j); /* 20031226 */
      jL=MAX(j-1,nL);
      jH=MIN(j+1,nH);
      polint(vX+jL-1,vY+jL-1,jH-jL+1,vXNew[nHCount],&(vYNew[nHCount]),&dError);
      //polint(vX+nStart-1,vY+nStart-1,nStop-nStart+1,vXNew[nHCount],&(vYNew[nHCount]),&dError);
      nHCount++;
   }
   for (i=nStop;i<=nH;i++) { /* greater than dXStop */
      vXNew[nHCount]=vX[i];
      vYNew[nHCount]=vY[i];
      nHCount++;
   }
   nHCount--;

   if (bReversed) {
      for (i=nL,j=nHCount;i<j;i++,j--) {
         dZ=vX[i];vX[i]=vX[j];vX[j]=dZ;
         dZ=vY[i];vY[i]=vY[j];vY[j]=dZ;
      }
   }

   *pvXNew=vXNew;
   *pvYNew=vYNew;
   *pnLNew=nL;
   *pnHNew=nHCount;
   return *pnLNew**pnHNew;
}

int VWriteToFile(
   const char *qFile,const char *qFormat,VECTOR vAny,int nL,int nH
   )
{
   FILE *o;
   int i;
   char qFmt[32],qFmtNan[32];

   if (!(o=fopen(qFile,"w"))) return FALSE;
   sprintf(qFmt," %s",qFormat);
   sprintf(qFmtNan,qFmt,0.0);
   memset(qFmtNan+2,' ',strlen(qFmtNan+2));
   qFmtNan[2]=NUMNULLCHR;
   fprintf(o,"! %s : [%d..%d]\n",qFile,nL,nH);
   for (i=nL;i<=nH;i++) {
      IsNaNDouble(vAny[i]) ? fprintf(o,qFmtNan):fprintf(o,qFmt,vAny[i]);
      fprintf(o,"\n");
   }
   fclose(o);
   return TRUE;
}

MATRIX MCreate(
   int nRl,int nRh,int nCl,int nCh
   )
{
   return dmatrix(nRl,nRh,nCl,nCh);
}

int MDestroy(
   MATRIX M,int nRl,int nRh,int nCl,int nCh
   )
{
   free_dmatrix(M,nRl,nRh,nCl,nCh);
   return TRUE;
}

int MCopy(
   MATRIX mSource,MATRIX mDestination,
   int nRl,int nRh,int nCl,int nCh
   )
{
   int i,j;
   for (i=nRl;i<=nRh;i++)
      for (j=nCl;j<=nCh;j++)
         mDestination[i][j]=mSource[i][j];
   return TRUE;
}

int MGetMinMaxVector( mtrx,dir,nRL,nRH,nCL,nCH,minvec,maxvec )
   const MATRIX mtrx;
   int dir,nRL,nRH,nCL,nCH;
   double *(*minvec),*(*maxvec);
{
   register int i,j;

   switch (dir) {
   case MTX_HORIZONTAL : /* == */
        (*minvec)=dvector(nRL,nRH);
        (*maxvec)=dvector(nRL,nRH);
        for (i=nRL;i<=nRH;i++) {
           j=nCL;
           while (IsNaNDouble(mtrx[i][j])&&j<nCH) j++;
           if (j==nCH)
              errExit("invalid raw-data in MtxGetMinMaxVector()");
           (*minvec)[i]=(*maxvec)[i]=mtrx[i][j];
        }
        for (i=nRL;i<=nRH;i++) {
           for (j=nCL;j<=nCH;j++) {
              if (!IsNaNDouble(mtrx[i][j])
              && (*maxvec)[i]<mtrx[i][j])
                 (*maxvec)[i]=mtrx[i][j];
              if (!IsNaNDouble(mtrx[i][j])
              && mtrx[i][j]<(*minvec)[i])
                 (*minvec)[i]=mtrx[i][j];
           }
        } break;
   case MTX_VERTICAL : /* || */
        (*minvec)=dvector(nCL,nCH);
        (*maxvec)=dvector(nCL,nCH);
        for (j=nCL;j<=nCH;j++) {
           i=nRL;
           while (IsNaNDouble(mtrx[i][j])&&i<nRH) i++;
           if (i==nRH)
              errExit("invalid col-data in MtxGetMinMaxVector()");
           (*minvec)[j]=(*maxvec)[j]=mtrx[i][j];
        }
        for (j=nCL;j<=nCH;j++) {
           for (i=nRL;i<=nRH;i++) {
              if (!IsNaNDouble(mtrx[i][j])
              && (*maxvec)[j]<mtrx[i][j])
                 (*maxvec)[j]=mtrx[i][j];
              if (!IsNaNDouble(mtrx[i][j])
              && mtrx[i][j]<(*minvec)[j])
                 (*minvec)[j]=mtrx[i][j];
            }
        }
   }
   return TRUE;
}

int MGetMinMaxValue( mAny,bVertical,nIndex,nL,nH,bLogarithm,pMin,pMax )
   const MATRIX mAny;
   int bVertical,nIndex,nL,nH,bLogarithm;
   double *pMin,*pMax;
{
#define isBad(d) (IsNaNDouble(d) || (bLogarithm&&(d)<=0))
   int i,nDir;
   double d;

   *pMin=NUMBER_MAX_POSITIVE_DOUBLE;
   *pMax=NUMBER_MAX_NEGATIVE_DOUBLE;

   nDir=bVertical ? MTX_VERTICAL:MTX_HORIZONTAL;

   switch (nDir) {
   case MTX_HORIZONTAL : /* == */
      for (i=nL;i<=nH&&isBad(mAny[nIndex][i]);i++);
      if (i>nH) {
         errWarning("MGetMinMaxValue(): Invalid row data to find MIN-MAX value.");
         return FALSE;
      }
      *pMin=*pMax=mAny[nIndex][i];
      for (i=nL;i<=nH;i++) {
         d=mAny[nIndex][i];
         if (!isBad(d) && *pMax<d) *pMax=d;
         if (!isBad(d) && d<*pMin) *pMin=d;
      } break;
   case MTX_VERTICAL : /* || */
      for (i=nL;i<=nH&&isBad(mAny[i][nIndex]);i++); /* 20030307 */
      if (i>nH) {
         errWarning("MGetMinMaxValue(): Invalid column data to figure out MIN-MAX value.");
         return FALSE;
      }
      *pMin=*pMax=mAny[i][nIndex];
      for (i=nL;i<=nH;i++) {
         d=mAny[i][nIndex];
         if (!isBad(d) && *pMax<d) *pMax=d;
         if (!isBad(d) && d<*pMin) *pMin=d;
      } break;
   }
   return TRUE;
#undef isBad
}

int MGetVector( mAny,bVertical,nIndex,nL,nH,pVec )
   const MATRIX mAny;
   int bVertical,nIndex,nL,nH;
   VECTOR *pVec;
{
   int j;
   *pVec=dvector(nL,nH);
   if (bVertical) { /* nIndex -> nColumn */
      for (j=nL;j<=nH;j++) (*pVec)[j]=mAny[j][nIndex];
   } else { /* nIndex -> nRow */
      for (j=nL;j<=nH;j++) (*pVec)[j]=mAny[nIndex][j];
   }
   return (nH-nL+1);
}

int MGetSafeVector( mAny,bVertical,nIndex,nL,nH,pVec,pnL,pnH ) /* 20030526 */
   const MATRIX mAny;
   int bVertical,nIndex,nL,nH,*pnL,*pnH;
   VECTOR *pVec;
{
   VECTOR Vector;
   int j;

   if (!bVertical) return 0; /* Under Construction */

   MGetVector(mAny,bVertical,nIndex,nL,nH,pVec);
   Vector=VCreate(nL,nH);
   *pnL=*pnH=nL;
   for (j=nL;j<=nH;j++) {
      if (IsNaNDouble((*pVec)[j])) continue;
      Vector[*pnH]=(*pVec)[j];
      (*pnH)++;
   }
   (*pnH)--;
   VDestroy(*pVec,nL,nH);
   *pVec=Vector;
   if (*pnL>*pnH) {
      VDestroy(*pVec,*pnL,*pnH);
      *pVec=(VECTOR)(size_t)(*pnL=*pnH=0);
      return 0;
   }
   return (nH-nL+1);
}

int MGetSafeVectorPair( /* 20030806 */
   mAny,bVertical,nL,nH,nXIndex,nYIndex,pXVec,pYVec,pnL,pnH
)
   const MATRIX mAny;
   int bVertical,nL,nH,nXIndex,nYIndex,*pnL,*pnH;
   VECTOR *pXVec,*pYVec;
{
   VECTOR vX,vY;
   int j,k;

   if (!bVertical) return 0; /* Under Construction */

   MGetVector(mAny,bVertical,nXIndex,nL,nH,pXVec);
   MGetVector(mAny,bVertical,nYIndex,nL,nH,pYVec);
   vX=VCreate(nL,nH);
   vY=VCreate(nL,nH);
   for (j=k=nL;j<=nH;j++) {
      if (IsNaNDouble((*pXVec)[j])) continue;
      if (IsNaNDouble((*pYVec)[j])) continue;
      vX[k]=(*pXVec)[j];
      vY[k]=(*pYVec)[j];
      k++;
   }
   if (k==nL) {
      VDestroy(vX,nL,nH);
      VDestroy(vY,nL,nH);
      *pXVec=*pYVec=(VECTOR)(size_t)(*pnL=*pnH=0);
      return 0;
   }
   VDestroy(*pXVec,nL,nH);
   VDestroy(*pYVec,nL,nH);
   *pXVec=vX;
   *pYVec=vY;
   *pnL=nL;
   *pnH=k-1;
   return (nH-nL+1);
}

int MGetSafeVectorTriple( /* 20040101 */
   mAny,bVertical,nL,nH,nXIndex,nYIndex,nZIndex,pXVec,pYVec,pZVec,pnL,pnH
)
   const MATRIX mAny;
   int bVertical,nL,nH,nXIndex,nYIndex,nZIndex,*pnL,*pnH;
   VECTOR *pXVec,*pYVec,*pZVec;
{
   VECTOR vX,vY,vZ;
   int j,k;

   if (!bVertical) return 0; /* Under Construction */

   MGetVector(mAny,bVertical,nXIndex,nL,nH,pXVec);
   MGetVector(mAny,bVertical,nYIndex,nL,nH,pYVec);
   MGetVector(mAny,bVertical,nZIndex,nL,nH,pZVec);
   vX=VCreate(nL,nH);
   vY=VCreate(nL,nH);
   vZ=VCreate(nL,nH);
   for (j=k=nL;j<=nH;j++) {
      if (IsNaNDouble((*pXVec)[j])) continue;
      if (IsNaNDouble((*pYVec)[j])) continue;
      if (IsNaNDouble((*pZVec)[j])) continue;
      vX[k]=(*pXVec)[j];
      vY[k]=(*pYVec)[j];
      vZ[k]=(*pZVec)[j];
      k++;
   }
   if (k==nL) {
      VDestroy(vX,nL,nH);
      VDestroy(vY,nL,nH);
      VDestroy(vZ,nL,nH);
      *pXVec=*pYVec=*pZVec=(VECTOR)(size_t)(*pnL=*pnH=0);
      return 0;
   }
   VDestroy(*pXVec,nL,nH);
   VDestroy(*pYVec,nL,nH);
   VDestroy(*pZVec,nL,nH);
   *pXVec=vX;
   *pYVec=vY;
   *pZVec=vZ;
   *pnL=nL;
   *pnH=k-1;
   return (nH-nL+1);
}

int MAddVector(
   MATRIX *pmAny,int nRL,int nRH,int nCL,int nCH,VECTOR vAny,int bRightHandSide,
   int *nRHNew,int *nCHNew
   )
{
   MATRIX M;
   VECTOR V;
   int r,c;

   if (!*pmAny) {
      if (bRightHandSide) {
         nCH=nCL;
         M=MCreate(nRL,nRH,nCL,nCH);
         for (r=nRL;r<=nRH;r++) M[r][nCL]=vAny[r];
      } else {
         nRH=nRL;
         M=MCreate(nRL,nRH,nCL,nCH);
         for (c=nCL;c<=nCH;c++) M[nRL][c]=vAny[c];
      }
      *pmAny=M;
   } else {
      if (bRightHandSide) {
         nCH++;
         for (r=nRL;r<=nRH;r++) {
            V=VCreate(nCL,nCH);
            memcpy(V+nCL,(*pmAny)[r]+nCL,sizeof(double)*(nCH-nCL));
            VDestroy((*pmAny)[r],nCL,nCH);
            (*pmAny)[r]=V;
            (*pmAny)[r][nCH]=vAny[r];
         }
      } else {
         nRH++;
         M=salloc(double*,nRH-nRL+1);
         M-=nRL;
         memcpy(M,(*pmAny),sizeof(double*)*(nRH-nRL));
         free(*pmAny);
         *pmAny=M;
         (*pmAny)[nRH]=vAny;
      }
   }
   *nRHNew=nRH;
   *nCHNew=nCH;
   return TRUE;
}

double MGetColMinimum( mAny,nRL,nRH,nCL,nCH,nCol )
   MATRIX mAny;
   int nRL,nRH,nCL,nCH;
   int nCol;
{
   int i;
   double dMin,d;

   dMin=NUMBER_MAX_POSITIVE_DOUBLE;

   if (nCol<nCL || nCH<nCol) return dMin;
   for (i=nRL;IsNaNDouble(mAny[i][nCol])&&i<=nRH;i++);
   if (i>nRH) return dMin;
   dMin=mAny[i][nCol];
   for (i=nRL;i<=nRH;i++) {
      d=mAny[i][nCol];
      if (!IsNaNDouble(d) && dMin>d) dMin=d;
   }
   return dMin;
}

double MGetColMaximum( mAny,nRL,nRH,nCL,nCH,nCol )
   MATRIX mAny;
   int nRL,nRH,nCL,nCH;
   int nCol;
{
   int i;
   double dMax,d;

   dMax=NUMBER_MAX_NEGATIVE_DOUBLE;

   if (nCol<nCL || nCH<nCol) return dMax;
   for (i=nRL;IsNaNDouble(mAny[i][nCol])&&i<=nRH;i++);
   if (i>nRH) return dMax;
   dMax=mAny[i][nCol];
   for (i=nRL;i<=nRH;i++) {
      d=mAny[i][nCol];
      if (!IsNaNDouble(d) && dMax<d) dMax=d;
   }
   return dMax;
}

double MGetColMinAndIndex( mAny,nRL,nRH,nColumn,pnIndex )
   MATRIX mAny;
   int nRL,nRH,nColumn,*pnIndex;
{
   int i;
   double dTarget,d;

   dTarget=NUMBER_MAX_NEGATIVE_DOUBLE;
   if (pnIndex) *pnIndex=nRL-1; // Make trouble intentionally.

   for (i=nRL;IsNaNDouble(mAny[i][nColumn])&&i<=nRH;i++);
   if (i>nRH) return dTarget;
   dTarget=mAny[i][nColumn];
   for (i=nRL;i<=nRH;i++) {
      d=mAny[i][nColumn];
      if (!IsNaNDouble(d) && dTarget>d) {
         dTarget=d;
         if (pnIndex) *pnIndex=i;
      }
   }
   return dTarget;
}

double MGetColMaxAndIndex( mAny,nRL,nRH,nColumn,pnIndex )
   MATRIX mAny;
   int nRL,nRH,nColumn,*pnIndex;
{
   int i;
   double dTarget,d;

   dTarget=NUMBER_MAX_POSITIVE_DOUBLE;
   if (pnIndex) *pnIndex=nRL-1; // Make trouble intentionally.

   for (i=nRL;IsNaNDouble(mAny[i][nColumn])&&i<=nRH;i++);
   if (i>nRH) return dTarget;
   dTarget=mAny[i][nColumn];
   for (i=nRL;i<=nRH;i++) {
      d=mAny[i][nColumn];
      if (!IsNaNDouble(d) && dTarget<d) {
         dTarget=d;
         if (pnIndex) *pnIndex=i;
      }
   }
   return dTarget;
}

MATRIX MRotate( m,nRL,nRH,nCL,nCH )
   MATRIX m;
   int nRL,nRH,nCL,nCH;
{
   int i,j;
   MATRIX mnew;

   mnew=dmatrix(nCL,nCH,nRL,nRH);
   for (i=nRL;i<=nRH;i++) {
      for (j=nCL;j<=nCH;j++) {
          mnew[j][i]=m[i][j];
      }
   }
   return mnew;
}

int MInflate( pMatrix,nRL,nRH,nCL,nCH,nrhNew,nchNew )
 /* Inflate */
   MATRIX *pMatrix;
   int nRL,nRH,nCL,nCH,nrhNew,nchNew;
{
   MATRIX pMtx;
   int i,j;

   pMtx=*pMatrix;
   /* if (nrhNew<=nRH && nchNew<=nCH) return FALSE; 20030428 */
   if (nrhNew>nRH) {
      pMtx=salloc(double*,nrhNew-nRL+1);
      pMtx-=nRL;
      memcpy((char*)&(pMtx[nRL]),(char*)&((*pMatrix)[nRL]),
         sizeof(double*)*(nRH-nRL+1));
      for (i=nRH+1;i<=nrhNew;i++) { /* 20030717 */
         pMtx[i]=salloc(double,nCH-nCL+1);
         memset((char*)(pMtx[i]),0,sizeof(double)*(nCH-nCL+1));
         pMtx[i]-=nCL;
      }
      free(*pMatrix+nRL);
      *pMatrix=pMtx;
   }
   if (nchNew>nCH) {
      double *pVec;
      j=nchNew-nCL+1;
      for (i=nRL;i<=nRH;i++) {
         pVec=salloc(double,j);
         pVec-=nCL;
         memcpy((char*)&(pVec[nCL]),(char*)&(pMtx[i][nCL]),
            sizeof(double)*(nCH-nCL+1));
         memset((char*)&(pVec[nCH+1]),0,
            sizeof(double)*(nchNew-nCH));
         free(pMtx[i]+nCL);
         pMtx[i]=pVec;
      }
      for (i=nRH+1;i<=nrhNew;i++) {
         pMtx[i]=salloc(double,j);
         pMtx[i]-=nCL;
      }
   }
   return TRUE;
}

int MReverseColumn(
   MATRIX mAny,int nRL,int nRH,int nColumnIndex
)
{
   int i,j;
   double d;
   for (i=nRL,j=nRH;i<j;i++,j--) {
      d=mAny[i][nColumnIndex];
      mAny[i][nColumnIndex]=mAny[j][nColumnIndex];
      mAny[j][nColumnIndex]=d;
   }
   return TRUE;
}

int MWriteToFile(
   const char *qFile,const char *qFormat,
   const MATRIX mAny,int nRL,int nRH,int nCL,int nCH
   )
{
   char qFmt[32],qFmtNan[32];
   FILE *o;
   register int i,j;

   if (!(o=fopen(qFile,"w"))) return FALSE;
   sprintf(qFmt," %s",qFormat);
   sprintf(qFmtNan,qFmt,0.0);
   memset(qFmtNan+2,' ',strlen(qFmtNan+2));
   qFmtNan[2]=NUMNULLCHR;
   fprintf(o,"! %s : [%d..%d][%d..%d]\n",qFile,nRL,nRH,nCL,nCH);
   for (i=nRL;i<=nRH;i++) {
      for (j=nCL;j<=nCH;j++) {
         if (IsNaNDouble(mAny[i][j]))
            fprintf(o,qFmtNan);
         else
            fprintf(o,qFmt,mAny[i][j]);
      }
      fprintf(o,"\n");
   }
   fclose(o);
   return (1);
}

void MWriteToStdout( mAny,nRL,nRH,nCL,nCH )
   MATRIX mAny;
   int nRL,nRH,nCL,nCH;
{
   int i,j;
   char *f=" %+1.2E",b[16];

   fprintf(stdout,"![%d..%d][%d..%d]\n",nRL,nRH,nCL,nCH);
   sprintf(b,f,0.0);
   b[1]='#';
   for (i=nRL;i<=nRH;i++) {
      for (j=nCL;j<=nCH;j++) {
         if (IsNaNDouble(mAny[i][j]))
            fprintf(stdout,"%s",b);
         else
            fprintf(stdout,f,mAny[i][j]);
      }
      fprintf(stdout,"\n");
   }
}

int MCreateFromStream( mem,mtrx,rowNo,colNo )
   char *mem;
   double ***mtrx;
   int *rowNo,*colNo;
/*
 * out : matrix[1..rowNo][1..colNo]
 */
{
   char *p,*skip=" ,'\"\\\t\f\n";
#  define DLL_MAX_NO 10000
   DLL *list,**table;
   DLN *node;
   int r=0,c=0,i,j;

   table=salloc(DLL*,DLL_MAX_NO);
   if (!table)
      errExit("table in MCreateFromStream()");

   while (*mem) {
      p=strchr(mem,'\n');
      mem+=p ? p-mem:strlen(mem);
      skipwhite(&p);
      if (!isnumstr(p)) continue;
      DLLOpen(&list);
      DLLAddTokens(list,p,skip);
      DLLDuplicate(list,&table[r]);
      DLLClose(list);
      r++;
      c=MAX(c,list->total);
      if (r>=DLL_MAX_NO)
         errExit("matrix-row > DLL_MAX_NO in MCreateFromStream()");
   }

   *mtrx=dmatrix(1,r,1,c);
   *rowNo=r;
   *colNo=c;

   for (i=1;i<=r;i++)
      for (j=1;j<=c;j++) {
         node=table[i-1]->head;
         while (node) {
            if (isnumchr(*node->tok))
               (*mtrx)[i][j]=atof(node->tok);
            else
               MkNaNDouble((*mtrx)[i][j]);
            node=node->next;
            j++;
         }
         for (;j<=c;j++)
               MkNaNDouble((*mtrx)[i][j]);
         DLLClose(table[i-1]);
      }
   return TRUE;
#  undef DLL_MAX_NO
}

/* 20030821
 + 20030929(-_-) GetPearsonR2() seems to be more reliable with unknown reason.
 * [Numerical Receipes in C,p.503,526*]
 * [Press,Numerical Receipes in C,p.526, Eq.(14.2.13)]
 * Linear correlation coefficient, Pearson's r. */
double GetR2WithChi2( VECTOR vData,int nLow,int nHigh,double dChi2 )
{
   int i,nData;
   double dSum,dAvg,dNVar;
   for (i=nLow,dSum=0.0;i<=nHigh;i++) dSum+=vData[i];
   nData=nHigh-nLow+1;
   dAvg=dSum/nData;
   for (i=nLow,dNVar=0.0;i<=nHigh;i++) dNVar+=pow(vData[i]-dAvg,2.);
   return 1.0-dChi2/dNVar;
}

/* 20030929
 * [Numerical Receipes in C,p.503*,526]
 * Linear correlation coefficient, Pearson's r.
 * Result is consistent with that of Excel. */
double GetPearsonR2( VECTOR vX,VECTOR vY,int nLow,int nHigh )
{
   int i;
   double xsum,ysum,xavg,yavg,numerator,denominator1,denominator2;
   xsum=ysum=0.;
   for (i=nLow;i<=nHigh;i++) {
      xsum+=vX[i];
      ysum+=vY[i];
   }
   xavg=xsum/(nHigh-nLow+1);
   yavg=ysum/(nHigh-nLow+1);
   numerator=denominator1=denominator2=0.;
   for (i=nLow;i<=nHigh;i++) {
      double dx,dy;
      dx=vX[i]-xavg;
      dy=vY[i]-yavg;
      numerator+=dx*dy;
      denominator1+=pow(dx,2.);
      denominator2+=pow(dy,2.);
   }
   return numerator/sqrt(denominator1*denominator2); /* 20030930 */
}

double xfit(
   VECTOR vX,VECTOR vY,int nData,double *yi,double *slope
   /* All vectors based on 1. */
)
{
   VECTOR sig;int i;
	double siga,sigb,chi2,q,r2;

   sig=vector(1,nData);
   for (i=1;i<=nData;i++) sig[i]=1;/* Unweighted data [Numerical Receipes in C,p.526*,529] */

   /* Press,Numerical Receipes in C,p.527 : vY=a+bx */
   fit(vX,vY,nData,sig,1,yi,slope,&siga,&sigb,&chi2,&q);
   free_vector(sig,1,nData);

   { /* 20030929 */
   VECTOR yy=VDuplicate(vY,1,nData);
   for (i=1;i<=nData;i++) yy[i]=*yi+*slope*vX[i];
   r2=GetPearsonR2(vY,yy,1,nData);
   VDestroy(yy,1,nData);
   if (r2>1||r2<0) r2=0;
   }

   return r2;
}

double xxfit( vX,vY,nData,pdYi,pdSlope,nMinFit,dMinR2 )
   VECTOR vX,vY;
   int nData,nMinFit;
   double *pdYi,*pdSlope,dMinR2;
{
   int j,nL,nH;
   double dR20,dR2,dYi,dSlope;

   dR20=0.;

   /* Fit first */
   for (j=1;(j+nMinFit-1)<=nData;j++) {
      dR2=xfit(vX+j-1,vY+j-1,nMinFit,&dYi,&dSlope);
      if (dR2>dR20) {
         dR20=dR2;
         *pdYi=dYi;
         *pdSlope=dSlope;
         nL=j;
         nH=j+nMinFit;
      }
   }

   if (dR20<dMinR2) return dR20;

   /* Expand */
   while (1<nL||nH<nData) {
      if (1<nL) nL--;
      if (nData>nH) nH++;
      dR2=xfit(vX+nL-1,vY+nL-1,nH-nL+1,&dYi,&dSlope);
      if (dR2<dMinR2) break;
      *pdYi=dYi;
      *pdSlope=dSlope;
      dR20=dR2;
   }
   return dR20;
}

double xsvdfit(
   VECTOR vX,VECTOR vY,int nData,VECTOR vOut,int nOut,void (*_svdfit)()
   /* All vectors based on 1 */
)
{
   int i;
   VECTOR sig,w;
   MATRIX u,v;
	double chi2,r2;

   sig=VCreate(1,nData);
   for (i=1;i<=nData;i++) sig[i]=1;/* Unweighted data [Numerical Receipes in C,p.526*,529] */
   u=MCreate(1,nData,1,nOut);
   v=MCreate(1,nOut,1,nOut);
   w=VCreate(1,nOut);
   /* Press,Numerical Receipes in C,p.537 */
   svdfit(vX,vY,sig,nData,vOut,nOut,u,v,w,&chi2,_svdfit);
   VDestroy(sig,1,nData);
   MDestroy(u,1,nData,1,nOut);
   MDestroy(v,1,nOut,1,nOut);
   VDestroy(w,1,nOut);

   /* 20030929 */
   r2=GetR2WithChi2(vY,1,nData,chi2);
   if (r2>1||r2<0) r2=0;

	return r2;
}

double xmrqmin(
   VECTOR vX,VECTOR vY,int nData,VECTOR vGuess,int nGuess,void (*_mrqmin)()
   /* All vectors based on 1 */
)
{
	int i,*ia,itst,k,mfit=nGuess;
	double alamda,chisq,ochisq,*sig,**covar,**alpha,r2;

	ia=ivector(1,nGuess);
	sig=vector(1,nData);
	covar=matrix(1,nGuess,1,nGuess);
	alpha=matrix(1,nGuess,1,nGuess);

	for (i=1;i<=nData;i++) sig[i]=1; /* Unweighted data [Numerical Receipes in C,p.526] */
                                  /* See Numerical Receipes in C,p.529. */
	for (i=1;i<=mfit;i++) ia[i]=i;

   alamda = -1;
   /* Press,Numerical Receipes in C,p.545 : Levenberg-Marguardt method */
   mrqmin (vX,vY,sig,nData,vGuess,nGuess,ia,mfit,covar,alpha,&chisq,_mrqmin,&alamda);
   if (_isnan(chisq)) return 0.; /* 20030901 */
   k=1;
   itst=0;
   for (;;) {
      //Echo(".#%2d: chisq=%.2e alamda=%.2e ",k,chisq,alamda);
      //for (i=1;i<=nGuess;i++) Echo("vGuess[%d]=%.3f ",i,vGuess[i]);
      //Echo("\n");
      k++;
      ochisq=chisq;
      mrqmin (vX,vY,sig,nData,vGuess,nGuess,ia,mfit,covar,alpha,&chisq,_mrqmin,&alamda);
      if (chisq > ochisq)
         itst=0;
      else if (fabs(ochisq-chisq) < 0.1)
         itst++;
      if (itst < 4) continue;
      alamda=0.0;
      mrqmin (vX,vY,sig,nData,vGuess,nGuess,ia,mfit,covar,alpha,&chisq,_mrqmin,&alamda);
      //Echo(".Uncertainties: ");
      //for (i=1;i<=nGuess;i++) Echo("vGuess[%d]=%.3e ",i,sqrt(covar[i][i]));
      //Echo("\n");
      break;
   }

   free_matrix(alpha,1,nGuess,1,nGuess);
	free_matrix(covar,1,nGuess,1,nGuess);
	free_vector(sig,1,nData);
	free_ivector(ia,1,nGuess);

   r2=GetR2WithChi2(vY,1,nData,chisq); /* 20030821+0929 */
   if (r2>1||r2<0) r2=0; /* 20030901 */
   return r2;

   { /* 20030929 */
   double dyda[8],drsq;
   VECTOR yy=VDuplicate(vY,1,nData);
   for (i=1;i<=nData;i++) _mrqmin(vX[i],vGuess,&(yy[i]),dyda,nGuess);
   drsq=GetPearsonR2(vY,yy,1,nData);
   VDestroy(yy,1,nData);
   r2=drsq;
   if (r2>1||r2<0)
      r2=0; /* 20030901 */
   }
   return r2;
}

double xxmrqmin(
   VECTOR vX,VECTOR vY,int nData,VECTOR vGuess,int nGuess,void (*_mrqmin)(),
   int nMinFit,double dMinR2,
   VECTOR *pvAnswer,int *pnRLAnswer,int *pnRHAnswer
)
{
   VECTOR vGuessCopy;
   int j,k,nL,nH;
   double dR2,dRTwo;

   /* Allocate */
   vGuessCopy=VDuplicate(vGuess,1,nGuess);
   *pvAnswer=VCreate(1,nGuess);

   /* Fit first */
   for (j=1;(j+nMinFit-1)<=nData;j++) {
      for (k=1;k<=nGuess;k++) vGuess[k]=vGuessCopy[k];
      dR2=xmrqmin(vX+j-1,vY+j-1,nMinFit,vGuess,nGuess,_mrqmin);
      for (k=1;k<=nGuess;k++) (*pvAnswer)[k]=vGuess[k];
      *pnRLAnswer=j;
      *pnRHAnswer=*pnRLAnswer+nMinFit-1;
      if (dR2>=dMinR2) break;
   }
   if (dR2<dMinR2) { /* 20031006 */
      goto R;
   }

   /* Change initial guess. 20040110 */
   for (k=1;k<=nGuess;k++) vGuessCopy[k]=(*pvAnswer)[k];

   /* Expand data range fit well. 20030721 <- Farther's Birthday */
   nL=*pnRLAnswer;
   nH=*pnRHAnswer;
   while (1<nL||nH<nData) {
      if (1<nL) nL--;
      if (nData>nH) nH++;
      for (k=1;k<=nGuess;k++) vGuess[k]=vGuessCopy[k];
      dRTwo=xmrqmin(vX+nL-1,vY+nL-1,nH-nL+1,vGuess,nGuess,_mrqmin);
      if (dRTwo<dMinR2) break;
      for (k=1;k<=nGuess;k++) (*pvAnswer)[k]=vGuess[k];
      *pnRLAnswer=nL;
      *pnRHAnswer=nH;
      dR2=dRTwo;
   }

   /* Deallocate */
   for (k=1;k<=nGuess;k++) vGuessCopy[k]=vGuess[k]; /* 20040614 */
R: VDestroy(vGuessCopy,1,nGuess);
   return dR2;
}

/******************************************************************************/

double dvalue(o)
int o;
{
	/*
	double d;
	float  f;

	d=pow10((double)o);
	* trick : 43250624 GY *
	f=(float)d;
	d=(double)f;
	return d;
	*/
	char str[16];
	double d;

	sprintf(str, "1.00000e%d", o);
	d = atof(str);
	return d;
}

double atofEx(value, isLessThanZero)
char *value;
int isLessThanZero;
{
	char *p = value, c;
	double d;

	while (isnumchr(*p)) p++;
	c = *p;
	d = atof(value);
	if (isLessThanZero) {
		switch (tolower(c)) {
		case 'a': d *= 1e-18; break;
		case 'f': d *= 1e-15; break;
		case 'p': d *= 1e-12; break;
		case 'n': d *= 1e-09; break;
		case 'u': d *= 1e-06; break;
		case 'm': d *= 1e-03; break;
		}
	}
	else {
		switch (toupper(c)) {
		case 'K': d *= 1e+03; break;
		case 'M': d *= 1e+06; break;
		case 'G': d *= 1e+09; break;
		case 'T': d *= 1e+12; break;
		case 'P': d *= 1e+15; break;
		case 'E': d *= 1e+18; break;
		}
	}
	return d;
}

int order(d)
double d;
{
	char str[16], *e;
	register int i;

	sprintf(str, "%1e", d);
	strtok(str, "e");
	e = strtok(NULL, "e");
	i = atoi(e);
	return(i);
}

#if _MSVSC_ == 6
double round(d)
double d;
{
	if ((d - floor(d)) >= 0.5) return(ceil(d));
	else return(floor(d));
}
#endif

double orderCeil(d, o)
double d;
int o;
{
	register double dd, tmpo;

	tmpo = dvalue(o);
	d /= tmpo;
	dd = ceil(d);
	/* if (d==dd) dd+=1; 2K.0608 */
	return(dd*tmpo);
}

double orderFloor(d, o)
double d;
int o;
{
	register double dd, tmpo;

	tmpo = dvalue(o);
	d /= tmpo;
	dd = floor(d);
	/* if (d==dd) dd-=1; 2K.0608 */
	return(dd*tmpo);
}

double stepRound(value, step)
double value;
double step;
{
	double r;

	r = value - round(value / step)*step;
	return value - r;
	/*
	return step*floor((double)(value/step+0.5));
	*/

	/*
	#define ABS(x) ((x)<0 ? (-(x)):(x))
	r=fmod(value,step);
	if (ABS(r)<=step/2)
	return value-r;
	else
	return step+value-r;
	*/
}

double fnorm(x, mean, stddev)
double x, mean, stddev;
{
	double z;

	z = (x - mean) / stddev;
	return 0.39894228 / stddev*exp(-z*z / 2);
}

double cnorm(x, mean, stddev)
double x, mean, stddev;
{
	/* later, 2016.3.24
	double z,p;

	z=(x-mean)/stddev;
	p=(x<0.0) ? -gammp(0.5,z*z/2.0)/stddev
	:  gammp(0.5,z*z/2.0)/stddev;

	return 0.5+0.5*p;
	*/
	return NAN;
}

/* 2001.0604 */
static double rtbis_argf_var1 = 0.0;
static double rtbis_argf(d)
double d;
{
	return cnorm(d, 0.0, 1.0) - rtbis_argf_var1;
}

/* 2001.0604, two point interpolation/extrapolation */
double twoptint(xa, ya, n, x)
double xa[], ya[], x;
int n;
{
	double s, y;

	if (x<xa[1]) {
		s = xa[2] == xa[1] ? 0.0 : (ya[2] - ya[1]) / (xa[2] - xa[1]);
		y = s*x + ya[1] - s*xa[1];
		return y;
	}
	else if (x >= xa[n]) {
		s = xa[n] == xa[n - 1] ? 0.0 : (ya[n] - ya[n - 1]) / (xa[n] - xa[n - 1]);
		y = s*x + ya[n - 1] - s*xa[n - 1];
		return y;
	}
	while (n-->1) {
		if (x >= xa[n] && x<xa[n + 1]) {
			s = xa[n + 1] == xa[n] ? 0.0 : (ya[n + 1] - ya[n]) / (xa[n + 1] - xa[n]);
			y = s*x + ya[n] - s*xa[n];
			return y;
		}
	}
	MkNaNDouble(y);
	return y;
}

double icnorm(d)
double d;
{
	/* later 2016.3.24
	double x1=-5.0,x2=5.0;
	if (d<cnorm(x1,0.0,1.0)) return x1;
	if (d>cnorm(x2,0.0,1.0)) return x2;
	rtbis_argf_var1=d;
	return rtbis(rtbis_argf,-5.0,5.0,1e-6);
	*/
	return NAN;
}

#if _MSVSC_ ==6

double asinh(x)
double x;
{
	return log(x + sqrt(x*x + 1));
}

double acosh(x)
double x;
{
	return log(x + sqrt(x*x - 1));
}

double atanh(x)
double x; // |x|>=1 error
{
	return (1 / 2 * log((1 + x) / (1 - x)));
}
#endif

/******************************************************************************/

/* https://en.wikipedia.org/wiki/Endianness */
int test_Endianness()
{
	short s;

	s = 0x1234;
	if (((char*)&s)[0] == 0x12
		&& ((char*)&s)[1] == 0x34) {
		printf("Big-Endian ...\n");
	}
	else if (((char*)&s)[1] == 0x12
		&& ((char*)&s)[0] == 0x34) {
		printf("Little-Endian ...\n");
	}
	return (1);
}

/******************************************************************************/
/* yNrecipe.c */
