/******************************************************************************/
/*                           file name : usrfunc.c                            */
/*                         description : OPEN user function library           */
/*                            compiler : unix-cc (SUN UNIX 4.0.3)             */
/*                                     + MS Visual C++ 4.0/6.0                */
/*                             creator : Kim,YongShik                         */
/*                       creating date : 43240412                             */
/* 4324 0412-0703,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4326 0321,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4327 1002,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4328 0124,0424,0505,0622,0708,1017,1031-1102,____,____,____,____,____,____ */
/* 4329 0411,0412,0612,0822,____,____,____,____,____,____,____,____,____,____ */
/* 4330 0717,0806-0811,0920,____,____,____,____,____,____,____,____,____,____ */
/* 4330 0317,____,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4333 0413-0528,0605,0611-0614,0825,0913,1107,____,____,____,____,____,____ */
/* 4334 0418-0419,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4335 1014-????,____,____,____,____,____,____,____,____,____,____,____,____ */
/* 4336 0210-0318,0427,0517,0522,0622,0805,0818,0901-0908,____,____,____,____ */
/* 4337 0216,0315,0612,____,____,____,____,____,____,____,____,____,____,____ */
/******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include "myCore.h"
#include "blob.h"
#include "any.h"
#include "str.h"
#include "tools.h"
#include "nrecipe.h"
#include "number.h"
#include "parser.h"
#include "geplot.h"
#include "gecore.h"
#include "usrfunc.h"

#define GE_BUFSIZE 1024 /* in gecore.h */

/******************************************************************************/

#define ABS(x) ((x)<0 ? (-(x)):(x))
#define RADIAN(degree) ((degree)*PI/180)
#define DEGREE(radian) ((radian)*180/PI)
#if !defined(SIGN)
#define SIGN(x)   ((x)>=0 ? 1:-1)
#endif

extern int Echo();
       IPTRFN ufunlookup();
static int BadCommand();
static int CheckArguments();
static int CheckMatrixBoundary();

static int Demo();
static int MatrixPrint();
static int MatrixHandler();
static int MathParser();
static int MathParserEx();
static int ColumnNormalizer();
static int ColumnGroupNormalizer();
static int ColumnNoiseCleaner();
static int ColumnTangentSloper();

       int PlotPolynomial();
static int PolynomialFit95();
static int PolyCoeffsDrawing();
static int GetCoefficientString();

extern int DataPointReformer();
extern int PolynomialFit();
extern int IdealMosCapacitor();
extern int IdealMosCapacitorEx();
extern int TwoFreqCapacitanceModel();
extern int MaserjianModel();
extern int MosCapacitorRegressor();
extern int MosDiodeRegressor();
extern int NormConductance();
extern int JunctionDiodeRegressor();
extern int SplitCV();
extern int MOSFETIdVg();

static int GetInterpolatedValue();
static int NORMSDIST(); /* ?? */
extern int ShiftAndRatioMethod();
static int FstDiffMaxFit(); /* ? */
extern int EEPROM();
extern int TrapInThinOxide();
extern int BandToBandTunneling();

/*- Useful Function ----------------------------------------------------------*/

int GetFittingRange(
   VECTOR vX,int nRL,int nRH,int nFitTotal,double dL,double dH,
   int *nL,int *nH
   );

/*----------------------------------------------------------------------------*/

#define SCALE_LIN    0 /* plot.h */
#define SCALE_LOG10  1 /* plot.h */
#define SCALE_SERIES 2 /* plot.h */
#define SCALE_NORM   3 /* plot.h */

static 
struct UFUNTABLE {
   char  *qFunction;
   IPTRFN pFunction;
} qUserFuncTable[]={
   {"Demo",                Demo},

   {"PolynomialFit95",     PolynomialFit95},
   {"PolyCoeffsDrawing",   PolyCoeffsDrawing},

   {"DataPointReformer",   DataPointReformer}, /* 20030716 */
   {"MatrixPrint",         MatrixPrint},
   {"MatrixHandler",       MatrixHandler},  /* 20040612 */
   {"MathParser",          MathParser},
   {"MathParserEx",        MathParserEx}, /* 20040612 */
   {"ColumnNormalizer",    ColumnNormalizer}, /* 20030212 */
   {"ColumnGroupNormalizer",ColumnGroupNormalizer}, /* 20030212 */
   {"ColumnNoiseCleaner",  ColumnNoiseCleaner},/* 20030224 */
   {"ColumnTangentSloper", ColumnTangentSloper},/* 20030318 */
   {"PolynomialFit",       PolynomialFit},/* 20030622 */
   {"IdealMosCapacitor",   IdealMosCapacitor},
   {"IdealMosCapacitorEx", IdealMosCapacitorEx}, /* 20030430 */
   {"TwoFreqCapacitanceModel",TwoFreqCapacitanceModel},
   {"NormConductance",     NormConductance}, /* 20040315 */
   {"MaserjianModel",      MaserjianModel},  /* 20030517 */
   {"MosCapacitorRegressor",MosCapacitorRegressor},
   {"MosDiodeRegressor",   MosDiodeRegressor}, /* 20030522 */
   {"JunctionDiodeRegressor",JunctionDiodeRegressor}, /* 20040227 */
   {"SplitCV",             SplitCV}, /* 20030904 */
   {"MOSFETIdVg",          MOSFETIdVg}, /* 20030908 */

   {"GetInterpolatedValue",GetInterpolatedValue},/* 20030318 */
   {"NORMSDIST",           NORMSDIST}, /* like in Excel */
   {"ShiftAndRatioMethod", ShiftAndRatioMethod},

   {"FstDiffMaxFit",       FstDiffMaxFit},
   {"EEPROM",              EEPROM},
   {"TrapInThinOxide",     TrapInThinOxide},
   {"BTBT",                BandToBandTunneling}
};

/******************************************************************************/

IPTRFN UfunLookUp( nFunction,qFunctionName ) 
   int nFunction;
   const char *qFunctionName;
{
   int nIndex;
   int nCount=noof(qUserFuncTable);

   for (nIndex=0;nIndex<nCount;nIndex++) {
      if (strequ(qUserFuncTable[nIndex].qFunction,qFunctionName)) {
         Echo("*Seq.=%d,Function=\"%s\"\n",nFunction,qFunctionName);
         return qUserFuncTable[nIndex].pFunction;
      }
   }
   Echo(0,"Error in usufunc.c, Invalid user-function selection :\n%s",
      qFunctionName);
   return (IPTRFN)BadCommand;
}

static
int BadCommand()
{
   return FALSE;
}

static
int CheckArguments( mtx,mrl,mrh,mcl,mch,nrl,nrh,ncl,nch,x,y,z )
   double ***mtx;
   int *mrl,*mrh,*mcl,*mch;
   int *nrl,*nrh,*ncl,*nch;
   int x,y,z;
{
   *nrl=MIN(*nrl,*nrh);
   *nrh=MAX(*nrl,*nrh);
   *ncl=MIN(*ncl,*nch);
   *nch=MAX(*ncl,*nch);

   if (*mrl==*mrh && *mcl==*mch) {
      *mrl=*nrl; *mrh=*nrh;
      *mcl=*ncl; *mch=*nch;
      *mtx=dmatrix(*mrl,*mrh,*mcl,*mch);
   } else {
      if (*nrl==*nrh &&  *ncl==*nch && *nrl==*ncl) {
         *nrl=*mrl; *nrh=*mrh;
         *ncl=*mcl; *nch=*mch;
      } else {
         if (*nrl<*mrl || *mrh<*nrl) *nrl=*mrl;
         if (*nrh<*mrl || *mrh<*nrh) *nrh=*mrh;
         if (*ncl<*mcl || *mch<*ncl) *ncl=*mcl;
         if (*nch<*mcl || *mch<*nch) *nch=*mch;
      }
   }

   //20030805 Echo(". [%d..%d][%d..%d],(x=%d,y=%d,z=%d)\n",*nrl,*nrh,*ncl,*nch,x,y,z);
  
   if (*mrl==*mrh && *mcl==*mch &&
       *nrl==*nrh && *ncl==*nch) {
      Echo(0,"Error in CheckArguments(),  "
         "mrl(%d)==mrh(%d),mcl(%d)==mch(%d),nrl(%d)==nrh(%d),ncl(%d)==nch(%d).",
         *mrl,*mrh,*nrl,*nrh,*ncl,*nch);
      return FALSE;
   }
   if (x<*ncl || x>*nch || y<*ncl || y>*nch) {
      Echo(0,"Error in CheckArguments(),  "
         "x=%d or y=%d is a wrong number wrt. ncl=%d and nch=%d.",
         x,y,*ncl,*nch);
      return FALSE;
   }
   return TRUE;
}

