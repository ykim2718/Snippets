/******************************************************************************/

const char *IdealMosCapacitor_Help=
"[Y.Kim]                                                                     \n"
"2002.10.14-11 -> matlab.                                                    \n"
"2003.02.21-22 -> as a user function of Gr.                                  \n"
"2003.03.16-29 -> 0502.                                                      \n"
"! IdealMosCapacitor() always prepares the Berman table whether used or not, \n"
"! and thus slow compared to IdealMosCapacitorEx().                          \n"
"                                                                            \n"
"[Reference]                                                                 \n"
"E.H.Nicollian and J.R.Brews,MOS Physics and Technology,1982,                \n"
"Page 161,Eq.(4.151)                                                         \n"
"                                                                            \n"
"[Input]                                                                     \n"
"argument=[n(mos)|p(mos)],Temp,Wgate,VfbShift,Tox,RDC,Nsub                   \n"
"! nmos|pmos: [string] NMOS or PMOS.                                         \n"
"! Temp: [C] Temperature in Celcius degree.                                  \n"
"! Wgate: [V] Gate Work Function.                                              \n"
"! Tox: [A] Gate oxide physical thickness.                                   \n"
"! RDC: [] Relatvie gate oxide dielectric constant. Dimensionless.           \n"
"! Nsub: [/cm3] Substrate concentration.                                     \n"
"option=[0|1|2]                                                              \n"
"! 0: Demo.                                                                  \n"
"! 1: Newtonian Piecewise correction (HF/Fast).                              \n"
"! 2: Newtonian Berman correction. (HF/Slow).                                \n"
"! 3: Newtonian Deep depletion consideration -> NA. Use IdealMosCapacitorEx().\n"
"! 4: Quantum correction -> NotAvailable.                                    \n"
"! suboption=[0|1]                                                           \n"
"! 0: Original full range data.                                              \n"
"! 1: Adaptive to gate bias point.                                           \n"
"sweep=start,stop,step                                                       \n"
"! Gate bias voltages for start,stop,step in the unit of [V].                \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! Matrix Creation : [nrl..nrh][ncl..MOS_MATRIX_COLUMN]                       ";

const char *IdealMosCapacitor_Sample=
"type=IdealMosCapacitorEx                                                    \n"
"argument=pmos,25,4.1,0,10,3.9,1e17 option=1 rsweep=-1,1,0.05                 ";
 
/******************************************************************************/

#include <math.h>
#include "usrfunc.h"
#include "nrecipe.h"
#include "number.h"
#include "tools.h"
#include "str.h"
#include "semiconductor.h"

#if !defined(SIGN)
#define SIGN(x)   ((x)>=0 ? 1:-1)
#endif

extern int Echo();
extern int EchoMosParameters();

#define MOS_MATRIX_VS     1
#define MOS_MATRIX_US     2
#define MOS_MATRIX_UB     3
#define MOS_MATRIX_FS     4
#define MOS_MATRIX_QS     5
#define MOS_MATRIX_VG     6
#define MOS_MATRIX_VSVOLT 7
#define MOS_MATRIX_VOX    8
#define MOS_MATRIX_EOX    9
#define MOS_MATRIX_CSL    10
#define MOS_MATRIX_CTL    11
#define MOS_MATRIX_BERMAN 12
#define MOS_MATRIX_CSH    13
#define MOS_MATRIX_CTH    14
#define MOS_MATRIX_EFMEFS 15
#define MOS_MATRIX_EFMECS 16
#define MOS_MATRIX_EFMEVS 17
#define MOS_MATRIX_COLUMN 17

/******************************************************************************/

/* Ref.:A.Berman and D.R.Kerr,"Inversion charge redistribution model of
 * the high-frequency MOS capacitance," Solid-State Electronics,1974,
 * Vol.17,pp.735-42.
 * -> The equation inside integral of Eq.11
 */
