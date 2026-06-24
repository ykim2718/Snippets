/******************************************************************************/

#define MOUDLENAME "JunctionDiodeRegressor()"

const char *JunctionDiodeRegressor_Help=
"[Y.Kim]                                                                     \n"
"2004.2.24-                                                                  \n"
"                                                                            \n"
"[Input]                                                                     \n"
"ARGUMENT=<MODEL>                                                            \n"
"! When <MODEL> is '*', every model is analyzed.                             \n"
"! OCPN : Ortiz-Conde PN junction diode model using Lambert W function.      \n"
"! J [=] A/cm2, Vox [=] V                                                    \n"
"XYT=(x,y,t)(x,y,t)...(x,y,t)                                                \n"
"! The first in parentheses is X vector index, which should be V [V] and monotonic. \n"
"! The second  is Y column index, which should be J [A/cm^2].                \n"
"! The third is temperature in Celcius degree, neither z-index nor floating. \n"
"OPTION=[01][01][01]                                                         \n"
"! 000: No parasitic resistance.                                             \n"
"! 100: Rs (Series resistance) only.                                         \n"
"! 010: Rp1 (Parallel resistance) only.                                      \n"
"! 001: Rp2 (Shunt resistance) only.                                         \n"
"! 110: Rs + Rp1                                                             \n"
"! 101: Rs + Rp2                                                             \n"
"! 011: Rp1 + Rp2                                                            \n"
"! 111: Rs + Rp1 + Rp2                                                       \n"
"SET=<N>                                                                     \n"
"! N [integer] : Defines minimum number of data point to fit.                \n"
"! Should be greater than 3 at least. Default is 5.                          \n"
"RANGE=[<L>,<H>,<G>|(<L>,<H>,<G>)]                                           \n"
"! L [double|*] : Lower limit X for fitting. <*> means data minimum.         \n"
"! H [double|*] : Upper limit X for fitting. <*> means data minimum.         \n"
"! G [double|*] : Lower limit of \"GoodnessOfFit\". Usually 1> and >0.95     \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! See Log window.   ";

const char *JunctionDiodeRegressor_Sample=
"type=JunctionDiodeRegressor                                                 \n"
"argument=OCPN xyt=(1,2,40)(1,3,80)(1,4,120) option=111 set=5 range=0,1,0.97 ";

/******************************************************************************/

#include <math.h>
#include <string.h>
#include "usrfunc.h"
#include "nrecipe.h"
#include "number.h"
#include "tools.h"
#include "str.h"
#include "semiconductor.h"
#include "nr2.h"

extern int Echo();
extern int GetFittingRange(
   VECTOR vX,int nRl,int nRh,int nFitTotal,double dL,double dH,
   int *nL,int *nH
   );

#if !defined(SIGN)
#define SIGN(x)   ((x)>=0 ? 1:-1)
#endif
#if !defined(SQ)
#define SQ(x)   SQUARE(x)
#endif

static char *qConductionModels[]={
   "OCPN"
};
#define MODEL_OCPN        0

/******************************************************************************/

// Usage: y=zbrent(dLambertW,1/e,1e99,1e-6);
static double _dLambertw_z=0.;
static double _dLambertw( double W )
{
   double dReturn=_dLambertw_z-W*exp(W);
  // if (fabs(dReturn)<_dLambertw_tolerance) dReturn=0.;
   return dReturn;
}
static double dLambertw( double z ) // z>=0 and 500>=W(z)>=0
{
   /*
   if (z<0) return MkNegativeMinDouble(z);
   _dLambertw_z=z;
   return zbrent(_dLambertw,0,500,1e-3);
   */
   //Approximate Equation: [2004.2] Private Communication with Enrique Miranda
   if (z<0.1)
      return z-pow(z,2)+1.5*pow(z,3);
   else if (z<500)
      return 0.665*(1+0.0195*log(z+1))*log(z+1)+0.04;
   else
      return  log(z-4)-(1-1/log(z))*log(log(z));
}

static int GetModelTotal()
{
   return noof(qConductionModels);
}

static const char *qGetModelName( int nModelIndex ) /* STATIC */
{
   int nModels;

   nModels=GetModelTotal();
   if (nModelIndex<0||nModelIndex>nModels) return CNULL;
   return qConductionModels[nModelIndex];
}

static char *pGetModelNamesAll()
{
   int j;
   int nTotal=GetModelTotal();
   char *pModels,*pPointer;

   pModels=strdpl(qGetModelName(1));
   for (j=2;j<nTotal;j++) {
      pPointer=strvcat(pModels,",",qGetModelName(j),0);
      freeEx(pModels);
      pModels=pPointer;
   }
   return pModels;
}

