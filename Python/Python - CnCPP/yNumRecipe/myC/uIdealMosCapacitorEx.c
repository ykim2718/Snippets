/******************************************************************************/
static char THIS_FILE[]="IdealMosCapacitorEx";

const char *IdealMosCapacitorEx_Help=
"Cavolre                                                                     \n"
"                                                                            \n"
"[Y.Kim]                                                                     \n"
"2002.1014-11 Matlab.                                                        \n"
"2003.0221-0322 As a user function of Gr.                                    \n"
"2003.0316-0329-0430 Get rid of the need of adaptive option due to rtsec().  \n"
"2003.0629 Deep-depletion effect realized.                                   \n"
"2003.1225 Numerical Poisson equation solver is made. Deep-depletion effect realized.                                   \n"
"                                                                            \n"
"[Reference]                                                                 \n"
"E.H.Nicollian and J.R.Brews,MOS Physics and Technology,1982,                \n"
"Page 161,Eq.(4.151)                                                         \n"
"                                                                            \n"
"[Input]                                                                     \n"
"option=[[0-4][?][01]]                                                       \n"
"! 1st digit: [Integer] Capacitance Model                                    \n"
"!   0= demonstration with reserved parameters.                              \n"
"!   1= Piecewise model for classic C-V.                                     \n"
"!   2= classic C-V with Piecewise model and Berman correction for strong inversion. \n"
"!   3= classic C-V by numerical computation of Poisson equation.            \n"
"!   4= quantum-effect-considered C-V with Hansch model.                     \n"
"!   5= quantum-effect-corrected C-V with Van Dort model. -> NA              \n"
"! 2nd digit: [Boolean] Whether HF (1) or LF (0). ---> NA                    \n"
"! 3rd digit: [Boolean] Whether deep depletion (1) or not (0).               \n"
"argument=[N(MOS)|P(MOS)],Temp,Wgate,VfbShift,Tox,RDC,Nsub,Hansch            \n"
"! NMOS|PMOS: [string] NMOS or PMOS.                                         \n"
"! Temp: [C] Temperature in Celcius degree.                                  \n"
"! Wgate: [V] Gate Work Function.                                             \n"
"! Tox: [A] Gate oxide physical thickness.                                   \n"
"! RDC: [] Relatvie gate oxide dielectric constant. Dimensionless.           \n"
"! Nsub: [/cm3] Substrate concentration.                                     \n"
"! Hansch: [cm] Characteristic length. Hansch model only.                    \n"
"sweep=start,stop,step                                                       \n"
"! Gate bias voltages for start,stop,step in the unit of [V].                \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! Matrix Creation : [nrl..nrh][ncl..MOS_MATRIX_COLUMN]                       ";

const char *IdealMosCapacitorEx_Sample=
"type=IdealMosCapacitorEx                                                    \n"
"argument=pmos,25,4.1,0,10,3.9,1e17 option=110 sweep=-1,1,0.05                ";
 
/******************************************************************************/

#include <math.h>
#include <memory.h>
#include "usrfunc.h"
#include "nrecipe.h"
#include "number.h"
#include "tools.h"
#include "str.h"
#include "nr.h"
#include "nr3.h"
#include "semiconductor.h"

extern int Echo();

#if !defined(SIGN)
#define SIGN(x)   ((x)>=0 ? 1:-1)
#endif

typedef struct { /* 20031210 */
   int bNType;          /* [Boolean] true(1) = n-type = n-Si = PMOS */
   int bHighFrequency;  /* If true, HF, or else, LF */
   int bDeepDepletion;  /* For the case of deep-depletion state in silicon substrate */
   double dKelvin;  /* [K] Kelvin degree */
   double dVth;
   double dni;
   double dLi; /* [cm] Intrinsic Debye length */
   double dLi2; /* dLi*dLi */
   double dLe; /* [cm] */
   double dCi;
   double dTox; /* [cm] */
   double dCox; /* [F/cm2] */
   double desub; /* substrate dielectric constant. */
   double deox; /* oxide dielectric constant. */
   double dVfb; /* [V] */
   double dUb;      /* [] Dimensionless bulk potential */
   double dsinhUb; /* sinh(dUb) */
   double dLth; /* Thermal wave length in Hansch model */
} SUBPROPERYTAG;

/******************************************************************************/

static double _GetSubProperty_dVg=0;
static const SUBPROPERYTAG *_GetSubProperty_Tag=0;
static void (*_GetSubProperty_Derivs)();
static void (*_GetSubProperty_Jacobn)();

static double _EvalVs_Result[2]; /* Qs,Es */

/*----------------------------------------------------------------------------*/
static double EvalVsWithPiecewiseModel( double dVs ) /* dimensionless Vs */
{
   double dVg=_GetSubProperty_dVg;
   double dUb=_GetSubProperty_Tag->dUb;
   double dLi=_GetSubProperty_Tag->dLi;
   double dCi=_GetSubProperty_Tag->dCi;
   double dVth=_GetSubProperty_Tag->dVth;
   double dVfb=_GetSubProperty_Tag->dVfb;
   double dCox=_GetSubProperty_Tag->dCox;
   double desub=_GetSubProperty_Tag->desub;
   int bDeepDepletion=_GetSubProperty_Tag->bDeepDepletion;
   double dUs,dFs,dEs,dQs,dVgNew,dReturn;
   int nSign;

   /* Dimensionless surface potential Us, corresponding to Ef-Ei(S) */
   dUs=dVs+dUb;
   /* Sign */
   nSign=SIGN(dVs);
   /* Dimensionless surface electric field, Fs[] */
   dFs=(bDeepDepletion&&IsSurfaceStrongInversion(dUb,dVs)) ? /* 20030629 */
      sqrt(2*(-cosh(dUb)-sinh(dUb)*dVs)):
      //dF=(exp(-dUb)*(exp(-dVs)+dVs-1)+exp(+dUb)*(exp(dVs)-dVs-1))^0.5;
      //dF=sqrt(2*(cosh(dUs)-cosh(dUb)-sinh(dUb)*dVs));
      sqrt(2*(cosh(dUs)-cosh(dUb)-sinh(dUb)*dVs));
   /* Surface electric field, Es[V/cm] */
   dEs=-nSign*dVth/dLi*dFs;
   /* Qs[C/cm2] */
   dQs=desub*dEs;
   //dQs=-nSign*dCi*dVth*dFs; /* dCi=desi/dLi */
   /* Vg[V] */
   dVgNew=dVfb-dQs/dCox+dVth*dVs;
   /* y=f(dVs)-dVg */
   dReturn=dVgNew-dVg;

   /* Output */
   _EvalVs_Result[0]=dQs;
   _EvalVs_Result[1]=dEs;

   return dReturn;
}
/*----------------------------------------------------------------------------*/
/* 20031206 */
extern double zriddr(double (*func)(double), double x1, double x2, double xacc);
extern void stifbs(double y[], double dydx[], int nv, double *xx, double htry, double eps,
	double yscal[], double *hdid, double *hnext,
	void (*derivs)(double, double [], double []));