/* invalid for accumlation region. */
static double _dLi;
static double _dUb;
static int _UsSign;
static double _dFs;
static double _Func(double dUs) {
   double dFs;
   /* F [Berman Eq.5] */
   dFs=sqrt(2/pow(_dLi,2)*(cosh(dUs)-dUs*sinh(_dUb)-cosh(_dUb)+_dUb*sinh(_dUb)));
   /* F [Berman Eq.5] 43360113 Y.Kim */
   /*dFs=(2/dLi^2*(cosh(dUs)-cosh(dUb)-sinh(dUb)*dVs))^0.5; */
   _dFs=dFs;
   return exp(_UsSign*dUs)/pow(dFs,3);
}

//static 20030430
int OpenBermanTable(
   double dKelvin,double dUb,double dVs_Start,double dVs_Stop,
   MATRIX *pmBerman,
   int *pnBermanRL,int *pnBermanRH,int *pnBermanCL,int *pnBermanCH
   )
{
   double dVs_Step,dLi,dVs,dUs,dUs0,dFs,dDelta,dIntegral,dFactor;
   int nWorkRowMax,nWorkColMax=6,nRow;

   /* Ub=0, I did not consider this situation yet. */

   dVs_Step=0.1; /* for p-Si (Ub<0) <-- default. */
   if (dUb>=0) dVs_Step=dVs_Step*-1; /* for n-Silicon (Ub>0) */
       
   dVs_Start=-1*dUb; /* make Us 0 at start. */
   nWorkRowMax=(int)ceil((dVs_Stop-dVs_Start)/dVs_Step)+1;
   *pmBerman=dmatrix(1,nWorkRowMax,1,nWorkColMax);
   dLi=GetIntrinsicDebyeLength(dKelvin,RDCSilicon);

   _dLi=dLi;
   _dUb=dUb;
   _UsSign=dUb<0 ? 1:-1;

   for (nRow=1;nRow<=nWorkRowMax;nRow++) {
   
      dVs=dVs_Start+(nRow-1)*dVs_Step;
      dUs=dVs+dUb; /* Us-Ub=Vs [Nicollian,p.79] */
      dFs=sqrt(2/pow(dLi,2)*  /* F [Berman Eq.5] */
         (cosh(dUs)-dUs*sinh(dUb)-cosh(dUb)+dUb*sinh(dUb)));
      
      if (nRow==1) {
         dUs0=dUs; /* must be zero by paper 20030224 */
         dFs=dIntegral=dDelta=dFactor=0.0;
      } else {
         /* Press, Numerical Receipes in C, p.121 -> qtrap(func,a,b) */
         /* Press, Numerical Receipes in C, p.123 -> qsimp(func,a,b) */
         /* Press, Numerical Receipes in C, p.124 -> qromb(func,a,b) */
         /* Press, Numerical Receipes in C, p.133 -> qgaus(func,a,b) */
         dIntegral=qromb(_Func,dUs0,dUs);
         if (dUb<0) /* for n-Silicon */
            dDelta=dFs*exp(-dUs-dUb)/2/pow(dLi,2)*dIntegral;
         else /* for p-Silicon */
            dDelta=-1*dFs*exp(dUs+dUb)/2/pow(dLi,2)*dIntegral;
         dFactor=1/(1+dDelta);
      }

      /* Assigning */
      (*pmBerman)[nRow][1]=dVs;
      (*pmBerman)[nRow][2]=dUs;
      (*pmBerman)[nRow][3]=dFs;
      (*pmBerman)[nRow][4]=dIntegral;
      (*pmBerman)[nRow][5]=dDelta;
      (*pmBerman)[nRow][6]=dFactor;
   }

   *pnBermanRL=1;
   *pnBermanRH=nWorkRowMax;
   *pnBermanCL=1;
   *pnBermanCH=nWorkColMax;
   return nWorkRowMax*nWorkColMax;
}

