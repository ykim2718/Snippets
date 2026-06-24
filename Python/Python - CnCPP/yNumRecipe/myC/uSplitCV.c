/******************************************************************************/
static char THIS_FILE[]="SplitCV";

const char *SplitCV_Help=
"[Y.Kim]                                                                     \n"

"2003.0904-0910 Created while Hendri measures in a way of SPLIT-CV.          \n"
"2003.1231 Capactiance regression routine is added. Backbone is not changed. \n"
"2004.1222-23 Only the best mobility is printed.                             \n"
"                                                                            \n"
"[Input]                                                                     \n"
"ARGUMENT1=<CV-FILE>                                                         \n"
"! 1st column : Vgate [V]. Should be monotonic.                              \n"
"! 2nd column : Cgate [F]. Note Cgc only. Qd from Cgb is computed.           \n"
"! NMOSFET or PMOSFET is determined by this data internally.                 \n"
"ARGUMENT2=<JV-FILE>                                                         \n"
"! 1st column : Vdrain [V]. Should be monotonic.                             \n"
"! 2nd,3rd,... columns : Idrain [A].                                         \n"
"! WATCH-OUT: Count of drain current columns MUST match that from SWEEP.     \n"
"ARGUMENT3=CV-WIDTH,CV-LENGTH,JV-WIDTH,JV-LENGTH,KEVLIN,NSUB                 \n"
"! CV- WIDTH & LENGTH : [um]. Gate width and length in layout (drawn).       \n"
"! JV- WIDTH & LENGTH : [um]. Gate width and length of CHANNEL.              \n"
"! KELVIN : [K]. Environment temperature in Kevlin scale.                    \n"
"! NSUB : [/cm^3]. Substrate doping concentration.                           \n"
"ARGUMENT4=[<Vg>,<C1>,<D1>,<C2>,<D2>:<F1>,<F2>|<iVg>,<iCg>]                  \n"
"! Same as the options of <argument=> in TwoFreqCapacitanceModel when 7 arguments.      \n"
"! If you donot want to use TwoFreqCapacitanceModel, Specify indexses of both \n"
"! iVg(Vgate) and iCg(Cgate) directly.                                       \n"
"SWEEP=<VGSTART>,<VGSTOP>,<VGSTEP>                                           \n"
"! VGSTART: [double] Gate start voltage for the first column of drain current.\n"
"! VGSTOP: [double] Gate stop voltage for the last column of drain current.  \n"
"! VGSTEP: [double] Gate step gate voltage.                                  \n"
"! Number of step is determined by (STOP-START)/STEP+1.                      \n"
"! Describe Vgate for each columun of J-V file. MUST be matched to JV-FILE.  \n"
"OPITON=[[0-9][0-9][01]]                                                     \n"
"! 1st digit: Expand both end of Vgs range for Eeff(Vgs) by [0-9]x<VGSTEP>.  \n"
"! 2nd digit: Number of interpolated points between the two data.            \n"
"! 3rd digit: [Boolean] true or false for the following                      \n"
"!      If FALSE(0), Cox is computed with CV-WIDTH and CV-LENGTH.            \n"
"!   Capacitance is substracted by Min(Capacitance) after Cox calculation,   \n"
"!   and then, substracted for Qi calculation.                               \n"
"!      If TRUE(1) : Cox is computed with JV-WIDTH and JV-LENGTH.            \n"
"!   Since two values mean effective dimension of channel area, this ratio and \n"
"!   capactiance ratio should be equal if you have good measurement data.    \n"
"!   Especially this is highly recommended if you have innant capactiance offset.\n"
"! Note: <OPTION=000> or <OPTION=001> does not add any new points.           \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! Create new data matrix, whose first column is Vgate, the second is Eeff,  \n"
"! the third is effective mobility Meff, and the other columns are mobilities\n"
"! calculated from C-V and J-V.                                              \n"
"! [*][1]=Vgate[V], [*][2]=Eeff[MV/cm], [*][3]=Univ.-Mobility[cm2/Vs],       \n"
"! [*][4]=Computed-Mobility.                                                 ";

const char *SplitCV_Sample=
"type=SplitCV                                                                \n"
"argument=<CV-FILE> argument2=<JV-FILE>                                      \n"
"argument3=50,5,50,5,300,4.1,1.34e15 argument4=1,2 sweep=0,2,0.25            ";

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