static int GetModelIndex( const char *pModel )
{
   int nModelOptionTotal,nModelIndex;
   char qName[128];
   const char *qModelName;

   strcpy2buf(qName,pModel,noof(qName));
   strtoupper(qName);
   nModelOptionTotal=GetModelTotal();
   for (nModelIndex=0;nModelIndex<nModelOptionTotal;nModelIndex++) {
      qModelName=qGetModelName(nModelIndex);
      if (strequ(qName,qModelName)) return nModelIndex;
   }
   return -1;
}

/*----------------------------------------------------------------------------*/

static double _OrtizCondeDiode_Vth=0;
static void _OrtizCondeDiode( x,a,y,dyda,na )
   double x,a[],*y,dyda[];
   int na;
{
   /* x=Voltage,*y=Current */
   double I0=a[1];
   double Eta=a[2];
   double Rs=a[3];
   double Rp1=a[4];
   double Rp2=a[5];
   double EtaVt=Eta*_OrtizCondeDiode_Vth;
   double X=Rp1*Rs/EtaVt/(Rp1+Rs)*exp(Rp1*(x+I0*Rs)/EtaVt/(Rp1+Rs));
   double W=dLambertw(X);
   double DW=W/X/(1+W);
   double Yeta,Yrs,Yrp1,dXdI0,dXdEta,dXdRs,dXdRp1,dXdRp2;
   Yeta=1/Eta;
   Yrs=Rs/(Rp1+Rs);
   Yrp1=Rp1/(Rp1+Rs);
   dXdI0=X*Rp1*Rs/EtaVt/(Rp1+Rs);
   dXdEta=-1/SQ(Eta)*X*(1/Yeta+Rp1*(x+I0*Rs)/EtaVt/(Rp1+Rs));
   dXdRs=Rp1/SQ(Rp1+Rs)*X*(1/Yrs+I0*Rp1/EtaVt);
   dXdRp1=Rs/SQ(Rp1+Rs)*X*(1/Yrp1+(x+I0*Rs)/EtaVt);
   dXdRp2=0.;
   *y=I0*EtaVt/Rs*W+(x-I0*Rp1)/(Rp1+Rs)+x/Rp2;
   dyda[1]=EtaVt/Rs*W+I0*EtaVt/Rs*(dXdI0*DW)-Rp1/(Rp1+Rs);
   dyda[2]=I0*_OrtizCondeDiode_Vth/Rs*W+I0*EtaVt/Rs*(dXdEta*DW);
   dyda[3]=-I0*EtaVt/SQ(Rs)*W+I0*EtaVt/Rs*(dXdRs*DW)-(x-I0*Rp1)/SQ(Rp1+Rs);
   dyda[4]=I0*EtaVt/Rs*(dXdRp1*DW)-(I0*Rs-x)/SQ(Rp1+Rs);
   dyda[5]=-x/SQ(Rp2);
}
static double _OrtizCondeDiode2( double V,double a[] )
{
   double I0,Eta,Rs,Rp1,Rp2,EtaVt,X,W,DW,J;
   if (a[1]<0||1<a[1]) return DBL_MAX;
   if (a[2]<0||10<a[2]) return DBL_MAX;
   if (a[3]<0||a[4]<0||a[5]<0) return DBL_MAX;
   I0=a[1];
   Eta=a[2];
   Rs=a[3];
   Rp1=a[4];
   Rp2=a[5];
   EtaVt=Eta*_OrtizCondeDiode_Vth;
   X=Rp1*Rs/EtaVt/(Rp1+Rs)*exp(Rp1*(V+I0*Rs)/EtaVt/(Rp1+Rs));
   W=dLambertw(X);
   DW=W/X/(1+W);
   J=I0*EtaVt/Rs*W+(V-I0*Rp1)/(Rp1+Rs)+V/Rp2;
   return log(fabs(J));
}