//static 20030430
double LookupBermanTable(
   MATRIX mBerman,int nRl,int nRh,int nCl,int nCh,int bNtypeSi,double dVs
   )
{  
   double dBerman=0.0; /* Berman Factor */
   double dMin,dMax,dBehind,dCurrent,dSlope;
   int nColVs,nColBerman,nRow;

   nColVs=1;
   nColBerman=6;
   dMin=MGetColMinimum(mBerman,nRl,nRh,nCl,nCh,nColVs);
   dMax=MGetColMaximum(mBerman,nRl,nRh,nCl,nCh,nColVs);
   if (bNtypeSi && dVs>dMax) return dBerman; /* for n-Silicon */
   if (!bNtypeSi && dVs<dMin) return dBerman; /* for p-Silicon */
   for (nRow=nRl+1;nRow<=nRh;nRow++) { /* 20030223 */
      dBehind=mBerman[nRow-1][nColVs];
      dCurrent=mBerman[nRow][nColVs];
      if ((dBehind<dCurrent && dBehind<=dVs && dVs<=dCurrent) || /* 20030225 */
          (dBehind>dCurrent && dBehind>=dVs && dVs>=dCurrent)) {
         dSlope=(mBerman[nRow][nColBerman]-mBerman[nRow-1][nColBerman])/
            (mBerman[nRow][nColVs]-mBerman[nRow-1][nColVs]);
         dBerman=dSlope*(dVs-mBerman[nRow-1][nColVs])+
            mBerman[nRow-1][nColBerman];
         break;
      }
   }
   return dBerman;
}

//static 20030430
int CloseBermanTable( MATRIX mBerman,int nRl,int nRh,int nCl,int nCh )
{
   return MDestroy(mBerman,nRl,nRh,nCl,nCh);
}

/* 4335.11-4335.11.07 I created Excel version first.
 * 4336.01.06-14
 * Ref: 1) E.H.Nicollian and J.R.Brews,MOS Physics and Technology,p.161,1982.
 *      2) A.Berman and D.R.Kerr,"Inversion charge redistribution model of the high-frequency MOS
 *         capacitance," Solid-State Electronics,1974,Vol.17,pp.735-42.
 * All are assumed to silicon.
 */