int SplitCV( ARGUMENTS )
   ARGULIST
{
   MATRIX mCV,mJV,mQi,mGd,mOut;
   int bNMOSFET,nRHCV,nCHCV,nRHJV,nCHJV,nRHQi,nCHQi,nRHGd,nCHGd,nRH,nRL,nCH,nCL,
      nExpandBoth,nInterpolate,bJVWidthLength,
      nIndex,i,j,k;
   char *qDelimiter=",():;",*pAddr;
   VECTOR vX,vY,vSlope;
   double dStartVg,dStopVg,dStepVg,dStartVd,dStopVd,dStepVd,
      dWidthCV,dLengthCV,dWidthJV,dLengthJV,
      dMin,dMax,dR2,dR2Old,dSlopeQi,dYiQi,dVal,dCRatio,dARatio;
   double dKelvin,dNsub,dTox,dCox,dni,dVthermal,dUb,dVth,dVt0,dVfb,dWgate,dWsub;

   //Version
   Echo(" V.1.3");

   mCV=mJV=mQi=mGd=mOut=(MATRIX)0;
   nRHCV=nCHCV=nRHJV=nCHJV=nRHQi=nCHQi=nRHGd=nCHGd=nRH=nRL=nCH=nCL=0;

   //Check "ARGUMENT1"
   if (!myDoesFileExist(ARGUMENT)) {
      Echo(0,"%s()\nError, CV-FILE is missed, whose name is \"%s\".\n",THIS_FILE,ARGUMENT);
      goto F;
   }
   if (!GetMtrxFrFile(ARGUMENT,&mCV,&nRHCV,&nCHCV)) {
      Echo(0,"%s()\nError, CV-FILE is abnormal, whose name is \"%s\".\n",THIS_FILE,ARGUMENT);
      goto F;
   }
   if (nCHCV==2) { /* [*][1]=Vg,[*][2]=Cg,[*][3]=Qi. Not 3rd column is reserved. */
      MInflate(&mCV,1,nRHCV,1,nCHCV,nRHCV,nCHCV+1);
      nCHCV++;
   }
   //Check "ARGUMENT2"
   if (!myDoesFileExist(ARGUMENT2)) {
      Echo(0,"%s()\nError, JV-FILE is missed, whose name is \"%s\".\n",THIS_FILE,ARGUMENT2);
      goto F;
   }
   if (!GetMtrxFrFile(ARGUMENT2,&mJV,&nRHJV,&nCHJV)) {
      Echo(0,"%s()\nError, JV-FILE is abnormal, whose name is \"%s\".\n",THIS_FILE,ARGUMENT2);
      goto F;
   }
   MGetMinMaxValue(mJV,TRUE,1,1,nRHJV,FALSE,&dMin,&dMax);
   dStartVd=dMin;
   dStopVd=dMax;
   dStepVd=(dMax-dMin)/10;
   //Check "ARGUMENT3"
   if (strtokcount(ARGUMENT3,qDelimiter)!=6) {
      Echo(0,"%s()\nError, no 6 items at the expression of <ARGUMENT3=>\n",THIS_FILE);
      goto F;
   }
   for (nIndex=0;nIndex<6;nIndex++) {
      pAddr=strtokbyindex(ARGUMENT3,qDelimiter,nIndex);
      switch (nIndex) {
      case 0 : dWidthCV=atof(pAddr);break;
      case 1 : dLengthCV=atof(pAddr);break;
      case 2 : dWidthJV=atof(pAddr);break;
      case 3 : dLengthJV=atof(pAddr);break;
      case 4 : dKelvin=atof(pAddr);break;
      case 5 : dNsub=atof(pAddr);break;
      }
      freeEx(pAddr);
   }
   if (dKelvin<0) dKelvin=300;
   if (dWidthCV*dLengthCV*dWidthJV*dLengthJV==0) {
      Echo(0,"%s()\nError, zero value is not found at <ARGUMENT3=%g,%g,%g,%g>\n",
         THIS_FILE,dWidthCV,dLengthCV,dWidthJV,dLengthJV);
      goto F;
   }
   dWidthCV*=1e-4;  /* [um] -> [cm] */
   dLengthCV*=1e-4; /* [um] -> [cm] */
   dWidthJV*=1e-4;  /* [um] -> [cm] */
   dLengthJV*=1e-4; /* [um] -> [cm] */

    //Check "ARGUMENT4"
   k=strtokcount(ARGUMENT4,qDelimiter);
   if (k!=2&&k!=7) {
      Echo(0,"%s()\nError, no 2 or 7 items at the expression of <ARGUMENT4=>\n",THIS_FILE);
      goto F;
   }
   //Check "SWEEP"
   if (strtokcount(SWEEP,qDelimiter)!=3) {
      Echo(0,"%s()\nError, no 3 arguments at the expression of <SWEEP=>\n",THIS_FILE);
      goto F;
   }
   for (nIndex=0;nIndex<3;nIndex++) {
      pAddr=strtokbyindex(SWEEP,qDelimiter,nIndex);
      switch (nIndex) {
      case 0 : dStartVg=atof(pAddr);break; /* [V] Gate voltage */
      case 1 : dStopVg=atof(pAddr);break; /* [V] Gate voltage */
      case 2 : dStepVg=atof(pAddr);break; /* [V] Gate voltage */
      }
      freeEx(pAddr);
   }
   if (dStartVg>=dStopVg||dStepVg==0||((dStopVg-dStartVg)/dStepVg)>1e3) {
      Echo(0,"%s()\nError, incorrect are 3 arguments of <SWEEP=%g,%g,%g>\n",
         THIS_FILE,dStartVg,dStopVg,dStepVg);
      goto F;
   }
   k=(int)((dStopVg-dStartVg)/dStepVg)+1;
   if (k!=(nCHJV-1)) {
      Echo(0,"%s()\nError, SWEEP count %d do not match current column count %d of JV-FILE.\n",
         THIS_FILE,k,nCHJV-1);
      goto F;
   }
   /* Check "OPTION" */
   nExpandBoth=(int)(NOPTION-NOPTION%100)/100;
   nInterpolate=(int)(NOPTION%100-NOPTION%10)/10;
   bJVWidthLength=NOPTION%10;

   /* Echo */
   Echo("\n");
   Echo(" CV-file=\"%s\"\n",ARGUMENT);
   Echo(" JV-file=\"%s\"\n",ARGUMENT2);
   Echo(" W/L dimensions [um]: 1) %g/%g for CV, 2) %g/%g for JV.\n",
      dWidthCV*1e4,dLengthCV*1e4,dWidthJV*1e4,dLengthJV*1e4);
   Echo(" Vgate(start,stop,step)=%.2f,%.2f,%.2fV Kelvin=%.1fK Nsub=%.2e/cm3\n",
      dStartVg,dStopVg,dStepVg,dKelvin,dNsub);
   Echo(" Option=%d\n",NOPTION);

   /* Check whether NMOSFET or PMOSFET is. */
   bNMOSFET=(mCV[nRHCV][2]-mCV[1][2])*(mCV[nRHCV][1]-mCV[1][1])>0 ? TRUE:FALSE;
   if ((mJV[nRHJV][2]-mJV[1][2])*(mJV[nRHJV][1]-mCV[1][1])<0) {
      Echo(0,"%s()\nError, C-V file is for %c-MOSFET, while J-V file is %c-MOSFET.\n",
         THIS_FILE,bNMOSFET?'n':'p',bNMOSFET?'p':'n');
      goto F;
   }
   Echo(" %sMOSFET.\n",bNMOSFET ? "N":"P");

   /* TwoFreqCapacitanceModel or else ... */
   if (strtokcount(ARGUMENT4,qDelimiter)==7) {
      ARGULIST4USER
      extern int TwoFreqCapacitanceModel();
      char *pAddr;
      uMTX=mCV;
      uMRL=1;uMRH=nRHCV;uMCL=1;uMCH=nCHCV;
      uNRL=uMRL;uNRH=uMRH;uNCL=uMCL;uNCH=uMCH;
      uNOPTION='c';
      uNSUBOPTION=1;
      uARGUMENT=ARGUMENT4;
      Echo(" TwoFreqCapacitanceModel() {\n");
      if (!TwoFreqCapacitanceModel(ARGUMENTS4USER)) goto F;
      Echo(" }\n");
      k=atoi(pAddr=strtokbyindex(ARGUMENT4,qDelimiter,0));freeEx(pAddr);
      mCV=MCreate(1,nRHCV,1,nCHCV=2);
      for (i=1;i<=nRHCV;i++) {
         mCV[i][1]=uMTX[i][k]; /* Vg [V] */
         mCV[i][2]=uMTX[i][uMCH]; /* Cg [F] */
      }
      MDestroy(uMTX,uMRL,uMRH,uMCL,uMCH);
   } else { /* == 2 */
      char *pAddr;
      j=atoi(pAddr=strtokbyindex(ARGUMENT4,qDelimiter,0));freeEx(pAddr);
      k=atoi(pAddr=strtokbyindex(ARGUMENT4,qDelimiter,1));freeEx(pAddr);
      MGetVector(mCV,TRUE,j,1,nRHCV,&vX); /* Vgate */
      MGetVector(mCV,TRUE,k,1,nRHCV,&vY); /* Cgate */
      MDestroy(mCV,1,nRHCV,1,nCHCV);
      mCV=MCreate(1,nRHCV,1,nCHCV=2);
      for (i=1;i<=nRHCV;i++) {
         mCV[i][1]=vX[i]; /* Vg [V] */
         mCV[i][2]=vY[i]; /* Cg [F] */
      }
      VDestroy(vX,1,nRHCV);
      VDestroy(vY,1,nRHCV);
      Echo(" No capacitance correction : Vg=CV[*][%d], Cg=CV[*][%d]\n",j,k);
   }

   /* Check capacitance measurement error primarily due to offset. 20031231AM02:14 */
   MGetMinMaxValue(mCV,TRUE,2,1,nRHCV,FALSE,&dMin,&dMax);
   dCRatio=dMin/dMax;
   dARatio=1-(dWidthJV*dLengthJV)/(dWidthCV*dLengthCV);
   Echo(" C-Ratio=Min(C)/Max(C)=%.2e/%.2e=%.2f\n",dMin,dMax,dCRatio);
   Echo(" A-Ratio=(1-Area(JV)/Area(CV))=%.2f\n",dARatio);
   dVal=fabs(dARatio-dCRatio)/dCRatio;
   if (dVal>0.1&&!bJVWidthLength) {
      Echo(" WATCH-OUT! Capacitance ratio could not match area ratio well.\n");
      Echo(" Setting OPTION=##1 is highly recommended.\n");
   }

   /* Change unit of mCV[*][2] into [F/cm2]. */
   if (bJVWidthLength) {
      /* Cut Cov(i.e.,Min(C)) off and figure out Cox over channel region [fF/cm2]. */
      MGetMinMaxValue(mCV,TRUE,2,1,nRHCV,FALSE,&dMin,&dMax);
      for (i=1;i<=nRHCV;i++) mCV[i][2]-=dMin;//Cut-off overlap and parasitic capacitance.
      dVal=dWidthJV*dLengthJV;
      for (i=1;i<=nRHCV;i++) mCV[i][2]/=dVal;
      Echo(" Capacitance(Cgc) is substracted by MIN(C).\n");
      Echo(" And divided by JV-area (channel area).\n");
   } else {
      dVal=dWidthCV*dLengthCV;
      for (i=1;i<=nRHCV;i++) mCV[i][2]/=dVal;
      Echo(" Capacitance(Cgc) is divided by CV-area (gate electrode area).\n");
      Echo(" And will be substracted by MIN(C) after Cox fitting.\n");
   }
   /* Transform current in [Aum/um], i.e. I*L/W : mJV[*][2..nCHJV] */
   dVal=dLengthJV/dWidthJV;
   for (i=1;i<=nRHJV;i++) { for (j=2;j<=nCHJV;j++) mJV[i][j]*=dVal; }

   /* MosCapacitorRegressor */ { //20031230
      ARGULIST4USER
      extern int MosCapacitorRegressor();
      char qText[62];
      uMTX=mCV;
      uMRL=1;uMRH=nRHCV;uMCL=1;uMCH=nCHCV;
      uNRL=uMRL;uNRH=uMRH;uNCL=uMCL;uNCH=uMCH;
      uNOPTION=110;//PiecewiseModel+HF+woDeepDepletion
      uNSUBOPTION=0;//Don't add any result vector into the matrix.
      sprintf(qText,"%cmos,%.1f,*,*,*,*",bNMOSFET?'p':'n',dKelvin-KKelvin);//Exchange minority carrier type to fit.
      uARGUMENT=strdpl(qText);
      uARGUMENT2="1,2";
      uSWEEP="*,*";
      Echo(" MosCapacitorRegressor() {\n");
      if (!MosCapacitorRegressor(ARGUMENTS4USER)) goto F;
      Echo(" }\n");
      if (uOUTTOT!=4) {
         Echo(0,"%s()\nError, MosCapacitorRegressor() is changed. Cannot execute further.\n",
            THIS_FILE);
         free(uARGUMENT);
         if (uOUTVEC) VDestroy(uOUTVEC,0,uOUTTOT);
         goto F;
      }
      dWgate=uOUTVEC[0];
      dTox=uOUTVEC[1];
      dCox=GetSimpleMosCapacitance(dTox,RDCOxide);
      free(uARGUMENT);
      VDestroy(uOUTVEC,0,uOUTTOT);
   }
   Echo(" Cox[F/cm2]=%s (EOT[A]=%.2f)\n",pAddr=dtostre(dCox,2),dTox);
   freeEx(pAddr);
   dVal=MGetColMaximum(mCV,1,nRHCV,1,2,2)/dCox; //20041225PM11:58
   if (dVal<0.9||dVal>1.5) {
      char *p1,*p2;
      dVal*=dCox;
      Echo(" Warning: Cox(EOT) from MosCapacitorRegressor() is doubtful!\n");
      Echo(" Warning: Cox(%s) is replaced with %s.\n",p1=dtostre(dCox,2),p2=dtostre(dVal,2));
      freeEx(p1);
      freeEx(p2);
   }

   if (!bJVWidthLength) { //20031231AM2:40
      /* Cut Cov(i.e.,Min(C)) off and figure out Cox over channel region [fF/cm2]. */
      dMin=MGetColMinAndIndex(mCV,1,nRHCV,2,&j);
      for (i=1;i<=nRHCV;i++) mCV[i][2]-=dMin;//Cut-off overlap and parasitic capacitance.
      //20031230 dCox=dMax-dMin; /* TERRIBLY IMPORTANT 20030909 */
      /* Remove possible error (floating bulk,parasitic cap. and overlap cap.). 2004103 */
      if (bNMOSFET) for (i=1;i<=j;i++) mCV[i][2]=0.; /* Should be zero theoretically */
      else for (i=j;i<=nRHCV;i++) mCV[i][2]=0.; /* Should be zero theoretically */
   }

   /* Allocate mQi and integrate C-V to get Qi[C/cm2] */
   mQi=MCreate(1,nRHQi=nRHCV,1,nCHQi=2); //[][1]=Vgs,[][2]=Qi
   for (i=1;i<nRHCV;i++) {
      mQi[i][1]=mCV[i][1];
      mQi[i][2]=fabs((mCV[i+1][2]+mCV[i][2])/2*(mCV[i+1][1]-mCV[i][1]));
   }
   mQi[i][1]=mCV[i][1];/* i=nRHCV */
   mQi[i][2]=fabs(mQi[i-1][2]+(mQi[i-1][2]-mQi[i-2][2])); /* i=nRHCV */
   for (i=2;i<=nRHCV;i++) mQi[i][2]+=mQi[i-1][2];

   /* Figure out slope and intercept of Qi for Vgate above CV range. */
   MGetVector(mQi,TRUE,1,1,nRHQi,&vX); /* Vgate */
   MGetVector(mQi,TRUE,2,1,nRHQi,&vY); /* Qi */
   dR2Old=0.;
   if (bNMOSFET) {
      for (i=(nRHCV>>1);i<nRHCV;i++) {
         j=i-1;
         dR2=xfit(vX+j,vY+j,nRHCV-j,&dYiQi,&dSlopeQi);
         if (dR2<dR2Old||dR2>0.999) break;
         dR2Old=dR2;
      }
   } else { /* PMOSFET */
      for (i=(nRHCV>>1);i>1;i--) {
         j=i-1;
         dR2=xfit(vX+j,vY+j,nRHCV-j,&dYiQi,&dSlopeQi);
         if (dR2<dR2Old||dR2>0.999) break;
         dR2Old=dR2;
      }
   }
   VDestroy(vX,1,nRHCV);
   VDestroy(vY,1,nRHCV);

   /* Threshold Voltage : Vth */
   /* [YKim,20040103] Vth is redeifined as Vg when Qi(Vg)=0. */
   dVth=-dYiQi/dSlopeQi;

   /* Flat-band Voltage : Vfb */ 
   dni=GetSiIntrinsicCarrierConc(dKelvin);
   dVthermal=GetThermalVoltage(dKelvin);
   /* Nicollian,p.52. -> [Ef-Ei(B)]/kT Nicollian,p.50 */
   dUb=log(dNsub/dni)*(bNMOSFET ? -1:1); /* Ub<0 for p-Si(NMOS), Ub>0 for n-Si. */
   /* Taur,p.119,Eq.(3.20). */
   dVt0=2*-dUb*dVthermal+sqrt(4*RDCSilicon*VacPermittivity*Qelectron*dNsub*-dUb*dVthermal)/dCox;
   dVfb=dVth-dVt0;

   /* Substrate work function */ {
   double dKai=4.05; /* [V] Silicon electron affinity [Taur p.59] */
   double dEgap=GetSiBandGapEnergy(dKelvin); /* [V] Silicon band gap */
   dWsub=dKai+dEgap/2-dUb*dVthermal;/* [V] [Taur p.60 Eq.2.144] for p-type silicon. */
   }

   /* Echo Vth, Vfb, and related results */
   Echo(" Vthermal=%.1fmV ni=%.2e/cm3 Ub=%.1f(%.2fV) Wsub=%.2fV\n",
      dVthermal*1e3,dni,dUb,dUb*dVthermal,dWsub);
   Echo(" Vt0(Vfb=0)=%.2fV Vth(CV)=%.2fV Vfb=(Vth-Vt0)=%.2fV DVfb(Wgate=4.1V)=%.2fV\n",
      dVt0,dVth,dVfb,dVfb-(4.1-dWsub));
   
   /* Allocate mGd and calculate drain conductance term Gd*L/W[A/V] */
   mGd=MCreate(1,nRHGd=nCHJV-1,1,nCHGd=2); //[][1]=Vgs,[][2]=Gd
   MGetVector(mJV,TRUE,1,1,nRHJV,&vX);
   for (i=2;i<=nCHJV;i++) {
      double a,b,abdev;
      MGetVector(mJV,TRUE,i,1,nRHJV,&vY);
      VGetSlopeVector(vX,vY,1,nRHJV,FALSE,&vSlope);
      medfit(vX,vSlope,nRHJV,&a,&b,&abdev);
      mGd[i-1][1]=dStartVg+dStepVg*(i-2);
      mGd[i-1][2]=a; //yi
      VDestroy(vSlope,1,nRHJV);
      VDestroy(vY,1,nRHJV);
   }
   VDestroy(vX,1,nRHJV);

   dStartVg-=dStepVg*nExpandBoth;
   dStopVg+=dStepVg*nExpandBoth;
   dStepVg/=(nInterpolate+1);

   /* Allocate output matrix */
   nRH=(int)((dStopVg-dStartVg)/dStepVg)+1;
   nCH=4; //[][1]=Vg,[][2]=Eeff,[][3]=Ueff(Uni),[][4]=Ueff(Exp)
   mOut=MCreate(nRL=1,nRH,nCL=1,nCH);

   /* Fill mOut[*][1] up with Vgate */
   for (i=1;i<=nRH;i++) mOut[i][1]=dStartVg+dStepVg*(i-1);

   /* Fill mOut[*][2] up with Qi temporarily for moblity calculation. */
   MGetMinMaxValue(mQi,TRUE,1,1,nRHQi,FALSE,&dMin,&dMax); /* Vg */
   MGetVector(mQi,TRUE,1,1,nRHQi,&vX); /* Vg */
   MGetVector(mQi,TRUE,2,1,nRHQi,&vY); /* Qi */
   for (i=1;i<=nRH;i++) {
      double dQi;
      if ((bNMOSFET&&mOut[i][1]>dMax)||
         (!bNMOSFET&&mOut[i][1]<dMin)) {
         mOut[i][2]=dSlopeQi*mOut[i][1]+dYiQi;
      } else {
         VGetInterpolatedYValueWithXYVectors(mOut[i][1],vX,vY,1,nRHQi,4,&dQi);
         mOut[i][2]=dQi;
      }
   }
   VDestroy(vX,1,nRHQi);
   VDestroy(vY,1,nRHQi);

   /* Fill mOut[*][4] up with Mobility!!!!! */
   MGetVector(mGd,TRUE,1,1,nRHGd,&vX);//Vg
   MGetVector(mGd,TRUE,2,1,nRHGd,&vY);//Gd
   for (i=1;i<=nRH;i++) {
      double dGd;
      if (!VGetInterpolatedYValueWithXYVectors(mOut[i][1],vX,vY,1,nRHGd,4,&dGd)) {
         double dSlope,dYi;
         Echo(" Gd for Vgs=%gV is extrapolated by adjacent two points.\n",mOut[i][1]);
         if (mOut[i][1]<vX[1]) {
            dSlope=(vY[1]-vY[2])/(vX[1]-vX[2]);
            dYi=vY[1]-dSlope*vX[1];
         } else {
            dSlope=(vY[nRHGd-1]-vY[nRHGd])/(vX[nRHGd-1]-vX[nRHGd]);
            dYi=vY[nRHGd]-dSlope*vX[nRHGd];
         }
         dGd=mOut[i][1]*dSlope+dYi;
      }
      /* (Gd*L/W)/Qi */
      /* See N.Arora,MOSFET Models for VLSI Circuit Simulation,1993,p.453,Eq.(9.52) */
      mOut[i][4]=dGd/mOut[i][2]; /* mOut[*][2]=Qi */
   }
   VDestroy(vX,1,nRHJV);

   /* Fill mOut[*][2,3] up with Eeff(Silicon) and Universal Mobility */
   for (i=1;i<=nRH;i++) {
      double dQd,dQi;
      if ((bNMOSFET&&mOut[i][1]<dVth)||(!bNMOSFET&&mOut[i][1]>dVth)) { /* 20040103 */
         MkNaNDouble(mOut[i][1]);
         MkNaNDouble(mOut[i][2]);
         MkNaNDouble(mOut[i][3]);
         continue;
      }
      /* Y.Taur,Fundamentals of Modern VLSI Devices, 1998, p.132 */
      dQd=fabs(dCox*(dVth-dVfb-2*-dUb*dVthermal));/* |Qd| */
      dQi=fabs(dCox*(mOut[i][1]-dVth)); /* |Qi| */
      mOut[i][2]=(dQd+dQi/(bNMOSFET ? 2:3))/(RDCSilicon*VacPermittivity);/* Eeff [V/cm] */
      mOut[i][2]*=1e-6;/* Eeff [MV/cm] */
      /*
      1) K.Chen et.al,"Predicting CMOS Speed with Gate Oxide and Voltage
         Scaling and Interconnect Loading Effects," Elec.Dev. 44[11]1951-57(1997).
      2) Dieter K. Schroder, Semiconductor Material and Device Characterization,
         1998 2ed. p.553.
      */
      if (bNMOSFET) mOut[i][3]=540/(1+pow(mOut[i][2]/0.9,1.85));
      else mOut[i][3]=180/(1+mOut[i][2]/0.45);
   }

   /* Find out Max(mobility) and print it. */
   Echo(" Max(Ueff)[cm2/V-s]=");
   MGetMinMaxValue(mOut,TRUE,4,nRL,nRH,FALSE,&dMin,&dMax);
   Echo("%.1f\n",dMax);

   //Assign
   *MTX=mOut;
   *MRL=nRL;
   *MCL=nCL;
   *MRH=nRH;
   *MCH=nCH;

   Echo(" Matrix [%d..%d][%d..%d] is created well.\n",nRL,nRH,nCL,nCH);

   //Release
   MDestroy(mCV,1,nRHCV,1,nCHCV);
   MDestroy(mJV,1,nRHJV,1,nCHJV);
   MDestroy(mQi,1,nRHQi,1,nCHQi);
   MDestroy(mGd,1,nRHGd,1,nCHGd);
   return TRUE;
F: if (mCV) MDestroy(mCV,1,nRHCV,1,nCHCV);
   if (mJV) MDestroy(mJV,1,nRHJV,1,nCHJV);
   if (mQi) MDestroy(mQi,1,nRHQi,1,nCHQi);
   if (mGd) MDestroy(mGd,1,nRHGd,1,nCHGd);
   if (mOut) MDestroy(mOut,nRL,nRH,nCL,nCH);
   return FALSE;
}

/******************************************************************************/
/* SplitCV.c */

