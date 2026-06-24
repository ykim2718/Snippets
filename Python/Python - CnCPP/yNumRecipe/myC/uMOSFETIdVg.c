/******************************************************************************/
static char THIS_FILE[]="MOSFETIdVg";

const char *MOSFETIdVg_Help=
"[Y.Kim]                                                                     \n"
"2003.0908-0910,1230-31-T_T                                                  \n"
"                                                                            \n"
"[Input]                                                                     \n"
"OPTION=[1-9]                                                                \n"
"!  1=GM-MAX method (linear extraploation method).                           \n"
"!  2=Saturation current method.                                             \n"
"!  3=Transconductance change method.                                        \n"
"!  4=Constant drain current method.                                         \n"
"!  5=Drain conductance / transconductance method.                           \n"
"!  6=Threshold drain current method.                                        \n"
"!  7=Split C-V method.                                                      \n"
"!  8=Subthreshold current method.                                           \n"
"!  9=Quaratic mobility model.                                               \n"
"! 1) For details of OPTION=0-7, Refer to Dieter K. Schroder, Semiconductor Material\n"
"! and Device Characterization,1998,2ed.,pp.242-48.                          \n"
"! 2) For details of OPTION=8, See P.K.McLarty et al,\"A simple parameter extraction\n"
"! method for ultra-thin oxide MOSFETs,\" Solid-State Elec. 38[6]1175-77(1995).\n"
"SUBOPTION=[0|1-9]                                                           \n"
"!  0 : FALSE -> No addition of result vectors. No change in the matrix.     \n"
"!  1-9 : TRUE -> Addition of result vectors. Number accounts for each model.\n"
"XYV|ARGUMENT2=(X,Y,Vds)(X,Y,Vds)...(X,Y,Vds)                                \n"
"! The first of each parentheses is X column index, which value in should be \n"
"! Vg in [V] unit and monotonic.                                             \n"
"! The second is Y column index, which should be Id in [A] unit.             \n"
"! The third parameter Vds should be specified in [V] unit.                  \n"
"ARGUMENT3=COX,WIDTH,LENGTH                                                  \n"
"! COX : [F/cm2].                                                            \n"
"! WIDTH & LENGTH : [um].                                                    \n"
"! Transconductance is computed with this length and width.                  \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! Add TWO new columns of transconductance Gm [A/V] and transconductance     \n"
"! or field-effect mobility [cm2/Vs] at the end of data matrix.              \n"
"! Refer to mobility calculation to N.Arora 1993, p.449.                     ";

const char *MOSFETIdVg_Sample=
"type=MOSFETIdVg                                                             \n"
"option=0 suboption=0 xyv=(1,2,0.1) argument3=1e-6,50,5                      ";

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

/******************************************************************************/