static
double ClassicMosCapacitance( 
   int bNtype,          /* [Boolean] n-type = n-Si = PMOS */
   double dKelvinTemp,  /* [K] Kelvin degree */
   double dGateWorkFunc,/* [eV] Gate elctrode work function */
   double dVfbShift,    /* [V] Flat-band voltage shift */
   double dTox,         /* [A] Gate oxide thicknesse */
   double dRDCOxide,    /* [] Relative dielectric constant of oxide */
   double dNsub,        /* [#/cm3] Substrate concentration */
   int nOption,         /* 0=Demo(IwaiLab2002),1=Piecewise,2=Berman,3=NA,4=NA */
   MATRIX *pmCap,       /* output matrix */
   int *pnRrl,int *pnRh,int *pnCl,int *pnCh /* output */
   )
{
   const double dZeroTolerance=1e-9; /* while calculating. [YKim] */
   double dVs_Start,dVs_Stop,dVs_Step;
   int nWorkRowMax,nWorkColMax,nRow,nSign,
      nBermanRL,nBermanRH,nBermanCL,nBermanCH;
   double dVth,dEgap,dni,dLi,dLe,dCi,dCox,desi,deox,dWorkFuncDiff,dVfb,dUb,dVs,
      dUs,dQs,dFs,dVg,dCsl,dCtl,dVsVolt,dEox,dNumerator,dVox,
      dBermanFactor,dCsh,dCth;
   MATRIX mBerman,mWork;

   if (bNtype) { /* PMOS, [V] inversion when Vs<0,i.e,band-bend-upward. */
      dVs_Start=+20;
      dVs_Stop=-60;
      dVs_Step=-0.2;
   } else { /* NMOS, [V] inversion when Vs>0,i.e,band-bend-downward. */
      dVs_Start=-20;
      dVs_Stop=60;
      dVs_Step=+0.2;
   }

   nWorkRowMax=(int)floor((dVs_Stop-dVs_Start)/dVs_Step)+1;
   nWorkColMax=MOS_MATRIX_COLUMN;
   /* Vs[],Us[],Sign[],F[/cm],Qs[C/cm2],Vg[V],Csl[F/cm2],Ctl[F/cm2],
    * Vs[V],Vox[V],Eox[V/cm],BermanFactor,Csh[F/cm2],Cth[F/cm2],
    * (Ef(m)-Ef(si))[V],(Ef(m)-Ec(si))[V],(Ef(m)-Ev(si))[V]
    */
   mWork=dmatrix(1,nWorkRowMax,1,nWorkColMax);

   dVth=GetThermalVoltage(dKelvinTemp);
   dEgap=GetSiBandGapEnergy(dKelvinTemp);
   dni=GetSiIntrinsicCarrierConc(dKelvinTemp);
   dLi=GetIntrinsicDebyeLength(dKelvinTemp,RDCSilicon); /* [cm] */
   dLe=GetExtrinsicDebyeLength(dKelvinTemp,RDCSilicon,dNsub); /* [cm] */
   dCi=GetIntrinsicDebyeCapacitance(dKelvinTemp,RDCSilicon);
   dCox=GetSimpleMosCapacitance(dTox,dRDCOxide);
   desi=VacPermittivity*RDCSilicon; /* Silicon dielectric constant. */
   deox=VacPermittivity*dRDCOxide; /* Oxide dielectric constant. */
   dWorkFuncDiff= /* [V] Metal - Silicon */
      GetWorkFuncDiffToSiEf(dKelvinTemp,dGateWorkFunc,bNtype,dNsub);

   dVfb=dWorkFuncDiff+dVfbShift; /* for tunning to real data */

   dUb=log(dNsub/dni); /* Nicollian,p.52. -> [Ef-Ei(B)]/kT Nicollian,p.50 */
   if (!bNtype) dUb=dUb*-1; /* Ub<0 for p-Si(NMOS), Ub>0 for n-Si. */

   Echo(".Ideal work-func. diff. [V] = %.3g\n",dWorkFuncDiff);
   /* reserved for debugging 20030329
   * Nicollian,p.50 *
   Echo(".Bulk potential : Ef-Ei [V] = %.3g\n",dUb*dVth); 
   * Sze,p.372,Eq.26 *
   Echo(".Flat-band capacitance [C/cm^2] = %.3g\n",deox/(dTox*cmoverA+(deox/desi)*dLe));
   */

   OpenBermanTable(
      dKelvinTemp,dUb,dVs_Start,dVs_Stop,
      &mBerman,&nBermanRL,&nBermanRH,&nBermanCL,&nBermanCH);
   
   for (nRow=1;nRow<=nWorkRowMax;nRow++) {
       
      /* Dimensionless surface band-bending Vs, which means Pi(s)-Pi(B) */
      dVs=dVs_Start+(nRow-1)*dVs_Step;
      if (ABS(dVs)<dZeroTolerance) dVs=4336.0111e-9;
      
      /* Dimensionless surface potential Us, corresponding to Ef-Ei(S) */
      dUs=dVs+dUb;
      
      /* Low Frequency Calculation */
      
      /* Sign */
      nSign=SIGN(dVs);
      
      /* F[/cm] */
      /*dFs=(exp(-dUb)*(exp(-dVs)+dVs-1)+exp(+dUb)*(exp(dVs)-dVs-1))^0.5; */
      dFs=pow(2*(cosh(dUs)-cosh(dUb)-sinh(dUb)*dVs),0.5);
      
      /* Qs[C/cm2] */
      dQs=-nSign*dCi*dVth*dFs;
      
      /* Vg[V] */
      dVg=dVfb-dQs/dCox+dVth*dVs;
      
      /* Numerator */
      dNumerator=nSign/dVth*sqrt(2*KBoltzman*dKelvinTemp*desi*dni)
         *(sinh(dVs+dUb)-sinh(dUb));
      
      /* Csl[F/cm2] in low frequency */
      dCsl=dNumerator/dFs;
      
      /* Ctl[F/cm2] Total capacitance in low frequency */
      dCtl=(dCox*dCsl)/(dCox+dCsl);
      
      /* Checking */
      /* Vs[V] <-- [Ei(B)-Ei(S)]/q [Nicollian,p.51 Eq.2.40] */
      dVsVolt=dVs*dVth;
      /* Vox=Vg-Vfb-Vs [V] [Taur, p.68 Eq.2.167 + p.75 Eq.2.180 + p.117 comment] */
      dVox=dVg-dVfb-dVsVolt; 
      dEox=dVox/(dTox*cmoverA)*-1e-6; /* Vox/Tox[MV/cm] */
                            /* -1 -> to correct error in sign. 20030310 Y.Kim*/

      /* Sze,p.371,Eq.(24) : for debugging */
      //dEox=dQs/(VacPermittivity*dRDCOxide)*1e-6; /* [MV/cm] */

      /* Assigning */
      mWork[nRow][MOS_MATRIX_VS]=dVs; /* [] */
      mWork[nRow][MOS_MATRIX_US]=dUs; /* [] */
      mWork[nRow][MOS_MATRIX_UB]=dUb; /* [] */
      mWork[nRow][MOS_MATRIX_FS]=dFs; /* [/cm] */
      mWork[nRow][MOS_MATRIX_QS]=dQs; /* [C/cm2] */
      mWork[nRow][MOS_MATRIX_VG]=dVg; /* [V] */
      mWork[nRow][MOS_MATRIX_VSVOLT]=dVsVolt; /* Vs[V] */
      mWork[nRow][MOS_MATRIX_VOX]=dVox; /* Vox[V] */
      mWork[nRow][MOS_MATRIX_EOX]=dEox; /* Eox[MV/cm] */
      mWork[nRow][MOS_MATRIX_CSL]=dCsl; /* [C/cm2] Low Frequency */
      mWork[nRow][MOS_MATRIX_CTL]=dCtl; /* [C/cm2] Low Frequency */
      
      /* High Frequency Calculation */
      
      /* Inversion dispersion factor [Y.Kim+Berman] */
      switch (nOption) {
      case 1 : /* Newtonian Piecewise correction */
      default:
         if (IsSurfaceStrongInversion(dUb,dVs)) {
            dFs=sqrt(2*(/*cosh(dUs)*/-cosh(dUb)-sinh(dUb)*dVs));
            dBermanFactor=1.;
         } else
            dBermanFactor=0.;
         break;
      case 2 : /* Newtonian Berman correction */
         dBermanFactor=LookupBermanTable(
            mBerman,nBermanRL,nBermanRH,nBermanCL,nBermanCH,bNtype,dVs);
         break;
      }
      
      /* Numerator */
      dNumerator=nSign/dVth*sqrt(2*KBoltzman*dKelvinTemp*desi*dni)
         *((1-dBermanFactor)*sinh(dVs+dUb)-sinh(dUb));
      
      /* Csh[F/cm2] in high frequency */
      dCsh=dNumerator/dFs;

      /* Cth[F/cm2] Total capacitance in low frequency */
      dCth=(dCox*dCsh)/(dCox+dCsh);

      /* Assigning */
      mWork[nRow][MOS_MATRIX_BERMAN]=dBermanFactor; /* [] */
      mWork[nRow][MOS_MATRIX_CSH]=dCsh;
      mWork[nRow][MOS_MATRIX_CTH]=dCth;
      /* Ef(Metal)-Ef(Silicon) [V] 20030310 */
      mWork[nRow][MOS_MATRIX_EFMEFS]=-1*dVg;
      /* Ef(m)-Ec(si) at the surface. [V] 20030310+20030319 */
      mWork[nRow][MOS_MATRIX_EFMECS]=-1*dVg-(dVsVolt-dUb*dVth)-dEgap/2;
      /* Ef(m)-Ev(si) at the surface. [V] 20030310+20030319 */
      mWork[nRow][MOS_MATRIX_EFMEVS]=-1*dVg-(dVsVolt-dUb*dVth)+dEgap/2;
    
   }

   CloseBermanTable(mBerman,nBermanRL,nBermanRH,nBermanCL,nBermanCH);
   *pmCap=mWork;
   *pnRrl=1;
   *pnRh=nWorkRowMax;
   *pnCl=1;
   *pnCh=nWorkColMax;
   return TRUE;
}