extern void simpr(double y[], double dydx[], double dfdx[], double **dfdy, int n,
	double xs, double htot, int nstep, double yout[],
	void (*derivs)(double, double [], double []));
void jacobn(double x, double y[], double dfdx[], double **dfdy, int n)
{
   (*_GetSubProperty_Jacobn)(x,y,dfdx,dfdy,n);
}
static int GetUxWithPoissonEquation( // band bending along with substrate depth
   double dVs, // Surface band bending []
   double dF0, // Semi-dimensionless surface electric field [/cm], Y.Kim
   VECTOR *pvX,VECTOR *pvY1,VECTOR *pvY2,int *pnL,int *pnH )
{
   VECTOR vX,vY1,vY2;
   int nL,nH,nVar;
   double dVsZero,x1,x2,y[3],y1,y2;

   *pvX=*pvY1=*pvY2=(VECTOR)(*pnL=*pnH=0);
   dVsZero=fabs(dVs)/50; /* 0.02% */
   x1=1e-8;   // 1e-8cm=0.1nm=1A
   x2=1e-4;   // 1e-4cm=1um
   nL=1;
   nH=256;
   nVar=2;
   y1=y[1]=dVs; // Surface band bending []
   y2=y[2]=dF0; // Semi-dimensionless surface electric field [/cm]
   vX=VCreate(nL,nH); // Depth[cm]
   vY1=VCreate(nL,nH); // Surface band bending []
   vY2=VCreate(nL,nH); // Semi-dimensionless surface electric field [/cm]
   /* H.Press, odeint()+stifbs() */  {
   extern int kmax,kount; // nr.c
   extern double *xp,**yp,dxsav; // nr.c
   double eps=1e-9; // integrate starting values y[] from x1 to x2 with accuracy eps
   double h1=1e-8;  // first step size
   double hmin=h1;  // minimum allowed stepsize (can be zero)
   int nok,nbad,i,j,nVsSign=SIGN(dVs);
   kmax=32;
   xp=VCreate(1,kmax+1);
   yp=MCreate(1,nVar,1,kmax+1);
   dxsav=h1;
   // x1=0.; silicon surface is not x=0 since sinh function will diverge if zero.
   vX[nL]=x1;
   vY1[nL]=y1;
   vY2[nL]=y2;
   for (i=nL+1;i<=nH;i++) {
      x2=x1+y1/(-y2); // y1=y[1]@i-1,y2=y[2]@i-1
      odeint(y,2,x1,x2,eps,h1,hmin,&nok,&nbad,_GetSubProperty_Derivs,stifbs);
      if (fabs(y[1])<dVsZero) { b:
         for (j=2;i<nH&&j<=kount;i++,j++) {
            if (!_finite(yp[1][j])||!_finite(yp[2][j])) break;
            if ((yp[1][j]*yp[2][j])>0) break;
            if ((nVsSign*(yp[1][j]-yp[1][j-1]))>=0) break;
            if ((yp[1][j-1]*yp[1][j])<0) break;
            x1=vX[i]=xp[j];
            y1=vY1[i]=yp[1][j];
            y2=vY2[i]=yp[2][j];
         }
         vX[i]=x1+y1/(-y2); // Yahooooo 20031217,AM 03:15
         vY1[i]=0;
         vY2[i]=0;
         nH=i;
         for (i=nL;i<nH;i++) { /* 20031223 */
            if (fabs(vY1[i]-vY1[i+1])<fabs(dVs)*1e-3) { //20031227
               memcpy(vY1+i,vY1+i+1,sizeof(double)*(nH-i));
               memcpy(vY2+i,vY2+i+1,sizeof(double)*(nH-i));
               memcpy(vX+i,vX+i+1,sizeof(double)*(nH-i));
               nH--;
            }
         }
         break;
      }
      // abnormal calculation
      if (!_finite(y[1])) goto b;
      if ((y[1]*y[2])>0) goto b;
      if (vY1[i-1]*y[1]<0) goto b;
      if (y[1]==vY1[i-1]) goto b;
      if ((nVsSign*(y[1]-y1))>0) goto b;
      // assign
      for (j=2;i<=nH&&j<=kount;i++,j++) {
         vX[i]=xp[j];
         vY1[i]=yp[1][j];
         vY2[i]=yp[2][j];
      }
      // for next
      i--;j--;
      x1=vX[i];
      y1=vY1[i];
      y2=vY2[i];
   }
   VDestroy(xp,1,kmax+1);
   MDestroy(yp,1,nVar,1,kmax+1);
   kmax=0;
   }
   *pvX=vX;
   *pvY1=vY1;
   *pvY2=vY2;
   *pnL=nL;
   *pnH=nH;
   return nH-nL+1;
}
static void _GetUxDerivs_PoissonEquation( double x,double y[],double dydx[] )
/* Poisson equation d^2y/dx^2=[sinh(y+ub)-sinh(ub)]/Li^2
 * dy[1]/dx = y[2]
 * dy[2]/dx = (sinh(y[1]+ub)-sinh(ub))/Li^2
 */
{
   double Li2=_GetSubProperty_Tag->dLi2;
   double Ub=_GetSubProperty_Tag->dUb;
   double sinhUb=_GetSubProperty_Tag->dsinhUb;
   dydx[1]=y[2];
   dydx[2]=(sinh(y[1]+Ub)-sinhUb)/Li2;
}
static void _GetUxJacobn_PoissonEquation(
   double x,double y[],double dfdx[],double **dfdy,int n
   )
{
   double Li2=_GetSubProperty_Tag->dLi2;
   double Ub=_GetSubProperty_Tag->dUb;
   dfdx[1]=dfdx[2]=0.0;//for (i=1;i<=n;i++) dfdx[i]=0.0;
   dfdy[1][1]=0.;
	dfdy[1][2]=1.;
   dfdy[2][1]=cosh(y[1]+Ub)/Li2;
	dfdy[2][2]=0.;
}
static double EvalVsWithPoissonEquation( double dVs )
{
   double dVg=_GetSubProperty_dVg;
   double dVth=_GetSubProperty_Tag->dVth;
   double dVfb=_GetSubProperty_Tag->dVfb;
   double dCox=_GetSubProperty_Tag->dCox;
   double desub=_GetSubProperty_Tag->desub;
   double dni=_GetSubProperty_Tag->dni;
   double dUb=_GetSubProperty_Tag->dUb;
   double dsinhUb=_GetSubProperty_Tag->dsinhUb;
   double dF0,dEs,dQs,dVgNew;
   VECTOR vX,vY1,vY2,vArea;
   int nL,nH,i;
//#define _DEBUG_POISSON 1
#ifdef _DEBUG_POISSON
Matrix m;
#endif

   dEs=(dVfb+dVs*dVth-dVg)*dCox/desub;
   if (SIGN(dVs*dEs)>0) return SIGN(dEs)*43361214;
   dF0=dEs/dVth; /* Semi-dimensionless surface electric field [/cm], Y.Kim */

   GetUxWithPoissonEquation(dVs,dF0,&vX,&vY1,&vY2,&nL,&nH);
#ifdef _DEBUG_POISSON
m.m=0;m.rl=nL;m.rh=nH;m.cl=1;m.ch=1;
MAddVector(&(m.m),m.rl,m.rh,m.cl,m.ch,vX,TRUE,&(m.rh),&(m.ch));
MAddVector(&(m.m),m.rl,m.rh,m.cl,m.ch,vY1,TRUE,&(m.rh),&(m.ch));
#endif
   for (i=nL;i<=nH;i++) vY1[i]=2*dni*(sinh(vY1[i]+dUb)-dsinhUb);
   VGetCumAreaVector(vX,vY1,nL,nH,FALSE,&vArea);
   dQs=-vArea[nH]*Qelectron;
#ifdef _DEBUG_POISSON
MAddVector(&(m.m),m.rl,m.rh,m.cl,m.ch,vY1,TRUE,&(m.rh),&(m.ch));
{char buf[16];
sprintf(buf,"zp%.2f",dVg);
MWriteToFile(buf,"%g",m.m,m.rl,m.rh,m.cl,m.ch);
MDestroy(m.m,m.rl,m.rh,m.cl,m.ch); }
#endif
   VDestroy(vX,nL,nH);
   VDestroy(vY1,nL,nH);
   VDestroy(vY2,nL,nH);
   VDestroy(vArea,nL,nH);

   dEs=dQs/desub;
   dVgNew=dVfb-dQs/dCox+dVs*dVth;

   _EvalVs_Result[0]=dQs;
   _EvalVs_Result[1]=dEs;

   return dVgNew-dVg;
}
static void GetCsWithPoissonEquation(
   const SUBPROPERYTAG *Tag,
   double dVs1,double dVs2, /* [] Dimensionless surface potential */
   double dVgDelta, /* [V] */
   double *pdCsl,double *pdCsh
)
{
   double dVg=_GetSubProperty_dVg;
   double dVth=_GetSubProperty_Tag->dVth;
   double dVfb=_GetSubProperty_Tag->dVfb;
   double dTox=_GetSubProperty_Tag->dTox;
   double dCox=_GetSubProperty_Tag->dCox;
   double deox=_GetSubProperty_Tag->deox;
   double desub=_GetSubProperty_Tag->desub;
   double dni=_GetSubProperty_Tag->dni;
   double dUb=_GetSubProperty_Tag->dUb;
   double dsinhUb=_GetSubProperty_Tag->dsinhUb;
   double dEox1,dEox2,dCtl;
   double dF1,dF2,dCth,dEs1,dEs2,dX,dError;
   VECTOR vX,vY1,vY2;
   int nL,nH;

   /* Low frequency silicon capacitance */

   dEox1=(dVg-dVfb-dVs1*dVth)/dTox;
   dEox2=(dVg+dVgDelta-dVfb-dVs2*dVth)/dTox;
   dCtl=deox*fabs((dEox2-dEox1)/dVgDelta);
   //dCtl=desub*fabs((dEs1-dEs2)/dVgDelta);
   *pdCsl=dCox*dCtl/(dCox-dCtl);

   /* High frequency silicon capacitance */

   *pdCsh=*pdCsl;
   return; /* I feel sorrow for this. */

   if (!IsSurfaceStrongInversion(dUb,dVs1)) {
      *pdCsh=*pdCsl;
   } else { // Consider only minority carrier
      double dY1Crit=-1*dUb;
      dEs1=(dVfb+dVs1*dVth-dVg)*dCox/desub;
      GetUxWithPoissonEquation(dVs1,dEs1/dVth,&vX,&vY1,&vY2,&nL,&nH);
      ratint(vY1+nL-1,vX+nL-1,nH-nL+1,dY1Crit,&dX,&dError);
      ratint(vX+nL-1,vY2+nL-1,nH-nL+1,dX,&dF1,&dError);
      *pdCsh=desub/(vX[nH]-dX);
      VDestroy(vX,nL,nH);
      VDestroy(vY1,nL,nH);
      VDestroy(vY2,nL,nH);
      return;
      dEs2=(dVfb+dVs2*dVth-(dVg+dVgDelta))*dCox/desub;
      GetUxWithPoissonEquation(dVs2,dEs2/dVth,&vX,&vY1,&vY2,&nL,&nH);
      ratint(vY1+nL-1,vX+nL-1,nH-nL+1,dY1Crit,&dX,&dError);
      ratint(vX+nL-1,vY2+nL-1,nH-nL+1,dX,&dF2,&dError);
      VDestroy(vX,nL,nH);
      VDestroy(vY1,nL,nH);
      VDestroy(vY2,nL,nH);
      dCth=desub*fabs((dF1-dF2)*dVth/dVgDelta);
      *pdCsh=dCox*dCth/(dCox-dCth);
   }
   return;
}
/*----------------------------------------------------------------------------*/
static void _GetUxDerivs_HanschModel( double x,double y[],double dydx[] )
/* Poisson equation d^2y/dx^2=[(1-exp(-(x/Lth)^2))*sinh(y+ub)-sinh(ub)]/Li^2
 * dy[1]/dx = y[2]
 * dy[2]/dx = ((1-exp(-(x/Lth)^2))*sinh(y[1]+ub)-sinh(ub))/Li^2
 */
{
   double Li2=_GetSubProperty_Tag->dLi2;
   double Ub=_GetSubProperty_Tag->dUb;
   double sinhUb=_GetSubProperty_Tag->dsinhUb;
   double Lth=_GetSubProperty_Tag->dLth;
   double dHansch=1-exp(-pow(x/Lth,2));
   dydx[1]=y[2];
   dydx[2]=(dHansch*sinh(y[1]+Ub)-sinhUb)/Li2;
}
static void _GetUxJacobn_HanschModel(
   double x,double y[],double dfdx[],double **dfdy,int n
   )
{
   double Li2=_GetSubProperty_Tag->dLi2;
   double Ub=_GetSubProperty_Tag->dUb;
   double Lth=_GetSubProperty_Tag->dLth;
   double dHansch=1-exp(-pow(x/Lth,2));
   dfdx[1]=0.0;
   dfdx[2]=(2*x/pow(Lth,2)*exp(-pow(x/Lth,2)))*sinh(y[1]+Ub)/Li2;//20031226
   dfdy[1][1]=0.;
	dfdy[1][2]=1.;
	dfdy[2][1]=dHansch*cosh(y[1]+Ub)/Li2;
	dfdy[2][2]=0.;
}
static double EvalVsWithHanschModel( double dVs ) //2003.12.17-
{
   double dVg=_GetSubProperty_dVg;
   double dVth=_GetSubProperty_Tag->dVth;
   double dVfb=_GetSubProperty_Tag->dVfb;
   double dCox=_GetSubProperty_Tag->dCox;
   double desub=_GetSubProperty_Tag->desub;
   double dUb=_GetSubProperty_Tag->dUb;
   double dni=_GetSubProperty_Tag->dni;
   double dsinhUb=_GetSubProperty_Tag->dsinhUb;
   double dLth=_GetSubProperty_Tag->dLth;
   int bDeepDepletion=_GetSubProperty_Tag->bDeepDepletion;
   double dF0,dEs,dHansch,dQs,dVgNew;

   VECTOR vX,vY1,vY2,vArea;
   int nL,nH,i;
   VECTOR vXNew,vYNew;
   int nLNew,nHNew;
   double dXCrit,dXStep;

//#define _DEBUG_HANSCH 1
#ifdef _DEBUG_HANSCH
Matrix m;
#endif

   dEs=(dVfb+dVs*dVth-dVg)*dCox/desub;
   if (SIGN(dVs*dEs)>0) return SIGN(dEs)*433612141;
   dF0=dEs/dVth; /* Semi-dimensionless surface electric field [/cm], Y.Kim */
   GetUxWithPoissonEquation(dVs,dF0,&vX,&vY1,&vY2,&nL,&nH);

   //dQs=vY2[nL]*dVth*desub; ????

//   if (!IsSurfaceInversion(dUb,dVs)) {
   dXCrit=dLth*4; // ~15A
   dXStep=2e-8; // 2A
   VChangeXStepsInARange(vX,vY1,nL,nH,&vXNew,&vYNew,&nLNew,&nHNew,vX[nL],dXCrit,dXStep);
   VDestroy(vX,nL,nH);vX=vXNew;
   VDestroy(vY1,nL,nH);vY1=vYNew;
   nL=nLNew;nH=nHNew;
   //}
#ifdef _DEBUG_HANSCH
m.m=0;m.rl=nL;m.rh=nH;m.cl=1;m.ch=1;
MAddVector(&(m.m),m.rl,m.rh,m.cl,m.ch,vX,TRUE,&(m.rh),&(m.ch));
MAddVector(&(m.m),m.rl,m.rh,m.cl,m.ch,vY1,TRUE,&(m.rh),&(m.ch));
#endif
   for (i=nL;i<=nH;i++) {
      dHansch=vX[i]/dLth;
      dHansch*=dHansch;
      dHansch=1-exp(-dHansch);
      vY1[i]=2*dni*(dHansch*sinh(vY1[i]+dUb)-dsinhUb);
   }
#ifdef _DEBUG_HANSCH
MAddVector(&(m.m),m.rl,m.rh,m.cl,m.ch,vY1,TRUE,&(m.rh),&(m.ch));
{char buf[16];
sprintf(buf,"zh%.2f",dVg);
if (dVg>0) MWriteToFile(buf,"%g",m.m,m.rl,m.rh,m.cl,m.ch);
MDestroy(m.m,m.rl,m.rh,m.cl,m.ch); }
#endif
   if (!VGetCumAreaVector(vX,vY1,nL,nH,FALSE,&vArea)) return 0.; /* ??? */
   dQs=-vArea[nH]*Qelectron;
   VDestroy(vArea,nL,nH);
   VDestroy(vX,nL,nH);
   VDestroy(vY1,nL,nH);
   dHansch=vY2[nL]*dVth*desub;
   VDestroy(vY2,nL,nH);

   dEs=dQs/desub;
   dVgNew=dVfb-dQs/dCox+dVs*dVth;

   _EvalVs_Result[0]=dQs; // When fitted, dQs equals vY2[nL]*dVth*desub.
   _EvalVs_Result[1]=dEs;

   return (dVgNew-dVg);
}