static
int CheckMatrixBoundary( mtx,mrl,mrh,mcl,mch,nrl,nrh,ncl,nch )
   double ***mtx;
   int *mrl,*mrh,*mcl,*mch;
   int *nrl,*nrh,*ncl,*nch;
{
   *nrl=MIN(*nrl,*nrh);
   *nrh=MAX(*nrl,*nrh);
   *ncl=MIN(*ncl,*nch);
   *nch=MAX(*ncl,*nch);

   if (*mrl==*mrh &&  *mcl==*mch) {
      *mrl=*nrl; *mrh=*nrh;
      *mcl=*ncl; *mch=*nch;
      *mtx=dmatrix(*mrl,*mrh,*mcl,*mch);
   } else {
      if (*nrl==*nrh &&  *ncl==*nch  &&  *nrl==*ncl) {
         *nrl=*mrl; *nrh=*mrh;
         *ncl=*mcl; *nch=*mch;
      } else {
         if (*nrl<*mrl || *mrh<*nrl) *nrl=*mrl;
         if (*nrh<*mrl || *mrh<*nrh) *nrh=*mrh;
         if (*ncl<*mcl || *mch<*ncl) *ncl=*mcl;
         if (*nch<*mcl || *mch<*nch) *nch=*mch;
      }
   }
   Echo(" [%d..%d][%d..%d]\n",*nrl,*nrh,*ncl,*nch);
   if (*mrl==*mrh && *mcl==*mch
      &&  *nrl==*nrh && *ncl==*nch) {
      Echo(0,"Error CheckMatrixBoundary(),  "
         "mrl(%d)==mrh(%d),mcl(%d)==mch(%d),nrl(%d)==nrh(%d),ncl(%d)==nch(%d).",
         *mrl,*mrh,*nrl,*nrh,*ncl,*nch);
      return FALSE;
   }
   return TRUE;
}

/*----------------------------------------------------------------------------*/

uFuncTableTag uDemoTag={
"Demo",
"type=Demo nrl=1 nrh=60 ncl=1 nch=2 drl=0 drh=360\r\n"
"! FOUR_LEAVED ROSE\r\n"
"! drl,drh: start and stop angle",
""
};

static
int Demo( ARGUMENTS ) /* FOUR_LEAVED ROSE */
   ARGULIST
{
/*
   register int i,j;
   int scale=XSCALE;
   double **mtrx,drl,drs;
   double r,t;

   Echo("*** in : NRL,NRH,NCL,NCH,(*XNO)[0],(*YNO)[0],"
        "DRL,DRH\n");
   Echo("*** out: ...\n");
  
   CheckArguments(MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH,
                  (*XNO)[0],(*YNO)[0],*ZNO?(*ZNO)[0]:0);
   mtrx=*MTX;

   drl=DRL;
   drs=(DRH-DRL)/(NRH-NRL);

   for (i=NRL;i<=NRH;i++)
      switch (scale) {
         case SCALE_LIN   : mtrx[i][NCL]=drl+(i-NRL)*drs; break;
         case SCALE_LOG10 : mtrx[i][NCL]=pow10(drl+(i-NRL)*drs);
      }
   for (i=NRL;i<=NRH;i++) {
      for (j=NCL+1;j<=NCH;j++) {
         t=mtrx[i][NCL];
         r=10*cos(2*RADIAN(t));
         mtrx[i][NCL]=r*cos(RADIAN(t));
         mtrx[i][j]=r*sin(RADIAN(t));
      }
   }
   */
   return TRUE;
}

/*----------------------------------------------------------------------------*/

static
int GetCoefficientString( coeff,degree,out )
   double *coeff;
   int degree;
   char **out;
{
   double a,b;
   char qBuffer[1024];
   int i,k=4;

   if (degree==1) {
      a=coeff[0];
      b=coeff[1];
      sprintf(qBuffer,"# xi=%1.2e yi=%1.2e slope=%1.2e 1/s=%1.2e",
              -a/b,a,b,1/b);
   } else {
      sprintf(qBuffer,"* c%d=%+1.4e ",i=0,coeff[0]);
      for (i++;i<=degree;i++) {
         if (!(i%k))
            sprintf(qBuffer+strlen(qBuffer),"\n* ");
         sprintf(qBuffer+strlen(qBuffer),"c%d=%+1.4e ",i,coeff[i]);
      }
   }
   *out=strdpl(qBuffer);
   return TRUE;
}

static
int PolynomialFit95( mtrx,mrl,mrh,mcl,mch,
                   xTotal,xNo,yTotal,yNo,zTotal,zNo,
                   nrl,nrh,ncl,nch,
                   degree,set,xScale,yScale,zscale,
                   argument,xyz,sweep,
                   outtot,outvec,outtext ) 
   double ***mtrx;
   int *mrl,*mrh,*mcl,*mch,
       *xTotal,**xNo,*yTotal,**yNo,*zTotal,**zNo;
   int degree,set,nrl,nrh,ncl,nch,xScale,yScale,zscale;
   char *argument,*xyz,*sweep;
   int *outtot; /*return*/
   double **outvec; /*return*/
   char **outtext; /*return*/
{ 
   double **mData,*vX,*vY;
   double *sig,**u,**v,*w,chisq;
   int bResult,n,i;
   extern void fpoly(),ifpoly();
   void (*func)();
 
   if (*yTotal<=set) {
      Echo(".Warning @PolynomialFit95(),  yTotal(%d)<=set(%d). Job ignored. \n",
         *yTotal,set);
      return TRUE;
   }
   bResult=CheckArguments(mtrx,mrl,mrh,mcl,mch,&nrl,&nrh,&ncl,&nch,
      (*xNo)[set],(*yNo)[set],*zNo?*zNo:0);
   if (!bResult) return FALSE;
   mData=*mtrx;

   MGetSafeVector(mData,TRUE,(*xNo)[set],nrl,nrh,&vX,&i,&n);
   MGetSafeVector(mData,TRUE,(*yNo)[set],nrl,nrh,&vY,&i,&n);
   switch (xScale) {
   case SCALE_LOG10 : for (i=1;i<=n;i++) vX[i]=log10(vX[i]);break;
   case SCALE_NORM : for (i=1;i<=n;i++) vX[i]=icnorm(vX[i]);break;
   }
   switch (yScale) {
   case SCALE_LOG10 : for (i=1;i<=n;i++) vY[i]=log10(vY[i]);break;
   case SCALE_NORM : for (i=1;i<=n;i++) vY[i]=icnorm(vY[i]);break;
   }

   Echo(".(x=%d)=[%d..%d],(y=%d)=[%d..%d]\n",(*xNo)[set],1,n,(*yNo)[set],1,n);
   if (ABS(degree)>=n) {
      Echo(
         GE_MB_WARNING,
         "Polynomial.Degree (%d) >= Data Total (%d)\n in PolynomialFit95()",
         degree,n);
      free_dvector(vX,1,n);
      free_dvector(vY,1,n);
      return FALSE;
   }
   if (degree>0) {
      func=fpoly;
   } else if (degree==0) {
      func=fpoly;
      degree=1;
   } else if (degree<0) {
      for (i=1;i<=n;i++)
         if (vX[i]==0)
            errExit("data==0 for polyn.degree < 0 in PolynomialFit95()");
      func=ifpoly;
   }
   Echo("* scale : x=%-5s y=%-5s z=%-5s\n",
      xScale==SCALE_LIN ? "lin" : xScale==SCALE_LOG10 ? "log10" : "norm",
      yScale==SCALE_LIN ? "lin" : yScale==SCALE_LOG10 ? "log10" : "norm",
      zscale==SCALE_LIN ? "lin" : zscale==SCALE_LOG10 ? "log10" : "norm");
   Echo("# General Linear Least Squares : polynomial degree = %d\n",degree);
   sort2(n,vX,vY);
   *outtot=ABS(degree)+1;
   *outvec=salloc(double,*outtot);
   sig=dvector(1,n);
   for (i=1;i<=n;i++) sig[i]=(double)1.0; /* ????? */
   u=dmatrix(1,n,1,*outtot);
   v=dmatrix(1,*outtot,1,*outtot);
   w=dvector(1,*outtot);
   /* Press,Numerical Receipes in C,p.537 */
   svdfit(vX,vY,sig,n,*outvec-1,*outtot,u,v,w,&chisq,func);
   GetCoefficientString(*outvec,*outtot-1,outtext);
   Echo(*outtext);
   Echo("\n# x2=%1.4e\n",chisq);
   free_dvector(sig,1,n);
   free_dmatrix(u,1,n,1,*outtot);
   free_dmatrix(v,1,*outtot,1,*outtot);
   free_dvector(w,1,*outtot);
   free_dvector(vX,1,n);
   free_dvector(vY,1,n);
   return TRUE;
}

