/******************************************************************************/
/*                           file name : semiconductor.c                      */
/*                         description : semiconductor calcus library         */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43360430                             */
/* 4336 0430-0503,0619,0901,____,____,____,____,____,____,____,____,____,____ */
/* 4337 0207,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <math.h>
#include <memory.h>
#include "number.h"
#include "nrecipe.h"
#include "semiconductor.h"

#if !defined(SIGN)
#define SIGN(x)   ((x)>=0 ? 1:-1)
#endif

/******************************************************************************/

double GetThermalVoltage( double dKelvin /* [K] */ )
{  
   return KBoltzman*dKelvin/Qelectron; /* [V] */
}

double GetExtrinsicDebyeLength( /* [K] -> [cm] [Nicollian p.63] */
   double dKelvin,
   double dRelativeDielectricConstant, /* substrate,e.g.silicon */
   double dNextrinsic
   )
{
   double desi=VacPermittivity*dRelativeDielectricConstant;
   return sqrt(desi*KBoltzman*dKelvin/(pow(Qelectron,2)*dNextrinsic));
}

double GetIntrinsicDebyeLength( /* [K] -> [cm]  [Nicollian p.55] */
   double dKelvin,
   double dRelativeDielectricConstant /* substrate,e.g.silicon */
   )
{   
   double dni,dLe;
   dni=GetSiIntrinsicCarrierConc(dKelvin);
   dLe=GetExtrinsicDebyeLength(dKelvin,dRelativeDielectricConstant,dni);
   return dLe/sqrt(2); /* 20030329 */
}

double GetIntrinsicDebyeCapacitance( /* [K] -> [F/cm2] */
   double dKelvin,
   double dRelativeDielectricConstant /* substrate,e.g.silicon */
   )
{
   double desi=VacPermittivity*dRelativeDielectricConstant;
   return desi/GetIntrinsicDebyeLength(dKelvin,dRelativeDielectricConstant);
}

double GetSimpleMosCapacitance( /* [A] -> [F/cm2] */
   double dTox,
   double dRelativeDielectricConstant
   )
{
   /* Oxide dieletric constant, permittivity. */
   double deox=VacPermittivity*dRelativeDielectricConstant;
   return deox/(dTox*cmoverA);
}

double GetSiBulkPotential(
   int bNtype,double dKelvin,double dNsub
)
{
   double dni,dVth,dBulkPotential;

   dni=GetSiIntrinsicCarrierConc(dKelvin);
   dVth=GetThermalVoltage(dKelvin);

   /* [V] [Taur p.25 Eq.2.37] <- always positive [Y.Kim] */
   dBulkPotential=dVth*log(dNsub/dni);
   
   /* [Sze p.363 Eq.1] <- for n-type silicon [Y.Kim] */
   /* [20031228,YKim's Notation] Ub<0 for p-Si(NMOS), Ub>0 for n-Si. */
   if (!bNtype) dBulkPotential=dBulkPotential*-1;

   return dBulkPotential;
}

/* [Y.Kim,20030312]
 * Michael Shur, Physics of Semiconductor Devices, p.41
 * from Blackmore 1982
 * S.Blakemore,"Semiconductor and Other Major Properties of GaAs," J.Appl.Phys.,
 * 53,no.10,pp.R123-R181,Oct.(1982).
 */
double GetSiBandGapEnergy( /* [K] -> [V] */
   double dKelvin
   )
{  
   double dEg,dEgo,dAlpha,dBeta;
   dEgo=1.170; /* [eV] */
   dAlpha=4.73e-4; /* [eV/K^2] */
   dBeta=636; /* [K] */
   dEg=dEgo-dAlpha*sqrt(dKelvin)/(dKelvin+dBeta);
   return dEg;
}

/* [Y.Kim,20031205]
 * N.Arora,
 * MOSFET Models for VLSI Cirucit Simulation,
 * 1993,p.17,Eq.(2.2)
 */