/******************************************************************************/

/* 20030316+0329 */
//static 20030430
int EchoMosParameters(
   const MOSTAG *MOSTag, /* 20031206 */
   MATRIX mMos,int nRl,int nRh,int nCl,int nCh
   )
{
   VECTOR vV,vC;
   int nPosition,nVec,nR;

   double vX[6],vY[6],dWdiff,dError,dVthermal,dKelvin,dVfb,dCfb,dUb,dVth;

   if (nCh!=MOS_MATRIX_COLUMN) return FALSE;

   dWdiff=GetWorkFuncDiffToSiEf(MOSTag->dKelvin,MOSTag->dWgate,MOSTag->bNType,MOSTag->dNsub);
   Echo(" Wgate-Wsub [V] = %.3g (Wg=%.3gV,Wb=%.3gV)\n",
      dWdiff,MOSTag->dWgate,MOSTag->dWgate-dWdiff);
   

   dVthermal=mMos[1][MOS_MATRIX_VSVOLT]/mMos[1][MOS_MATRIX_VS]; /* [V] */
   dKelvin=dVthermal*Qelectron/KBoltzman; /* [K] */

   MGetVector(mMos,TRUE,MOS_MATRIX_VS,nRl,nRh,&vV);
   if (!VGetValueIndexOfMonotonicVector(vV,nRl,nRh,0.0,&nPosition) ||
      nPosition<nRl+2 || nPosition>nRh-2) {
      VDestroy(vV,nRl,nRh);
      Echo(" Interpolaton did not succeed due to few data to cope with.");
      return FALSE;
   }
   VDestroy(vV,nRl,nRh);

   nVec=sizeof(vX)/sizeof(vX[0])-1; /* -1 to make base be 1 */
   for (nR=1;nR<=nVec;nR++) vX[nR]=mMos[nPosition-3+nR][MOS_MATRIX_VS];
   for (nR=1;nR<=nVec;nR++) vY[nR]=mMos[nPosition-3+nR][MOS_MATRIX_VG];
   polint(vX,vY,nVec,0.0,&dVfb,&dError); /* Press,Numerical Receipes in C,p.90 */
   for (nR=1;nR<=nVec;nR++) vY[nR]=mMos[nPosition-3+nR][MOS_MATRIX_CTH];
   polint(vX,vY,nVec,0.0,&dCfb,&dError); /* Press,Numerical Receipes in C,p.90 */
   Echo(" Interpolated Vfb [V] = %.3g\n",dVfb);
   Echo(" Interpolated Cfb [C/cm^2] = %.3g\n",dCfb);

   dUb=mMos[nPosition][MOS_MATRIX_UB];
   Echo(" Interpolated Ub (Ef-Ei) [V] = %.3g\n",dUb*dVthermal);

   /* For details on Vth, see Sze 2ed. pp.371-74. */
   MGetVector(mMos,TRUE,MOS_MATRIX_VS,nRl,nRh,&vV);
   if (!VGetValueIndexOfMonotonicVector(vV,nRl,nRh,-2*dUb,&nPosition) ||
      nPosition<nRl+2 || nPosition>nRh-2) {
      Echo(" Interpolated Vth [V] = *\n");
   } else {
      for (nR=1;nR<=nVec;nR++) vX[nR]=mMos[nPosition-3+nR][MOS_MATRIX_VS];
      for (nR=1;nR<=nVec;nR++) vY[nR]=mMos[nPosition-3+nR][MOS_MATRIX_VG];
      polint(vX,vY,nVec,-2*dUb,&dVth,&dError); /* Press,Numerical Receipes in C,p.90 */
      Echo(" Interpolated Vth [V] = %.3g\n",dVth);
   }
   VDestroy(vV,nRl,nRh);

   /* Y.Taur, Eq.(2.37) of p.25 for Nb and Eq.(2.162) of p.67 for Wdm */ {
   double dni,dNb,dWdm;
   dni=GetSiIntrinsicCarrierConc(dKelvin); /* [/cm^3] */
   dNb=dni*exp(dUb);
   dWdm=4*MOSTag->dRDCsub*VacPermittivity*dVthermal*log(dNb/dni)/Qelectron/dNb;
   dWdm=sqrt(dWdm);
   Echo(" Max depletion width, Wdm [nm] = %.3g (Nb=%.3g/cm3)\n",dWdm*1e7,dNb);
   }

   /* Hillard */
   MGetVector(mMos,TRUE,MOS_MATRIX_VG,nRl,nRh,&vV);
   MGetVector(mMos,TRUE,MOS_MATRIX_CTH,nRl,nRh,&vC);
   if (GetFlatBandVoltageByHillard(vV,vC,nRl,nRh,&dVfb))
   Echo(" Vfb (by Hillard method) [V] = %.3g <- strongly sensitive to non-ideality.\n",dVfb);
   VDestroy(vV,nRl,nRh);
   VDestroy(vC,nRl,nRh);

   return TRUE;
}