uFuncTableTag uPolyCoeffsDrawingTag={
"PolyCoeffsDrawing",
"type=PolyCoeffsDrawing\r\n"
"option=3 argument=\"1,2,3,4\"\r\n"
"rline.color=blue rline.width=4 rline.dash_list=(4,4)\r\n"
"! option: polynomial equation degree, if 3, y=a+bx+cx^2+dx^3\r\n"
"! argument: coefficients separated by comma",
""
};

static
int PolyCoeffsDrawing( ARGUMENTS )
   ARGULIST
/* input  : NOPTION,ARGUMENT
 * output : OUTTOT,OUTVEC,OUTTEXT
 */
{
   DLL *dll;
   DLN *dln;
   char qBuffer[1024];
   int i;

   Echo("* degree=%d\n* coeffs=%s\n",NOPTION,ARGUMENT);
   if (!ARGUMENT)
      errExit("!program in PolyCoeffsDrawing()");
   if (noof(qBuffer)<=(i=strlen(ARGUMENT)))
      errExit("noof(qBuffer)<=strlen(ARGUMENT) in PolyCoeffsDrawing()");
   memcpy(qBuffer,ARGUMENT,strlen(ARGUMENT)+1);
   DLLOpen(&dll);
   DLLAddTokens(dll,qBuffer,",");
   if (dll->total!=ABS(NOPTION)+1)
      errExit("# of coeffs. != ABS(NOPTION)+1 in PolyCoeffsDrawing()");
   *OUTTOT=dll->total;
   *OUTVEC=salloc(double,*OUTTOT);
   for (i=0,dln=dll->head;
        i<*OUTTOT;
        i++,dln=dln->next)
      (*OUTVEC)[i]=(double)atof(dln->tok);
   GetCoefficientString(*OUTVEC,*OUTTOT-1,OUTTEXT);
   DLLClose(dll);
   return TRUE;
}

int PlotPolynomial( xlb,xub,ylb,yub,degree,coeff_tot,coeff,point_tot,point )
   double xlb,xub,ylb,yub; /* in linear scale */
   int degree,coeff_tot;
   double *coeff;
   int *point_tot; /* return */
   BLOBPOINT **point; /* return */
{
   double a,b,c;
   register int i,j;

   (*point_tot)=GE_BUFSIZE;
   (*point)=salloc(BLOBPOINT,(*point_tot));
   a=xlb;
   if (degree<0 && a==0.0) a=(xub)*1e-18;
   b=(xub-xlb)/((*point_tot)-1);
   for (i=0;i<*point_tot;i++) {
      (*point)[i].x=a;
      if (degree>0)
         for (j=1,c=coeff[0];j<coeff_tot;j++) {
            c+=coeff[j]*a;
            a*=(*point)[i].x; 
         }
      else
         for (j=1,c=coeff[0];j<coeff_tot;j++) {
            c+=coeff[j]/a;
            a/=(*point)[i].x; 
         }
      (*point)[i].y=c;
      a=b+(*point)[i].x;
   }
   return TRUE;
}

/*----------------------------------------------------------------------------*/

/*
static
char *GetOptimizedNumericFormat(
   const MATRIX M,int nIndex,int nL,int nH,int nMaxDigit
)
{
   char qBuffer[256],*pDot,*pExp;
   int nRow,nSubDigit,nReturn;
   int bNegative,bFractional,nOrder;
   
   bNegative=0;
   nSubDigit=0;
   bFractional=0;
   nOrder=0;

   for (nRow=nL;nRow<=nH;nRow++) {
      if (IsNaNDouble(M[nRow][nIndex])) continue;
      sprintf(qBuffer,"%.E",M[nRow][nIndex]);
      pDot=strchr(qBuffer,'.');
      pExp=strchr(qBuffer,'E');
      if (!bNegative && qBuffer[0]=='-') {
         bNegative=1;
      }
      if (nSubDigit<nMaxDigit) {         
         nReturn=(int)(pExp-pDot);
         nSubDigit=MAX(nSubDigit,nReturn);
         if (nSubDigit>nMaxDigit) nSubDigit=nMaxDigit;
      }
      if (!bFractional && pExp[1]=='-') {
         bFractional=1;
      }
      nOrder=MAX(ABS(atoi(pExp+1)),nOrder);
   }

   sprintf(qBuffer,"%d",nSubDigit);

   a=strvcat("%%",bNegative?"+":"",".",qBuffer,"e",
   sprintf(qBuffer,"%%+.%de",nSubDigit);
   return strdpl(qBuffer);
}
*/

static
int CheckXyzColOption( nColIndex,qOption,vXNo,nXNo,vYNo,nYNo,vZNo,nZNo )
   int nColIndex,nXNo,nYNo,nZNo;
   int *vXNo,*vYNo,*vZNo;
   const char *qOption;
{
   const char *qDelimiter=",",*qDoubleDelimiter=",,";
   char *pOption;
   int nResult,nIndex;

   pOption=strdpl(qOption ? (char*)qOption:"a");

   if (isdigit(pOption[0])) {
      char *pTok;
      int nCount;
      strtrim(pOption);
      while (strreplace(&pOption,qDoubleDelimiter,qDelimiter));
      nCount=chrcount(pOption,qDelimiter[0])+1;
      pTok=NULL;
      for (nIndex=0;nIndex<nCount;nIndex++) {
         pTok=strtokbyindex(pOption,qDelimiter,nIndex);
         if (nColIndex==atoi(pTok)) break;
         freeEx(pTok);/* <- pTok=NULL; */
      }
      nResult=pTok ? TRUE:FALSE;
      freeEx(pTok);
   } else {
      switch (toupper(*pOption)) {
      case 'A' : nResult=TRUE;break;
      case 'X' : nResult=IsInIntVector(nColIndex,vXNo,0,nXNo-1);break;
      case 'Y' : nResult=IsInIntVector(nColIndex,vYNo,0,nYNo-1);break;
      case 'Z' : nResult=IsInIntVector(nColIndex,vZNo,0,nZNo-1);break;
      case 'B' : nResult=IsInIntVector(nColIndex,vYNo,0,nYNo-1)|| /* 20030303 */
                         IsInIntVector(nColIndex,vZNo,0,nZNo-1);break;
      }
   }

   freeEx(pOption);
   return nResult;
}

/*----------------------------------------------------------------------------*/

