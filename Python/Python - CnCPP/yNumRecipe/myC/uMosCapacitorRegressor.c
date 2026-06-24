/******************************************************************************/
static char THIS_FILE[]="MosCapacitorRegressor";
#include "usrfunc.h"
uFuncTableTag uMosCapacitorRegressorTag={
"MosCapacitorRegressor(C-V)",
"type=MosCapacitorRegressor                                                  \n"
"argument=nmos,*,*,* option=110 range=-1,1 xyz=1,2,20                         ",
"[Y.Kim]                                                                     \n"
"2003.04.29-04.30 based on the uIdealMosCapacitorEx().                       \n"
"2003.0501-0610-0615,0802,0805,0901,1204                                     \n"
"                                                                            \n"
"[Computation Flow]                                                          \n"
"Vgate -NA-> Vs -> Cs -> Ctot -NA-> Wgate,Tox, and Nsub.                     \n"
"                                                                            \n"
"[Input]                                                                     \n"
"OPITON=[[0-4][01][01]]                                                      \n"
"! 1st digit: [Integer] Capacitance Model                                    \n"
"!   0= demonstration with reserved parameters.                              \n"
"!   1= Piecewise model for classic C-V.                                     \n"
"!   2= classic C-V with Piecewise model and Berman correction for strong inversion. \n"
"!   3= classic C-V by numerical computation of Poisson equation.            \n"
"!   4= quantum-effect-considered C-V with Hansch model.                     \n"
"!   5= quantum-effect-corrected C-V with Van Dort model. -> NA              \n"
"! 2nd digit: [Boolean] Whether HF (1) or LF (0).                            \n"
"! 3rd digit: [Boolean] Whether deep depletion (1) or not (0).               \n"
"SUBOPTION=[0|1|2|3]                                                         \n"
"! 0: No column addition(s) of result to matrix. Output only in log window.  \n"
"! 1: Add one column of calculated capacitance to matrix.                    \n"
"! 2: Add two columns : Vs and Dit by calculation of Terman method.          \n"
"! 3: Fuctions as both suboption=1 and suboption=2.                          \n"
"ARGUMENT=N(MOS)|P(MOS),<TEMP>,<WGATE>,<TOX>,<NSUB>                          \n"
"! NMOS|PMOS: [string]  NMOS or PMOS.                                        \n"
"! TEMP: [Celcius] Ambient temperature.                                      \n"
"! WGATE: [eV] Gate Work Function. Computed if <*>.                          \n"
"! TOX: [A] Gate oxide physical thickness. Computed if <*>.                  \n"
"! NSUB: [/cm3] Substrate impurity concentration. Computed if <*>.           \n"
"XT=(<X>,<Y>)(<X>,<Y>)...(<X>,<Y>) <--- if <TEMP> is specified.              \n"
"XYT=(<X>,<Y>,<T>)(<X>,<Y>,<T>)...(<X>,<Y>,<T>) <--- if <TEMP>==<*>          \n"
"! X: The first of each parentheses is x, which should be Vg [V].            \n"
"! Y: The second of those is y column index, which should be Cox [F/cm^2].   \n"
"! T: The third is temperature in Celcius degree, not z-index.               \n"
"RANGE=[<L>,<H>|<L>,<H>,<L>,<H>]                                             \n"
"! L: [double|*] Lower limit Vg to fit. <*> means data minimum.              \n"
"! H: [double|*] Upper limit Vg to fit. <*> means data minimum.              \n"
"! If <range=> is missed, Fitting is performed on the whole data range.      \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! Add one, two, or three columns depending your suboption value.            \n"
"! See also Log window.   "
};

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

/******************************************************************************/

extern int _IdealMosCapacitorEx( 
   const MOSTAG *MOSTag,
   double dVg_Start,    /* [V] */
   double dVg_Stop,     /* [V] */
   double dVg_Step,     /* [V] */
   Matrix *mOut         /* output matrix */
   );