/* static <- be commented for MosCapacitorRegressor() */
int _IdealMosCapacitorEx(
   const MOSTAG *MTag,
   double dVg_Start,    /* [V] */
   double dVg_Stop,     /* [V] */
   double dVg_Step,     /* [V] */
   Matrix *mOut         /* output matrix */
   )
{
   extern double OpenBermanTable();
   extern double CloseBermanTable();
   int nWorkRowMax,nWorkColMax,nRow;
   double dVs_Start,dVs_Stop;
   double dWdiff,dEgapsub,dUb,dVs,dUs,dQs,dFs,dEs,dVg,dCsl,dCtl,dVsVolt,dEox,dVox,dCsh,dCth;
   MATRIX mWork;
   Matrix mBerman;
   SUBPROPERYTAG Tag;
   double (*EvaluateVs)(double);

   nWorkRowMax=(int)floor((dVg_Stop-dVg_Start)/dVg_Step)+1;
   nWorkColMax=MOS_MATRIX_COLUMN;
   /* Vs[],Us[],Sign[],F[],Qs[C/cm2],Vg[V],Csl[F/cm2],Ctl[F/cm2],
    * Vs[V],Vox[V],Eox[V/cm],BermanFactor,Csh[F/cm2],Cth[F/cm2],
    * (Ef(m)-Ef(si))[V],(Ef(m)-Ec(si))[V],(Ef(m)-Ev(si))[V]
    */
   mWork=dmatrix(1,nWorkRowMax,1,nWorkColMax);

   /* reserved for debugging 20030329
   * Nicollian,p.50 *
   Echo(".Bulk potential : Ef-Ei [V] = %.3g\n",dUb*dVth); 
   * Sze,p.372,Eq.26 *
   Echo(".Flat-band capacitance [C/cm^2] = %.3g\n",deox/(MTag->dTox*cmoverA+(deox/desi)*dLe));
   */

   /* Piecewise Equation Tag */
   Tag.bNType=MTag->bNType;
   Tag.bDeepDepletion=MTag->bDeepDepletion;
   Tag.bHighFrequency=MTag->bHighFrequency;
   Tag.dKelvin=MTag->dKelvin;
   Tag.dVth=GetThermalVoltage(MTag->dKelvin);
   Tag.dni=GetSiIntrinsicCarrierConc(MTag->dKelvin);
   Tag.dLi=GetIntrinsicDebyeLength(MTag->dKelvin,MTag->dRDCsub); /* [cm] */
   Tag.dLi2=Tag.dLi*Tag.dLi;
   Tag.dLe=GetExtrinsicDebyeLength(MTag->dKelvin,MTag->dRDCsub,MTag->dNsub); /* [cm] */
   Tag.dCi=GetIntrinsicDebyeCapacitance(MTag->dKelvin,RDCSilicon);
   Tag.dTox=MTag->dTox*cmoverA;
   Tag.dCox=GetSimpleMosCapacitance(MTag->dTox,MTag->dRDCox);
   Tag.desub=VacPermittivity*MTag->dRDCsub; /* Silicon dielectric constant. */
   Tag.deox=VacPermittivity*MTag->dRDCox; /* Oxide dielectric constant. */
   dWdiff= /* [V] Metal - Silicon */
      GetWorkFuncDiffToSiEf(MTag->dKelvin,MTag->dWgate,MTag->bNType,MTag->dNsub);
   Tag.dVfb=dWdiff+MTag->dVfbShift; /* for tunning to real data */
   dUb=log(MTag->dNsub/Tag.dni); /* Nicollian,p.52. -> [Ef-Ei(B)]/kT Nicollian,p.50 */
   if (!MTag->bNType) dUb=dUb*-1; /* Ub<0 for p-Si(NMOS), Ub>0 for n-Si. */
   Tag.dUb=dUb;
   Tag.dsinhUb=sinh(Tag.dUb);
   Tag.dLth=MTag->dHansch;

   dEgapsub=GetSiBandGapEnergy(MTag->dKelvin);

   /* Set fitting range of Vs */
   if (MTag->bNType) { /* PMOS, [V] inversion when Vs<0,i.e,band-bend-upward. */
      dVs_Start=-60;
      dVs_Stop=20;
   } else { /* NMOS, [V] inversion when Vs>0,i.e,band-bend-downward. */
      dVs_Start=-20;
      dVs_Stop=60;
   }

   switch (MTag->nMethod) {
   case MT_PIECEWISE :
      EvaluateVs=EvalVsWithPiecewiseModel;
      _GetSubProperty_Derivs=0;
      _GetSubProperty_Jacobn=0;
      break;
   case MT_BERMAN :
      EvaluateVs=EvalVsWithPiecewiseModel;
      _GetSubProperty_Derivs=0;
      _GetSubProperty_Jacobn=0;
      OpenBermanTable( /* Inversion dispersion factor [Y.Kim+Berman] */
         //MTag->dKelvin,dUb,dVs_Start,dVs_Stop,
         MTag->dKelvin,dUb,MTag->bNType?dVs_Stop:dVs_Start,MTag->bNType?dVs_Start:dVs_Stop,
         &mBerman.m,&mBerman.rl,&mBerman.rh,&mBerman.cl,&mBerman.ch);
      break;
   case MT_NUMERICALPOISSON :
      EvaluateVs=EvalVsWithPoissonEquation;
      _GetSubProperty_Derivs=_GetUxDerivs_PoissonEquation;
      _GetSubProperty_Jacobn=_GetUxJacobn_PoissonEquation;
      break;
   case MT_HANSCH :
      EvaluateVs=EvalVsWithHanschModel;
      _GetSubProperty_Derivs=_GetUxDerivs_HanschModel;
      _GetSubProperty_Jacobn=_GetUxJacobn_HanschModel;
      if (Tag.dLth<1e-8) Tag.dLth=1e-8; //1e-8cm=1A
      break;
   }

   _GetSubProperty_Tag=&Tag;

   for (nRow=1;nRow<=nWorkRowMax;nRow++) {

      dVg=dVg_Start+(nRow-1)*dVg_Step;

      /* Dimensionless surface band-bending Vs, which means Pi(s)-Pi(B) */
      _GetSubProperty_dVg=dVg;
      /* Press, Numerical Recipes in C, p.265 -> rtflsp(func,xdLow1,dHigh,xacc) --> bad */
      /* Press, Numerical Recipes in C, p.266 -> rtsec(func,dLow,dHigh,xacc)  --> bad */
      /* Press, Numerical Recipes in C -> zriddr(...) --> bad */
      /* Press, Numerical Recipes in C, p.268 -> zbrent(func,dLow,dHigh,tol)  --> good */
      dVs=zbrent(EvaluateVs,dVs_Start,dVs_Stop,1e-5);
      /* Further more */
      (*EvaluateVs)(dVs);
      dQs=_EvalVs_Result[0];
      dEs=_EvalVs_Result[1];
      dFs=dEs/(-SIGN(dVs)*Tag.dVth/Tag.dLi);
      if (dVg_Step>0) dVs_Start=dVs; //20031226
      else dVs_Stop=dVs;
      //dVs_Stop=dVs+dVg_Step/Tag.dVth*2; /* '2' is the value determined experimentally */

      /* Dimensionless surface potential Us, corresponding to Ef-Ei(S) */
      dUs=dVs+dUb;

      /* Checking */
      /* Vs[V] <-- [Ei(B)-Ei(S)]/q [Nicollian,p.51 Eq.2.40] */
      dVsVolt=dVs*Tag.dVth;
      /* Vox=Vg-Vfb-Vs [V] [Taur, p.68 Eq.2.167 + p.75 Eq.2.180 + p.117 comment] */
      dVox=dVg-Tag.dVfb-dVsVolt; /* --> dVox=-dQs/dCox [Y.Kim] */
      dEox=dVox/(MTag->dTox*cmoverA)*-1e-6; /* Vox/Tox[MV/cm] */
                            /* -1 -> to correct error in sign. 20030310 Y.Kim*/

      /* Sze,p.371,Eq.(24) : for debugging */
      //dEox=dQs/(VacPermittivity*MTag->dRDC)*1e-6; /* [MV/cm] */
      /* for debugging. Y.Kim,20031206 */
      //dFs=dEox*RDCOxide/RDCSilicon*1e6;

      /* Assigning */
      mWork[nRow][MOS_MATRIX_VG]=dVg; /* [V] */
      mWork[nRow][MOS_MATRIX_VS]=dVs; /* [] */
      mWork[nRow][MOS_MATRIX_US]=dUs; /* [] */
      mWork[nRow][MOS_MATRIX_FS]=dFs; /* [] */
      mWork[nRow][MOS_MATRIX_QS]=dQs; /* [C/cm2] */
      mWork[nRow][MOS_MATRIX_UB]=dUb; /* [] */
      mWork[nRow][MOS_MATRIX_VSVOLT]=dVsVolt; /* Vs[V] */
      mWork[nRow][MOS_MATRIX_VOX]=dVox; /* Vox[V] */
      mWork[nRow][MOS_MATRIX_EOX]=dEox; /* Eox[MV/cm] */
      /* Ef(Metal)-Ef(Silicon) [V] 20030310 */
      mWork[nRow][MOS_MATRIX_EFMEFS]=-1*dVg;
      /* Ef(m)-Ec(si) at the surface. [V] 20030310+20030319 */
      mWork[nRow][MOS_MATRIX_EFMECS]=-1*dVg-(dVsVolt-dUb*Tag.dVth)-dEgapsub/2;
      /* Ef(m)-Ev(si) at the surface. [V] 20030310+20030319 */
      mWork[nRow][MOS_MATRIX_EFMEVS]=-1*dVg-(dVsVolt-dUb*Tag.dVth)+dEgapsub/2;
   }

   if (MTag->nMethod==MT_PIECEWISE) {
      double dVth=Tag.dVth;
      double dKelvin=Tag.dKelvin;
      double desub=Tag.desub;
      double dni=Tag.dni;
      int nSign;
      double dNumerator;
      for (nRow=1;nRow<=nWorkRowMax;nRow++) {
         dVs=mWork[nRow][MOS_MATRIX_VS];
         dFs=mWork[nRow][MOS_MATRIX_FS];
         /* Sign */
         nSign=SIGN(dVs);
         /* Low Frequency Calculation */
         /* Vg[V] */
         /* dVg=dVfb-dQs/dCox+dVth*dVs; 20030814 */
         /* Numerator */
         dNumerator=nSign/dVth*sqrt(2*KBoltzman*dKelvin*desub*dni)
            *(sinh(dVs+dUb)-sinh(dUb));
         /* Csl[F/cm2] in low frequency */
         dCsl=dNumerator/dFs;
         /* High Frequency Calculation */
         if (IsSurfaceStrongInversion(dUb,dVs)) {
            dFs=sqrt(2*(/*cosh(dUs)*/-cosh(dUb)-sinh(dUb)*dVs));
            dNumerator=nSign/dVth*sqrt(2*KBoltzman*dKelvin*desub*dni)
               *(-sinh(dUb));
         }
         /* Csh[F/cm2] in high frequency */
         dCsh=dNumerator/dFs;
         /* Ctl[F/cm2] Total capacitance in low frequency */
         dCtl=(Tag.dCox*dCsl)/(Tag.dCox+dCsl);
         /* Cth[F/cm2] Total capacitance in high frequency */
         dCth=(Tag.dCox*dCsh)/(Tag.dCox+dCsh);
         /* Assigning */
         mWork[nRow][MOS_MATRIX_CSL]=dCsl; /* [F/cm2] Low Frequency */
         mWork[nRow][MOS_MATRIX_CTL]=dCtl; /* [F/cm2] Low Frequency */
         mWork[nRow][MOS_MATRIX_CSH]=dCsh; /* [F/cm2] High Frequency */
         mWork[nRow][MOS_MATRIX_CTH]=dCth; /* [F/cm2] High Frequency */
      }
   } else if (MTag->nMethod==MT_BERMAN) {
      extern double LookupBermanTable();
      double dVth=Tag.dVth;
      double dKelvin=Tag.dKelvin;
      double desub=Tag.desub;
      double dni=Tag.dni;
      int nSign;
      double dNumerator,dBermanFactor;
      for (nRow=1;nRow<=nWorkRowMax;nRow++) {
         dVs=mWork[nRow][MOS_MATRIX_VS];
         /* Low Frequency Calculation, like Piecewise case */
         nSign=SIGN(dVs);
         dNumerator=nSign/dVth*sqrt(2*KBoltzman*dKelvin*desub*dni)
            *(sinh(dVs+dUb)-sinh(dUb));
         dCsl=dNumerator/dFs;
         /* High Frequency Calculation */
         /* Inversion dispersion factor [Y.Kim+Berman] */
         dBermanFactor=LookupBermanTable(
            mBerman.m,mBerman.rl,mBerman.rh,mBerman.cl,mBerman.ch,dUb>0,dVs);
         /* Numerator */
         dNumerator=SIGN(dVs)/dVth*sqrt(2*KBoltzman*dKelvin*desub*dni)
            *((1-dBermanFactor)*sinh(dVs+dUb)-sinh(dUb));   
         /* Csh[F/cm2] in high frequency */
         dCsh=dNumerator/dFs;
         /* Assigning */
         dCtl=(Tag.dCox*dCsl)/(Tag.dCox+dCsl);
         dCth=(Tag.dCox*dCsh)/(Tag.dCox+dCsh);
         mWork[nRow][MOS_MATRIX_CSL]=dCsl;
         mWork[nRow][MOS_MATRIX_CTL]=dCtl;
         mWork[nRow][MOS_MATRIX_CSH]=dCsh;
         mWork[nRow][MOS_MATRIX_CTH]=dCth;
      }
   } else if (MTag->nMethod==MT_NUMERICALPOISSON||MTag->nMethod==MT_HANSCH) {
      double deox=Tag.deox;
      double dVth=Tag.dVth;
      double dTox=Tag.dTox;
      double dCox=Tag.dCox;
      VECTOR vX,vY,vS;
      int nL=1;
      int nH=nWorkRowMax;
      MGetVector(mWork,TRUE,MOS_MATRIX_VG,nL,nH,&vX);
      MGetVector(mWork,TRUE,MOS_MATRIX_VS,nL,nH,&vY);
      if (nH>nL)
         VGetSlopeVector(vX,vY,nL,nH,TRUE,&vS); // dVsDelta/dVgDelta
      else { // nL=nH=1
         double dVgDelta=0.04; //4mV
         double dVsNew;
         dVg=mWork[nL][MOS_MATRIX_VG];
         dVs=mWork[nL][MOS_MATRIX_VS];
         _GetSubProperty_dVg=dVg+dVgDelta;
         dVsNew=zbrent(EvaluateVs,dVs,dVs+dVgDelta*200,1e-7); //1e-7 <-- 20031226
         vS=VCreate(nL,nH);
         vS[nL]=(dVsNew-dVs)/dVgDelta;
      }
      for (nRow=nL;nRow<=nH;nRow++) {
         if (nH>nL&&0) {
            double dVgDelta=0.04; //4mV
            double dVsNew;
            dVg=mWork[nL][MOS_MATRIX_VG];
            dVs=mWork[nL][MOS_MATRIX_VS];
            _GetSubProperty_dVg=dVg+dVgDelta;
            dVsNew=zbrent(EvaluateVs,dVs,dVs+dVgDelta*200,1e-7); //1e-7 <-- 20031226
            vS[nL]=(dVsNew-dVs)/dVgDelta;
         }
         /* Low frequency silicon capacitance */
         dCtl=deox*fabs(1-vS[nRow]*dVth)/dTox;
         //1)/dEox1=(dVg-dVfb-dVs1*dVth)/dTox;
         //1)/dEox2=(dVg+dVgDelta-dVfb-dVs2*dVth)/dTox;
         //1)/dCtl=deox*fabs((dEox2-dEox1)/dTox/dVgDelta);
         //2)/dCtl=desub*fabs((dEs1-dEs2)/dVgDelta);
         dCsl=dCox*dCtl/(dCox-dCtl);
         /* High frequency silicon capacitance */
         dCth=dCtl; // T_T
         dCsh=dCsl; // T_T
         /* Assigning */
         mWork[nRow][MOS_MATRIX_CSL]=dCsl;
         mWork[nRow][MOS_MATRIX_CTL]=dCtl;
         mWork[nRow][MOS_MATRIX_CSH]=dCsh;
         mWork[nRow][MOS_MATRIX_CTH]=dCth;
      }
      VDestroy(vX,nL,nH);
      VDestroy(vY,nL,nH);
      VDestroy(vS,nL,nH);
   }

   switch (MTag->nMethod) {
   case MT_BERMAN: CloseBermanTable(mBerman.m,mBerman.rl,mBerman.rh,mBerman.cl,mBerman.ch);
      break;
   }

   mOut->m=mWork;
   mOut->rl=1;
   mOut->rh=nWorkRowMax;
   mOut->cl=1;
   mOut->ch=nWorkColMax;

   return TRUE;
}