uFuncTableTag uMatrixPrintTag={
"MatrixPrint",
"type=MatrixPrint                                                            \n"
"argument=\"savedbygr\" option=3 xyz=a                                        ",
"[Y.Kim] \n"
"Created a long time ago.                                                    \n"
"Modified at 2003.6.1-2.                                                     \n"
"\n"
"[Input] \n"
"argument=[<filename>] option=[<d>] xyz=[a|x|y|z|b|<d>,<d>,...,<d>]          \n"
"! argument: output file path to save matrix                                 \n"
"! option: number of precision for printing, always positive or zero.        \n"
"!    If you want like 1.234e5, option should be 4.                          \n"
"! xyz: you can set character or column number directly as a paramter.       \n"
"!    Default is \"xyz=a\".                                                   "
};

static
int MatrixPrint( ARGUMENTS )
   ARGULIST
{
   char qFormat[64],qFormatNaN[64];
   FILE *pFile;
   int j,k,nCount;
   
   if (NRL<*MRL || *MRH<NRL) NRL=*MRL;
   if (NRH<*MRL || *MRH<NRH) NRH=*MRH;
   if (NCL<*MCL || *MCH<NCL) NCL=*MCL;
   if (NCH<*MCL || *MCH<NCH) NCH=*MCH;

   if (!ARGUMENT) {
      Echo(0,"Error! Output file name is undefined. \n");
      return FALSE;
   }
   if (NOPTION<=0) NOPTION=3;

   /* MWriteToFile(ARGUMENT,qFormat,*MTX,NRL,NRH,NCL,NCH); */

   if (!(pFile=fopen(ARGUMENT,"w"))) {
      Echo(" Error,<%s> could not opened. Aborted.\n",ARGUMENT);
      return FALSE;
   }
   sprintf(qFormat,"%%.%de ",NOPTION);   
   sprintf(qFormatNaN,qFormat,0.0);
   memset(qFormatNaN+2,' ',strlen(qFormatNaN+2));
   qFormatNaN[2]=NUMNULLCHR;
   fprintf(pFile,"! [%d..%d][%d..%d] argument=\"%s\" ",NRL,NRH,NCL,NCH,ARGUMENT);
   fprintf(pFile,"xyz=%s\n",ARGUMENT2);
   fprintf(pFile,"!");
   for (k=NCL;k<=NCH;k++) {
      if (!CheckXyzColOption(
         k,ARGUMENT2,*XNO,*XTOTAL,*YNO,*YTOTAL,*ZNO,*ZTOTAL)) continue;
      fprintf(pFile," %d",k);
   }
   fprintf(pFile,"\n");
   nCount=0;
   for (j=NRL;j<=NRH;j++) {
      for (k=NCL;k<=NCH;k++) {
         if (!CheckXyzColOption(
            k,ARGUMENT2,*XNO,*XTOTAL,*YNO,*YTOTAL,*ZNO,*ZTOTAL)) continue;
         if (IsNaNDouble((*MTX)[j][k])) fprintf(pFile,qFormatNaN);
         else fprintf(pFile,qFormat,(*MTX)[j][k]);
         if (j==NRL) nCount++;
      }
      fprintf(pFile,"\n");
   }
   fclose(pFile);

   Echo(" <%s> %dx%d written ...\n",ARGUMENT,NRH-NRL+1,nCount);

   return TRUE;
}

/*----------------------------------------------------------------------------*/

uFuncTableTag uMatrixHandlerTag={
"MatrixHandler",
"type=MatrixHandler                                                          \n"
"argument=c+1,c-1,r+1,r-1                                                    ",
"[Y.Kim] \n"
"Originated by Y.Kim, June 12 2004                                           \n"
"\n"
"[Input] \n"
"argument=[rc][+-]<d>,..,[rc][+-]<d>                                         \n"
"! r/c: row or column operation                                              \n"
"! +/-: add or remove it                                                     \n"
"! <d>: target index of row or column                                         "
};

static
int MatrixHandler( ARGUMENTS )
   ARGULIST
{
   const char *qDeliminator=",";
   int nTotal,nToken,bColumn,nIndex,nDelta,nR,nC;
   char *pToken;
   MATRIX mData;

   NRL=*MRL;
   NRH=*MRH;
   NCL=*MCL;
   NCH=*MCH;

   nTotal=strtokcount(ARGUMENT,qDeliminator);
   for (nToken=0;nToken<nTotal;nToken++) {
      pToken=strtokbyindex(ARGUMENT,qDeliminator,nToken);
      Echo(" %s\n",pToken);
      if (strlen(pToken)<3) continue;
      bColumn=toupper(*pToken)=='C' ? TRUE:FALSE;
      nIndex=atoi(pToken+2);
      nDelta=pToken[1]=='+' ? 1:-1;
      freeEx(pToken);
      if (!bColumn) {
         if (nDelta<0&&NRL==NRH) continue;
         if (nIndex<NRL) continue;
         if (NRH<nIndex) nIndex=NRH+1;
         mData=MCreate(NRL,NRH+nDelta,NCL,NCH);
         for (nR=NRL;nR<nIndex;nR++) {
            for (nC=NCL;nC<=NCH;nC++) {
               mData[nR][nC]=(*MTX)[nR][nC];
            }
         }
         if (nDelta>0) {
            for (nC=NCL;nC<=NCH;nC++) {
               MkNaNDouble(mData[nIndex][nC]);
               mData[nIndex+1][nC]=(*MTX)[nIndex][nC];
            }
         }
         for (nR=nIndex+1;nR<=NRH;nR++) {
            for (nC=NCL;nC<=NCH;nC++) {
               mData[nR+nDelta][nC]=(*MTX)[nR][nC];
            }
         }
         NRH+=nDelta;
      } else if (bColumn) {
         if (nDelta<0&&NCL==NCH) continue;
         if (nIndex<NCL) continue;
         if (NCH<nIndex) nIndex=NCH+1;
         mData=MCreate(NRL,NRH,NCL,NCH+nDelta);
         for (nC=NCL;nC<nIndex;nC++) {
            for (nR=NRL;nR<=NRH;nR++) {
               mData[nR][nC]=(*MTX)[nR][nC];
            }
         }
         if (nDelta>0) {
            for (nR=NRL;nR<=NRH;nR++) {
               MkNaNDouble(mData[nR][nIndex]);
               mData[nR][nIndex+1]=(*MTX)[nR][nIndex];
            }
         }
         for (nC=nIndex+1;nC<=NCH;nC++) {
            for (nR=NRL;nR<=NRH;nR++) {
               mData[nR][nC+nDelta]=(*MTX)[nR][nC];
            }
         }
         NCH+=nDelta;
      }
   }

   if (NRL!=*MRL||NRH!=*MRH||NCL!=*MCL||NCH!=*MCH) {
      Echo(" Matrix dimension has been changed: [%d..%d][%d..%d] to [%d..%d][%d..%d].\n",
         *MRL,*MRH,*MCL,*MCH,NRL,NRH,NCL,NCH);
      MDestroy(*MTX,*MRL,*MRH,*MCL,*MCH);
      *MRL=NRL;
      *MRH=NRH;
      *MCL=NCL;
      *MCH=NCH;
      *MTX=mData;
   }

   return TRUE;
}

/*----------------------------------------------------------------------------*/

uFuncTableTag uMathParserTag={
"MathParser",
"type=MathParser\r\n"
"argument=\"a=a*b\"\r\n"
"! \'a\' and \'b\'in argument represent each column.\r\n",
""
};

static 
int MathParser( ARGUMENTS ) 
   ARGULIST