static MOSTAG _MOSTag;
static enum {FIT_WGATE,FIT_TOX,FIT_NSUB,FIT_HANSCH };
static int    nFit;
static int   *vFitType;
static VECTOR vFitParameter;
static VECTOR vFitParameterInc;
static MATRIX mFitLimit; /* [1][1..nFit]=MIN,[2][1..nFit]=MAX */
static double _MOSC( double x,double a[] )
{
   Matrix mMos;
   int i;
   double dReturn;

   for (i=1;i<=nFit;i++) {
      if (a[i]<mFitLimit[1][i]||mFitLimit[2][i]<a[i]) { /* 20031225 */
		  MkNaNDouble(dReturn);  /* DBL_MAX */ /* How interesting it works well ! */
		  return dReturn; /* 20030615,0805,1231 */
      }
      switch (vFitType[i]) { /* 20031225 */
      case FIT_WGATE :  _MOSTag.dWgate=a[i];break;
      case FIT_TOX :    _MOSTag.dTox=a[i];break;
      case FIT_NSUB :   _MOSTag.dNsub=a[i];break;
      case FIT_HANSCH : _MOSTag.dHansch=a[i];break;
      }
   }
   _IdealMosCapacitorEx(&_MOSTag,x,x,1.,&mMos);
   dReturn=mMos.m[1][_MOSTag.bHighFrequency ? MOS_MATRIX_CTH:MOS_MATRIX_CTL];
   MDestroy(mMos.m,mMos.rl,mMos.rh,mMos.cl,mMos.ch);

   return dReturn;
}
static void _MOSCAtEachIteration( int nTrial )
{
   if (_MOSTag.nMethod==MT_HANSCH) //20031227
      Echo(" #%02d: Wgate=%.2feV,Tox(3.9)=%.2fA,Nsub=%.2e/cm^3,Hansch=%.2ecm\n",
      nTrial,_MOSTag.dWgate,_MOSTag.dTox,_MOSTag.dNsub,_MOSTag.dHansch);
   else
      Echo(" #%02d: Wgate=%.2feV,Tox(3.9)=%.2fA,Nsub=%.2e/cm^3\n",
      nTrial,_MOSTag.dWgate,_MOSTag.dTox,_MOSTag.dNsub);
}