static
int AdaptMosMatrixToGateBias(
   MATRIX *mMos,int *nRl,int *nRh,int *nCl,int *nCh,int nGateColumn,
   double dVg_Start,double dVg_Stop,double dVg_Step /* [V] */
   )
{
   MATRIX mNew;
   VECTOR vGate;
   int nRlNew,nRhNew,nRow,nCol,nIndex,nPosition,nVec,nBehind,nAhead,
      nStart,nStop;
   double dVg,vX[6],vY[6],y,dy;

   nVec=sizeof(vX)/sizeof(vX[0])-1; /* make base index be one */
   nBehind=nVec>>1;
   nAhead=nVec-nBehind;

   if (dVg_Step==0.0) return FALSE;
   if ((*mMos)[*nRl][nGateColumn]<(*mMos)[*nRh][nGateColumn]) {
      if ((*mMos)[*nRl][nGateColumn]>dVg_Start) return FALSE;
      if ((*mMos)[*nRh][nGateColumn]<dVg_Stop) return FALSE;
   } else {
      if ((*mMos)[*nRl][nGateColumn]<dVg_Start) return FALSE;
      if ((*mMos)[*nRh][nGateColumn]>dVg_Stop) return FALSE;
   }

   nRlNew=1;
   nRhNew=(int)((dVg_Stop-dVg_Start)/dVg_Step)+1;

   mNew=MCreate(nRlNew,nRhNew,*nCl,*nCh);
   for (nRow=nRlNew;nRow<=nRhNew;nRow++) {
      mNew[nRow][nGateColumn]=dVg_Start+dVg_Step*(nRow-nRlNew);
   }

   MGetVector((*mMos),TRUE,nGateColumn,*nRl,*nRh,&vGate);
   for (nIndex=nRlNew;nIndex<=nRhNew;nIndex++) {
      dVg=mNew[nIndex][nGateColumn];
      VGetValueIndexOfMonotonicVector(vGate,*nRl,*nRh,dVg,&nPosition);
      if ((nPosition-nBehind)<*nRl) {
         nStart=*nRl;
         nStop=*nRl+nVec-1;
      } else if ((nPosition+nAhead)>*nRh) {
         nStart=*nRh-nAhead+1;
         nStop=*nRl;
      } else {
         nStart=nPosition-nBehind;
         nStop=nPosition+nAhead-1;
      }
      for (nRow=nStart;nRow<=nStop;nRow++)
         vX[nRow-nStart+1]=vGate[nRow];
      for (nCol=*nCl;nCol<=*nCh;nCol++) {
         if (nCol==nGateColumn) continue;
         for (nRow=nStart;nRow<=nStop;nRow++)
            vY[nRow-nStart+1]=(*mMos)[nRow][nCol];
         /* Press,Numerical Receipes in C,p.90 */
         polint(vX,vY,nVec,dVg,&y,&dy);
         mNew[nIndex][nCol]=y;
      }
   }
   VDestroy(vGate,*nRl,*nRh);

   MDestroy(*mMos,*nRl,*nRh,*nCl,*nCh);
   *mMos=mNew;
   *nRl=nRlNew;
   *nRh=nRhNew;
   *nCl=*nCl;
   *nCh=*nCh;

   return TRUE;
}