/*
 *  A B C D E F G ... X  Y  Z
 *  1 2 3 4 5 6 7 ... 24 25 26
 *
 *  e.g of pgm) "a=a+b"
 */
{ 
#define PGM_TOT 10
   double **mtrx;
   int j,k;
   DLL *list;
   DLN *node;
   char qBuffer[1024];
   double result;

   if (!ARGUMENT) {
      errWarning("Error, no program in MathParser()");
      return FALSE;
   }
   Echo(" Eq=\"%s\" \n",ARGUMENT);

   CheckArguments(
      MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH,
      (*XNO)[0],(*YNO)[0],*ZNO?(*ZNO)[0]:0);
   mtrx=*MTX;

   DLLOpen(&list);
   DLLAddTokens(list,ARGUMENT,";");
/*-check-syntax-------*/
   node=list->head;
   while (node) {
      if (!strchr(node->tok,'=')) {
         DLLClose(list);
         errWarning("Error,\"=\" missing at input program in MathParser()");
         return FALSE;
      }
      if (!(isalpha(node->tok[0])&&!isalpha(node->tok[1]))) {
         errWarning("Error, variable error of input program in MathParser()");
         return FALSE;
      }
      node=node->next;
   }
/*-calculate----------*/
#define v_i(c) (toupper(c)-'@')
   for(k=NRL;k<=NRH;k++){
      node=list->head;
      while (node) {
         for (j=strchr(node->tok,'=')-node->tok,j++;
              j<(int)strlen(node->tok);
              j++) {
            if (isalpha(node->tok[j]))
               if ((node->tok[j-1]==' '
               ||  node->tok[j-1]=='+'
               ||  node->tok[j-1]=='-'
               ||  node->tok[j-1]=='*'
               ||  node->tok[j-1]=='/'
               ||  node->tok[j-1]=='%'
               ||  node->tok[j-1]=='^'
               ||  node->tok[j-1]=='='
               ||  node->tok[j-1]=='(') &&
                   (node->tok[j+1]==' '
               ||  node->tok[j+1]=='+'
               ||  node->tok[j+1]=='-'
               ||  node->tok[j+1]=='*'
               ||  node->tok[j+1]=='/'
               ||  node->tok[j+1]=='%'
               ||  node->tok[j+1]=='^'
               ||  node->tok[j+1]=='='
               ||  node->tok[j+1]==')'
               ||  node->tok[j+1]==0))
                  ;
               else
                  continue;
            else
               continue;
            if (NCL<=v_i(node->tok[j])
            &&  v_i(node->tok[j])<=NCH) {
               if (IsNaNDouble(mtrx[k][v_i(node->tok[j])]))
                  goto SKIP;
               sprintf(qBuffer,"%c=%1.9e",
                       node->tok[j],mtrx[k][v_i(node->tok[j])]);
               mathparser(qBuffer,&result);
            }
         }
         setjmp(jb_parser);
         mathparser(node->tok,&result);
         if (NCL<=v_i(node->tok[0])
         &&  v_i(node->tok[0])<=NCH)
            mtrx[k][v_i(node->tok[0])]=result;
         node=node->next;
      }
      SKIP:;
   }
#undef  v_i
/*--------------------*/
   DLLClose(list);
   return TRUE;
}

/*----------------------------------------------------------------------------*/

uFuncTableTag uMathParserExTag={
"MathPaserEx",
"type=MathParserEx \n"
"argument=\"z=z+0\"",
"[Y.Kim]                                                                     \n"
"Once upon a time -  2003.05.22                                              \n"
"                                                                            \n"
"[Input]                                                                     \n"
"argument=\"z=z*1\" option=[a|x|y|z|b|u] xyz=<d>,<d>,<d>-<d>,<d>             \n"
"! where z variable of equation represents matrix element.                   \n"
"! a=all, b=y&z.                                                             \n"
"! If option=u, you can use \"xyz=\".                                         "
};

static int MathParserEx( ARGUMENTS )
   ARGULIST
{ 
   int i,j,k,bSkip;
   char qBuffer[1024];
   double dResult;
   int nAxyz,*aXyz;

   //CheckMatrixBoundary(MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH);
   if (!ARGUMENT) {
      Echo(0,"Error, no program in MathParserEx()");
      return FALSE;
   } else {
      strtolower(ARGUMENT);
      if (!strchr(ARGUMENT,'z')) {
         Echo(0,"Error, \"z\" variable missed in MathParserEx()");
         return FALSE;
      }
   }
   
   Echo(" Eq=\"%s\" opt=%c xyz=%s\n",ARGUMENT,NOPTION<=4 ?NOPTION+'0':NOPTION,ARGUMENT2);

   if (toupper(NOPTION)=='U') {
      getintgerarray(ARGUMENT2,&nAxyz,&aXyz);
   } else {
      aXyz=(int*)(nAxyz=0);
   }

   for (j=NCL;j<=NCH;j++) {
      /*{ Y.Kim,20030212 */
      bSkip=TRUE;
      switch (NOPTION) { 
      case 1 : case 'x' : case 'X' :
         for (k=0;k<*XTOTAL&&bSkip;k++) {if (j==(*XNO)[k]) bSkip=FALSE;}
         break;
      case 2 : case 'y' : case 'Y' :
         for (k=0;k<*YTOTAL&&bSkip;k++) {if (j==(*YNO)[k]) bSkip=FALSE;}
         break;
      case 3 : case 'z' : case 'Z' :
         for (k=0;k<*ZTOTAL&&bSkip;k++) {if (j==(*ZNO)[k]) bSkip=FALSE;}
         break;
      case 4 : case 'b' : case 'B' :
         bSkip=FALSE; /* 20030317 */
         for (k=0;k<*XTOTAL&&!bSkip;k++) {if (j==(*XNO)[k]) bSkip=TRUE;} /* 20030317 */
         break;
      case 'u' : case 'U' : /* 20030522 */
         bSkip=IsInIntVector(j,aXyz,0,nAxyz) ? FALSE:TRUE;
         break;
      }
      if (bSkip) continue;
      /*}*/
      for (i=NRL;i<=NRH;i++) {
         if (IsNaNDouble((*MTX)[i][j])) continue;
         sprintf(qBuffer,"z=%e",(*MTX)[i][j]);
         if (!setjmp(jb_parser)) {
            mathparser(qBuffer,&dResult);
            mathparser(ARGUMENT,&dResult);
         } else {
            sprintf(qBuffer,"Error, [%d][%d],qBuffer=<%s>,ARGUMENT=<%s>"
               "in mathparser()",i,j,qBuffer,ARGUMENT);
            errWarning(qBuffer);
            if (aXyz) free(aXyz);
            return FALSE;
         }
         (*MTX)[i][j]=dResult;
      }
   }
/*
   PrintMatrix(*MTX,NRL,NRH,NCL,NCH);
*/
   if (aXyz) free(aXyz);
   return TRUE;
}

/*----------------------------------------------------------------------------*/