int MosCapacitorRegressor( ARGUMENTS )
   ARGULIST
{
   char qXYT[256],*qDelimiter=",(){}",*qWildChars="*?",*pAddr;
   int bSucceeded,nArgument,nXYT,iXYT,nX,nY,nDataTotal,nTrial,bTempSpecifiedAtArgument,i;
   VECTOR vX,vY,vSig;
   double dChiSq;

   double aFitRange[4];
   int nFitRange=4;

   /* Version */
   Echo(" V.2.0\n");

   /* Set defaults */
   bSucceeded=TRUE;
   _MOSTag.nMethod=MT_PIECEWISE;
   _MOSTag.bDeepDepletion=FALSE;
   _MOSTag.bHighFrequency=TRUE;
   _MOSTag.bNType=FALSE;
   _MOSTag.dKelvin=300;
   _MOSTag.dWgate=4.1;
   _MOSTag.dVfbShift=0.;
   _MOSTag.dTox=10;
   _MOSTag.dRDCox=RDCOxide;
   _MOSTag.dRDCsub=RDCSilicon;
   _MOSTag.dNsub=1e16;
   _MOSTag.dHansch=15e-8; /* [cm] 15A */

   /* Check "OPTION" */
   switch (NOPTION-NOPTION%100) {
   case 100 : _MOSTag.nMethod=MT_PIECEWISE;       Echo(" Piecewise Model.");break;
   case 300 : _MOSTag.nMethod=MT_NUMERICALPOISSON;Echo(" Numerical Poisson Equation.");break;
   case 400 : _MOSTag.nMethod=MT_HANSCH;          Echo(" Hansch Model.");break;
   default : 
      Echo(0,"%s()\nSorry, your option <OPTION=%d> is not allowed. See help.\n",
         THIS_FILE,NOPTION);
      return FALSE;
   }
   _MOSTag.bHighFrequency=(NOPTION%100-NOPTION%10) ? 1:0;
   Echo(_MOSTag.bHighFrequency ? " +HF":" +LF");
   _MOSTag.bDeepDepletion=(NOPTION%10) ? 1:0; /* 20031204 */
   if (_MOSTag.bDeepDepletion) Echo("+DeepDepletion");
   Echo(" (option=%03d)\n",NOPTION);
   
   /* Check "SUBOPTION" */
   if (NSUBOPTION<0||NSUBOPTION>3) {
      Echo(0,"%s()\nSorry, your option <SUBOPTION=%d> is invalid. See help.\n",
         THIS_FILE,NSUBOPTION);
      return FALSE;
   }
   switch (NSUBOPTION) {
   case 0 : Echo(" No columns will be added.");break;
   case 1 : Echo(" Cg_fitted with Vg will be added, inflating column by 1.");break;
   case 2 : Echo(" Vs and Dit with Vg will be added, inflating column by 2.");break;
   case 3 : Echo(" Cg_fitted, Vs, and Dit will be added, inflating column by 3.");break;
   }
   Echo(" (suboption=%d)\n",NSUBOPTION);

   /* Allocate environment variables based on OPTION */
   nFit=_MOSTag.nMethod==MT_HANSCH ? 4:3;
   vFitType=salloc(int,nFit);
   vFitParameter=VCreate(1,nFit);
   vFitParameterInc=VCreate(1,nFit);
   mFitLimit=MCreate(1,2,1,nFit);

   /* Check "ARGUMENT" */
   nArgument=strtokcount(ARGUMENT,qDelimiter);
   if (nArgument!=5&&nArgument!=6) {
      Echo(0,"%s()\nCount of parameter is not 5 or 6 at the expression of <ARGUMENT=>\n",
         THIS_FILE);
      return FALSE;
   }
   _MOSTag.bNType=tolower(ARGUMENT[0])=='p' ? TRUE:FALSE; /* true(1) = n-type = n-Si = PMOS */
   pAddr=strtokbyindex(ARGUMENT,qDelimiter,1); /* Temperature */
   bTempSpecifiedAtArgument=isnumchr(*pAddr); /* 20030905 */
   _MOSTag.dKelvin=atof(pAddr)+KKelvin;
   free(pAddr);
   nFit=0;
   pAddr=strtokbyindex(ARGUMENT,qDelimiter,2); /* GateWorkFunction */
   if (chrchrs(*pAddr,qWildChars)) vFitType[++nFit]=FIT_WGATE;
   else _MOSTag.dWgate=atof(pAddr);
   free(pAddr);
   pAddr=strtokbyindex(ARGUMENT,qDelimiter,3); /* Tox */
   if (chrchrs(*pAddr,qWildChars)) vFitType[++nFit]=FIT_TOX;
   else _MOSTag.dTox=atof(pAddr);
   free(pAddr);
   pAddr=strtokbyindex(ARGUMENT,qDelimiter,4); /* Nsub */
   if (chrchrs(*pAddr,qWildChars)) vFitType[++nFit]=FIT_NSUB;
   else _MOSTag.dNsub=atof(pAddr);
   free(pAddr);
   if (_MOSTag.nMethod==MT_HANSCH) {
      if (nArgument==6) {
         pAddr=strtokbyindex(ARGUMENT,qDelimiter,5); /* Hansch factor */
         if (chrchrs(*pAddr,qWildChars)) vFitType[++nFit]=FIT_HANSCH;
         else _MOSTag.dHansch=atof(pAddr);
         free(pAddr);
      } else {
         _MOSTag.dHansch=15e-8; //15A
      }
   }
   if (nFit==0) {
      Echo(0,"%s()\nYou wanted nothing to fit at the expression of <ARGUMENT=>.\n",
         THIS_FILE);
      return FALSE;
   }

   for (i=1;i<=nFit;i++) {
	   switch (vFitType[i]) {
	   case FIT_WGATE :
		   vFitParameter[i]=_MOSTag.dWgate;
         mFitLimit[1][i]=1;
		   mFitLimit[2][i]=10; /* Must see S.Sze,2ed.1981, p.251 Fig.4. [YKim,20030805] */;
		   break;
	   case FIT_TOX :
		   vFitParameter[i]=_MOSTag.dTox;
         mFitLimit[1][i]=1;   /* [A] <- 1A */
		   mFitLimit[2][i]=1e3; /* [A] <- 1000A */
		   break;
	   case FIT_NSUB :
		   vFitParameter[i]=_MOSTag.dNsub;
         mFitLimit[1][i]=1e10; /* [#/cm^3] */
		   mFitLimit[2][i]=6.02204e23; /* [/cm3] Avogadro Constant */
		   break;
      case FIT_HANSCH :
		   vFitParameter[i]=_MOSTag.dHansch;
         mFitLimit[1][i]=5e-8; /* [cm] 5A */
		   mFitLimit[2][i]=500e-8; /* [cm] 500A(50nm) */
		   break;
	   }
   }
   /* Check "XYT" */
   if (chrcount(ARGUMENT2,'(')!=chrcount(ARGUMENT2,')')) {
      Echo(0,"Not paired parentheses at the expression of <XYZ=>\n");
      return FALSE;
   } else {
      pAddr=strvcat("(",ARGUMENT2,")",0);
      strreplace(&pAddr,"((","(");
      strreplace(&pAddr,"))",")");
      strreplace(&pAddr,")(",",");
      strreplace(&pAddr,")",",");
      strcpy(qXYT,pAddr);
      free(pAddr);
   }
   nXYT=chrcount(qXYT,',');
   if ((bTempSpecifiedAtArgument&&nXYT%2)||
      (!bTempSpecifiedAtArgument&&nXYT%3)) {
      Echo(0,"%s()\nError, not a muliple of %d at the expression of <XY%s=>.\n",
         THIS_FILE,
         bTempSpecifiedAtArgument ? 2:3,
         bTempSpecifiedAtArgument ? "T":"");
      if (bTempSpecifiedAtArgument)
         Echo(0,"%s()\nWatch out whether you specified temperature twice "
                "at both <ARGUMENT=> and <XY|XYT=>.\n",THIS_FILE);
      return FALSE;
   }
   /* Check "RANGE" */
   if (SWEEP&&*SWEEP) { /* 20030615 */
      int nCount,nIndex;
      nCount=strtokcount(SWEEP,qDelimiter);
      if (nCount%2||nCount>nFitRange) {
         Echo(0,"%s\nParameter of <range=> is not counted to 2 or 4.\n",THIS_FILE);
         return FALSE;
      }
      for (nIndex=0;nIndex<nCount;nIndex++) {
         pAddr=strtokbyindex(SWEEP,qDelimiter,nIndex);
         if (chrchrs(pAddr[0],qWildChars)) MkNaNDouble(aFitRange[nIndex]);
         else aFitRange[nIndex]=atof(pAddr);
         freeEx(pAddr);
         if (IsNaNDouble(aFitRange[nIndex])&&0<nIndex&&nIndex<(nCount-1)) {
            Echo(0,"%s\nParameter of <range=> is <*> inside the range.\n",THIS_FILE);
            return FALSE;
         }
      }
      for (nIndex=nCount;nIndex<nFitRange;nIndex++)
         MkNaNDouble(aFitRange[nIndex]);
      nFitRange=nCount;
   }
   /* Echo */
   Echo(" Parameters: %cMOS,%dK,nFit=%d", _MOSTag.bNType?'P':'N',(int)_MOSTag.dKelvin,nFit);
   for (i=1;i<=nFit;i++) {
	   switch (vFitType[i]) {
	   case FIT_WGATE : Echo(",Wgate=%.2feV",_MOSTag.dWgate);break;
	   case FIT_TOX :   Echo(",Tox(3.9)=%.2fA",_MOSTag.dTox);break;
	   case FIT_NSUB :  Echo(",Nsub=%.2e/cm^3",_MOSTag.dNsub);break;
      case FIT_HANSCH :Echo(",Hansch=%.2ecm",_MOSTag.dHansch);break;
	   }
   }
   Echo("\n");

   /* Fit */
   vX=VCreate(NRL,NRH);
   vY=VCreate(NRL,NRH);
   for (iXYT=0;iXYT<nXYT&&bSucceeded;iXYT++) {
      int nIndex,nL,nH;
      double dL,dH;
      VECTOR vXX,vYY;

      pAddr=strtokbyindex(qXYT,qDelimiter,iXYT++);
      nX=atoi(pAddr);freeEx(pAddr);
      pAddr=strtokbyindex(qXYT,qDelimiter,iXYT++);
      nY=atoi(pAddr);freeEx(pAddr);
      if (!bTempSpecifiedAtArgument) {
         double dTemperature;
         pAddr=strtokbyindex(qXYT,qDelimiter,iXYT);
         dTemperature=atof(pAddr);freeEx(pAddr);
         _MOSTag.dKelvin=dTemperature+KKelvin; /* [K] Kelvin degree */
         Echo(" xyt=%d,%d,%g",nX,nY,dTemperature);
      } else
         Echo(" xy=%d,%d",nX,nY);

      /* vX & vY */
      MGetVector(*MTX,TRUE,nX,NRL,NRH,&vXX);
      MGetVector(*MTX,TRUE,nY,NRL,NRH,&vYY);
      VGetMinMaxValue(vXX,NRL,NRH,&dL,&dH);
      if (IsNaNDouble(aFitRange[0])) aFitRange[0]=dL;
      if (IsNaNDouble(aFitRange[nFitRange-1])) aFitRange[nFitRange-1]=dH;
      nDataTotal=0;
      for (nIndex=0;nIndex<nFitRange;nIndex+=2) {
         int nResult=GetFittingRange(
            vXX,NRL,NRH,5,aFitRange[nIndex],aFitRange[nIndex+1],&nL,&nH);
         if (!nResult) continue;
         memcpy(vX+NRL+nDataTotal,vXX+nL,nResult*sizeof(double));
         memcpy(vY+NRL+nDataTotal,vYY+nL,nResult*sizeof(double));
         nDataTotal+=nResult;
      }
      if (!nDataTotal) {
         nDataTotal+=NRH-NRL+1;
         memcpy(vX+NRL,vXX+NRL,nDataTotal*sizeof(double));
         memcpy(vY+NRL,vYY+NRL,nDataTotal*sizeof(double));
      }
      VDestroy(vXX,NRL,NRH);
      VDestroy(vYY,NRL,NRH);
      Echo(" range=%s total=%d\n",SWEEP,nDataTotal);

      vX+=NRL-1;
      vY+=NRL-1;
      vSig=VCreate(1,nDataTotal);
      for (nIndex=1;nIndex<=nDataTotal;nIndex++) {
         vSig[nIndex]=1; /* default */
         vY[nIndex]=fabs(vY[nIndex]); /* 20030802 */
      }
      for (nIndex=1;nIndex<=nFit;nIndex++) {
         vFitParameterInc[nIndex]=vFitParameter[nIndex] ?
         vFitParameter[nIndex]*1e-3:1e-3;
      }
      /* Guess EOT roughly from the maximum capacitance. 20040105 */ {
      double dMin,dMax;
      VGetMinMaxValue(vY,1,nDataTotal,&dMin,&dMax);
      for (i=1;i<=nFit;i++) {
         if (vFitType[i]==FIT_TOX) {
            vFitParameter[i]=RDCOxide*VacPermittivity/dMax/cmoverA;
            _MOSTag.dTox=vFitParameter[i];
         } else if (vFitType[i]==FIT_NSUB) {
            ; // Later ...
         }
      }
      }
      /* Initialze variables. 20031218 */
      if (_MOSTag.nMethod!=MT_PIECEWISE) {
         int j,nMethod_,nFit_,*vFitType_;
         VECTOR vFitParameter_;
         VECTOR vFitParameterInc_;
         MATRIX mFitLimit_;
         nMethod_=_MOSTag.nMethod;
         _MOSTag.nMethod=MT_PIECEWISE;
         nFit_=3;
         vFitType_=salloc(int,nFit_);
         vFitParameter_=VCreate(1,nFit_);
         vFitParameterInc_=VCreate(1,nFit_);
         mFitLimit_=MCreate(1,2,1,nFit_);
         for (i=1,j=0;i<=nFit;i++) {
            if (vFitType[i]!=FIT_HANSCH) {
               j++;
               vFitType_[j]=vFitType[i];
               vFitParameter_[j]=vFitParameter[i];
               vFitParameterInc_[j]=vFitParameterInc[i];
		         mFitLimit_[1][j]=mFitLimit[1][i];
               mFitLimit_[2][j]=mFitLimit[2][i];
            }
         }
         SWAP(nFit,nFit_);
         SWAP((int)vFitType,(int)vFitType_);
         SWAP((int)vFitParameter,(int)vFitParameter_);
         SWAP((int)vFitParameterInc,(int)vFitParameterInc_);
         SWAP((int)mFitLimit,(int)mFitLimit_);
         nTrial=LinearAndNonlinearFit(
            vX,vY,vSig,nDataTotal,
            vFitParameter,vFitParameterInc,nFit,3,
            &dChiSq,0,_MOSC,NULL);
         SWAP(_MOSTag.nMethod,nMethod_);
         SWAP(nFit,nFit_);
         SWAP((int)vFitType,(int)vFitType_);
         SWAP((int)vFitParameter,(int)vFitParameter_);
         SWAP((int)vFitParameterInc,(int)vFitParameterInc_);
         SWAP((int)mFitLimit,(int)mFitLimit_);
         for (i=1;i<=nFit_;i++) {
            if (vFitType_[i]==FIT_HANSCH) continue;
            for (j=1;j<=nFit;j++) {
               if (vFitType[j]==vFitType_[i]) {
                  vFitParameter[j]=vFitParameter_[i];
                  switch (vFitType[j]) { //20031226
                  case FIT_WGATE :
                  case FIT_TOX :
                     mFitLimit_[1][j]=vFitParameter[j]*0.5;
                     mFitLimit_[2][j]=vFitParameter[j]*1.2;
                     break;
                  case FIT_NSUB :
                     mFitLimit_[1][j]=vFitParameter[j]*0.1;
                     mFitLimit_[2][j]=vFitParameter[j]*10;
                     break;
                  }
               }
            }
         }
         free(vFitType_);
         VDestroy(vFitParameter_,1,nFit_);
         VDestroy(vFitParameterInc_,1,nFit_);
         MDestroy(mFitLimit_,1,2,1,nFit_);
      }
            
      nTrial=LinearAndNonlinearFit(
         vX,vY,vSig,nDataTotal,
         vFitParameter,vFitParameterInc,nFit,3,
         &dChiSq,0,_MOSC,_MOSCAtEachIteration);
      VDestroy(vSig,1,nDataTotal);
      vX-=NRL-1;
      vY-=NRL-1;

      Echo(" Results (%d trial%s) : ",nTrial,nTrial>1?"s":"");
      for (i=1;i<=nFit;i++) {
         switch (vFitType[i]) {
         case FIT_WGATE :  _MOSTag.dWgate=vFitParameter[i]; break;
         case FIT_TOX :    _MOSTag.dTox=vFitParameter[i];   break;
         case FIT_NSUB :   _MOSTag.dNsub=vFitParameter[i];  break;
         case FIT_HANSCH : _MOSTag.dHansch=vFitParameter[i];break;
         }
      }
      for (i=1;i<=nFit;i++) {
         if (i!=1) Echo(",");
         switch (vFitType[i]) {
         case FIT_WGATE : Echo("Wgate=%.2feV",_MOSTag.dWgate);break;
         case FIT_TOX :   Echo("Tox(3.9)=%.2fA",_MOSTag.dTox);break;
         case FIT_NSUB :  Echo("Nsub=%.2e/cm^3",_MOSTag.dNsub);break;
         case FIT_HANSCH :
            if (_MOSTag.nMethod==MT_HANSCH) Echo("Hansch=%.2ecm",_MOSTag.dHansch);break;
         }
      }
      Echo("\n");

      /* 20030904 for uSplitCV.c */
      *OUTTOT=4;
      *OUTVEC=VCreate(0,3);
      (*OUTVEC)[0]=_MOSTag.dWgate;
      (*OUTVEC)[1]=_MOSTag.dTox;
      (*OUTVEC)[2]=_MOSTag.dNsub;
      (*OUTVEC)[3]=_MOSTag.dHansch; /* 20031226 */

      { /* 20030901 */
         extern int EchoMosParameters();
         Matrix mMos;
         int j;
         /* 20030905 */
         if (!NSUBOPTION) continue; 
         /* 20031122+1204 */
         _IdealMosCapacitorEx(&_MOSTag,dL,dH,(dH-dL)/(NRH-NRL),&mMos);
         if (*MRL!=mMos.rl||*MRH!=mMos.rh) {
            MDestroy(mMos.m,mMos.rl,mMos.rh,mMos.cl,mMos.ch);
            Echo(0,"Mismatching occurred..\n");
            continue;
         }
         EchoMosParameters(&_MOSTag,mMos.m,mMos.rl,mMos.rh,mMos.cl,mMos.ch);

         if (NSUBOPTION&BIT(0)) { /* Attach calculated capacitance */
            MInflate(MTX,*MRL,*MRH,*MCL,*MCH,*MRH,*MCH+1);
            (*MCH)++;
            nIndex=_MOSTag.bHighFrequency ? MOS_MATRIX_CTH:MOS_MATRIX_CTL;
            for (j=*MRL;j<=*MRH;j++) (*MTX)[j][*MCH]=mMos.m[j][nIndex];
            Echo(" [%d..%d][%d..%d]. Added 1 column: [*][%d] is Cg(fitted).\n",
               *MRL,*MRH,*MCL,*MCH,*MCH);
         }

         if (NSUBOPTION&BIT(1)) { /* Attach calculated Dit following Terman */
            VECTOR vVg,vCgtest,vVs,vCg,vDit=0;
            double dVth,dDitZero,dDitMax;
            MGetVector(*MTX,TRUE,nX,*MRL,*MRH,&vVg);
            MGetVector(*MTX,TRUE,nY,*MRL,*MRH,&vCgtest);
            MGetVector(mMos.m,TRUE,MOS_MATRIX_VS,*MRL,*MRH,&vVs);
            MGetVector(mMos.m,TRUE,_MOSTag.bHighFrequency ? MOS_MATRIX_CTH:MOS_MATRIX_CTL,*MRL,*MRH,&vCg);
            if (!VCheckMonotonity(vCgtest,*MRL,*MRH)) {
               VMakeYVectorMonotonicByXVector(vVg,vCgtest,*MRL,*MRH);
               Echo(" Made Cg(test) be monotonic vector.\n");
            }
            dVth=GetThermalVoltage(_MOSTag.dKelvin);
            for (j=*MRL;j<=*MRH;j++) vVs[j]*=dVth; /* Vs [eV] */
            if (GetInterfaceTrapDensityByTerman(
               !_MOSTag.bNType,vVg,vCgtest,vCg,vVs,*MRL,*MRH,&vDit)) {
               MInflate(MTX,*MRL,*MRH,*MCL,*MCH,*MRH,*MCH+2);
               (*MCH)+=2;
               for (j=*MRL;j<=*MRH;j++) {
                  (*MTX)[j][*MCH-1]=vVs[j];
                  (*MTX)[j][*MCH]=vDit[j];
               }
               Echo(" [%d..%d][%d..%d]. Added 2 columns: [*][%d] is Vs and [*][%d] is Dit.\n",
                  *MRL,*MRH,*MCL,*MCH,*MCH-1,*MCH);
               VGetInterpolatedYValueWithXYVectors(0,vVs,vDit,*MRL,*MRH,5,&dDitZero);
               VGetMinMaxValue(vDit,*MRL,*MRH,NULL,&dDitMax);
               Echo(" Dit(Vs=0V)=%.2e Max(Dit)=%.2e\n",dDitZero,dDitMax);
            } else {
               Echo(0,"Error ... occurred at GetInterfaceTrapDensityByTerman().\n");
               bSucceeded=FALSE;
            }
            VDestroy(vVg,*MRL,*MRH);
            VDestroy(vCgtest,*MRL,*MRH);
            VDestroy(vVs,*MRL,*MRH);
            VDestroy(vCg,*MRL,*MRH);
            if (vDit) VDestroy(vDit,*MRL,*MRH);
         }
         MDestroy(mMos.m,mMos.rl,mMos.rh,mMos.cl,mMos.ch);
      }
     
   }
   VDestroy(vX,NRL,NRH);
   VDestroy(vY,NRL,NRH);

   /* Deallocate environment variables */
   free(vFitType);
   VDestroy(vFitParameter,1,nFit);
   VDestroy(vFitParameterInc,1,nFit);
   MDestroy(mFitLimit,1,2,1,nFit);

   return bSucceeded;
}

/******************************************************************************/
/* uMosCapacitorRegressor.c */