int IdealMosCapacitor( ARGUMENTS )
   ARGULIST
{
   double dVg_Start,dVg_Stop,dVg_Step;
   double dKelvin,dGateWorkFunc,dVfbShift,dTox,dRDCOxide,dNsub;
   int bNtype,nOption,bDemo,bAdaptive;
   MATRIX mMos;
   int nRl,nRh,nCl,nCh,nIndex;
   char *pTok,*qDelimiter=",";

   Echo(" V.1.0\n");
   
   if (chrcount(SWEEP,*qDelimiter)!=2) {
      Echo(0,"Too many or short argument in SWEEP. Only 3 required : \n"
             "%s \n",SWEEP);
      return FALSE;
   }
   if (chrcount(ARGUMENT,*qDelimiter)!=6) {
      Echo(0,
         "Too many or short argument in ARGUMENT. Just 7 required. \n\n"
         "Those are MOS-type [n|p],temperature [K],gate work function [V], \n"
         "flat-band voltage shift [V] (which adds to Vfb),gate oxide thickness [A], \n"
         "oxide dielectric constant, and substrate concentration [/cm3], \n"
         "which should be kept in order and separated by comma. \n\n"
         "Your agrument is as following : \n"
         "%s \n",ARGUMENT);
      return FALSE;
   }

   switch (NOPTION) {
   case 0 : bDemo=TRUE;break;
   default:
   case 1 : bDemo=FALSE;nOption=1;break; /* No modification from ideal curve */
   case 2 : bDemo=FALSE;nOption=2;break; /* Berman correction */
   }
   switch (NSUBOPTION) {
   case 0 : default : bAdaptive=FALSE;break;
   case 1 : bAdaptive=TRUE;break;
   }
   for (nIndex=0;nIndex<=2;nIndex++) {
      pTok=strtokbyindex(SWEEP,qDelimiter,nIndex);
      switch (nIndex) {
      case 0 : dVg_Start=atof(pTok);break; /* [V] Gate voltage */
      case 1 : dVg_Stop=atof(pTok);break; /* [V] Gate voltage */
      case 2 : dVg_Step=atof(pTok);break; /* [V] Gate voltage */
      }
      freeEx(pTok);
   }
   for (nIndex=0;nIndex<=6;nIndex++) {
      pTok=strtokbyindex(ARGUMENT,qDelimiter,nIndex);
      switch (nIndex) {
      case 0 : bNtype=tolower(*pTok)=='n' ?0:1;break; /* NMOS/PMOS */
      case 1 : dKelvin=atof(pTok)+KKelvin;break;  /* [K] Kelvin degree */
      case 2 : dGateWorkFunc=atof(pTok);break;/* [V] Gate metal work function */
      case 3 : dVfbShift=atof(pTok);break; /* [V] Flat-band voltage shift */
      case 4 : dTox=atof(pTok);break; /* [A] Gate oxide thicknesse */
      case 5 : dRDCOxide=atof(pTok);break; /* [] Relative dielectric constant of oxide */
      case 6 : dNsub=atof(pTok);break; /* [#/cm3] Substrate concentration */
      }
      freeEx(pTok);
   }
   if (bDemo) {
      bNtype=1;         /* [Boolean] 1 = n-type (silicon) = PMOS */
      dKelvin=290;      /* [K] Kelvin degree */
      dGateWorkFunc=4.1;/* [V] Al=4.1V, Ag=5.1V [Sze p.396 Table 3 Metal Work Function (Volts)] */
      dVfbShift=0.0;    /* [V] Flat-band voltage shift */
      dTox=10;          /* [A] Gate oxide thickness */
      dRDCOxide=3.9;    /* [] Relative dielectric constant of oxide */
      dNsub=7.035e18;   /* [#/cm3] Substrate concentration ; 7.03e18->Ub=20V for p-Si,-20V for n-Si */
      dVg_Start=-2.5;   /* [V] Gate voltage */
      dVg_Stop=+2.5;    /* [V] Gate voltage */
      nOption=1;
   }
   
   Echo(" Option=%d Suboption=%d\n",NOPTION,NSUBOPTION);
   Echo(" Parameters: %cMOS,%gK,Wgate=%geV,VfbShift=%gV,Tox=%gA,RDC=%gA,Nb=%.2e/cm^3\n",
      bNtype?'P':'N',dKelvin,dGateWorkFunc,dVfbShift,dTox,dRDCOxide,dNsub);

   ClassicMosCapacitance(
      bNtype,dKelvin,dGateWorkFunc,dVfbShift,dTox,dRDCOxide,dNsub,nOption,
      &mMos,&nRl,&nRh,&nCl,&nCh);

   //EchoMosParameters(mMos,nRl,nRh,nCl,nCh);

   if (bAdaptive) AdaptMosMatrixToGateBias(
      &mMos,&nRl,&nRh,&nCl,&nCh,6,dVg_Start,dVg_Stop,dVg_Step);

   *MTX=mMos;
   Echo(" MTX=[%d..%d][%d..%d]\n",*MRL=nRl,*MRH=nRh,*MCL=nCl,*MCH=nCh);
   Echo(" [*][%d]=Vs (Dimensionless surface band bending)\n",MOS_MATRIX_VS);
   Echo(" [*][%d]=Us (Dimensionless surface potential)\n",MOS_MATRIX_US);
   Echo(" [*][%d]=Ub (Dimensionless bulk potential)\n",MOS_MATRIX_UB);
   Echo(" [*][%d]=Fs (Dimensionless surface electric field)\n",MOS_MATRIX_FS);
   Echo(" [*][%d]=Qs (Surface charge density) [C/cm^2]\n",MOS_MATRIX_QS);
   Echo(" [*][%d]=Vg (Calculated gate voltage) [V]\n",MOS_MATRIX_VG);
   Echo(" [*][%d]=VsVolt (Surface band bending) [V]\n",MOS_MATRIX_VSVOLT);
   Echo(" [*][%d]=Vox (Voltage drop in oxide) [V]\n",MOS_MATRIX_VOX);
   Echo(" [*][%d]=Eox (Electric field across oxide) [MV/cm]\n",MOS_MATRIX_EOX);
   Echo(" [*][%d]=Csl (Low frequency silicon capacitance) [F/cm^2]\n",MOS_MATRIX_CSL);
   Echo(" [*][%d]=Ctl (Low frequency (total) MOS capacitance) [F/cm^2]\n",MOS_MATRIX_CTL);
   Echo(" [*][%d]=Berman (Dimensionless Berman factor)\n",MOS_MATRIX_BERMAN);
   Echo(" [*][%d]=Csh (High frequency silicon capacitance) [F/cm^2]\n",MOS_MATRIX_CSH);
   Echo(" [*][%d]=Cth (High frequency (total) MOS capacitance) [F/cm^2]\n",MOS_MATRIX_CTH);
   Echo(" [*][%d]=Ef(metal)-Ef(silicon) (Fermi-level difference) [V]\n",MOS_MATRIX_EFMEFS);
   Echo(" [*][%d]=Ef(metal)-Ec(silicon) at the surface [V]\n",MOS_MATRIX_EFMECS);
   Echo(" [*][%d]=Ef(metal)-Ev(silicon) at the surface [V]\n",MOS_MATRIX_EFMEVS);

   return TRUE;
}

/******************************************************************************/
/* uIdealMosCapacitor.c */