const char *ColumnNormalizer_Help=
"[Y.Kim] \n"
"Created a long time ago.                                                    \n"
"Modified at 30/5/2003                                                       \n"
"\n"
"[Input] \n"
"option=[a|x|y|z|b|u] xyz=<d>,<d>,...,<d>                                \n"
"! a=all=x&y&z, b=y&z.                                                       \n"
"! If option=u, you can use \"xyz=\".                                        \n"
"! Normalize column which matches the option.                                 ";
const char *ColumnNormalizer_Sample=
"type=ColumnNormalizer                                                       \n"
"option=b                                                                     ";
static
int ColumnNormalizer( ARGUMENTS )
   ARGULIST
{ 
   int nRow,nCol,nCount4U,nIndex;
   double dMax;
   const char *qDelimiter=",",*qDoubleDelimiter=",,";
   char *pTok;

   NOPTION=toupper(NOPTION);
   switch (NOPTION) { 
   case 'A' : case 'X' : case 'Y' : case 'Z' : case 'B' : case 'U' :
      Echo("* NOPTION=%c \n",NOPTION);
      break;
   default :
      Echo("* Invalid NOPTION=%c \n",NOPTION);
      return FALSE;
   }
   if (NOPTION=='U') {
      char *pAddr;
      if (!ARGUMENT2 || !ARGUMENT2[0]) return TRUE;
      while (pAddr=strstr(ARGUMENT2,qDoubleDelimiter)) pAddr[1]=' ';
      strtrim(ARGUMENT2);
      while (ARGUMENT2[0] && !isnumchr(ARGUMENT2[0])) strcpy(ARGUMENT2,ARGUMENT2+1);
      if (!(nCount4U=strlen(ARGUMENT2))) return TRUE;
      strreverse(ARGUMENT2);
      while (ARGUMENT2[0] && !isnumchr(ARGUMENT2[0])) strcpy(ARGUMENT2,ARGUMENT2+1);
      if (!(nCount4U=strlen(ARGUMENT2))) return TRUE;
      strreverse(ARGUMENT2);
      nCount4U=chrcount(ARGUMENT2,qDelimiter[0])+1;
   }

   CheckMatrixBoundary(MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH);
   
   for (nCol=NCL;nCol<=NCH;nCol++) {
      switch (NOPTION) {
      case 'X' : if (!IsInIntVector(nCol,*XNO,0,*XTOTAL-1)) continue;break;
      case 'Y' : if (!IsInIntVector(nCol,*YNO,0,*YTOTAL-1)) continue;break;
      case 'Z' : if (!IsInIntVector(nCol,*ZNO,0,*ZTOTAL-1)) continue;break;
      case 'B' : if (!IsInIntVector(nCol,*YNO,0,*YTOTAL-1) && /* 20030303 */
                     !IsInIntVector(nCol,*ZNO,0,*ZTOTAL-1)) continue;break;
      case 'U' : for (nIndex=0;nIndex<nCount4U;nIndex++) {
                    pTok=strtokbyindex(ARGUMENT2,qDelimiter,nIndex);
                    if (nCol==atoi(pTok)) break;
                    freeEx(pTok);
                 }
                 if (pTok) freeEx(pTok);
                 else continue;
                 break;
      }
      dMax=MGetColMaximum(*MTX,NRL,NRH,NCL,NCH,nCol);
      if (dMax==0.0||IsNaNDouble(dMax)) continue;
      for (nRow=NRL;nRow<=NRH;nRow++) {
         if (IsNaNDouble((*MTX)[nRow][nCol])) continue;
         (*MTX)[nRow][nCol]/=dMax;
      }
   }
   return TRUE;
}

/*----------------------------------------------------------------------------*/

const char *ColumnGroupNormalizer_Help=
"[Y.Kim] \n"
"Created a long time ago.                                                    \n"
"Modified at 30/5/2003                                                       \n"
"\n"
"[Input] \n"
"option=[a|x|y|z|b|u] xyz=<d>,<d>,<d>-<d>,<d>                                \n"
"! a=all=x&y&z, b=y&z.                                                       \n"
"! If option=u, you can use \"xyz=\".                                        \n"
"! Normalize column block which matches the option.                           ";
const char *ColumnGroupNormalizer_Sample=
"type=ColumnGroupNormalizer                                                  \n"
"option=b                                                                     ";
static
int ColumnGroupNormalizer( ARGUMENTS )
   ARGULIST
{
   int nRow,nCol,k,nCount4U,nIndex;
   const char *qDelimiter=",",*qDoubleDelimiter=",,";
   char *pTok;
   double dMax,dReturn;
   int *ukTOTAL,**ukNO;

   NOPTION=toupper(NOPTION);
   switch (NOPTION) { 
   case 'A' : case 'X' : case 'Y' : case 'Z' : case 'B' : case 'U' :
      Echo("* NOPTION=%c \n",NOPTION);
      break;
   default :
      Echo("* Invalid NOPTION=%c \n",NOPTION);
      return FALSE;
   }
   if (NOPTION=='U') {
      char *pAddr;
      if (!ARGUMENT2 || !ARGUMENT2[0]) return TRUE;
      while (pAddr=strstr(ARGUMENT2,qDoubleDelimiter)) pAddr[1]=' ';
      strtrim(ARGUMENT2);
      while (ARGUMENT2[0] && !isnumchr(ARGUMENT2[0])) strcpy(ARGUMENT2,ARGUMENT2+1);
      if (!(nCount4U=strlen(ARGUMENT2))) return TRUE;
      strreverse(ARGUMENT2);
      while (ARGUMENT2[0] && !isnumchr(ARGUMENT2[0])) strcpy(ARGUMENT2,ARGUMENT2+1);
      if (!(nCount4U=strlen(ARGUMENT2))) return TRUE;
      strreverse(ARGUMENT2);
      nCount4U=chrcount(ARGUMENT2,qDelimiter[0])+1;
   }

   CheckMatrixBoundary(MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH);
   
   dMax=NUMBER_MAX_NEGATIVE_DOUBLE;
   switch (NOPTION) {
   case 'X' :
   case 'Y' :
   case 'Z' :
      switch (NOPTION) {
      case 'X' : ukTOTAL=XTOTAL;ukNO=XNO;break;
      case 'Y' : ukTOTAL=YTOTAL;ukNO=YNO;break;
      case 'Z' : ukTOTAL=ZTOTAL;ukNO=ZNO;break;
      }
      for (k=0;k<*ukTOTAL;k++) {
         dReturn=MGetColMaximum(*MTX,NRL,NRH,NCL,NCH,(*ukNO)[k]);
         if (IsNaNDouble(dReturn)) continue;
         if (dMax<dReturn) dMax=dReturn;
      }
      break;
   case 'A' :
   case 'B' :
      for (k=0;k<*YTOTAL;k++) {
         dReturn=MGetColMaximum(*MTX,NRL,NRH,NCL,NCH,(*YNO)[k]);
         if (IsNaNDouble(dReturn)) continue;
         if (dMax<dReturn) dMax=dReturn;
      }
      for (k=0;k<*ZTOTAL;k++) {
         dReturn=MGetColMaximum(*MTX,NRL,NRH,NCL,NCH,(*ZNO)[k]);
         if (IsNaNDouble(dReturn)) continue;
         if (dMax<dReturn) dMax=dReturn;
      }
      if (NOPTION=='B') break; /* Y&Z */
      for (k=0;k<*XTOTAL;k++) {
         dReturn=MGetColMaximum(*MTX,NRL,NRH,NCL,NCH,(*XNO)[k]);
         if (IsNaNDouble(dReturn)) continue;
         if (dMax<dReturn) dMax=dReturn;
      }
      break;
   case 'U' :
      for (nIndex=0;nIndex<nCount4U;nIndex++) {
         pTok=strtokbyindex(ARGUMENT2,qDelimiter,nIndex);
         nCol=atoi(pTok);
         freeEx(pTok);
         if (nCol<NCL || NCH<nCol) continue;
         dReturn=MGetColMaximum(*MTX,NRL,NRH,NCL,NCH,nCol);
         if (IsNaNDouble(dReturn)) continue;
         if (dMax<dReturn) dMax=dReturn;
      }
      break;
   }
   
   if (dMax==0.0||IsNaNDouble(dMax)) return TRUE;

   for (nCol=NCL;nCol<=NCH;nCol++) {
      switch (NOPTION) {
      case 'X' : if (!IsInIntVector(nCol,*XNO,0,*XTOTAL-1)) continue;break;
      case 'Y' : if (!IsInIntVector(nCol,*YNO,0,*YTOTAL-1)) continue;break;
      case 'Z' : if (!IsInIntVector(nCol,*ZNO,0,*ZTOTAL-1)) continue;break;
      case 'A' : if (!IsInIntVector(nCol,*XNO,0,*XTOTAL-1) && /* 20030303 */
                     !IsInIntVector(nCol,*YNO,0,*YTOTAL-1) && /* 20030303 */
                     !IsInIntVector(nCol,*ZNO,0,*ZTOTAL-1)) continue;break;
      case 'B' : if (!IsInIntVector(nCol,*YNO,0,*YTOTAL-1) && /* 20030303 */
                     !IsInIntVector(nCol,*ZNO,0,*ZTOTAL-1)) continue;break;
      case 'U' : for (nIndex=0;nIndex<nCount4U;nIndex++) {
                    pTok=strtokbyindex(ARGUMENT2,qDelimiter,nIndex);
                    if (nCol==atoi(pTok)) break;
                    freeEx(pTok);
                 }
                 if (pTok) freeEx(pTok);
                 else continue;
                 break;
      }
      for (nRow=NRL;nRow<=NRH;nRow++) {
         if (IsNaNDouble((*MTX)[nRow][nCol])) continue;
         (*MTX)[nRow][nCol]/=dMax;
      }
   }
   return TRUE;
}