static int GmMaxMethod( ARGUMENTS )
   ARGULIST
{
   int bNMOSFET,nXYTotal,iXY,iXCol,iYCol,i,j,nL,nH,nFit;
   char *qDelimiter=",():;",*pTok;
   VECTOR vXIndex,vYIndex,vVds,vGmMax,vGmMaxVg,vVth,vMobility,vSwing,vSwingVg;
   VECTOR vX,vY,vSlope;
   double dCox,dWidth,dLength,dVds,dValue,dSlope,dSlopeOld,dYi,
      dChi2,dChi2Old;

   vX=vY=vSlope=(VECTOR)0;
   vXIndex=vYIndex=vVds=vGmMax=vGmMaxVg=vVth=vMobility=vSwing=vSwingVg=(VECTOR)0;

   /* Version */
   Echo(" V.1.1");

   /* Check */
   nXYTotal=strtokcount(ARGUMENT2,qDelimiter)/3;
   dCox=fabs(atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,0)));freeEx(pTok);
   dWidth=fabs(atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,1)));freeEx(pTok);
   dLength=fabs(atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,2)));freeEx(pTok);

   /* Calculate */
   NRL=*MRL;
   NRH=*MRH;
   NCL=*MCL;
   NCH=*MCH;
   vXIndex=VCreate(1,nXYTotal);
   vYIndex=VCreate(1,nXYTotal);
   vVds=VCreate(1,nXYTotal);
   vGmMax=VCreate(1,nXYTotal);
   vGmMaxVg=VCreate(1,nXYTotal);
   vVth=VCreate(1,nXYTotal);
   vMobility=VCreate(1,nXYTotal);
   vSwing=VCreate(1,nXYTotal);
   vSwingVg=VCreate(1,nXYTotal);

   nFit=5;

   if (NSUBOPTION) {
      /* Inflate matrix by two : [*][*MCH+1]=>Gm,[*][*MCH+2]=>Mobility */
      *MCH+=2*nXYTotal;
      MInflate(MTX,NRL,NRH,NCL,NCH,NRH,*MCH);
   }

   for (iXY=1;iXY<=nXYTotal;iXY++) {
      iXCol=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,(iXY-1)*3));freeEx(pTok);
      iYCol=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,(iXY-1)*3+1));freeEx(pTok);
      dVds=atof(pTok=strtokbyindex(ARGUMENT2,qDelimiter,(iXY-1)*3+2));freeEx(pTok);
      if (iXCol<NCL||iXCol>NCH||iYCol<NCL||iYCol>NCH) {
         Echo(0,"%s()\nError, index (%d,%d) at <XYV=> is outside of matrix columns [%d..%d]. \n",
            THIS_FILE,iXCol,iYCol,NCL,NCH);
         goto F;
      }
      /* Register index and Vds */
      vXIndex[iXY]=iXCol;
      vYIndex[iXY]=iYCol;
      vVds[iXY]=dVds;
      /* Check NMOST or PMOST */
      dValue=((*MTX)[NRH][iYCol]-(*MTX)[NRL][iYCol])/((*MTX)[NRH][iXCol]-(*MTX)[NRL][iXCol]);
      bNMOSFET=dValue>=0. ? TRUE:FALSE; /* 20030910 */
      /* Allocate vX and vY */
      MGetVector(*MTX,TRUE,iXCol,NRL,NRH,&vX); /* Vgate */
      MGetVector(*MTX,TRUE,iYCol,NRL,NRH,&vY); /* Idrain */
      /* Get slope */
      if (!VGetSlopeVector(vX,vY,NRL,NRH,FALSE,&vSlope)) { /* 20030910 */
         Echo(0,"%s()\nError, cannot extract slope vector from x and y columns.\n",
            THIS_FILE);
         goto F;
      }
      /* Gm.Max. [A/V] */
      if (bNMOSFET) VGetMinMaxValue(vSlope,NRL,NRH,NULL,&dValue); /* [A/V] */
      else VGetMinMaxValue(vSlope,NRL,NRH,&dValue,NULL); /* [A/V]<0 */
      vGmMax[iXY]=dValue;
      /* Vth & Vg@GmMax */
      VGetValueIndexOfMonotonicVector(vSlope,NRL,NRH,vGmMax[iXY],&j); /* Max(Gm) */
      vGmMaxVg[iXY]=vX[j];
      nL=MAX(NRL,j-(nFit>>1));
      nH=MIN(NRH,j+(nFit>>1));
      dChi2=xfit(vX+nL-NRL,vY+nL-NRL,nH-nL+1,&dYi,&dSlope);
      vVth[iXY]=-dYi/dSlope-dVds*0.5*(bNMOSFET ? 1:-1);
      /* Mobility */
      vMobility[iXY]=vGmMax[iXY]/(dCox*dVds*dWidth/dLength);
      /* Swing */
      for (i=NRL;i<=NRH;i++) vY[i]=log10(fabs(vY[i]));
      dSlopeOld=0;
      dChi2Old=1e99;
      for (i=NRL;i<=(NRH-nFit);i++) {
         dChi2=xfit(vX+i-NRL,vY+i-NRL,nFit,&dYi,&dSlope);
         dSlope=fabs(dSlope);
         if (dSlope>dSlopeOld) { /* 20030909 */
            vSwing[iXY]=1e3/dSlope;
            vSwingVg[iXY]=vX[i+nFit/2];
            dSlopeOld=dSlope;
            dChi2Old=dChi2;
         }
      }
      /* Assign */
      if (NSUBOPTION) {
         /* Max(Gm) */
         for (i=NRL;i<=NRH;i++) (*MTX)[i][NCH+iXY*2-1]=vSlope[i];
         /* Mobility */
         dValue=dCox*dVds*dWidth/dLength;
         if (!bNMOSFET) dValue*=-1;
         for (i=NRL;i<=NRH;i++) (*MTX)[i][NCH+iXY*2]=vSlope[i]/dValue;
      }
      /* Release */
      VDestroy(vX,NRL,NRH);
      VDestroy(vY,NRL,NRH);
      VDestroy(vSlope,NRL,NRH);
      vX=vY=vSlope=(VECTOR)0;
   }

   if (NSUBOPTION) {
      Echo(" Matrix [%d..%d][%d..%d] is changed into [%d..%d][%d..%d].\n",
         NRL,NRH,NCL,NCH,NRL,NRH,NCL,*MCH);
      Echo(" Matrix is inflated  by two : [*][%d]=Gm,[*][%d]=Mobility\n",
         *MCH-1,*MCH);
   }

   Echo(" [ #]  X  Y Vd[V] GmMAX[A/V]@Vg[V] Vt[V] M[cm2/Vs] S[mV/d]@Vg[V] \n");
   for (i=1;i<=nXYTotal;i++) {
      Echo(" [%2d] %2d %2d %-5.3g %10.2e@%-5.2f %5.2f %9.1f %7.1f@%-.2f \n",
         i,(int)vXIndex[i],(int)vYIndex[i],vVds[i],vGmMax[i],vGmMaxVg[i],
         vVth[i],vMobility[i],vSwing[i],vSwingVg[i]);
   }

   VDestroy(vXIndex,1,nXYTotal);
   VDestroy(vYIndex,1,nXYTotal);
   VDestroy(vVds,1,nXYTotal);
   VDestroy(vGmMax,1,nXYTotal);
   VDestroy(vGmMaxVg,1,nXYTotal);
   VDestroy(vVth,1,nXYTotal);
   VDestroy(vMobility,1,nXYTotal);
   VDestroy(vSwing,1,nXYTotal);
   VDestroy(vSwingVg,1,nXYTotal);

   return TRUE;