double GetSiBandGapEnergyEx( /* [K] -> [V] */
   double dKelvin
   )
{  
   double dEg;
   if (dKelvin>=250) dEg=1.206-2.73e-4*dKelvin;
   else if (300>dKelvin&&dKelvin>170) dEg=1.1785-9.025e-5*dKelvin-3.05e-7*pow(dKelvin,2);
   else /* 170>=dKelvin */ dEg=1.17+1.059e-5*dKelvin-6.05e-7*pow(dKelvin,2);
   return dEg;
}

/* [Y.Kim,20031205]
 * N.Arora,
 * MOSFET Models for VLSI Cirucit Simulation,
 * 1993,p.19,Eq.(2.5) or Eq.(2.7)
 */
double GetSiIntrinsicCarrierConc( double dKelvin /* [K] */ )
{
   //double dEg=GetSiBandGapEnergyEx(dKelvin);
   double dVth,dni;
   dVth=GetThermalVoltage(dKelvin);
   dni=3.1e16*pow(dKelvin,(double)3/2)*exp(-1.206/(2*dVth)); /* (2.5) */
   //dni=3.9e16*pow(dKelvin,(double)3/2)*exp(-dEg/(2*dVth)); /* (2.6) */
   return dni; /* [/cm^3] */
}

/* Work function is the energy difference between the vacuum level and the
 * Fermi level. [Taur,p.59]. So, its difference value is based on the vacuum
 * level and is contrary to the Fermi level difference. [20030310 Y.Kim]
 * In other words, work function difference equals to Fermi level difference
 * except the opposite sign. [20030310 Y.Kim]
 */
double GetWorkFuncDiffToSiEf( /* [K],[eV],[],[/cm3] -> [V] */
   double dKelvin,double dGateWorkFunc,int bNtype,double dNsub
   )
{
   double dKai,dBandGap,dBulkPotential,dWorkFunc;

   /* [V] Silicon electron affinity [Taur p.59] */
   dKai=4.05;
   /* [V] Silicon band gap */
   dBandGap=GetSiBandGapEnergy(dKelvin);
   dBulkPotential=GetSiBulkPotential(bNtype,dKelvin,dNsub);
   /* [V] [Taur p.60 Eq.2.144] for p-type silicon. */
   /* [20031228,YKim's Notation] Ub<0 for p-Si(NMOS), Ub>0 for n-Si. */
   dWorkFunc=dKai+dBandGap/2-dBulkPotential;
   return dGateWorkFunc-dWorkFunc;
}

int IsNMOS( double dUb )
{
   return dUb<0;
}
/* Y.Kim,20030618,0627
 *                  NMOS     PMOS
 * Bulk             Ub<0     Ub>0
 * Strong Inversion Us>0     Us<0  <-- Us=Vs+Ub
 *                  Vs>-Ub>0 Vs<-Ub<0
 * Weak Inversion   Vs>0     Vs<0  <-- Positive Vs means bands bend downward.
 */
int IsSurfaceStrongInversion( double dUb, double dVs/* =dUs-dUb */ )
{
   int bResult=FALSE;
   if (dUb<0 && dVs>-dUb) /* NMOS */ bResult=TRUE;
   else if (dUb>0 && dVs<-dUb) /* PMOS */ bResult=TRUE;
   return bResult;
}

int IsSurfaceInversion( double dUb, double dVs/* =dUs-dUb */ )
{
   int bResult=FALSE;
   if (dUb<0) /* NMOS */ bResult=dVs>0 ? TRUE:FALSE;
   else if (dUb>0) /* PMOS */ bResult=dVs<0 ? TRUE:FALSE;
   return bResult;
}