int IdealMosCapacitorEx( ARGUMENTS )
   ARGULIST
{
   MOSTAG MOSTag;
   double dVg_Start,dVg_Stop,dVg_Step;
   int nIndex,nArgument;
   Matrix mMos;
   char *pTok,*qDelimiter=",";

   Echo(" V.2.0\n");
   
   if (chrcount(SWEEP,*qDelimiter)!=2) {
      Echo(0,"%s()\nToo many or short argument in SWEEP. Only 3 required : \n%s \n",
         THIS_FILE,SWEEP);
      return FALSE;
   }
   nArgument=strtokcount(ARGUMENT,qDelimiter);
   if (nArgument<7) { ERROR_IN_ARGUMENT:
      Echo(0,
         "%s()\n"
         "Too many or short argument in ARGUMENT. \n"
         "7 or 8 (for Hansch model) parameters required. \n\n"
         "Those are MOS-type [n|p],temperature [K],gate work function [V], \n"
         "flat-band voltage shift [V] (which adds to Vfb),gate oxide thickness [A], \n"
         "oxide dielectric constant, and substrate concentration [/cm3], \n"
         "which should be kept in order and separated by comma. \n\n"
         "Your agrument is as following : \n"
         "%s \n",THIS_FILE,ARGUMENT);
      return FALSE;
   }

   /* 20031204 */
   MOSTag.nMethod=MT_DEMO;
   MOSTag.bDeepDepletion=(NOPTION%10) ? 1:0;
   MOSTag.bHighFrequency=(NOPTION%100-NOPTION%10) ? 1:0;
   switch (NOPTION-NOPTION%100) {
   default:
   case 000 : MOSTag.nMethod=MT_DEMO;break;
   case 100 : MOSTag.nMethod=MT_PIECEWISE;break;
   case 200 : MOSTag.nMethod=MT_BERMAN;break;
   case 300 : MOSTag.nMethod=MT_NUMERICALPOISSON;break;
   case 400 : MOSTag.nMethod=MT_HANSCH;break;
   }
   if (MOSTag.nMethod==MT_HANSCH&&nArgument!=8) goto ERROR_IN_ARGUMENT;

   for (nIndex=0;nIndex<=2;nIndex++) {
      pTok=strtokbyindex(SWEEP,qDelimiter,nIndex);
      switch (nIndex) {
      case 0 : dVg_Start=atof(pTok);break; /* [V] Gate voltage */
      case 1 : dVg_Stop=atof(pTok);break; /* [V] Gate voltage */
      case 2 : dVg_Step=atof(pTok);break; /* [V] Gate voltage */
      }
      freeEx(pTok);
   }
   for (nIndex=0;nIndex<nArgument;nIndex++) {
      pTok=strtokbyindex(ARGUMENT,qDelimiter,nIndex);
      switch (nIndex) {
      case 0 : MOSTag.bNType=tolower(*pTok)=='n'?0:1;break; /* NMOS/PMOS */
      case 1 : MOSTag.dKelvin=atof(pTok)+KKelvin;break;  /* [K] Kelvin degree */
      case 2 : MOSTag.dWgate=atof(pTok);break;/* [V] Gate metal work function */
      case 3 : MOSTag.dVfbShift=atof(pTok);break; /* [V] Flat-band voltage shift */
      case 4 : MOSTag.dTox=atof(pTok);break; /* [A] Gate oxide thicknesse */
      case 5 : MOSTag.dRDCox=atof(pTok);break; /* [] Relative dielectric constant of oxide */
      case 6 : MOSTag.dNsub=atof(pTok);break; /* [#/cm3] Substrate concentration */
      case 7 : MOSTag.dHansch=atof(pTok);break; /* [cm] Hansch factor */
      }
      freeEx(pTok);
   }
   MOSTag.dRDCsub=RDCSilicon;

   if (MOSTag.nMethod==MT_DEMO) {
      Echo(" Demonstration C-V : capacitance will be computed by PIECEWISE model.\n");
      MOSTag.nMethod=MT_PIECEWISE;
      MOSTag.bNType=1;         /* [Boolean] true(1) = n-type (silicon) = PMOS */
      MOSTag.dKelvin=290;      /* [K] Kelvin degree */
      MOSTag.dWgate=4.1;/* [V] Al=4.1V, Ag=5.1V [Sze p.396 Table 3 Metal Work Function (Volts)] */
      MOSTag.dVfbShift=0.0;    /* [V] Flat-band voltage shift */
      MOSTag.dTox=10;          /* [A] Gate oxide thickness */
      MOSTag.dRDCox=3.9;    /* [] Relative dielectric constant of oxide */
      MOSTag.dRDCsub=RDCSilicon;  /* [] Relative dielectric constant of substrate */
      MOSTag.dNsub=7.035e18;   /* [#/cm3] Substrate concentration ; 7.03e18->Ub=20V for p-Si,-20V for n-Si */
      MOSTag.dHansch=15e-8;   /* [cm] 15A <-- Hansch factor */
      dVg_Start=-2.5;   /* [V] Gate voltage */
      dVg_Stop=+2.5;    /* [V] Gate voltage */
   }
   
   Echo(" Option=%d (%s,%s,%sDeepDepletion)\n",NOPTION,
      MOSTag.nMethod==MT_PIECEWISE ? "Piecewise":
      MOSTag.nMethod==MT_BERMAN ?    "Piecewise+Berman":
      MOSTag.nMethod==MT_NUMERICALPOISSON ?   "Poisson":
      MOSTag.nMethod==MT_HANSCH ?    "Hansch": "?",
      MOSTag.bHighFrequency ?        "HF":"LF",
      MOSTag.bDeepDepletion ?        "w/":"w/o");
   Echo(" Parameters: %cMOS,%.0fK,Wgate=%geV,DVfb=%gV,Tox=%gA,RDC=%gA,Nb=%s/cm^3\n",
      MOSTag.bNType?'P':'N',MOSTag.dKelvin,MOSTag.dWgate,MOSTag.dVfbShift,
      MOSTag.dTox,MOSTag.dRDCox,pTok=dtostr(MOSTag.dNsub,"%.2e"));
   freeEx(pTok);

   _IdealMosCapacitorEx(&MOSTag,dVg_Start,dVg_Stop,dVg_Step,&mMos);
   EchoMosParameters(&MOSTag,mMos.m,mMos.rl,mMos.rh,mMos.cl,mMos.ch);

   *MTX=mMos.m;
   Echo(" MTX=[%d..%d][%d..%d]\n",*MRL=mMos.rl,*MRH=mMos.rh,*MCL=mMos.cl,*MCH=mMos.ch);
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
/* uIdealMosCapacitorEx.c */
