/******************************************************************************/

const char *TwoFreqCapacitanceModel_Help=
"[Y.Kim]                                                                     \n"
"2003.04.26                                                                  \n"
"2004.12.24                                                                  \n"
"                                                                            \n"
"[Reference]                                                                 \n"
"Kevin J. Yang and Chenming Hu,                                              \n"
"\"MOS Capacitance Measurements for High-Leakage Thin Dielectrics,\"         \n"
"IEEE Trans.Elec.Dev. 46[7]1500(1999)                                        \n"
"                                                                            \n"
"[Input]                                                                     \n"
"ARGUMENT=<Vg>,<C1>,<D1>,<C2>,<D2>:<F1>,<F2>                                 \n"
"! Vg,C1,D1,C2,D2 are all column index, not a real number.                   \n"
"! F1 and F2 are frequency in Hz unit for C and D with the same subscript.   \n"
"OPTION=[0|1]                                                                \n"
"! 0=NotUse, 1=Use absolute inside sqrt for Rp calculation.                  \n"
"SUBOPTION=NA                                                                \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! Add three columns : Rs,Rp,CorrectedCapacitance                            \n"
"! Matrix Addition : [nrl..nrh][ncl..nch+3] <-- [nrl..nrh][ncl..nch]         ";

const char *TwoFreqCapacitanceModel_Sample=
"type=TwoFreqCapacitanceModel                                                \n"
"argument=1,2,3,4,5:1e6,1e5 option=0                                         ";

/******************************************************************************/

#include <math.h>
#include "str.h"
#include "nrecipe.h"
#include "number.h"
#include "usrfunc.h"

extern int Echo();

/******************************************************************************/

int TwoFreqCapacitanceModel( ARGUMENTS )
   ARGULIST
{
   char *pTok,*qDelimiter=",:;";
   int nIndex,nColVg,nC1,nD1,nC2,nD2,nColRs,nColRp,nColCC,bSucceeded;
   double dF1,dC1,dD1,dF2,dC2,dD2,dFF1,dFF2,dDD1,dDD2,dFactor,dCC,dRs,dRp;
   MATRIX M;

   Echo(" V.1.1\n");
   Echo(" option=%d (%s Absolute Square)\n",NOPTION,NOPTION==0 ? "Not Used":"Used");

   if (strtokcount(ARGUMENT,qDelimiter)!=7) {
      Echo(0,"Error, no 7 arguments at the expression of <ARGUMENT=>\n");
      return FALSE;
   }
   for (nIndex=0;nIndex<=6;nIndex++) {
      pTok=strtokbyindex(ARGUMENT,qDelimiter,nIndex);
      switch (nIndex) {
      case 0 : nColVg=atoi(pTok);break;
      case 1 : nC1=atoi(pTok);break;
      case 2 : nD1=atoi(pTok);break;
      case 3 : nC2=atoi(pTok);break;
      case 4 : nD2=atoi(pTok);break;
      case 5 : dF1=atof(pTok);break;
      case 6 : dF2=atof(pTok);break;
      }
      freeEx(pTok);
   }
   Echo(" iVg,iC1,iD1,iC2,iD2=%d,%d,%d,%d,%d\n",nColVg,nC1,nD1,nC2,nD2);
   Echo(" dF1,dF2=%g,%gHz\n",dF1,dF2);
   
   M=*MTX;
   MInflate(&M,*MRL,*MRH,*MCL,*MCH,*MRH,*MCH+3);
   *MTX=M;
   *MCH+=3;
   nColRs=*MCH-2;
   nColRp=nColRs+1;
   nColCC=nColRs+2;

   bSucceeded=FALSE;
   dFF1=dF1*dF1;
   dFF2=dF2*dF2;
   for (nIndex=*MRL;nIndex<=*MRH;nIndex++) {
      dC1=M[nIndex][nC1];
      dD1=M[nIndex][nD1];
      dC2=M[nIndex][nC2];
      dD2=M[nIndex][nD2];
      dDD1=dD1*dD1;
      dDD2=dD2*dD2;
      dCC=(dFF2*dC2*(dDD2+1)-dFF1*dC1*(dDD1+1))/(dFF2-dFF1);
      dFactor=dC1/dCC*(dDD1+1)-1;
      if (NOPTION) dFactor=ABS(dFactor);
      if (dFactor>0) {
         //dRp=1/sqrt(dFF1*dCC*dC1*(dDD1+1)-pow(dF1*dCC,2));
         dRp=1/(dF1*dCC*sqrt(dFactor));
         dRs=dD1/(dF1*dC1*(dDD1+1))-dRp/(1+pow(dF1*dRp*dCC,2));
         bSucceeded=TRUE;
      } else {
         MkNaNDouble(dRs);
         MkNaNDouble(dRp);
      }
      M[nIndex][nColRs]=dRs;
      M[nIndex][nColRp]=dRp;
      M[nIndex][nColCC]=dCC;
   }
   if (!bSucceeded) Echo(" Warning: Model is not able to describe the data.\n");

   Echo(" Matrix has been inflated: [*][%d..%d] to [*][%d..%d]\n",
      NCL,NCH,*MCL,*MCH);

   return TRUE;
}

/******************************************************************************/
/* uTwoFreqCapacitanceModel.c */