int JunctionDiodeRegressor( ARGUMENTS )
   ARGULIST
{
   int j,k;
   int nModelTotal,nModelIndex,iModelIndex;
   int nXYT,iXYT,nFitTotal,nXCol,nYCol,nRLAnswer,nRHAnswer;
   char *pArgument,*pXYT,*qDelimiter=",()",*pTok,*pL,*pH;
   double dKelvin/*[K]*/,dL,dH,dR2,dR2AtLeast;
   VECTOR vXData,vYData,vXMirror,vYMirror;
   int nVLow,nVHigh;

   /* Version */
   Echo(" V.1.0\n");

   /* Check "ARGUMENT" */ {
      if (strequ(ARGUMENT,"*")) {
         nModelTotal=GetModelTotal();
         pArgument=pGetModelNamesAll();
      } else {
         nModelTotal=strtokcount(ARGUMENT,qDelimiter);
         for (j=0;j<nModelTotal;j++) {
            pTok=strtokbyindex(ARGUMENT,qDelimiter,j);
            k=GetModelIndex(pTok);
            if (k<0) {
               Echo(0,"%s\n\"%s\" is invalid model at the expression of <ARGUMENT=>\n",
                  MOUDLENAME,pTok);
               freeEx(pTok);
               return FALSE;
            }
            freeEx(pTok);
         }
         pArgument=strdpl(ARGUMENT);
      }
   }
   /* Check "XYT" */
   pXYT=strvcat("(",ARGUMENT2,")",0);
   if (chrcount(pXYT,'(')!=chrcount(pXYT,')')) {
      Echo(0,"%s\nNot paired parentheses at the expression of <XYZ=>\n",
         MOUDLENAME);
      free(pXYT);
      return FALSE;
   }
   nXYT=strtokcount(pXYT,qDelimiter);
   if (nXYT%3) {
      Echo(0,"%s\nTotal number is not a muliple of 3 at the expression of <XYT=>\n",
         MOUDLENAME);
      free(pXYT);
      return FALSE;
   }
   /* Check "NSUBOPTION" */
   nFitTotal=NSUBOPTION<10 ? 10:NSUBOPTION;
   /* Check "RANGE" */
   if (strtokcount(SWEEP,qDelimiter)!=3) {
      Echo(0,"%s\nParameters are not counted to 3 at the expression of <RANGE=>\n",
         MOUDLENAME);
      return FALSE;
   }
   pTok=strtokbyindex(SWEEP,qDelimiter,2);
   dR2AtLeast=pTok[0]!='*' ? atof(pTok):0.5; //20031112
   freeEx(pTok);

   /* Echo */
   Echo(" Model=%s min.fit=%d r2=%g \n",ARGUMENT,nFitTotal,dR2AtLeast);

   /* Compute */
   for (iXYT=0;iXYT<nXYT;) {
      int nLBoundary,nHBoundary,nGuess;
      double vGuess[8],vAnswer[8];
      //nXCol,nYCol
      nXCol=atoi(pTok=strtokbyindex(pXYT,qDelimiter,iXYT++));freeEx(pTok);
      nYCol=atoi(pTok=strtokbyindex(pXYT,qDelimiter,iXYT++));freeEx(pTok);
      dKelvin=atof(pTok=strtokbyindex(pXYT,qDelimiter,iXYT++));freeEx(pTok);
      dKelvin+=KKelvin;
      Echo(" [%d] xyt=%d,%d,%.1fK ",(int)(iXYT/3),nXCol,nYCol,dKelvin);
      if (nXCol<NCL||nXCol>NCH||nYCol<NCL||nYCol>NCH) {
         Echo(0,
            "%s\nX(%d) or Y(%d) index is out of range "
            "compared to matrix columns [%d..%d] by the command of <XYT=>.\n",
            MOUDLENAME,nXCol,nYCol,NCL,NCH);
         free(pXYT);
         return FALSE;
      }
      _OrtizCondeDiode_Vth=GetThermalVoltage(dKelvin);
      /* Allocate vXData,vYData,vXMirror,vYMirror,vXMirror,vYCopy */
      MGetSafeVectorPair(*MTX,TRUE,NRL,NRH,nXCol,nYCol,
         &vXData,&vYData,&nLBoundary,&nHBoundary);
      vXMirror=VDuplicate(vXData,nLBoundary,nHBoundary);
      vYMirror=VDuplicate(vYData,nLBoundary,nHBoundary);
      nVLow=nLBoundary;
      nVHigh=nHBoundary;
      /* Find out proper data range */
      VGetMinMaxValue(vXData,nLBoundary,nHBoundary,&dL,&dH);
      pTok=strtokbyindex(SWEEP,qDelimiter,0);
      if (pTok[0]!='*') dL=atof(pTok);
      freeEx(pTok);
      pTok=strtokbyindex(SWEEP,qDelimiter,1);
      if (pTok[0]!='*') dH=atof(pTok);
      freeEx(pTok);
      if (!GetFittingRange(vXData,nLBoundary,nHBoundary,nFitTotal,dL,dH,
         &nLBoundary,&nHBoundary)) {
         Echo("No valid range.\n");
         goto N;
      }
      if ((nHBoundary-nLBoundary+1)<nFitTotal) nFitTotal=nHBoundary-nLBoundary+1;
      /* Echo various parameters */
      pL=dtostr(dL,"%.1z");
      pH=dtostr(dH,"%.1z");
      Echo("range(%dpts)=%s,%s\n",nHBoundary-nLBoundary+1,pL,pH);
      freeEx(pL);
      freeEx(pH);
      /* Fit by model */
      for (iModelIndex=0;iModelIndex<nModelTotal;iModelIndex++) { /* 20030820 */
         int nLFit,nHFit;
         /* Set Model ID */
         pTok=strtokbyindex(pArgument,qDelimiter,iModelIndex);
         nModelIndex=GetModelIndex(pTok);
         freeEx(pTok);
         /* Handle Boundary issue */
         nLFit=nLBoundary;
         nHFit=nHBoundary;
         /* Vector Copy */
         VCopy(vXMirror,vXData,nLFit,nHFit);
         VCopy(vYMirror,vYData,nLFit,nHFit);
         //nGuess,vGuess
         nGuess=5;
         for (k=1;k<=nGuess;k++) vGuess[k]=1;
         vGuess[1]=1e-7;
         {
         int nFit,nTrial,nDataTotal;
         static VECTOR vFitParameter;
         static VECTOR vFitParameterInc;
         static VECTOR vSig;
         double dChi2;
         nFit=5;
         vFitParameter=VCreate(1,nFit);
         vFitParameterInc=VCreate(1,nFit);
         vFitParameter[1]=1e-7;
         vFitParameter[2]=1;
         vFitParameter[3]=1;
         vFitParameter[4]=1e4;
         vFitParameter[5]=1e8;
         vFitParameterInc[1]=1e-6;
         vFitParameterInc[2]=0.1;
         vFitParameterInc[3]=10;
         vFitParameterInc[4]=1e4;
         vFitParameterInc[5]=1e8;
         nDataTotal=nHFit-nLFit+1;
         vSig=VCreate(1,nDataTotal);
         for (k=1;k<=nDataTotal;k++) vSig[k]=1;
         for (k=1;k<=nDataTotal;k++) vYData[k]=log(fabs(vYData[k]));
         nTrial=LinearAndNonlinearFit(
            vXData,vYData,vSig,nDataTotal,
            vFitParameter,vFitParameterInc,nFit,3,
            &dChi2,0,_OrtizCondeDiode2,0);
         nTrial=LinearAndNonlinearFit(
            vXData,vYData,vSig,nDataTotal,
            vFitParameter,vFitParameterInc,nFit,3,
            &dChi2,0,_OrtizCondeDiode2,0);
         VDestroy(vFitParameter,1,nFit);
         VDestroy(vFitParameterInc,1,nFit);
         VDestroy(vSig,1,nDataTotal);
         }
R:       /* Fit first and expand. 20040110 */ {
         VECTOR vAns;
         VChangeBase2(&vXData,&vYData,nLFit,1);
         dR2=xxmrqmin(vXData,vYData,nHFit-nLFit+1,vGuess,nGuess,_OrtizCondeDiode,nFitTotal,dR2AtLeast,
            &vAns,&nRLAnswer,&nRHAnswer);
         nRLAnswer+=(nLFit-1);
         nRHAnswer+=(nLFit-1);
         VChangeBase2(&vXData,&vYData,1,nLFit);
         for (k=1;k<=nGuess;k++) vAnswer[k]=vAns[k];
         VDestroy(vAns,1,nGuess);
         }
         /* Print out */ if (dR2>=dR2AtLeast) {
            const char *qName=qGetModelName(nModelIndex);
            Echo(" %s a=%.2e b=%.2e",qName,vAnswer[1],vAnswer[2]);
            pL=dtostr(vXMirror[nRLAnswer]<vXMirror[nRHAnswer]?vXMirror[nRLAnswer]:vXMirror[nRHAnswer],"%.1z");
            pH=dtostr(vXMirror[nRLAnswer]>vXMirror[nRHAnswer]?vXMirror[nRLAnswer]:vXMirror[nRHAnswer],"%.1z");
            Echo(" r2=%.3f from %d pts (%s..%s)\n",dR2,nRHAnswer-nRLAnswer+1,pL,pH);
            freeEx(pL);
            freeEx(pH);
         }
         /* Adjust fitted range to look up overlap region. 20031006 */ {
            j=nRHAnswer+(nFitTotal>>1)-nFitTotal;
            if (nRLAnswer<j&&(nRLAnswer+nFitTotal)<=nHBoundary) {
               nLFit=j;
               goto R;
            }
         }
      }
      /* Deallocate vXData,vYData,vXMirror */
N:    VDestroy(vXData,nVLow,nVHigh);
      VDestroy(vYData,nVLow,nVHigh);
      VDestroy(vXMirror,nVLow,nVHigh);
      VDestroy(vYMirror,nVLow,nVHigh);
   }

   freeEx(pArgument);
   return TRUE;
}

/******************************************************************************/
/* JunctionDiodeRegressor.c */