F: if (vXIndex) VDestroy(vXIndex,1,nXYTotal);
   if (vYIndex) VDestroy(vYIndex,1,nXYTotal);
   if (vVds) VDestroy(vVds,1,nXYTotal);
   if (vGmMax) VDestroy(vGmMax,1,nXYTotal);
   if (vGmMaxVg) VDestroy(vGmMaxVg,1,nXYTotal);
   if (vVth) VDestroy(vVth,1,nXYTotal);
   if (vMobility) VDestroy(vMobility,1,nXYTotal);
   if (vSwing) VDestroy(vSwing,1,nXYTotal);
   if (vSwingVg) VDestroy(vSwingVg,1,nXYTotal);
   if (vX) VDestroy(vX,1,nXYTotal);
   if (vY) VDestroy(vY,1,nXYTotal);
   if (vSlope) VDestroy(vSlope,1,nXYTotal);
   return FALSE;
}

static int QuaraticMobilityModel( ARGUMENTS )
   ARGULIST
{
   int nXYTotal,iXY,iXCol,iYCol,bNMOSFET,bAscending,i,j,nL,nH;
   char *qDelimiter=",():;",*pTok;
   VECTOR vXIndex,vYIndex,vVds,vVth,vMobility,vTheta2,vA,vVgStart,vVgStop,vR2;
   VECTOR vX,vY,vSlope1,vSlope2;
   double dCox,dWidth,dLength,dVds,dYi,dSlope,dA,dU0,dVth,dTheta2,dValue;

   /* Version */
   Echo(" V.1.0\n");

   /* Check */
   nXYTotal=strtokcount(ARGUMENT2,qDelimiter)/3;
   dCox=fabs(atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,0)));freeEx(pTok);
   dWidth=fabs(atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,1)));freeEx(pTok);
   dLength=fabs(atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,2)));freeEx(pTok);

   /* Allocate */
   vXIndex=VCreate(1,nXYTotal);
   vYIndex=VCreate(1,nXYTotal);
   vVds=VCreate(1,nXYTotal);
   vVth=VCreate(1,nXYTotal);
   vMobility=VCreate(1,nXYTotal);
   vTheta2=VCreate(1,nXYTotal);
   vA=VCreate(1,nXYTotal);
   vVgStart=VCreate(1,nXYTotal);
   vVgStop=VCreate(1,nXYTotal);
   vR2=VCreate(1,nXYTotal);

   if (NSUBOPTION) {
      /* Inflate matrix by 3 : [*][*MCH+1]=Eq(2),[*][*MCH+2]=Eq(3),[*][*MCH+2]=Theta1 */
      *MCH+=3*nXYTotal;
      MInflate(MTX,*MRL,*MRH,*MCL,NCH,*MRH,*MCH);
   }

   /* Calculate */

   for (iXY=1;iXY<=nXYTotal;iXY++) {
      /* Get input parameters */
      iXCol=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,(iXY-1)*3));freeEx(pTok);
      iYCol=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,(iXY-1)*3+1));freeEx(pTok);
      dVds=atof(pTok=strtokbyindex(ARGUMENT2,qDelimiter,(iXY-1)*3+2));freeEx(pTok);
      /* Allocate vX and vY */
      MGetVector(*MTX,TRUE,iXCol,NRL=*MRL,NRH=*MRH,&vX); /* Vgate */
      MGetVector(*MTX,TRUE,iYCol,NRL=*MRL,NRH=*MRH,&vY); /* Idrain */
      /* Check NMOST or PMOST */
      bNMOSFET=(vY[NRH]-vY[NRL])/(vX[NRH]-vX[NRL])>=0. ? TRUE:FALSE; /* 20030910 */
      /* Check montonic vector is ascending or descending */
      bAscending=vX[NRH]>vX[NRL];
      /* Get Vth with GM-MAX method at first. */
      VGetSlopeVector(vX,vY,NRL,NRH,FALSE,&vSlope1);
      for (i=NRL;i<=NRH;i++) vSlope1[i]=fabs(vSlope1[i]);
      j=VGetMinOrMaxValue(vSlope1,NRL,NRH,TRUE,&dValue);
      nL=MAX(NRL,j-3);
      nH=MIN(NRH,j+3);
      xfit(vX+nL-NRL,vY+nL-NRL,nH-nL+1,&dYi,&dSlope);
      dVth=-dYi/dSlope-fabs(dVds)*0.5;
      if (bNMOSFET) {
         VGetValueIndexOfMonotonicVector(vX,NRL,NRH,dVth,&nL);
         nH=bAscending ? NRH:NRL;
      } else {
         dVth*=-1;
         VGetValueIndexOfMonotonicVector(vX,NRL,NRH,dVth,&nL);
         nH=bAscending ? NRL:NRH;
      }
      if (nH<nL) SWAP(nL,nH);
      VDestroy(vSlope1,NRL,NRH);
      /* Change vector base */
      NRL=nL;
      NRH=nH;
      vVgStart[iXY]=vX[NRL];
      vVgStop[iXY]=vX[NRH];

      /*  Make (d2(1/Id)/d2Vg)^(-1/3) and ... */
      for (i=NRL;i<=NRH;i++) vY[i]=1/vY[i];
      VGetSlopeVector(vX,vY,NRL,NRH,FALSE,&vSlope1);//vSlope1=d(1/Id)/dVg
      VGetSlopeVector(vX,vSlope1,NRL,NRH,FALSE,&vSlope2);//vSlope2=d2(1/Id)/d2Vg
      for (i=NRL;i<=NRH;i++) vY[i]=pow(vSlope2[i],-1./3);//vY=(d2(1/Id)/d2Vg)^(-1/3)
      /* Find Vth */
      xxfit(vX+NRL-1,vY+NRL-1,NRH-NRL+1,&dYi,&dSlope,(NRH-NRL+1)>>1,0.95);
      dVth=-dYi/dSlope;
      dA=pow(dSlope,3.)*2;//A=Cox*U0*Vds*W/L [1/Ohm]
      /* Find mobility U0 */
      dU0=dA/(dCox*dVds*dWidth/dLength);
      /* Find mobility reduction factor theta 2 */
      VGetValueIndexOfMonotonicVector(vX,NRL,NRH,dVth+(bNMOSFET?+0.5:-0.5),&nL);
      nH=((bNMOSFET&&bAscending)||(!bNMOSFET&&!bAscending)) ? NRH:NRL;
      for (i=nL,dValue=0;i<=nH;i++) vX[i]=vSlope1[i]*dA+1/pow(vX[i]-dVth,2.);
      mdian2(vX+nL-1,nH-nL+1,&dTheta2); //See,NR in C,2ed.1992,p.703
      /* Assign */
      vXIndex[iXY]=iXCol;
      vYIndex[iXY]=iYCol;
      vVds[iXY]=dVds;
      vVds[iXY]=dVds;
      vVth[iXY]=dVth;
      vMobility[iXY]=dU0;
      vTheta2[iXY]=dTheta2;
      vA[iXY]=dA;
      if (NSUBOPTION) { // Matrix inflated by 3.
         double dVg,dId,dVtCrit;
         for (i=*MRL;i<NRL;i++) {
            MkNaNDouble((*MTX)[i][NCH+iXY*3-2]);
            MkNaNDouble((*MTX)[i][NCH+iXY*3-1]);
            MkNaNDouble((*MTX)[i][NCH+iXY*3-0]);
         }
         dVtCrit=dVth+ (bNMOSFET ? 0.01:-0.01);
         for (i=NRL;i<=NRH;i++) {
            dVg=(*MTX)[i][iXCol];
            dId=(*MTX)[i][iYCol];
            (*MTX)[i][NCH+iXY*3-2]=vSlope1[i];//d(1/Id)/dVg
            (*MTX)[i][NCH+iXY*3-1]=vSlope2[i];//(d2(1/Id)/d2Vg)^(-1/3)
            if ((bNMOSFET&&dVg>dVtCrit)||(!bNMOSFET&&dVg<dVtCrit))
               (*MTX)[i][NCH+iXY*3-0]=/* Theta 1 */
               dCox*dU0/dId*dWidth/dLength*dVds-1/(dVg-dVth)-dTheta2*(dVg-dVth);
            else {
               MkNaNDouble((*MTX)[i][NCH+iXY*3-0]);
            }
         }
         for (i=NRH+1;i<=*MRH;i++) {
            MkNaNDouble((*MTX)[i][NCH+iXY*3-2]);
            MkNaNDouble((*MTX)[i][NCH+iXY*3-1]);
            MkNaNDouble((*MTX)[i][NCH+iXY*3-0]);
         }
      }
      /* Final check */ { //20040101
      double dVg,dTheta1;
      VECTOR vVg,vId,vT1,vIdCalc;
      MGetSafeVectorTriple(*MTX,TRUE,NRL,NRH,iXCol,iYCol,NCH+iXY*3,&vVg,&vId,&vT1,&nL,&nH);
      vIdCalc=VCreate(nL,nH);
      for (i=nL;i<=nH;i++) {
         dVg=vVg[i];
         dTheta1=vT1[i];
         vIdCalc[i]=dCox*dU0/(1+dTheta1*(dVg-dVth)+dTheta2*pow(dVg-dVth,2.))
            *dWidth/dLength*(dVg-dVth)*dVds;
      }
      vR2[iXY]=GetPearsonR2(vId+nL-1,vIdCalc+nL-1,1,nH-nL+1);
      if (vR2[iXY]<0) vR2[iXY]=0;
      VDestroy(vVg,nL,nH);
      VDestroy(vId,nL,nH);
      VDestroy(vT1,nL,nH);
      VDestroy(vIdCalc,nL,nH);
      }
      /* Release */
      VDestroy(vSlope1,NRL,NRH);
      VDestroy(vSlope2,NRL,NRH);
      VDestroy(vX,*MRL,*MRH);
      VDestroy(vY,*MRL,*MRH);
   }

   Echo("            Vds   Vth    Mobility Const.A   Theta2    R2   Vg Range\n");
   Echo(" [ #]  X  Y [V]   [V]    [cm2/Vs] [1/ohm]   [1/V^2]   []   [V]\n");
   for (i=1;i<=nXYTotal;i++) {
      Echo(" [%2d] %2d %2d %-5.3g %-4.2f  %-8.1f %.2e %.2e %.2f %g/%g\n",
         i,(int)vXIndex[i],(int)vYIndex[i],vVds[i],vVth[i],vMobility[i],vA[i],vTheta2[i],
         vR2[i],vVgStart[i],vVgStop[i]);
   }

   VDestroy(vXIndex,1,nXYTotal);
   VDestroy(vYIndex,1,nXYTotal);
   VDestroy(vVds,1,nXYTotal);
   VDestroy(vVth,1,nXYTotal);
   VDestroy(vMobility,1,nXYTotal);
   VDestroy(vTheta2,1,nXYTotal);
   VDestroy(vA,1,nXYTotal);
   VDestroy(vVgStart,1,nXYTotal);
   VDestroy(vVgStop,1,nXYTotal);
   VDestroy(vR2,1,nXYTotal);

   return TRUE;
}