/*
 Dieter K.Schroder,"Semicondcutor Material and Device Characterization",
 2ed.,1998,p.350
*/
int GetFlatBandVoltageByHillard(
   VECTOR vVg,VECTOR vCghf, int nLow,int nHigh, double *dVfb)
{
   VECTOR vV,vC,vX,vY;
   double dStep,dError,dSlope1,dSlope2;
   int nCV,nXY,nXYHalf,nIndex,nPosition,nXYStart,nXYEnd,nXYIndex,
      nIndex1,nIndex2;

   *dVfb=0.0;
   dStep=(vVg[nHigh]-vVg[nLow])>=0 ? 0.01:-0.01; /* [V] */
   nCV=1024+1;
   for (dStep/=2;nCV>1024;) { /* 20030521 */
      dStep*=2;
      nCV=(int)ceil((vVg[nHigh]-vVg[nLow])/dStep)+0;
   }
   nXY=7; /* should be odd !!! */

   if (!(nXY%2)) nXY++;
   if ((nHigh-nLow+1)<nXY) return FALSE;
   nXYHalf=nXY>>1;
   
   vV=VCreate(1,nCV);
   vC=VCreate(1,nCV);
   vX=VCreate(1,nXY);
   vY=VCreate(1,nXY);

   for (nIndex=1;nIndex<=nCV;nIndex++)
      vV[nIndex]=vVg[nLow]+(nIndex-1)*dStep;
   for (nIndex=1;nIndex<=nCV;nIndex++) {
      if (!VGetValueIndexOfMonotonicVector(vVg,nLow,nHigh,vV[nIndex],&nPosition)) {
         VDestroy(vV,1,nCV);
         VDestroy(vC,1,nCV);
         VDestroy(vX,1,nXY);
         VDestroy(vY,1,nXY);
         return FALSE;
      }
      nXYStart=nPosition-nXYHalf;
      nXYEnd=nPosition+nXYHalf;
      if (nXYStart<nLow) {
         nXYStart=nLow;
         nXYEnd=nLow+nXY-1;
      }
      if (nXYEnd>nHigh) {
         nXYStart=nHigh-(nXY-1);
         nXYEnd=nHigh;
      }
      for (nXYIndex=nXYStart;nXYIndex<=nXYEnd;nXYIndex++) {
         vX[nXYIndex-nXYStart+1]=vVg[nXYIndex];
         vY[nXYIndex-nXYStart+1]=vCghf[nXYIndex];
      }
      /* Press,Numerical Receipes in C,p.90 */
      polint(vX,vY,nXY,vV[nIndex],&(vC[nIndex]),&dError);
   }
   
   VDestroy(vX,1,nXY);
   VDestroy(vY,1,nXY);

   /* to plot square(1/Cg) versus Vg */
   for (nIndex=1;nIndex<=nCV;nIndex++) {
      vC[nIndex]=pow(1/vC[nIndex],2);
   }

   /* to plot d(square(1/Cg))/dVg versus Vg */
   for (nIndex=1;nIndex<nCV;nIndex++) {
      vC[nIndex]=vC[nIndex+1]-vC[nIndex];
      vC[nIndex]/=vV[nIndex+1]-vV[nIndex];
   }
   vC[nCV]=vC[nCV-1]; /* for simplicity */

   VGetMaxValueIndexOfMonotonicVector(vC,nCV,&nPosition);
   if (nPosition<1||nCV<nPosition) goto E;
   nIndex1=VGetMaxSlopeOfMonotonicVectorByHalfRangeMethod(
      vV,vC,nPosition,&dSlope1);
   nIndex2=VGetMaxSlopeOfMonotonicVectorByHalfRangeMethod(
      vV+nPosition-1,vC+nPosition-1,nCV-nPosition+1,&dSlope2);

   nPosition=dSlope1>dSlope2 ? nIndex1:nIndex2;
   *dVfb=vV[nPosition];

E: VDestroy(vV,1,nCV);
   VDestroy(vC,1,nCV);

   return (1<=nPosition&&nPosition<=nCV) ? TRUE:FALSE;
}

/*
 * Dieter K.Schroder,2ed. 1998,
 * Semiconductor Material and Device Characterization,
 * pp.377-79.
 * 
 * [Y.Kim]
 * 2003,2004.2.8
 */
