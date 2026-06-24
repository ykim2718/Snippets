/******************************************************************************/
#define MOUDLENAME "MosDiodeRegressor()"

#include "usrfunc.h"
uFuncTableTag uMosDiodeRegressorTag={
"MosDiodeRegressor(J-V)",
"type=MosDiodeRegressor                                                      \n"
"argument=PF xyt=(1,2,40)(1,3,80)(1,4,120) unit=5 range=-2e6,2e6,0.97",
"[Y.Kim]                                                                     \n"
"2003.0522-0721,0807,0820,0825-0829,0921-1008,1112                           \n"
"2004.0114-15,0211,0326,0409-0410,0611                                       \n"
"                                                                            \n"
"[Input]                                                                     \n"
"ARGUMENT=<MODEL>                                                            \n"
"! OHM (Ohmic Conduction) : |J|=a*|V|                                        \n"
"! OHM2 (Ohmic Conduction ) : |J|=a*|V|+yi                                   \n"
"! SCLCEXP (SCLC with exponential trap level distribution) : |J|=a*|V|^(b+1) \n"
"! SCLCUNI (SCLC with uniform trap level distribution) : |J|=a*|V|*exp(b*|V|) \n"
"! SCLCSQR (Space-Charge-Limited Current with sqaure law of voltage) : |J|=a*|V|^2 \n"
"! LAMPERT (Mixed Model of Ohmic and SCLC) : |J|=a*|V|+b*|V|^2               \n"
"! CUBE (SCLC) : |J|=a*|V|^3                                                 \n"
"! DT (Direct Tunneling) : |J|=a*sinh(b*|Eox|),b=3.125e-7*sq(Tox)*sqrt((m*/m0)/BarrierHeight) \n"
"! DTLEE2 (Direct Tunneling) : |J|=a*Eox^2*exp(-b/|Eox|*(1-(1-|Eox|*c)^(2/3))),c=Tox/BH \n"
"! FN (Flower-Nordheim Tunneling) : |J|=a*|Eox|^2*exp(-b/|Eox|)              \n"
"! POOLE : |J|=a*exp(b*|Eox|)                                                \n"
"! SCHOTTKY (Richardson-Schottky) : |J|=a*exp(b*|Eox|^0.5)                   \n"
"! PF (Poole-Frenkel) : |J|=a*|Eox|*exp(b*|Eox|^0.5)                         \n"
"! STAT (Shallow Trap-Assisted Tunneling) : |J|=a(1-b/|Eox|)*exp(-c/|Eox|)/|Eox| \n"
"! DTAT (Deep Trap-Assisted Tunneling) : |J|=a/|Eox|*exp(-b/|Eox|)           \n"
"! Note 1) When <MODEL> is '*', every model is analyzed.                     \n"
"! Note 2) J [=] A/cm2, V [=] V, Eox [=] V/cm                                \n"
"XYT=(X,Y,T)(X1,X2,Y,T)...(X,Y,T)                                            \n"
"! The first in parentheses is X vector index, which should be V [V] or Eox [V/cm], and monotonic. \n"
"! The second is Y column index, which should be J [A/cm^2].                 \n"
"! The third is temperature in Celcius degree, neither z-index nor floating. \n"
">>>>>>>>>>> (Vg,Jg,Temperature) (Vg,Eox,Jg,Temperature) <<<<<<<<<< "
"ARGUMENT3=TOX,MRATIO                                                        \n"
"! TOX [nm] : Physical thickness of insulator. (for DT)                      \n"
"! MRATIO [] (=m*/m0) : Effective electron mass ratio. (for DT and FN)       \n"
"OPTION= NOT-USED                                                            \n"
"SUBOPTION|UNIT=<N>                                                          \n"
"! N [integer] : Defines minimum number of data point to fit.                \n"
"! Should be greater than 3 at least. Default is 5.                          \n"
"RANGE=[<L>,<H>,<G>|(<L>,<H>,<G>)]                                           \n"
"! L [double|*] : Lower limit X for fitting. <*> means data minimum.         \n"
"! H [double|*] : Upper limit X for fitting. <*> means data minimum.         \n"
"! G [double|*] : Lower limit of \"GoodnessOfFit\". Usually 1> and >0.95     \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! See Log window.   "
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

extern int Echo();
extern int GetFittingRange(
   VECTOR vX,int nRl,int nRh,int nFitTotal,double dL,double dH,
   int *nL,int *nH
   );

#if !defined(SIGN)
#define SIGN(x)   ((x)>=0 ? 1:-1)
#endif

/*
DT_HESTO     P.Hesto,Instabilities in silicon devices vol.1,1986,p.291,Eq.(5.28)
DT_LEE       2000,198-99,W.Lee,Symp.VLSI Tech.
DT_SCHUEGRAF 1992,18-19,K.Schuegraf,Symp.VLSI Tech.
*/
static char *qConductionModels[]={
   "OHM",
   "OHM2",
   "SCLCEXP",
   "SCLCUNI",
   "SCLCSQR",
   "LAMPERT",
   "CUBE",
   "DT",//"DT_HESTO","DT_SCHUEGRAF","DT_LEE"
   "DTLEE2",
   "FN",
   "POOLE",
   "SCHOTTKY",
   "PF",
   "STAT",
   "DTAT"
};
#define MODEL_OHM       0
#define MODEL_OHM2      1
#define MODEL_SCLCEXPONENTIAL 2
#define MODEL_SCLCUNIFORM     3
#define MODEL_SCLCSQUARE      4
#define MODEL_LAMPERT   5
#define MODEL_SCLCCUBE  6
#define MODEL_DT        7
#define MODEL_DT_LEE2   8
#define MODEL_FN        9
#define MODEL_POOLE     10
#define MODEL_SCHOTTKY  11
#define MODEL_PF        12
#define MODEL_STAT      13
#define MODEL_DTAT      14

/******************************************************************************/

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

/* J=a*Eox+(yi) -> y=a[1]*x or y=a[1]+a[2]*x */
static void _OHM(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   if (na==1) {
      *y=a[1]*x;
      dyda[1]=x;
   } else /* if (na==2) */ {
      *y=a[1]+a[2]*x;
      dyda[1]=1.;
      dyda[2]=x;
   }
}

/* J=a*Eox^(b+1) -> ln(J)=ln(a)+b+1)*Eox -> y=a[1]+a[2]*x */
static void _SCLCEXPONENTIAL(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   _OHM(x,a,y,dyda,na);
}

/* D.R.Lamb,"Electrical Conduction Mechanisms in Thin Insulating Films,"
 * 1967,p.30,Eq.(4.28)
 * J=a*Eox*exp(b*Eox) -> ln(J/Eox)=ln(a)+b*Eox -> y=a[1]+a[2]*x */
static void _SCLCUNIFORM(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   *y=a[1]+a[2]*x;
   dyda[1]=1;
   dyda[2]=x;
}

/* J=a*Eox^2 -> ln(J)=ln(a)+2*ln(Eox) -> y=a[1]+2*x */
static void _SCLCSHALLOW(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   *y=a[1]+2*x;
   dyda[1]=1;
}

/* J=a*Eox+b*Eox^2 -> y=a[1]*x+a[2]*x^2 */
static void _LAMPERT(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   double xx=x*x;
   *y=a[1]*x+a[2]*xx;
   dyda[1]=x;
   dyda[2]=xx;
}

/* J=a*Eox^3 -> ln(J)=ln(a)+3*ln(Eox) -> y=a[1]+3*x */
static void _SCLCCUBE(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   *y=a[1]+3*x;
   dyda[1]=1;
}

/* P.Hesto,Instabilities in silicon devices vol.1,1986,p.291,Eq.(5.28)
 * J=a*sinh(b*Fox) -> ln(J)=ln(a)+ln(sinh(b*Fox)) -> y=a[1]+ln(sinh(a[2]*x))
 * where Fox=3.125e7*s^2*Eox and b=sqrt(MassRatio/BarrierHeight)
 */
static void _DT(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   *y=a[1]+log(sinh(a[2]*x));
   dyda[1]=1;
   dyda[2]=x*cosh(a[2]*x)/sinh(a[2]*x);
}

/* Approximated Form of Lee Model [20041221]
 * Lee model:
 *   2000,198-99,W.Lee,Symp.VLSI Tech.pdf
 *   2000,21(11),540-42,Y.Yeo,IEEE Elec.Dev.Lett.pdf
 *   1999,20(6),268-70,W.Lee,IEEE Elec.Dev.Lett.pdf
 * Approximation of Lee model:
 *   E. Miranda. Submitted to APL 2004.
 *   1999,86(1),480-86,C.Chaneliere,J.Appl.Phys.pdf
 * Coding form:
 *   |J|=a*Eox^2*exp(-b/|Eox|*(1-(1-|Eox|*c)^(2/3))),c=Tox/BH
 *   -> ln(|J|/Eox^2)=ln(a)-b/|Eox|*(1-(1-|Eox|*c)^(2/3))
 *   -> y=a[1]-a[2]/|x|*(1-(1-|x|*a[3])^(2/3))
 *   y=ln(|J|/Eox^2), x=|Eox|, a[1]=ln(a), a[2]=b, a[3]=c
 */
static void _DTLEE2(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   double z,z23,z13;

   z=1-x*a[3];
   /* If z<0, current will not be DT but FN.
    * So, following is under the assumption of positive z.
    */
   z23=exp(1./3*log(z*z)); /* Be carefule that wrong is "=exp(1/3*log(z*z));" */
   z13=sqrt(1/z23);
   *y=a[1]-a[2]/x*(1-z23);
   dyda[1]=1;
   dyda[2]=-1./x*(1-z23);
   dyda[3]=2./3*a[2]*z13; /* Be carefule that wrong is "=2/3*a[2]*z1;" */
}

/* P.Hesto,"Instabilities in silicon devices vol.1",1986
 * p.291,Eq.(5.30)
 * J=a*Eox^2*exp(-b/Eox) -> ln(J/Eox^2)=ln(a)-b/Eox -> y=a[1]-a[2]*x */
static void _FN(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   *y=a[1]-a[2]*x;
   dyda[1]=1.;
   dyda[2]=-x;
}

/* "A general bulk-limited transport analysis of a 10 nm-thick oxide
 * stress-induced leakage current," B. De Salvo et al.,
 * Solid-State Electronics 44(2000)895-903
 * J=a*exp(b*Eox) -> ln(J)=ln(a)+b*Eox -> y=a[1]+a[2]*x */
static void _POOLE(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   _OHM(x,a,y,dyda,na);
}

/* P.Hesto,"Instabilities in silicon devices vol.1",1986
 * p.287,Eq.(5.22)
 * J=a*exp(b*Eox^0.5) -> ln(J)=ln(a)+b*Eox^0.5 -> y=a[1]+a[2]*x */
static void _SCHOTTKY(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   _OHM(x,a,y,dyda,na);
}

/* P.Hesto,"Instabilities in silicon devices vol.1",1986
 * p.304,Eq.(5.55)
 * J=a*Eox*exp(b*Eox^0.5) -> ln(J/Eox)=ln(a)+b*Eox^0.5 -> y=a[1]+a[2]*x */
static void _PF(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   _OHM(x,a,y,dyda,na);
}

/*
 [Yang1996] B.Yang et al., "Modelling of trap-assisted electronic
 conduction in thin thermally nitrided oxide films,"
 Solid-State Electronics 39[3]385-390(1996).
 |J|=a(1-b/|Eox|)*exp(-c/|Eox|)/|Eox| ->
 |J*Eox|=a(1-b/|Eox|)*exp(-c/|Eox|) -->
 ln(|J*Eox|)=ln(a)+ln(1-b/|Eox|)-c/|Eox| --->
 y=a[1]+ln(1-a[2]*x)-a[3]*x
 */
static void _STAT(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   *y=a[1]+log(1-a[2]*x)-a[3]*x;
   dyda[1]=1;
   dyda[2]=-x/(1-a[2]*x);
   dyda[3]=-x;
}

/*
 [Fleischer1993] S.Fleischer and P.T.Lai, gA new method for extracting
 the trap energy in insulators,h J.Appl.Phys. 73[7]3348-51(1993).
 |J|=a/|Eox|*exp(-b/|Eox|) ->
 ln(|J*Eox|)=ln(a)-b/|Eox| -->
 y=a[1]+a[2]*x
 */
static void _DTAT(x,a,y,dyda,na)
double x,a[],*y,dyda[];
int na;
{
   _OHM(x,a,y,dyda,na);
}

static int ComplyFittingVectorsWithModel(
   int nModel,VECTOR vX,VECTOR vY,
   int nL,int nH,
   double dTox // Physical Tox [cm]
)
{
   int j;
   double dX,dY;

   switch (nModel) {
   case MODEL_OHM :
   case MODEL_OHM2 :
   /* J=a*|V|+yi -> y=a[1]*x+a[2] */
      for (j=nL;j<=nH;j++) vX[j]=fabs(vX[j]); /* 20031006 */
      break;
   case MODEL_SCLCEXPONENTIAL :
   /* |J|=a*|V|^(b+1) -> ln(|J|)=ln(a)+(b+1)*ln(|V|) -> y=a[1]+a[2]*x */
      for (j=nL;j<=nH;j++) {
         vX[j]=log(fabs(vX[j]));
         vY[j]=log(fabs(vY[j]));
      }
      break;
   case MODEL_SCLCUNIFORM :
   /* |J|=a*|V|*exp(b*|V|) -> ln(|J|/|V|)=ln(a)+b*|V| -> y=a[1]+a[2]*x */
      for (j=nL;j<=nH;j++) vX[j]=fabs(vX[j]); /* 20031006 */
      for (j=nL;j<=nH;j++) vY[j]=log(fabs(vY[j]/vX[j]));
      break;
   case MODEL_SCLCSQUARE :
   /* |J|=a*|V|^2 -> ln(|J|)=ln(a)+2*ln(|V|) -> y=a[1]+2*x */
      for (j=nL;j<=nH;j++) {
         vX[j]=log(fabs(vX[j]));
         vY[j]=log(fabs(vY[j]));
      }
      break;
   case MODEL_LAMPERT :
   /* J=a*|Eox|+b*|Eox|^2 -> y=a[1]*x+a[2]*x^2 */
      for (j=nL;j<=nH;j++) vX[j]=fabs(vX[j]); /* 20031006 */
      break;
   case MODEL_SCLCCUBE :
   /* |J|=a*|V|^3 -> ln(|J|)=ln(a)+3*ln(|V|) -> y=a[1]+3*x */
      for (j=nL;j<=nH;j++) {
         vX[j]=log(fabs(vX[j]));
         vY[j]=log(fabs(vY[j]));
      }
      break;
   case MODEL_DT :
      /* P.Hesto,"Instabilities in silicon devices vol.1",1986,p.291,Eq.(5.28)
       * J=a*sinh(b*|Eox|) -> ln(|J|)=ln(a)+ln(sinh(b*|Eox|)) -> y=a[1]+ln(sinh(a[2]*x))
       * where Fox=3.125e7*s^2*Eox and b=sqrt(MassRatio/BarrierHeight)
       */
      for (j=nL;j<=nH;j++) {
         vX[j]=fabs(vX[j])*3.125e7*dTox*dTox; //Fox=3.125e7*s^2*Eox
         vY[j]=log(fabs(vY[j]));
      }
      break;
   case MODEL_DT_LEE2 :
     /*   |J|=a*Eox^2*exp(-b/|Eox|*(1-(1-|Eox|*c)^(2/3))),c=Tox/BH
      *   -> ln(|J|/Eox^2)=ln(a)-b/|Eox|*(1-(1-|Eox|*c)^(2/3))
      *   -> y=a[1]-a[2]/|x|*(1-(1-|x|*a[3])^(2/3))
      *   y=ln(|J|/Eox^2), x=|Eox|, a[1]=ln(a), a[2]=b, a[3]=c
      */
      for (j=nL;j<=nH;j++) {
         dX=vX[j];
         dY=vY[j];
         vX[j]=fabs(dX);
         vY[j]=log(fabs(dY/(dX*dX)));
      }
      break;
   case MODEL_FN :
   /* |J|=a*|Eox|^2*exp(-b/|Eox|) -> ln(|J|/|Eox|^2)=ln(a)-b/|Eox| -> y=a[1]-a[2]*x */
      for (j=nL;j<=nH;j++) {
         dX=vX[j];
         dY=vY[j];
         vX[j]=fabs(1/dX);
         vY[j]=log(fabs(dY/(dX*dX)));
      }
      break;
   case MODEL_POOLE :
   /* |J|=a*exp(b*|Eox|) -> ln(|J|)=ln(a)+b*|Eox| -> y=a[1]+a[2]*x */
      for (j=nL;j<=nH;j++) vX[j]=fabs(vX[j]); /* 20031006 */
      for (j=nL;j<=nH;j++) vY[j]=log(fabs(vY[j]));
      break;
   case MODEL_SCHOTTKY :
   /* |J|=a*exp(b*|Eox|^0.5) -> ln(|J|)=ln(a)+b*|Eox|^0.5 -> y=a[1]+a[2]*x */
      for (j=nL;j<=nH;j++) {
         //vX[j]=pow(fabs(vX[j]),0.5)*SIGN(vX[j]);
         vX[j]=pow(fabs(vX[j]),0.5); /* 20031004 */
         vY[j]=log(fabs(vY[j]));
      }
      break;
   case MODEL_PF :
   /* |J|=a*|Eox|*exp(b*|Eox|^0.5) -> ln(|J|/|Eox|)=ln(a)+b*|Eox|^0.5 -> y=a[1]+a[2]*x */
      for (j=nL;j<=nH;j++) {
         dX=fabs(vX[j]);
         dY=vY[j];
         //vX[j]=pow(dX,0.5)*SIGN(vX[j]); /* 20030827 */
         vX[j]=pow(dX,0.5); /* 20031004 */
         vY[j]=log(dY/dX);
      }
      break;
   case MODEL_STAT :
      for (j=nL;j<=nH;j++) {
         vY[j]=log(fabs(vY[j]*vX[j]));
         vX[j]=1/fabs(vX[j]);
      }
      break;
   case MODEL_DTAT :
      for (j=nL;j<=nH;j++) {
         vY[j]=log(fabs(vY[j]*vX[j]));
         vX[j]=-1/fabs(vX[j]);
      }
      break;
   }

   return nH-nL+1;
}

static int EchoXYTArgumentsInParenthesis( //20041221
   const char *qXYT,const char *qDelimiter,int nIndex,
   int *nX1,int *nX2,int *nY,
   double *dKelvin
)
{
   int i,nCount;
   char *pXYT,*pTok;

   pXYT=(char*)qXYT;
   for (i=0;i<nIndex;i++) {
      pXYT=strchr(pXYT,'(');
      pXYT++;
   }

   nCount=strtokcount(pXYT,qDelimiter);
   if (nCount<=2||nCount>=4) return FALSE;

   nIndex=0;
   *nX1=atoi(pTok=strtokbyindex(pXYT,qDelimiter,nIndex++));
   freeEx(pTok);
   *nX2=nCount==4 ? atoi(pTok=strtokbyindex(pXYT,qDelimiter,nIndex++)):0;
   freeEx(pTok);
   *nY=atoi(pTok=strtokbyindex(pXYT,qDelimiter,nIndex++));
   freeEx(pTok);
   *dKelvin=atof(pTok=strtokbyindex(pXYT,qDelimiter,nIndex++));
   freeEx(pTok);
   *dKelvin+=KKelvin;

   switch (nCount) {
   case 3 : Echo("xyt(Vg,Jg,Temp)=%d,%d,%.1fK ",*nX1,*nY,*dKelvin);break;
   case 4 : Echo("xxyt(Vg,Eox,Jg,Temp)=%d,%d,%d,%.1fK ",*nX1,*nX2,*nY,*dKelvin);break;
   }

   return nCount;
}

int MosDiodeRegressor( ARGUMENTS )
   ARGULIST
{
   int j,k;
   int nModelTotal,nModelIndex,iModelIndex;
   int nXYT,iXYT,nFitTotal,nXCol,nX2Col,nYCol,nRLAnswer,nRHAnswer;
   int aBoundary[3],nBoundary,iBoundary; /* 20031004 */
   char *pArgument,*pXYT,*qDelimiter=",()",*pTok,*pL,*pH;
   double dKelvin/*[K]*/,dTox/*[cm]*/,dMRatio/*[]=m(*)/m(0)*/,dL,dH,dR2,dR2AtLeast;
   VECTOR vXData,vYData,vXCopy,vYCopy,vXMirror,vYMirror;
   int nVLow,nVHigh;

   /* Version */
   Echo(" V.1.9\n");

   /* Check "ARGUMENT" */ {
      int nModelOptionTotal;
      char *pAddr;
      nModelOptionTotal=GetModelTotal();
      if (strequ(ARGUMENT,"*")) {
         nModelTotal=nModelOptionTotal;
         pArgument=strdpl(qGetModelName(0));
         for (j=1;j<nModelTotal;j++) {
            pAddr=strvcat(pArgument,",",qGetModelName(j),0);
            freeEx(pArgument);
            pArgument=pAddr;
         }
      } else {
         nModelTotal=strtokcount(ARGUMENT,qDelimiter);
         for (j=0;j<nModelTotal;j++) {
            pTok=strtokbyindex(ARGUMENT,qDelimiter,j);
            k=GetModelIndex(pTok);
            freeEx(pTok);
            if (k<0) {
               pTok=itostr2(j+1,"%d");
               Echo(0,"%s\n%s model at your expression of <ARGUMENT=> is invalid: \n%s",
                  MOUDLENAME,pTok,ARGUMENT);
               freeEx(pTok);
               return FALSE;
            }
         }
         pArgument=strdpl(ARGUMENT);
      }
   }
   /* Check "XYT" */
   pXYT=ARGUMENT2[0]!='(' ? strvcat("(",ARGUMENT2,")",0):strdpl(ARGUMENT2);
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
   } else {
      nXYT/=3;
   }
   /* Check "NSUBOPTION" */
   nFitTotal=NSUBOPTION<5 ? 5:NSUBOPTION;
   /* Check "RANGE" */
   if (strtokcount(SWEEP,qDelimiter)!=3) {
      Echo(0,"%s\nParameters are not counted to 3 at the expression of <RANGE=>\n",
         MOUDLENAME);
      return FALSE;
   }
   pTok=strtokbyindex(SWEEP,qDelimiter,2);
   dR2AtLeast=pTok[0]!='*' ? atof(pTok):0.5; //20031112
   freeEx(pTok);
   /* Check "ARGUMENT3" */
   if (ARGUMENT3&&*ARGUMENT3
      &&strtokcount(ARGUMENT3,qDelimiter)==2) {
      dTox/*[cm]*/=atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,0))*1e-7;freeEx(pTok);
      dMRatio=atof(pTok=strtokbyindex(ARGUMENT3,qDelimiter,1));freeEx(pTok);
   } else {
      dTox=1e-7;
      dMRatio=0.5;
      Echo(" Following parameters are defined arbitrarily: Tox[nm]=%.2f m*/m0=%.3f\n",
         dTox*1e7,dMRatio);
   }

   /* Echo */
   Echo(" Model=%s min.fit=%d r2=%g (tox[nm]=%.2f m*/m0=%.3f)\n",
      ARGUMENT,nFitTotal,dR2AtLeast,dTox*1e7,dMRatio);

   /* Compute */
   for (iXYT=1;iXYT<=nXYT;iXYT++) {
      int nLBoundary,nHBoundary,nGuess;
      double vGuess[8],vAnswer[8];
      //nXCol,nX2Col,nYCol <-- (Vg,Jg,Temp) or (Vg,Eox,Jg,Temp)
      Echo(" [%d] ",iXYT);
      k=EchoXYTArgumentsInParenthesis(
         (const char*)pXYT,qDelimiter,iXYT,&nXCol,&nX2Col,&nYCol,&dKelvin);
      if ((k==3&&(nXCol<NCL||nXCol>NCH||nYCol<NCL||nYCol>NCH)) ||
         (k==4&&(nXCol<NCL||nXCol>NCH||nX2Col<NCL||nX2Col>NCH||nYCol<NCL||nYCol>NCH))) {
         Echo(0,
            "%s\nX(%d)(%d) or Y(%d) index is out of range."
            "compared to matrix columns [%d..%d] by the command of <XYT=>.\n",
            MOUDLENAME,nXCol,nX2Col,nYCol,NCL,NCH);
         free(pXYT);
         return FALSE;
      }
      /* Allocate vXData,vYData,vXMirror,vYMirror,vXCopy,vYCopy */
      MGetSafeVectorPair(*MTX,TRUE,NRL,NRH,nXCol,nYCol,
         &vXData,&vYData,&nLBoundary,&nHBoundary);
      vXMirror=VDuplicate(vXData,nLBoundary,nHBoundary);
      vYMirror=VDuplicate(vYData,nLBoundary,nHBoundary);      
      vXCopy=VDuplicate(vXData,nLBoundary,nHBoundary);
      vYCopy=VDuplicate(vYData,nLBoundary,nHBoundary);
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
      /* Check Eox whether the change in sign is. [20031004] */
      nBoundary=2;
      aBoundary[0]=nLBoundary;
      aBoundary[1]=nHBoundary;
      for (j=nLBoundary;j<nHBoundary;j++) {
         if (SIGN(vXCopy[j])!=SIGN(vXCopy[j+1])) {
            nBoundary=3;
            aBoundary[1]=j+1;
            aBoundary[2]=nHBoundary;
            break;
         }
      }
      /* Fit by model */
      for (iModelIndex=0;iModelIndex<nModelTotal;iModelIndex++) { /* 20030820 */
         int nLFit,nHFit;
         void (*pFunc)();
         /* Set Model ID */
         pTok=strtokbyindex(pArgument,qDelimiter,iModelIndex);
         nModelIndex=GetModelIndex(pTok);
         freeEx(pTok);
         /* Handle Boundary issue */
         iBoundary=0;
B:       nLFit=aBoundary[iBoundary++];
         nHFit=aBoundary[iBoundary];
         if (nBoundary==3&&iBoundary==1) nHFit--;
         /* Vector Copy */
         VCopy(vXMirror,vXData,nLFit,nHFit);
         VCopy(vYMirror,vYData,nLFit,nHFit);
         VCopy(vXMirror,vXCopy,nLFit,nHFit);
         VCopy(vYMirror,vYCopy,nLFit,nHFit);
         //vXData,vYData,nHFit
         ComplyFittingVectorsWithModel(nModelIndex,vXData,vYData,nLFit,nHFit,dTox);
         //nGuess
         switch (nModelIndex) {
         case MODEL_OHM:      pFunc=_OHM;      nGuess=1;break;
         case MODEL_OHM2:     pFunc=_OHM;      nGuess=2;break;
         case MODEL_SCLCEXPONENTIAL:pFunc=_SCLCEXPONENTIAL;nGuess=2;break;
         case MODEL_SCLCUNIFORM:pFunc=_SCLCUNIFORM;nGuess=2;break;
         case MODEL_SCLCSQUARE:pFunc=_SCLCSHALLOW;nGuess=1;break;
         case MODEL_LAMPERT:  pFunc=_LAMPERT;  nGuess=2;break;
         case MODEL_SCLCCUBE:     pFunc=_SCLCCUBE;     nGuess=1;break;
         case MODEL_DT:       pFunc=_DT;       nGuess=2;break;
         case MODEL_DT_LEE2:  pFunc=_DTLEE2;      nGuess=3;break;
         case MODEL_FN:       pFunc=_FN;       nGuess=2;break;
         case MODEL_POOLE:    pFunc=_POOLE;    nGuess=2;break;
         case MODEL_SCHOTTKY: pFunc=_SCHOTTKY; nGuess=2;break;
         case MODEL_PF:       pFunc=_PF;       nGuess=2;break;
         case MODEL_STAT:     pFunc=_STAT;     nGuess=3;break;
         case MODEL_DTAT:     pFunc=_DTAT;     nGuess=2;break;
         }
R:       /* Fit first and expand. 20040110 */ {
         VECTOR vAns;
         VChangeBase2(&vXData,&vYData,nLFit,1);
         for (k=1;k<=nGuess;k++) vGuess[k]=1; /* 20040614 */
         dR2=xxmrqmin(vXData,vYData,nHFit-nLFit+1,vGuess,nGuess,pFunc,
            nFitTotal,dR2AtLeast,
            &vAns,&nRLAnswer,&nRHAnswer);
         nRLAnswer+=(nLFit-1);
         nRHAnswer+=(nLFit-1);
         VChangeBase2(&vXData,&vYData,1,nLFit);
         for (k=1;k<=nGuess;k++) vAnswer[k]=vAns[k];
         VDestroy(vAns,1,nGuess);
         if (dR2<dR2AtLeast) { /* 20031006 */
            if ((iBoundary+1)<nBoundary) goto B;
            /* else */ continue;
         }
         }
         /* I gave up applying this module. 2004.2.11 TT
         * Check the calculated current divergence with respect to data.
            If then, worthless. However, be careful this method is not complete.
            Still have an hole.
            Check calculate current with extracted coeffs compared to the
            orginal data, always.
            20031003-4 * {
            int nCount=0;
            double dBase=12.,dYdata,dYcalc,dY,J,Eox,a,b;
            a=vAnswer[1];
            b=vAnswer[2];
            dYdata=dYcalc=0.;
            for (j=nLFit;j<=nHFit;j++) {
               Eox=(vXCopy[j]);
               dY=log(fabs(vYCopy[j]))+dBase;
               switch (nModelIndex) {
               case MODEL_OHM :      J=nGuess==1 ? a*Eox:a+b*Eox;break;
               case MODEL_SCLCEXPONENTIAL :J=a*pow(Eox,b+1.);break;
               case MODEL_SCLCUNIFORM :J=a*Eox*exp(b*Eox);break;
               case MODEL_SCLCSQUARE :J=a*pow(Eox,2.);break;
               case MODEL_LAMPERT :  J=a*Eox+b*pow(Eox,2.);break;
               case MODEL_SCLCCUBE :     J=a*pow(Eox,3.);break;
               case MODEL_DT :       J=a*sinh(3.13e7*b*fabs(Eox));break;
               case MODEL_FN :       J=a*pow(Eox,2.)*exp(-b/Eox);break;
               case MODEL_POOLE :    J=a*exp(b*Eox);break;
               case MODEL_SCHOTTKY : J=a*exp(b*sqrt(Eox));break;
               case MODEL_PF :       J=a*Eox*exp(b*sqrt(Eox));break;
               }
               J=SIGN(J)>0 ? log(fabs(J))+dBase:log(fabs(J))-dBase;
               if (J>dY) {
                  dYdata+=dY;
                  dYcalc+=J;
                  nCount++;
               }
            }
            if (nCount) {
               dYdata/=nCount;
               dYcalc/=nCount;
               if ((dYcalc-dYdata)>=0.5) dR2=0.; // 0.5 order
            }
         }
         */
         /* Print out */ if (dR2>=dR2AtLeast) {
            const char *qName=qGetModelName(nModelIndex);
            char cEoxSign=SIGN(vXCopy[nLFit])>0 ? '+':'-';
            switch (nModelIndex) {
            case MODEL_OHM :
               Echo(" %s %c a=%.2e",qName,cEoxSign,vAnswer[1]);
               break;
            case MODEL_OHM2 :
               Echo(" %s %c a=%.2e yi=%.2e",qName,cEoxSign,vAnswer[2],vAnswer[1]);
               break;
            case MODEL_SCLCEXPONENTIAL:
               vAnswer[1]=exp(vAnswer[1]);
               vAnswer[2]-=1;
               Echo(" %s %c a=%.2e b=%.2e",qName,cEoxSign,vAnswer[1],vAnswer[2]);
               break;
            case MODEL_SCLCUNIFORM:
               vAnswer[1]=exp(vAnswer[1]);
               Echo(" %s %c a=%.2e b=%.2e",qName,cEoxSign,vAnswer[1],vAnswer[2]);
               break;
            case MODEL_SCLCSQUARE:
            case MODEL_SCLCCUBE:
               vAnswer[1]=exp(vAnswer[1]);
               Echo(" %s %c a=%.2e",qName,cEoxSign,vAnswer[1]);
               break;
            case MODEL_LAMPERT:
               vAnswer[1]=exp(vAnswer[1]);
               Echo(" %s %c a=%.2e b=%.2e",qName,cEoxSign,vAnswer[1],vAnswer[2]);
               break;
            case MODEL_DT:
               vAnswer[1]=exp(vAnswer[1]);
               Echo(" %s %c a=%.2e b=%.2e",qName,cEoxSign,vAnswer[1],vAnswer[2]*3.125e7*dTox*dTox);
               break;
            case MODEL_DT_LEE2:
            case MODEL_FN:
            case MODEL_POOLE:
            case MODEL_SCHOTTKY:
            case MODEL_PF:
               vAnswer[1]=exp(vAnswer[1]);
               Echo(" %s %c a=%.2e b=%.2e",qName,cEoxSign,vAnswer[1],vAnswer[2]);
               break;
            case MODEL_STAT:
               vAnswer[1]=exp(vAnswer[1]);
               Echo(" %s %c a=%.2e b(>0)=%.2e c(>0)=%.2e",qName,cEoxSign,vAnswer[1],vAnswer[2],vAnswer[3]);
               break;
            case MODEL_DTAT:
               vAnswer[1]=exp(vAnswer[1]);
               Echo(" %s %c a=%.2e b=%.2e",qName,cEoxSign,vAnswer[1],vAnswer[2]);
               break;
            }
            pL=dtostr(vXCopy[nRLAnswer]<vXCopy[nRHAnswer]?vXCopy[nRLAnswer]:vXCopy[nRHAnswer],"%.1z");
            pH=dtostr(vXCopy[nRLAnswer]>vXCopy[nRHAnswer]?vXCopy[nRLAnswer]:vXCopy[nRHAnswer],"%.1z");
            Echo(" r2=%.3f from %d pts (%s..%s)\n",dR2,nRHAnswer-nRLAnswer+1,pL,pH);
            freeEx(pL);
            freeEx(pH);
            /* Check validity */
            if (nModelIndex==MODEL_SCLCEXPONENTIAL) {
               Echo("   Tc[K]=%.1f \n",vAnswer[2]*dKelvin);
            } else if (nModelIndex==MODEL_DT) {
               /* vAnswer[2] <= a[2]=sqrt(MassRatio/BarrierHeight) */
               double dBarrier=dMRatio/SQUARE(vAnswer[2]);
               Echo("   tox[nm]=%.2f(arg) m*/m0=%.2f(arg) barrier[eV]=%.3g Eox(ohm)[MV/cm]=%.2g \n",
                  dTox*1e7,dMRatio,dBarrier,1e-6/(3.125e7*dTox*dTox*vAnswer[2]));
            } else if (nModelIndex==MODEL_DT_LEE2) {
               double dBarrier=vAnswer[3]*dTox;
               Echo("   tox[nm]=%.2f(arg) BH[eV]=%.3g \n",dTox*1e7,dBarrier);
            } else if (nModelIndex==MODEL_FN) { /* J=a[1]*Eox^2*exp(-a[2]/Eox) */
               double dK,dRatio,dBarrier;
               dK=vAnswer[1]*pow(vAnswer[2],2./3);
               dRatio=4./9*pow(8*PI*KPlanck*dK/SQUARE(Qelectron),3.)/SQUARE(10.25e7);
               dBarrier=!_isnan(dRatio) ? pow(fabs(vAnswer[2])/(2./3*10.25e7*sqrt(dRatio)),2./3):0.;
               if (!_isnan(dRatio)&&1e-3<dRatio&&dRatio<10)
                  Echo("   m*/m0=%.2f barrier[eV]=%.2f\n",dRatio,dBarrier);
               //else
                  Echo("   m*/m0=%.2f(arg) BH[eV]=%.2f\n",
                  dMRatio,pow(fabs(vAnswer[2])/(2./3*10.25e7*sqrt(dMRatio)),2./3));
            } else if (nModelIndex==MODEL_POOLE) {
               double dTrapCenterDistance;
               dTrapCenterDistance=vAnswer[2]/0.5*GetThermalVoltage(dKelvin)/cmoverA;
               Echo("   d[A]=%.2g Nt[/cm^3]~%.2g\n",dTrapCenterDistance,1/pow(dTrapCenterDistance*cmoverA,3));
            } else if (nModelIndex==MODEL_PF) {
               double dBeta,dRDC;
               dBeta=vAnswer[2]*GetThermalVoltage(dKelvin);
               dRDC=Qelectron/(PI*VacPermittivity*pow(dBeta,2));
               Echo("   betaPF[(Vcm)^0.5]=%.2e RDC[]=%.1f\n",dBeta,dRDC);
            } else if (nModelIndex==MODEL_SCHOTTKY) {
               double dBeta,dRDC;
               dBeta=vAnswer[2]*GetThermalVoltage(dKelvin);
               dRDC=Qelectron/(4*PI*VacPermittivity*pow(dBeta,2));
               Echo("   betaS[(Vcm)^0.5]=%.2e RDC[]=%.1f RDC/4[]=%.1f \n",dBeta,dRDC,dRDC/4);
               /* Modified PF Equation : RDC/4
                  1) M.Stuart,"Electrode-Limited to Bulk-Limited Conduction in Silicon Oxide Films,"
                  Phys.Stat.Sol.23,595(1967).
                  2) J.G.Simmons,Phys.Rev,155,657(1967).
               */
            } else if (nModelIndex==MODEL_STAT) {
               if (vAnswer[3]>0) {
                  double dBarrier;
                  dBarrier=vAnswer[3]/(4*sqrt(2*dMRatio*MFreeElectron)/(3*KReducedPlanck*Qelectron));
                  dBarrier=pow(dBarrier,2./3)/Qelectron;
                  Echo("   barrier[eV]=%.3f (%.3f)\n",vAnswer[2]*dTox,dBarrier);
               } else {
                  Echo("   barrier[eV]=%.3f\n",vAnswer[2]*dTox);
               }
            } else if (nModelIndex==MODEL_DTAT) {
               double dA=4*sqrt(2*Qelectron*dMRatio*MFreeElectron)/(3*KReducedPlanck);
               double dBarrier=pow(vAnswer[2]/dA,2./3);
               Echo("   barrier[eV]=%.3f\n",dBarrier);
            }
         }
         /* Adjust fitted range to look up overlap region. 20031006 */ {
         /*
            int nLFitNew=nRHAnswer-(nFitTotal>>1)+2;
            int nHFitNew=nLFitNew+nFitTotal-1;
            if (nRLAnswer<nLFitNew&&nHFitNew<=nHFit) {
               nLFit=nLFitNew;
               nHFit=nHFitNew;
               goto R;
            }
            */
            /* Make it more simple and effective. 20040110 */
            j=nRHAnswer+(nFitTotal>>1)-nFitTotal;
            if (nRLAnswer<j&&(nRLAnswer+nFitTotal)<=aBoundary[iBoundary]) {
               nLFit=j;
               goto R;
            }
         }
         /* 20031005 */
         if ((iBoundary+1)<nBoundary)
            goto B;
      }
      /* Deallocate vXData,vYData,vXCopy */
N:    VDestroy(vXData,nVLow,nVHigh);
      VDestroy(vYData,nVLow,nVHigh);
      VDestroy(vXMirror,nVLow,nVHigh);
      VDestroy(vYMirror,nVLow,nVHigh);
      VDestroy(vXCopy,nVLow,nVHigh);
      VDestroy(vYCopy,nVLow,nVHigh);
   }

   freeEx(pArgument);
   return TRUE;
}

/******************************************************************************/
/* MosDiodeRegressor.c */