/*----------------------------------------------------------------------------*/

const char *ColumnNoiseCleaner_Help=
"[Y.Kim] \n"
"Created a long time ago.                                                    \n"
"Modified at 2003.6.19-20,8.18                                               \n"
"\n"
"[Input] \n"
"option=[a|x|y|z|b|u] suboption=[-1|0|1] xyz=<d>,<d>,<d>-<d>,<d>             \n"
"argument=<d>,<d>                                                            \n"
"! option: a=all=x&y&z, b=y&z. If option=u, you can use <xyz=>.              \n"
"! suboption=0: Default. Noise data is smoothed/replaced by a new value.     \n"
"! suboption=1: Noise data is cleaned, i.e., changed into Nan.               \n"
"! suboption=-1: Same with \"suboption=1\" except that argument values are regarded \n"
"!      as a value in data scale, not in stddev scale. \n"
"! argument=<d>,<d>: Two numbers concerning to postive and negative side data. \n"
"! Noise will be filtered based on each column data population.              \n"
"! For \"suboption=0 or 1\", data outside the stdev multiplied by the argument value are identified to noise.\n"
"! For \"suboption=-1\", data outside the argument value are identified to noise. ";
const char *ColumnNoiseCleaner_Sample=
"type=ColumnNoiseCleaner                                                     \n"
"option=b suboption=0 argument=3,3                                            ";
static
int ColumnNoiseCleaner( ARGUMENTS )
   ARGULIST
{ 
   char *pTok,*qDelimiter=",";
   int nRow,nCol,nColumn,nCount,nCountSum;
   VECTOR vColumn;
   double dMinFactor,dMaxFactor,dStdevPositiveSide,dStdevNegativeSide,
      dMin,dMax,dMed,dValue;
   int nAxyz,*aXyz;

   /* NOPTION */
   NOPTION=toupper(NOPTION);
   switch (NOPTION) { 
   case 'A' : case 'X' : case 'Y' : case 'Z' : case 'B' : case 'U' :
      if (NOPTION=='U') getintgerarray(ARGUMENT2,&nAxyz,&aXyz);
      else aXyz=(int*)(nAxyz=0);
      Echo(" NOPTION=%c \n",NOPTION);
      break;
   default :
      Echo(0," Invalid NOPTION=%c \n",NOPTION);
      return FALSE;
   }
   /* ARGUMENT */
   if (strtokcount(ARGUMENT,qDelimiter)!=2) {
      Echo(0," Number of <argument=> parameter does not equal 2.\n");
      return FALSE;
   }
   dMinFactor=atof(pTok=strtokbyindex(ARGUMENT,qDelimiter,0));freeEx(pTok);
   dMaxFactor=atof(pTok=strtokbyindex(ARGUMENT,qDelimiter,1));freeEx(pTok);
   if (NSUBOPTION<0&&dMinFactor==dMaxFactor) {
      Echo(0," Values of <argument=> parameter equal together.\n");
      return FALSE;
   }

   /* Boundary Check */
   CheckMatrixBoundary(MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH);
   
   /* Clean */
   nCountSum=0;
   for (nCol=NCL;nCol<=NCH;nCol++) {
      switch (NOPTION) {
      case 'X' : if (!IsInIntVector(nCol,*XNO,0,*XTOTAL-1)) continue;break;
      case 'Y' : if (!IsInIntVector(nCol,*YNO,0,*YTOTAL-1)) continue;break;
      case 'Z' : if (!IsInIntVector(nCol,*ZNO,0,*ZTOTAL-1)) continue;break;
      case 'B' : if (!IsInIntVector(nCol,*YNO,0,*YTOTAL-1) && /* 20030303 */
                     !IsInIntVector(nCol,*ZNO,0,*ZTOTAL-1)) continue;break;
      case 'U' : if (!IsInIntVector(nCol,aXyz,0,nAxyz)) continue;break;
      }
      if (NRL==NRH) continue;
      MGetVector(*MTX,TRUE,nCol,NRL,NRH,&vColumn);
      VChangeBase(&vColumn,NRL,1);
      nColumn=NRH-NRL+1;
      switch (NSUBOPTION) {
      case 0 :
         mdian2(vColumn,nColumn,&dMed);
         dStdevPositiveSide=VGetOneSideStdev(vColumn,1,nColumn,dMed,TRUE);
         dStdevNegativeSide=VGetOneSideStdev(vColumn,1,nColumn,dMed,FALSE);
         dMin=dMed-dMinFactor*dStdevNegativeSide;
         dMax=dMed+dMaxFactor*dStdevPositiveSide;
         break;
      default:
         dMin=dMinFactor;
         dMax=dMaxFactor;
         break;
      }
      nCount=0;
      for (nRow=NRL;nRow<=NRH;nRow++) {
         dValue=(*MTX)[nRow][nCol];
         if (IsNaNDouble(dValue)) continue;
         if (dValue<=dMin||dValue>=dMax) {
            if (NSUBOPTION==0) {
               int j;
               double dFormer,dLatter;
               MkNaNDouble(dFormer);
               MkNaNDouble(dLatter);
               for (j=nRow-1;j>=NRL;j--) {
                  dFormer=(*MTX)[j][nCol];
                  if (!IsNaNDouble(dFormer)) break;
               }
               for (j=nRow+1;j<=NRH;j++) {
                  dLatter=(*MTX)[j][nCol];
                  if (!IsNaNDouble(dLatter)) break;
               }
               if (IsNaNDouble(dFormer)&&IsNaNDouble(dLatter))
                  MkNaNDouble((*MTX)[nRow][nCol]);
               else if (!IsNaNDouble(dFormer)&&IsNaNDouble(dLatter))
                  (*MTX)[nRow][nCol]=dFormer;
               else if (IsNaNDouble(dFormer)&&!IsNaNDouble(dLatter))
                  (*MTX)[nRow][nCol]=dLatter;
               else
                  (*MTX)[nRow][nCol]=(dFormer+dLatter)/2.;
            } else 
               MkNaNDouble((*MTX)[nRow][nCol]);
            nCount++;
         }
      }
      if (IsNaNDouble(MGetColMaximum(*MTX,NRL,NRH,NCL,NCH,nCol))) {
         VChangeBase(&vColumn,1,NRL);
         for (nRow=NRL;nRow<=NRH;nRow++) (*MTX)[nRow][nCol]=vColumn[nRow];
         VChangeBase(&vColumn,NRL,1);
         nCount=0;
         Echo(" %d column is bound to be cleared all. Aborted.\n",nCol);
      }
      nCountSum+=nCount;
      VDestroy(vColumn,1,nColumn);
   }
   Echo(" Criteria for noise are %g and %g in %s scale.\n",
      dMinFactor,dMaxFactor,NSUBOPTION<0?"real":"sigma");
   Echo(" Total %d number of data are %s.\n",nCountSum,NSUBOPTION?"cleared":"smoothed");
   if (aXyz) free(aXyz);
   return TRUE;
}

/*----------------------------------------------------------------------------*/

static
int ColumnTangentSloper( ARGUMENTS )
   ARGULIST
/*
 *  e.g) option=[y|z|b] 
 *                   b -> y&z
 *  Fill out tangent slopes of each column which matches the option.
 */
{ 
   int nRow,nCol;

   NOPTION=toupper(NOPTION);
   switch (NOPTION) {
   case 'Y' : case 'Z' : case 'B' : Echo("* NOPTION=%c \n",NOPTION);break;
   default : Echo("* Invalid NOPTION=%c \n",NOPTION);return FALSE;
   }

   CheckMatrixBoundary(MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH);
   
   for (nCol=NCL;nCol<=NCH;nCol++) {
      switch (NOPTION) {
      case 'Y' : if (!IsInIntVector(nCol,*YNO,0,*YTOTAL-1)) continue;break;
      case 'Z' : if (!IsInIntVector(nCol,*ZNO,0,*ZTOTAL-1)) continue;break;
      case 'B' : if (!IsInIntVector(nCol,*YNO,0,*YTOTAL-1) && /* 20030303 */
                     !IsInIntVector(nCol,*ZNO,0,*ZTOTAL-1)) continue;break;
      }
      for (nRow=NRL;nRow<=NRH;nRow++) {
         ; /* ???? */
      }
   }
   return TRUE;
}

