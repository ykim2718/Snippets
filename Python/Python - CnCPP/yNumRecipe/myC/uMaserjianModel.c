/******************************************************************************/

#define MOUDLENAME "MaserjianModel()"

const char *MaserjianModel_Help=
"[Y.Kim]                                                                     \n"
"2003.0517,0928                                                              \n"
"                                                                            \n"
"[Source]                                                                    \n"
"J.Maserjian, G.Petersson and C.Svensson,                                    \n"
"\"Saturation Capacitance of Thin Oxide MOS Structures and the Effective     \n"
"Surface Density of States of Silicon,\"                                     \n"
"Solid-State Electronics,v.17,pp.335-339,1974.                               \n"
"                                                                            \n"
"[Input]                                                                     \n"
"xy=x,y                                                                      \n"
"! The first is x column index, which is gate voltage in [V].                \n"
"! The second is y column index, which is gate capacitance in [F/cm^2].      \n"
"range=<l>,<h>                                                               \n"
"! l: lower limit of gate voltage to fit. If not, data minimum.              \n"
"! h: upper limit of gate voltage to fit. If not, data maximum.              \n"
"! * Range should cover degenerate accumulation region.                      \n"
"                                                                            \n"
"[Output]                                                                    \n"
"! See Log window.   ";

const char *MaserjianModel_Sample=
"type=MaserjianModel                                                         \n"
"xy=1,2 range=-1,1                                                           ";

/******************************************************************************/

#include <math.h>
#include "usrfunc.h"
#include "nrecipe.h"
#include "number.h"
#include "tools.h"
#include "str.h"
#include "semiconductor.h"

extern int Echo();

/******************************************************************************/

int MaserjianModel( ARGUMENTS )
   ARGULIST
{
   char *pTok,*qDelimiter=",()";
   int bResult,iX,iY,nL,nH,i;
   VECTOR vX,vY,vXX,vSlope,vYY;
   double dRL,dRH,dMin,dMax,dSlope,dYIntercept,dChi2,dR2;

   vX=vY=vXX=vSlope=vYY=(VECTOR)0;

   //Version
   Echo(" V.0.9");

   //Check "XY"
   if (strtokcount(ARGUMENT2,qDelimiter)!=2) {
      Echo(0,"Option count is not 2 at the expression of <XY=>\n");
      goto E;
   }
   iX=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,0));freeEx(pTok);
   iY=atoi(pTok=strtokbyindex(ARGUMENT2,qDelimiter,1));freeEx(pTok);
   if (strtokcount(ARGUMENT2,qDelimiter)!=2) {
      Echo(0,"\n%s\nNot enough parameter at <XY=>\n",MOUDLENAME);
      goto E;
   }
   //Check "RANGE" and allocate X&Y Vectors
   MGetSafeVectorPair(*MTX,TRUE,NRL,NRH,iX,iY,&vX,&vY,&NRL,&NRH);
   VGetMinMaxValue(vX,NRL,NRH,&dMin,&dMax);
   if (SWEEP&&*SWEEP) {
      pTok=strtokbyindex(SWEEP,qDelimiter,0);
      dRL=pTok[0]=='*' ? dMin:atof(pTok);
      freeEx(pTok);
      pTok=strtokbyindex(SWEEP,qDelimiter,1);
      dRH=pTok[0]=='*' ? dMax:atof(pTok);
      freeEx(pTok);
   } else {
      Echo(0,"\n%s\n<RANGE=> missed ...\n",MOUDLENAME);
      goto E;
   }
   if (dMin>dRL) dRL=dMin;
   if (dMax<dRH) dRH=dMax;
   

   Echo(" xy=%d,%d range[V]=%.3g,%.3g\n",iX,iY,dRL,dRH);

   //Find fit range
   if (VGetValueIndexOfMonotonicVector(vX,NRL,NRH,dRL,&nL)) {
      if (!VGetValueIndexOfMonotonicVector(vX,NRL,NRH,dRH,&nH)) {
         Echo(0,"\n%s\nCould not find upper gate voltage in data. You wanted %g.",
            MOUDLENAME,dRH);
         goto E;
      }
   } else {
      Echo(0,"%s\nCould not find lower gate voltage in data. You wanted %g.",
         MOUDLENAME,dRL);
      goto E;
   }
   if (nL>nH) SWAP(nL,nH);
   if ((i=(nH-nL+1))<5) {
      Echo(0,"%s\nYour gate volrage range is too short to fit. Counted %d.",
         MOUDLENAME,i);
      goto E;
   }

   for (i=nL;i<=nH;i++) {
      if (vY[i]==0) {
         Echo(0,"%s\nFound zero value at [%d][%d]",MOUDLENAME,i,iY);
         goto E;
      }
   }

   //Calculate
   bResult=TRUE;
   vXX=VCreate(nL,nH);
   vYY=VCreate(nL,nH);
   VGetSlopeVector(vX,vY,nL,nH,FALSE,&vSlope);
   for (i=nL;i<=nH;i++) {
      vXX[i]=1/vY[i];
      vYY[i]=sqrt(vXX[i])*pow(vSlope[i],(double)1/6); /* 1/4 ??? */
   }
   dChi2=xfit(vXX+nL-1,vYY+nL-1,nH-nL+1,&dYIntercept,&dSlope);
   for (i=nL;i<=nH;i++) vY[i]=dYIntercept+dSlope*vX[i];
   dR2=GetPearsonR2(vY,vYY,nL,nH);
   Echo(" s=%.2e yi=%.2e r2=%.3f\n",dSlope,dYIntercept,dR2);
   Echo(" EOT[nm]=%g\n",VacPermittivity*RDCOxide*dYIntercept/cmovernm);
   if (dYIntercept<=0) Echo(" WATCH-OUT! Results have ERRORs.\n");

E: if (vX) VDestroy(vX,NRL,NRH);
   if (vY) VDestroy(vY,NRL,NRH);
   if (vXX) VDestroy(vXX,nL,nH);
   if (vSlope) VDestroy(vSlope,nL,nH);
   if (vYY) VDestroy(vYY,nL,nH);
   return bResult;
}

/******************************************************************************/
/* MaserjianModel.c */