int MOSFETIdVg( ARGUMENTS )
   ARGULIST
{
   int nXYTotal,iXY,iXCol,iYCol;
   char *qDelimiter=",():;",*pTok;
   VECTOR vXIndex,vYIndex,vVds,vGmMax,vGmMaxVg,vVth,vMobility,vSwing,vSwingVg;
   VECTOR vX,vY,vSlope;
   double dCox,dWidth,dLength,dVds;

   vX=vY=vSlope=(VECTOR)0;
   vXIndex=vYIndex=vVds=vGmMax=vGmMaxVg=vVth=vMobility=vSwing=vSwingVg=(VECTOR)0;

   //Version
   Echo(" V.1.1\n");

   //Check "OPTION="
   if (NOPTION<0) {
      Echo(0,"%s()\nSorry, your option <OPTION=%d> is invalid. See help.\n",
         THIS_FILE,NOPTION);
      return FALSE;
   }

   //Check "ARGUMENT2=" or "XYV="
   nXYTotal=strtokcount(ARGUMENT2,qDelimiter)%3;
   if (nXYTotal%3) {
      Echo(0,"Error, input is not a multiple of 3 at the expression of <XYV=>\n");
      return FALSE;
   }
   nXYTotal/=3;
   for (iXY=1;iXY<=nXYTotal;iXY++) {
      iXCol=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,(iXY-1)*3));freeEx(pTok);
      iYCol=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,(iXY-1)*3+1));freeEx(pTok);
      dVds=atof(pTok=strtokbyindex(ARGUMENT2,qDelimiter,(iXY-1)*3+2));freeEx(pTok);
      if (iXCol<NCL||iXCol>NCH||iYCol<NCL||iYCol>NCH) {
         Echo(0,"%s()\nError, index (%d,%d) at <XYV=> is outside of matrix columns [%d..%d]. \n",
            THIS_FILE,iXCol,iYCol,NCL,NCH);
         return FALSE;
      }
   }

   //Check "ARGUMENT3="
   if (strtokcount(ARGUMENT3,qDelimiter)!=3) {
      Echo(0,"Error, no 3 items at the expression of <ARGUMENT3=>\n");
      return FALSE;
   } else {
      dCox=fabs(atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,0)));freeEx(pTok);
      dWidth=fabs(atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,1)));freeEx(pTok);
      dLength=fabs(atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,2)));freeEx(pTok);
   }

   /* Echo */
   if (NOPTION<=0) NOPTION=1;
   Echo(" Option=%d ",NOPTION);
   switch (NOPTION) {
   case 1 : Echo("GM-MAX method (linear extrapolation method)\n");break;
   case 2 : Echo("Saturation current method.\n");break;
   case 3 : Echo("Transconductance change method.\n");break;
   case 4 : Echo("Constant drain current method.\n");break;
   case 5 : Echo("Drain conductance / transconductance method.\n");break;
   case 6 : Echo("Threshold drain current method.\n");break;
   case 7 : Echo("Split C-V method.\n");break;
   case 8 : Echo("Subthreshold current method.\n");break;
   case 9 : Echo("Quaratic mobility model.\n");break;
   }
   Echo(" Cox[F/cm2]=%g \n",dCox);
   Echo(" W/L[um]=%g/%g \n",dWidth,dLength);
 
   /* Execute */
   switch (NOPTION) {
   case 1 : return GmMaxMethod(ARGUMENTS);
   case 2 : return FALSE;
   case 3 : return FALSE;
   case 4 : return FALSE;
   case 5 : return FALSE;
   case 6 : return FALSE;
   case 7 : return FALSE;
   case 8 : return FALSE;
   case 9 : return QuaraticMobilityModel(ARGUMENTS);
   }
   return TRUE;
}

/******************************************************************************/
/* MOSFETIdVg.c */