static
int GetInterpolatedValue( ARGUMENTS )
   ARGULIST
/*
 *  e.g) option=[0] argument=<d>
 *  option : interpolation method for x-y curve.
 *           0 -> polymoial interplation
 *  argument : x axis value to interpolate.
 */
{ 
   VECTOR vX,vY;
   int nRow,nIndex,nStart,nEnd,nCount,nXY5;
   double dValue,vX5[6],vY5[6],y,dy;

   if (!*XNO||!*XTOTAL) return FALSE;
   if (!ARGUMENT||!*ARGUMENT) return FALSE;
   dValue=atof(ARGUMENT);
   nXY5=sizeof(vX5)/sizeof(vX5[0])-1; /* 5 */

   CheckMatrixBoundary(MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH);

   Echo(".interpolation results at x-axis %.3e : \n",dValue);
   
   for (nRow=0;*YNO&&*YTOTAL&&nRow<*YTOTAL;nRow++) {
      MGetVector(*MTX,TRUE,(*XNO)[nRow],NRL,NRH,&vX);
      MGetVector(*MTX,TRUE,(*YNO)[nRow],NRL,NRH,&vY);
      if (!VGetValueIndexOfMonotonicVector(vX,NRL,NRH,dValue,&nIndex)) goto N;
      nStart=MAX(NRL,nIndex-(nXY5>>1));
      nEnd=MIN(NRH,nIndex+(nXY5>>1));
      nCount=0;
      for (nIndex=nStart;nIndex<=nEnd;nIndex++) {
         if (IsNaNDouble(vX[nIndex])||IsNaNDouble(vY[nIndex])) break;
         vX5[nCount]=vX[nIndex];
         vY5[nCount]=vY[nIndex];
         nCount++;
      }
      if (nCount>=2) {
         /* Press,Numerical Receipes in C,p.90 */
         polint(vX5,vY5,nCount,dValue,&y,&dy);
         Echo(
            ".for (%d,%d) pair, y is %.3e with an error %g \n",
            (*XNO)[nRow],(*YNO)[nRow],y,dy);
      }
N:    VDestroy(vX,NRL,NRH);
      VDestroy(vY,NRL,NRH);
   }

   return TRUE;
}

/*----------------------------------------------------------------------------*/

/* 표준정규누적분포
 * Standard Normalization CDF (Cumulative Density of Function)
 * like in Excel Spread Sheet Function
 */
static 
int NORMSDIST( ARGUMENTS )
   ARGULIST
/*
 * DCL : standard deviation
 */
{ 
/*
   double **mtrx;
   int i,j;
   double dRowStep,dColStep,dColValue;
   
   CheckArguments(MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH, 
                  (*XNO)[0],(*YNO)[0],*ZNO?(*ZNO)[0]:0);
   mtrx=*MTX;

   switch (YSCALE) {
   case SCALE_LIN :
      dRowStep=(DRH-DRL)/(NRH-NRL);
      dColStep=(NCH-NCL)==1 ? DCL2:(DCH-DCL2)/(NCH-NCL-1);
      Echo("   row : l=%.2e,h=%.2e,step=%.2e\n",DRL,DRH,dRowStep);
      Echo("   col : l2=%.2e,h=%.2e,step=%.2e\n",DCL2,DCH,dColStep);
      for (i=NRL;i<=NRH;i++)
         mtrx[i][NCL]=DRL+(i-NRL)*dRowStep; 
      for (j=NCL+1;j<=NCH;j++) {
         dColValue=DCL2+dColStep*(j-(NCL+1));
         for (i=NRL;i<=NRH;i++)
            mtrx[i][j]=cnorm(mtrx[i][NCL],0.0,dColValue);
      }
      break;
   case SCALE_LOG10 :
      DRH=log10(DRH);DRL=log10(DRL);
      DCL2=log10(DCL2);DCH=log10(DCH);
      dRowStep=(DRH-DRL)/(NRH-NRL);
      dColStep=(NCH-NCL)==1 ? DCL2:(DCH-DCL2)/(NCH-NCL-1);
      Echo("   row : l=%.2e,h=%.2e,step=%.2e\n",DRL,DRH,dRowStep);
      Echo("   col : l2=%.2e,h=%.2e,step=%.2e\n",DCL2,DCH,dColStep);
      for (i=NRL;i<=NRH;i++)
         mtrx[i][NCL]=DRL+(i-NRL)*dRowStep;
      * pow10(DRL+(i-NRL)*dRowStep); *
      for (j=NCL+1;j<=NCH;j++) {
         dColValue=DCL2+dColStep*(j-(NCL+1));
         for (i=NRL;i<=NRH;i++)
            mtrx[i][j]=cnorm(mtrx[i][NCL],0.0,dColValue);
      }  
      for (i=NRL;i<=NRH;i++)
         mtrx[i][NCL]=pow10(mtrx[i][NCL]);
      break;
   }
*/
   return TRUE;
}

/*----------------------------------------------------------------------------*/

static
int FstDiffMaxFit( ARGUMENTS )
   ARGULIST
{
   double **mtrx;
   register int i;
   double tmp_slope,max_slope,delta;
   int max_slope_i=0;

   CheckArguments(MTX,MRL,MRH,MCL,MCH,&NRL,&NRH,&NCL,&NCH,
                  (*XNO)[0],(*YNO)[0],*ZNO?(*ZNO)[0]:0);
   mtrx=*MTX;

   tmp_slope=0.0;
   max_slope=0.0;
   max_slope_i=0;
   delta=0.0;
   for (i=NRL;i<NRH;i++) {
     delta=mtrx[i+1][(*XNO)[0]]-mtrx[i][(*XNO)[0]];
     if (delta) {
        tmp_slope=ABS((mtrx[i+1][(*YNO)[0]]-mtrx[i][(*YNO)[0]])/delta);
        if (max_slope<tmp_slope) {
           max_slope=tmp_slope;
           max_slope_i=i+1;
        }
     }
   }
   NRL=max_slope_i-1;
   NRH=max_slope_i;
   NOPTION=1;
   Echo("fit [%d...%d][%d]\n",NRL,NRH,(*YNO)[0]);
   Echo("max slope = %1.5e\n",max_slope);
   PolynomialFit95( ARGUMENTS );
   return TRUE;
}

/*- Useful Function ----------------------------------------------------------*/

int GetFittingRange( vX,nRL,nRH,nFitTotal,dL,dH,nL,nH )
   VECTOR vX;
   int nRL,nRH,nFitTotal,*nL,*nH;
   double dL,dH;
{
   int nRow;
   double dMin,dMax;
   *nL=*nH=0;
   VGetMinMaxValue(vX,nRL,nRH,&dMin,&dMax); //20040216
   if (dMin>dL) dL=dMin;
   if (dMax<dH) dH=dMax;
   if (VGetValueIndexOfMonotonicVector(vX,nRL,nRH,dL,nL)) {
      if (!VGetValueIndexOfMonotonicVector(vX,nRL,nRH,dH,nH)) {
         //Echo(0,"Could not find upper range %g in your data.\n",dH);
         return FALSE;
      }
      if (vX[*nL]<dL) (*nL)+=SIGN(*nH-*nL);
      if (vX[*nH]>dH) (*nH)-=SIGN(*nH-*nL);
   } else {
      //Echo(0,"Could not find lower range %g in your data.\n",dL);
      return FALSE;
   }
   if (*nL>*nH) SWAP(*nL,*nH);
   if ((nRow=(*nH-*nL+1))<nFitTotal) {
      //Echo(0,"Your range is too short to fit. Counted %d.\n",nRow);
      return FALSE;
   }
   return *nH-*nL+1; /* 20030620 */
}

/******************************************************************************/
/* usrfunc.c */