int GetInterfaceTrapDensityByTerman(
    int bNMOS,
    VECTOR vVgate/*[V]*/,VECTOR vCgtest/*[F/cm2]*/,VECTOR vCgideal/*[F/cm2]*/,
    VECTOR vVsideal/*[eV]*/,int nLow,int nHigh,
    VECTOR *pvDit/*[1/(cm2eV)]*/
)
{
   int nL,nH,i;
   double dHalfEgap,dCox,dV;
   VECTOR vVg,vCgt,vCgi,vVsi,vDVg,vSlope,vDit;

   /* Find silicon band gap region */
   dHalfEgap=GetSiBandGapEnergy(25+KKelvin)/2; /* Assumed room temperature */
   VGetMinOrMaxValue(vCgtest,nLow,nHigh,TRUE,&dCox);
   nL=nLow; while (fabs(vVsideal[nL])>dHalfEgap) nL++;
   nH=nHigh;while (fabs(vVsideal[nH])>dHalfEgap) nH--;
   if (nL>nH) SWAP(nL,nH);
   if ((nH-nL+1)<5) {
      *pvDit=0;
      return FALSE;
   }

   /* Change Vg steps into smaller steps */
   if (fabs(vVgate[nL]-vVgate[nL+1])>0.01) {
      double dXStart,dXStop,dXStep;
      int rL,rH;
      dXStart=vVgate[nL];
      dXStop=vVgate[nH];
      dXStep=(dXStart<dXStop) ? 0.01:-0.01;
      VChangeXStepsInARange(vVgate,vCgtest,nLow,nHigh,&vVg,&vCgt,&rL,&rH,dXStart,dXStop,dXStep);
      VDestroy(vVg,rL,rH);
      VChangeXStepsInARange(vVgate,vCgideal,nLow,nHigh,&vVg,&vCgi,&rL,&rH,dXStart,dXStop,dXStep);
      VDestroy(vVg,rL,rH);
      VChangeXStepsInARange(vVgate,vVsideal,nLow,nHigh,&vVg,&vVsi,&rL,&rH,dXStart,dXStop,dXStep);
      nL=rL;
      nH=rH;
   } else {
      nL=nLow;
      nH=nHigh;
      vVg=VDuplicate(vVgate,nL,nH);
      vCgt=VDuplicate(vCgtest,nL,nH);
      vCgi=VDuplicate(vCgideal,nL,nH);
      vVsi=VDuplicate(vVsideal,nL,nH);
   }
   
   /* Figure out delta of gate voltage */
   vDVg=VCreate(nL,nH);
   for (i=nL;i<=nH;i++) {
      if (!VGetInterpolatedYValueWithXYVectors(vCgi[i],vCgt,vVg,nL,nH,5,&dV)) {
         MkNaNDouble(vDVg[i]);
         continue;
      }
      vDVg[i]=bNMOS ? dV-vVg[i]:vVg[i]-dV; /* should be positive */
   }

   /* Compute d(delta-Vg)/dVs */
   i=nL;
   while(IsNaNDouble(vVsi[i])||IsNaNDouble(vDVg[i])) i++;
   memcpy(&(vVsi[nL]),&(vVsi[i]),sizeof(double)*(nH-i+1));
   memcpy(&(vDVg[nL]),&(vDVg[i]),sizeof(double)*(nH-i+1));
   nH+=nL-i;
   while(IsNaNDouble(vVsi[nH])||IsNaNDouble(vDVg[nH])) nH--;
   VGetSlopeVector(vVsi,vDVg,nL,nH-nL+1,FALSE,&vSlope);

   /* Calculate Dit */
   vDit=VCreate(nL,nH);
   for (i=nL;i<=nH;i++) {
      vDit[i]=dCox/Qelectron*vSlope[i];
      vDit[i]=fabs(vDit[i]); /* fabs() -> Urawaza of YKim */
   }

   /* Assign */
   (*pvDit)=VCreate(nLow,nHigh);
   for (i=nLow;i<=nHigh;i++) {
      if (!VGetInterpolatedYValueWithXYVectors(vVgate[i],vVg,vDit,nL,nH,5,&dV)) {
         MkNaNDouble((*pvDit)[i]);
         continue;
      }
      (*pvDit)[i]=dV;
   }

   /* Deallocate */
   VDestroy(vVg,nL,nH);
   VDestroy(vCgt,nL,nH);
   VDestroy(vCgi,nL,nH);
   VDestroy(vVsi,nL,nH);
   VDestroy(vDVg,nL,nH);
   VDestroy(vSlope,nL,nH);
   VDestroy(vDit,nL,nH);

   return TRUE;
}

/******************************************************************************/
/* semiconductor.c */
